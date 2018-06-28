#include "masternodelist.h"
#include "ui_masternodelist.h"

#include "activemasternode.h"
#include "clientmodel.h"
#include "guiutil.h"
#include "init.h"
#include "masternode-sync.h"
#include "masternodeconfig.h"
#include "masternodeman.h"
#include "sync.h"
#include "util.h"
#include "wallet/wallet.h"
#include "walletmodel.h"

#include <QMessageBox>
#include <QTextStream>
#include <QTimer>
#include <QDesktopServices>
#include <QFile>
#include <QMap>

MasternodeList::MasternodeList(const PlatformStyle* platformStyle, QWidget* parent) : QWidget(parent),
                                                                                      ui(new Ui::MasternodeList),
                                                                                      clientModel(0),
                                                                                      walletModel(0)
{
    ui->setupUi(this);

    ui->startButton->setEnabled(false);

    int columnAliasWidth = 100;
    int columnAddressWidth = 200;
    int columnProtocolWidth = 60;
    int columnStatusWidth = 80;
    int columnActiveWidth = 130;
    int columnLastSeenWidth = 130;

    ui->tableWidgetMyMasternodes->setColumnWidth(0, columnAliasWidth);
    ui->tableWidgetMyMasternodes->setColumnWidth(1, columnAddressWidth);
    ui->tableWidgetMyMasternodes->setColumnWidth(2, columnProtocolWidth);
    ui->tableWidgetMyMasternodes->setColumnWidth(3, columnStatusWidth);
    ui->tableWidgetMyMasternodes->setColumnWidth(4, columnActiveWidth);
    ui->tableWidgetMyMasternodes->setColumnWidth(5, columnLastSeenWidth);

    ui->tableWidgetMasternodes->setColumnWidth(0, columnAddressWidth);
    ui->tableWidgetMasternodes->setColumnWidth(1, columnProtocolWidth);
    ui->tableWidgetMasternodes->setColumnWidth(2, columnStatusWidth);
    ui->tableWidgetMasternodes->setColumnWidth(3, columnActiveWidth);
    ui->tableWidgetMasternodes->setColumnWidth(4, columnLastSeenWidth);

    ui->tableWidgetMyMasternodes->setContextMenuPolicy(Qt::CustomContextMenu);

    QAction* startAliasAction = new QAction(tr("Start alias"), this);
    contextMenu = new QMenu();
    contextMenu->addAction(startAliasAction);
    connect(ui->tableWidgetMyMasternodes, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));
    connect(startAliasAction, SIGNAL(triggered()), this, SLOT(on_startButton_clicked()));
    
    ui->pushButtonAddMaster->setVisible(true);
    ui->buttonDocument->setVisible(false);
    ui->masternodeOnlineButton->setVisible(false);
    ui->pushButtonSaveAll->setEnabled(true);
    ui->pushButtonSaveMaster->setEnabled(true);
    ui->pushButtonSaveConfig->setEnabled(true);

    connect(ui->pushButtonAddMaster, SIGNAL(clicked()), this, SLOT(on_ButtonAddMaster_clicked()));
    connect(ui->pushButtonSaveAll, SIGNAL(clicked()), this, SLOT(on_ButtonSaveAll_clicked()));
    connect(ui->pushButtonSaveConfig, SIGNAL(clicked()), this, SLOT(on_ButtonSaveConfig_clicked()));
    connect(ui->pushButtonSaveMaster, SIGNAL(clicked()), this, SLOT(on_ButtonSaveMaster_clicked())); 
    connect(ui->buttonDocument, SIGNAL(clicked()), this, SLOT(on_ButtonDocument_clicked()));
    connect(ui->pushButtonLoad, SIGNAL(clicked()), this, SLOT(loadMasterConfigFile()));
        
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateNodeList()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMyNodeList()));
    timer->start(1500);

    fFilterUpdated = false;
    nTimeFilterUpdated = GetTime();
    updateNodeList();
    loadMasterConfigFile();
}

MasternodeList::~MasternodeList()
{
    delete ui;
}

void MasternodeList::setClientModel(ClientModel* model)
{
    this->clientModel = model;
    if (model) {
        // try to update list when masternode count changes
        connect(clientModel, SIGNAL(strMasternodesChanged(QString)), this, SLOT(updateNodeList()));
    }
}

void MasternodeList::setWalletModel(WalletModel* model)
{
    this->walletModel = model;
}

void MasternodeList::showContextMenu(const QPoint& point)
{
    QTableWidgetItem* item = ui->tableWidgetMyMasternodes->itemAt(point);
    if (item)
        contextMenu->exec(QCursor::pos());
}

void MasternodeList::StartAlias(std::string strAlias)
{
    std::string strStatusHtml;
    strStatusHtml += "<center>Alias: " + strAlias;

    BOOST_FOREACH (CMasternodeConfig::CMasternodeEntry mne, masternodeConfig.getEntries()) {
        if (mne.getAlias() == strAlias) {
            std::string strError;
            CMasternodeBroadcast mnb;

            bool fSuccess = CMasternodeBroadcast::Create(mne.getIp(), mne.getPrivKey(), mne.getTxHash(), mne.getOutputIndex(), strError, mnb);

            if (fSuccess) {
                strStatusHtml += "<br>Successfully started masternode.";
                mnodeman.UpdateMasternodeList(mnb);
                mnb.Relay();
                mnodeman.NotifyMasternodeUpdates();
            } else {
                strStatusHtml += "<br>Failed to start masternode.<br>Error: " + strError;
            }
            break;
        }
    }
    strStatusHtml += "</center>";

    QMessageBox msg;
    msg.setText(QString::fromStdString(strStatusHtml));
    msg.exec();

    updateMyNodeList(true);
}

void MasternodeList::StartAll(std::string strCommand)
{
    int nCountSuccessful = 0;
    int nCountFailed = 0;
    std::string strFailedHtml;

    BOOST_FOREACH (CMasternodeConfig::CMasternodeEntry mne, masternodeConfig.getEntries()) {
        std::string strError;
        CMasternodeBroadcast mnb;

        int32_t nOutputIndex = 0;
        if (!ParseInt32(mne.getOutputIndex(), &nOutputIndex)) {
            continue;
        }

        CTxIn txin = CTxIn(uint256S(mne.getTxHash()), nOutputIndex);

        if (strCommand == "start-missing" && mnodeman.Has(txin))
            continue;

        bool fSuccess = CMasternodeBroadcast::Create(mne.getIp(), mne.getPrivKey(), mne.getTxHash(), mne.getOutputIndex(), strError, mnb);

        if (fSuccess) {
            nCountSuccessful++;
            mnodeman.UpdateMasternodeList(mnb);
            mnb.Relay();
            mnodeman.NotifyMasternodeUpdates();
        } else {
            nCountFailed++;
            strFailedHtml += "\nFailed to start " + mne.getAlias() + ". Error: " + strError;
        }
    }
    pwalletMain->Lock();

    std::string returnObj;
    returnObj = strprintf("Successfully started %d masternodes, failed to start %d, total %d", nCountSuccessful, nCountFailed, nCountFailed + nCountSuccessful);
    if (nCountFailed > 0) {
        returnObj += strFailedHtml;
    }

    QMessageBox msg;
    msg.setText(QString::fromStdString(returnObj));
    msg.exec();

    updateMyNodeList(true);
}

void MasternodeList::updateMyMasternodeInfo(QString strAlias, QString strAddr, masternode_info_t& infoMn)
{
    bool fOldRowFound = false;
    int nNewRow = 0;

    for (int i = 0; i < ui->tableWidgetMyMasternodes->rowCount(); i++) {
        if (ui->tableWidgetMyMasternodes->item(i, 0)->text() == strAlias) {
            fOldRowFound = true;
            nNewRow = i;
            break;
        }
    }

    if (nNewRow == 0 && !fOldRowFound) {
        nNewRow = ui->tableWidgetMyMasternodes->rowCount();
        ui->tableWidgetMyMasternodes->insertRow(nNewRow);
    }

    QTableWidgetItem* aliasItem = new QTableWidgetItem(strAlias);
    QTableWidgetItem* addrItem = new QTableWidgetItem(infoMn.fInfoValid ? QString::fromStdString(infoMn.addr.ToString()) : strAddr);
    QTableWidgetItem* protocolItem = new QTableWidgetItem(QString::number(infoMn.fInfoValid ? infoMn.nProtocolVersion : -1));
    QTableWidgetItem* statusItem = new QTableWidgetItem(QString::fromStdString(infoMn.fInfoValid ? CMasternode::StateToString(infoMn.nActiveState) : "MISSING"));
    QTableWidgetItem* activeSecondsItem = new QTableWidgetItem(QString::fromStdString(DurationToDHMS(infoMn.fInfoValid ? (infoMn.nTimeLastPing - infoMn.sigTime) : 0)));
    QTableWidgetItem* lastSeenItem = new QTableWidgetItem(QString::fromStdString(DateTimeStrFormat("%Y-%m-%d %H:%M",
        infoMn.fInfoValid ? infoMn.nTimeLastPing + QDateTime::currentDateTime().offsetFromUtc() : 0)));
    QTableWidgetItem* pubkeyItem = new QTableWidgetItem(QString::fromStdString(infoMn.fInfoValid ? CBitcoinAddress(infoMn.pubKeyCollateralAddress.GetID()).ToString() : ""));
    QString amntStr = QString::fromStdString(strprintf("%d BTNX",infoMn.nCollateral/COIN));
    QTableWidgetItem* amountItem = new QTableWidgetItem(amntStr);

    ui->tableWidgetMyMasternodes->setItem(nNewRow, 0, aliasItem);
    ui->tableWidgetMyMasternodes->setItem(nNewRow, 1, addrItem);
    ui->tableWidgetMyMasternodes->setItem(nNewRow, 2, protocolItem);
    ui->tableWidgetMyMasternodes->setItem(nNewRow, 3, statusItem);
    ui->tableWidgetMyMasternodes->setItem(nNewRow, 4, activeSecondsItem);
    ui->tableWidgetMyMasternodes->setItem(nNewRow, 5, lastSeenItem);
    ui->tableWidgetMyMasternodes->setItem(nNewRow, 6, pubkeyItem);
    ui->tableWidgetMyMasternodes->setItem(nNewRow, 7, amountItem);
}

void MasternodeList::updateMyNodeList(bool fForce)
{
    TRY_LOCK(cs_mymnlist, fLockAcquired);
    if (!fLockAcquired) {
        return;
    }
    static int64_t nTimeMyListUpdated = 0;

    // automatically update my masternode list only once in MY_MASTERNODELIST_UPDATE_SECONDS seconds,
    // this update still can be triggered manually at any time via button click
    int64_t nSecondsTillUpdate = nTimeMyListUpdated + MY_MASTERNODELIST_UPDATE_SECONDS - GetTime();
    ui->secondsLabel->setText(QString::number(nSecondsTillUpdate));

    if (nSecondsTillUpdate > 0 && !fForce)
        return;
    nTimeMyListUpdated = GetTime();

    ui->tableWidgetMasternodes->setSortingEnabled(false);
    BOOST_FOREACH (CMasternodeConfig::CMasternodeEntry mne, masternodeConfig.getEntries()) {
        int32_t nOutputIndex = 0;
        if (!ParseInt32(mne.getOutputIndex(), &nOutputIndex)) {
            continue;
        }

        CTxIn txin = CTxIn(uint256S(mne.getTxHash()), nOutputIndex);

        masternode_info_t infoMn = mnodeman.GetMasternodeInfo(txin);

        updateMyMasternodeInfo(QString::fromStdString(mne.getAlias()), QString::fromStdString(mne.getIp()), infoMn);
    }
    ui->tableWidgetMasternodes->setSortingEnabled(true);

    // reset "timer"
    ui->secondsLabel->setText("0");
    ui->tableWidgetMasternodes->verticalHeader()->setVisible(true); 
}

void MasternodeList::updateNodeList()
{
    TRY_LOCK(cs_mnlist, fLockAcquired);
    if (!fLockAcquired) {
        return;
    }

    static int64_t nTimeListUpdated = GetTime();

    // to prevent high cpu usage update only once in MASTERNODELIST_UPDATE_SECONDS seconds
    // or MASTERNODELIST_FILTER_COOLDOWN_SECONDS seconds after filter was last changed
    int64_t nSecondsToWait = fFilterUpdated ? nTimeFilterUpdated - GetTime() + MASTERNODELIST_FILTER_COOLDOWN_SECONDS : nTimeListUpdated - GetTime() + MASTERNODELIST_UPDATE_SECONDS;

    if (fFilterUpdated)
        ui->countLabel->setText(QString::fromStdString(strprintf("Please wait... %d", nSecondsToWait)));
    if (nSecondsToWait > 0)
        return;

    nTimeListUpdated = GetTime();
    fFilterUpdated = false;

    QString strToFilter;
    ui->countLabel->setText("Updating...");
    ui->tableWidgetMasternodes->setSortingEnabled(false);
    ui->tableWidgetMasternodes->clearContents();
    ui->tableWidgetMasternodes->setRowCount(0);
    std::vector<CMasternode> vMasternodes = mnodeman.GetFullMasternodeVector();

    BOOST_FOREACH (CMasternode& mn, vMasternodes) {
        // populate list
        // Address, Protocol, Status, Active Seconds, Last Seen, Pub Key
        QTableWidgetItem* addressItem = new QTableWidgetItem(QString::fromStdString(mn.addr.ToString()));
        QTableWidgetItem* protocolItem = new QTableWidgetItem(QString::number(mn.nProtocolVersion));
        QTableWidgetItem* statusItem = new QTableWidgetItem(QString::fromStdString(mn.GetStatus()));
        QTableWidgetItem* activeSecondsItem = new QTableWidgetItem(QString::fromStdString(DurationToDHMS(mn.lastPing.sigTime - mn.sigTime)));
        QTableWidgetItem* lastSeenItem = new QTableWidgetItem(QString::fromStdString(DateTimeStrFormat("%Y-%m-%d %H:%M", mn.lastPing.sigTime + QDateTime::currentDateTime().offsetFromUtc())));
        QTableWidgetItem* pubkeyItem = new QTableWidgetItem(QString::fromStdString(CBitcoinAddress(mn.pubKeyCollateralAddress.GetID()).ToString()));

        QString amntStr = QString::fromStdString(strprintf("%d BTNX",mn.getCollateralValue()/COIN));
        QTableWidgetItem* amountItem = new QTableWidgetItem(amntStr);
        QTableWidgetItem* banItem = new QTableWidgetItem(QString::number(mn.nPoSeBanScore));
       // int vote=0,rank=0;
       // QString dbgStr = QString::fromStdString(strprintf("vote=%d rank=%d",vote,rank);
       // QTableWidgetItem* debugItem = new QTableWidgetItem(dbgStr);
        if (strCurrentFilter != "") {
            strToFilter = addressItem->text() + " " +
                          protocolItem->text() + " " +
                          statusItem->text() + " " +
                          activeSecondsItem->text() + " " +
                          lastSeenItem->text() + " " +
                          pubkeyItem->text();
            if (!strToFilter.contains(strCurrentFilter))
                continue;
        }

        ui->tableWidgetMasternodes->insertRow(0);
        ui->tableWidgetMasternodes->setItem(0, 0, addressItem);
        ui->tableWidgetMasternodes->setItem(0, 1, protocolItem);
        ui->tableWidgetMasternodes->setItem(0, 2, statusItem);
        ui->tableWidgetMasternodes->setItem(0, 3, activeSecondsItem);
        ui->tableWidgetMasternodes->setItem(0, 4, lastSeenItem);
        ui->tableWidgetMasternodes->setItem(0, 5, pubkeyItem);
        ui->tableWidgetMasternodes->setItem(0, 6, amountItem);
        ui->tableWidgetMasternodes->setItem(0, 7, banItem);
   }

    ui->countLabel->setText(QString::number(ui->tableWidgetMasternodes->rowCount()));
    ui->tableWidgetMasternodes->setSortingEnabled(true);
}

void MasternodeList::on_filterLineEdit_textChanged(const QString& strFilterIn)
{
    strCurrentFilter = strFilterIn;
    nTimeFilterUpdated = GetTime();
    fFilterUpdated = true;
    ui->countLabel->setText(QString::fromStdString(strprintf("Please wait... %d", MASTERNODELIST_FILTER_COOLDOWN_SECONDS)));
}

void MasternodeList::on_startButton_clicked()
{
    std::string strAlias;
    {
        LOCK(cs_mymnlist);
        // Find selected node alias
        QItemSelectionModel* selectionModel = ui->tableWidgetMyMasternodes->selectionModel();
        QModelIndexList selected = selectionModel->selectedRows();

        if (selected.count() == 0)
            return;

        QModelIndex index = selected.at(0);
        int nSelectedRow = index.row();
        strAlias = ui->tableWidgetMyMasternodes->item(nSelectedRow, 0)->text().toStdString();
    }

    // Display message box
    QMessageBox::StandardButton retval = QMessageBox::question(this, tr("Confirm masternode start"),
        tr("Are you sure you want to start masternode %1?").arg(QString::fromStdString(strAlias)),
        QMessageBox::Yes | QMessageBox::Cancel,
        QMessageBox::Cancel);

    if (retval != QMessageBox::Yes)
        return;

    WalletModel::EncryptionStatus encStatus = walletModel->getEncryptionStatus();

    if (encStatus == walletModel->Locked || encStatus == walletModel->UnlockedForMixingOnly) {
        WalletModel::UnlockContext ctx(walletModel->requestUnlock());

        if (!ctx.isValid())
            return; // Unlock wallet was cancelled

        StartAlias(strAlias);
        return;
    }

    StartAlias(strAlias);
}

void MasternodeList::on_startAllButton_clicked()
{
    // Display message box
    QMessageBox::StandardButton retval = QMessageBox::question(this, tr("Confirm all masternodes start"),
        tr("Are you sure you want to start ALL masternodes?"),
        QMessageBox::Yes | QMessageBox::Cancel,
        QMessageBox::Cancel);

    if (retval != QMessageBox::Yes)
        return;

    WalletModel::EncryptionStatus encStatus = walletModel->getEncryptionStatus();

    if (encStatus == walletModel->Locked || encStatus == walletModel->UnlockedForMixingOnly) {
        WalletModel::UnlockContext ctx(walletModel->requestUnlock());

        if (!ctx.isValid())
            return; // Unlock wallet was cancelled

        StartAll();
        return;
    }

    StartAll();
}

void MasternodeList::on_startMissingButton_clicked()
{
    if (!masternodeSync.IsMasternodeListSynced()) {
        QMessageBox::critical(this, tr("Command is not available right now"),
            tr("You can't use this command until masternode list is synced"));
        return;
    }

    // Display message box
    QMessageBox::StandardButton retval = QMessageBox::question(this,
        tr("Confirm missing masternodes start"),
        tr("Are you sure you want to start MISSING masternodes?"),
        QMessageBox::Yes | QMessageBox::Cancel,
        QMessageBox::Cancel);

    if (retval != QMessageBox::Yes)
        return;

    WalletModel::EncryptionStatus encStatus = walletModel->getEncryptionStatus();

    if (encStatus == walletModel->Locked || encStatus == walletModel->UnlockedForMixingOnly) {
        WalletModel::UnlockContext ctx(walletModel->requestUnlock());

        if (!ctx.isValid())
            return; // Unlock wallet was cancelled

        StartAll("start-missing");
        return;
    }

    StartAll("start-missing");
}

void MasternodeList::on_tableWidgetMyMasternodes_itemSelectionChanged()
{
    if (ui->tableWidgetMyMasternodes->selectedItems().count() > 0) {
        ui->startButton->setEnabled(true);
    }
}

void MasternodeList::on_UpdateButton_clicked()
{
    updateMyNodeList(true);
}


void MasternodeList::saveFile(int id){
    boost::filesystem::path pathConfig= GetConfigFile();
    QString line = ui->textEditConfig->toPlainText();
    if(id==1){
      pathConfig = GetMasternodeConfigFile();
      line = ui->textEditMaster->toPlainText();
    }

    QString fconfig = QString::fromStdString(pathConfig.string());
    QFile file(fconfig);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream stream(&file);
    stream << line;
    stream.flush();
    file.close();
    if(id==0) ui->textEditConfig->document()->setModified(false);
    if(id==0) ui->textEditMaster->document()->setModified(false);

}
void MasternodeList::on_ButtonSaveAll_clicked()
{
    this->saveFile(0);
    this->saveFile(1);
    QMessageBox msgBox;
    msgBox.setText("bitcoinnode.conf and masternode.conf have been saved.");
    msgBox.exec();
   // ui->pushButtonSaveAll->setEnabled(false);
}

void MasternodeList::on_ButtonSaveConfig_clicked()
{
    this->saveFile(0);
    QMessageBox msgBox;
    msgBox.setText("bitcoinnode.conf have been saved.");
    msgBox.exec();
}
void MasternodeList::on_ButtonSaveMaster_clicked()
{
    this->saveFile(1);
    QMessageBox msgBox;
    msgBox.setText("masternode.conf have been saved.");
    msgBox.exec();
}



void MasternodeList::on_ButtonAddMaster_clicked()
{
    QString config = ui->textEditConfig->toPlainText();
    if(config.isEmpty()){
       std::string stxt = "listen=1\ndaemon=1\nlogtimestamps=1\nmaxconnections=120\nserver=1\nrpcuser=bitnexus\nrpcpassword=btnx\nrpcallowip=127.0.0.1\n";
       stxt += "externalip=\nmasternode=1\n";
       CKey secret;
       secret.MakeNewKey(false);
       stxt += ("masternodeprivkey=" + CBitcoinSecret(secret).ToString()+"\n"); 
       ui->textEditConfig->setPlainText( QString::fromStdString(stxt));
    }
    /*
    boost::filesystem::path pathConfig = GetConfigFile();
    boost::filesystem::path masterConfig = GetMasternodeConfigFile();
    QString config = ui->textEditConfig->toPlainText();
    QMap<QString, QString> map;    
    for(QString s : config.split("\n")){
       QStringList v=s.split("="); 
       if(v.size()==2){
         map[v.at(0)] = v.at(1);
       }
    } 
    map["server"]="1";
    map["daemon"]="1";
    map["listen"]="1";
    map["masternode"]="1";
    if(!map.contains("masternodeprivkey")){
      CKey secret;
      secret.MakeNewKey(false);
      map["masternodeprivkey"]= CBitcoinSecret(secret).ToString();  
    }
    if(!map.contains("externalip")){
      map["externalip"]="";  
    }    
    */
}


void MasternodeList::on_ButtonDocument_clicked()
{
}
void MasternodeList::on_DocumentConfig_changed()
{
    ui->pushButtonSaveAll->setEnabled(true);
    ui->pushButtonSaveConfig->setEnabled(true);
}

void MasternodeList::on_DocumentMaster_changed()
{
    ui->pushButtonSaveAll->setEnabled(true);
    ui->pushButtonSaveMaster->setEnabled(true);
}
void MasternodeList::loadMasterConfigFile()
{
    boost::filesystem::path pathConfig = GetConfigFile();
    boost::filesystem::path masterConfig = GetMasternodeConfigFile();

    /* Open bitcoinnode.conf with the associated application */
    if (boost::filesystem::exists(pathConfig)) {
        QString fconfig = QString::fromStdString(pathConfig.string());
        QFile file(fconfig);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        ui->textEditConfig->clear();
        QTextStream stream(&file);
        ui->textEditConfig->setPlainText(stream.readAll());
        file.close();
    }
    /* Open masternode.conf with the associated application */
    if (boost::filesystem::exists(masterConfig)) {
        QString fconfig = QString::fromStdString(masterConfig.string());
        QFile file(fconfig);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        ui->textEditMaster->clear();
        QTextStream stream(&file);
        ui->textEditMaster->setPlainText(stream.readAll());
        file.close();
    }
  //  ui->pushButtonSaveAll->setEnabled(false);
  //  ui->pushButtonSaveMaster->setEnabled(false);
  //  ui->pushButtonSaveConfig->setEnabled(false);
    ui->textEditConfig->document()->setModified(false); 
    ui->textEditMaster->document()->setModified(false); 

}

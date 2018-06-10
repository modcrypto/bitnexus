#ifndef MASTERNODELIST_H
#define MASTERNODELIST_H

#include "masternode.h"
#include "platformstyle.h"
#include "sync.h"
#include "util.h"

#include <QMenu>
#include <QTimer>
#include <QWidget>

#define MY_MASTERNODELIST_UPDATE_SECONDS                 60
#define MASTERNODELIST_UPDATE_SECONDS                    15
#define MASTERNODELIST_FILTER_COOLDOWN_SECONDS            3

namespace Ui {
    class MasternodeList;
}

class ClientModel;
class WalletModel;

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

/** Masternode Manager page widget */
class MasternodeList : public QWidget
{
    Q_OBJECT

public:
    explicit MasternodeList(const PlatformStyle *platformStyle, QWidget *parent = 0);
    ~MasternodeList();

    void setClientModel(ClientModel *clientModel);
    void setWalletModel(WalletModel *walletModel);
    void StartAlias(std::string strAlias);
    void StartAll(std::string strCommand = "start-all");

private:
    QMenu *contextMenu;
    int64_t nTimeFilterUpdated;
    bool fFilterUpdated;

public Q_SLOTS:
    void updateMyMasternodeInfo(QString strAlias, QString strAddr, masternode_info_t& infoMn);
    void updateMyNodeList(bool fForce = false);
    void updateNodeList();

Q_SIGNALS:

private:
    QTimer *timer;
    Ui::MasternodeList *ui;
    ClientModel *clientModel;
    WalletModel *walletModel;

    // Protects tableWidgetMasternodes
    CCriticalSection cs_mnlist;

    // Protects tableWidgetMyMasternodes
    CCriticalSection cs_mymnlist;

    QString strCurrentFilter;

    void loadMasterConfigFile();
    void saveFile(int id);

private Q_SLOTS:
    void showContextMenu(const QPoint &);
    void on_filterLineEdit_textChanged(const QString &strFilterIn);
    void on_startButton_clicked();
    void on_startAllButton_clicked();
    void on_startMissingButton_clicked();
    void on_tableWidgetMyMasternodes_itemSelectionChanged();
    void on_UpdateButton_clicked();

    void on_ButtonSaveAll_clicked();
    void on_ButtonSaveConfig_clicked();
    void on_ButtonSaveMaster_clicked();
    void on_ButtonAddMaster_clicked();
    void on_ButtonDocument_clicked();
    void on_DocumentConfig_changed();    
    void on_DocumentMaster_changed(); 

};
#endif // MASTERNODELIST_H

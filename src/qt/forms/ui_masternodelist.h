/********************************************************************************
** Form generated from reading UI file 'masternodelist.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MASTERNODELIST_H
#define UI_MASTERNODELIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MasternodeList
{
public:
    QVBoxLayout *topLayout;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tabMyMasternodes;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_note;
    QLabel *updateNote;
    QTableWidget *tableWidgetMyMasternodes;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *startButton;
    QPushButton *startAllButton;
    QPushButton *startMissingButton;
    QPushButton *UpdateButton;
    QLabel *autoupdate_label;
    QLabel *secondsLabel;
    QSpacerItem *horizontalSpacer_5;
    QWidget *tabAllMasternodes;
    QGridLayout *gridLayout;
    QTableWidget *tableWidgetMasternodes;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_filter;
    QLineEdit *filterLineEdit;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_count;
    QLabel *countLabel;
    QPushButton *masternodeOnlineButton;
    QWidget *tabConfigFile;
    QGridLayout *gridLayout_4;
    QTextEdit *textEditMaster;
    QHBoxLayout *HLayout;
    QPushButton *pushButtonLoad;
    QPushButton *pushButtonSaveAll;
    QPushButton *pushButtonSaveConfig;
    QPushButton *pushButtonSaveMaster;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QPushButton *pushButtonAddMaster;
    QPushButton *buttonDocument;
    QTextEdit *textEditConfig;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer0;

    void setupUi(QWidget *MasternodeList)
    {
        if (MasternodeList->objectName().isEmpty())
            MasternodeList->setObjectName(QStringLiteral("MasternodeList"));
        MasternodeList->resize(723, 470);
        topLayout = new QVBoxLayout(MasternodeList);
        topLayout->setObjectName(QStringLiteral("topLayout"));
        topLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 0);
        tabWidget = new QTabWidget(MasternodeList);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setStyleSheet(QStringLiteral(""));
        tabMyMasternodes = new QWidget();
        tabMyMasternodes->setObjectName(QStringLiteral("tabMyMasternodes"));
        gridLayout_2 = new QGridLayout(tabMyMasternodes);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, -1, -1, 0);
        horizontalLayout_note = new QHBoxLayout();
        horizontalLayout_note->setObjectName(QStringLiteral("horizontalLayout_note"));
        horizontalLayout_note->setContentsMargins(-1, -1, -1, 0);
        updateNote = new QLabel(tabMyMasternodes);
        updateNote->setObjectName(QStringLiteral("updateNote"));

        horizontalLayout_note->addWidget(updateNote);


        verticalLayout_2->addLayout(horizontalLayout_note);

        tableWidgetMyMasternodes = new QTableWidget(tabMyMasternodes);
        if (tableWidgetMyMasternodes->columnCount() < 8)
            tableWidgetMyMasternodes->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetMyMasternodes->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetMyMasternodes->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetMyMasternodes->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetMyMasternodes->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetMyMasternodes->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetMyMasternodes->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetMyMasternodes->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetMyMasternodes->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        tableWidgetMyMasternodes->setObjectName(QStringLiteral("tableWidgetMyMasternodes"));
        tableWidgetMyMasternodes->setMinimumSize(QSize(695, 0));
        tableWidgetMyMasternodes->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidgetMyMasternodes->setAlternatingRowColors(true);
        tableWidgetMyMasternodes->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetMyMasternodes->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetMyMasternodes->setSortingEnabled(true);
        tableWidgetMyMasternodes->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_2->addWidget(tableWidgetMyMasternodes);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, -1, -1, 0);
        startButton = new QPushButton(tabMyMasternodes);
        startButton->setObjectName(QStringLiteral("startButton"));

        horizontalLayout_5->addWidget(startButton);

        startAllButton = new QPushButton(tabMyMasternodes);
        startAllButton->setObjectName(QStringLiteral("startAllButton"));

        horizontalLayout_5->addWidget(startAllButton);

        startMissingButton = new QPushButton(tabMyMasternodes);
        startMissingButton->setObjectName(QStringLiteral("startMissingButton"));

        horizontalLayout_5->addWidget(startMissingButton);

        UpdateButton = new QPushButton(tabMyMasternodes);
        UpdateButton->setObjectName(QStringLiteral("UpdateButton"));

        horizontalLayout_5->addWidget(UpdateButton);

        autoupdate_label = new QLabel(tabMyMasternodes);
        autoupdate_label->setObjectName(QStringLiteral("autoupdate_label"));

        horizontalLayout_5->addWidget(autoupdate_label);

        secondsLabel = new QLabel(tabMyMasternodes);
        secondsLabel->setObjectName(QStringLiteral("secondsLabel"));

        horizontalLayout_5->addWidget(secondsLabel);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        verticalLayout_2->addLayout(horizontalLayout_5);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);

        tabWidget->addTab(tabMyMasternodes, QString());
        tabAllMasternodes = new QWidget();
        tabAllMasternodes->setObjectName(QStringLiteral("tabAllMasternodes"));
        gridLayout = new QGridLayout(tabAllMasternodes);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableWidgetMasternodes = new QTableWidget(tabAllMasternodes);
        if (tableWidgetMasternodes->columnCount() < 8)
            tableWidgetMasternodes->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetMasternodes->setHorizontalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetMasternodes->setHorizontalHeaderItem(1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidgetMasternodes->setHorizontalHeaderItem(2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidgetMasternodes->setHorizontalHeaderItem(3, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidgetMasternodes->setHorizontalHeaderItem(4, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidgetMasternodes->setHorizontalHeaderItem(5, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidgetMasternodes->setHorizontalHeaderItem(6, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidgetMasternodes->setHorizontalHeaderItem(7, __qtablewidgetitem15);
        tableWidgetMasternodes->setObjectName(QStringLiteral("tableWidgetMasternodes"));
        tableWidgetMasternodes->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidgetMasternodes->setAlternatingRowColors(true);
        tableWidgetMasternodes->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetMasternodes->setSortingEnabled(true);
        tableWidgetMasternodes->setCornerButtonEnabled(true);
        tableWidgetMasternodes->setRowCount(0);
        tableWidgetMasternodes->horizontalHeader()->setStretchLastSection(true);

        gridLayout->addWidget(tableWidgetMasternodes, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, -1, -1, 0);
        label_filter = new QLabel(tabAllMasternodes);
        label_filter->setObjectName(QStringLiteral("label_filter"));

        horizontalLayout_3->addWidget(label_filter);

        filterLineEdit = new QLineEdit(tabAllMasternodes);
        filterLineEdit->setObjectName(QStringLiteral("filterLineEdit"));

        horizontalLayout_3->addWidget(filterLineEdit);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        label_count = new QLabel(tabAllMasternodes);
        label_count->setObjectName(QStringLiteral("label_count"));

        horizontalLayout_3->addWidget(label_count);

        countLabel = new QLabel(tabAllMasternodes);
        countLabel->setObjectName(QStringLiteral("countLabel"));

        horizontalLayout_3->addWidget(countLabel);

        masternodeOnlineButton = new QPushButton(tabAllMasternodes);
        masternodeOnlineButton->setObjectName(QStringLiteral("masternodeOnlineButton"));

        horizontalLayout_3->addWidget(masternodeOnlineButton);


        gridLayout->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        tabWidget->addTab(tabAllMasternodes, QString());
        tabConfigFile = new QWidget();
        tabConfigFile->setObjectName(QStringLiteral("tabConfigFile"));
        gridLayout_4 = new QGridLayout(tabConfigFile);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        textEditMaster = new QTextEdit(tabConfigFile);
        textEditMaster->setObjectName(QStringLiteral("textEditMaster"));
        textEditMaster->setMinimumSize(QSize(0, 200));
        textEditMaster->setMaximumSize(QSize(16777215, 400));
        QFont font;
        font.setFamily(QStringLiteral("Courier New"));
        textEditMaster->setFont(font);
        textEditMaster->setLineWrapMode(QTextEdit::NoWrap);
        textEditMaster->setAcceptRichText(false);

        gridLayout_4->addWidget(textEditMaster, 1, 0, 1, 1);

        HLayout = new QHBoxLayout();
        HLayout->setObjectName(QStringLiteral("HLayout"));
        HLayout->setContentsMargins(-1, 2, -1, -1);
        pushButtonLoad = new QPushButton(tabConfigFile);
        pushButtonLoad->setObjectName(QStringLiteral("pushButtonLoad"));

        HLayout->addWidget(pushButtonLoad);

        pushButtonSaveAll = new QPushButton(tabConfigFile);
        pushButtonSaveAll->setObjectName(QStringLiteral("pushButtonSaveAll"));

        HLayout->addWidget(pushButtonSaveAll);

        pushButtonSaveConfig = new QPushButton(tabConfigFile);
        pushButtonSaveConfig->setObjectName(QStringLiteral("pushButtonSaveConfig"));

        HLayout->addWidget(pushButtonSaveConfig);

        pushButtonSaveMaster = new QPushButton(tabConfigFile);
        pushButtonSaveMaster->setObjectName(QStringLiteral("pushButtonSaveMaster"));

        HLayout->addWidget(pushButtonSaveMaster);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HLayout->addItem(horizontalSpacer);


        gridLayout_4->addLayout(HLayout, 3, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 5, -1, -1);
        label = new QLabel(tabConfigFile);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(0, 20));

        horizontalLayout_2->addWidget(label);

        pushButtonAddMaster = new QPushButton(tabConfigFile);
        pushButtonAddMaster->setObjectName(QStringLiteral("pushButtonAddMaster"));

        horizontalLayout_2->addWidget(pushButtonAddMaster);

        buttonDocument = new QPushButton(tabConfigFile);
        buttonDocument->setObjectName(QStringLiteral("buttonDocument"));

        horizontalLayout_2->addWidget(buttonDocument);


        verticalLayout_3->addLayout(horizontalLayout_2);

        textEditConfig = new QTextEdit(tabConfigFile);
        textEditConfig->setObjectName(QStringLiteral("textEditConfig"));
        textEditConfig->setMinimumSize(QSize(0, 60));
        textEditConfig->setFont(font);
        textEditConfig->setLineWrapMode(QTextEdit::NoWrap);
        textEditConfig->setAcceptRichText(false);

        verticalLayout_3->addWidget(textEditConfig);

        label_2 = new QLabel(tabConfigFile);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(0, 20));

        verticalLayout_3->addWidget(label_2);


        gridLayout_4->addLayout(verticalLayout_3, 0, 0, 1, 1);

        tabWidget->addTab(tabConfigFile, QString());

        verticalLayout->addWidget(tabWidget);

        horizontalSpacer0 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer0);


        topLayout->addLayout(verticalLayout);


        retranslateUi(MasternodeList);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MasternodeList);
    } // setupUi

    void retranslateUi(QWidget *MasternodeList)
    {
        MasternodeList->setWindowTitle(QApplication::translate("MasternodeList", "Form", 0));
        updateNote->setText(QApplication::translate("MasternodeList", "Note: Status of your masternodes in local wallet can potentially be slightly incorrect.<br />Always wait for wallet to sync additional data and then double check from another node<br />if your masternode should be running but you still do not see \"ENABLED\" in \"Status\" field.", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetMyMasternodes->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MasternodeList", "Alias", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetMyMasternodes->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MasternodeList", "Address", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetMyMasternodes->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MasternodeList", "Protocol", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetMyMasternodes->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MasternodeList", "Status", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetMyMasternodes->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MasternodeList", "Active", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetMyMasternodes->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MasternodeList", "Last Seen", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetMyMasternodes->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("MasternodeList", "Payee", 0));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetMyMasternodes->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("MasternodeList", "Amount", 0));
        startButton->setText(QApplication::translate("MasternodeList", "S&tart alias", 0));
        startAllButton->setText(QApplication::translate("MasternodeList", "Start &all", 0));
        startMissingButton->setText(QApplication::translate("MasternodeList", "Start &MISSING", 0));
        UpdateButton->setText(QApplication::translate("MasternodeList", "&Update status", 0));
        autoupdate_label->setText(QApplication::translate("MasternodeList", "Status will be updated automatically in (sec):", 0));
        secondsLabel->setText(QApplication::translate("MasternodeList", "0", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabMyMasternodes), QApplication::translate("MasternodeList", "My Masternodes", 0));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetMasternodes->horizontalHeaderItem(0);
        ___qtablewidgetitem8->setText(QApplication::translate("MasternodeList", "Address", 0));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetMasternodes->horizontalHeaderItem(1);
        ___qtablewidgetitem9->setText(QApplication::translate("MasternodeList", "Protocol", 0));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidgetMasternodes->horizontalHeaderItem(2);
        ___qtablewidgetitem10->setText(QApplication::translate("MasternodeList", "Status", 0));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidgetMasternodes->horizontalHeaderItem(3);
        ___qtablewidgetitem11->setText(QApplication::translate("MasternodeList", "Active", 0));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidgetMasternodes->horizontalHeaderItem(4);
        ___qtablewidgetitem12->setText(QApplication::translate("MasternodeList", "Last Seen", 0));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidgetMasternodes->horizontalHeaderItem(5);
        ___qtablewidgetitem13->setText(QApplication::translate("MasternodeList", "Payee", 0));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidgetMasternodes->horizontalHeaderItem(6);
        ___qtablewidgetitem14->setText(QApplication::translate("MasternodeList", "Amount", 0));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidgetMasternodes->horizontalHeaderItem(7);
        ___qtablewidgetitem15->setText(QApplication::translate("MasternodeList", "Ban", 0));
        label_filter->setText(QApplication::translate("MasternodeList", "Filter List:", 0));
#ifndef QT_NO_TOOLTIP
        filterLineEdit->setToolTip(QApplication::translate("MasternodeList", "Filter masternode list", 0));
#endif // QT_NO_TOOLTIP
        label_count->setText(QApplication::translate("MasternodeList", "Node Count:", 0));
        countLabel->setText(QApplication::translate("MasternodeList", "0", 0));
#ifndef QT_NO_TOOLTIP
        masternodeOnlineButton->setToolTip(QApplication::translate("MasternodeList", "Browse to http://explorer.btnodes.online/masternode ", 0));
#endif // QT_NO_TOOLTIP
        masternodeOnlineButton->setText(QApplication::translate("MasternodeList", "Masternodes Stats", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabAllMasternodes), QApplication::translate("MasternodeList", "All Masternodes", 0));
        pushButtonLoad->setText(QApplication::translate("MasternodeList", "Load All Files", 0));
        pushButtonSaveAll->setText(QApplication::translate("MasternodeList", "Save All Files", 0));
        pushButtonSaveConfig->setText(QApplication::translate("MasternodeList", "Save bitnexus.conf", 0));
        pushButtonSaveMaster->setText(QApplication::translate("MasternodeList", "Save masternode.conf", 0));
        label->setText(QApplication::translate("MasternodeList", "bitnexus.conf", 0));
        pushButtonAddMaster->setText(QApplication::translate("MasternodeList", "add masternode", 0));
        buttonDocument->setText(QApplication::translate("MasternodeList", "Setup Guide", 0));
        label_2->setText(QApplication::translate("MasternodeList", "masternode.conf", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabConfigFile), QApplication::translate("MasternodeList", "Configuration Files", 0));
    } // retranslateUi

};

namespace Ui {
    class MasternodeList: public Ui_MasternodeList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MASTERNODELIST_H

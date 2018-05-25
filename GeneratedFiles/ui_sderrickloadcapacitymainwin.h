/********************************************************************************
** Form generated from reading UI file 'sderrickloadcapacitymainwin.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SDERRICKLOADCAPACITYMAINWIN_H
#define UI_SDERRICKLOADCAPACITYMAINWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SDerrickLoadCapacityMainWin
{
public:
    QAction *actionOpenOriFile;
    QAction *actionExitAnalysis;
    QAction *actionExit;
    QAction *action_export_word;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *wChannelStartEdit;
    QLineEdit *wChannelEndEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *wMaxLoadCapacityEdit;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *wLoadCapacityIndexStartEdit;
    QLineEdit *wLoadCapacityIndexEndEdit;
    QTableWidget *tableWidgetLoadVal;
    QGroupBox *wMaxLoadStressGroupBox;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tableWidgetMaxLoadStress;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *comboBox_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLineEdit *wlxEdit;
    QLineEdit *wlyEdit;
    QGridLayout *gridLayout;
    QLabel *label_10;
    QLineEdit *wWingbEdit;
    QLabel *label_11;
    QLineEdit *wBodyaEdit;
    QLabel *label_12;
    QLineEdit *wWingt1Edit;
    QLabel *label_13;
    QLineEdit *wBodyt2Edit;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QLineEdit *wrxEdit;
    QLineEdit *wryEdit;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QLineEdit *wrEdit;
    QGridLayout *gridLayout_2;
    QLabel *label_8;
    QLineEdit *wEedit;
    QLabel *label_9;
    QLineEdit *wFyEdit;
    QLabel *label_14;
    QLineEdit *wDerrickWeightEdit;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_5;
    QGridLayout *gridLayout_3;
    QLabel *label_15;
    QLabel *label_19;
    QLineEdit *wCcEdit;
    QLineEdit *wFbEdit;
    QLabel *label_18;
    QLineEdit *wFeyEdit;
    QLabel *label_20;
    QLineEdit *wFexEdit;
    QLabel *label_16;
    QLineEdit *wldividerEdit;
    QLabel *label_17;
    QLineEdit *wFaEdit;
    QTableWidget *tableWidgetMaxLoadCapacity;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer;
    QPushButton *wComputeButton;
    QPushButton *pushButton_printOut;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menuBar;
    QMenu *w;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SDerrickLoadCapacityMainWin)
    {
        if (SDerrickLoadCapacityMainWin->objectName().isEmpty())
            SDerrickLoadCapacityMainWin->setObjectName(QStringLiteral("SDerrickLoadCapacityMainWin"));
        SDerrickLoadCapacityMainWin->resize(907, 674);
        actionOpenOriFile = new QAction(SDerrickLoadCapacityMainWin);
        actionOpenOriFile->setObjectName(QStringLiteral("actionOpenOriFile"));
        actionExitAnalysis = new QAction(SDerrickLoadCapacityMainWin);
        actionExitAnalysis->setObjectName(QStringLiteral("actionExitAnalysis"));
        actionExit = new QAction(SDerrickLoadCapacityMainWin);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        action_export_word = new QAction(SDerrickLoadCapacityMainWin);
        action_export_word->setObjectName(QStringLiteral("action_export_word"));
        centralWidget = new QWidget(SDerrickLoadCapacityMainWin);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_7 = new QVBoxLayout(centralWidget);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMaximumSize(QSize(300, 16777215));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        wChannelStartEdit = new QLineEdit(groupBox);
        wChannelStartEdit->setObjectName(QStringLiteral("wChannelStartEdit"));
        wChannelStartEdit->setEnabled(false);

        horizontalLayout->addWidget(wChannelStartEdit);

        wChannelEndEdit = new QLineEdit(groupBox);
        wChannelEndEdit->setObjectName(QStringLiteral("wChannelEndEdit"));
        wChannelEndEdit->setEnabled(false);

        horizontalLayout->addWidget(wChannelEndEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        wMaxLoadCapacityEdit = new QLineEdit(groupBox);
        wMaxLoadCapacityEdit->setObjectName(QStringLiteral("wMaxLoadCapacityEdit"));

        horizontalLayout_2->addWidget(wMaxLoadCapacityEdit);

        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setEnabled(false);

        horizontalLayout_2->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        wLoadCapacityIndexStartEdit = new QLineEdit(groupBox);
        wLoadCapacityIndexStartEdit->setObjectName(QStringLiteral("wLoadCapacityIndexStartEdit"));
        wLoadCapacityIndexStartEdit->setEnabled(false);

        horizontalLayout_3->addWidget(wLoadCapacityIndexStartEdit);

        wLoadCapacityIndexEndEdit = new QLineEdit(groupBox);
        wLoadCapacityIndexEndEdit->setObjectName(QStringLiteral("wLoadCapacityIndexEndEdit"));
        wLoadCapacityIndexEndEdit->setEnabled(false);

        horizontalLayout_3->addWidget(wLoadCapacityIndexEndEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        tableWidgetLoadVal = new QTableWidget(groupBox);
        if (tableWidgetLoadVal->columnCount() < 2)
            tableWidgetLoadVal->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLoadVal->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLoadVal->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLoadVal->setObjectName(QStringLiteral("tableWidgetLoadVal"));
        tableWidgetLoadVal->setMinimumSize(QSize(0, 210));

        verticalLayout->addWidget(tableWidgetLoadVal);


        verticalLayout_3->addWidget(groupBox);

        wMaxLoadStressGroupBox = new QGroupBox(centralWidget);
        wMaxLoadStressGroupBox->setObjectName(QStringLiteral("wMaxLoadStressGroupBox"));
        wMaxLoadStressGroupBox->setMaximumSize(QSize(300, 16777215));
        verticalLayout_2 = new QVBoxLayout(wMaxLoadStressGroupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        tableWidgetMaxLoadStress = new QTableWidget(wMaxLoadStressGroupBox);
        if (tableWidgetMaxLoadStress->columnCount() < 2)
            tableWidgetMaxLoadStress->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetMaxLoadStress->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetMaxLoadStress->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetMaxLoadStress->setObjectName(QStringLiteral("tableWidgetMaxLoadStress"));

        verticalLayout_2->addWidget(tableWidgetMaxLoadStress);


        verticalLayout_3->addWidget(wMaxLoadStressGroupBox);


        horizontalLayout_8->addLayout(verticalLayout_3);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setSizeConstraint(QLayout::SetFixedSize);
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setMaximumSize(QSize(240, 16777215));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        comboBox_2 = new QComboBox(groupBox_2);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setEnabled(false);

        horizontalLayout_4->addWidget(comboBox_2);


        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        wlxEdit = new QLineEdit(groupBox_2);
        wlxEdit->setObjectName(QStringLiteral("wlxEdit"));

        horizontalLayout_5->addWidget(wlxEdit);

        wlyEdit = new QLineEdit(groupBox_2);
        wlyEdit->setObjectName(QStringLiteral("wlyEdit"));

        horizontalLayout_5->addWidget(wlyEdit);


        verticalLayout_4->addLayout(horizontalLayout_5);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 0, 0, 1, 1);

        wWingbEdit = new QLineEdit(groupBox_2);
        wWingbEdit->setObjectName(QStringLiteral("wWingbEdit"));

        gridLayout->addWidget(wWingbEdit, 0, 1, 1, 1);

        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 1, 0, 1, 1);

        wBodyaEdit = new QLineEdit(groupBox_2);
        wBodyaEdit->setObjectName(QStringLiteral("wBodyaEdit"));

        gridLayout->addWidget(wBodyaEdit, 1, 1, 1, 1);

        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout->addWidget(label_12, 2, 0, 1, 1);

        wWingt1Edit = new QLineEdit(groupBox_2);
        wWingt1Edit->setObjectName(QStringLiteral("wWingt1Edit"));

        gridLayout->addWidget(wWingt1Edit, 2, 1, 1, 1);

        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout->addWidget(label_13, 3, 0, 1, 1);

        wBodyt2Edit = new QLineEdit(groupBox_2);
        wBodyt2Edit->setObjectName(QStringLiteral("wBodyt2Edit"));

        gridLayout->addWidget(wBodyt2Edit, 3, 1, 1, 1);


        verticalLayout_4->addLayout(gridLayout);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setEnabled(false);

        horizontalLayout_6->addWidget(label_6);

        wrxEdit = new QLineEdit(groupBox_2);
        wrxEdit->setObjectName(QStringLiteral("wrxEdit"));
        wrxEdit->setEnabled(false);

        horizontalLayout_6->addWidget(wrxEdit);

        wryEdit = new QLineEdit(groupBox_2);
        wryEdit->setObjectName(QStringLiteral("wryEdit"));
        wryEdit->setEnabled(false);

        horizontalLayout_6->addWidget(wryEdit);


        verticalLayout_4->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setEnabled(false);

        horizontalLayout_7->addWidget(label_7);

        wrEdit = new QLineEdit(groupBox_2);
        wrEdit->setObjectName(QStringLiteral("wrEdit"));
        wrEdit->setEnabled(false);

        horizontalLayout_7->addWidget(wrEdit);


        verticalLayout_4->addLayout(horizontalLayout_7);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_2->addWidget(label_8, 0, 0, 1, 1);

        wEedit = new QLineEdit(groupBox_2);
        wEedit->setObjectName(QStringLiteral("wEedit"));

        gridLayout_2->addWidget(wEedit, 0, 1, 1, 1);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_2->addWidget(label_9, 1, 0, 1, 1);

        wFyEdit = new QLineEdit(groupBox_2);
        wFyEdit->setObjectName(QStringLiteral("wFyEdit"));

        gridLayout_2->addWidget(wFyEdit, 1, 1, 1, 1);

        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_2->addWidget(label_14, 2, 0, 1, 1);

        wDerrickWeightEdit = new QLineEdit(groupBox_2);
        wDerrickWeightEdit->setObjectName(QStringLiteral("wDerrickWeightEdit"));

        gridLayout_2->addWidget(wDerrickWeightEdit, 2, 1, 1, 1);


        verticalLayout_4->addLayout(gridLayout_2);


        verticalLayout_6->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setMaximumSize(QSize(240, 16777215));
        verticalLayout_5 = new QVBoxLayout(groupBox_3);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_15 = new QLabel(groupBox_3);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setMaximumSize(QSize(40, 16777215));

        gridLayout_3->addWidget(label_15, 0, 0, 1, 1);

        label_19 = new QLabel(groupBox_3);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout_3->addWidget(label_19, 5, 0, 1, 1);

        wCcEdit = new QLineEdit(groupBox_3);
        wCcEdit->setObjectName(QStringLiteral("wCcEdit"));
        wCcEdit->setEnabled(false);

        gridLayout_3->addWidget(wCcEdit, 0, 1, 1, 2);

        wFbEdit = new QLineEdit(groupBox_3);
        wFbEdit->setObjectName(QStringLiteral("wFbEdit"));
        wFbEdit->setEnabled(false);

        gridLayout_3->addWidget(wFbEdit, 4, 1, 1, 2);

        label_18 = new QLabel(groupBox_3);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout_3->addWidget(label_18, 4, 0, 1, 1);

        wFeyEdit = new QLineEdit(groupBox_3);
        wFeyEdit->setObjectName(QStringLiteral("wFeyEdit"));
        wFeyEdit->setEnabled(false);

        gridLayout_3->addWidget(wFeyEdit, 7, 1, 1, 2);

        label_20 = new QLabel(groupBox_3);
        label_20->setObjectName(QStringLiteral("label_20"));

        gridLayout_3->addWidget(label_20, 7, 0, 1, 1);

        wFexEdit = new QLineEdit(groupBox_3);
        wFexEdit->setObjectName(QStringLiteral("wFexEdit"));
        wFexEdit->setEnabled(false);

        gridLayout_3->addWidget(wFexEdit, 5, 1, 1, 2);

        label_16 = new QLabel(groupBox_3);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout_3->addWidget(label_16, 2, 0, 1, 1);

        wldividerEdit = new QLineEdit(groupBox_3);
        wldividerEdit->setObjectName(QStringLiteral("wldividerEdit"));
        wldividerEdit->setEnabled(false);

        gridLayout_3->addWidget(wldividerEdit, 2, 1, 1, 2);

        label_17 = new QLabel(groupBox_3);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout_3->addWidget(label_17, 3, 0, 1, 1);

        wFaEdit = new QLineEdit(groupBox_3);
        wFaEdit->setObjectName(QStringLiteral("wFaEdit"));
        wFaEdit->setEnabled(false);

        gridLayout_3->addWidget(wFaEdit, 3, 1, 1, 2);


        verticalLayout_5->addLayout(gridLayout_3);


        verticalLayout_6->addWidget(groupBox_3);


        horizontalLayout_8->addLayout(verticalLayout_6);

        tableWidgetMaxLoadCapacity = new QTableWidget(centralWidget);
        if (tableWidgetMaxLoadCapacity->columnCount() < 3)
            tableWidgetMaxLoadCapacity->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetMaxLoadCapacity->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetMaxLoadCapacity->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetMaxLoadCapacity->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        tableWidgetMaxLoadCapacity->setObjectName(QStringLiteral("tableWidgetMaxLoadCapacity"));
        tableWidgetMaxLoadCapacity->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_8->addWidget(tableWidgetMaxLoadCapacity);


        verticalLayout_7->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer);

        wComputeButton = new QPushButton(centralWidget);
        wComputeButton->setObjectName(QStringLiteral("wComputeButton"));

        horizontalLayout_9->addWidget(wComputeButton);

        pushButton_printOut = new QPushButton(centralWidget);
        pushButton_printOut->setObjectName(QStringLiteral("pushButton_printOut"));

        horizontalLayout_9->addWidget(pushButton_printOut);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_2);


        verticalLayout_7->addLayout(horizontalLayout_9);

        SDerrickLoadCapacityMainWin->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SDerrickLoadCapacityMainWin);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 907, 26));
        w = new QMenu(menuBar);
        w->setObjectName(QStringLiteral("w"));
        SDerrickLoadCapacityMainWin->setMenuBar(menuBar);
        statusBar = new QStatusBar(SDerrickLoadCapacityMainWin);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SDerrickLoadCapacityMainWin->setStatusBar(statusBar);

        menuBar->addAction(w->menuAction());
        w->addAction(actionOpenOriFile);
        w->addAction(actionExit);

        retranslateUi(SDerrickLoadCapacityMainWin);

        QMetaObject::connectSlotsByName(SDerrickLoadCapacityMainWin);
    } // setupUi

    void retranslateUi(QMainWindow *SDerrickLoadCapacityMainWin)
    {
        SDerrickLoadCapacityMainWin->setWindowTitle(QApplication::translate("SDerrickLoadCapacityMainWin", "\346\211\277\350\275\275\350\203\275\345\212\233\345\210\206\346\236\220\347\263\273\347\273\237", Q_NULLPTR));
        actionOpenOriFile->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\346\211\223\345\274\200\345\216\237\345\247\213\346\225\260\346\215\256\346\226\207\344\273\266", Q_NULLPTR));
        actionExitAnalysis->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\345\205\263\351\227\255\345\216\237\345\247\213\346\225\260\346\215\256", Q_NULLPTR));
        actionExit->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\351\200\200\345\207\272\347\250\213\345\272\217", Q_NULLPTR));
        action_export_word->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\345\257\274\345\207\272word\346\212\245\350\241\250", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("SDerrickLoadCapacityMainWin", "\347\272\277\346\200\247\345\244\226\346\216\250\345\217\202\346\225\260", Q_NULLPTR));
        label->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\347\272\277\346\200\247\345\233\236\345\275\222\347\202\271\345\217\267\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\347\272\277\346\200\247\345\244\226\346\216\250\350\275\275\350\215\267\357\274\232", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("SDerrickLoadCapacityMainWin", "\350\275\275\350\215\267\357\274\210kN\357\274\211", Q_NULLPTR)
         << QApplication::translate("SDerrickLoadCapacityMainWin", "\345\216\213\345\212\233\357\274\210MPa\357\274\211", Q_NULLPTR)
        );
        label_3->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\350\275\275\350\215\267\346\225\260\346\215\256\347\232\204\346\254\241\345\210\253\357\274\232", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLoadVal->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\350\275\275\350\215\267\346\254\241\345\210\253", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLoadVal->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\350\276\223\345\205\245\350\275\275\350\215\267\345\200\274", Q_NULLPTR));
        wMaxLoadStressGroupBox->setTitle(QApplication::translate("SDerrickLoadCapacityMainWin", "\350\277\207\347\250\213\346\225\260\346\215\256", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetMaxLoadStress->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\346\265\213\347\202\271\345\217\267", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetMaxLoadStress->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\346\234\200\345\244\247\351\222\251\350\275\275\346\227\266\345\272\224\345\212\233", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("SDerrickLoadCapacityMainWin", "\346\211\277\350\275\275\350\203\275\345\212\233\345\217\202\346\225\260", Q_NULLPTR));
        label_4->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\347\225\214\351\235\242\347\261\273\345\236\213", Q_NULLPTR));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("SDerrickLoadCapacityMainWin", "H\345\236\213", Q_NULLPTR)
        );
        label_5->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\346\227\240\346\224\257\346\222\221\351\225\277\345\272\246(lx,ly)", Q_NULLPTR));
        wlxEdit->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "2450", Q_NULLPTR));
        wlyEdit->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "2450", Q_NULLPTR));
        label_10->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\347\277\274\346\235\277\351\225\277b", Q_NULLPTR));
        wWingbEdit->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "260", Q_NULLPTR));
        label_11->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\350\205\271\346\235\277\351\225\277a", Q_NULLPTR));
        wBodyaEdit->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "300", Q_NULLPTR));
        label_12->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\347\277\274\346\235\277\345\216\232\345\272\246t1", Q_NULLPTR));
        wWingt1Edit->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "13.25", Q_NULLPTR));
        label_13->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\350\205\271\346\235\277\345\216\232\345\272\246t2", Q_NULLPTR));
        wBodyt2Edit->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "9.20", Q_NULLPTR));
        label_6->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\345\233\236\350\275\254\345\215\212\345\276\204(rx,ry)", Q_NULLPTR));
        label_7->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\345\233\236\350\275\254\345\215\212\345\276\204(r)", Q_NULLPTR));
        label_8->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\345\274\271\346\200\247\346\250\241\351\207\217(E)", Q_NULLPTR));
        label_9->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\345\261\210\346\234\215\346\236\201\351\231\220(Fy)", Q_NULLPTR));
        label_14->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\344\272\225\346\236\266\350\207\252\351\207\215", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("SDerrickLoadCapacityMainWin", "\350\277\207\347\250\213\346\225\260\346\215\256", Q_NULLPTR));
        label_15->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "Cc =", Q_NULLPTR));
        label_19->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "Fex =", Q_NULLPTR));
        label_18->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "Fb =", Q_NULLPTR));
        label_20->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "Fey =", Q_NULLPTR));
        label_16->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "l/r =", Q_NULLPTR));
        label_17->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "Fa =", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetMaxLoadCapacity->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\345\210\206\347\273\204\347\274\226\345\217\267", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetMaxLoadCapacity->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\345\274\272\345\272\246\346\240\241\346\240\270", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetMaxLoadCapacity->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\346\234\200\345\244\247\346\211\277\350\275\275", Q_NULLPTR));
        wComputeButton->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\350\256\241\347\256\227", Q_NULLPTR));
        pushButton_printOut->setText(QApplication::translate("SDerrickLoadCapacityMainWin", "\346\212\245\345\221\212\347\224\237\346\210\220", Q_NULLPTR));
        w->setTitle(QApplication::translate("SDerrickLoadCapacityMainWin", "\346\226\207\344\273\266", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SDerrickLoadCapacityMainWin: public Ui_SDerrickLoadCapacityMainWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SDERRICKLOADCAPACITYMAINWIN_H

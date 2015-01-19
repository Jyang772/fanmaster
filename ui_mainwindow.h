/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *Auto;
    QWidget *tab;
    QSpinBox *sleepBox;
    QSpinBox *critBox;
    QSpinBox *safeBox;
    QPushButton *pushButton;
    QTextBrowser *infoBox;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLabel *currentOptions;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QWidget *tab_2;
    QLabel *label_5;
    QLCDNumber *lcdNumber;
    QLabel *label_6;
    QPushButton *pushButton_2;
    QComboBox *comboBox;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(549, 456);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        Auto = new QTabWidget(centralWidget);
        Auto->setObjectName(QStringLiteral("Auto"));
        Auto->setFocusPolicy(Qt::TabFocus);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        sleepBox = new QSpinBox(tab);
        sleepBox->setObjectName(QStringLiteral("sleepBox"));
        sleepBox->setGeometry(QRect(320, 70, 91, 27));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sleepBox->sizePolicy().hasHeightForWidth());
        sleepBox->setSizePolicy(sizePolicy);
        critBox = new QSpinBox(tab);
        critBox->setObjectName(QStringLiteral("critBox"));
        critBox->setGeometry(QRect(320, 100, 91, 27));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(critBox->sizePolicy().hasHeightForWidth());
        critBox->setSizePolicy(sizePolicy1);
        critBox->setMaximum(106);
        critBox->setValue(0);
        safeBox = new QSpinBox(tab);
        safeBox->setObjectName(QStringLiteral("safeBox"));
        safeBox->setGeometry(QRect(320, 130, 91, 27));
        sizePolicy.setHeightForWidth(safeBox->sizePolicy().hasHeightForWidth());
        safeBox->setSizePolicy(sizePolicy);
        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(150, 180, 171, 27));
        infoBox = new QTextBrowser(tab);
        infoBox->setObjectName(QStringLiteral("infoBox"));
        infoBox->setGeometry(QRect(40, 210, 401, 91));
        widget = new QWidget(tab);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(50, 30, 261, 131));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        currentOptions = new QLabel(widget);
        currentOptions->setObjectName(QStringLiteral("currentOptions"));

        gridLayout_2->addWidget(currentOptions, 0, 1, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 2);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 2);

        Auto->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(60, 60, 171, 17));
        lcdNumber = new QLCDNumber(tab_2);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(230, 60, 64, 23));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(60, 100, 181, 20));
        pushButton_2 = new QPushButton(tab_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(310, 100, 191, 27));
        comboBox = new QComboBox(tab_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(210, 100, 85, 27));
        Auto->addTab(tab_2, QString());

        gridLayout->addWidget(Auto, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 549, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        Auto->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Apply Current Options", 0));
        label->setText(QApplication::translate("MainWindow", "Current options: ", 0));
        currentOptions->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_2->setText(QApplication::translate("MainWindow", "Sleep Time: ", 0));
        label_3->setText(QApplication::translate("MainWindow", "Critical Temperature:", 0));
        label_4->setText(QApplication::translate("MainWindow", "Safe Temperature: ", 0));
        Auto->setTabText(Auto->indexOf(tab), QApplication::translate("MainWindow", "Automatic Control", 0));
        label_5->setText(QApplication::translate("MainWindow", "Current Temperature: ", 0));
        label_6->setText(QApplication::translate("MainWindow", "Choose Speed: ", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Change Speed", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "auto", 0)
         << QApplication::translate("MainWindow", "1", 0)
         << QApplication::translate("MainWindow", "2", 0)
         << QApplication::translate("MainWindow", "3", 0)
         << QApplication::translate("MainWindow", "4", 0)
         << QApplication::translate("MainWindow", "5", 0)
         << QApplication::translate("MainWindow", "6", 0)
         << QApplication::translate("MainWindow", "7", 0)
         << QApplication::translate("MainWindow", "full speed", 0)
        );
        Auto->setTabText(Auto->indexOf(tab_2), QApplication::translate("MainWindow", "Manual Control", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

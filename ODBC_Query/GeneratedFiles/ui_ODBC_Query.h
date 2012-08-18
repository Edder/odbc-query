/********************************************************************************
** Form generated from reading UI file 'ODBC_Query.ui'
**
** Created: Sat 18. Aug 11:18:22 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ODBC_QUERY_H
#define UI_ODBC_QUERY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>
#include "ODBC_TableView.h"

QT_BEGIN_NAMESPACE

class Ui_ODBC_QueryClass
{
public:
    QAction *ActionExit;
    QAction *NewConnectionAction;
    QAction *CloseAllConnectionsAction;
    QAction *actionTest;
    QWidget *CentralWidget;
    QHBoxLayout *horizontalLayout;
    QToolButton *AddConnectionToolButton;
    QToolButton *OpenConnectionsToolButton;
    QToolButton *CloseAllConnectionsToolButton;
    QLabel *StatusLabel;
    QSplitter *MainHorizontalSplitter;
    QSplitter *HorizontalSplitter;
    QTreeWidget *TableTreeWidget;
    QTreeWidget *FieldTreeWidget;
    QSplitter *VerticalSplitter;
    ODBC_TableView *SQLResultTableView;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *HorizontalLayout_3;
    QToolButton *ExecuteToolButton;
    QFrame *Line;
    QToolButton *LeftToolButton;
    QLabel *CurrentStatementLabel;
    QToolButton *RightToolButton;
    QFrame *Line_2;
    QSpacerItem *HorizontalSpacer;
    QWidget *layoutWidget;
    QHBoxLayout *HorizontalLayout;
    QTextEdit *SQLCommandTextEdit;
    QTextBrowser *SQLLogTextBrowser;
    QMenuBar *MenuBar;
    QMenu *MenuFile;
    QMenu *MenuConnections;
    QMenu *OpenConnectionsMenu;
    QStatusBar *StatusBar;
    QToolBar *ToolBar;

    void setupUi(QMainWindow *ODBC_QueryClass)
    {
        if (ODBC_QueryClass->objectName().isEmpty())
            ODBC_QueryClass->setObjectName(QString::fromUtf8("ODBC_QueryClass"));
        ODBC_QueryClass->resize(1074, 672);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ODBC_Query/Resources/database_icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        ODBC_QueryClass->setWindowIcon(icon);
        ActionExit = new QAction(ODBC_QueryClass);
        ActionExit->setObjectName(QString::fromUtf8("ActionExit"));
        NewConnectionAction = new QAction(ODBC_QueryClass);
        NewConnectionAction->setObjectName(QString::fromUtf8("NewConnectionAction"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ODBC_Query/Resources/database_add.png"), QSize(), QIcon::Normal, QIcon::Off);
        NewConnectionAction->setIcon(icon1);
        CloseAllConnectionsAction = new QAction(ODBC_QueryClass);
        CloseAllConnectionsAction->setObjectName(QString::fromUtf8("CloseAllConnectionsAction"));
        CloseAllConnectionsAction->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ODBC_Query/Resources/database_remove.png"), QSize(), QIcon::Normal, QIcon::Off);
        CloseAllConnectionsAction->setIcon(icon2);
        actionTest = new QAction(ODBC_QueryClass);
        actionTest->setObjectName(QString::fromUtf8("actionTest"));
        CentralWidget = new QWidget(ODBC_QueryClass);
        CentralWidget->setObjectName(QString::fromUtf8("CentralWidget"));
        horizontalLayout = new QHBoxLayout(CentralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        AddConnectionToolButton = new QToolButton(CentralWidget);
        AddConnectionToolButton->setObjectName(QString::fromUtf8("AddConnectionToolButton"));
        AddConnectionToolButton->setIcon(icon1);
        AddConnectionToolButton->setIconSize(QSize(32, 32));
        AddConnectionToolButton->setAutoRaise(true);

        horizontalLayout->addWidget(AddConnectionToolButton);

        OpenConnectionsToolButton = new QToolButton(CentralWidget);
        OpenConnectionsToolButton->setObjectName(QString::fromUtf8("OpenConnectionsToolButton"));
        OpenConnectionsToolButton->setEnabled(false);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ODBC_Query/Resources/database.png"), QSize(), QIcon::Normal, QIcon::Off);
        OpenConnectionsToolButton->setIcon(icon3);
        OpenConnectionsToolButton->setIconSize(QSize(32, 32));
        OpenConnectionsToolButton->setPopupMode(QToolButton::InstantPopup);
        OpenConnectionsToolButton->setAutoRaise(true);

        horizontalLayout->addWidget(OpenConnectionsToolButton);

        CloseAllConnectionsToolButton = new QToolButton(CentralWidget);
        CloseAllConnectionsToolButton->setObjectName(QString::fromUtf8("CloseAllConnectionsToolButton"));
        CloseAllConnectionsToolButton->setEnabled(false);
        CloseAllConnectionsToolButton->setIcon(icon2);
        CloseAllConnectionsToolButton->setIconSize(QSize(32, 32));
        CloseAllConnectionsToolButton->setAutoRaise(true);

        horizontalLayout->addWidget(CloseAllConnectionsToolButton);

        StatusLabel = new QLabel(CentralWidget);
        StatusLabel->setObjectName(QString::fromUtf8("StatusLabel"));

        horizontalLayout->addWidget(StatusLabel);

        MainHorizontalSplitter = new QSplitter(CentralWidget);
        MainHorizontalSplitter->setObjectName(QString::fromUtf8("MainHorizontalSplitter"));
        MainHorizontalSplitter->setOrientation(Qt::Horizontal);
        HorizontalSplitter = new QSplitter(MainHorizontalSplitter);
        HorizontalSplitter->setObjectName(QString::fromUtf8("HorizontalSplitter"));
        HorizontalSplitter->setOrientation(Qt::Horizontal);
        TableTreeWidget = new QTreeWidget(HorizontalSplitter);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        TableTreeWidget->setHeaderItem(__qtreewidgetitem);
        TableTreeWidget->setObjectName(QString::fromUtf8("TableTreeWidget"));
        TableTreeWidget->setAlternatingRowColors(true);
        TableTreeWidget->setIndentation(0);
        TableTreeWidget->setItemsExpandable(false);
        TableTreeWidget->setExpandsOnDoubleClick(false);
        HorizontalSplitter->addWidget(TableTreeWidget);
        FieldTreeWidget = new QTreeWidget(HorizontalSplitter);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(3, QString::fromUtf8("4"));
        __qtreewidgetitem1->setText(2, QString::fromUtf8("3"));
        __qtreewidgetitem1->setText(1, QString::fromUtf8("2"));
        __qtreewidgetitem1->setText(0, QString::fromUtf8("1"));
        FieldTreeWidget->setHeaderItem(__qtreewidgetitem1);
        FieldTreeWidget->setObjectName(QString::fromUtf8("FieldTreeWidget"));
        FieldTreeWidget->setAlternatingRowColors(true);
        FieldTreeWidget->setIndentation(0);
        FieldTreeWidget->setItemsExpandable(false);
        FieldTreeWidget->setExpandsOnDoubleClick(false);
        FieldTreeWidget->setColumnCount(4);
        HorizontalSplitter->addWidget(FieldTreeWidget);
        FieldTreeWidget->header()->setDefaultSectionSize(75);
        MainHorizontalSplitter->addWidget(HorizontalSplitter);
        VerticalSplitter = new QSplitter(MainHorizontalSplitter);
        VerticalSplitter->setObjectName(QString::fromUtf8("VerticalSplitter"));
        VerticalSplitter->setOrientation(Qt::Vertical);
        SQLResultTableView = new ODBC_TableView(VerticalSplitter);
        SQLResultTableView->setObjectName(QString::fromUtf8("SQLResultTableView"));
        QFont font;
        font.setPointSize(8);
        font.setKerning(true);
        SQLResultTableView->setFont(font);
        SQLResultTableView->setFrameShape(QFrame::StyledPanel);
        SQLResultTableView->setFrameShadow(QFrame::Sunken);
        SQLResultTableView->setMidLineWidth(1);
        SQLResultTableView->setAlternatingRowColors(true);
        SQLResultTableView->setSortingEnabled(true);
        VerticalSplitter->addWidget(SQLResultTableView);
        SQLResultTableView->verticalHeader()->setDefaultSectionSize(20);
        horizontalLayoutWidget = new QWidget(VerticalSplitter);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        HorizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget);
        HorizontalLayout_3->setSpacing(6);
        HorizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        HorizontalLayout_3->setObjectName(QString::fromUtf8("HorizontalLayout_3"));
        HorizontalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        HorizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        ExecuteToolButton = new QToolButton(horizontalLayoutWidget);
        ExecuteToolButton->setObjectName(QString::fromUtf8("ExecuteToolButton"));
        ExecuteToolButton->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ExecuteToolButton->sizePolicy().hasHeightForWidth());
        ExecuteToolButton->setSizePolicy(sizePolicy);
        ExecuteToolButton->setLayoutDirection(Qt::LeftToRight);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/ODBC_Query/Resources/play_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        ExecuteToolButton->setIcon(icon4);
        ExecuteToolButton->setIconSize(QSize(20, 20));
        ExecuteToolButton->setCheckable(false);
        ExecuteToolButton->setAutoRaise(true);

        HorizontalLayout_3->addWidget(ExecuteToolButton);

        Line = new QFrame(horizontalLayoutWidget);
        Line->setObjectName(QString::fromUtf8("Line"));
        Line->setWindowModality(Qt::NonModal);
        Line->setEnabled(true);
        Line->setFrameShape(QFrame::VLine);
        Line->setFrameShadow(QFrame::Sunken);

        HorizontalLayout_3->addWidget(Line);

        LeftToolButton = new QToolButton(horizontalLayoutWidget);
        LeftToolButton->setObjectName(QString::fromUtf8("LeftToolButton"));
        LeftToolButton->setEnabled(false);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/ODBC_Query/Resources/left_arrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        LeftToolButton->setIcon(icon5);
        LeftToolButton->setIconSize(QSize(20, 20));
        LeftToolButton->setAutoRaise(true);

        HorizontalLayout_3->addWidget(LeftToolButton);

        CurrentStatementLabel = new QLabel(horizontalLayoutWidget);
        CurrentStatementLabel->setObjectName(QString::fromUtf8("CurrentStatementLabel"));
        CurrentStatementLabel->setEnabled(false);

        HorizontalLayout_3->addWidget(CurrentStatementLabel);

        RightToolButton = new QToolButton(horizontalLayoutWidget);
        RightToolButton->setObjectName(QString::fromUtf8("RightToolButton"));
        RightToolButton->setEnabled(false);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/ODBC_Query/Resources/right_arrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        RightToolButton->setIcon(icon6);
        RightToolButton->setIconSize(QSize(20, 20));
        RightToolButton->setAutoRaise(true);

        HorizontalLayout_3->addWidget(RightToolButton);

        Line_2 = new QFrame(horizontalLayoutWidget);
        Line_2->setObjectName(QString::fromUtf8("Line_2"));
        Line_2->setFrameShape(QFrame::VLine);
        Line_2->setFrameShadow(QFrame::Sunken);

        HorizontalLayout_3->addWidget(Line_2);

        HorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayout_3->addItem(HorizontalSpacer);

        VerticalSplitter->addWidget(horizontalLayoutWidget);
        layoutWidget = new QWidget(VerticalSplitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        HorizontalLayout = new QHBoxLayout(layoutWidget);
        HorizontalLayout->setSpacing(6);
        HorizontalLayout->setContentsMargins(11, 11, 11, 11);
        HorizontalLayout->setObjectName(QString::fromUtf8("HorizontalLayout"));
        HorizontalLayout->setContentsMargins(0, 0, 0, 0);
        SQLCommandTextEdit = new QTextEdit(layoutWidget);
        SQLCommandTextEdit->setObjectName(QString::fromUtf8("SQLCommandTextEdit"));

        HorizontalLayout->addWidget(SQLCommandTextEdit);

        VerticalSplitter->addWidget(layoutWidget);
        SQLLogTextBrowser = new QTextBrowser(VerticalSplitter);
        SQLLogTextBrowser->setObjectName(QString::fromUtf8("SQLLogTextBrowser"));
        SQLLogTextBrowser->setReadOnly(true);
        VerticalSplitter->addWidget(SQLLogTextBrowser);
        MainHorizontalSplitter->addWidget(VerticalSplitter);

        horizontalLayout->addWidget(MainHorizontalSplitter);

        ODBC_QueryClass->setCentralWidget(CentralWidget);
        MenuBar = new QMenuBar(ODBC_QueryClass);
        MenuBar->setObjectName(QString::fromUtf8("MenuBar"));
        MenuBar->setGeometry(QRect(0, 0, 1074, 21));
        MenuFile = new QMenu(MenuBar);
        MenuFile->setObjectName(QString::fromUtf8("MenuFile"));
        MenuConnections = new QMenu(MenuBar);
        MenuConnections->setObjectName(QString::fromUtf8("MenuConnections"));
        OpenConnectionsMenu = new QMenu(MenuConnections);
        OpenConnectionsMenu->setObjectName(QString::fromUtf8("OpenConnectionsMenu"));
        OpenConnectionsMenu->setEnabled(false);
        OpenConnectionsMenu->setIcon(icon3);
        ODBC_QueryClass->setMenuBar(MenuBar);
        StatusBar = new QStatusBar(ODBC_QueryClass);
        StatusBar->setObjectName(QString::fromUtf8("StatusBar"));
        ODBC_QueryClass->setStatusBar(StatusBar);
        ToolBar = new QToolBar(ODBC_QueryClass);
        ToolBar->setObjectName(QString::fromUtf8("ToolBar"));
        ODBC_QueryClass->addToolBar(Qt::TopToolBarArea, ToolBar);

        MenuBar->addAction(MenuFile->menuAction());
        MenuBar->addAction(MenuConnections->menuAction());
        MenuFile->addAction(ActionExit);
        MenuConnections->addAction(NewConnectionAction);
        MenuConnections->addAction(OpenConnectionsMenu->menuAction());
        MenuConnections->addAction(CloseAllConnectionsAction);

        retranslateUi(ODBC_QueryClass);

        QMetaObject::connectSlotsByName(ODBC_QueryClass);
    } // setupUi

    void retranslateUi(QMainWindow *ODBC_QueryClass)
    {
        ODBC_QueryClass->setWindowTitle(QApplication::translate("ODBC_QueryClass", "ODBC_Query", 0, QApplication::UnicodeUTF8));
        ActionExit->setText(QApplication::translate("ODBC_QueryClass", "Exit", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ActionExit->setToolTip(QApplication::translate("ODBC_QueryClass", "Close program", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        ActionExit->setStatusTip(QApplication::translate("ODBC_QueryClass", "Close program", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        NewConnectionAction->setText(QApplication::translate("ODBC_QueryClass", "New connection", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        NewConnectionAction->setStatusTip(QApplication::translate("ODBC_QueryClass", "New connection", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        CloseAllConnectionsAction->setText(QApplication::translate("ODBC_QueryClass", "Close all connections", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        CloseAllConnectionsAction->setStatusTip(QApplication::translate("ODBC_QueryClass", "Close all connections", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionTest->setText(QApplication::translate("ODBC_QueryClass", "test", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        AddConnectionToolButton->setToolTip(QApplication::translate("ODBC_QueryClass", "New connection", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        AddConnectionToolButton->setStatusTip(QApplication::translate("ODBC_QueryClass", "New connection", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        AddConnectionToolButton->setText(QString());
        OpenConnectionsToolButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        CloseAllConnectionsToolButton->setToolTip(QApplication::translate("ODBC_QueryClass", "Close all connections", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        CloseAllConnectionsToolButton->setStatusTip(QApplication::translate("ODBC_QueryClass", "Close all connections", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        CloseAllConnectionsToolButton->setText(QString());
        StatusLabel->setText(QString());
#ifndef QT_NO_TOOLTIP
        ExecuteToolButton->setToolTip(QApplication::translate("ODBC_QueryClass", "<F5> Executes the entered SQL statement", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ExecuteToolButton->setText(QString());
        LeftToolButton->setText(QApplication::translate("ODBC_QueryClass", "left", 0, QApplication::UnicodeUTF8));
        CurrentStatementLabel->setText(QApplication::translate("ODBC_QueryClass", "1", 0, QApplication::UnicodeUTF8));
        RightToolButton->setText(QApplication::translate("ODBC_QueryClass", "right", 0, QApplication::UnicodeUTF8));
        MenuFile->setTitle(QApplication::translate("ODBC_QueryClass", "File", 0, QApplication::UnicodeUTF8));
        MenuConnections->setTitle(QApplication::translate("ODBC_QueryClass", "Connections", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        OpenConnectionsMenu->setToolTip(QApplication::translate("ODBC_QueryClass", "Open existing connections", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        OpenConnectionsMenu->setStatusTip(QApplication::translate("ODBC_QueryClass", "Open existing connections", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        OpenConnectionsMenu->setTitle(QApplication::translate("ODBC_QueryClass", "Open connections...", 0, QApplication::UnicodeUTF8));
        ToolBar->setWindowTitle(QApplication::translate("ODBC_QueryClass", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ODBC_QueryClass: public Ui_ODBC_QueryClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ODBC_QUERY_H

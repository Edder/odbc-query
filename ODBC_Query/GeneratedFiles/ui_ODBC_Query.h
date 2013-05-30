/********************************************************************************
** Form generated from reading UI file 'ODBC_Query.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ODBC_QUERY_H
#define UI_ODBC_QUERY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>
#include "ODBC_TableView.h"

QT_BEGIN_NAMESPACE

class Ui_ODBC_QueryClass
{
public:
    QAction *ExitAction;
    QAction *NewConnectionAction;
    QAction *CloseAllConnectionsAction;
    QAction *actionTest;
    QAction *ShowToolbarAction;
    QAction *SyntaxHighlightingAction;
    QAction *OptionsAction;
    QAction *AboutAction;
    QAction *RefreshTablesAction;
    QWidget *CentralWidget;
    QHBoxLayout *horizontalLayout;
    QToolButton *AddConnectionToolButton;
    QToolButton *OpenConnectionsToolButton;
    QToolButton *CloseAllConnectionsToolButton;
    QToolButton *RefreshTablesToolButton;
    QLabel *StatusLabel;
    QSplitter *MainHorizontalSplitter;
    QSplitter *HorizontalSplitter;
    QTreeWidget *TableTreeWidget;
    QSplitter *VerticalSplitter;
    QLabel *ResultCountLabel;
    ODBC_TableView *SQLResultTableView;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *HorizontalLayout_3;
    QToolButton *ExecuteToolButton;
    QFrame *Line;
    QToolButton *LeftToolButton;
    QLabel *CurrentStatementLabel;
    QToolButton *RightToolButton;
    QFrame *Line_2;
    QToolButton *ExtractToolButton;
    QSpacerItem *HorizontalSpacer;
    QTextEdit *SQLCommandTextEdit;
    QTextBrowser *SQLLogTextBrowser;
    QMenuBar *MenuBar;
    QMenu *FileMenu;
    QMenu *ConnectionsMenu;
    QMenu *OpenConnectionsMenu;
    QMenu *ViewMenu;
    QMenu *ToolsMenu;
    QMenu *HelpMenu;
    QStatusBar *StatusBar;
    QToolBar *ToolBar;

    void setupUi(QMainWindow *ODBC_QueryClass)
    {
        if (ODBC_QueryClass->objectName().isEmpty())
            ODBC_QueryClass->setObjectName(QStringLiteral("ODBC_QueryClass"));
        ODBC_QueryClass->resize(1074, 672);
        QIcon icon;
        icon.addFile(QStringLiteral(":/ODBC_Query/Resources/database_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        ODBC_QueryClass->setWindowIcon(icon);
        ExitAction = new QAction(ODBC_QueryClass);
        ExitAction->setObjectName(QStringLiteral("ExitAction"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/ODBC_Query/Resources/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        ExitAction->setIcon(icon1);
        NewConnectionAction = new QAction(ODBC_QueryClass);
        NewConnectionAction->setObjectName(QStringLiteral("NewConnectionAction"));
        NewConnectionAction->setEnabled(true);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/ODBC_Query/Resources/database_add.png"), QSize(), QIcon::Normal, QIcon::Off);
        NewConnectionAction->setIcon(icon2);
        CloseAllConnectionsAction = new QAction(ODBC_QueryClass);
        CloseAllConnectionsAction->setObjectName(QStringLiteral("CloseAllConnectionsAction"));
        CloseAllConnectionsAction->setEnabled(false);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/ODBC_Query/Resources/database_remove.png"), QSize(), QIcon::Normal, QIcon::Off);
        CloseAllConnectionsAction->setIcon(icon3);
        actionTest = new QAction(ODBC_QueryClass);
        actionTest->setObjectName(QStringLiteral("actionTest"));
        ShowToolbarAction = new QAction(ODBC_QueryClass);
        ShowToolbarAction->setObjectName(QStringLiteral("ShowToolbarAction"));
        ShowToolbarAction->setCheckable(true);
        ShowToolbarAction->setChecked(true);
        SyntaxHighlightingAction = new QAction(ODBC_QueryClass);
        SyntaxHighlightingAction->setObjectName(QStringLiteral("SyntaxHighlightingAction"));
        SyntaxHighlightingAction->setCheckable(true);
        SyntaxHighlightingAction->setChecked(true);
        OptionsAction = new QAction(ODBC_QueryClass);
        OptionsAction->setObjectName(QStringLiteral("OptionsAction"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/ODBC_Query/Resources/options.png"), QSize(), QIcon::Normal, QIcon::Off);
        OptionsAction->setIcon(icon4);
        AboutAction = new QAction(ODBC_QueryClass);
        AboutAction->setObjectName(QStringLiteral("AboutAction"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/ODBC_Query/Resources/info.png"), QSize(), QIcon::Normal, QIcon::Off);
        AboutAction->setIcon(icon5);
        RefreshTablesAction = new QAction(ODBC_QueryClass);
        RefreshTablesAction->setObjectName(QStringLiteral("RefreshTablesAction"));
        RefreshTablesAction->setEnabled(false);
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/ODBC_Query/Resources/table_refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        RefreshTablesAction->setIcon(icon6);
        CentralWidget = new QWidget(ODBC_QueryClass);
        CentralWidget->setObjectName(QStringLiteral("CentralWidget"));
        horizontalLayout = new QHBoxLayout(CentralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        AddConnectionToolButton = new QToolButton(CentralWidget);
        AddConnectionToolButton->setObjectName(QStringLiteral("AddConnectionToolButton"));
        AddConnectionToolButton->setIcon(icon2);
        AddConnectionToolButton->setIconSize(QSize(32, 32));
        AddConnectionToolButton->setAutoRaise(true);

        horizontalLayout->addWidget(AddConnectionToolButton);

        OpenConnectionsToolButton = new QToolButton(CentralWidget);
        OpenConnectionsToolButton->setObjectName(QStringLiteral("OpenConnectionsToolButton"));
        OpenConnectionsToolButton->setEnabled(false);
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/ODBC_Query/Resources/database.png"), QSize(), QIcon::Normal, QIcon::Off);
        OpenConnectionsToolButton->setIcon(icon7);
        OpenConnectionsToolButton->setIconSize(QSize(32, 32));
        OpenConnectionsToolButton->setPopupMode(QToolButton::InstantPopup);
        OpenConnectionsToolButton->setAutoRaise(true);

        horizontalLayout->addWidget(OpenConnectionsToolButton);

        CloseAllConnectionsToolButton = new QToolButton(CentralWidget);
        CloseAllConnectionsToolButton->setObjectName(QStringLiteral("CloseAllConnectionsToolButton"));
        CloseAllConnectionsToolButton->setEnabled(false);
        CloseAllConnectionsToolButton->setIcon(icon3);
        CloseAllConnectionsToolButton->setIconSize(QSize(32, 32));
        CloseAllConnectionsToolButton->setAutoRaise(true);

        horizontalLayout->addWidget(CloseAllConnectionsToolButton);

        RefreshTablesToolButton = new QToolButton(CentralWidget);
        RefreshTablesToolButton->setObjectName(QStringLiteral("RefreshTablesToolButton"));
        RefreshTablesToolButton->setEnabled(false);
        RefreshTablesToolButton->setIcon(icon6);
        RefreshTablesToolButton->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(RefreshTablesToolButton);

        StatusLabel = new QLabel(CentralWidget);
        StatusLabel->setObjectName(QStringLiteral("StatusLabel"));

        horizontalLayout->addWidget(StatusLabel);

        MainHorizontalSplitter = new QSplitter(CentralWidget);
        MainHorizontalSplitter->setObjectName(QStringLiteral("MainHorizontalSplitter"));
        MainHorizontalSplitter->setOrientation(Qt::Horizontal);
        HorizontalSplitter = new QSplitter(MainHorizontalSplitter);
        HorizontalSplitter->setObjectName(QStringLiteral("HorizontalSplitter"));
        HorizontalSplitter->setOrientation(Qt::Horizontal);
        TableTreeWidget = new QTreeWidget(HorizontalSplitter);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        TableTreeWidget->setHeaderItem(__qtreewidgetitem);
        TableTreeWidget->setObjectName(QStringLiteral("TableTreeWidget"));
        TableTreeWidget->setAlternatingRowColors(false);
        TableTreeWidget->setIndentation(15);
        TableTreeWidget->setRootIsDecorated(true);
        TableTreeWidget->setItemsExpandable(true);
        TableTreeWidget->setAnimated(true);
        TableTreeWidget->setExpandsOnDoubleClick(true);
        HorizontalSplitter->addWidget(TableTreeWidget);
        TableTreeWidget->header()->setVisible(true);
        MainHorizontalSplitter->addWidget(HorizontalSplitter);
        VerticalSplitter = new QSplitter(MainHorizontalSplitter);
        VerticalSplitter->setObjectName(QStringLiteral("VerticalSplitter"));
        VerticalSplitter->setCursor(QCursor(Qt::ArrowCursor));
        VerticalSplitter->setOrientation(Qt::Vertical);
        ResultCountLabel = new QLabel(VerticalSplitter);
        ResultCountLabel->setObjectName(QStringLiteral("ResultCountLabel"));
        ResultCountLabel->setMargin(3);
        VerticalSplitter->addWidget(ResultCountLabel);
        SQLResultTableView = new ODBC_TableView(VerticalSplitter);
        SQLResultTableView->setObjectName(QStringLiteral("SQLResultTableView"));
        QFont font;
        font.setPointSize(8);
        font.setKerning(true);
        SQLResultTableView->setFont(font);
        SQLResultTableView->viewport()->setProperty("cursor", QVariant(QCursor(Qt::ArrowCursor)));
        SQLResultTableView->setFrameShape(QFrame::StyledPanel);
        SQLResultTableView->setFrameShadow(QFrame::Sunken);
        SQLResultTableView->setMidLineWidth(1);
        SQLResultTableView->setAlternatingRowColors(true);
        SQLResultTableView->setSortingEnabled(true);
        VerticalSplitter->addWidget(SQLResultTableView);
        SQLResultTableView->verticalHeader()->setDefaultSectionSize(20);
        horizontalLayoutWidget = new QWidget(VerticalSplitter);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        HorizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget);
        HorizontalLayout_3->setSpacing(6);
        HorizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        HorizontalLayout_3->setObjectName(QStringLiteral("HorizontalLayout_3"));
        HorizontalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        HorizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        ExecuteToolButton = new QToolButton(horizontalLayoutWidget);
        ExecuteToolButton->setObjectName(QStringLiteral("ExecuteToolButton"));
        ExecuteToolButton->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ExecuteToolButton->sizePolicy().hasHeightForWidth());
        ExecuteToolButton->setSizePolicy(sizePolicy);
        ExecuteToolButton->setLayoutDirection(Qt::LeftToRight);
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/ODBC_Query/Resources/play_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        ExecuteToolButton->setIcon(icon8);
        ExecuteToolButton->setIconSize(QSize(20, 20));
        ExecuteToolButton->setCheckable(false);
        ExecuteToolButton->setAutoRaise(true);

        HorizontalLayout_3->addWidget(ExecuteToolButton);

        Line = new QFrame(horizontalLayoutWidget);
        Line->setObjectName(QStringLiteral("Line"));
        Line->setWindowModality(Qt::NonModal);
        Line->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Line->sizePolicy().hasHeightForWidth());
        Line->setSizePolicy(sizePolicy1);
        Line->setFrameShape(QFrame::VLine);
        Line->setFrameShadow(QFrame::Sunken);

        HorizontalLayout_3->addWidget(Line);

        LeftToolButton = new QToolButton(horizontalLayoutWidget);
        LeftToolButton->setObjectName(QStringLiteral("LeftToolButton"));
        LeftToolButton->setEnabled(false);
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/ODBC_Query/Resources/left_arrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        LeftToolButton->setIcon(icon9);
        LeftToolButton->setIconSize(QSize(20, 20));
        LeftToolButton->setAutoRaise(true);

        HorizontalLayout_3->addWidget(LeftToolButton);

        CurrentStatementLabel = new QLabel(horizontalLayoutWidget);
        CurrentStatementLabel->setObjectName(QStringLiteral("CurrentStatementLabel"));
        CurrentStatementLabel->setEnabled(false);

        HorizontalLayout_3->addWidget(CurrentStatementLabel);

        RightToolButton = new QToolButton(horizontalLayoutWidget);
        RightToolButton->setObjectName(QStringLiteral("RightToolButton"));
        RightToolButton->setEnabled(false);
        sizePolicy.setHeightForWidth(RightToolButton->sizePolicy().hasHeightForWidth());
        RightToolButton->setSizePolicy(sizePolicy);
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/ODBC_Query/Resources/right_arrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        RightToolButton->setIcon(icon10);
        RightToolButton->setIconSize(QSize(20, 20));
        RightToolButton->setAutoRaise(true);

        HorizontalLayout_3->addWidget(RightToolButton);

        Line_2 = new QFrame(horizontalLayoutWidget);
        Line_2->setObjectName(QStringLiteral("Line_2"));
        sizePolicy1.setHeightForWidth(Line_2->sizePolicy().hasHeightForWidth());
        Line_2->setSizePolicy(sizePolicy1);
        Line_2->setMaximumSize(QSize(16777215, 16777215));
        Line_2->setSizeIncrement(QSize(0, 0));
        Line_2->setBaseSize(QSize(0, 0));
        Line_2->setFrameShape(QFrame::VLine);
        Line_2->setFrameShadow(QFrame::Sunken);

        HorizontalLayout_3->addWidget(Line_2);

        ExtractToolButton = new QToolButton(horizontalLayoutWidget);
        ExtractToolButton->setObjectName(QStringLiteral("ExtractToolButton"));
        ExtractToolButton->setEnabled(false);
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/ODBC_Query/Resources/expand.png"), QSize(), QIcon::Normal, QIcon::Off);
        ExtractToolButton->setIcon(icon11);
        ExtractToolButton->setIconSize(QSize(20, 20));
        ExtractToolButton->setAutoRaise(true);

        HorizontalLayout_3->addWidget(ExtractToolButton);

        HorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayout_3->addItem(HorizontalSpacer);

        VerticalSplitter->addWidget(horizontalLayoutWidget);
        SQLCommandTextEdit = new QTextEdit(VerticalSplitter);
        SQLCommandTextEdit->setObjectName(QStringLiteral("SQLCommandTextEdit"));
        VerticalSplitter->addWidget(SQLCommandTextEdit);
        SQLLogTextBrowser = new QTextBrowser(VerticalSplitter);
        SQLLogTextBrowser->setObjectName(QStringLiteral("SQLLogTextBrowser"));
        SQLLogTextBrowser->setReadOnly(true);
        VerticalSplitter->addWidget(SQLLogTextBrowser);
        MainHorizontalSplitter->addWidget(VerticalSplitter);

        horizontalLayout->addWidget(MainHorizontalSplitter);

        ODBC_QueryClass->setCentralWidget(CentralWidget);
        MenuBar = new QMenuBar(ODBC_QueryClass);
        MenuBar->setObjectName(QStringLiteral("MenuBar"));
        MenuBar->setGeometry(QRect(0, 0, 1074, 21));
        FileMenu = new QMenu(MenuBar);
        FileMenu->setObjectName(QStringLiteral("FileMenu"));
        ConnectionsMenu = new QMenu(MenuBar);
        ConnectionsMenu->setObjectName(QStringLiteral("ConnectionsMenu"));
        OpenConnectionsMenu = new QMenu(ConnectionsMenu);
        OpenConnectionsMenu->setObjectName(QStringLiteral("OpenConnectionsMenu"));
        OpenConnectionsMenu->setEnabled(false);
        OpenConnectionsMenu->setIcon(icon7);
        ViewMenu = new QMenu(MenuBar);
        ViewMenu->setObjectName(QStringLiteral("ViewMenu"));
        ToolsMenu = new QMenu(MenuBar);
        ToolsMenu->setObjectName(QStringLiteral("ToolsMenu"));
        HelpMenu = new QMenu(MenuBar);
        HelpMenu->setObjectName(QStringLiteral("HelpMenu"));
        ODBC_QueryClass->setMenuBar(MenuBar);
        StatusBar = new QStatusBar(ODBC_QueryClass);
        StatusBar->setObjectName(QStringLiteral("StatusBar"));
        StatusBar->setSizeGripEnabled(true);
        ODBC_QueryClass->setStatusBar(StatusBar);
        ToolBar = new QToolBar(ODBC_QueryClass);
        ToolBar->setObjectName(QStringLiteral("ToolBar"));
        ODBC_QueryClass->addToolBar(Qt::TopToolBarArea, ToolBar);

        MenuBar->addAction(FileMenu->menuAction());
        MenuBar->addAction(ConnectionsMenu->menuAction());
        MenuBar->addAction(ViewMenu->menuAction());
        MenuBar->addAction(ToolsMenu->menuAction());
        MenuBar->addAction(HelpMenu->menuAction());
        FileMenu->addAction(ExitAction);
        ConnectionsMenu->addAction(NewConnectionAction);
        ConnectionsMenu->addAction(OpenConnectionsMenu->menuAction());
        ConnectionsMenu->addAction(CloseAllConnectionsAction);
        ConnectionsMenu->addAction(RefreshTablesAction);
        ViewMenu->addAction(ShowToolbarAction);
        ViewMenu->addAction(SyntaxHighlightingAction);
        ToolsMenu->addAction(OptionsAction);
        HelpMenu->addAction(AboutAction);

        retranslateUi(ODBC_QueryClass);

        QMetaObject::connectSlotsByName(ODBC_QueryClass);
    } // setupUi

    void retranslateUi(QMainWindow *ODBC_QueryClass)
    {
        ODBC_QueryClass->setWindowTitle(QApplication::translate("ODBC_QueryClass", "ODBC Query", 0));
        ExitAction->setText(QApplication::translate("ODBC_QueryClass", "Exit", 0));
#ifndef QT_NO_TOOLTIP
        ExitAction->setToolTip(QApplication::translate("ODBC_QueryClass", "Close program", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        ExitAction->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        NewConnectionAction->setText(QApplication::translate("ODBC_QueryClass", "New connection", 0));
#ifndef QT_NO_STATUSTIP
        NewConnectionAction->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        CloseAllConnectionsAction->setText(QApplication::translate("ODBC_QueryClass", "Close all connections", 0));
#ifndef QT_NO_STATUSTIP
        CloseAllConnectionsAction->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        actionTest->setText(QApplication::translate("ODBC_QueryClass", "test", 0));
        ShowToolbarAction->setText(QApplication::translate("ODBC_QueryClass", "Show toolbar", 0));
        SyntaxHighlightingAction->setText(QApplication::translate("ODBC_QueryClass", "Syntax highlighting", 0));
        OptionsAction->setText(QApplication::translate("ODBC_QueryClass", "Options", 0));
        AboutAction->setText(QApplication::translate("ODBC_QueryClass", "About", 0));
        RefreshTablesAction->setText(QApplication::translate("ODBC_QueryClass", "Refresh all tables", 0));
#ifndef QT_NO_TOOLTIP
        AddConnectionToolButton->setToolTip(QApplication::translate("ODBC_QueryClass", "New connection", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        AddConnectionToolButton->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        AddConnectionToolButton->setText(QString());
        OpenConnectionsToolButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        CloseAllConnectionsToolButton->setToolTip(QApplication::translate("ODBC_QueryClass", "Close all connections", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        CloseAllConnectionsToolButton->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        CloseAllConnectionsToolButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        RefreshTablesToolButton->setToolTip(QApplication::translate("ODBC_QueryClass", "Refreshes all tables", 0));
#endif // QT_NO_TOOLTIP
        RefreshTablesToolButton->setText(QString());
        StatusLabel->setText(QString());
        ResultCountLabel->setText(QApplication::translate("ODBC_QueryClass", "Rows: ", 0));
#ifndef QT_NO_TOOLTIP
        ExecuteToolButton->setToolTip(QApplication::translate("ODBC_QueryClass", "<F5> Starts/Stops execution of the entered SQL statement", 0));
#endif // QT_NO_TOOLTIP
        ExecuteToolButton->setText(QString());
        LeftToolButton->setText(QApplication::translate("ODBC_QueryClass", "left", 0));
        CurrentStatementLabel->setText(QApplication::translate("ODBC_QueryClass", "1", 0));
        RightToolButton->setText(QApplication::translate("ODBC_QueryClass", "right", 0));
#ifndef QT_NO_TOOLTIP
        ExtractToolButton->setToolTip(QApplication::translate("ODBC_QueryClass", "Copies the current result to a separate window", 0));
#endif // QT_NO_TOOLTIP
        ExtractToolButton->setText(QString());
        FileMenu->setTitle(QApplication::translate("ODBC_QueryClass", "File", 0));
        ConnectionsMenu->setTitle(QApplication::translate("ODBC_QueryClass", "Connections", 0));
#ifndef QT_NO_TOOLTIP
        OpenConnectionsMenu->setToolTip(QApplication::translate("ODBC_QueryClass", "Open existing connections", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        OpenConnectionsMenu->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        OpenConnectionsMenu->setTitle(QApplication::translate("ODBC_QueryClass", "Open connections...", 0));
        ViewMenu->setTitle(QApplication::translate("ODBC_QueryClass", "View", 0));
        ToolsMenu->setTitle(QApplication::translate("ODBC_QueryClass", "Tools", 0));
        HelpMenu->setTitle(QApplication::translate("ODBC_QueryClass", "Help", 0));
        ToolBar->setWindowTitle(QApplication::translate("ODBC_QueryClass", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class ODBC_QueryClass: public Ui_ODBC_QueryClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ODBC_QUERY_H

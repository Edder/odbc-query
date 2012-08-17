#include "precompiled.h"
#include "ODBC_Query.h"
#include "ODBC_CustomSyntaxHighlighter.h"
#include "ODBC_Connection.h"

ODBC_Query::ODBC_Query(QWidget *parent, Qt::WFlags flags) : QMainWindow(parent, flags)
{
	ui.setupUi(this);

	InitGui();

	m_pCurrentConnection = NULL;
}

ODBC_Query::~ODBC_Query()
{
	CloseAllConnections();

	if (m_pCurrentConnection != NULL)
	{
		delete m_pCurrentConnection;
		m_pCurrentConnection = NULL;
	}
}

void ODBC_Query::InitGui()
{
	// set the default sizes of the splitter
	QList<int> list;
	list << 1000 << 50 << 100 << 100;
	ui.VerticalSplitter->setSizes(list);
	list.clear();
	list << 500 << 1000;
	ui.MainHorizontalSplitter->setSizes(list);

	// setup gui
	ui.StatusBar->addPermanentWidget(ui.StatusLabel, -1);
	ui.TableTreeWidget->setHeaderLabel("Tables");
	ui.FieldTreeWidget->setHeaderLabels(QStringList() << "Name" << "Type" << "Length" << "Nullable");
	ui.FieldTreeWidget->resizeColumnToContents(1);
	ui.FieldTreeWidget->resizeColumnToContents(2);	
	ui.FieldTreeWidget->resizeColumnToContents(3);

	installEventFilter(this);

	// init the syntax highlighter
	ODBC_CustomSyntaxHighlighter *highlighter = new ODBC_CustomSyntaxHighlighter(ui.SQLCommandTextEdit->document());
	highlighter->Init();

	// connect gui signals to slots
	QObject::connect(ui.ExecuteToolButton, SIGNAL(clicked()), SLOT(ExecuteButtonClicked()));
	QObject::connect(ui.LeftToolButton, SIGNAL(clicked()), SLOT(LeftButtonClicked()));
	QObject::connect(ui.RightToolButton, SIGNAL(clicked()), SLOT(RightButtonClicked()));
	QObject::connect(ui.TableTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), SLOT(TableItemClicked(QTreeWidgetItem*, int)));
	QObject::connect(ui.ActionExit, SIGNAL(triggered()), SLOT(Exit()));
	QObject::connect(ui.ActionNew_Connection, SIGNAL(triggered()), SLOT(NewConnection()));
	QObject::connect(ui.ActionClose_all_connections, SIGNAL(triggered()), SLOT(CloseAllConnections()));
}

void ODBC_Query::ResetGui()
{
	ui.TableTreeWidget->clear();
	ui.FieldTreeWidget->clear();
	ui.SQLCommandTextEdit->clear();
	ui.SQLLogTextBrowser->clear();
	ui.CurrentStatementLabel->setText("1");
	ui.StatusLabel->clear();
	ui.SQLResultTableView->setModel(NULL);
	ui.MenuOpen_connections->clear();
	ui.MenuOpen_connections->setDisabled(true);
}

void ODBC_Query::SetQueryToolbar(bool activate)
{
	if (activate)
	{
		if (!ui.ExecuteToolButton->isEnabled())
			ui.ExecuteToolButton->setEnabled(true);

		if (!ui.CurrentStatementLabel->isEnabled())
			ui.CurrentStatementLabel->setEnabled(true);
	}
	else
	{
		if (ui.ExecuteToolButton->isEnabled())
			ui.ExecuteToolButton->setDisabled(true);

		if (ui.CurrentStatementLabel->isEnabled())
			ui.CurrentStatementLabel->setDisabled(true);
	}
}

// <SLOTS>
void ODBC_Query::ExecuteButtonClicked()
{
	if (m_pCurrentConnection != NULL)
		m_pCurrentConnection->ExecuteQuery(ui.SQLCommandTextEdit->toPlainText(), true);
}

void ODBC_Query::LeftButtonClicked()
{
	if (m_pCurrentConnection != NULL)
		m_pCurrentConnection->HandleLeftRightButton(false);
}

void ODBC_Query::RightButtonClicked()
{
	if (m_pCurrentConnection != NULL)
		m_pCurrentConnection->HandleLeftRightButton(true);
}

void ODBC_Query::TableItemClicked(QTreeWidgetItem *item, int column)
{
	if (m_pCurrentConnection != NULL)
		m_pCurrentConnection->LoadTableColumns(item->text(0));
}

void ODBC_Query::Exit()
{
	QApplication::exit();
}

void ODBC_Query::NewConnection()
{
	ODBC_ConnectionDialog connectiondialog;
	connectiondialog.Init();
	connectiondialog.exec();
	QString database = connectiondialog.getDatabase();
	if (database == "") // if database is empty, no selection is made
		return;

	// set wait cursor
	setCursor(Qt::WaitCursor);
	QApplication::processEvents();
	QString newConnectionName = QString("%1 (%2)").arg(database, connectiondialog.isSystemDSN() ? "System" : "User");
	// check whether we already have a connection with that name
	for (int i = 0, count = m_lConnections.count(); i < count; i++)
	{
		ODBC_Connection *connection = m_lConnections.value(i);
		if (connection != NULL)
		{
			if (connection->getConnectionName() == newConnectionName)
			{
				setCursor(Qt::ArrowCursor);
				return;
			}
		}
	}

	// close the current connection (if there is one)
	if (m_pCurrentConnection != NULL)
		m_pCurrentConnection->CloseConnection();
	m_pCurrentConnection = NULL;
	// make a new connection
	m_pCurrentConnection = new ODBC_Connection(ui);
	m_pCurrentConnection->OpenConnection(newConnectionName);
	// and connect to the dsn
	if (m_pCurrentConnection->ConnectToDatabase(database, connectiondialog.getUsername(), connectiondialog.getPassword(), true))
	{
		// set the status label
		ui.StatusLabel->setText(QString("Connected to %1").arg(newConnectionName));
		m_lConnections.append(m_pCurrentConnection);
		// add a new action with the connectionName
		QAction *pAction = new QAction(newConnectionName, this);
		pAction->setCheckable(true);
		pAction->setChecked(true);
		ui.MenuOpen_connections->addAction(pAction);
		// make a submenu under connection
		QMenu *pMenu = new QMenu(newConnectionName, this); 
		QObject::connect(pMenu, SIGNAL(triggered(QAction*)), SLOT(ConnectionsClicked(QAction*)));
		pMenu->addAction("Select");
		pMenu->addAction("Disconnect");
		// set the menu to the action
		pAction->setMenu(pMenu);
		for (int i = 0, count = ui.MenuOpen_connections->actions().count(); i < count; i++)
		{
			QAction *pAction = ui.MenuOpen_connections->actions().value(i);
			if (pAction->text() != newConnectionName)
				pAction->setChecked(false);
		}
		if (!ui.MenuOpen_connections->isEnabled())
			ui.MenuOpen_connections->setEnabled(true);

		SetQueryToolbar(true);
	}
	// set back to arrow cursor
	setCursor(Qt::ArrowCursor);
}

void ODBC_Query::CloseAllConnections()
{
	// iterate through all connections and close them
	for (int i = 0, count = m_lConnections.count(); i < count; i++)
	{
		ODBC_Connection *pConnection = m_lConnections.value(i);
		if (pConnection != NULL)
		{
			pConnection->CloseConnection();
			delete pConnection;
			pConnection = NULL;
		}
	}
	m_lConnections.clear();
	m_pCurrentConnection = NULL;
	
	ResetGui();
}

void ODBC_Query::ConnectionsClicked(QAction *action)
{
	setCursor(Qt::WaitCursor);
	QApplication::processEvents();
	QMenu *menu = (QMenu*)action->parentWidget();
	QString command = action->text();
	if (command == "Select")
	{
		for (int i = 0, count = m_lConnections.count(); i < count; i++)
		{
			ODBC_Connection *connection = m_lConnections.value(i);
			QString newConnectionName = menu->title();
			if (connection != NULL)
			{
				QString oldConnectionName = connection->getConnectionName();
				if (oldConnectionName != newConnectionName)
					continue;

				if (m_pCurrentConnection != NULL)
				{
					if (m_pCurrentConnection->getConnectionName() != oldConnectionName)
					{
						m_pCurrentConnection->CloseConnection();
						m_pCurrentConnection = connection;
						m_pCurrentConnection->OpenConnection(newConnectionName);
						m_pCurrentConnection->ConnectToDatabase("", "", "", false);
						for (int j = 0, count = ui.MenuOpen_connections->actions().count(); j < count; j++)
						{					
							if (ui.MenuOpen_connections->actions().value(j)->text() != newConnectionName)
								ui.MenuOpen_connections->actions().value(j)->setChecked(false);
							else
								ui.MenuOpen_connections->actions().value(j)->setChecked(true);
						}
					}
				}
			}
		}
	}
	else if (command == "Disconnect")
	{
		QString ConnectionNameToClose = menu->title();
		QAction *action;

		
		for (int i = 0, count = ui.MenuOpen_connections->actions().count(); i < count; i++)
		{
			action = ui.MenuOpen_connections->actions().value(i);
			if (action->text() == ConnectionNameToClose)
				break;
		}

		bool foundConnection = false;
		if (m_pCurrentConnection != NULL)
		{
			if (m_pCurrentConnection->getConnectionName() == ConnectionNameToClose) // is it the current connection we need to close?
			{
				m_lConnections.removeOne(m_pCurrentConnection);
				ui.MenuOpen_connections->removeAction(action);
				m_pCurrentConnection->CloseConnection();
				delete m_pCurrentConnection;
				m_pCurrentConnection = NULL;
				ResetGui();
				SetQueryToolbar(false);
				foundConnection = true;
			}
		}

		if (!foundConnection)
		{
			// nope, we have to iterate through all connections
			for (int i = 0, count = m_lConnections.count(); i < count; i++)
			{
				ODBC_Connection *connection = m_lConnections.value(i);
				if (connection != NULL)
				{
					QString CurrentConnectionName = connection->getConnectionName();
					if (CurrentConnectionName != ConnectionNameToClose)
						continue;

					m_lConnections.removeAt(i);
					ui.MenuOpen_connections->removeAction(action);
					connection->CloseConnection();
					delete connection;
					connection = NULL;
				}
			}
		}
		if (ui.MenuOpen_connections->actions().count() == 0)
			ui.MenuOpen_connections->setDisabled(true);
	}
	setCursor(Qt::ArrowCursor);
}
// </SLOTS>

bool ODBC_Query::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_F5) 
			ExecuteButtonClicked();
		else
            return false;
    }
    return false;
}
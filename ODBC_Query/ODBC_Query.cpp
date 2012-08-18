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
<<<<<<< HEAD
	CloseAllConnections(true);
=======
	CloseAllConnections();
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9

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
<<<<<<< HEAD
	ui.ToolBar->addWidget(ui.AddConnectionToolButton);
	ui.ToolBar->addWidget(ui.OpenConnectionsToolButton);
	ui.OpenConnectionsToolButton->setMenu(ui.OpenConnectionsMenu);
	ui.ToolBar->addWidget(ui.CloseAllConnectionsToolButton);
=======
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9

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
<<<<<<< HEAD
	QObject::connect(ui.NewConnectionAction, SIGNAL(triggered()), SLOT(NewConnection()));
	QObject::connect(ui.AddConnectionToolButton, SIGNAL(clicked()), SLOT(NewConnection()));
	QObject::connect(ui.CloseAllConnectionsAction, SIGNAL(triggered()), SLOT(CloseAllConnections()));
	QObject::connect(ui.CloseAllConnectionsToolButton, SIGNAL(clicked()), SLOT(CloseAllConnections()));
	QObject::connect(ui.SQLCommandTextEdit, SIGNAL(textChanged()), SLOT(SQLCommandTextChanged()));
=======
	QObject::connect(ui.ActionNew_Connection, SIGNAL(triggered()), SLOT(NewConnection()));
	QObject::connect(ui.ActionClose_all_connections, SIGNAL(triggered()), SLOT(CloseAllConnections()));
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
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
<<<<<<< HEAD
	if (m_lConnections.count() == 0)
	{
		ui.OpenConnectionsMenu->clear();
		ui.OpenConnectionsMenu->setDisabled(true);
		ui.OpenConnectionsToolButton->setDisabled(true);
		ui.CloseAllConnectionsAction->setDisabled(true);
		ui.CloseAllConnectionsToolButton->setDisabled(true);
	}
	DisableQueryToolbar();
}

void ODBC_Query::DisableQueryToolbar()
{
	if (ui.ExecuteToolButton->isEnabled())
		ui.ExecuteToolButton->setDisabled(true);

	if (ui.CurrentStatementLabel->isEnabled())
		ui.CurrentStatementLabel->setDisabled(true);

	if (m_pCurrentConnection == NULL)
	{
		if (ui.RightToolButton->isEnabled())
			ui.RightToolButton->setDisabled(true);

		if (ui.LeftToolButton->isEnabled())
			ui.LeftToolButton->setDisabled(true);
=======
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
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
	}
}

// <SLOTS>
void ODBC_Query::ExecuteButtonClicked()
{
<<<<<<< HEAD
	if (m_pCurrentConnection != NULL && ui.ExecuteToolButton->isEnabled())
=======
	if (m_pCurrentConnection != NULL)
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
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

<<<<<<< HEAD
	ResetGui();

=======
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
	// close the current connection (if there is one)
	if (m_pCurrentConnection != NULL)
		m_pCurrentConnection->CloseConnection();
	m_pCurrentConnection = NULL;
	// make a new connection
<<<<<<< HEAD
	m_pCurrentConnection = new ODBC_Connection(ui, this);
	m_pCurrentConnection->OpenConnection(newConnectionName);
	// and connect to the dsn
	if (m_pCurrentConnection->ConnectToDatabase(true, database, connectiondialog.getUsername(), connectiondialog.getPassword()))
=======
	m_pCurrentConnection = new ODBC_Connection(ui);
	m_pCurrentConnection->OpenConnection(newConnectionName);
	// and connect to the dsn
	if (m_pCurrentConnection->ConnectToDatabase(database, connectiondialog.getUsername(), connectiondialog.getPassword(), true))
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
	{
		// set the status label
		ui.StatusLabel->setText(QString("Connected to %1").arg(newConnectionName));
		m_lConnections.append(m_pCurrentConnection);
		// add a new action with the connectionName
		QAction *pAction = new QAction(newConnectionName, this);
		pAction->setCheckable(true);
		pAction->setChecked(true);
<<<<<<< HEAD
		ui.OpenConnectionsMenu->addAction(pAction);
=======
		ui.MenuOpen_connections->addAction(pAction);
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
		// make a submenu under connection
		QMenu *pMenu = new QMenu(newConnectionName, this); 
		QObject::connect(pMenu, SIGNAL(triggered(QAction*)), SLOT(ConnectionsClicked(QAction*)));
		pMenu->addAction("Select");
		pMenu->addAction("Disconnect");
		// set the menu to the action
		pAction->setMenu(pMenu);
<<<<<<< HEAD
		for (int i = 0, count = ui.OpenConnectionsMenu->actions().count(); i < count; i++)
		{
			QAction *pAction = ui.OpenConnectionsMenu->actions().value(i);
			if (pAction->text() != newConnectionName)
				pAction->setChecked(false);
		}
		if (!ui.OpenConnectionsMenu->isEnabled())
			ui.OpenConnectionsMenu->setEnabled(true);

		if (!ui.OpenConnectionsToolButton->isEnabled())
			ui.OpenConnectionsToolButton->setEnabled(true);

		if (!ui.CloseAllConnectionsAction->isEnabled())
			ui.CloseAllConnectionsAction->setEnabled(true);

		if (!ui.CloseAllConnectionsToolButton->isEnabled())
			ui.CloseAllConnectionsToolButton->setEnabled(true);
=======
		for (int i = 0, count = ui.MenuOpen_connections->actions().count(); i < count; i++)
		{
			QAction *pAction = ui.MenuOpen_connections->actions().value(i);
			if (pAction->text() != newConnectionName)
				pAction->setChecked(false);
		}
		if (!ui.MenuOpen_connections->isEnabled())
			ui.MenuOpen_connections->setEnabled(true);

		SetQueryToolbar(true);
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
	}
	// set back to arrow cursor
	setCursor(Qt::ArrowCursor);
}

<<<<<<< HEAD
void ODBC_Query::CloseAllConnections(bool close)
{
	if (m_lConnections.count() == 0)
		return;

	if (!close)
		if (QMessageBox::question(this, "Connections", "Do you really want to disconnect from all open connections?", QMessageBox::Yes, QMessageBox::No) != QMessageBox::Yes)
			return;

=======
void ODBC_Query::CloseAllConnections()
{
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
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
<<<<<<< HEAD
						m_pCurrentConnection->ConnectToDatabase(false);
						for (int j = 0, count = ui.OpenConnectionsMenu->actions().count(); j < count; j++)
						{					
							if (ui.OpenConnectionsMenu->actions().value(j)->text() != newConnectionName)
								ui.OpenConnectionsMenu->actions().value(j)->setChecked(false);
							else
								ui.OpenConnectionsMenu->actions().value(j)->setChecked(true);
						}
					}
				}
				else
				{
					m_pCurrentConnection = connection;
					m_pCurrentConnection->OpenConnection(newConnectionName);
					m_pCurrentConnection->ConnectToDatabase(false);
					for (int j = 0, count = ui.OpenConnectionsMenu->actions().count(); j < count; j++)
					{					
						if (ui.OpenConnectionsMenu->actions().value(j)->text() != newConnectionName)
							ui.OpenConnectionsMenu->actions().value(j)->setChecked(false);
						else
							ui.OpenConnectionsMenu->actions().value(j)->setChecked(true);
					}
				}
=======
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
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
			}
		}
	}
	else if (command == "Disconnect")
	{
		QString ConnectionNameToClose = menu->title();
		QAction *action;
<<<<<<< HEAD
		
		for (int i = 0, count = ui.OpenConnectionsMenu->actions().count(); i < count; i++)
		{
			action = ui.OpenConnectionsMenu->actions().value(i);
=======

		
		for (int i = 0, count = ui.MenuOpen_connections->actions().count(); i < count; i++)
		{
			action = ui.MenuOpen_connections->actions().value(i);
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
			if (action->text() == ConnectionNameToClose)
				break;
		}

		bool foundConnection = false;
		if (m_pCurrentConnection != NULL)
		{
			if (m_pCurrentConnection->getConnectionName() == ConnectionNameToClose) // is it the current connection we need to close?
			{
				m_lConnections.removeOne(m_pCurrentConnection);
<<<<<<< HEAD
				ui.OpenConnectionsMenu->removeAction(action);
=======
				ui.MenuOpen_connections->removeAction(action);
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
				m_pCurrentConnection->CloseConnection();
				delete m_pCurrentConnection;
				m_pCurrentConnection = NULL;
				ResetGui();
<<<<<<< HEAD
=======
				SetQueryToolbar(false);
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
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
<<<<<<< HEAD
					ui.OpenConnectionsMenu->removeAction(action);
=======
					ui.MenuOpen_connections->removeAction(action);
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
					connection->CloseConnection();
					delete connection;
					connection = NULL;
				}
			}
		}
<<<<<<< HEAD
		if (ui.OpenConnectionsMenu->actions().count() == 0)
			ui.OpenConnectionsMenu->setDisabled(true);
	}
	setCursor(Qt::ArrowCursor);
}

void ODBC_Query::SQLCommandTextChanged()
{
	if (m_pCurrentConnection != NULL)
		m_pCurrentConnection->HandleSQLCommandTextChanged();
}
=======
		if (ui.MenuOpen_connections->actions().count() == 0)
			ui.MenuOpen_connections->setDisabled(true);
	}
	setCursor(Qt::ArrowCursor);
}
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
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
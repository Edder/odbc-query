#include "precompiled.h"
#include "ODBC_Query.h"
#include "ODBC_CustomSyntaxHighlighter.h"
#include "ODBC_Connection.h"
#include "Logging.h"

ODBC_Query::ODBC_Query(QWidget *parent, Qt::WFlags flags) : QMainWindow(parent, flags)
{
	ui.setupUi(this);

	QCoreApplication::setApplicationName("ODBC Query");

	Logging::getInstance()->Init();
	Logging::getInstance()->WriteLog(INFORMATION, QString("Starting %1...").arg(QCoreApplication::applicationName()));

	InitGui();

	m_pCurrentConnection = NULL;
}

ODBC_Query::~ODBC_Query()
{
	Logging::getInstance()->WriteLog(INFORMATION, QString("Closing %1...").arg(QCoreApplication::applicationName()));

	CloseAllConnections(true);

	m_pCurrentConnection = NULL;

	Logging::getInstance()->WriteLog(INFORMATION, QString("Shutting down %1").arg(QCoreApplication::applicationName()));
}

void ODBC_Query::InitGui()
{
	Logging::getInstance()->WriteLog(INFORMATION, "Initializing gui...");

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
	ui.ToolBar->addWidget(ui.AddConnectionToolButton);
	ui.ToolBar->addWidget(ui.OpenConnectionsToolButton);
	ui.OpenConnectionsToolButton->setMenu(ui.OpenConnectionsMenu);
	ui.ToolBar->addWidget(ui.CloseAllConnectionsToolButton);

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
	QObject::connect(ui.NewConnectionAction, SIGNAL(triggered()), SLOT(NewConnection()));
	QObject::connect(ui.AddConnectionToolButton, SIGNAL(clicked()), SLOT(NewConnection()));
	QObject::connect(ui.CloseAllConnectionsAction, SIGNAL(triggered()), SLOT(CloseAllConnections()));
	QObject::connect(ui.CloseAllConnectionsToolButton, SIGNAL(clicked()), SLOT(CloseAllConnections()));
	QObject::connect(ui.SQLCommandTextEdit, SIGNAL(textChanged()), SLOT(SQLCommandTextChanged()));

	Logging::getInstance()->WriteLog(INFORMATION, "Gui initialized");
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
	}
}

// <SLOTS>
void ODBC_Query::ExecuteButtonClicked()
{
	if (m_pCurrentConnection != NULL && ui.ExecuteToolButton->isEnabled())
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
	Logging::getInstance()->WriteLog(INFORMATION, "Opening new connection...");
	ODBC_ConnectionDialog connectiondialog;
	connectiondialog.Init();
	connectiondialog.exec();
	if (!connectiondialog.isValid())
		return;

	QString sDatabase = connectiondialog.getDatabase();

	// set wait cursor
	setCursor(Qt::WaitCursor);
	QApplication::processEvents();
	QString sNewConnectionName = QString("%1 (%2)").arg(sDatabase, connectiondialog.isSystemDSN() ? "System" : "User");
	// check whether we already have a connection with that name
	for (int i = 0, count = m_lConnections.count(); i < count; i++)
	{
		ODBC_Connection *connection = m_lConnections.value(i);
		if (connection != NULL)
		{
			if (connection->getConnectionName() == sNewConnectionName)
			{
				setCursor(Qt::ArrowCursor);
				return;
			}
		}
	}

	Logging::getInstance()->WriteLog(INFORMATION, QString("Connecting to \"%1\"").arg(sNewConnectionName));

	// close the current connection (if there is one)
	if (m_pCurrentConnection != NULL)
		m_pCurrentConnection->CloseConnection();
	m_pCurrentConnection = NULL;
	// make a new connection
	m_pCurrentConnection = new ODBC_Connection(ui, this);
	m_pCurrentConnection->OpenConnection(sNewConnectionName);
	ResetGui();
	// and connect to the dsn
	if (m_pCurrentConnection->ConnectToDatabase(false, sDatabase, connectiondialog.getUsername(), connectiondialog.getPassword()))
	{
		// set the status label
		ui.StatusLabel->setText(QString("Connected to %1").arg(sNewConnectionName));
		m_lConnections.append(m_pCurrentConnection);
		// add a new action with the connectionName
		QAction *pAction = new QAction(sNewConnectionName, this);
		pAction->setCheckable(true);
		pAction->setChecked(true);
		ui.OpenConnectionsMenu->addAction(pAction);
		// make a submenu under connection
		QMenu *pMenu = new QMenu(sNewConnectionName, this); 
		QObject::connect(pMenu, SIGNAL(triggered(QAction*)), SLOT(ConnectionsClicked(QAction*)));
		pMenu->addAction("Select");
		pMenu->addAction("Disconnect");
		// set the menu to the action
		pAction->setMenu(pMenu);
		for (int i = 0, count = ui.OpenConnectionsMenu->actions().count(); i < count; i++)
		{
			QAction *pAction = ui.OpenConnectionsMenu->actions().value(i);
			if (pAction->text() != sNewConnectionName)
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
	}
	// set back to arrow cursor
	setCursor(Qt::ArrowCursor);
}

void ODBC_Query::CloseAllConnections(bool close)
{
	if (m_lConnections.count() == 0)
		return;

	if (!close)
		if (QMessageBox::question(this, "Connections", "Do you really want to disconnect from all open connections?", QMessageBox::Yes, QMessageBox::No) != QMessageBox::Yes)
			return;

	// iterate through all connections and close them
	for (int i = 0, count = m_lConnections.count(); i < count; i++)
	{
		ODBC_Connection *pConnection = m_lConnections.value(i);
		if (pConnection != NULL)
		{
			QString sConnectionName = pConnection->getConnectionName();
			Logging::getInstance()->WriteLog(INFORMATION, QString("Attempting to close \"%1\"...").arg(sConnectionName));
			pConnection->CloseConnection();
			delete pConnection;
			pConnection = NULL;
			Logging::getInstance()->WriteLog(INFORMATION, QString("Connection \"%1\" closed").arg(sConnectionName));
		}
		else
		{
			Logging::getInstance()->WriteLog(CRITICAL, QString("Null pointer at CloseAllConnections() in m_lConnections at i = %1").arg(QString().setNum(i)));
			#ifdef _DEBUG
			qDebug() << QString("Null pointer at CloseAllConnections() in m_lConnections at i = %1").arg(QString().setNum(i));
			#endif
		}
	}
	m_lConnections.clear();
	m_pCurrentConnection = NULL;
	
	ResetGui();

	Logging::getInstance()->WriteLog(INFORMATION, "Closed all connections");
}

void ODBC_Query::ConnectionsClicked(QAction *action)
{
	setCursor(Qt::WaitCursor);
	QApplication::processEvents();
	
	QMenu *pMenu = (QMenu*)action->parentWidget();
	if (pMenu != NULL)
	{
		QString command = action->text();
		if (command == "Select")
		{
			QString sNewConnectionName = pMenu->title();
			if (m_pCurrentConnection != NULL)
				Logging::getInstance()->WriteLog(INFORMATION, QString("Switching to connection \"%1\" (current connection: \"%2\")...").arg(sNewConnectionName, m_pCurrentConnection->getConnectionName()));
			else
				Logging::getInstance()->WriteLog(INFORMATION, QString("Switching to connection \"%1\"...").arg(sNewConnectionName));
			for (int i = 0, count = m_lConnections.count(); i < count; i++)
			{
				ODBC_Connection *pConnection = m_lConnections.value(i);
				if (pConnection != NULL)
				{
					QString sOldConnectionName = pConnection->getConnectionName();
					if (sOldConnectionName != sNewConnectionName)
						continue;

					if (m_pCurrentConnection != NULL)
					{
						if (m_pCurrentConnection->getConnectionName() != sOldConnectionName)
						{
							m_pCurrentConnection->CloseConnection();
							m_pCurrentConnection = pConnection;
							m_pCurrentConnection->OpenConnection(sNewConnectionName);
							m_pCurrentConnection->ConnectToDatabase(true);
							QAction *pAction;
							QList<QAction*> lActions = ui.OpenConnectionsMenu->actions();
							for (int j = 0, count = lActions.count(); j < count; j++)
							{	
								pAction = lActions.value(j);
								if (pAction != NULL)
								{
									if (pAction->text() != sNewConnectionName)
										pAction->setChecked(false);
									else
										pAction->setChecked(true);
								}
								else
								{
									Logging::getInstance()->WriteLog(CRITICAL, QString("Null pointer at ConnectionsClicked() in lActions at j = %1, count = %2").arg(QString().setNum(j), QString().setNum(count)));
									#ifdef _DEBUG
									qDebug() << QString("Null pointer at ConnectionsClicked() in lActions at j = %1, count = %2").arg(QString().setNum(j), QString().setNum(count));
									#endif
								}

							}
						}
					}
					else
					{
						m_pCurrentConnection = pConnection;
						m_pCurrentConnection->OpenConnection(sNewConnectionName);
						m_pCurrentConnection->ConnectToDatabase(true);
						QAction *pAction2;
						QList<QAction*> lActions2 = ui.OpenConnectionsMenu->actions();
						for (int k = 0, count = lActions2.count(); k < count; k++)
						{	
							pAction2 = lActions2.value(k);
							if (pAction2 != NULL)
							{
								if (pAction2->text() != sNewConnectionName)
									pAction2->setChecked(false);
								else
									pAction2->setChecked(true);
							}
							else
							{
								Logging::getInstance()->WriteLog(CRITICAL, QString("Null pointer at ConnectionsClicked() in lActions2 at k = %1, count = %2").arg(QString().setNum(k), QString().setNum(count)));
								#ifdef _DEBUG
								qDebug() << QString("Null pointer at ConnectionsClicked() in lActions2 at k = %1, count = %2").arg(QString().setNum(k), QString().setNum(count));
								#endif
							}
						}
					}
					if (m_pCurrentConnection != NULL)
						Logging::getInstance()->WriteLog(INFORMATION, QString("Switched connection, current connection \"%1\"").arg(m_pCurrentConnection->getConnectionName()));
				}
			}
		}
		else if (command == "Disconnect")
		{
			QString sConnectionNameToClose = pMenu->title();
			Logging::getInstance()->WriteLog(INFORMATION, QString("Attempting to close \"%1\"...").arg(sConnectionNameToClose));
			QAction *pAction;
			QList<QAction*> lActions = ui.OpenConnectionsMenu->actions();
			for (int i = 0, count = lActions.count(); i < count; i++)
			{
				pAction = lActions.value(i);
				if (pAction != NULL)
				{
					if (pAction->text() == sConnectionNameToClose)
						break;
				}
				else
				{
					Logging::getInstance()->WriteLog(CRITICAL, QString("Null pointer at ConnectionsClicked() in lActions at i = %1, count = %2").arg(QString().setNum(i), QString().setNum(count)));
					#ifdef _DEBUG
					qDebug() << QString("Null pointer at ConnectionsClicked() in lActions at i = %1, count = %2").arg(QString().setNum(i), QString().setNum(count));
					#endif
				}

			}

			bool foundConnection = false;
			if (m_pCurrentConnection != NULL)
			{
				if (m_pCurrentConnection->getConnectionName() == sConnectionNameToClose) // is it the current connection we need to close?
				{
					m_lConnections.removeOne(m_pCurrentConnection);
					ui.OpenConnectionsMenu->removeAction(action);
					m_pCurrentConnection->CloseConnection();
					delete m_pCurrentConnection;
					m_pCurrentConnection = NULL;
					Logging::getInstance()->WriteLog(INFORMATION, QString("Connection \"%1\" closed").arg(sConnectionNameToClose));
					ResetGui();
					foundConnection = true;
				}
			}
			else
			{
				Logging::getInstance()->WriteLog(WARNING, "Null pointer at ConnectionsClicked() in m_pCurrentConnection");
				#ifdef _DEBUG
				qDebug() << "Null pointer at ConnectionsClicked() in m_pCurrentConnection";
				#endif
			}

			if (!foundConnection)
			{
				// nope, we have to iterate through all connections
				for (int i = 0, count = m_lConnections.count(); i < count; i++)
				{
					ODBC_Connection *pConnection = m_lConnections.value(i);
					if (pConnection != NULL)
					{
						QString CurrentConnectionName = pConnection->getConnectionName();
						if (CurrentConnectionName != sConnectionNameToClose)
							continue;

						m_lConnections.removeAt(i);
						ui.OpenConnectionsMenu->removeAction(action);
						pConnection->CloseConnection();
						delete pConnection;
						pConnection = NULL;
						Logging::getInstance()->WriteLog(INFORMATION, QString("Connection %1 closed").arg(sConnectionNameToClose));
					}
					else
					{
						Logging::getInstance()->WriteLog(CRITICAL, QString("Null pointer at ConnectionsClicked() in m_lConnections at i = %1").arg(QString().setNum(i)));
						#ifdef _DEBUG
						qDebug() << QString("Null pointer at ConnectionsClicked() in m_lConnections at i = %1").arg(QString().setNum(i));
						#endif
					}
				}
			}

			if (ui.OpenConnectionsMenu->actions().count() == 0)
				ui.OpenConnectionsMenu->setDisabled(true);
		}
	}
	else
	{
		Logging::getInstance()->WriteLog(CRITICAL, "Null pointer at ConnectionsClicked() in pMenu");
		#ifdef _DEBUG
		qDebug() << "Null pointer at ConnectionsClicked() in pMenu";
		#endif
	}
	setCursor(Qt::ArrowCursor);
}

void ODBC_Query::SQLCommandTextChanged()
{
	if (m_pCurrentConnection != NULL)
		m_pCurrentConnection->HandleSQLCommandTextChanged();
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
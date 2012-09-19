#include "precompiled.h"
#include "ODBC_Query.h"
#include "ODBC_Connection.h"
#include "ODBC_ConnectionDialog.h"
#include "ODBC_OptionsDialog.h"

ODBC_Query::ODBC_Query(QWidget *parent, Qt::WFlags flags) : QMainWindow(parent, flags)
{
	ui.setupUi(this);

	QCoreApplication::setApplicationName(APPLICATION_NAME);

	// initialize the logging
	QLogging::getInstance()->Init();
	QLogging::getInstance()->WriteLog(INFORMATION, QString("Starting %1 (PID: %2)...").arg(QCoreApplication::applicationName(), QString().setNum(QCoreApplication::applicationPid())));
	
	InitGui();

	m_pCurrentConnection = NULL;
}

ODBC_Query::~ODBC_Query()
{
	ODBC_OptionsDialog::getInstance()->ExitInstance();

	QLogging::getInstance()->WriteLog(INFORMATION, QString("Closing %1...").arg(QCoreApplication::applicationName()));

	CloseAllConnections(true);

	m_pCurrentConnection = NULL;

	QLogging::getInstance()->WriteLog(INFORMATION, QString("Shutting down %1").arg(QCoreApplication::applicationName()));
	QLogging::getInstance()->Close();
	QLogging::getInstance()->ExitInstance();
}

void ODBC_Query::InitGui()
{
	QLogging::getInstance()->WriteLog(INFORMATION, "Initializing gui...");

	// set the default sizes of the splitter
	QList<int> list;
	list << 1000 << 26 << 200 << 200;
	ui.VerticalSplitter->setSizes(list);
	list.clear();
	list << 250 << 1000;
	ui.MainHorizontalSplitter->setSizes(list);

	// setup gui
	ui.StatusBar->addPermanentWidget(ui.StatusLabel, -1);
	ui.ToolBar->addWidget(ui.AddConnectionToolButton);
	ui.ToolBar->addWidget(ui.OpenConnectionsToolButton);
	ui.OpenConnectionsToolButton->setMenu(ui.OpenConnectionsMenu);
	ui.ToolBar->addWidget(ui.CloseAllConnectionsToolButton);
	m_pLoadingAnimation = new QMovie(":/ODBC_Query/Resources/loading.gif");
	m_pLoadingLabel = new QLabel(this);
	m_pLoadingLabel->setMovie(m_pLoadingAnimation);
	ui.StatusBar->addPermanentWidget(m_pLoadingLabel);
	m_pLoadingLabel->setHidden(true);
	ui.TableTreeWidget->setHeaderLabel("Tables");

	installEventFilter(this);

	// init the syntax highlighter
	m_pHighlighter = new ODBC_CustomSyntaxHighlighter(ui.SQLCommandTextEdit->document());
	m_pHighlighter->Init();

	// connect gui signals to slots
	QObject::connect(ui.ExecuteToolButton, SIGNAL(clicked()), SLOT(ExecuteButtonClicked()));
	QObject::connect(ui.LeftToolButton, SIGNAL(clicked()), SLOT(LeftButtonClicked()));
	QObject::connect(ui.RightToolButton, SIGNAL(clicked()), SLOT(RightButtonClicked()));
	QObject::connect(ui.TableTreeWidget, SIGNAL(itemExpanded(QTreeWidgetItem*)), SLOT(TableItemExpanded(QTreeWidgetItem*)));
	QObject::connect(ui.ExitAction, SIGNAL(triggered()), SLOT(Exit()));
	QObject::connect(ui.NewConnectionAction, SIGNAL(triggered()), SLOT(NewConnection()));
	QObject::connect(ui.AddConnectionToolButton, SIGNAL(clicked()), SLOT(NewConnection()));
	QObject::connect(ui.CloseAllConnectionsAction, SIGNAL(triggered()), SLOT(CloseAllConnections()));
	QObject::connect(ui.CloseAllConnectionsToolButton, SIGNAL(clicked()), SLOT(CloseAllConnections()));
	QObject::connect(ui.ShowToolbarAction, SIGNAL(triggered()), SLOT(ShowToolbarTriggered()));
	QObject::connect(ui.SyntaxHighlightingAction, SIGNAL(triggered()), SLOT(SyntaxHighlightingTriggered()));
	QObject::connect(ui.SQLCommandTextEdit, SIGNAL(textChanged()), SLOT(SQLCommandTextChanged()));
	QObject::connect(ui.OptionsAction, SIGNAL(triggered()), SLOT(ShowOptions()));
	QObject::connect(ui.AboutAction, SIGNAL(triggered()), SLOT(ShowAbout()));

	// initialize options menu
	ODBC_OptionsDialog::getInstance()->Init();

	QLogging::getInstance()->WriteLog(INFORMATION, "Gui initialized");
}

void ODBC_Query::ResetGui()
{
	ui.TableTreeWidget->clear();
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

	QLogging::getInstance()->WriteLog(INFORMATION, "Gui resetted");
}

void ODBC_Query::DisableQueryToolbar()
{
	if (ui.ExecuteToolButton->isEnabled())
		ui.ExecuteToolButton->setDisabled(true);

	if (ui.CurrentStatementLabel->isEnabled())
		ui.CurrentStatementLabel->setDisabled(true);

	if (ui.RightToolButton->isEnabled())
		ui.RightToolButton->setDisabled(true);

	if (ui.LeftToolButton->isEnabled())
		ui.LeftToolButton->setDisabled(true);
}

bool ODBC_Query::SwitchToConnection(ODBC_Connection *connection, QString newConnectionName)
{
	if (connection == NULL)
	{
		QLogging::getInstance()->WriteLog(CRITICAL, "Null pointer at SwitchToConnection() in connection");
		#ifdef _DEBUG
		qDebug() << "Null pointer at SwitchToConnection() in connection";
		#endif
		return false;
	}

	m_pCurrentConnection = connection;
	m_pCurrentConnection->RestoreGui();
	
	QAction *pAction;
	QList<QAction*> lActions = ui.OpenConnectionsMenu->actions();
	for (int i = 0, count = lActions.count(); i < count; i++)
	{	
		pAction = lActions.value(i);
		if (pAction != NULL)
		{
			if (pAction->text() != newConnectionName)
				pAction->setChecked(false);
			else
				pAction->setChecked(true);
		}
		else
		{
			QLogging::getInstance()->WriteLog(CRITICAL, QString("Null pointer at SwitchToConnection() in lActions at i = %1, count = %2").arg(QString().setNum(i), QString().setNum(count)));
			#ifdef _DEBUG
			qDebug() << QString("Null pointer at SwitchToConnection() in lActions at i = %1, count = %2").arg(QString().setNum(i), QString().setNum(count));
			#endif
		}
	}
	return true;
}

// <SLOTS>
void ODBC_Query::ExecuteButtonClicked()
{
	if (!ui.ExecuteToolButton->isEnabled())
		return;

	if (m_pCurrentConnection != NULL)
	{
		QString sQuery = ui.SQLCommandTextEdit->toPlainText();
		if (!m_pCurrentConnection->IsConnectionOpen())
		{
			QString sConnectionName = m_pCurrentConnection->GetConnectionName();
			QLogging::getInstance()->WriteLog(ERROR, QString("Couldn't execute statement \"%1\" of connection \"%2\", connection isn't open").arg(sQuery, sConnectionName));
			#ifdef _DEBUG
			qDebug() << QString("Couldn't execute statement \"%1\" of connection \"%2\", connection isn't open").arg(sQuery, sConnectionName);
			#endif
			return;
		}
		QStringList lQueries = sQuery.split(';');
		// send the signal to the execute thread
		for (int i = 0, count = lQueries.count(); i < count; i++)
		{
			QString sNewQuery = lQueries.value(i);
			if (!sNewQuery.isEmpty())
				emit ExecuteQuery(sNewQuery);
		}

		// disable execute button and start the loading animation
		ui.ExecuteToolButton->setDisabled(true);
		m_pLoadingLabel->setHidden(false);
		m_pLoadingAnimation->start();
	}
	else
	{
		QLogging::getInstance()->WriteLog(WARNING, "Null pointer at ExecuteButtonClicked() in m_pCurrentConnection");
		#ifdef _DEBUG
		qDebug() << "Null pointer at ExecuteButtonClicked() in m_pCurrentConnection";
		#endif
	}
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

void ODBC_Query::TableItemExpanded(QTreeWidgetItem* item)
{
	if (m_pCurrentConnection != NULL)
	{
		if (item == NULL)
			return;

		if (item->childCount() > 0)
			return;

		m_pCurrentConnection->LoadTableColumns(item);
	}
}

void ODBC_Query::Exit()
{
	QApplication::exit();
}

void ODBC_Query::NewConnection()
{
	QLogging::getInstance()->WriteLog(INFORMATION, "Opening new connection...");
	ODBC_ConnectionDialog ConnectionDialog;
	ConnectionDialog.Init();
	while (!ConnectionDialog.IsClosed())
	{
		ConnectionDialog.Reset();
		ConnectionDialog.exec();
		if (!ConnectionDialog.IsValid())
			return;

		QString sDatabase = ConnectionDialog.GetDatabase();

		// set wait cursor
		QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
		QApplication::processEvents();
		QString sNewConnectionName = QString("%1 (%2)").arg(sDatabase, ConnectionDialog.IsSystemDSN() ? "System" : "User");
		// check whether we already have a connection with that name and switch to it if yes
		for (int i = 0, count = m_lConnections.count(); i < count; i++)
		{
			ODBC_Connection *pConnection = m_lConnections.value(i);
			if (pConnection != NULL)
			{
				if (pConnection->GetConnectionName() == sNewConnectionName)
				{
					if (m_pCurrentConnection != NULL)
						m_pCurrentConnection->RestoreGui();
					SwitchToConnection(pConnection, sNewConnectionName);
					QApplication::restoreOverrideCursor();
					return;
				}
			}
		}

		QLogging::getInstance()->WriteLog(INFORMATION, QString("Connecting to \"%1\"").arg(sNewConnectionName));

		// close the current connection (if there is one)
		if (m_pCurrentConnection != NULL)
			m_pCurrentConnection->SaveGui();
		m_pCurrentConnection = NULL;
		QThread *pThread = new QThread(this);
		// make a new connection
		m_pCurrentConnection = new ODBC_Connection(ui, pThread);
		QObject::connect(this, SIGNAL(ExecuteQuery(QString)), m_pCurrentConnection, SLOT(ExecuteQuery(QString)));
		QObject::connect(m_pCurrentConnection, SIGNAL(Executed()), this, SLOT(Executed()));
		m_pCurrentConnection->moveToThread(pThread);
		pThread->start();
		m_pCurrentConnection->OpenConnection(sNewConnectionName);
		ResetGui();
		// and connect to the dsn
		if (m_pCurrentConnection->ConnectToDatabase(sDatabase, ConnectionDialog.GetUsername(), ConnectionDialog.GetPassword()))
		{
			m_lConnections.append(m_pCurrentConnection);
			QObject::connect(m_pCurrentConnection, SIGNAL(finished()), SLOT(Executed()));
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
			QList<QAction*> lActions = ui.OpenConnectionsMenu->actions();
			for (int i = 0, count = lActions.count(); i < count; i++)
			{
				pAction = lActions.value(i);
				if (pAction != NULL)
				{
					if (pAction->text() != sNewConnectionName)
						pAction->setChecked(false);
				}
				else
				{
					QLogging::getInstance()->WriteLog(CRITICAL, QString("Null pointer at NewConnection() in lActions at i = %1, count = %2").arg(QString().setNum(i), QString().setNum(count)));
					#ifdef _DEBUG
					qDebug() << QString("Null pointer at NewConnection() in lActions at i = %1, count = %2").arg(QString().setNum(i), QString().setNum(count));
					#endif
				}
			}
			if (!ui.OpenConnectionsMenu->isEnabled())
				ui.OpenConnectionsMenu->setEnabled(true);

			if (!ui.OpenConnectionsToolButton->isEnabled())
				ui.OpenConnectionsToolButton->setEnabled(true);

			if (!ui.CloseAllConnectionsAction->isEnabled())
				ui.CloseAllConnectionsAction->setEnabled(true);

			if (!ui.CloseAllConnectionsToolButton->isEnabled())
				ui.CloseAllConnectionsToolButton->setEnabled(true);

			// set back to arrow cursor
			QApplication::restoreOverrideCursor();
			break;
		}
		else
		{
			// set back to arrow cursor
			QApplication::restoreOverrideCursor();
			QMessageBox::critical(this, "Error", m_pCurrentConnection->GetDatabaseError(), QMessageBox::Ok);
			// delete the error connection
			m_pCurrentConnection->CloseConnection();
			delete m_pCurrentConnection;
			m_pCurrentConnection = NULL;
		}
		// set back to arrow cursor
		QApplication::restoreOverrideCursor();
	}
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
			QString sConnectionName = pConnection->GetConnectionName();
			QLogging::getInstance()->WriteLog(INFORMATION, QString("Attempting to close \"%1\"...").arg(sConnectionName));
			pConnection->CloseConnection();
			delete pConnection;
			pConnection = NULL;
			QLogging::getInstance()->WriteLog(INFORMATION, QString("Connection \"%1\" closed").arg(sConnectionName));
		}
		else
		{
			QLogging::getInstance()->WriteLog(CRITICAL, QString("Null pointer at CloseAllConnections() in m_lConnections at i = %1, count = %2").arg(QString().setNum(i), QString().setNum(count)));
			#ifdef _DEBUG
			qDebug() << QString("Null pointer at CloseAllConnections() in m_lConnections at i = %1, count = %2").arg(QString().setNum(i), QString().setNum(count));
			#endif
		}
	}
	m_lConnections.clear();
	m_pCurrentConnection = NULL;
	
	ResetGui();

	QLogging::getInstance()->WriteLog(INFORMATION, "Closed all connections");
}

void ODBC_Query::ConnectionsClicked(QAction *action)
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	QApplication::processEvents();
	
	QMenu *pMenu = (QMenu*)action->parentWidget();
	if (pMenu != NULL)
	{
		QString command = action->text();
		if (command == "Select")
		{
			QString sNewConnectionName = pMenu->title();
			if (m_pCurrentConnection != NULL)
				QLogging::getInstance()->WriteLog(INFORMATION, QString("Switching to connection \"%1\" (current connection: \"%2\")...").arg(sNewConnectionName, m_pCurrentConnection->GetConnectionName()));
			else
				QLogging::getInstance()->WriteLog(INFORMATION, QString("Switching to connection \"%1\"...").arg(sNewConnectionName));
			for (int i = 0, count = m_lConnections.count(); i < count; i++)
			{
				ODBC_Connection *pConnection = m_lConnections.value(i);
				if (pConnection != NULL)
				{
					QString sOldConnectionName = pConnection->GetConnectionName();
					if (sOldConnectionName != sNewConnectionName)
						continue;

					if (m_pCurrentConnection != NULL)
					{
						if (m_pCurrentConnection->GetConnectionName() != sOldConnectionName)
						{
							m_pCurrentConnection->SaveGui();
							if (!SwitchToConnection(pConnection, sNewConnectionName))
								return;
						}
					}
					else
						if (!SwitchToConnection(pConnection, sNewConnectionName))
							return;
					if (m_pCurrentConnection != NULL)
						QLogging::getInstance()->WriteLog(INFORMATION, QString("Switched connection, current connection \"%1\"").arg(m_pCurrentConnection->GetConnectionName()));
				}
			}
		}
		else if (command == "Disconnect")
		{
			QString sConnectionNameToClose = pMenu->title();
			QLogging::getInstance()->WriteLog(INFORMATION, QString("Attempting to close \"%1\"...").arg(sConnectionNameToClose));
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
					QLogging::getInstance()->WriteLog(CRITICAL, QString("Null pointer at ConnectionsClicked() in lActions at i = %1, count = %2").arg(QString().setNum(i), QString().setNum(count)));
					#ifdef _DEBUG
					qDebug() << QString("Null pointer at ConnectionsClicked() in lActions at i = %1, count = %2").arg(QString().setNum(i), QString().setNum(count));
					#endif
				}

			}

			bool bCurrentConnection = false;
			if (m_pCurrentConnection != NULL)
			{
				if (m_pCurrentConnection->GetConnectionName() == sConnectionNameToClose) // is it the current connection we need to close?
				{
					m_lConnections.removeOne(m_pCurrentConnection);
					ui.OpenConnectionsMenu->removeAction(pAction);
					m_pCurrentConnection->CloseConnection();
					delete m_pCurrentConnection;
					m_pCurrentConnection = NULL;
					QLogging::getInstance()->WriteLog(INFORMATION, QString("Connection \"%1\" closed, it was the current connection").arg(sConnectionNameToClose));
					ResetGui();
					bCurrentConnection = true;
				}
			}
			else
			{
				QLogging::getInstance()->WriteLog(WARNING, "Null pointer at ConnectionsClicked() in m_pCurrentConnection");
				#ifdef _DEBUG
				qDebug() << "Null pointer at ConnectionsClicked() in m_pCurrentConnection";
				#endif
			}

			if (!bCurrentConnection)
			{
				// nope, we have to iterate through all connections
				for (int i = 0, count = m_lConnections.count(); i < count; i++)
				{
					ODBC_Connection *pConnection = m_lConnections.value(i);
					if (pConnection != NULL)
					{
						QString CurrentConnectionName = pConnection->GetConnectionName();
						if (CurrentConnectionName != sConnectionNameToClose)
							continue;

						m_lConnections.removeAt(i);
						ui.OpenConnectionsMenu->removeAction(pAction);
						pConnection->CloseConnection();
						delete pConnection;
						pConnection = NULL;
						QLogging::getInstance()->WriteLog(INFORMATION, QString("Connection %1 closed, it wasn't the current connection").arg(sConnectionNameToClose));
					}
					else
					{
						QLogging::getInstance()->WriteLog(CRITICAL, QString("Null pointer at ConnectionsClicked() in m_lConnections at i = %1, count = %2").arg(QString().setNum(i), QString().setNum(count)));
						#ifdef _DEBUG
						qDebug() << QString("Null pointer at ConnectionsClicked() in m_lConnections at i = %1, count = %2").arg(QString().setNum(i), QString().setNum(count));
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
		QLogging::getInstance()->WriteLog(CRITICAL, "Null pointer at ConnectionsClicked() in pMenu");
		#ifdef _DEBUG
		qDebug() << "Null pointer at ConnectionsClicked() in pMenu";
		#endif
	}
	QApplication::restoreOverrideCursor();
}

void ODBC_Query::ShowToolbarTriggered()
{
	// toggle toolbar
	if (ui.ToolBar->isHidden())
		ui.ToolBar->setHidden(false);
	else
		ui.ToolBar->setHidden(true);
}

void ODBC_Query::SyntaxHighlightingTriggered()
{
	// toggle syntax highlighter
	if (m_pHighlighter->IsActive())
	{
		m_pHighlighter->SetActive(false);
		ui.SQLCommandTextEdit->setText(ui.SQLCommandTextEdit->toPlainText());
	}
	else
	{
		m_pHighlighter->SetActive(true);
		ui.SQLCommandTextEdit->setText(ui.SQLCommandTextEdit->toPlainText());
	}
}

void ODBC_Query::SQLCommandTextChanged()
{
	if (m_pCurrentConnection != NULL)
		m_pCurrentConnection->HandleSQLCommandTextChanged();
}

void ODBC_Query::Executed()
{
	if (m_pCurrentConnection != NULL)
	{	
		// get the model
		QAbstractItemModel *pModel = m_pCurrentConnection->GetSQLResultTable();
		if (pModel != NULL)
		{
			// and bind it to the tableview
			ui.SQLResultTableView->setModel(pModel);
			ui.SQLResultTableView->sortByColumn(-1, Qt::AscendingOrder);
			ui.SQLResultTableView->verticalScrollBar()->setSliderPosition(ui.SQLResultTableView->verticalScrollBar()->minimum());
			ui.SQLResultTableView->horizontalScrollBar()->setSliderPosition(ui.SQLResultTableView->horizontalScrollBar()->minimum());
		}

		// update log text and the query toolbar
		ui.SQLLogTextBrowser->append(m_pCurrentConnection->GetLogText());
		int iCurIndex = m_pCurrentConnection->GetCurrentHistoryIndex();
		if (iCurIndex > 0 && !ui.LeftToolButton->isEnabled())
			ui.LeftToolButton->setEnabled(true);
		if (!ui.RightToolButton->isEnabled())
			ui.RightToolButton->setEnabled(true);
		if (!ui.CurrentStatementLabel->isEnabled())
			ui.CurrentStatementLabel->setEnabled(true);	
		ui.CurrentStatementLabel->setText(QString().setNum(iCurIndex + 1));
	}

	// restore the gui state and stop the loading animation
	ui.ExecuteToolButton->setEnabled(true);
	m_pLoadingAnimation->stop();
	m_pLoadingLabel->setHidden(true);
}

void ODBC_Query::ShowOptions()
{
	ODBC_OptionsDialog::getInstance()->exec();
}

void ODBC_Query::ShowAbout()
{
	QMessageBox::about(this, QString("About %1").arg(APPLICATION_NAME), QString("<b>ODBC Query (build: %1)</b><br/><br/>written by Daniel Rosenauer<br/><br/>mail: <a href='mailto:d.rosenauer@googlemail.com'>d.rosenauer@gmail.com</a><br/>github: <a href='https://github.com/Edder/odbc-query'>project page</a><br/><br/>linked against Qt %2").arg(QString().setNum(REVISION), QT_VERSION_STR));
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
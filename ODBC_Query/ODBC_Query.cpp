#include "precompiled.h"
#include "ODBC_Query.h"

ODBC_Query::ODBC_Query(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags)
{
	ui.setupUi(this);

	QCoreApplication::setApplicationName(APPLICATION_NAME);

	// initialize the logging
	Logging::getInstance()->Init();
	Logging::getInstance()->WriteLog(INFORMATION, QString("Starting %1 (PID: %2)...").arg(QCoreApplication::applicationName(), QString().setNum(QCoreApplication::applicationPid())));
	
	InitGui();

	m_pCurrentConnection = NULL;
}

ODBC_Query::~ODBC_Query()
{
	ODBC_OptionsDialog::getInstance()->ExitInstance();

	Logging::getInstance()->WriteLog(INFORMATION, QString("Closing %1...").arg(QCoreApplication::applicationName()));

	CleanResultWindows();

	CloseAllConnections(true);

	if (m_pHighlighter != NULL)
	{
		delete m_pHighlighter;
		m_pHighlighter = NULL;
	}

	Logging::getInstance()->WriteLog(INFORMATION, QString("Shutting down %1").arg(QCoreApplication::applicationName()));
	Logging::getInstance()->Close();
	Logging::getInstance()->ExitInstance();
}

void ODBC_Query::InitGui()
{
	Logging::getInstance()->WriteLog(INFORMATION, "Initializing gui...");

	// set the default sizes of the splitter
	QList<int> list;
	list << 10 << 1000 << 26 << 200 << 200;
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
	ui.ToolBar->addWidget(ui.RefreshTablesToolButton);
	m_pLoadingAnimation = new QMovie(this);
	m_pLoadingAnimation->setFileName(":/ODBC_Query/Resources/loading.gif");
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
	QObject::connect(ui.RefreshTablesAction, SIGNAL(triggered()), SLOT(RefreshTables()));
	QObject::connect(ui.RefreshTablesToolButton, SIGNAL(clicked()), SLOT(RefreshTables()));
	QObject::connect(ui.ShowToolbarAction, SIGNAL(triggered()), SLOT(ShowToolbarTriggered()));
	QObject::connect(ui.SyntaxHighlightingAction, SIGNAL(triggered()), SLOT(SyntaxHighlightingTriggered()));
	QObject::connect(ui.SQLCommandTextEdit, SIGNAL(textChanged()), SLOT(SQLCommandTextChanged()));
	QObject::connect(ui.OptionsAction, SIGNAL(triggered()), SLOT(ShowOptions()));
	QObject::connect(ui.AboutAction, SIGNAL(triggered()), SLOT(ShowAbout()));
	QObject::connect(ui.ExtractToolButton, SIGNAL(clicked()), SLOT(ExtractResult()));

	// initialize options menu
	ODBC_OptionsDialog::getInstance()->Init();

	Logging::getInstance()->WriteLog(INFORMATION, "Gui initialized");
}

void ODBC_Query::ResetGui()
{
	ui.TableTreeWidget->clear();
	ui.SQLCommandTextEdit->clear();
	ui.SQLLogTextBrowser->clear();
	ui.CurrentStatementLabel->setText("1");
	ui.ResultCountLabel->setText("Rows:");
	ui.StatusLabel->clear();
	ui.SQLResultTableView->setModel(NULL);

	if (m_lConnections.count() == 0)
	{
		ui.OpenConnectionsMenu->clear();
		ui.OpenConnectionsMenu->setDisabled(true);
		ui.OpenConnectionsToolButton->setDisabled(true);
		ui.CloseAllConnectionsAction->setDisabled(true);
		ui.CloseAllConnectionsToolButton->setDisabled(true);
		ui.RefreshTablesAction->setDisabled(true);
		ui.RefreshTablesToolButton->setDisabled(true);
	}
	DisableQueryToolbar();

	Logging::getInstance()->WriteLog(INFORMATION, "Gui resetted");
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

	if (ui.ExtractToolButton->isEnabled())
		ui.ExtractToolButton->setDisabled(true);
}

bool ODBC_Query::SwitchToConnection(ODBC_Connection *connection, QString newConnectionName)
{
	if (connection == NULL)
	{
		Logging::getInstance()->WriteLog(CRITICAL, "Null pointer at SwitchToConnection() in connection");
		#ifdef _DEBUG
		qDebug() << "Null pointer at SwitchToConnection() in connection";
		#endif
		return false;
	}

	DisconnectConnectionSlots();

	m_pCurrentConnection = connection;
	m_pCurrentConnection->RestoreGui();

	ConnectConnectionSlots();
	
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
			Logging::getInstance()->WriteLog(CRITICAL, QString("Null pointer at SwitchToConnection() in lActions at i = %1, count = %2").arg(QString().setNum(i), QString().setNum(count)));
			#ifdef _DEBUG
			qDebug() << QString("Null pointer at SwitchToConnection() in lActions at i = %1, count = %2").arg(QString().setNum(i), QString().setNum(count));
			#endif
		}
	}
	return true;
}

void ODBC_Query::CleanResultWindows()
{
	for (int i = 0; i < m_lResultWindows.count(); i++)
	{
		ODBC_ResultWindow* pResultWindow = NULL;
		pResultWindow = m_lResultWindows.at(i);
			
		if (pResultWindow != NULL)
		{
			if (!pResultWindow->isVisible())
			{
				pResultWindow->GetModel()->SetExtracted(false);
				pResultWindow->Clean();
				delete pResultWindow;
				pResultWindow = NULL;

				m_lResultWindows.removeAt(i);
				i--;
			}
		}
	}
}

void ODBC_Query::closeEvent(QCloseEvent *event)
{
	Exit();
}

void ODBC_Query::ConnectConnectionSlots()
{
	// (re)connect all slots to current connection
	QObject::connect(this, SIGNAL(ExecuteQuery(QString)), m_pCurrentConnection, SLOT(ExecuteQuery(QString)));
	QObject::connect(m_pCurrentConnection, SIGNAL(Executed()), this, SLOT(Executed()));
	QObject::connect(m_pCurrentConnection, SIGNAL(LimitReached()), this, SLOT(LimitReached()));
}

void ODBC_Query::DisconnectConnectionSlots()
{
	// disconnect all slots from current connection
	QObject::disconnect(this, SIGNAL(ExecuteQuery(QString)), m_pCurrentConnection, SLOT(ExecuteQuery(QString)));
	QObject::disconnect(m_pCurrentConnection, SIGNAL(Executed()), this, SLOT(Executed()));
	QObject::disconnect(m_pCurrentConnection, SIGNAL(LimitReached()), this, SLOT(LimitReached()));
}

// <SLOTS>
void ODBC_Query::ExecuteButtonClicked()
{
	if (!ui.ExecuteToolButton->isEnabled())
		return;

	if (!m_pLoadingLabel->isHidden()) // label is hidden, currently execution takes place
	{
		m_pCurrentConnection->StopExecution();
		return;
	}

	if (m_pCurrentConnection != NULL)
	{
		QString sQuery = ui.SQLCommandTextEdit->toPlainText();
		if (!m_pCurrentConnection->IsConnectionOpen())
		{
			QString sConnectionName = m_pCurrentConnection->GetConnectionName();
			Logging::getInstance()->WriteLog(ERR, QString("Couldn't execute statement \"%1\" of connection \"%2\", connection isn't open").arg(sQuery, sConnectionName));
			#ifdef _DEBUG
			qDebug() << QString("Couldn't execute statement \"%1\" of connection \"%2\", connection isn't open").arg(sQuery, sConnectionName);
			#endif
			return;
		}

		if (!sQuery.isEmpty())
			emit ExecuteQuery(sQuery);

		// change execute button icon and start the loading animation
		ui.ExecuteToolButton->setIcon(QIcon(":/ODBC_Query/Resources/stop_icon.png"));
		m_pLoadingLabel->setHidden(false);
		m_pLoadingAnimation->start();
	}
	else
	{
		Logging::getInstance()->WriteLog(WARNING, "Null pointer at ExecuteButtonClicked() in m_pCurrentConnection");
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
	Logging::getInstance()->WriteLog(INFORMATION, "Opening new connection...");
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

		Logging::getInstance()->WriteLog(INFORMATION, QString("Connecting to \"%1\"").arg(sNewConnectionName));

		// close the current connection (if there is one)
		if (m_pCurrentConnection != NULL)
		{
			m_pCurrentConnection->SaveGui();
			DisconnectConnectionSlots();
		}
		m_pCurrentConnection = NULL;
		QThread *pThread = new QThread(this);
		// make a new connection
		m_pCurrentConnection = new ODBC_Connection(ui, pThread);
		ConnectConnectionSlots();
		m_pCurrentConnection->moveToThread(pThread);
		pThread->start();
		m_pCurrentConnection->OpenConnection(sNewConnectionName);
		ResetGui();
		// and connect to the dsn
		if (m_pCurrentConnection->ConnectToDatabase(sDatabase, ConnectionDialog.GetUsername(), ConnectionDialog.GetPassword()))
		{
			m_lConnections.append(m_pCurrentConnection);
			
			// dont know why I added this
			//QObject::connect(m_pCurrentConnection, SIGNAL(finished()), SLOT(Executed()));

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
					Logging::getInstance()->WriteLog(CRITICAL, QString("Null pointer at NewConnection() in lActions at i = %1, count = %2").arg(QString().setNum(i), QString().setNum(count)));
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
			
			if (!ui.RefreshTablesAction->isEnabled())
				ui.RefreshTablesAction->setEnabled(true);

			if (!ui.RefreshTablesToolButton->isEnabled())
				ui.RefreshTablesToolButton->setEnabled(true);

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
			Logging::getInstance()->WriteLog(INFORMATION, QString("Attempting to close \"%1\"...").arg(sConnectionName));
			pConnection->CloseConnection();
			delete pConnection;
			pConnection = NULL;
			Logging::getInstance()->WriteLog(INFORMATION, QString("Connection \"%1\" closed").arg(sConnectionName));
		}
		else
		{
			Logging::getInstance()->WriteLog(CRITICAL, QString("Null pointer at CloseAllConnections() in m_lConnections at i = %1, count = %2").arg(QString().setNum(i), QString().setNum(count)));
			#ifdef _DEBUG
			qDebug() << QString("Null pointer at CloseAllConnections() in m_lConnections at i = %1, count = %2").arg(QString().setNum(i), QString().setNum(count));
			#endif
		}
	}
	m_lConnections.clear();
	m_pCurrentConnection = NULL;
	
	ResetGui();

	Logging::getInstance()->WriteLog(INFORMATION, "Closed all connections");
}

void ODBC_Query::RefreshTables()
{
	if (m_pCurrentConnection != NULL)
		m_pCurrentConnection->LoadTables();
	else
	{
		Logging::getInstance()->WriteLog(CRITICAL, QString("Null pointer at RefreshTables() in m_pCurrentConnection"));
		#ifdef _DEBUG
		qDebug() << QString("Null pointer at RefreshTables() in m_pCurrentConnection");
		#endif
	}
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
				Logging::getInstance()->WriteLog(INFORMATION, QString("Switching to connection \"%1\" (current connection: \"%2\")...").arg(sNewConnectionName, m_pCurrentConnection->GetConnectionName()));
			else
				Logging::getInstance()->WriteLog(INFORMATION, QString("Switching to connection \"%1\"...").arg(sNewConnectionName));
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
						Logging::getInstance()->WriteLog(INFORMATION, QString("Switched connection, current connection \"%1\"").arg(m_pCurrentConnection->GetConnectionName()));
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
					Logging::getInstance()->WriteLog(INFORMATION, QString("Connection \"%1\" closed, it was the current connection").arg(sConnectionNameToClose));
					ResetGui();
					bCurrentConnection = true;
				}
			}
			else
			{
				Logging::getInstance()->WriteLog(WARNING, "Null pointer at ConnectionsClicked() in m_pCurrentConnection");
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
						Logging::getInstance()->WriteLog(INFORMATION, QString("Connection %1 closed, it wasn't the current connection").arg(sConnectionNameToClose));
					}
					else
					{
						Logging::getInstance()->WriteLog(CRITICAL, QString("Null pointer at ConnectionsClicked() in m_lConnections at i = %1, count = %2").arg(QString().setNum(i), QString().setNum(count)));
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
		Logging::getInstance()->WriteLog(CRITICAL, "Null pointer at ConnectionsClicked() in pMenu");
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
		ODBC_StandardItemModel *pModel = m_pCurrentConnection->GetMainModel();
		if (pModel != NULL)
		{
			ui.ResultCountLabel->setText(QString("Rows: %1").arg(pModel->rowCount()));

			// and bind it to the tableview
			ui.SQLResultTableView->setModel(pModel);
			ui.SQLResultTableView->sortByColumn(-1, Qt::AscendingOrder);
			ui.SQLResultTableView->verticalScrollBar()->setSliderPosition(ui.SQLResultTableView->verticalScrollBar()->minimum());
			ui.SQLResultTableView->horizontalScrollBar()->setSliderPosition(ui.SQLResultTableView->horizontalScrollBar()->minimum());
			ui.ExtractToolButton->setEnabled(true);

			CleanResultWindows();

			int iResultTableCount = m_pCurrentConnection->GetResultTableCount();
			if (iResultTableCount > 0)
			{
				for (int i = 0; i < iResultTableCount; i++)
				{
					ODBC_StandardItemModel *pModel2 = m_pCurrentConnection->GetSQLResultTable(i);
					if (pModel2 != NULL)
					{
						if (pModel2->rowCount() > 0)
						{
							ODBC_ResultWindow* pResultWindow = new ODBC_ResultWindow();
							m_lResultWindows.append(pResultWindow);

							pModel2->SetExtracted(true);
							pResultWindow->Init((i + 2), m_pCurrentConnection->GetConnectionName(), pModel2);
							pResultWindow->show();
						}	
					}
				}
			}
		}
		else
		{
			Logging::getInstance()->WriteLog(CRITICAL, "Null pointer at Executed() in pModel");
			#ifdef _DEBUG
			qDebug() << "Null pointer at Executed() in pModel";
			#endif
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
	ui.ExecuteToolButton->setIcon(QIcon(":/ODBC_Query/Resources/play_icon.png"));;
	m_pLoadingAnimation->stop();
	m_pLoadingLabel->setHidden(true);
}

void ODBC_Query::LimitReached()
{
	if (m_pCurrentConnection != NULL)
	{	
		if (QMessageBox::question(NULL, "Result limit", QString("Currently %1 rows are fetched, do you want to continue fetching?").arg(ODBC_OptionsDialog::getInstance()->GetResultLimitCount()), QMessageBox::Yes, QMessageBox::No) != QMessageBox::Yes)
			m_pCurrentConnection->SetContinueFetch(false);
		else
			m_pCurrentConnection->SetContinueFetch(true);

		m_pCurrentConnection->SetWaitForAnswer(false);
	}
}

void ODBC_Query::ShowOptions()
{
	ODBC_OptionsDialog::getInstance()->exec();
}

void ODBC_Query::ShowAbout()
{
	QMessageBox::about(this, QString("About %1").arg(APPLICATION_NAME), QString("<b>%1 (build: %2)</b><br/><br/>written by Daniel Rosenauer<br/><br/>mail: <a href='mailto:d.rosenauer@googlemail.com'>d.rosenauer@gmail.com</a><br/>github: <a href='https://github.com/Edder/odbc-query'>project page</a><br/><br/>linked against Qt %3").arg(APPLICATION_NAME, QString().setNum(REVISION), QT_VERSION_STR));
}

void ODBC_Query::ExtractResult()
{
	ODBC_StandardItemModel *pModel = m_pCurrentConnection->GetMainModel();
	if (pModel != NULL)
	{
		ODBC_ResultWindow* pResultWindow = NULL;

		// check if there is already a ResultWindows with that Model
		bool bFound = false;
		for (int i = 0; i < m_lResultWindows.count(); i++)
		{
			pResultWindow = m_lResultWindows.at(i);
			if (pResultWindow != NULL)
			{
				if (pResultWindow->GetModel() == pModel)
				{
					pResultWindow->show();
					pResultWindow->raise();
					bFound = true;
				}
			}
		}

		if (!bFound)
		{
			pResultWindow = new ODBC_ResultWindow();
			m_lResultWindows.append(pResultWindow);

			pModel->SetExtracted(true);
			pResultWindow->Init(1, m_pCurrentConnection->GetConnectionName(), pModel);
			pResultWindow->show();
		}
	}
	else
	{
		Logging::getInstance()->WriteLog(CRITICAL, "Null pointer at ExtractResult() in pModel");
		#ifdef _DEBUG
		qDebug() << "Null pointer at ExtractResult() in pModel";
		#endif
	}
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
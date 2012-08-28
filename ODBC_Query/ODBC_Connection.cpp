#include "precompiled.h"
#include "ODBC_Connection.h"
#include "Logging.h"

ODBC_Connection::ODBC_Connection(Ui::ODBC_QueryClass ui, QThread *ownThread)
{
	m_ui = ui;
	m_pOwnThread = ownThread;

	m_iCurrentHistoryIndex = 0;

	m_sConnectionName = QString();
	m_sCurrentStatement = QString();

	m_pQuery = NULL;
	m_pSqlQueryModel = NULL;
	m_pSortModel = NULL;
	m_pSQLResultTable = NULL;
}

ODBC_Connection::~ODBC_Connection()
{

}

bool ODBC_Connection::ConnectToDatabase(QString database, QString user, QString password)
{
	if (m_db.isOpen())
	{
		Logging::getInstance()->WriteLog(WARNING, "Warning in ConnectToDatabase(): Attempted to connect while connection is open");
		#ifdef _DEBUG
		qDebug() << "Warning in ConnectToDatabase(): Attempted to connect while connection is open";
		#endif
		return true;
	}

	m_db.setDatabaseName(database);
	if (user != "")
		m_db.setUserName(user);
	if (password != "")
		m_db.setPassword(password);

	m_db.setConnectOptions("SQL_ATTR_LOGIN_TIMEOUT=3");

	if (!m_db.open())
	{
		m_sDatabaseError = m_db.lastError().text();
		Logging::getInstance()->WriteLog(ERROR, QString("Couldn't connect to \"%1\", error: %2").arg(m_sConnectionName, m_sDatabaseError));
		#ifdef _DEBUG
		qDebug() << QString("Couldn't connect to \"%1\", error: %2").arg(m_sConnectionName, m_sDatabaseError);
		#endif
		return false;
	}
	else
	{
		// set the status label
		m_ui.StatusLabel->setText(QString("Connected to %1").arg(m_sConnectionName));
		Logging::getInstance()->WriteLog(INFORMATION, QString("Connected to \"%1\"").arg(m_sConnectionName));
		LoadTables();
		return true;
	}
}

void ODBC_Connection::LoadTables()
{
	// the table and field view
	m_ui.TableTreeWidget->clear();
	m_ui.FieldTreeWidget->clear();
	// populate the available tables
	Logging::getInstance()->WriteLog(INFORMATION, QString("Retrieving database tables of connection \"%1\"...").arg(m_sConnectionName));
	for (int i = 0, count = m_db.tables().count(); i < count; i++)
	{
		QString sTableName = m_db.tables().value(i);
		QTreeWidgetItem *pItem = new QTreeWidgetItem(QStringList() << sTableName);
		m_ui.TableTreeWidget->addTopLevelItem(pItem);
		// if its the previously loaded table, select and load it
		if (sTableName == m_sLoadedTable)
		{
			pItem->setSelected(true);
			LoadTableColumns(m_sLoadedTable);
		}
	}
}

void ODBC_Connection::LoadTableColumns(QString tableName)
{
	if (m_db.isOpen())
	{
		// set wait cursor
		QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
		QApplication::processEvents();
		Logging::getInstance()->WriteLog(INFORMATION, QString("Retrieving tableinfo for table \"%1\" of connection \"%2\"...").arg(tableName, m_sConnectionName));
		bool bTableWarningShown = false;
		m_ui.FieldTreeWidget->clear();
		QSqlRecord records = m_db.record(tableName);
		QSqlField field;
		QSqlIndex index = m_db.primaryIndex(tableName);
		QString sName;
		QSqlQuery query;
		QString sTypeName;
		QString sLength;
		QString sNullable;
		for (int i = 0, count = records.count(); i < count; i++)
		{
			field = records.field(i);
			sName = field.name();
			query = m_db.exec(QString("SELECT DATA_TYPE, CHARACTER_MAXIMUM_LENGTH, NUMERIC_PRECISION, IS_NULLABLE FROM INFORMATION_SCHEMA.COLUMNS WHERE COLUMN_NAME = '%1' AND TABLE_NAME = '%2'").arg(sName, tableName));
			if (query.next())
			{
				sTypeName = query.value(0).toString();
				sLength = query.value(1).toString() != "0" ? query.value(1).toString() : query.value(2).toString();
				sNullable = query.value(3).toString();
				query.finish();
			}
			else
			{
				if (!bTableWarningShown)
				{	
					Logging::getInstance()->WriteLog(WARNING, QString("Couldn't retrieve fieldinfo for table \"%1\" of connection \"%2\", database INFORMATION_SCHEMA.COLUMNS doesn't exist").arg(tableName, m_sConnectionName));
					#ifdef _DEBUG
					qDebug() << QString("Couldn't retrieve fieldinfo for table \"%1\" of connection \"%2\", database INFORMATION_SCHEMA.COLUMNS doesn't exist").arg(tableName, m_sConnectionName);
					#endif
					bTableWarningShown = true;
				}
			}
			bool isPrimaryKey = index.contains(sName) ? true : false;
			QTreeWidgetItem *pItem = new QTreeWidgetItem(QStringList() << sName << sTypeName << sLength << sNullable);
			if (isPrimaryKey)
				pItem->setIcon(0, QIcon(":/ODBC_Query/Resources/primary_key.png"));

			m_ui.FieldTreeWidget->addTopLevelItem(pItem);
		}
		m_ui.FieldTreeWidget->resizeColumnToContents(1);
		m_ui.FieldTreeWidget->resizeColumnToContents(2);	
		m_ui.FieldTreeWidget->resizeColumnToContents(3);
		m_sLoadedTable = tableName;
		Logging::getInstance()->WriteLog(INFORMATION, QString("Tableinfo for table \"%1\" of connection \"%2\" retrieved").arg(tableName, m_sConnectionName));
	}
	else
	{
		Logging::getInstance()->WriteLog(ERROR, QString("Couldn't retrieve tableinfo for table \"%1\" of connection \"%2\", connection isn't open").arg(tableName, m_sConnectionName));
		#ifdef _DEBUG
		qDebug() << QString("Couldn't retrieve tableinfo for table \"%1\" of connection \"%2\", connection isn't open").arg(tableName, m_sConnectionName);
		#endif
	}
	// set back to arrow cursor
	QApplication::restoreOverrideCursor();
}

void ODBC_Connection::ExecuteQuery(QString query)
{
	if (m_pQuery != NULL)
		if (m_pQuery->isActive())
			m_pQuery->finish();
	Logging::getInstance()->WriteLog(INFORMATION, QString("Executing statement \"%1\" of connection \"%2\"...").arg(query, m_sConnectionName));
	mTime = mTime.currentTime();
	mTime.start(); // count the time, the query execution takes
	m_pQuery = new QSqlQuery(m_db);
	if (!m_pQuery->exec(query))
	{
		QString sError = m_pQuery->lastError().text();
		m_sLogText = QString("<table><tr><td><b>%1</b></td><td><font color='#FF0000'>%2</font></td></tr></table>").arg(QDateTime::currentDateTime().toString("(hh:mm:ss)"), sError);
		Logging::getInstance()->WriteLog(ERROR, sError);
	}
	else
	{
		m_pSqlQueryModel = new QSqlQueryModel();
		m_pSqlQueryModel->setQuery(*m_pQuery);
		if (m_pSqlQueryModel->rowCount() != 0)
		{			
			m_pSortModel = new QSortFilterProxyModel();
			m_pSortModel->setSourceModel(m_pSqlQueryModel);
			m_pSQLResultTable = m_pSortModel;
		}

		m_sLogText = QString("<table><tr><td><b>%1</b></td><td>%2</td></tr><tr><td></td><td>%3</td></table>").arg(QDateTime::currentDateTime().toString("(hh:mm:ss)"), "Query executed successfully after " + QString().setNum(mTime.elapsed()) + " ms!", QString().setNum(m_pQuery->numRowsAffected()) + " row(s) affected\n");	
		Logging::getInstance()->WriteLog(INFORMATION, QString("Statement executed succssfully after %1 ms, %2 row(s) affected").arg(QString().setNum(mTime.elapsed()), QString().setNum(m_pQuery->numRowsAffected())));
		if (m_slStatementHistory.count() != 0)
		{
			if (m_slStatementHistory.value(m_iCurrentHistoryIndex) != query)
			{
				m_slStatementHistory << query;
				m_iCurrentHistoryIndex = (m_slStatementHistory.count() - 1);
			}
		}
		else
			m_slStatementHistory << query;
	}	
	emit Executed();
}

void ODBC_Connection::HandleLeftRightButton(bool directionRight)
{
	m_ui.LeftToolButton->setEnabled(true);
	m_ui.RightToolButton->setEnabled(true);
	int iStatementCount = m_slStatementHistory.count();
	if (directionRight)
	{
		m_iCurrentHistoryIndex++;
		if (m_iCurrentHistoryIndex > iStatementCount)
			m_iCurrentHistoryIndex = iStatementCount;
	}
	else
	{
		m_iCurrentHistoryIndex--;
		if (m_iCurrentHistoryIndex < 0)
			m_iCurrentHistoryIndex = 0;
	}
	if (m_iCurrentHistoryIndex < iStatementCount)
		m_ui.SQLCommandTextEdit->setText(m_slStatementHistory.value(m_iCurrentHistoryIndex));
	else
		m_ui.SQLCommandTextEdit->setText("");

	if (m_iCurrentHistoryIndex == 0)
		m_ui.LeftToolButton->setDisabled(true);

	if (m_iCurrentHistoryIndex == iStatementCount && iStatementCount != 0)
		m_ui.RightToolButton->setDisabled(true);

	m_ui.CurrentStatementLabel->setText(QString().setNum(m_iCurrentHistoryIndex + 1));
}

void ODBC_Connection::HandleSQLCommandTextChanged()
{
	if (m_ui.SQLCommandTextEdit->toPlainText() != "")
		m_ui.ExecuteToolButton->setEnabled(true);
	else
		m_ui.ExecuteToolButton->setDisabled(true);
}

void ODBC_Connection::OpenConnection(QString connectionName)
{
	m_db = QSqlDatabase::addDatabase("QODBC", connectionName);
	m_sConnectionName = connectionName;
}

void ODBC_Connection::RestoreGui()
{
	m_ui.SQLCommandTextEdit->setText(m_sCurrentStatement);
	m_ui.SQLLogTextBrowser->setText(m_sLogFile);
	m_ui.SQLResultTableView->setModel(NULL);

	LoadTables();

	int iStatementCount = m_slStatementHistory.count();
	if (m_iCurrentHistoryIndex < iStatementCount)
		m_ui.SQLCommandTextEdit->setText(m_slStatementHistory.value(m_iCurrentHistoryIndex));
	else
		m_ui.SQLCommandTextEdit->setText("");

	m_ui.CurrentStatementLabel->setText(QString().setNum(m_iCurrentHistoryIndex + 1));

	if (m_ui.SQLCommandTextEdit->toPlainText() == "")
		m_ui.ExecuteToolButton->setDisabled(true);

	if (m_iCurrentHistoryIndex == 0)
	{
		m_ui.LeftToolButton->setDisabled(true);
		if (m_ui.SQLCommandTextEdit->toPlainText() == "")
			m_ui.RightToolButton->setDisabled(true);
		else
		{
			m_ui.RightToolButton->setEnabled(true);
			m_ui.CurrentStatementLabel->setEnabled(true);
		}
	}
	else if (m_iCurrentHistoryIndex == iStatementCount && iStatementCount != 0)
	{
		m_ui.RightToolButton->setDisabled(true);
		m_ui.LeftToolButton->setEnabled(true);
		m_ui.CurrentStatementLabel->setEnabled(true);
	}
	else
	{
		m_ui.RightToolButton->setEnabled(true);
		m_ui.LeftToolButton->setEnabled(true);
		m_ui.CurrentStatementLabel->setEnabled(true);
	} 

	// set the status label
	m_ui.StatusLabel->setText(QString("Connected to %1").arg(m_sConnectionName));
}

void ODBC_Connection::SaveGui()
{
	m_sCurrentStatement = m_ui.SQLCommandTextEdit->toPlainText();
	m_sLogFile = m_ui.SQLLogTextBrowser->toHtml();
}

void ODBC_Connection::CloseConnection()
{
	if (m_pQuery != NULL)
	{
		if (m_pQuery->isActive())
			m_pQuery->finish();
	}

	if (m_pOwnThread != NULL)
	{
		if (m_pOwnThread->isRunning())
			m_pOwnThread->quit();
	}

	if (m_pQuery != NULL)
	{
		delete m_pQuery;
		m_pQuery = NULL;
	}

	if (m_pSqlQueryModel != NULL)
	{
		delete m_pSqlQueryModel;
		m_pSqlQueryModel = NULL;
	}

	if (m_pSortModel != NULL)
	{
		delete m_pSortModel;
		m_pSortModel = NULL;
	}

    m_db.close();
	m_db = QSqlDatabase();
	QSqlDatabase::removeDatabase(m_sConnectionName);
}
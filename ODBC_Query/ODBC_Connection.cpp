#include "precompiled.h"
#include "ODBC_Connection.h"
#include "Logging.h"

ODBC_Connection::ODBC_Connection(Ui::ODBC_QueryClass ui, QWidget *parent) : QWidget(parent)
{
	m_ui = ui;

	m_iCurrentHistoryIndex = 0;

	m_sLastSelectStatement = QString();
	m_sCurrentStatement = QString();

	m_pQuery = NULL;
	m_pSqlQueryModel = NULL;
}

ODBC_Connection::~ODBC_Connection()
{

}

bool ODBC_Connection::ConnectToDatabase(bool reconnect, QString database, QString user, QString password)
{
	if (m_db.isOpen())
		m_db.close();

	if (!reconnect)
	{
		m_sDatabase = database;
		m_sUser = user;
		m_sPassword = password;
	}

	m_db.setDatabaseName(m_sDatabase);
	if (m_sUser != "")
		m_db.setUserName(m_sUser);
	if (m_sPassword != "")
		m_db.setPassword(m_sPassword);

	m_db.setConnectOptions("SQL_ATTR_LOGIN_TIMEOUT=3");

	if (!m_db.open())
	{
		QMessageBox::critical(this, "Error", m_db.lastError().text(), QMessageBox::Ok);
		Logging::getInstance()->WriteLog(ERROR, QString("Couldn't connect to \"%1\", error: %2").arg(m_sConnectionName, m_db.lastError().text()));
		#ifdef _DEBUG
		qDebug() << QString("Couldn't connect to \"%1\", error: %2").arg(m_sConnectionName, m_db.lastError().text());
		#endif
		return false;
	}
	else
	{
		// set the status label
		m_ui.StatusLabel->setText(QString("Connected to %1").arg(m_sConnectionName));
		Logging::getInstance()->WriteLog(INFORMATION, QString("Connected to \"%1\"").arg(m_sConnectionName));
		// the table and field view
		m_ui.TableTreeWidget->clear();
		m_ui.FieldTreeWidget->clear();
		// populate the available tables
		Logging::getInstance()->WriteLog(INFORMATION, QString("Retrieving database tables of connection \"%1\"...").arg(m_sConnectionName));
		for (int i = 0, count = m_db.tables().count(); i < count; i++)
		{
			QString tableName = m_db.tables().value(i);
			QTreeWidgetItem *item = new QTreeWidgetItem(QStringList() << tableName);
			m_ui.TableTreeWidget->addTopLevelItem(item);
			// if its the previously loaded table, select and load it
			if (tableName == m_sLoadedTable)
			{
				item->setSelected(true);
				LoadTableColumns(m_sLoadedTable);
			}
		}
		// restore the command and logging textbox
		m_ui.SQLCommandTextEdit->setText(m_sCurrentStatement);
		m_ui.SQLLogTextBrowser->setText(m_sLogFile);
		// reexecute the query if its a select statement
		if (m_sLastSelectStatement != "")
			ExecuteQuery(m_sLastSelectStatement, false);
		return true;
	}
}

void ODBC_Connection::LoadTableColumns(QString sTableName)
{
	if (m_db.isOpen())
	{
		Logging::getInstance()->WriteLog(INFORMATION, QString("Retrieving tableinfo for table \"%1\" of connection \"%2\"...").arg(sTableName, m_sConnectionName));
		bool bTableWarningShown = false;
		m_ui.FieldTreeWidget->clear();
		QSqlRecord records = m_db.record(sTableName);
		QSqlField field;
		QSqlIndex index = m_db.primaryIndex(sTableName);
		QString sName;
		QSqlQuery query;
		QString sTypeName;
		QString sLength;
		QString sNullable;
		for (int i = 0, count = records.count(); i < count; i++)
		{
			field = records.field(i);
			sName = field.name();
			query = m_db.exec(QString("SELECT DATA_TYPE, CHARACTER_MAXIMUM_LENGTH, NUMERIC_PRECISION, IS_NULLABLE FROM INFORMATION_SCHEMA.COLUMNS WHERE COLUMN_NAME = '%1' AND TABLE_NAME = '%2'").arg(sName, sTableName));
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
					Logging::getInstance()->WriteLog(WARNING, QString("Couldn't retrieve fieldinfo for table \"%1\" of connection \"%2\", database INFORMATION_SCHEMA.COLUMNS doesn't exist").arg(sTableName, m_sConnectionName));
					#ifdef _DEBUG
					qDebug() << QString("Couldn't retrieve fieldinfo for table \"%1\" of connection \"%2\", database INFORMATION_SCHEMA.COLUMNS doesn't exist").arg(sTableName, m_sConnectionName);
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
		m_sLoadedTable = sTableName;
		Logging::getInstance()->WriteLog(INFORMATION, QString("Tableinfo for table \"%1\" of connection \"%2\" retrieved").arg(sTableName, m_sConnectionName));
	}
	else
	{
		Logging::getInstance()->WriteLog(ERROR, QString("Couldn't retrieve tableinfo for table \"%1\" of connection \"%2\", connection isn't open").arg(sTableName, m_sConnectionName));
		#ifdef _DEBUG
		qDebug() << QString("Couldn't retrieve tableinfo for table \"%1\" of connection \"%2\", connection isn't open").arg(sTableName, m_sConnectionName);
		#endif
	}
}

void ODBC_Connection::ExecuteQuery(QString sQuery, bool firstExecute)
{
	if (m_db.isOpen())
	{
		Logging::getInstance()->WriteLog(INFORMATION, QString("Executing statement \"%1\" of connection \"%2\"...").arg(sQuery, m_sConnectionName));
		QTime time;
		time.start(); // count the time, the query execution takes
		m_pQuery = new QSqlQuery(m_db);
		if (!m_pQuery->exec(sQuery))
		{
			QString errorText = m_pQuery->lastError().text();
			if (errorText.trimmed() != "" && firstExecute)
				m_ui.SQLLogTextBrowser->append(QString("<table><tr><td><b>%1</b></td><td><font color='#FF0000'>%2</font></td></tr></table>").arg(QDateTime::currentDateTime().toString("(hh:mm:ss)"), errorText));
		}
		else
		{
			m_pSqlQueryModel = new QSqlQueryModel(parent());
			m_pSqlQueryModel->setQuery(*m_pQuery);
			if (m_pSqlQueryModel->rowCount() != 0)
			{			
				QSortFilterProxyModel *pSortModel = new QSortFilterProxyModel(this->parent());
				pSortModel->setSourceModel(m_pSqlQueryModel);
				m_ui.SQLResultTableView->setModel(pSortModel);
				m_ui.SQLResultTableView->sortByColumn(-1, Qt::AscendingOrder);
				m_ui.SQLResultTableView->verticalScrollBar()->setSliderPosition(m_ui.SQLResultTableView->verticalScrollBar()->minimum());
				m_ui.SQLResultTableView->horizontalScrollBar()->setSliderPosition(m_ui.SQLResultTableView->horizontalScrollBar()->minimum());
			}
			Logging::getInstance()->WriteLog(INFORMATION, QString("Statement executed succssfully after %1 ms, %2 row(s) affected").arg(QString().setNum(time.elapsed()), QString().setNum(m_pQuery->numRowsAffected())));
			if (firstExecute)
			{
				m_ui.SQLLogTextBrowser->append(QString("<table><tr><td><b>%1</b></td><td>%2</td></tr><tr><td></td><td>%3</td></table>").arg(QDateTime::currentDateTime().toString("(hh:mm:ss)"), "Query executed successfully after " + QString().setNum(time.elapsed()) + " ms!", QString().setNum(m_pQuery->numRowsAffected()) + " row(s) affected\n"));	
				if (m_slStatementHistory.count() != 0)
				{
					if (m_slStatementHistory.value(m_iCurrentHistoryIndex) != sQuery)
					{
						m_slStatementHistory << sQuery;
						m_iCurrentHistoryIndex = (m_slStatementHistory.count() - 1);
					}
				}
				else
					m_slStatementHistory << sQuery;
				if (m_iCurrentHistoryIndex > 0)
					m_ui.LeftToolButton->setEnabled(true);
				m_ui.RightToolButton->setEnabled(true);
				if (!m_ui.CurrentStatementLabel->isEnabled())
					m_ui.CurrentStatementLabel->setEnabled(true);
				m_ui.CurrentStatementLabel->setText(QString().setNum(m_iCurrentHistoryIndex + 1));
				if (m_pQuery->isSelect())
					m_sLastSelectStatement = m_pQuery->executedQuery();
			}
		}
	}
	else
	{
		Logging::getInstance()->WriteLog(ERROR, QString("Couldn't execute statement \"%1\" of connection \"%2\", connection isn't open").arg(sQuery, m_sConnectionName));
		#ifdef _DEBUG
		qDebug() << QString("Couldn't execute statement \"%1\" of connection \"%2\", connection isn't open").arg(sQuery, m_sConnectionName);
		#endif
	}
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
	m_sConnectionName = m_db.connectionName();

	RestoreGui();
}

void ODBC_Connection::RestoreGui()
{
	m_ui.SQLCommandTextEdit->setText(m_sCurrentStatement);
	m_ui.SQLLogTextBrowser->setText(m_sLogFile);

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

	m_ui.SQLResultTableView->setModel(NULL);
}

void ODBC_Connection::SaveGui()
{
	m_sCurrentStatement = m_ui.SQLCommandTextEdit->toPlainText();
	m_sLogFile = m_ui.SQLLogTextBrowser->toHtml();
}

void ODBC_Connection::CloseConnection()
{
	SaveGui();

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

	QString connection = m_db.connectionName();
    m_db.close();
    m_db = QSqlDatabase();
    m_db.removeDatabase(connection);
}
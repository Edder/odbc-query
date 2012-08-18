#include "precompiled.h"
#include "ODBC_Connection.h"

<<<<<<< HEAD
ODBC_Connection::ODBC_Connection(Ui::ODBC_QueryClass ui, QWidget *parent) : QWidget(parent)
=======
ODBC_Connection::ODBC_Connection(Ui::ODBC_QueryClass ui)
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
{
	m_ui = ui;

	m_iCurrentHistoryIndex = 0;

<<<<<<< HEAD
	m_sLastSelectStatement = QString();
	m_sCurrentStatement = QString();

	m_pSqlQueryModel = NULL;
=======
	m_pQuery = NULL;
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
}

ODBC_Connection::~ODBC_Connection()
{

}

<<<<<<< HEAD
bool ODBC_Connection::ConnectToDatabase(bool firstConnect, QString database, QString user, QString password)
=======
bool ODBC_Connection::ConnectToDatabase(QString database, QString user, QString password, bool firstConnect)
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
{
	if (m_db.isOpen())
		m_db.close();

	if (firstConnect)
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
		return false;
	}
	else
	{
		// the talbe and field view
		m_ui.TableTreeWidget->clear();
		m_ui.FieldTreeWidget->clear();
		// populate the available tables
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
<<<<<<< HEAD
		if (m_sLastSelectStatement != "")
			ExecuteQuery(m_sLastSelectStatement, false);
=======
		if (m_pQuery != NULL)
		{
			if (m_pQuery->isSelect()) // do not execute it, if its no select statement
				ExecuteQuery(m_pQuery->executedQuery(), false);
		}
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
		return true;
	}
}

void ODBC_Connection::LoadTableColumns(QString tableName)
{
	m_ui.FieldTreeWidget->clear();
	QSqlRecord records = m_db.record(tableName);
	QSqlField field;
	QSqlIndex index = m_db.primaryIndex(tableName);
	QString name;
	QSqlQuery query;
	QString typeName;
	QString length;
	QString nullable;
	for (int i = 0, count = records.count(); i < count; i++)
	{
		field = records.field(i);
		name = field.name();
		query = m_db.exec(QString("SELECT DATA_TYPE, CHARACTER_MAXIMUM_LENGTH, NUMERIC_PRECISION, IS_NULLABLE FROM INFORMATION_SCHEMA.COLUMNS WHERE COLUMN_NAME = '%1' AND TABLE_NAME = '%2'").arg(name, tableName));
		query.next();
		typeName = query.value(0).toString();
		length = query.value(1).toString() != "0" ? query.value(1).toString() : query.value(2).toString();
		nullable = query.value(3).toString();
		query.finish();
		bool isPrimaryKey = index.contains(name) ? true : false;
		QTreeWidgetItem *item = new QTreeWidgetItem(QStringList() << name << typeName << length << nullable);
		if (isPrimaryKey)
			item->setIcon(0, QIcon(":/ODBC_Query/Resources/primary_key.png"));

		m_ui.FieldTreeWidget->addTopLevelItem(item);
	}
<<<<<<< HEAD
	query.finish();
=======
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
	m_ui.FieldTreeWidget->resizeColumnToContents(1);
	m_ui.FieldTreeWidget->resizeColumnToContents(2);	
	m_ui.FieldTreeWidget->resizeColumnToContents(3);
	m_sLoadedTable = tableName;
}

void ODBC_Connection::ExecuteQuery(QString s_query, bool firstExecute)
{
	if (m_db.isOpen())
	{
		QTime time;
		time.start(); // count the time, the query execution takes
<<<<<<< HEAD
		QSqlQuery m_pQuery = QSqlQuery(m_db);
		if (!m_pQuery.exec(s_query))
		{
			QString errorText = m_pQuery.lastError().text();
=======
		m_pQuery = new QSqlQuery(m_db);
		if (!m_pQuery->exec(s_query))
		{
			QString errorText = m_pQuery->lastError().text();
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
			if (errorText.trimmed() != "" && firstExecute)
				m_ui.SQLLogTextBrowser->append(QString("<table><tr><td><b>%1</b></td><td><font color='#FF0000'>%2</font></td></tr></table>").arg(QDateTime::currentDateTime().toString("(hh:mm:ss)"), errorText));
		}
		else
		{
<<<<<<< HEAD
			m_pSqlQueryModel = new QSqlQueryModel(this->parent());
			m_pSqlQueryModel->setQuery(m_pQuery);
			if (m_pSqlQueryModel->rowCount() != 0)
			{			
				QSortFilterProxyModel *pSortModel = new QSortFilterProxyModel(this->parent());
				pSortModel->setSourceModel(m_pSqlQueryModel);
=======
			QSqlQueryModel *pSqlQueryModel = new QSqlQueryModel(this);
			pSqlQueryModel->setQuery(*m_pQuery);
			if (pSqlQueryModel->rowCount() != 0)
			{			
				QSortFilterProxyModel *pSortModel = new QSortFilterProxyModel(this);
				pSortModel->setSourceModel(pSqlQueryModel);
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
				m_ui.SQLResultTableView->setModel(pSortModel);
				m_ui.SQLResultTableView->sortByColumn(-1, Qt::AscendingOrder);
				m_ui.SQLResultTableView->verticalScrollBar()->setSliderPosition(m_ui.SQLResultTableView->verticalScrollBar()->minimum());
				m_ui.SQLResultTableView->horizontalScrollBar()->setSliderPosition(m_ui.SQLResultTableView->horizontalScrollBar()->minimum());
			}
			if (firstExecute)
			{
<<<<<<< HEAD
				m_ui.SQLLogTextBrowser->append(QString("<table><tr><td><b>%1</b></td><td>%2</td></tr><tr><td></td><td>%3</td></table>").arg(QDateTime::currentDateTime().toString("(hh:mm:ss)"), "Query executed successfully after " + QString().setNum(time.elapsed()) + " ms!", QString().setNum(m_pQuery.numRowsAffected()) + " row(s) affected\n"));	
=======
				m_ui.SQLLogTextBrowser->append(QString("<table><tr><td><b>%1</b></td><td>%2</td></tr><tr><td></td><td>%3</td></table>").arg(QDateTime::currentDateTime().toString("(hh:mm:ss)"), "Query executed successfully after " + QString().setNum(time.elapsed()) + " ms!", QString().setNum(m_pQuery->numRowsAffected()) + " row(s) affected\n"));	
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
				if (m_slStatementHistory.count() != 0)
				{
					if (m_slStatementHistory.value(m_iCurrentHistoryIndex) != s_query)
					{
						m_slStatementHistory << s_query;
						m_iCurrentHistoryIndex = (m_slStatementHistory.count() - 1);
					}
				}
				else
					m_slStatementHistory << s_query;
<<<<<<< HEAD
				if (m_iCurrentHistoryIndex > 0)
					m_ui.LeftToolButton->setEnabled(true);
				m_ui.RightToolButton->setEnabled(true);
				if (!m_ui.CurrentStatementLabel->isEnabled())
					m_ui.CurrentStatementLabel->setEnabled(true);
				m_ui.CurrentStatementLabel->setText(QString().setNum(m_iCurrentHistoryIndex + 1));
				if (m_pQuery.isSelect())
					m_sLastSelectStatement = m_pQuery.executedQuery();
=======
				m_ui.RightToolButton->setEnabled(true);
				m_ui.CurrentStatementLabel->setText(QString().setNum(m_iCurrentHistoryIndex + 1));
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
			}
		}
	}
}

void ODBC_Connection::HandleLeftRightButton(bool directionRight)
{
	m_ui.LeftToolButton->setEnabled(true);
	m_ui.RightToolButton->setEnabled(true);
	if (directionRight)
	{
		m_iCurrentHistoryIndex++;
		if (m_iCurrentHistoryIndex == (m_slStatementHistory.count() + 1))
			m_iCurrentHistoryIndex = m_slStatementHistory.count();
	}
	else
	{
		m_iCurrentHistoryIndex--;
		if (m_iCurrentHistoryIndex == -1)
			m_iCurrentHistoryIndex = 0;
	}
	if (m_iCurrentHistoryIndex < m_slStatementHistory.count())
		m_ui.SQLCommandTextEdit->setText(m_slStatementHistory.value(m_iCurrentHistoryIndex));
	else
		m_ui.SQLCommandTextEdit->setText("");
	m_ui.CurrentStatementLabel->setText(QString().setNum(m_iCurrentHistoryIndex + 1));

	if (m_iCurrentHistoryIndex == 0)
		m_ui.LeftToolButton->setDisabled(true);

	if (m_iCurrentHistoryIndex == m_slStatementHistory.count() && m_slStatementHistory.count() != 0)
		m_ui.RightToolButton->setDisabled(true);
}

<<<<<<< HEAD
void ODBC_Connection::HandleSQLCommandTextChanged()
{
	if (m_ui.SQLCommandTextEdit->toPlainText() != "")
		m_ui.ExecuteToolButton->setEnabled(true);
	else
		m_ui.ExecuteToolButton->setDisabled(true);
}

=======
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
void ODBC_Connection::OpenConnection(QString connectionName)
{
	m_db = QSqlDatabase::addDatabase("QODBC", connectionName);
	m_sConnectionName = m_db.connectionName();

<<<<<<< HEAD
	RestoreGui();
}

void ODBC_Connection::RestoreGui()
{
	m_ui.SQLCommandTextEdit->setText(m_sCurrentStatement);
	m_ui.SQLLogTextBrowser->setText(m_sLogFile);

=======
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
	if (m_iCurrentHistoryIndex < m_slStatementHistory.count())
		m_ui.SQLCommandTextEdit->setText(m_slStatementHistory.value(m_iCurrentHistoryIndex));
	else
		m_ui.SQLCommandTextEdit->setText("");
	m_ui.CurrentStatementLabel->setText(QString().setNum(m_iCurrentHistoryIndex + 1));

<<<<<<< HEAD
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
	else if (m_iCurrentHistoryIndex == m_slStatementHistory.count() && m_slStatementHistory.count() != 0)
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

	if (m_pSqlQueryModel != NULL)
	{
		delete m_pSqlQueryModel;
		m_pSqlQueryModel = NULL;
	}

=======
	if (m_iCurrentHistoryIndex == 0)
		m_ui.LeftToolButton->setDisabled(true);
	else
		m_ui.LeftToolButton->setEnabled(true);

	if (m_iCurrentHistoryIndex == m_slStatementHistory.count() && m_slStatementHistory.count() != 0)
		m_ui.RightToolButton->setDisabled(true);
	else
		m_ui.RightToolButton->setEnabled(true);
}

void ODBC_Connection::CloseConnection()
{
	m_sCurrentStatement = m_ui.SQLCommandTextEdit->toPlainText();
	m_sLogFile = m_ui.SQLLogTextBrowser->toHtml();
	m_ui.SQLResultTableView->setModel(NULL);
	if (m_pQuery != NULL)
		m_pQuery->finish();
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
	QString connection;
    connection = m_db.connectionName();
    m_db.close();
    m_db = QSqlDatabase();
    m_db.removeDatabase(connection);
}
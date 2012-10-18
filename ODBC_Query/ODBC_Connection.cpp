#include "precompiled.h"
#include "ODBC_Connection.h"
#include "ODBC_OptionsDialog.h"

ODBC_Connection::ODBC_Connection(Ui::ODBC_QueryClass ui, QThread *ownThread)
{
	m_ui = ui;
	m_pOwnThread = ownThread;

	m_iCurrentHistoryIndex = 0;

	m_sConnectionName = QString();
	m_sCurrentStatement = QString();
}

ODBC_Connection::~ODBC_Connection()
{

}

bool ODBC_Connection::ConnectToDatabase(QString database, QString user, QString password)
{
	if (m_db.isOpen())
	{
		QMyLogging::getInstance()->WriteLog(WARNING, "Warning in ConnectToDatabase(): Attempted to connect while connection is open");
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

	m_db.setConnectOptions(QString("SQL_ATTR_LOGIN_TIMEOUT=%1").arg(ODBC_OptionsDialog::getInstance()->GetConnectionTimeout()));

	if (!m_db.open())
	{
		m_sDatabaseError = m_db.lastError().text();
		QMyLogging::getInstance()->WriteLog(ERR, QString("Couldn't connect to \"%1\", error: %2").arg(m_sConnectionName, m_sDatabaseError));
		#ifdef _DEBUG
		qDebug() << QString("Couldn't connect to \"%1\", error: %2").arg(m_sConnectionName, m_sDatabaseError);
		#endif
		return false;
	}
	else
	{
		// set the status label
		m_ui.StatusLabel->setText(QString("Connected to %1").arg(m_sConnectionName));
		QMyLogging::getInstance()->WriteLog(INFORMATION, QString("Connected to \"%1\"").arg(m_sConnectionName));
		LoadTables();
		return true;
	}
}

void ODBC_Connection::LoadTables()
{
	// the table and field view
	m_ui.TableTreeWidget->clear();

	// populate the available tables
	QMyLogging::getInstance()->WriteLog(INFORMATION, QString("Retrieving database tables of connection \"%1\"...").arg(m_sConnectionName));
	for (int i = 0, count = m_db.tables().count(); i < count; i++)
	{
		QString sTableName = m_db.tables().value(i);
		QTreeWidgetItem *pItem = new QTreeWidgetItem(QStringList() << sTableName);
		pItem->setIcon(0, QIcon(":/ODBC_Query/Resources/table.png"));
		m_ui.TableTreeWidget->addTopLevelItem(pItem);
		pItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
	}
}

void ODBC_Connection::LoadTableColumns(QTreeWidgetItem *item)
{
	for (int i = 0, count = item->childCount(); i < count; i++)
		item->removeChild(item->child(0));
		
	QString sTableName = item->text(0);

	if (m_db.isOpen())
	{
		if (!m_db.tables().contains(sTableName)) // if it isnt a table, return
			return;

		// set wait cursor
		QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
		QApplication::processEvents();
		QMyLogging::getInstance()->WriteLog(INFORMATION, QString("Retrieving tableinfo for table \"%1\" of connection \"%2\"...").arg(sTableName, m_sConnectionName));
		bool bTableWarningShown = false;
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
					QMyLogging::getInstance()->WriteLog(WARNING, QString("Couldn't retrieve fieldinfo for table \"%1\" of connection \"%2\", database INFORMATION_SCHEMA.COLUMNS doesn't exist, starting fallback to manual type detection").arg(sTableName, m_sConnectionName));
					#ifdef _DEBUG
					qDebug() << QString("Couldn't retrieve fieldinfo for table \"%1\" of connection \"%2\", database INFORMATION_SCHEMA.COLUMNS doesn't exist, starting fallback to manual type detection").arg(sTableName, m_sConnectionName);
					#endif
					bTableWarningShown = true;
				}
				sTypeName = QVariant::typeToName(field.type());
				sLength = QString().setNum(field.length());
				sNullable = (field.requiredStatus() == 1 ? "YES" : "NO");
			}
			bool isPrimaryKey = index.contains(sName) ? true : false;
			QTreeWidgetItem *pItem = new QTreeWidgetItem();
			if (isPrimaryKey)
			{
				pItem->setText(0, QString("%1 (PS, %2(%3), %4)").arg(sName, sTypeName, sLength, (sNullable == "YES" ? "NULL" : "NOT NULL")));
				pItem->setIcon(0, QIcon(":/ODBC_Query/Resources/primary_key.png"));
			}
			else
			{
				pItem->setText(0, QString("%1 (%2(%3), %4)").arg(sName, sTypeName, sLength, (sNullable == "YES" ? "NULL" : "NOT NULL")));
				pItem->setIcon(0, QIcon(":/ODBC_Query/Resources/row.png"));
			}
			item->addChild(pItem);
		}
		m_ui.TableTreeWidget->expandItem(item);
		QMyLogging::getInstance()->WriteLog(INFORMATION, QString("Tableinfo for table \"%1\" of connection \"%2\" retrieved").arg(sTableName, m_sConnectionName));
	}
	else
	{
		QMyLogging::getInstance()->WriteLog(ERR, QString("Couldn't retrieve tableinfo for table \"%1\" of connection \"%2\", connection isn't open").arg(sTableName, m_sConnectionName));
		#ifdef _DEBUG
		qDebug() << QString("Couldn't retrieve tableinfo for table \"%1\" of connection \"%2\", connection isn't open").arg(sTableName, m_sConnectionName);
		#endif
	}
	// set back to arrow cursor
	QApplication::restoreOverrideCursor();
}

void ODBC_Connection::ExecuteQuery(QString query)
{
	if (mQuery.isActive())
		mQuery.finish();

	QMyLogging::getInstance()->WriteLog(INFORMATION, QString("Executing statement \"%1\" of connection \"%2\"...").arg(query, m_sConnectionName));
	mTime = mTime.currentTime();
	mTime.start(); // count the time, the query execution takes
	QSqlQuery mQuery(m_db);
	mQuery.setForwardOnly(ODBC_OptionsDialog::getInstance()->ForwardOnly());
	if (!mQuery.exec(query))
	{
		QString sError = mQuery.lastError().text();
		m_sLogText = QString("<table><tr><td><b>%1</b></td><td><font color='#FF0000'>%2</font></td></tr></table>").arg(QDateTime::currentDateTime().toString("(hh:mm:ss)"), sError.replace('<', "&lt;").replace('>', "&gt;"));
		QMyLogging::getInstance()->WriteLog(ERR, sError);
	}
	else
	{
		if (mQuery.isSelect())
		{
			m_iResultTableCount = 0;
			m_lSQLResultTables.clear();

			do
			{
				QSqlRecord sqlRecord = mQuery.record();
				int columns = sqlRecord.count();
				QStandardItemModel* model = new QStandardItemModel();
				model->setColumnCount(columns);

				QStringList headerLabels;
				for (int i = 0; i < columns; i++)
					headerLabels.append(sqlRecord.fieldName(i));
				model->setHorizontalHeaderLabels(headerLabels);
		
				while (mQuery.next())
				{
					QList<QStandardItem*> itemList;
					for (int column = 0; column < columns; column++) 
					{
						QStandardItem *item = new QStandardItem(mQuery.value(column).toString());
						itemList.append(item);
					}
					model->appendRow(itemList);
				}
				m_lSQLResultTables.append(model);
				m_iResultTableCount++;

			} 
			while (mQuery.nextResult());
		}

		int iNumRowsAffected = mQuery.numRowsAffected();
		if (iNumRowsAffected == -1)
		{
			m_sLogText = QString("<table><tr><td><b>%1</b></td><td>%2</td></tr></table>").arg(QDateTime::currentDateTime().toString("(hh:mm:ss)"), "Query executed successfully after " + QString().setNum(mTime.elapsed()) + " ms!");	
			QMyLogging::getInstance()->WriteLog(INFORMATION, QString("Statement executed succssfully after %1 ms").arg(QString().setNum(mTime.elapsed())));
		}
		else
		{
			m_sLogText = QString("<table><tr><td><b>%1</b></td><td>%2</td></tr><tr><td></td><td>%3</td></tr></table>").arg(QDateTime::currentDateTime().toString("(hh:mm:ss)"), "Query executed successfully after " + QString().setNum(mTime.elapsed()) + " ms!", QString().setNum(iNumRowsAffected) + " row(s) affected\n");	
			QMyLogging::getInstance()->WriteLog(INFORMATION, QString("Statement executed succssfully after %1 ms, %2 row(s) affected").arg(QString().setNum(mTime.elapsed()), QString().setNum(iNumRowsAffected)));
		}

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
	m_db = QSqlDatabase::addDatabase("QODBC3", connectionName);
	m_sConnectionName = connectionName;
}

void ODBC_Connection::RestoreGui()
{
	m_ui.SQLCommandTextEdit->setText(m_sCurrentStatement);
	m_ui.SQLLogTextBrowser->setText(m_sLogFile);
	m_ui.SQLLogTextBrowser->verticalScrollBar()->setSliderPosition(m_ui.SQLLogTextBrowser->verticalScrollBar()->maximum());
	m_ui.SQLResultTableView->setModel(NULL);

	LoadTables();

	for (int i = 0, count = m_db.tables().count(); i < count; i++)
	{
		QString sTableName = m_db.tables().value(i);
		QList<QTreeWidgetItem*> lItems = m_ui.TableTreeWidget->findItems(sTableName, Qt::MatchExactly);
		if (lItems.count() > 0)
		{
			QTreeWidgetItem *pItem = lItems.value(0);
			if (pItem == NULL)
				return;

			if (m_lExpandedTables.contains(sTableName))
				m_ui.TableTreeWidget->expandItem(pItem);
		}
	}

	int iStatementCount = m_slStatementHistory.count();
	if (m_iCurrentHistoryIndex < iStatementCount)
		m_ui.SQLCommandTextEdit->setText(m_slStatementHistory.value(m_iCurrentHistoryIndex));
	else
		m_ui.SQLCommandTextEdit->setText("");

	m_ui.CurrentStatementLabel->setText(QString().setNum(m_iCurrentHistoryIndex + 1));

	if (m_ui.SQLCommandTextEdit->toPlainText().isEmpty())
		m_ui.ExecuteToolButton->setDisabled(true);

	if (m_iCurrentHistoryIndex == 0)
	{
		m_ui.LeftToolButton->setDisabled(true);
		if (m_ui.SQLCommandTextEdit->toPlainText().isEmpty())
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

	m_lExpandedTables.clear();
	for (int i = 0, count = m_db.tables().count(); i < count; i++)
	{
		QString sTableName = m_db.tables().value(i);
		QList<QTreeWidgetItem*> lItems = m_ui.TableTreeWidget->findItems(sTableName, Qt::MatchExactly);
		if (lItems.count() > 0)
		{
			QTreeWidgetItem *pItem = lItems.value(0);
			if (pItem == NULL)
				return;

			if (pItem->isExpanded())
				m_lExpandedTables << pItem->text(0);
		}
	}
}

void ODBC_Connection::CloseConnection()
{
	if (mQuery.isActive())
		mQuery.finish();

	if (m_pOwnThread != NULL)
	{
		if (m_pOwnThread->isRunning())
			m_pOwnThread->quit();
	}


    m_db.close();
	m_db = QSqlDatabase();
	QSqlDatabase::removeDatabase(m_sConnectionName);
}
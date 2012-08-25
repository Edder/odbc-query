#ifndef ODBC_CONNECTION_H
#define ODBC_CONNECTION_H

#include "precompiled.h"
#include "ui_ODBC_Query.h"

class ODBC_Connection : public QThread 
{
	public:
		ODBC_Connection(Ui::ODBC_QueryClass ui);
		~ODBC_Connection();

		QString ConnectToDatabase(bool reconnect, QString database = NULL, QString user = NULL, QString password = NULL); 
		void LoadTableColumns(QString tableName);
		void ExecuteQuery(QString query);
		void HandleLeftRightButton(bool directionRight);
		void HandleSQLCommandTextChanged();
		void OpenConnection(QString connectionName);
		void RestoreGui();
		void SaveGui();
		void CloseConnection();
		QString GetConnectionName() { return m_sConnectionName; };
		void SetNextStatement(QString nextStatement) { m_sNextStatement = nextStatement; };
		void SetFirstStatement(QString nextStatement) { m_sNextStatement = nextStatement; };
		bool IsConnectionOpen() { return m_db.isOpen(); };
		QString GetStatementError() { return m_sStatementExecutionError; };

				QSqlQuery *m_pQuery;

	private:
		void run();

		QString m_sDatabase;
		QString m_sUser;
		QString m_sPassword;
		QString m_sConnectionName;
		Ui::ODBC_QueryClass m_ui;
		QSqlDatabase m_db;

		QSortFilterProxyModel *m_pSortModel;
		QSqlQueryModel *m_pSqlQueryModel;
		QString m_sCurrentStatement;
		QString m_sLastSelectStatement;
		QStringList m_slStatementHistory;
		int m_iCurrentHistoryIndex;
		QString m_sLoadedTable;
		QString m_sLogFile;
		QTime mTime;
		QString m_sNextStatement;
		QString m_sStatementExecutionError;
		bool m_bStatementExecuted;

	public slots:
		void Executed();
};

#endif // ODBC_CONNECTION_H
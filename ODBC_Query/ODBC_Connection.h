#ifndef ODBC_CONNECTION_H
#define ODBC_CONNECTION_H

#include "precompiled.h"
#include "ui_ODBC_Query.h"

class ODBC_Connection : public QWidget
{
	Q_OBJECT

	public:
		ODBC_Connection(Ui::ODBC_QueryClass ui, QWidget *parent = 0);
		~ODBC_Connection();

		bool ConnectToDatabase(bool firstConnect, QString database = NULL, QString user = NULL, QString password = NULL); 
		void LoadTableColumns(QString tableName);
		void ExecuteQuery(QString query, bool firstExecute);
		void HandleLeftRightButton(bool directionRight);
		void HandleSQLCommandTextChanged();
		void OpenConnection(QString connectionName);
		void RestoreGui();
		void SaveGui();
		void CloseConnection();
		QString getConnectionName() { return m_sConnectionName; };

	private:
		QString m_sDatabase;
		QString m_sUser;
		QString m_sPassword;
		QString m_sConnectionName;
		Ui::ODBC_QueryClass m_ui;
		QSqlDatabase m_db;
		QSqlQueryModel *m_pSqlQueryModel;
		QString m_sCurrentStatement;
		QString m_sLastSelectStatement;
		QStringList m_slStatementHistory;
		int m_iCurrentHistoryIndex;
		QString m_sLoadedTable;
		QString m_sLogFile;
};

#endif // ODBC_CONNECTION_H
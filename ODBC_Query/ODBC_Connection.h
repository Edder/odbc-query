#ifndef ODBC_CONNECTION_H
#define ODBC_CONNECTION_H

#include "precompiled.h"
#include "ui_ODBC_Query.h"

class ODBC_Connection : public QWidget
{
	Q_OBJECT

	public:
<<<<<<< HEAD
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
=======
		ODBC_Connection(Ui::ODBC_QueryClass ui);
		~ODBC_Connection();

		bool ConnectToDatabase(QString database, QString user, QString password, bool firstConnect); 
		void LoadTableColumns(QString tableName);
		void ExecuteQuery(QString query, bool firstExecute);
		void HandleLeftRightButton(bool directionRight);
		void OpenConnection(QString connectionName);
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
		void CloseConnection();
		QString getConnectionName() { return m_sConnectionName; };

	private:
		QString m_sDatabase;
		QString m_sUser;
		QString m_sPassword;
		QString m_sConnectionName;
		Ui::ODBC_QueryClass m_ui;
		QSqlDatabase m_db;
<<<<<<< HEAD
		QSqlQueryModel *m_pSqlQueryModel;
		QString m_sCurrentStatement;
		QString m_sLastSelectStatement;
=======
		QSqlQuery *m_pQuery;
		QString m_sCurrentStatement;
>>>>>>> 930f78f550971e678d62656160dc4b72ba836ef9
		QStringList m_slStatementHistory;
		int m_iCurrentHistoryIndex;
		QString m_sLoadedTable;
		QString m_sLogFile;
};

#endif // ODBC_CONNECTION_H
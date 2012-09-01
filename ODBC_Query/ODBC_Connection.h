#ifndef ODBC_CONNECTION_H
#define ODBC_CONNECTION_H

#include "precompiled.h"
#include "ui_ODBC_Query.h"

class ODBC_Connection : public QObject 
{
	Q_OBJECT

	public:
		ODBC_Connection(Ui::ODBC_QueryClass ui, QThread* ownThread);
		~ODBC_Connection();

		bool ConnectToDatabase(QString database = NULL, QString user = NULL, QString password = NULL); 
		void LoadTables();
		void LoadTableColumns(QString tableName);
		void HandleLeftRightButton(bool directionRight);
		void HandleSQLCommandTextChanged();
		void OpenConnection(QString connectionName);
		void RestoreGui();
		void SaveGui();
		void CloseConnection();
		bool IsConnectionOpen() { return m_db.isOpen(); };

		// Getter / Setter
		QString GetConnectionName() { return m_sConnectionName; };
		QString GetLogText() { return m_sLogText; };
		QString GetDatabaseError() { return m_sDatabaseError; };
		int GetCurrentHistoryIndex() { return m_iCurrentHistoryIndex; };
		QAbstractItemModel* GetSQLResultTable() { return m_pSQLResultTable; };

	private:
		QString m_sConnectionName;
		Ui::ODBC_QueryClass m_ui;
		QSqlDatabase m_db;
		QSqlQuery* m_pQuery;
		QSqlQueryModel* m_pSqlQueryModel;
		QString m_sCurrentStatement;
		QStringList m_slStatementHistory;
		int m_iCurrentHistoryIndex;
		QString m_sLoadedTable;
		QString m_sLogFile;
		QTime mTime;
		QString m_sLogText;
		QString m_sDatabaseError;
		QThread* m_pOwnThread;
		QAbstractItemModel* m_pSQLResultTable;

	public slots:
		void ExecuteQuery(QString query);
		
	signals:
		void Executed();
};

#endif // ODBC_CONNECTION_H
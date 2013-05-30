#ifndef ODBC_CONNECTION_H
#define ODBC_CONNECTION_H

#include "precompiled.h"
#include "ui_ODBC_Query.h"
#include "ODBC_StandardItemModel.h"

class ODBC_Connection : public QObject 
{
	Q_OBJECT

	public:
		ODBC_Connection(Ui::ODBC_QueryClass ui, QThread* ownThread);
		~ODBC_Connection();

		bool ConnectToDatabase(QString database = NULL, QString user = NULL, QString password = NULL); 
		void LoadTables();
		void LoadTableColumns(QTreeWidgetItem *item);
		void HandleLeftRightButton(bool directionRight);
		void HandleSQLCommandTextChanged();
		void OpenConnection(QString connectionName);
		void RestoreGui();
		void SaveGui();
		void CloseConnection();
		void StopExecution();

		// Getter / Setter
		QString GetConnectionName() { return m_sConnectionName; };
		QString GetLogText() { return m_sLogText; };
		QString GetDatabaseError() { return m_sDatabaseError; };
		int GetCurrentHistoryIndex() { return m_iCurrentHistoryIndex; };
		int GetResultTableCount() { return m_iResultTableCount; };
		ODBC_StandardItemModel* GetSQLResultTable(int index) { return m_lSQLResultTables.count() > 0 ? m_lSQLResultTables[index] : NULL; };
		ODBC_StandardItemModel* GetMainModel() { return m_pMainModel; };
		bool IsConnectionOpen() { return m_db.isOpen(); };
		void SetWaitForAnswer(bool waitForAnswer) { m_bWaitForAnswer = waitForAnswer; };
		void SetContinueFetch(bool continueFetch) { m_bContinueFetch = continueFetch; };

	private:
		QString m_sConnectionName;
		Ui::ODBC_QueryClass m_ui;
		QSqlDatabase m_db;
		QSqlQuery mQuery;
		QString m_sCurrentStatement;
		QStringList m_slStatementHistory;
		int m_iCurrentHistoryIndex;
		int m_iResultTableCount;
		QStringList m_lExpandedTables;
		QString m_sLogFile;
		QTime mTime;
		QString m_sLogText;
		QString m_sDatabaseError;
		QThread* m_pOwnThread;
		QList<ODBC_StandardItemModel*> m_lSQLResultTables;
		ODBC_StandardItemModel* m_pMainModel;
		bool m_bWaitForAnswer;
		bool m_bContinueFetch;

	public slots:
		void ExecuteQuery(QString query);
		
	signals:
		void Executed();
		void LimitReached();
};

#endif // ODBC_CONNECTION_H
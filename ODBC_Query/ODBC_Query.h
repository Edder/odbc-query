#ifndef ODBC_QUERY_H
#define ODBC_QUERY_H

#include "precompiled.h"
#include "ui_ODBC_Query.h"
#include "ODBC_ConnectionDialog.h"
#include "ODBC_Connection.h"
#include "ODBC_CustomSyntaxHighlighter.h"
#include "ODBC_OptionsDialog.h"
#include "ODBC_ResultWindow.h"

#define REVISION 24
#define APPLICATION_NAME "ODBC Query"

class ODBC_Query : public QMainWindow
{
	Q_OBJECT

	public:
		ODBC_Query(QWidget* parent = 0, Qt::WindowFlags flags = 0);
		~ODBC_Query();

	private:	
		void InitGui();
		void ResetGui();
		void DisableQueryToolbar();
		bool SwitchToConnection(ODBC_Connection* connection, QString newConnectionName);
		void CleanResultWindows();
		bool eventFilter(QObject* object, QEvent* event);

		Ui::ODBC_QueryClass ui;
		ODBC_Connection* m_pCurrentConnection;
		QList<ODBC_Connection*> m_lConnections;
		QList<ODBC_ResultWindow*> m_lResultWindows;
		ODBC_CustomSyntaxHighlighter* m_pHighlighter;
		QMovie* m_pLoadingAnimation;
		QLabel* m_pLoadingLabel;

	private slots:
		void ExecuteButtonClicked();
		void LeftButtonClicked();
		void RightButtonClicked();
		void TableItemExpanded(QTreeWidgetItem *item);
		void Exit();
		void NewConnection();
		void RefreshTables();
		void CloseAllConnections(bool close = false);
		void ConnectionsClicked(QAction* action);
		void ShowToolbarTriggered();
		void SyntaxHighlightingTriggered();
		void SQLCommandTextChanged();
		void ShowOptions();
		void ShowAbout();

	public slots:	
		void Executed();
		void LimitReached();

	signals:
		void ExecuteQuery(QString query);
};

#endif // ODBC_QUERY_H

#ifndef ODBC_QUERY_H
#define ODBC_QUERY_H

#include <QtGui/QMainWindow>
#include "ui_ODBC_Query.h"
#include "ODBC_ConnectionDialog.h"
#include "ODBC_Connection.h"
#include "ODBC_CustomSyntaxHighlighter.h"
#include "ODBC_OptionsDialog.h"

#define REVISION 23
#define APPLICATION_NAME "ODBC Query"

class ODBC_Query : public QMainWindow
{
	Q_OBJECT

	public:
		ODBC_Query(QWidget* parent = 0, Qt::WFlags flags = 0);
		~ODBC_Query();

	private:	
		void InitGui();
		void ResetGui();
		void DisableQueryToolbar();
		bool SwitchToConnection(ODBC_Connection* connection, QString newConnectionName);
		bool eventFilter(QObject* object, QEvent* event);

		Ui::ODBC_QueryClass ui;
		ODBC_Connection* m_pCurrentConnection;
		QList<ODBC_Connection*> m_lConnections;
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
		void CloseAllConnections(bool close = false);
		void ConnectionsClicked(QAction* action);
		void ShowToolbarTriggered();
		void SyntaxHighlightingTriggered();
		void SQLCommandTextChanged();
		void ShowOptions();
		void ShowAbout();

	public slots:	
		void Executed();

	signals:
		void ExecuteQuery(QString query);
};

#endif // ODBC_QUERY_H

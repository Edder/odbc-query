#ifndef ODBC_QUERY_H
#define ODBC_QUERY_H

#include <QtGui/QMainWindow>
#include "ui_ODBC_Query.h"
#include "ODBC_ConnectionDialog.h"
#include "ODBC_Connection.h"

class ODBC_Query : public QMainWindow
{
	Q_OBJECT

	public:
		ODBC_Query(QWidget *parent = 0, Qt::WFlags flags = 0);
		~ODBC_Query();

	private:	
		void InitGui();
		void ResetGui();
		void DisableQueryToolbar();
		void SwitchToConnection(ODBC_Connection *connection, QString newConnectionName);
		bool eventFilter(QObject *object, QEvent *event);

		Ui::ODBC_QueryClass ui;
		ODBC_Connection *m_pCurrentConnection;
		QList<ODBC_Connection*> m_lConnections;

	private slots:
		void ExecuteButtonClicked();
		void LeftButtonClicked();
		void RightButtonClicked();
		void TableItemClicked(QTreeWidgetItem *item, int column);
		void Exit();
		void NewConnection();
		void CloseAllConnections(bool close = false);
		void ConnectionsClicked(QAction *action);
		void SQLCommandTextChanged();
};

#endif // ODBC_QUERY_H

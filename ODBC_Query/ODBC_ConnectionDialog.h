#ifndef ODBC_CONNECTION_DIALOG_H
#define ODBC_CONNECTION_DIALOG_H

#include <QtGui/QMainWindow>
#include "ui_ODBC_ConnectionDialog.h"

class ODBC_ConnectionDialog : public QDialog
{
	Q_OBJECT

	public:
		void Init();
		QString getDatabase() { return m_sSelectedDatabase; };
		QString getUsername() { return m_sEnteredUsername; };
		QString getPassword() { return m_sEnteredPassword; };
		bool isSystemDSN() { return m_bSystemDSNSelected; };

	private:
		Ui::Dialog ui;
		QString m_sSelectedDatabase;
		QString m_sEnteredUsername;
		QString m_sEnteredPassword;
		bool m_bSystemDSNSelected;

	private slots:
		void ConnectButtonClicked();
		void CancelButtonClicked();
		void SystemDSNitemClicked(QTreeWidgetItem *item, int column);
		void UserDSNitemClicked(QTreeWidgetItem *item, int column);
};

#endif // ODBC_CONNECTION_DIALOG_H

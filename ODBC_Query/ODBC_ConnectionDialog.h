#ifndef ODBC_CONNECTIONDIALOG_H
#define ODBC_CONNECTIONDIALOG_H

#include <QtGui/QMainWindow>
#include "ui_ODBC_ConnectionDialog.h"

class ODBC_ConnectionDialog : public QDialog
{
	Q_OBJECT

	public:
		void Init();
		bool IsSystemDSN() { return m_bSystemDSNSelected; };
		bool IsValid() { return m_bChoiceMade; };

		// Getter / Setter
		QString GetDatabase() { return m_sSelectedDatabase; };
		QString GetUsername() { return m_sEnteredUsername; };
		QString GetPassword() { return m_sEnteredPassword; };

	private:
		Ui::ConnectionDialog ui;
		QString m_sSelectedDatabase;
		QString m_sEnteredUsername;
		QString m_sEnteredPassword;
		bool m_bChoiceMade;
		bool m_bSystemDSNSelected;

	private slots:
		void ConnectButtonClicked();
		void CancelButtonClicked() { close(); };
		void SystemDSNitemClicked(QTreeWidgetItem *item, int column);
		void UserDSNitemClicked(QTreeWidgetItem *item, int column);
};

#endif // ODBC_CONNECTIONDIALOG_H

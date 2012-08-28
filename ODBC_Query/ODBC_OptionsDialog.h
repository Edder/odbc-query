#ifndef ODBC_OPTIONSDIALOG_H
#define ODBC_OPTIONSDIALOG_H

#include <QtGui/QMainWindow>
#include "ui_ODBC_OptionsDialog.h"

class ODBC_OptionsDialog : public QDialog
{
	Q_OBJECT

	public:
		void Init();
		
		// Getter / Setter
		int GetConnectionTimeout() { return m_iConnectionTimeout; };

	private:
		Ui::OptionsDialog ui;
		int m_iConnectionTimeout;

	private slots:
		void OKButtonClicked();
		void CancelButtonClicked() { close(); };
		void ApplyButtonClicked();
};

#endif // ODBC_OPTIONSDIALOG_H

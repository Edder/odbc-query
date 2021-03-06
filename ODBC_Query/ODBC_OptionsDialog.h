#ifndef ODBC_OPTIONSDIALOG_H
#define ODBC_OPTIONSDIALOG_H

#include "precompiled.h"
#include "ui_ODBC_OptionsDialog.h"

class ODBC_OptionsDialog : public QDialog
{
	Q_OBJECT

	public:
		static ODBC_OptionsDialog* getInstance();
		static void ExitInstance();
		
		void Init();
		
		// Getter / Setter
		int GetConnectionTimeout() { return m_iConnectionTimeout; };
		bool ForwardOnly() { return m_bForwardOnly; };
		bool LimitResults() { return m_bLimitResults; };
		int GetResultLimitCount() { return m_iResultCount; };

	private:
		ODBC_OptionsDialog();
		ODBC_OptionsDialog(ODBC_OptionsDialog const&) { }; 
		ODBC_OptionsDialog& operator=(ODBC_OptionsDialog const&) { };
		static ODBC_OptionsDialog* m_pInstance;

		bool m_bInitialized;
		Ui::OptionsDialog ui;
		int m_iConnectionTimeout;
		bool m_bForwardOnly;
		bool m_bLimitResults;
		int m_iResultCount;

	private slots:
		void OKButtonClicked();
		void CancelButtonClicked() { close(); };
		void ApplyButtonClicked();
};

#endif // ODBC_OPTIONSDIALOG_H

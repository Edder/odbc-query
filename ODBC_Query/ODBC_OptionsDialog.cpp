#include "precompiled.h"
#include "ODBC_OptionsDialog.h"

ODBC_OptionsDialog::ODBC_OptionsDialog()
{
	m_bInitialized = false;
}

ODBC_OptionsDialog* ODBC_OptionsDialog::m_pInstance = NULL; 

ODBC_OptionsDialog* ODBC_OptionsDialog::getInstance()
{
	if (!m_pInstance)
		m_pInstance = new ODBC_OptionsDialog;
	return m_pInstance;
}

void ODBC_OptionsDialog::Init()
{
	ui.setupUi(this);

	// remove the ? in the titlebar
	Qt::WindowFlags flags = windowFlags();
	Qt::WindowFlags helpFlag = Qt::WindowContextHelpButtonHint;
	flags = flags & (~helpFlag);
	setWindowFlags(flags);

	QSettings Settings("settings.ini", QSettings::IniFormat, this);
	Settings.beginGroup("connection");
	if (Settings.contains("timeout")) // get the value
		m_iConnectionTimeout = Settings.value("timeout").toInt();
	else // set the default value
	{
		Settings.setValue("timeout", 3);
		m_iConnectionTimeout = 3;
	}
	Settings.endGroup();
	Settings.beginGroup("statements");
	if (Settings.contains("forwardonly")) // get the value
		m_bForwardOnly = Settings.value("forwardonly").toBool();
	else // set the default value
	{
		Settings.setValue("forwardonly", true);
		m_bForwardOnly = true;
	}
	if (Settings.contains("limitresults")) // get the value
		m_bLimitResults = Settings.value("limitresults").toBool();
	else // set the default value
	{
		Settings.setValue("limitresults", true);
		m_bLimitResults = true;
	}
	Settings.endGroup();
	if (Settings.contains("resultcount")) // get the value
		m_iResultCount = Settings.value("resultcount").toInt();
	else // set the default value
	{
		Settings.setValue("resultcount", 2000);
		m_iResultCount = 2000;
	}
	Settings.endGroup();

	ui.TimeoutSpinBox->setValue(m_iConnectionTimeout);
	ui.ForwardOnlyCheckBox->setChecked(m_bForwardOnly);
	ui.LimitResultsCheckBox->setChecked(m_bLimitResults);

	QObject::connect(ui.OKButton, SIGNAL(clicked()), SLOT(OKButtonClicked()));
	QObject::connect(ui.CancelButton, SIGNAL(clicked()), SLOT(CancelButtonClicked()));
	QObject::connect(ui.ApplyButton, SIGNAL(clicked()), SLOT(ApplyButtonClicked()));
}

void ODBC_OptionsDialog::OKButtonClicked()
{
	ApplyButtonClicked();
	close();
}

void ODBC_OptionsDialog::ApplyButtonClicked()
{
	m_iConnectionTimeout = ui.TimeoutSpinBox->value();
	m_bForwardOnly = ui.ForwardOnlyCheckBox->isChecked();
	QSettings Settings("settings.ini", QSettings::IniFormat, this);
	Settings.beginGroup("connection");
	Settings.setValue("timeout", m_iConnectionTimeout);
	Settings.endGroup();
	Settings.beginGroup("statements");
	Settings.setValue("forwardonly", m_bForwardOnly);
	Settings.endGroup();
}

void ODBC_OptionsDialog::ExitInstance()
{
	delete m_pInstance;
	m_pInstance = NULL;
}
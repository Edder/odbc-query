#include "precompiled.h"
#include "ODBC_OptionsDialog.h"

void ODBC_OptionsDialog::Init()
{
	ui.setupUi(this);

	// remove the ? in the titlebar
	Qt::WindowFlags flags = windowFlags();
	Qt::WindowFlags helpFlag = Qt::WindowContextHelpButtonHint;
	flags = flags & (~helpFlag);
	setWindowFlags(flags);

	QObject::connect(ui.OKButton, SIGNAL(clicked()), SLOT(OKButtonClicked()));
	QObject::connect(ui.CancelButton, SIGNAL(clicked()), SLOT(CancelButtonClicked()));
	QObject::connect(ui.ApplyButton, SIGNAL(clicked()), SLOT(ApplyButtonClicked()));
}

void ODBC_OptionsDialog::OKButtonClicked()
{

}

void ODBC_OptionsDialog::ApplyButtonClicked()
{

}
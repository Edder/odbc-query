#include "precompiled.h"
#include "ODBC_ConnectionDialog.h"

void ODBC_ConnectionDialog::Init()
{
	ui.setupUi(this);

	// remove the ? in the titlebar
	Qt::WindowFlags flags = windowFlags();
	Qt::WindowFlags helpFlag = Qt::WindowContextHelpButtonHint;
	flags = flags & (~helpFlag);
	setWindowFlags(flags);

	m_bChoiceMade = false;
	m_bClosed = false;

	QObject::connect(ui.ConnectButton, SIGNAL(clicked()), SLOT(ConnectButtonClicked()));
	QObject::connect(ui.CancelButton, SIGNAL(clicked()), SLOT(CancelButtonClicked()));
	QObject::connect(ui.SystemDSNTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), SLOT(SystemDSNitemClicked(QTreeWidgetItem*, int)));
	QObject::connect(ui.UserDSNTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), SLOT(UserDSNitemClicked(QTreeWidgetItem*, int)));

	// look for system DSN
	QSettings SystemDSN("HKEY_LOCAL_MACHINE\\SOFTWARE\\ODBC\\ODBC.INI\\ODBC Data Sources", QSettings::NativeFormat);
	QStringList SystemDSNList = SystemDSN.allKeys();

	ui.SystemDSNTreeWidget->setHeaderLabels(QStringList() << "Name" << "Driver");

	for (int i = 0, count = SystemDSNList.count(); i < count; i++)
		ui.SystemDSNTreeWidget->addTopLevelItem(new QTreeWidgetItem(QStringList() << SystemDSNList.value(i) << SystemDSN.value(SystemDSNList.value(i)).toString()));

	// look for user DSN
	QSettings UserDSN("HKEY_CURRENT_USER\\SOFTWARE\\ODBC\\ODBC.INI\\ODBC Data Sources", QSettings::NativeFormat);
	QStringList UserDSNList = UserDSN.allKeys();

	ui.UserDSNTreeWidget->setHeaderLabels(QStringList() << "Name" << "Driver");

	for (int i = 0, count = UserDSNList.count(); i < count; i++)
		ui.UserDSNTreeWidget->addTopLevelItem(new QTreeWidgetItem(QStringList() << UserDSNList.value(i) << UserDSN.value(UserDSNList.value(i)).toString()));
}

void ODBC_ConnectionDialog::Reset()
{
	m_bChoiceMade = false;
	m_bClosed = false;
}

void ODBC_ConnectionDialog::ConnectButtonClicked()
{	
	if (m_sSelectedDatabase.isEmpty())
	{
		QMessageBox::information(this, "Database selection", "You need to select a ODBC Data Source to connect!", QMessageBox::Ok);
		return;
	}

	m_sEnteredUsername = ui.UsernameLineEdit->text();
	m_sEnteredPassword = ui.PasswordLineEdit->text();

	QSettings Login("login.ini", QSettings::IniFormat, this);
	Login.beginGroup(QString("%1 (%2)").arg(m_sSelectedDatabase, m_bSystemDSNSelected ? "System" : "User"));
	if (ui.RememberCheckBox->checkState() == Qt::Checked)
	{
		Login.setValue("user", m_sEnteredUsername);
		Login.setValue("password", m_sEnteredPassword);
	}
	else
		Login.remove("");
	Login.endGroup();

	m_bChoiceMade = true;

	close();
}

void ODBC_ConnectionDialog::SystemDSNitemClicked(QTreeWidgetItem *item, int column)
{
	ui.UserDSNTreeWidget->clearSelection();
	m_sSelectedDatabase = item->text(0);
	m_bSystemDSNSelected = true;

	QSettings Login("login.ini", QSettings::IniFormat, this);
	Login.beginGroup(QString("%1 (System)").arg(m_sSelectedDatabase));
	if (Login.contains("user") && Login.contains("password"))
	{
		ui.RememberCheckBox->setChecked(true);
		ui.UsernameLineEdit->setText(Login.value("user").toString());
		ui.PasswordLineEdit->setText(Login.value("password").toString());
	}
	else
	{
		ui.RememberCheckBox->setChecked(false);
		ui.UsernameLineEdit->clear();
		ui.PasswordLineEdit->clear();
	}
	Login.endGroup();
}

void ODBC_ConnectionDialog::UserDSNitemClicked(QTreeWidgetItem *item, int column)
{
	ui.SystemDSNTreeWidget->clearSelection();
	m_sSelectedDatabase = item->text(0);
	m_bSystemDSNSelected = false;

	QSettings Login("login.ini", QSettings::IniFormat, this);
	Login.beginGroup(QString("%1 (User)").arg(m_sSelectedDatabase));
	if (Login.contains("user") && Login.contains("password"))
	{
		ui.RememberCheckBox->setChecked(true);
		ui.UsernameLineEdit->setText(Login.value("user").toString());
		ui.PasswordLineEdit->setText(Login.value("password").toString());
	}
	else
	{
		ui.RememberCheckBox->setChecked(false);
		ui.UsernameLineEdit->clear();
		ui.PasswordLineEdit->clear();
	}
	Login.endGroup();
}

void ODBC_ConnectionDialog::close()
{ 
	if (!m_bChoiceMade) 
		m_bClosed = true; 
	QDialog::close(); 
};
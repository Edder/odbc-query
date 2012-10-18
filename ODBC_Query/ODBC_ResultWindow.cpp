#include "precompiled.h"
#include "ODBC_ResultWindow.h"
#include "ODBC_Query.h"

void ODBC_ResultWindow::Init(int iResultCount, QStandardItemModel* pResultTable)
{
	ui.setupUi(this);

	this->setWindowTitle(QString("%1 - Result %2").arg(APPLICATION_NAME, QString().setNum(iResultCount)));

	ui.ResultCountLabel->setText(QString("Rows: %1").arg(pResultTable->rowCount()));

	ui.SQLResultTableView->setModel(pResultTable);
	ui.SQLResultTableView->sortByColumn(-1, Qt::AscendingOrder);
	ui.SQLResultTableView->verticalScrollBar()->setSliderPosition(ui.SQLResultTableView->verticalScrollBar()->minimum());
	ui.SQLResultTableView->horizontalScrollBar()->setSliderPosition(ui.SQLResultTableView->horizontalScrollBar()->minimum());

	//// remove the ? in the titlebar
	//Qt::WindowFlags flags = windowFlags();
	//Qt::WindowFlags helpFlag = Qt::WindowContextHelpButtonHint;
	//flags = flags & (~helpFlag);
	//setWindowFlags(flags);
}
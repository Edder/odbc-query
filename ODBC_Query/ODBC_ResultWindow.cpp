#include "precompiled.h"
#include "ODBC_ResultWindow.h"
#include "ODBC_Query.h"

void ODBC_ResultWindow::Init(int iResultCount, QString sDSN, ODBC_StandardItemModel* pResultTable)
{
	m_pResultTable = pResultTable;

	ui.setupUi(this);

	this->setWindowTitle(QString("%1 - Result %2").arg(APPLICATION_NAME, QString().setNum(iResultCount)));

	ui.ResultCountLabel->setText(QString("Rows: %1").arg(m_pResultTable->rowCount()));
	ui.DSNLabel->setText(QString("DSN: %1").arg(sDSN));

	ui.SQLResultTableView->setModel(m_pResultTable);
	ui.SQLResultTableView->sortByColumn(-1, Qt::AscendingOrder);
	ui.SQLResultTableView->verticalScrollBar()->setSliderPosition(ui.SQLResultTableView->verticalScrollBar()->minimum());
	ui.SQLResultTableView->horizontalScrollBar()->setSliderPosition(ui.SQLResultTableView->horizontalScrollBar()->minimum());

	//// remove the ? in the titlebar
	//Qt::WindowFlags flags = windowFlags();
	//Qt::WindowFlags helpFlag = Qt::WindowContextHelpButtonHint;
	//flags = flags & (~helpFlag);
	//setWindowFlags(flags);
}

void ODBC_ResultWindow::Clean()
{
	if (m_pResultTable != NULL)
	{
		if (m_pResultTable->IsMainModel())
			return;

		delete m_pResultTable;
		m_pResultTable = NULL;
	}
}
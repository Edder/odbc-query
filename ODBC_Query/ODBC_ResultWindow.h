#ifndef ODBC_RESULTWINDOW_H
#define ODBC_RESULTWINDOW_H

#include "precompiled.h"
#include "ui_ODBC_ResultWindow.h"

class ODBC_ResultWindow : public QWidget
{
	public:
		void Init(int iResultCount, QStandardItemModel* pResultTable);

	private:
		Ui::ResultWindow ui;
};

#endif // ODBC_RESULTWINDOW_H
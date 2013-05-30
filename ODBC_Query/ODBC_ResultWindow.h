#ifndef ODBC_RESULTWINDOW_H
#define ODBC_RESULTWINDOW_H

#include "precompiled.h"
#include "ui_ODBC_ResultWindow.h"
#include "ODBC_StandardItemModel.h"

class ODBC_ResultWindow : public QWidget
{
	public:
		void Init(int iResultCount, ODBC_StandardItemModel* pResultTable);
		ODBC_StandardItemModel* GetModel() { return m_pResultTable; };
		void Clean();

	private:
		Ui::ResultWindow ui;
		ODBC_StandardItemModel* m_pResultTable;
};

#endif // ODBC_RESULTWINDOW_H
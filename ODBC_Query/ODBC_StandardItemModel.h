#ifndef ODBC_STANDARDITEMMODEL_H
#define ODBC_STANDARDITEMMODEL_H

#include "precompiled.h"

class ODBC_StandardItemModel : public QStandardItemModel
{
	public:
		ODBC_StandardItemModel() : QStandardItemModel() { m_bExtracted = false; m_bMainModel = false; };
		bool IsExtracted() { return m_bExtracted; };
		bool IsMainModel() { return m_bMainModel; };
		void SetExtracted(bool extracted) { m_bExtracted = extracted; };
		void SetMainModel(bool main) { m_bMainModel = main; };

	private:
		bool m_bExtracted;
		bool m_bMainModel;

};

#endif // ODBC_STANDARDITEMMODEL_H
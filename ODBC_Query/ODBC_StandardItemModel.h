#ifndef ODBC_STANDARDITEMMODEL_H
#define ODBC_STANDARDITEMMODEL_H

#include "precompiled.h"

class ODBC_StandardItemModel : public QStandardItemModel
{
	public:
		ODBC_StandardItemModel() : QStandardItemModel() { m_bExtracted = false; };
		bool IsExtracted() { return m_bExtracted; };
		void SetExtracted(bool extracted) { m_bExtracted = extracted; };

	private:
		bool m_bExtracted;

};

#endif // ODBC_STANDARDITEMMODEL_H
#ifndef ODBC_LOGGING_H
#define ODBC_LOGGING_H

#include "precompiled.h"

enum LOG_TYPE
{
	INFORMATION,
	WARNING,
	ERROR,
	CRITICAL,
};

class ODBC_Logging
{
	public:
		static ODBC_Logging* getInstance();
		static void ExitInstance();

		bool Init();
		void Close();
		void WriteLog(int logtype, QString text);

	private:
		ODBC_Logging();
		ODBC_Logging(ODBC_Logging const&) { }; 
		ODBC_Logging& operator=(ODBC_Logging const&) { };
		static ODBC_Logging* m_pInstance;

		bool m_bInitialized;
		QFile mFile;
};

#endif // ODBC_LOGGING_H
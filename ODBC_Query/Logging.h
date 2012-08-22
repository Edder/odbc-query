#ifndef LOGGING_H
#define LOGGING_H

#include "precompiled.h"

enum LOG_TYPE
{
	INFORMATION,
	WARNING,
	ERROR,
	CRITICAL,
};

class Logging
{
	public:
		static Logging* getInstance();

		bool Init();
		void Close();
		void WriteLog(int logtype, QString text);

	private:
		Logging();
		Logging(Logging const&) { }; 
		Logging& operator=(Logging const&) { };
		static Logging* m_pInstance;

		bool m_bInitialized;
		QFile mFile;
};

#endif // LOGGING_H
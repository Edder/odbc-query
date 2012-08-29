#include "precompiled.h"
#include "ODBC_Logging.h"

ODBC_Logging::ODBC_Logging()
{
	m_bInitialized = false;
}

ODBC_Logging* ODBC_Logging::m_pInstance = NULL; 

ODBC_Logging* ODBC_Logging::getInstance()
{
	if (!m_pInstance)
		m_pInstance = new ODBC_Logging;
	return m_pInstance;
}

bool ODBC_Logging::Init()
{
	if (m_bInitialized)
		return false;

	if (!QDir("logs").exists())
		QDir().mkdir("logs");

	QDateTime timestamp = QDateTime::currentDateTime();
	mFile.setFileName(QString("logs/%1 %2.log").arg(timestamp.toString("dd.MM.yyyy"), QCoreApplication::applicationName()));
	if (mFile.open(QIODevice::ReadWrite | QIODevice::Append |QIODevice::Text))
	{
		if (mFile.size() != 0)
		{
			mFile.write("\n\n");
			mFile.flush();
		}
		m_bInitialized = true;
		return true;
	}
	else
		return false;
}

void ODBC_Logging::Close()
{
	if (!m_bInitialized)
		return;

	mFile.close();

	m_bInitialized = false;
}

void ODBC_Logging::WriteLog(int logtype, QString text)
{
	QDateTime timestamp = QDateTime::currentDateTime();
	if (!m_bInitialized)
	{
		#ifdef _DEBUG
		qDebug() << QString("(%1) %2").arg(timestamp.toString("dd.MM.yyyy"), "Attempted to write to logfile while it wasn't open!");
		#endif
		return;
	}
	QString sLogtype;
	switch (logtype)
	{
		case INFORMATION:
			sLogtype = "INFORMATION";
			break;
		case WARNING:
			sLogtype = "WARNING";
			break;
		case ERROR:
			sLogtype = "ERROR";
			break;
		case CRITICAL:
			sLogtype = "CRITICAL";
			break;
		default:
			sLogtype = "?";
			#ifdef _DEBUG
			qDebug() << QString("(%1) %2").arg(timestamp.toString("dd.MM.yyyy - hh:mm:ss"), "Unknown Logtype used!");
			#endif
			break;
	}
	mFile.write(QString("(%1) %2: %3\n").arg(timestamp.toString("dd.MM.yyyy - hh:mm:ss"), sLogtype, text).toAscii());
	mFile.flush();
}

void ODBC_Logging::ExitInstance()
{
	delete m_pInstance;
	m_pInstance = NULL;
}
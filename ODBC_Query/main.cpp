#include "precompiled.h"
#include "odbc_query.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ODBC_Query w;
	w.show();
	return a.exec();
}

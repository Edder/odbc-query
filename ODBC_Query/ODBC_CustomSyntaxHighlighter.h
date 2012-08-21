#include "precompiled.h"

class ODBC_CustomSyntaxHighlighter: public QSyntaxHighlighter
{   
	public:    
		ODBC_CustomSyntaxHighlighter(QTextDocument* document): QSyntaxHighlighter(document) { };
		~ODBC_CustomSyntaxHighlighter() { };
	
		void highlightBlock(const QString &text)
		{  
			enum 
			{ 
				NormalState = 0, 
				TextFieldState = 1
			};

			int state = previousBlockState();
			int start = 0;
    
			for (int i = 0; i < text.length(); ++i) 
			{     
				if (state == TextFieldState) 
				{
					if (text.mid(i, 1) == "'") 
					{
						state = NormalState;
						setFormat((i + 1), (text.length() - i), Qt::black);
					}
				}
				else 
				{
					if (text.mid(i, 1) == "'") 
					{
						start = i;
						state = TextFieldState;
						setFormat(start, (text.length() - i), Qt::red);
					}

					for (int j = 0, count = keywords.count(); j < count; j++)
					{
						int length = keywords.value(j).length();
						if (text.mid(i, length).toUpper() == keywords.value(j)) 
						{
							if (i == 0)
							{
								if (text.mid((i + length), 1) == " " || text.length() == length)
									setFormat(i, length, Qt::blue);	
							}
							else
							{
								if (text.mid((i - 1), 1) == " " && text.mid((i + length), 1) == " " || text.mid((i - 1), 1) == " " && text.length() == (i + length))
									setFormat(i, length, Qt::blue);	
							}
						}
					}

					for (int j = 0, count = functions.count(); j < count; j++)
					{
						int length = functions.value(j).length();
						if (text.mid(i, length).toUpper() == functions.value(j)) 
						{
							if (i == 0)
							{
								if (text.mid((i + length), 1) == "(")
									setFormat(i, length, Qt::magenta);	
							}
							else
							{
								if (text.mid((i - 1), 1) == " " && text.mid((i + length), 1) == "(")
									setFormat(i, length, Qt::magenta);	
							}
						}
					}

					for (int j = 0, count = operators.count(); j < count; j++)
					{
						int length = operators.value(j).length();
						if (text.mid(i, length).toUpper() == operators.value(j)) 
						{
							if (i == 0)
							{
								if (text.mid((i + length), 1) == " " || text.length() == length)
									setFormat(i, length, Qt::green);	
							}
							else
							{
								if (text.mid((i - 1), 1) == " " && text.mid((i + length), 1) == " " || text.mid((i - 1), 1) == " " && text.length() == (i + length))
									setFormat(i, length, Qt::green);	
							}
						}
					}
				}
			}  
		};

		void Init()
		{
			keywords << "ABSOLUTE" << "ACTION" << "ADD" << "AFTER" << "ALTER" << "AS" << "ASC" << "AT" << "AUTHORIZATION" << "BEGIN" << "BIGINT" <<
							"BINARY" << "BIT" << "BY" << "CASCADE" << "CHAR" << "CHARACTER" << "CHECK" << "CHECKPOINT" << "CLOSE" << "COLLATE" <<
							"COLUMN" << "COMMIT" << "COMMITTED" << "CONNECT" << "CONNECTION" << "CONSTRAINT" << "CONTAINS" << "CONTINUE" <<
							"CREATE" << "CUBE" << "CURRENT" << "CURRENT_DATE" << "CURRENT_TIME" << "CURSOR" << "DATABASE" << "DATE" <<
							"DEALLOCATE" << "DEC" << "DECIMAL" << "DECLARE" << "DEFAULT" << "DELETE" << "DESC" << "DISTINCT" << "DOUBLE" << "DROP" <<
							"DYNAMIC" << "ELSE" << "END" << "END-EXEC" << "ESCAPE" << "EXCEPT" << "EXEC" << "EXECUTE" << "FALSE" << "FETCH" << "FIRST" <<
							"FLOAT" << "FOR" << "FORCE" << "FOREIGN" << "FORWARD" << "FREE" << "FROM" << "FULL" << "FUNCTION" << "GLOBAL" << "GOTO" << "GRANT" <<
							"GROUP" << "GROUPING" << "HAVING" << "HOUR" << "IGNORE" << "INDEX" << "INNER" << "INSENSITIVE" << "INSERT" << "INSTEAD" <<
							"INT" << "INTEGER" << "INTERSECT" << "INTO" << "IS" << "ISOLATION" << "KEY" << "LAST" << "LEVEL" << "LOAD" << "LOCAL" << "MAX" << "MIN" <<
							"MINUTE" << "MODIFY" << "MOVE" << "NAME" << "NATIONAL" << "NCHAR" << "NEXT" << "NO" << "NUMERIC" << "OF" << "OFF" << "ON" << "ONLY" <<
							"OPEN" << "OPTION" << "ORDER" << "OUT" << "OUTPUT" << "PARTIAL" << "PASSWORD" << "PRECISION" << "PREPARE" << "PRIMARY" <<
							"PRIOR" << "PRIVILEGES" << "PROCEDURE" << "PUBLIC" << "READ" << "REAL" << "REFERENCES" << "RELATIVE" << "REPEATABLE" <<
							"RESTRICT" << "RETURN" << "RETURNS" << "REVOKE" << "ROLLBACK" << "ROLLUP" << "ROWS" << "RULE" << "SCHEMA" << "SCROLL" <<
							"SECOND" << "SECTION" << "SELECT" << "SEQUENCE" << "SERIALIZABLE" << "SET" << "SIZE" << "SMALLINT" << "STATIC" <<
							"STATISTICS" << "TABLE" << "TEMP" << "TEMPORARY" << "THEN" << "TIME" << "TIMESTAMP" << "TO" << "TOP" << "TRANSACTION" <<
							"TRANSLATION" << "TRIGGER" << "TRUE" << "TRUNCATE" << "UNCOMMITTED" << "UNION" << "UNIQUE" << "UPDATE" << "VALUES" <<
							"VARCHAR" << "VARYING" << "VIEW" << "WHEN" << "WHERE" << "WITH" << "WORK";
			functions << "ABS" << "AVG" << "CASE" << "CAST" << "COALESCE" << "CONVERT" << "COUNT" << "CURRENT_TIMESTAMP" << 
							"CURRENT_USER" << "DAY" << "ISNULL" << "LEFT" << "LOWER" << "MONTH" << "NULLIF" << "REPLACE" << "RIGHT" << 
							"SESSION_USER" << "SPACE" << "SUBSTRING" << "SUM" << "SYSTEM_USER" << "UPPER" << "USER" << "YEAR";
			operators << "ALL" << "AND" << "ANY" << "BETWEEN" << "CROSS" << "IN" << "JOIN" << "LIKE" << "NOT" << "NULL" << "OR" << "OUTER" << "SOME";
		}

	private:
		QStringList keywords;
		QStringList functions;
		QStringList operators;
};
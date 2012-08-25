#include "precompiled.h"

class ODBC_CustomSyntaxHighlighter: public QSyntaxHighlighter
{   
	public:    
		ODBC_CustomSyntaxHighlighter(QTextDocument* document): QSyntaxHighlighter(document) { };
		~ODBC_CustomSyntaxHighlighter() { };
	
		void SetActive(bool active) { m_bActive = active; };
		bool IsActive() { return m_bActive; };
		void highlightBlock(const QString &text)
		{  
			if (!m_bActive)
			{
				setFormat(0, text.length(), Qt::black);
				return;
			}

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

					for (int j = 0, count = m_lKeywords.count(); j < count; j++)
					{
						int length = m_lKeywords.value(j).length();
						if (text.mid(i, length).toUpper() == m_lKeywords.value(j)) 
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

					for (int j = 0, count = m_lFunctions.count(); j < count; j++)
					{
						int length = m_lFunctions.value(j).length();
						if (text.mid(i, length).toUpper() == m_lFunctions.value(j)) 
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

					for (int j = 0, count = m_lOperators.count(); j < count; j++)
					{
						int length = m_lOperators.value(j).length();
						if (text.mid(i, length).toUpper() == m_lOperators.value(j)) 
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
			m_lKeywords << "ABSOLUTE" << "ACTION" << "ADD" << "AFTER" << "ALTER" << "AS" << "ASC" << "AT" << "AUTHORIZATION" << "BEGIN" << "BIGINT" <<
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
			m_lFunctions << "ABS" << "AVG" << "CASE" << "CAST" << "COALESCE" << "CONVERT" << "COUNT" << "CURRENT_TIMESTAMP" << 
							"CURRENT_USER" << "DAY" << "ISNULL" << "LEFT" << "LOWER" << "MONTH" << "NULLIF" << "REPLACE" << "RIGHT" << 
							"SESSION_USER" << "SPACE" << "SUBSTRING" << "SUM" << "SYSTEM_USER" << "UPPER" << "USER" << "YEAR";
			m_lOperators << "ALL" << "AND" << "ANY" << "BETWEEN" << "CROSS" << "IN" << "JOIN" << "LIKE" << "NOT" << "NULL" << "OR" << "OUTER" << "SOME";
		
			m_bActive = true;
		}

	private:
		QStringList m_lKeywords;
		QStringList m_lFunctions;
		QStringList m_lOperators;
		bool m_bActive;
};
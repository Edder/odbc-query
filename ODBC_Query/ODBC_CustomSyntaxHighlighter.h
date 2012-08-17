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

					for (int j = 0, count = blueKeywords.count(); j < count; j++)
					{
						int length = blueKeywords.value(j).length();
						if (text.mid(i, length).toUpper() == blueKeywords.value(j)) 
						{
							if (i == 0)
							{
								if (text.mid((i + length), 1) == " ")
									setFormat(i, length, Qt::blue);	
							}
							else
							{
								if (text.mid((i - 1), 1) == " " && text.mid((i + length), 1) == " ")
									setFormat(i, length, Qt::blue);	
							}
						}
					}

					for (int j = 0, count = magentaKeywords.count(); j < count; j++)
					{
						int length = magentaKeywords.value(j).length();
						if (text.mid(i, length).toUpper() == magentaKeywords.value(j)) 
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
				}
			}  
		};

		void Init()
		{
			blueKeywords << "SELECT" << "UPDATE" << "INSERT" << "DELETE" << "FROM" << "WHERE" << "AS";
			magentaKeywords << "COUNT";
		}

	private:
		QStringList blueKeywords;
		QStringList magentaKeywords;
};
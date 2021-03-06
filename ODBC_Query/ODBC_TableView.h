#ifndef ODBC_TABLEVIEW_H
#define ODBC_TABLEVIEW_H

#include "precompiled.h"

class ODBC_TableView : public QTableView
{
	Q_OBJECT

	public:
		ODBC_TableView(QWidget *parent) : QTableView(parent) { };
	
	protected:
		void keyPressEvent(QKeyEvent *event)
		{
			if (event->matches(QKeySequence::Copy))
			{
				QAbstractItemModel *abmodel = this->model();
				QItemSelectionModel *model = this->selectionModel();
				QModelIndexList list = model->selectedIndexes();

				qSort(list);

				QString copy_table;

				if(list.size() == 1)
					copy_table = abmodel->data(list.value(0)).toString();
				else if (list.size() > 1)
				{
					QModelIndex last = list.last();
					QModelIndex previous = list.first();

					list.removeFirst();

					for(int i = 0; i < list.size(); i++)
					{
						QVariant data = abmodel->data(previous);
						QString text = data.toString();

						QModelIndex index = list.at(i);
						copy_table.append(text);

						if(index.row() != previous.row())
							copy_table.append('\n');
						else
							copy_table.append('\t');
						previous = index;
					}

					copy_table.append(abmodel->data(list.last()).toString());
					copy_table.append('\n');
				}
				else
					return;

				QClipboard *clipboard = QApplication::clipboard();
				clipboard->setText(copy_table);
			}
			else
				QTableView::keyPressEvent(event);
		};
};

#endif // ODBC_TABLEVIEW_H


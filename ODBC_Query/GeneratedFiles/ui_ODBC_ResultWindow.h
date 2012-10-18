/********************************************************************************
** Form generated from reading UI file 'ODBC_ResultWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ODBC_RESULTWINDOW_H
#define UI_ODBC_RESULTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "ODBC_TableView.h"

QT_BEGIN_NAMESPACE

class Ui_ResultWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *ResultCountLabel;
    ODBC_TableView *SQLResultTableView;

    void setupUi(QWidget *ResultWindow)
    {
        if (ResultWindow->objectName().isEmpty())
            ResultWindow->setObjectName(QStringLiteral("ResultWindow"));
        ResultWindow->resize(685, 451);
        verticalLayout = new QVBoxLayout(ResultWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        ResultCountLabel = new QLabel(ResultWindow);
        ResultCountLabel->setObjectName(QStringLiteral("ResultCountLabel"));
        ResultCountLabel->setMargin(3);

        verticalLayout->addWidget(ResultCountLabel);

        SQLResultTableView = new ODBC_TableView(ResultWindow);
        SQLResultTableView->setObjectName(QStringLiteral("SQLResultTableView"));
        QFont font;
        font.setPointSize(8);
        font.setKerning(true);
        SQLResultTableView->setFont(font);
        SQLResultTableView->viewport()->setProperty("cursor", QVariant(QCursor(Qt::ArrowCursor)));
        SQLResultTableView->setFrameShape(QFrame::StyledPanel);
        SQLResultTableView->setFrameShadow(QFrame::Sunken);
        SQLResultTableView->setMidLineWidth(1);
        SQLResultTableView->setAlternatingRowColors(true);
        SQLResultTableView->setSortingEnabled(true);
        SQLResultTableView->verticalHeader()->setDefaultSectionSize(20);

        verticalLayout->addWidget(SQLResultTableView);


        retranslateUi(ResultWindow);

        QMetaObject::connectSlotsByName(ResultWindow);
    } // setupUi

    void retranslateUi(QWidget *ResultWindow)
    {
        ResultWindow->setWindowTitle(QApplication::translate("ResultWindow", "Form", 0));
        ResultCountLabel->setText(QApplication::translate("ResultWindow", "Rows: ", 0));
    } // retranslateUi

};

namespace Ui {
    class ResultWindow: public Ui_ResultWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ODBC_RESULTWINDOW_H

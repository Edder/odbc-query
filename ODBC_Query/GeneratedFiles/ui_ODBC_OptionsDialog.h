/********************************************************************************
** Form generated from reading UI file 'ODBC_OptionsDialog.ui'
**
** Created: Tue 28. Aug 21:37:31 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ODBC_OPTIONSDIALOG_H
#define UI_ODBC_OPTIONSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OptionsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *OptionsTabWidget;
    QWidget *ConnectionTab;
    QFormLayout *formLayout;
    QVBoxLayout *VerticalLayout;
    QHBoxLayout *HorizontalLayout;
    QLabel *label;
    QSpinBox *spinBox;
    QSpacerItem *horizontalSpacer;
    QWidget *StatementsTab;
    QHBoxLayout *MainHorizontalLayout;
    QPushButton *OKButton;
    QPushButton *CancelButton;
    QPushButton *ApplyButton;

    void setupUi(QDialog *OptionsDialog)
    {
        if (OptionsDialog->objectName().isEmpty())
            OptionsDialog->setObjectName(QString::fromUtf8("OptionsDialog"));
        OptionsDialog->resize(400, 299);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ODBC_Query/Resources/options.png"), QSize(), QIcon::Normal, QIcon::Off);
        OptionsDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(OptionsDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        OptionsTabWidget = new QTabWidget(OptionsDialog);
        OptionsTabWidget->setObjectName(QString::fromUtf8("OptionsTabWidget"));
        ConnectionTab = new QWidget();
        ConnectionTab->setObjectName(QString::fromUtf8("ConnectionTab"));
        formLayout = new QFormLayout(ConnectionTab);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setContentsMargins(5, 5, 9, -1);
        VerticalLayout = new QVBoxLayout();
        VerticalLayout->setSpacing(6);
        VerticalLayout->setObjectName(QString::fromUtf8("VerticalLayout"));
        HorizontalLayout = new QHBoxLayout();
        HorizontalLayout->setSpacing(6);
        HorizontalLayout->setObjectName(QString::fromUtf8("HorizontalLayout"));
        label = new QLabel(ConnectionTab);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setTextFormat(Qt::AutoText);

        HorizontalLayout->addWidget(label);

        spinBox = new QSpinBox(ConnectionTab);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        HorizontalLayout->addWidget(spinBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayout->addItem(horizontalSpacer);


        VerticalLayout->addLayout(HorizontalLayout);


        formLayout->setLayout(1, QFormLayout::FieldRole, VerticalLayout);

        OptionsTabWidget->addTab(ConnectionTab, QString());
        StatementsTab = new QWidget();
        StatementsTab->setObjectName(QString::fromUtf8("StatementsTab"));
        OptionsTabWidget->addTab(StatementsTab, QString());

        verticalLayout->addWidget(OptionsTabWidget);

        MainHorizontalLayout = new QHBoxLayout();
        MainHorizontalLayout->setObjectName(QString::fromUtf8("MainHorizontalLayout"));
        OKButton = new QPushButton(OptionsDialog);
        OKButton->setObjectName(QString::fromUtf8("OKButton"));

        MainHorizontalLayout->addWidget(OKButton);

        CancelButton = new QPushButton(OptionsDialog);
        CancelButton->setObjectName(QString::fromUtf8("CancelButton"));

        MainHorizontalLayout->addWidget(CancelButton);

        ApplyButton = new QPushButton(OptionsDialog);
        ApplyButton->setObjectName(QString::fromUtf8("ApplyButton"));

        MainHorizontalLayout->addWidget(ApplyButton);


        verticalLayout->addLayout(MainHorizontalLayout);


        retranslateUi(OptionsDialog);

        OptionsTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(OptionsDialog);
    } // setupUi

    void retranslateUi(QDialog *OptionsDialog)
    {
        OptionsDialog->setWindowTitle(QApplication::translate("OptionsDialog", "Options", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label->setToolTip(QApplication::translate("OptionsDialog", "Sets the connection timeout in seconds", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        label->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        label->setText(QApplication::translate("OptionsDialog", "Timeout:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        spinBox->setToolTip(QApplication::translate("OptionsDialog", "Sets the connection timeout in seconds", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        spinBox->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        OptionsTabWidget->setTabText(OptionsTabWidget->indexOf(ConnectionTab), QApplication::translate("OptionsDialog", "Connection", 0, QApplication::UnicodeUTF8));
        OptionsTabWidget->setTabText(OptionsTabWidget->indexOf(StatementsTab), QApplication::translate("OptionsDialog", "Statements", 0, QApplication::UnicodeUTF8));
        OKButton->setText(QApplication::translate("OptionsDialog", "OK", 0, QApplication::UnicodeUTF8));
        CancelButton->setText(QApplication::translate("OptionsDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        ApplyButton->setText(QApplication::translate("OptionsDialog", "Apply", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class OptionsDialog: public Ui_OptionsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ODBC_OPTIONSDIALOG_H

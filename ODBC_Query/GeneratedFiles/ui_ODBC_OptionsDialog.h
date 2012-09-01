/********************************************************************************
** Form generated from reading UI file 'ODBC_OptionsDialog.ui'
**
** Created: Sat 1. Sep 23:23:20 2012
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
#include <QtGui/QCheckBox>
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
    QLabel *TimeoutLabel;
    QSpinBox *TimeoutSpinBox;
    QSpacerItem *TimeoutSpacer;
    QWidget *StatementsTab;
    QFormLayout *formLayout_2;
    QVBoxLayout *VerticalLayout_2;
    QHBoxLayout *HorizontalLayout_2;
    QCheckBox *FetchResultsCheckBox;
    QSpacerItem *FetchResultsSpacer;
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
        verticalLayout->setContentsMargins(5, 5, 5, 5);
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
        TimeoutLabel = new QLabel(ConnectionTab);
        TimeoutLabel->setObjectName(QString::fromUtf8("TimeoutLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TimeoutLabel->sizePolicy().hasHeightForWidth());
        TimeoutLabel->setSizePolicy(sizePolicy);
        TimeoutLabel->setTextFormat(Qt::AutoText);

        HorizontalLayout->addWidget(TimeoutLabel);

        TimeoutSpinBox = new QSpinBox(ConnectionTab);
        TimeoutSpinBox->setObjectName(QString::fromUtf8("TimeoutSpinBox"));
        TimeoutSpinBox->setMaximum(300);

        HorizontalLayout->addWidget(TimeoutSpinBox);

        TimeoutSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayout->addItem(TimeoutSpacer);


        VerticalLayout->addLayout(HorizontalLayout);


        formLayout->setLayout(1, QFormLayout::FieldRole, VerticalLayout);

        OptionsTabWidget->addTab(ConnectionTab, QString());
        StatementsTab = new QWidget();
        StatementsTab->setObjectName(QString::fromUtf8("StatementsTab"));
        formLayout_2 = new QFormLayout(StatementsTab);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setContentsMargins(5, 11, -1, -1);
        VerticalLayout_2 = new QVBoxLayout();
        VerticalLayout_2->setObjectName(QString::fromUtf8("VerticalLayout_2"));
        HorizontalLayout_2 = new QHBoxLayout();
        HorizontalLayout_2->setSpacing(6);
        HorizontalLayout_2->setObjectName(QString::fromUtf8("HorizontalLayout_2"));
        FetchResultsCheckBox = new QCheckBox(StatementsTab);
        FetchResultsCheckBox->setObjectName(QString::fromUtf8("FetchResultsCheckBox"));

        HorizontalLayout_2->addWidget(FetchResultsCheckBox);

        FetchResultsSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayout_2->addItem(FetchResultsSpacer);


        VerticalLayout_2->addLayout(HorizontalLayout_2);


        formLayout_2->setLayout(0, QFormLayout::FieldRole, VerticalLayout_2);

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
        TimeoutLabel->setToolTip(QApplication::translate("OptionsDialog", "Sets the connection timeout in seconds", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        TimeoutLabel->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        TimeoutLabel->setText(QApplication::translate("OptionsDialog", "Timeout:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        TimeoutSpinBox->setToolTip(QApplication::translate("OptionsDialog", "Sets the connection timeout in seconds", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        TimeoutSpinBox->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        OptionsTabWidget->setTabText(OptionsTabWidget->indexOf(ConnectionTab), QApplication::translate("OptionsDialog", "Connection", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        FetchResultsCheckBox->setToolTip(QApplication::translate("OptionsDialog", "Determines whether select statements results should be fetched dynamically", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        FetchResultsCheckBox->setText(QApplication::translate("OptionsDialog", "Fetch results dynamically", 0, QApplication::UnicodeUTF8));
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

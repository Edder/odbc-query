/********************************************************************************
** Form generated from reading UI file 'ODBC_OptionsDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ODBC_OPTIONSDIALOG_H
#define UI_ODBC_OPTIONSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

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
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *ForwardOnlyCheckBox;
    QHBoxLayout *horizontalLayout;
    QCheckBox *LimitResultsCheckBox;
    QSpinBox *ResultCountSpinBox;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *MainHorizontalLayout;
    QPushButton *OKButton;
    QPushButton *CancelButton;
    QPushButton *ApplyButton;

    void setupUi(QDialog *OptionsDialog)
    {
        if (OptionsDialog->objectName().isEmpty())
            OptionsDialog->setObjectName(QStringLiteral("OptionsDialog"));
        OptionsDialog->resize(400, 299);
        QIcon icon;
        icon.addFile(QStringLiteral(":/ODBC_Query/Resources/options.png"), QSize(), QIcon::Normal, QIcon::Off);
        OptionsDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(OptionsDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        OptionsTabWidget = new QTabWidget(OptionsDialog);
        OptionsTabWidget->setObjectName(QStringLiteral("OptionsTabWidget"));
        ConnectionTab = new QWidget();
        ConnectionTab->setObjectName(QStringLiteral("ConnectionTab"));
        formLayout = new QFormLayout(ConnectionTab);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setContentsMargins(5, 5, 9, -1);
        VerticalLayout = new QVBoxLayout();
        VerticalLayout->setSpacing(6);
        VerticalLayout->setObjectName(QStringLiteral("VerticalLayout"));
        HorizontalLayout = new QHBoxLayout();
        HorizontalLayout->setSpacing(6);
        HorizontalLayout->setObjectName(QStringLiteral("HorizontalLayout"));
        TimeoutLabel = new QLabel(ConnectionTab);
        TimeoutLabel->setObjectName(QStringLiteral("TimeoutLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TimeoutLabel->sizePolicy().hasHeightForWidth());
        TimeoutLabel->setSizePolicy(sizePolicy);
        TimeoutLabel->setTextFormat(Qt::AutoText);

        HorizontalLayout->addWidget(TimeoutLabel);

        TimeoutSpinBox = new QSpinBox(ConnectionTab);
        TimeoutSpinBox->setObjectName(QStringLiteral("TimeoutSpinBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(TimeoutSpinBox->sizePolicy().hasHeightForWidth());
        TimeoutSpinBox->setSizePolicy(sizePolicy1);
        TimeoutSpinBox->setMinimumSize(QSize(0, 0));
        TimeoutSpinBox->setMaximum(300);

        HorizontalLayout->addWidget(TimeoutSpinBox);

        TimeoutSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayout->addItem(TimeoutSpacer);


        VerticalLayout->addLayout(HorizontalLayout);


        formLayout->setLayout(1, QFormLayout::FieldRole, VerticalLayout);

        OptionsTabWidget->addTab(ConnectionTab, QString());
        StatementsTab = new QWidget();
        StatementsTab->setObjectName(QStringLiteral("StatementsTab"));
        formLayout_2 = new QFormLayout(StatementsTab);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_2->setContentsMargins(5, 11, -1, -1);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        ForwardOnlyCheckBox = new QCheckBox(StatementsTab);
        ForwardOnlyCheckBox->setObjectName(QStringLiteral("ForwardOnlyCheckBox"));

        horizontalLayout_2->addWidget(ForwardOnlyCheckBox);


        formLayout_2->setLayout(0, QFormLayout::FieldRole, horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        LimitResultsCheckBox = new QCheckBox(StatementsTab);
        LimitResultsCheckBox->setObjectName(QStringLiteral("LimitResultsCheckBox"));

        horizontalLayout->addWidget(LimitResultsCheckBox);

        ResultCountSpinBox = new QSpinBox(StatementsTab);
        ResultCountSpinBox->setObjectName(QStringLiteral("ResultCountSpinBox"));
        sizePolicy1.setHeightForWidth(ResultCountSpinBox->sizePolicy().hasHeightForWidth());
        ResultCountSpinBox->setSizePolicy(sizePolicy1);
        ResultCountSpinBox->setMinimumSize(QSize(60, 0));
        ResultCountSpinBox->setMinimum(1);
        ResultCountSpinBox->setMaximum(999999);
        ResultCountSpinBox->setValue(2000);

        horizontalLayout->addWidget(ResultCountSpinBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        formLayout_2->setLayout(2, QFormLayout::FieldRole, horizontalLayout);

        OptionsTabWidget->addTab(StatementsTab, QString());

        verticalLayout->addWidget(OptionsTabWidget);

        MainHorizontalLayout = new QHBoxLayout();
        MainHorizontalLayout->setObjectName(QStringLiteral("MainHorizontalLayout"));
        OKButton = new QPushButton(OptionsDialog);
        OKButton->setObjectName(QStringLiteral("OKButton"));

        MainHorizontalLayout->addWidget(OKButton);

        CancelButton = new QPushButton(OptionsDialog);
        CancelButton->setObjectName(QStringLiteral("CancelButton"));

        MainHorizontalLayout->addWidget(CancelButton);

        ApplyButton = new QPushButton(OptionsDialog);
        ApplyButton->setObjectName(QStringLiteral("ApplyButton"));

        MainHorizontalLayout->addWidget(ApplyButton);


        verticalLayout->addLayout(MainHorizontalLayout);


        retranslateUi(OptionsDialog);

        OptionsTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(OptionsDialog);
    } // setupUi

    void retranslateUi(QDialog *OptionsDialog)
    {
        OptionsDialog->setWindowTitle(QApplication::translate("OptionsDialog", "Options", 0));
#ifndef QT_NO_TOOLTIP
        TimeoutLabel->setToolTip(QApplication::translate("OptionsDialog", "Sets the connection timeout in seconds", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        TimeoutLabel->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        TimeoutLabel->setText(QApplication::translate("OptionsDialog", "Timeout:", 0));
#ifndef QT_NO_TOOLTIP
        TimeoutSpinBox->setToolTip(QApplication::translate("OptionsDialog", "Sets the connection timeout in seconds", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        TimeoutSpinBox->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        OptionsTabWidget->setTabText(OptionsTabWidget->indexOf(ConnectionTab), QApplication::translate("OptionsDialog", "Connection", 0));
#ifndef QT_NO_TOOLTIP
        ForwardOnlyCheckBox->setToolTip(QApplication::translate("OptionsDialog", "Forward only mode can be (depending on the driver) more memory efficient since results do not need to be cached. It will also improve performance on some databases.", 0));
#endif // QT_NO_TOOLTIP
        ForwardOnlyCheckBox->setText(QApplication::translate("OptionsDialog", "Use Forward Only", 0));
#ifndef QT_NO_TOOLTIP
        LimitResultsCheckBox->setToolTip(QApplication::translate("OptionsDialog", "Limits the select results to the given value and asks whether to fetch more", 0));
#endif // QT_NO_TOOLTIP
        LimitResultsCheckBox->setText(QApplication::translate("OptionsDialog", "Limit results", 0));
        OptionsTabWidget->setTabText(OptionsTabWidget->indexOf(StatementsTab), QApplication::translate("OptionsDialog", "Statements", 0));
        OKButton->setText(QApplication::translate("OptionsDialog", "OK", 0));
        CancelButton->setText(QApplication::translate("OptionsDialog", "Cancel", 0));
        ApplyButton->setText(QApplication::translate("OptionsDialog", "Apply", 0));
    } // retranslateUi

};

namespace Ui {
    class OptionsDialog: public Ui_OptionsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ODBC_OPTIONSDIALOG_H

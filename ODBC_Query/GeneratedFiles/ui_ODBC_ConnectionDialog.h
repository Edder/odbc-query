/********************************************************************************
** Form generated from reading UI file 'ODBC_ConnectionDialog.ui'
**
** Created: Sun 26. Aug 11:35:30 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ODBC_CONNECTIONDIALOG_H
#define UI_ODBC_CONNECTIONDIALOG_H

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
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *SystemDSNLabel;
    QTreeWidget *SystemDSNTreeWidget;
    QLabel *UserDSNLabel;
    QTreeWidget *UserDSNTreeWidget;
    QFormLayout *formLayout;
    QLabel *UsernameLabel;
    QLineEdit *UsernameLineEdit;
    QLabel *PasswordLabel;
    QLineEdit *PasswordLineEdit;
    QCheckBox *RememberCheckBox;
    QHBoxLayout *HorizontalLayout;
    QPushButton *ConnectButton;
    QPushButton *CancelButton;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(350, 400);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ODBC_Query/Resources/database_icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Dialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        SystemDSNLabel = new QLabel(Dialog);
        SystemDSNLabel->setObjectName(QString::fromUtf8("SystemDSNLabel"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        SystemDSNLabel->setFont(font);

        verticalLayout->addWidget(SystemDSNLabel);

        SystemDSNTreeWidget = new QTreeWidget(Dialog);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(1, QString::fromUtf8("2"));
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        SystemDSNTreeWidget->setHeaderItem(__qtreewidgetitem);
        SystemDSNTreeWidget->setObjectName(QString::fromUtf8("SystemDSNTreeWidget"));
        SystemDSNTreeWidget->setIndentation(0);
        SystemDSNTreeWidget->setItemsExpandable(false);
        SystemDSNTreeWidget->setExpandsOnDoubleClick(false);
        SystemDSNTreeWidget->setColumnCount(2);

        verticalLayout->addWidget(SystemDSNTreeWidget);

        UserDSNLabel = new QLabel(Dialog);
        UserDSNLabel->setObjectName(QString::fromUtf8("UserDSNLabel"));
        UserDSNLabel->setFont(font);

        verticalLayout->addWidget(UserDSNLabel);

        UserDSNTreeWidget = new QTreeWidget(Dialog);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(1, QString::fromUtf8("2"));
        __qtreewidgetitem1->setText(0, QString::fromUtf8("1"));
        UserDSNTreeWidget->setHeaderItem(__qtreewidgetitem1);
        UserDSNTreeWidget->setObjectName(QString::fromUtf8("UserDSNTreeWidget"));
        UserDSNTreeWidget->setIndentation(0);
        UserDSNTreeWidget->setItemsExpandable(false);
        UserDSNTreeWidget->setExpandsOnDoubleClick(false);
        UserDSNTreeWidget->setColumnCount(2);

        verticalLayout->addWidget(UserDSNTreeWidget);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        UsernameLabel = new QLabel(Dialog);
        UsernameLabel->setObjectName(QString::fromUtf8("UsernameLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, UsernameLabel);

        UsernameLineEdit = new QLineEdit(Dialog);
        UsernameLineEdit->setObjectName(QString::fromUtf8("UsernameLineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(UsernameLineEdit->sizePolicy().hasHeightForWidth());
        UsernameLineEdit->setSizePolicy(sizePolicy);
        UsernameLineEdit->setBaseSize(QSize(0, 0));
        UsernameLineEdit->setContextMenuPolicy(Qt::DefaultContextMenu);
        UsernameLineEdit->setEchoMode(QLineEdit::Normal);
        UsernameLineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::FieldRole, UsernameLineEdit);

        PasswordLabel = new QLabel(Dialog);
        PasswordLabel->setObjectName(QString::fromUtf8("PasswordLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, PasswordLabel);

        PasswordLineEdit = new QLineEdit(Dialog);
        PasswordLineEdit->setObjectName(QString::fromUtf8("PasswordLineEdit"));
        sizePolicy.setHeightForWidth(PasswordLineEdit->sizePolicy().hasHeightForWidth());
        PasswordLineEdit->setSizePolicy(sizePolicy);
        PasswordLineEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, PasswordLineEdit);

        RememberCheckBox = new QCheckBox(Dialog);
        RememberCheckBox->setObjectName(QString::fromUtf8("RememberCheckBox"));

        formLayout->setWidget(2, QFormLayout::FieldRole, RememberCheckBox);


        verticalLayout->addLayout(formLayout);

        HorizontalLayout = new QHBoxLayout();
        HorizontalLayout->setObjectName(QString::fromUtf8("HorizontalLayout"));
        ConnectButton = new QPushButton(Dialog);
        ConnectButton->setObjectName(QString::fromUtf8("ConnectButton"));

        HorizontalLayout->addWidget(ConnectButton);

        CancelButton = new QPushButton(Dialog);
        CancelButton->setObjectName(QString::fromUtf8("CancelButton"));

        HorizontalLayout->addWidget(CancelButton);


        verticalLayout->addLayout(HorizontalLayout);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Data Sources", 0, QApplication::UnicodeUTF8));
        SystemDSNLabel->setText(QApplication::translate("Dialog", "System DSN:", 0, QApplication::UnicodeUTF8));
        UserDSNLabel->setText(QApplication::translate("Dialog", "User DSN:", 0, QApplication::UnicodeUTF8));
        UsernameLabel->setText(QApplication::translate("Dialog", "Username:", 0, QApplication::UnicodeUTF8));
        PasswordLabel->setText(QApplication::translate("Dialog", "Password:", 0, QApplication::UnicodeUTF8));
        RememberCheckBox->setText(QApplication::translate("Dialog", "Remember", 0, QApplication::UnicodeUTF8));
        ConnectButton->setText(QApplication::translate("Dialog", "Connect", 0, QApplication::UnicodeUTF8));
        CancelButton->setText(QApplication::translate("Dialog", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ODBC_CONNECTIONDIALOG_H

/********************************************************************************
** Form generated from reading UI file 'ODBC_ConnectionDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ODBC_CONNECTIONDIALOG_H
#define UI_ODBC_CONNECTIONDIALOG_H

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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ConnectionDialog
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

    void setupUi(QDialog *ConnectionDialog)
    {
        if (ConnectionDialog->objectName().isEmpty())
            ConnectionDialog->setObjectName(QStringLiteral("ConnectionDialog"));
        ConnectionDialog->resize(350, 400);
        QIcon icon;
        icon.addFile(QStringLiteral(":/ODBC_Query/Resources/database_icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        ConnectionDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(ConnectionDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        SystemDSNLabel = new QLabel(ConnectionDialog);
        SystemDSNLabel->setObjectName(QStringLiteral("SystemDSNLabel"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        SystemDSNLabel->setFont(font);

        verticalLayout->addWidget(SystemDSNLabel);

        SystemDSNTreeWidget = new QTreeWidget(ConnectionDialog);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(1, QStringLiteral("2"));
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        SystemDSNTreeWidget->setHeaderItem(__qtreewidgetitem);
        SystemDSNTreeWidget->setObjectName(QStringLiteral("SystemDSNTreeWidget"));
        SystemDSNTreeWidget->setIndentation(0);
        SystemDSNTreeWidget->setItemsExpandable(false);
        SystemDSNTreeWidget->setExpandsOnDoubleClick(false);
        SystemDSNTreeWidget->setColumnCount(2);

        verticalLayout->addWidget(SystemDSNTreeWidget);

        UserDSNLabel = new QLabel(ConnectionDialog);
        UserDSNLabel->setObjectName(QStringLiteral("UserDSNLabel"));
        UserDSNLabel->setFont(font);

        verticalLayout->addWidget(UserDSNLabel);

        UserDSNTreeWidget = new QTreeWidget(ConnectionDialog);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(1, QStringLiteral("2"));
        __qtreewidgetitem1->setText(0, QStringLiteral("1"));
        UserDSNTreeWidget->setHeaderItem(__qtreewidgetitem1);
        UserDSNTreeWidget->setObjectName(QStringLiteral("UserDSNTreeWidget"));
        UserDSNTreeWidget->setIndentation(0);
        UserDSNTreeWidget->setItemsExpandable(false);
        UserDSNTreeWidget->setExpandsOnDoubleClick(false);
        UserDSNTreeWidget->setColumnCount(2);

        verticalLayout->addWidget(UserDSNTreeWidget);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        UsernameLabel = new QLabel(ConnectionDialog);
        UsernameLabel->setObjectName(QStringLiteral("UsernameLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, UsernameLabel);

        UsernameLineEdit = new QLineEdit(ConnectionDialog);
        UsernameLineEdit->setObjectName(QStringLiteral("UsernameLineEdit"));
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

        PasswordLabel = new QLabel(ConnectionDialog);
        PasswordLabel->setObjectName(QStringLiteral("PasswordLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, PasswordLabel);

        PasswordLineEdit = new QLineEdit(ConnectionDialog);
        PasswordLineEdit->setObjectName(QStringLiteral("PasswordLineEdit"));
        sizePolicy.setHeightForWidth(PasswordLineEdit->sizePolicy().hasHeightForWidth());
        PasswordLineEdit->setSizePolicy(sizePolicy);
        PasswordLineEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, PasswordLineEdit);

        RememberCheckBox = new QCheckBox(ConnectionDialog);
        RememberCheckBox->setObjectName(QStringLiteral("RememberCheckBox"));

        formLayout->setWidget(2, QFormLayout::FieldRole, RememberCheckBox);


        verticalLayout->addLayout(formLayout);

        HorizontalLayout = new QHBoxLayout();
        HorizontalLayout->setObjectName(QStringLiteral("HorizontalLayout"));
        ConnectButton = new QPushButton(ConnectionDialog);
        ConnectButton->setObjectName(QStringLiteral("ConnectButton"));

        HorizontalLayout->addWidget(ConnectButton);

        CancelButton = new QPushButton(ConnectionDialog);
        CancelButton->setObjectName(QStringLiteral("CancelButton"));

        HorizontalLayout->addWidget(CancelButton);


        verticalLayout->addLayout(HorizontalLayout);


        retranslateUi(ConnectionDialog);

        QMetaObject::connectSlotsByName(ConnectionDialog);
    } // setupUi

    void retranslateUi(QDialog *ConnectionDialog)
    {
        ConnectionDialog->setWindowTitle(QApplication::translate("ConnectionDialog", "Data Sources", 0));
        SystemDSNLabel->setText(QApplication::translate("ConnectionDialog", "System DSN:", 0));
        UserDSNLabel->setText(QApplication::translate("ConnectionDialog", "User DSN:", 0));
        UsernameLabel->setText(QApplication::translate("ConnectionDialog", "Username:", 0));
        PasswordLabel->setText(QApplication::translate("ConnectionDialog", "Password:", 0));
        RememberCheckBox->setText(QApplication::translate("ConnectionDialog", "Remember", 0));
        ConnectButton->setText(QApplication::translate("ConnectionDialog", "Connect", 0));
        CancelButton->setText(QApplication::translate("ConnectionDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class ConnectionDialog: public Ui_ConnectionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ODBC_CONNECTIONDIALOG_H

/********************************************************************************
** Form generated from reading UI file 'ODBC_ConnectionDialog.ui'
**
** Created: Fri 17. Aug 09:25:48 2012
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
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
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
    QHBoxLayout *HorizontalLayout_2;
    QLabel *UsernameLabel;
    QLineEdit *UsernameLineEdit;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *PasswordLabel;
    QLineEdit *PasswordLineEdit;
    QCheckBox *RememberCheckBox;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *HorizontalLayout;
    QPushButton *ConnectButton;
    QPushButton *CancelButton;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(350, 400);
        QIcon icon;
        icon.addFile(QString::fromUtf8("Resources/database_icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
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

        HorizontalLayout_2 = new QHBoxLayout();
        HorizontalLayout_2->setObjectName(QString::fromUtf8("HorizontalLayout_2"));
        UsernameLabel = new QLabel(Dialog);
        UsernameLabel->setObjectName(QString::fromUtf8("UsernameLabel"));

        HorizontalLayout_2->addWidget(UsernameLabel);

        UsernameLineEdit = new QLineEdit(Dialog);
        UsernameLineEdit->setObjectName(QString::fromUtf8("UsernameLineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(UsernameLineEdit->sizePolicy().hasHeightForWidth());
        UsernameLineEdit->setSizePolicy(sizePolicy);
        UsernameLineEdit->setBaseSize(QSize(0, 0));
        UsernameLineEdit->setContextMenuPolicy(Qt::DefaultContextMenu);
        UsernameLineEdit->setEchoMode(QLineEdit::Normal);
        UsernameLineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        HorizontalLayout_2->addWidget(UsernameLineEdit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(HorizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        PasswordLabel = new QLabel(Dialog);
        PasswordLabel->setObjectName(QString::fromUtf8("PasswordLabel"));

        horizontalLayout->addWidget(PasswordLabel);

        PasswordLineEdit = new QLineEdit(Dialog);
        PasswordLineEdit->setObjectName(QString::fromUtf8("PasswordLineEdit"));
        sizePolicy.setHeightForWidth(PasswordLineEdit->sizePolicy().hasHeightForWidth());
        PasswordLineEdit->setSizePolicy(sizePolicy);
        PasswordLineEdit->setEchoMode(QLineEdit::Password);

        horizontalLayout->addWidget(PasswordLineEdit);

        RememberCheckBox = new QCheckBox(Dialog);
        RememberCheckBox->setObjectName(QString::fromUtf8("RememberCheckBox"));

        horizontalLayout->addWidget(RememberCheckBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

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
        PasswordLabel->setText(QApplication::translate("Dialog", "Password: ", 0, QApplication::UnicodeUTF8));
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

/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *bt_OpenLocalDevice;
    QPushButton *bt_Choose;
    QPlainTextEdit *te_Details;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QPlainTextEdit *te_ReceiveContent;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *bt_ReceiveClear;
    QLabel *label_3;
    QPlainTextEdit *te_SendContent;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *bt_Send;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName("MainWidget");
        MainWidget->resize(800, 600);
        verticalLayoutWidget = new QWidget(MainWidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 10, 231, 581));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        bt_OpenLocalDevice = new QPushButton(verticalLayoutWidget);
        bt_OpenLocalDevice->setObjectName("bt_OpenLocalDevice");

        horizontalLayout->addWidget(bt_OpenLocalDevice);


        verticalLayout->addLayout(horizontalLayout);

        bt_Choose = new QPushButton(verticalLayoutWidget);
        bt_Choose->setObjectName("bt_Choose");

        verticalLayout->addWidget(bt_Choose);

        te_Details = new QPlainTextEdit(verticalLayoutWidget);
        te_Details->setObjectName("te_Details");

        verticalLayout->addWidget(te_Details);

        verticalLayoutWidget_2 = new QWidget(MainWidget);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(250, 10, 541, 581));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName("label_2");

        verticalLayout_2->addWidget(label_2);

        te_ReceiveContent = new QPlainTextEdit(verticalLayoutWidget_2);
        te_ReceiveContent->setObjectName("te_ReceiveContent");

        verticalLayout_2->addWidget(te_ReceiveContent);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        bt_ReceiveClear = new QPushButton(verticalLayoutWidget_2);
        bt_ReceiveClear->setObjectName("bt_ReceiveClear");

        horizontalLayout_2->addWidget(bt_ReceiveClear);


        verticalLayout_2->addLayout(horizontalLayout_2);

        label_3 = new QLabel(verticalLayoutWidget_2);
        label_3->setObjectName("label_3");

        verticalLayout_2->addWidget(label_3);

        te_SendContent = new QPlainTextEdit(verticalLayoutWidget_2);
        te_SendContent->setObjectName("te_SendContent");

        verticalLayout_2->addWidget(te_SendContent);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        bt_Send = new QPushButton(verticalLayoutWidget_2);
        bt_Send->setObjectName("bt_Send");

        horizontalLayout_3->addWidget(bt_Send);


        verticalLayout_2->addLayout(horizontalLayout_3);


        retranslateUi(MainWidget);

        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QCoreApplication::translate("MainWidget", "BLE\350\223\235\347\211\231\350\256\276\345\244\207\346\265\213\350\257\225", nullptr));
        bt_OpenLocalDevice->setText(QCoreApplication::translate("MainWidget", "\346\211\223\345\274\200\350\223\235\347\211\231", nullptr));
        bt_Choose->setText(QCoreApplication::translate("MainWidget", "\351\200\211\346\213\251\350\223\235\347\211\231", nullptr));
        label_2->setText(QCoreApplication::translate("MainWidget", "\346\216\245\346\224\266\345\206\205\345\256\271\357\274\232", nullptr));
        bt_ReceiveClear->setText(QCoreApplication::translate("MainWidget", "\346\270\205\351\231\244", nullptr));
        label_3->setText(QCoreApplication::translate("MainWidget", "\345\217\221\351\200\201\345\206\205\345\256\271\357\274\232", nullptr));
        bt_Send->setText(QCoreApplication::translate("MainWidget", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H

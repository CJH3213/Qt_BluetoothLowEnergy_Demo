/********************************************************************************
** Form generated from reading UI file 'connectdevicedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTDEVICEDIALOG_H
#define UI_CONNECTDEVICEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ConnectDeviceDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QListWidget *list_Devices;
    QListWidget *list_Services;
    QListWidget *list_Characteristics;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLabel *lb_DeviceDiscoveryState;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLabel *lb_ServiceDiscoveryState;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLabel *lb_CharacteristicDiscoveryState;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *bt_Search;
    QSpacerItem *horizontalSpacer;
    QPushButton *bt_OK;
    QPushButton *bt_Cancel;

    void setupUi(QDialog *ConnectDeviceDialog)
    {
        if (ConnectDeviceDialog->objectName().isEmpty())
            ConnectDeviceDialog->setObjectName("ConnectDeviceDialog");
        ConnectDeviceDialog->resize(958, 468);
        verticalLayout_2 = new QVBoxLayout(ConnectDeviceDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        list_Devices = new QListWidget(ConnectDeviceDialog);
        list_Devices->setObjectName("list_Devices");

        gridLayout->addWidget(list_Devices, 1, 0, 1, 1);

        list_Services = new QListWidget(ConnectDeviceDialog);
        list_Services->setObjectName("list_Services");

        gridLayout->addWidget(list_Services, 1, 1, 1, 1);

        list_Characteristics = new QListWidget(ConnectDeviceDialog);
        list_Characteristics->setObjectName("list_Characteristics");

        gridLayout->addWidget(list_Characteristics, 1, 2, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(ConnectDeviceDialog);
        label->setObjectName("label");

        horizontalLayout_3->addWidget(label);

        lb_DeviceDiscoveryState = new QLabel(ConnectDeviceDialog);
        lb_DeviceDiscoveryState->setObjectName("lb_DeviceDiscoveryState");

        horizontalLayout_3->addWidget(lb_DeviceDiscoveryState);


        gridLayout->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_2 = new QLabel(ConnectDeviceDialog);
        label_2->setObjectName("label_2");

        horizontalLayout_4->addWidget(label_2);

        lb_ServiceDiscoveryState = new QLabel(ConnectDeviceDialog);
        lb_ServiceDiscoveryState->setObjectName("lb_ServiceDiscoveryState");

        horizontalLayout_4->addWidget(lb_ServiceDiscoveryState);


        gridLayout->addLayout(horizontalLayout_4, 0, 1, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_3 = new QLabel(ConnectDeviceDialog);
        label_3->setObjectName("label_3");

        horizontalLayout_5->addWidget(label_3);

        lb_CharacteristicDiscoveryState = new QLabel(ConnectDeviceDialog);
        lb_CharacteristicDiscoveryState->setObjectName("lb_CharacteristicDiscoveryState");

        horizontalLayout_5->addWidget(lb_CharacteristicDiscoveryState);


        gridLayout->addLayout(horizontalLayout_5, 0, 2, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        bt_Search = new QPushButton(ConnectDeviceDialog);
        bt_Search->setObjectName("bt_Search");

        horizontalLayout_2->addWidget(bt_Search);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        bt_OK = new QPushButton(ConnectDeviceDialog);
        bt_OK->setObjectName("bt_OK");

        horizontalLayout_2->addWidget(bt_OK);

        bt_Cancel = new QPushButton(ConnectDeviceDialog);
        bt_Cancel->setObjectName("bt_Cancel");

        horizontalLayout_2->addWidget(bt_Cancel);


        verticalLayout_2->addLayout(horizontalLayout_2);


        retranslateUi(ConnectDeviceDialog);

        QMetaObject::connectSlotsByName(ConnectDeviceDialog);
    } // setupUi

    void retranslateUi(QDialog *ConnectDeviceDialog)
    {
        ConnectDeviceDialog->setWindowTitle(QCoreApplication::translate("ConnectDeviceDialog", "BLE\350\223\235\347\211\231\350\256\276\345\244\207\351\200\211\346\213\251\345\271\266\350\277\236\346\216\245", nullptr));
        label->setText(QCoreApplication::translate("ConnectDeviceDialog", "\350\256\276\345\244\207\357\274\232", nullptr));
        lb_DeviceDiscoveryState->setText(QCoreApplication::translate("ConnectDeviceDialog", "\345\260\261\347\273\252", nullptr));
        label_2->setText(QCoreApplication::translate("ConnectDeviceDialog", "\346\234\215\345\212\241\357\274\232", nullptr));
        lb_ServiceDiscoveryState->setText(QCoreApplication::translate("ConnectDeviceDialog", "\345\260\261\347\273\252", nullptr));
        label_3->setText(QCoreApplication::translate("ConnectDeviceDialog", "\347\211\271\345\276\201\357\274\232", nullptr));
        lb_CharacteristicDiscoveryState->setText(QCoreApplication::translate("ConnectDeviceDialog", "\345\260\261\347\273\252", nullptr));
        bt_Search->setText(QCoreApplication::translate("ConnectDeviceDialog", "\346\220\234\347\264\242", nullptr));
        bt_OK->setText(QCoreApplication::translate("ConnectDeviceDialog", "\347\241\256\350\256\244", nullptr));
        bt_Cancel->setText(QCoreApplication::translate("ConnectDeviceDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConnectDeviceDialog: public Ui_ConnectDeviceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTDEVICEDIALOG_H

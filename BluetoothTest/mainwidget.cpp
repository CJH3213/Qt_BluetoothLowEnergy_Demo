#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "connectdevicedialog.h"
#include <QMessageBox>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    mDeviceDiscoverAgent = new QBluetoothDeviceDiscoveryAgent(this);
    mLocalDevice = new QBluetoothLocalDevice(this);
    // auto deciceInfoList = new QList<QBluetoothDeviceInfo>();

    // 设置单次搜索新设备时长：5秒
    mDeviceDiscoverAgent->setLowEnergyDiscoveryTimeout(5000);

    if(mLocalDevice->hostMode() == QBluetoothLocalDevice::HostPoweredOff)
        ui->bt_OpenLocalDevice->setText("打开蓝牙");
    else
        ui->bt_OpenLocalDevice->setText("关闭蓝牙");

}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_bt_OpenLocalDevice_clicked()
{
    if(mLocalDevice->hostMode() == QBluetoothLocalDevice::HostPoweredOff)
    {
        mLocalDevice->powerOn();
        ui->bt_OpenLocalDevice->setText("关闭蓝牙");
    }
    else
    {
        mLocalDevice->setHostMode(QBluetoothLocalDevice::HostPoweredOff);
        ui->bt_OpenLocalDevice->setText("打开蓝牙");
    }
}


void MainWidget::on_bt_Choose_clicked()
{
    auto *dialog = new ConnectDeviceDialog();
    connect(dialog, SIGNAL(ChoseBLEDevice(QLowEnergyController*,QLowEnergyService*,QLowEnergyCharacteristic&)),
            this, SLOT(OnChoseBLEDevice(QLowEnergyController*,QLowEnergyService*,QLowEnergyCharacteristic&)));

    if(dialog->exec() == QDialog::Accepted)
    {

    }

    // dialog->show();
}

void MainWidget::OnBLECharacteristicRead(const QLowEnergyCharacteristic &characteristic, const QByteArray &bytes)
{
    qDebug() << "OnBLERead" << bytes;
}

// 特征变化事件：获取蓝牙收到数据
void MainWidget::OnBLECharacteristicChange(const QLowEnergyCharacteristic &characteristic, const QByteArray &bytes)
{
    qDebug() << "OnBLECharacteristicChange: "<< bytes;
    ui->te_ReceiveContent->insertPlainText(bytes);
}

void MainWidget::OnChoseBLEDevice(QLowEnergyController *controller, QLowEnergyService *service, QLowEnergyCharacteristic &characteristic)
{
    qDebug() << "newController: " << controller;
    if(controller == nullptr || service == nullptr || characteristic.isValid() == false)
        return;

    ForceDisconnectAndCleanup();

    mBLEController = controller;
    mBLEService = service;
    mBLECharacteristic = characteristic;

    // 显示选择蓝牙的参数
    QString detailStr = QString("Name: %1\r\n").arg(mBLEController->remoteName()) +
        QString("Mac: %1\r\n").arg(mBLEController->remoteAddress().toString()) +
        QString("Service: %1\r\n").arg(mBLEService->serviceUuid().toString()) +
        QString("Characteristic: %1\r\n").arg(mBLECharacteristic.uuid().toString());
    ui->te_Details->clear();
    ui->te_Details->appendPlainText(detailStr);

    // 接收通知，实测不写这部分也能收发
    QLowEnergyDescriptor descriptor = mBLECharacteristic.descriptor(QBluetoothUuid::DescriptorType::ClientCharacteristicConfiguration);
    if(descriptor.isValid() == false)
    {
        QMessageBox::warning(this, "警告", "BLE描述无效！");
        return;
    }
    // 订阅特征的通知（"0100" 表示启用通知；"0200" 表示启用指示）
    mBLEService->writeDescriptor(descriptor, QByteArray::fromHex("0100"));

    // 接收BLE特征的消息
    //mBLEService->readCharacteristic(mBLECharacteristic);
    // connect(mBLEService, SIGNAL(characteristicRead(QLowEnergyCharacteristic,QByteArray)), this, SLOT(OnBLERead(QLowEnergyCharacteristic,QByteArray)));
    connect(mBLEService, SIGNAL(characteristicChanged(QLowEnergyCharacteristic,QByteArray)), this, SLOT(OnBLECharacteristicChange(QLowEnergyCharacteristic,QByteArray)));
}

void MainWidget::ForceDisconnectAndCleanup()
{
    // 检查是否有蓝牙连接需要断开
    if (mBLEController)
    {
        QEventLoop loop;
        connect(mBLEController, &QLowEnergyController::disconnected, &loop, &QEventLoop::quit);

        mBLEController->disconnectFromDevice();

        // 等待直到设备断开连接
        if(mBLEController->state() != QLowEnergyController::UnconnectedState)
            loop.exec();
    }

    // 清理资源
    if (mBLEController)
    {
        mBLEController->deleteLater();
        mBLEController = nullptr;
    }
}


void MainWidget::on_bt_Send_clicked()
{
    if(mBLEService == nullptr)
    {
        QMessageBox::warning(this, "警告", "BLE服务无效！");
        return;
    }

    if(mBLECharacteristic.isValid() == false)
    {
        QMessageBox::warning(this, "警告", "BLE特征无效！");
        return;
    }

    QByteArray dataToSend = ui->te_SendContent->toPlainText().toLocal8Bit();
    mBLEService->writeCharacteristic(mBLECharacteristic, dataToSend);
}


void MainWidget::on_bt_ReceiveClear_clicked()
{
    ui->te_ReceiveContent->clear();
}


#include "connectdevicedialog.h"
#include "ui_connectdevicedialog.h"
#include <QMessageBox>
#include <QEventLoop>

const QString ConnectDeviceDialog::gStrDiscoveringState("扫描中");
const QString ConnectDeviceDialog::gStrDiscoveredState("扫描结束");

ConnectDeviceDialog::ConnectDeviceDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConnectDeviceDialog)
{
    ui->setupUi(this);

    mLocalDevice = new QBluetoothLocalDevice(this);
    mDeviceDiscoverAgent = new QBluetoothDeviceDiscoveryAgent(this);

    // 这是设置低功耗蓝牙搜索时长，经典蓝牙搜索会比这个更长至30秒
    mDeviceDiscoverAgent->setLowEnergyDiscoveryTimeout(mLowEnergyDiscoveryTimeout);

    connect(mDeviceDiscoverAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
            this, SLOT(DeviceDiscovered(QBluetoothDeviceInfo)));

    // 错误事件
    connect(mDeviceDiscoverAgent, &QBluetoothDeviceDiscoveryAgent::errorOccurred,
            [this](QBluetoothDeviceDiscoveryAgent::Error error){
                qDebug() << "Error()" << error;
                DeviceDiscoveredFinished();
    });

    // 只有手动调用stop()才会收到。
    connect(mDeviceDiscoverAgent, &QBluetoothDeviceDiscoveryAgent::canceled,
            [this](){
                qDebug() << "Canceled()";
                DeviceDiscoveredFinished();
    });

    // 开始搜索后固定30s收到finished信号，与低功耗蓝牙超时设置无关
    connect(mDeviceDiscoverAgent, &QBluetoothDeviceDiscoveryAgent::finished,
            [this](){
                qDebug() << "Finished()";
                DeviceDiscoveredFinished();
    });
}

ConnectDeviceDialog::~ConnectDeviceDialog()
{
    delete ui;
}

void ConnectDeviceDialog::closeEvent(QCloseEvent *event)
{
    if(mDisconnectOnClose)
        ForceDisconnectAndCleanup();

    // 继续正常关闭对话框
    // event->accept();
}

void ConnectDeviceDialog::DeviceDiscovered(QBluetoothDeviceInfo deviceInfo)
{
    if(deviceInfo.rssi() > -10 || deviceInfo.rssi() < -110)
    {
        qDebug() << "Device is invalid: " << deviceInfo.name() <<
            deviceInfo.address();
        return;
    }

    mDeviceInfoList.append(deviceInfo);

    QString name = deviceInfo.name();
    QString address = deviceInfo.address().toString();
    QString rssi = QString::number(deviceInfo.rssi());

    QListWidgetItem *item = new QListWidgetItem;
    item->setText(QString("%1 (%2) %3dBm").arg(name).arg(address).arg(rssi));
    item->setData(Qt::UserRole, address);
    ui->list_Devices->addItem(item);
}

void ConnectDeviceDialog::DeviceDiscoveredFinished()
{
    mTimeoutTimer.stop();
    ui->lb_DeviceDiscoveryState->setText(ConnectDeviceDialog::gStrDiscoveredState);
}

void ConnectDeviceDialog::on_bt_Search_clicked()
{
    if(mLocalDevice->hostMode() == QBluetoothLocalDevice::HostPoweredOff)
    {
        auto resBt = QMessageBox::warning(this, "警告", "蓝牙未打开，是否开启？",
                             QMessageBox::Yes | QMessageBox::No,
                             QMessageBox::No);
        if(resBt == QMessageBox::No)
            return;

        mLocalDevice->powerOn();
    }

    // 断开已连接的蓝牙
    // ForceDisconnectAndCleanup();

    mDeviceDiscoverAgent->stop();
    mDeviceInfoList.clear();
    ui->list_Devices->clear();
    mDeviceDiscoverAgent->start();       // 开始扫描蓝牙设备

    ui->lb_DeviceDiscoveryState->setText(ConnectDeviceDialog::gStrDiscoveringState);
    mTimeoutTimer.start(mLowEnergyDiscoveryTimeout);
    connect(&mTimeoutTimer, SIGNAL(timeout()), this, SLOT(DeviceDiscoveredFinished()));

}


void ConnectDeviceDialog::on_list_Devices_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(current == nullptr)
    {
        qDebug() << "currentItemChanged error!?";
        return;
    }

    auto strAddress = qvariant_cast<QString>( current->data(Qt::UserRole));
    QBluetoothAddress btAddress(strAddress);
    QBluetoothDeviceInfo info;
    foreach (auto otherInfo, mDeviceInfoList)
    {
        if(btAddress == otherInfo.address())
        {
            info = otherInfo;
            break;
        }
    }

    // qDebug() << info.address().toString();

    // 断开之前连接的蓝牙
    //ForceDisconnectAndCleanup();

    mLowEnergyController = QLowEnergyController::createCentral(info, this);
    if(mLowEnergyController == nullptr)
    {
        QMessageBox::warning(this, "警告", "创建BLE控制器失败");
        return;
    }

    qDebug() << "创建BLE控制器成功";

    connect(mLowEnergyController, SIGNAL(connected()), this, SLOT(OnControlConnected()));
    connect(mLowEnergyController, SIGNAL(disconnected()), this, SLOT(OnControlDisconnected()));
    connect(mLowEnergyController, SIGNAL(errorOccurred(QLowEnergyController::Error)), this, SLOT(OnDeviceError(QLowEnergyController::Error)));
    connect(mLowEnergyController, SIGNAL(serviceDiscovered(QBluetoothUuid)), this, SLOT(OnServiceDiscovered(QBluetoothUuid)));
    connect(mLowEnergyController, SIGNAL(discoveryFinished()), this, SLOT(OnServiceScanDone()));

    ui->lb_ServiceDiscoveryState->setText(ConnectDeviceDialog::gStrDiscoveringState);
    ui->list_Services->clear();
    mLowEnergyController->connectToDevice();      // 连接到选择的蓝牙设备
}

void ConnectDeviceDialog::OnControlConnected()
{
    qDebug() << "BLE Controller ConnectToDevice Connected!";
    mLowEnergyController->discoverServices();
}

void ConnectDeviceDialog::OnControlDisconnected()
{
    qDebug() << "BLE Controller ConnectToDevice Disconnected!";

    // 清空服务和特征列表
    ui->list_Services->clear();
    ui->list_Characteristics->clear();
}

void ConnectDeviceDialog::OnDeviceError(QLowEnergyController::Error newError)
{
    qDebug() << "BLE Controller ConnectToDevice Error!" << newError;

    QString errorInfo;
    if(mLowEnergyController)
        errorInfo = mLowEnergyController->remoteName() + "\r\n"
                  + mLowEnergyController->remoteDeviceUuid().toString() + "\r\n";
    else
        errorInfo = "未知设备\r\n";
    errorInfo +=  "连接失败！";
    QMessageBox::warning(this, "警告", errorInfo);
    ui->lb_ServiceDiscoveryState->setText(ConnectDeviceDialog::gStrDiscoveredState);

    // 设备连接后又断开，也会触发当前信号

    // 清空服务和特征列表
    ui->list_Services->clear();
    ui->list_Characteristics->clear();
}

void ConnectDeviceDialog::OnServiceDiscovered(const QBluetoothUuid &newService)
{
    qDebug() << "BLE Controller ConnectToDevice ServiceDiscovered!";
    ui->list_Services->addItem(newService.toString());
}

void ConnectDeviceDialog::OnServiceScanDone()
{
    qDebug() << "BLE Controller ConnectToDevice ServiceScanDone!";
    ui->lb_ServiceDiscoveryState->setText(ConnectDeviceDialog::gStrDiscoveredState);
}

void ConnectDeviceDialog::OnCharacteristicRead(const QLowEnergyCharacteristic &characteristic, const QByteArray &value)
{
    qDebug() << "BLE Service DiscoverDetails CharacteristicRead!";
    ui->list_Characteristics->addItem(characteristic.uuid().toString() + value.toHex());
}

// 服务状态改变：获取扫描到的特征
void ConnectDeviceDialog::OnServiceStateChanged(QLowEnergyService::ServiceState newState)
{
    qDebug() << "Service state changed:" << newState;
    if (newState == QLowEnergyService::RemoteServiceDiscovered) {
        qDebug() << "Service discovered all characteristics.";
        foreach (auto &c, mLowEnergyService->characteristics()) {
            qDebug() << "Characteristic:" << c.uuid().toString();
            ui->list_Characteristics->addItem(c.uuid().toString());
            ui->lb_CharacteristicDiscoveryState->setText(ConnectDeviceDialog::gStrDiscoveredState);
        }
    } else {
        qDebug() << "Service state is not ServiceDiscovered.";
    }
}


void ConnectDeviceDialog::on_list_Services_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(current == nullptr)
    {
        qDebug() << "currentItemChanged error!?";
        return;
    }

    QString serviceUuid = current->text();

    mLowEnergyService = mLowEnergyController->createServiceObject(QBluetoothUuid(serviceUuid), this);

    if(mLowEnergyService)
    {
        connect(mLowEnergyService, SIGNAL(stateChanged(QLowEnergyService::ServiceState)), this, SLOT(OnServiceStateChanged(QLowEnergyService::ServiceState)));
        connect(mLowEnergyService, SIGNAL(characteristicRead(QLowEnergyCharacteristic,QByteArray)),
                this, SLOT(OnCharacteristicRead(QLowEnergyCharacteristic,QByteArray)));

        ui->list_Characteristics->clear();
        foreach (auto &c, mLowEnergyService->characteristics())     // 先加载这个服务之前缓存好的特征
            ui->list_Characteristics->addItem(c.uuid().toString());

        // 如果已经有缓存的特征，就不需要扫描，直接退出
        if(mLowEnergyService->characteristics().size() > 0)
            return;

        mLowEnergyService->discoverDetails();   // 获取当前服务下的所有特征
        ui->lb_CharacteristicDiscoveryState->setText(ConnectDeviceDialog::gStrDiscoveringState);
    }
}


void ConnectDeviceDialog::on_bt_Cancel_clicked()
{
    this->close();
}


void ConnectDeviceDialog::on_bt_OK_clicked()
{
    auto *currentItem = ui->list_Characteristics->currentItem();

    if(currentItem == nullptr)
    {
        QMessageBox::warning(this, "警告", "请选择一个特征！");
        return;
    }

    auto characteristic = mLowEnergyService->characteristic(QBluetoothUuid(currentItem->text()));
    if(characteristic.isValid() != true)
    {
        QMessageBox::warning(this, "警告", "特征无效！");
        return;
    }

    if (mLowEnergyController)
    {
        emit ChoseBLEDevice(mLowEnergyController, mLowEnergyService, characteristic);
        mDisconnectOnClose = false;     //关闭串口但不断开连接
        this->close();
    }
}

void ConnectDeviceDialog::ForceDisconnectAndCleanup()
{
    // 检查是否有蓝牙连接需要断开
    if (mLowEnergyController)
    {
        QEventLoop loop;
        connect(mLowEnergyController, &QLowEnergyController::disconnected, &loop, &QEventLoop::quit);

        mLowEnergyController->disconnectFromDevice();

        // 等待直到设备断开连接
        if(mLowEnergyController->state() != QLowEnergyController::UnconnectedState)
            loop.exec();
    }

    // 清理资源
    if (mLowEnergyController)
    {
        mLowEnergyController->deleteLater();
        mLowEnergyController = nullptr;
    }
}


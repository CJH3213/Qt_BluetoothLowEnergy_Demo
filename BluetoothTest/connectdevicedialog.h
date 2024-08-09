#ifndef CONNECTDEVICEDIALOG_H
#define CONNECTDEVICEDIALOG_H

#include <QDialog>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothLocalDevice>
#include <QListWidgetItem>
#include <QTimer>
#include <QLowEnergyController>
#include <QLowEnergyService>


namespace Ui {
class ConnectDeviceDialog;
}

class ConnectDeviceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDeviceDialog(QWidget *parent = nullptr);
    ~ConnectDeviceDialog();

    void closeEvent(QCloseEvent *event) override;

signals:
    void ChoseBLEDevice(QLowEnergyController *controller, QLowEnergyService *service, QLowEnergyCharacteristic &characteristic);

private slots:
    // ui控件信号-槽
    void on_bt_Search_clicked();
    void on_list_Devices_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_list_Services_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    // 扫描发现设备产生的信号-槽
    void DeviceDiscovered(QBluetoothDeviceInfo deviceInfo);
    void DeviceDiscoveredFinished();

    // BLE设备连接产生的信号-槽
    void OnControlConnected();
    void OnControlDisconnected();
    void OnDeviceError(QLowEnergyController::Error newError);
    void OnServiceDiscovered(const QBluetoothUuid &newService);
    void OnServiceScanDone();

    // BLE服务产生的信号-槽
    void OnCharacteristicRead(const QLowEnergyCharacteristic &characteristic, const QByteArray &value);
    void OnServiceStateChanged(QLowEnergyService::ServiceState newState);

    void on_bt_Cancel_clicked();

    void on_bt_OK_clicked();

private:
    void ForceDisconnectAndCleanup();

private:
    static const QString gStrDiscoveringState;
    static const QString gStrDiscoveredState;

    Ui::ConnectDeviceDialog *ui;

    bool mDisconnectOnClose = true;
    int mLowEnergyDiscoveryTimeout = 5000;

    QBluetoothLocalDevice *mLocalDevice = nullptr;
    QBluetoothDeviceDiscoveryAgent *mDeviceDiscoverAgent = nullptr;
    QLowEnergyController *mLowEnergyController = nullptr;
    QLowEnergyService *mLowEnergyService = nullptr;

    QTimer mTimeoutTimer;
    QList<QBluetoothDeviceInfo> mDeviceInfoList;



};

#endif // CONNECTDEVICEDIALOG_H

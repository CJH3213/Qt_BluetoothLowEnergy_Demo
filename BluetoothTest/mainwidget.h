#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QBluetoothDeviceInfo>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QListWidgetItem>
#include <QLowEnergyController>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWidget;
}
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    // ui信号-槽
    void on_bt_Send_clicked();
    void on_bt_ReceiveClear_clicked();
    void on_bt_OpenLocalDevice_clicked();
    void on_bt_Choose_clicked();

    // 自定义槽
    void OnChoseBLEDevice(QLowEnergyController *controller, QLowEnergyService *service, QLowEnergyCharacteristic &characteristic);

    // BLE信号-槽
    void OnBLECharacteristicRead(const QLowEnergyCharacteristic &characteristic, const QByteArray &bytes);
    void OnBLECharacteristicChange(const QLowEnergyCharacteristic &characteristic, const QByteArray &bytes);

private:
    void ForceDisconnectAndCleanup();

private:
    Ui::MainWidget *ui;

    QBluetoothDeviceDiscoveryAgent *mDeviceDiscoverAgent = nullptr;
    QBluetoothLocalDevice *mLocalDevice = nullptr;

    QLowEnergyController *mBLEController = nullptr;
    QLowEnergyService *mBLEService = nullptr;
    QLowEnergyCharacteristic mBLECharacteristic;
};
#endif // MAINWIDGET_H

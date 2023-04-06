#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <string>
#include <iostream>

#include "device.h"
#include "menustate.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Device device;
    QTimer* sessionTimer;
    QTimer* breathTimer;
    QTimer* batteryTimer;

    vector<string> homeMenuOptions;
    vector<string> sessionOptions;
    vector<string> settingsMenuOptions;
    vector<string> breathPacerOptions;
    vector<string> challengeLevelOptions;

    void resetGraph();
    void updateMenuList(MenuState state);
    void displayLog(int logNum);

    void turnOnIndicator(int indicatorNum);
    void playBeep();
    void resetIndicators();
    void endSession();

private slots:
    void handleUpButtonPress();
    void handleDownButtonPress();
    void handleSelectButtonPress();
    void handleBackButtonPress();
    void handleMenuButtonPress();
    void handlePowerButtonPress();
    void updateSession();
    void updateBreathPace();
    void updateBatteryLevel();
    void resetBattryLevel();
};
#endif // MAINWINDOW_H

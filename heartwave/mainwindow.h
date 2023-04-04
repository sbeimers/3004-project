#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <string>
#include <iostream>

#include "device.h"
#include "menustate.h"

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

    vector<string> homeMenuOptions;
    vector<string> settingsMenuOptions;

    void updateMenuList(MenuState state);
    void displayLog(int logNum);

private slots:
    void handleUpButtonPress();
    void handleDownButtonPress();
    void handleSelectButtonPress();
    void handleBackButtonPress();
    void handleMenuButtonPress();
};
#endif // MAINWINDOW_H

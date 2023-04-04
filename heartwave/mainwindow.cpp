#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    homeMenuOptions = {"START NEW SESSION", "SETTINGS", "VIEW HISTORY"};
    settingsMenuOptions = {"CHANGE CHALLENGE LEVEL", "CHANGE BREATHE PACE"};

    for (string s : homeMenuOptions){
        ui->menuListWidget->addItem(QString::fromStdString(s));
    }

    ui->menuListWidget->setCurrentRow(0);

    connect(ui->upButton, SIGNAL(released()), this, SLOT(handleUpButtonPress()));
    connect(ui->downButton, SIGNAL(released()), this, SLOT(handleDownButtonPress()));
    connect(ui->selectButton, SIGNAL(released()), this, SLOT(handleSelectButtonPress()));
    connect(ui->backButton, SIGNAL(released()), this, SLOT(handleBackButtonPress()));
    connect(ui->menuButton, SIGNAL(released()), this, SLOT(handleMenuButtonPress()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleUpButtonPress(){
    int currentRow = ui->menuListWidget->currentRow();
    int lastIndex = ui->menuListWidget->count();
    ui->menuListWidget->setCurrentRow(currentRow == 0 ? lastIndex - 1 : currentRow - 1);
}

void MainWindow::handleDownButtonPress(){
    int currentRow = ui->menuListWidget->currentRow();
    int lastIndex = ui->menuListWidget->count();
    ui->menuListWidget->setCurrentRow(currentRow == lastIndex - 1 ? 0 : currentRow + 1);
}

void MainWindow::handleSelectButtonPress(){
    MenuState currentState = device.getState();
    int currentRow = ui->menuListWidget->currentRow();

    if (currentState == HOME){
        switch(currentRow){
            case 0: // Start new session
                updateMenuList(ACTIVE_SESSION);
                device.changeMenuState(ACTIVE_SESSION);
                break;
            case 1: // Settings
                updateMenuList(SETTINGS);
                device.changeMenuState(SETTINGS);
                break;
            case 2: //View history
                updateMenuList(LOGS);
                device.changeMenuState(LOGS);
                break;
        }
    } else if (currentState == SETTINGS){
        switch(currentRow){
            case 0: // Change challenge level
                updateMenuList(CHALLENGE_LEVEL);
                device.changeMenuState(CHALLENGE_LEVEL);
                break;
            case 1: // Breath pacer
                updateMenuList(BREATH_PACER);
                device.changeMenuState(BREATH_PACER);
                break;
        }
    } else if (currentState == LOGS){
        device.changeMenuState(LOG);
        displayLog(currentRow);
    }

}

void MainWindow::handleBackButtonPress(){
    MenuState currentState = device.getState();

    if (currentState == SETTINGS || currentState == LOGS){
        updateMenuList(HOME);
        device.changeMenuState(HOME);
    } else if (currentState == CHALLENGE_LEVEL || currentState == BREATH_PACER){
        updateMenuList(SETTINGS);
        device.changeMenuState(SETTINGS);
    } else if (currentState == LOG){
        updateMenuList(LOGS);
        device.changeMenuState(LOGS);
    } else if (currentState == ACTIVE_SESSION){
        // Have to add aditional logic for ending session
        // The below is a placeholder
        updateMenuList(HOME);
        device.changeMenuState(HOME);
    }
}

void MainWindow::handleMenuButtonPress(){
    MenuState currentState = device.getState();
    if (currentState == ACTIVE_SESSION){
        // TODO: Implement logic for ending active session
    }
    updateMenuList(HOME);
    device.changeMenuState(HOME);
}

void MainWindow::updateMenuList(MenuState state){
    ui->menuListWidget->clear();

    // This can be changed to a switch case if we want, I don't see a reason to -Elias
    if (state == HOME){
        for (string s : homeMenuOptions){
            ui->menuListWidget->addItem(QString::fromStdString(s));
        }
        ui->menuListWidget->setCurrentRow(0);
    } else if (state == SETTINGS){
        for (string s : settingsMenuOptions){
            ui->menuListWidget->addItem(QString::fromStdString(s));
        }
        ui->menuListWidget->setCurrentRow(0);
    } else if (state == LOGS){
        // TODO: Figure out how we should display logs
        ui->menuListWidget->addItem("One must imagine logs here");
        ui->menuListWidget->setCurrentRow(0);
    } else if (state == ACTIVE_SESSION){
        // TODO: Figure out how we should display sessions
        ui->menuListWidget->addItem("One must imagine a session here");
        ui->menuListWidget->setCurrentRow(0);
    } else if (state == CHALLENGE_LEVEL){
        // TODO: Figure out how to display challenge level change
        ui->menuListWidget->addItem("One must imagine challenge levels here");
        ui->menuListWidget->setCurrentRow(0);
    } else if (state == BREATH_PACER){
        // TODO: Figure out how to display breath pacer change
        ui->menuListWidget->addItem("One must imagine breath pacer here");
        ui->menuListWidget->setCurrentRow(0);
    }
}

void MainWindow::displayLog(int logNum){
    // TODO: Figure how to display and individual log
    // The below code is a placeholder until we figure out how we want to display log info
    ui->menuListWidget->clear();
    string placeHolder = "One must imagine log " + std::to_string(logNum) + " here";
    ui->menuListWidget->addItem(QString::fromStdString(placeHolder));
}

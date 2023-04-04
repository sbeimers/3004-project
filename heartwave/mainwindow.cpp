#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    homeMenuOptions = {"START NEW SESSION", "SETTINGS", "VIEW HISTORY"};
    sessionOptions = {"Start High Coherence Session Simulation", "Start Medium Coherence Session Simulation", "Start Low Coherence Session Simulation"};
    settingsMenuOptions = {"CHANGE CHALLENGE LEVEL", "CHANGE BREATHE PACE"};
    breathPacerOptions = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30"};
    challengeLevelOptions = {"1", "2", "3", "4"};

    highCoherenceDataSet = {63.3, 66.2, 68.4, 69.7, 70.0, 69.1, 67.2, 64.6, 61.4, 58.1, 55.0, 52.4, 50.7, 50.0, 50.4, 51.9, 54.2, 57.2, 60.5, 63.7, 66.6, 68.7, 69.8, 69.9, 68.9, 66.9, 64.1, 60.9, 57.6, 54.6, 52.1, 50.5, 50.0, 50.6, 52.2, 54.6, 57.7, 61.0, 64.2, 66.9, 68.9, 69.9, 69.8, 68.6, 66.5, 63.7, 60.4, 57.1, 54.1, 51.8, 50.4, 50.0, 50.7, 52.5, 55.1, 58.2, 61.5, 64.7, 67.3, 69.1, 70.0, 69.7, 68.4, 66.1, 63.2, 59.9, 56.6, 53.7, 51.5, 50.3, 50.1, 50.9, 52.8, 55.5, 58.7, 62.0, 65.1, 67.6, 69.3, 70.0, 69.6, 68.1, 65.7, 62.7, 59.4, 56.2, 53.4, 51.3, 50.2, 50.1, 51.2, 53.2, 56.0, 59.2, 62.5, 65.5, 67.9, 69.5, 70.0, 69.4, 67.8, 65.3, 62.2, 58.9, 55.7, 53.0, 51.0, 50.1, 50.2, 51.4, 53.6, 56.4, 59.7, 63.0, 65.9, 68.2, 69.6, 70.0, 69.2, 67.5, 64.9, 61.7, 58.4, 55.3, 52.6, 50.8, 50.0, 50.3, 51.7, 54.0, 56.9, 60.2, 63.4, 66.3, 68.5, 69.8, 69.9, 69.0, 67.1, 64.4, 61.2, 57.9, 54.8, 52.3, 50.6, 50.0, 50.5, 52.0, 54.4, 57.4, 60.7, 63.9, 66.7, 68.8, 69.9, 69.9, 68.8, 66.7, 64.0, 60.7, 57.4, 54.4, 52.0, 50.5, 50.0, 50.6, 52.3, 54.8, 57.9, 61.2, 64.4, 67.1, 69.0, 69.9, 69.8, 68.5, 66.4, 63.5, 60.2, 57.0, 54.0, 51.7, 50.3, 50.0, 50.8, 52.6, 55.2, 58.4, 61.7, 64.8, 67.4, 69.2, 70.0, 69.7, 68.3, 66.0, 63.0, 59.7, 56.5, 53.6};

    for (string s : homeMenuOptions){
        ui->menuListWidget->addItem(QString::fromStdString(s));
    }

    ui->menuListWidget->setCurrentRow(0);

    ui->heartRateGraph->addGraph();
    ui->heartRateGraph->hide();


    connect(ui->upButton, SIGNAL(released()), this, SLOT(handleUpButtonPress()));
    connect(ui->downButton, SIGNAL(released()), this, SLOT(handleDownButtonPress()));
    connect(ui->selectButton, SIGNAL(released()), this, SLOT(handleSelectButtonPress()));
    connect(ui->backButton, SIGNAL(released()), this, SLOT(handleBackButtonPress()));
    connect(ui->menuButton, SIGNAL(released()), this, SLOT(handleMenuButtonPress()));

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::update);
    x = 0;
    y = 0;
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
                updateMenuList(SESSION_SELECT);
                device.changeMenuState(SESSION_SELECT);
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
    }else if (currentState == SESSION_SELECT){
        switch (currentRow){
            case 0: // High coherence session
                device.startSession(&highCoherenceDataSet);
                break;
            case 1:
                //device.startSession(&mediumCoherenceDataSet);
                break;
            case 2:
                //device.startSession(&lowCoherenceDataSet);
                break;
        }
        timer->start(5000);
        ui->menuListWidget->hide();
        ui->heartRateGraph->show();
        ui->heartRateGraph->graph(0)->data()->clear();
        ui->heartRateGraph->graph(0)->addData(0, 0);
        ui->heartRateGraph->rescaleAxes();
        ui->heartRateGraph->graph(0)->data()->clear();
        ui->heartRateGraph->replot();
        device.changeMenuState(ACTIVE_SESSION);

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
    } else if (currentState == CHALLENGE_LEVEL){
         device.setChallengeLevel(currentRow);
         updateMenuList(SETTINGS);
         device.changeMenuState(SETTINGS);
    } else if (currentState == BREATH_PACER){
         device.setBreathPace(currentRow);
         updateMenuList(SETTINGS);
         device.changeMenuState(SETTINGS);
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
        timer->stop();
        ui->heartRateGraph->hide();
        ui->menuListWidget->show();
        // Have to add aditional logic for ending session
        // The below is a placeholder
        updateMenuList(SESSION_SELECT);
        device.changeMenuState(SESSION_SELECT);
    }
}

void MainWindow::handleMenuButtonPress(){
    MenuState currentState = device.getState();
    if (currentState == ACTIVE_SESSION){
        timer->stop();
        ui->heartRateGraph->hide();
        ui->menuListWidget->show();
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
    } else if (state == SESSION_SELECT){
        for (string s : sessionOptions){
            ui->menuListWidget->addItem(QString::fromStdString(s));
        }
        ui->menuListWidget->setCurrentRow(0);
    }else if (state == SETTINGS){
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
        for (string s : challengeLevelOptions){
            ui->menuListWidget->addItem(QString::fromStdString(s));
        }
        ui->menuListWidget->setCurrentRow(device.getChallengeLevel());
    } else if (state == BREATH_PACER){
        for (string s : breathPacerOptions){
            ui->menuListWidget->addItem(QString::fromStdString(s));
        }
        ui->menuListWidget->setCurrentRow(device.getBreathPace());
    }
}

void MainWindow::displayLog(int logNum){
    // TODO: Figure how to display and individual log
    // The below code is a placeholder until we figure out how we want to display log info
    ui->menuListWidget->clear();
    string placeHolder = "One must imagine log " + std::to_string(logNum) + " here";
    ui->menuListWidget->addItem(QString::fromStdString(placeHolder));
}

void MainWindow::update(){
    device.update();
    int recordingCoherenceScore = device.getRecordingCoherenceScore();
    int recordingLength = device.getRecordingLength();
    int recordingAchievementScore = device.getRecordingAchievementScore();

    cout << recordingLength << endl;

    for (int x = recordingLength - 5; x < recordingLength; x++){
        ui->heartRateGraph->graph()->addData(x, device.getCurrentRecordingDataPoints()->at(x));
    }
    // Add logic to get plot points

    ui->heartRateGraph->rescaleAxes();
    ui->heartRateGraph->replot();

}

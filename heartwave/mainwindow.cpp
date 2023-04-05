#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    homeMenuOptions = {"START NEW SESSION", "SETTINGS", "VIEW HISTORY"};
    sessionOptions = {"Start High Coherence Session Simulation", "Start Medium Coherence Session Simulation", "Start Low Coherence Session Simulation"};
    settingsMenuOptions = {"CHANGE CHALLENGE LEVEL", "CHANGE BREATHE PACE", "RESTORE DEVICE"};
    breathPacerOptions = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30"};
    challengeLevelOptions = {"1", "2", "3", "4"};

    for (string s : homeMenuOptions){
        ui->menuListWidget->addItem(QString::fromStdString(s));
    }

    ui->menuListWidget->setCurrentRow(0);

    ui->heartRateGraph->addGraph();
    ui->heartRateGraphBox->hide();


    connect(ui->upButton, SIGNAL(released()), this, SLOT(handleUpButtonPress()));
    connect(ui->downButton, SIGNAL(released()), this, SLOT(handleDownButtonPress()));
    connect(ui->selectButton, SIGNAL(released()), this, SLOT(handleSelectButtonPress()));
    connect(ui->backButton, SIGNAL(released()), this, SLOT(handleBackButtonPress()));
    connect(ui->menuButton, SIGNAL(released()), this, SLOT(handleMenuButtonPress()));
    connect(ui->powerButton, SIGNAL(released()), this, SLOT(handlePowerButtonPress()));

    breathTimer = new QTimer(this);
    sessionTimer = new QTimer(this);
    connect(sessionTimer, &QTimer::timeout, this, &MainWindow::updateSession);
    connect(breathTimer, &QTimer::timeout, this, &MainWindow::updateBreathPace);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetGraph(){
    // Start session and breath pacertimer
    sessionTimer->start(5000);
    breathTimer->start(1000);

    // Hide menu list and show graph
    ui->menuListWidget->hide();
    ui->heartRateGraphBox->show();

    // Reset graph and rescale axes
    ui->heartRateGraph->graph(0)->data()->clear();
    ui->heartRateGraph->graph(0)->addData(0, 0);
    ui->heartRateGraph->rescaleAxes();
    ui->heartRateGraph->graph(0)->data()->clear();
    ui->heartRateGraph->replot();

    // Reset breath pacer
    ui->breathPacer->setValue(0);
}

void MainWindow::handlePowerButtonPress(){
    device.toggleOnOff();

    if (device.getOnOffState()){
       ui->menuListWidget->show();
    }else{
        sessionTimer->stop();
        breathTimer->stop();
        device.saveRecording();
        updateMenuList(HOME);
        device.changeMenuState(HOME);
        ui->menuListWidget->hide();
        ui->heartRateGraphBox->hide();
        //ui->logDetailBox->hide();
        //ui->deviceDeletionBox->hide();
        //ui->logDeletionBox->hide();
    }
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
                device.startSession(0); // 0 for option high... change maybe later
                break;
            case 1:
                //device.startSession(&mediumCoherenceDataSet);
                break;
            case 2:
                //device.startSession(&lowCoherenceDataSet);
                break;
        }

        resetGraph();

        // Change device state
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
         ui->breathPacer->setMaximum(device.getBreathPace());
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
        sessionTimer->stop();
        breathTimer->stop();
        device.saveRecording();
        ui->heartRateGraphBox->hide();
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
        sessionTimer->stop();
        breathTimer->stop();
        device.saveRecording();
        ui->heartRateGraphBox->hide();
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

void MainWindow::updateSession(){
    device.update();
    int recordingCoherenceScore = device.getRecordingCoherenceScore();
    int recordingLength = device.getRecordingLength();
    int recordingAchievementScore = device.getRecordingAchievementScore();

    cout << recordingLength << endl;

    for (int x = recordingLength - 5; x < recordingLength; x++){
        ui->heartRateGraph->graph()->addData(x, device.getRecordingDataPoints()->at(x));
    }
    // Add logic to get plot points

    ui->heartRateGraph->rescaleAxes();
    ui->heartRateGraph->replot();
}


void MainWindow::updateBreathPace(){
    int currentValue = ui->breathPacer->value();
    int maxValue = ui->breathPacer->maximum();
    ui->breathPacer->setValue(currentValue == maxValue ? 0 : currentValue + 1);
}

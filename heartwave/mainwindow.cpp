#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    homeMenuOptions = {"START NEW SESSION", "SETTINGS", "VIEW HISTORY"};
    sessionOptions = {"Start High Coherence Session Simulation", "Start Medium Coherence Session Simulation", "Start Low Coherence Session Simulation"};
    settingsMenuOptions = {"CHANGE CHALLENGE LEVEL", "CHANGE BREATH PACER INTERVAL", "RESTORE DEVICE"};
    breathPacerOptions = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30"};
    challengeLevelOptions = {"1", "2", "3", "4"};

    for (string s : homeMenuOptions){
        ui->menuListWidget->addItem(QString::fromStdString(s));
    }

    ui->menuListWidget->setCurrentRow(0);

    ui->heartRateGraph->addGraph();
    ui->heartRateGraphBox->hide();

    ui->heartRateDetailGraph->addGraph();
    ui->detailSaveDelList->addItem("RETURN");
    ui->detailSaveDelList->addItem("DELETE");
    ui->logDetailBox->hide();

    connect(ui->upButton, SIGNAL(released()), this, SLOT(handleUpButtonPress()));
    connect(ui->downButton, SIGNAL(released()), this, SLOT(handleDownButtonPress()));
    connect(ui->selectButton, SIGNAL(released()), this, SLOT(handleSelectButtonPress()));
    connect(ui->backButton, SIGNAL(released()), this, SLOT(handleBackButtonPress()));
    connect(ui->menuButton, SIGNAL(released()), this, SLOT(handleMenuButtonPress()));
    connect(ui->powerButton, SIGNAL(released()), this, SLOT(handlePowerButtonPress()));
    connect(ui->rechargeBattryButton, SIGNAL(released()), this, SLOT(resetBatteryLevel()));

    breathTimer = new QTimer(this);
    sessionTimer = new QTimer(this);
    batteryTimer = new QTimer(this);
    connect(sessionTimer, &QTimer::timeout, this, &MainWindow::updateSession);
    connect(breathTimer, &QTimer::timeout, this, &MainWindow::updateBreathPace);
    connect(batteryTimer, &QTimer::timeout, this, &MainWindow::updateBatteryLevel);
    batteryTimer->start(15000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startSession(){
    // Start session and breath pacertimer
    sessionTimer->start(5000);
    breathTimer->start(1000);

    // Hide menu list and show graph
    ui->menuListWidget->hide();
    ui->heartRateGraphBox->show();

    resetGraph();


    // Reset breath pacer
    ui->breathPacer->setValue(0);

}

void MainWindow::resetLogGraph(){
    ui->heartRateDetailGraph->graph(0)->data()->clear();
    ui->heartRateDetailGraph->graph(0)->addData(0, 0);
    ui->heartRateDetailGraph->rescaleAxes();
    ui->heartRateDetailGraph->graph(0)->data()->clear();
    ui->heartRateDetailGraph->replot();
}
void MainWindow::resetGraph(){

    // Reset graph and rescale axes
    ui->heartRateGraph->graph(0)->data()->clear();
    ui->heartRateGraph->graph(0)->addData(0, 0);
    ui->heartRateGraph->rescaleAxes();
    ui->heartRateGraph->graph(0)->data()->clear();
    ui->heartRateGraph->replot();

}

void MainWindow::handlePowerButtonPress(){
    if (device.getBatteryLevel() <= 0) { return; }
    device.toggleOnOff();
    MenuState currentState = device.getState();

    if (device.getOnOffState()){
       ui->menuListWidget->show();
    }else{
        if (currentState == ACTIVE_SESSION) {
            endSession(); //stops timers and resets indicators
            device.saveRecording();
        }
        updateMenuList(HOME);
        device.changeMenuState(HOME);
        ui->menuListWidget->hide();
        ui->heartRateGraphBox->hide();
        ui->logDetailBox->hide();
        ui->readingIndicator->setStyleSheet("color: white;");
    }
}

void MainWindow::handleUpButtonPress(){
    if (device.getOnOffState() == false) { return; }
    MenuState currentState = device.getState();

    int currentRow;
    int lastIndex;

    if (currentState == LOG || currentState == SESSION_END){
        currentRow = ui->detailSaveDelList->currentRow();
        lastIndex = ui->detailSaveDelList->count();
        ui->detailSaveDelList->setCurrentRow(currentRow == 0 ? lastIndex - 1: currentRow - 1);
    }else {
        currentRow = ui->menuListWidget->currentRow();
        lastIndex = ui->menuListWidget->count();
        ui->menuListWidget->setCurrentRow(currentRow == 0 ? lastIndex - 1 : currentRow - 1);
    }
}

void MainWindow::handleDownButtonPress(){
    if (device.getOnOffState() == false) { return; }
    MenuState currentState = device.getState();

    int currentRow;
    int lastIndex;

    if (currentState == LOG || currentState == SESSION_END){
        currentRow = ui->detailSaveDelList->currentRow();
        lastIndex = ui->detailSaveDelList->count();
        ui->detailSaveDelList->setCurrentRow(currentRow == lastIndex - 1 ? 0 : currentRow + 1);
    }else {
        currentRow = ui->menuListWidget->currentRow();
        lastIndex = ui->menuListWidget->count();
        ui->menuListWidget->setCurrentRow(currentRow == lastIndex - 1 ? 0 : currentRow + 1);
    }
}

void MainWindow::handleSelectButtonPress(){
    if (device.getOnOffState() == false) { return; }
    MenuState currentState = device.getState();
    int menuListWidgetRow = ui->menuListWidget->currentRow();
    int saveDelListRow = ui->detailSaveDelList->currentRow();

    if (currentState == HOME){
        switch(menuListWidgetRow){
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

    } else if (currentState == SESSION_SELECT){
        switch (menuListWidgetRow){
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

        startSession();

        // Change device state
        device.changeMenuState(ACTIVE_SESSION);

        // Turn on reading indicator
        ui->readingIndicator->setStyleSheet("color: red;");

    } else if (currentState == SETTINGS){
        switch(menuListWidgetRow){
            case 0: // Change challenge level
                updateMenuList(CHALLENGE_LEVEL);
                device.changeMenuState(CHALLENGE_LEVEL);
                break;
            case 1: // Breath pacer
                updateMenuList(BREATH_PACER);
                device.changeMenuState(BREATH_PACER);
                break;
            case 2: // restore device
                device.restore();
                updateMenuList(HOME);
                device.changeMenuState(HOME);
                ui->breathPacer->setMaximum(device.getBreathPace());
                break;
        }

    } else if (currentState == CHALLENGE_LEVEL){
         device.setChallengeLevel(menuListWidgetRow);
         updateMenuList(SETTINGS);
         device.changeMenuState(SETTINGS);

    } else if (currentState == BREATH_PACER){
         device.setBreathPace(menuListWidgetRow);
         ui->breathPacer->setMaximum(device.getBreathPace());
         updateMenuList(SETTINGS);
         device.changeMenuState(SETTINGS);

    } else if (currentState == LOGS){
        device.changeMenuState(LOG);
        displayLog(menuListWidgetRow);

    } else if (currentState == ACTIVE_SESSION){
        endSession(); //stops timers and resets indicators
        device.saveRecording();
        displayLog(device.getLogs().size() - 1);
        device.changeMenuState(SESSION_END);
        ui->readingIndicator->setStyleSheet("color: white;");

    } else if (currentState == SESSION_END){
        if (saveDelListRow == 1){ device.deleteLog(device.getLogs().size() - 1); }
        device.changeMenuState(SESSION_SELECT);
        ui->logDetailBox->hide();
        ui->menuListWidget->show();
        updateMenuList(SESSION_SELECT);

    } else if (currentState == LOG){
        QString uiDateStr = ui->logDetailBox->title();
        if (saveDelListRow == 1){ device.deleteLog(device.getLogIndexByDate(uiDateStr)); }
        device.changeMenuState(LOGS);
        ui->logDetailBox->hide();
        ui->menuListWidget->show();
        updateMenuList(LOGS);
    }

}

void MainWindow::handleBackButtonPress(){
    if (device.getOnOffState() == false) { return; }
    MenuState currentState = device.getState();

    if (currentState == SESSION_SELECT || currentState == SETTINGS || currentState == LOGS){
        updateMenuList(HOME);
        device.changeMenuState(HOME);
    } else if (currentState == CHALLENGE_LEVEL || currentState == BREATH_PACER){
        updateMenuList(SETTINGS);
        device.changeMenuState(SETTINGS);
    } else if (currentState == LOG){
        ui->logDetailBox->hide();
        ui->menuListWidget->show();
        updateMenuList(LOGS);
        device.changeMenuState(LOGS);
    } else if (currentState == ACTIVE_SESSION){
        endSession(); //stops timers and resets indicators
        device.saveRecording();
        displayLog(device.getLogs().size() - 1);
        device.changeMenuState(SESSION_END);
        ui->readingIndicator->setStyleSheet("color: white;");
    } else if (currentState == SESSION_END){
        updateMenuList(SESSION_SELECT);
        device.changeMenuState(SESSION_SELECT);
        ui->logDetailBox->hide();
        ui->menuListWidget->show();
    }
}

void MainWindow::handleMenuButtonPress(){
    if (device.getOnOffState() == false) { return; }
    MenuState currentState = device.getState();
    if (currentState == ACTIVE_SESSION){
        endSession(); //stops timers and resets indicators
        device.saveRecording();
        ui->heartRateGraphBox->hide();
        ui->readingIndicator->setStyleSheet("color: white;");
    } else if (currentState == SESSION_END || currentState == LOG){
        ui->logDetailBox->hide();
    }
    ui->menuListWidget->show();
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
        for (int x = 0; x < device.getLogs().size(); ++x){
            ui->menuListWidget->addItem(QString::fromStdString(std::to_string(x + 1) + ": ") + device.getLogs().at(x)->getDate());
        }
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
    // Hide logs list and set menu list back to logs
    ui->menuListWidget->hide();
    ui->heartRateGraphBox->hide();

    // Get selected log
    Log* currentLog = device.getLogs().at(logNum);

    // Update ui details with log info
    ui->logDetailBox->setTitle("Log summary: " + currentLog->getDate());
    ui->detailChallengeLevelLabel->setText(QString("Challenge level: ") + QString::number(currentLog->getChallengeLevel(), 'f', 1));
    ui->detailSesLenLabel->setText(QString("Session length: ") + QString::number(currentLog->getLengthOfSession(), 'f', 1));
    ui->detailAchScoreLabel->setText(QString("Achievement score: ") + QString::number(currentLog->getAchievementScore(), 'f', 1));
    ui->detailAvgCoherenceLabel->setText(QString("Average coherence: ") + QString::number(currentLog->getAverageCoherence(), 'f', 1));
    ui->detailLowLabel->setText(QString("Low: ") + QString::number(currentLog->getLowPercentage(), 'f', 1) + QString("%"));
    ui->detailMedLabel->setText(QString("Med: ") + QString::number(currentLog->getMediumPercentage(), 'f', 1) + QString("%"));
    ui->detailHighLabel->setText(QString("High: ") + QString::number(currentLog->getHighPercentage(), 'f', 1) + QString("%"));

    resetLogGraph();
    // Update detail graph
    vector<float> currentLogPlotPoints = currentLog->getPlotPoints();

    for (int x = 0; x < currentLogPlotPoints.size(); ++x){
        ui->heartRateDetailGraph->graph(0)->addData(x, currentLogPlotPoints.at(x));
    }

    ui->heartRateDetailGraph->rescaleAxes();
    ui->heartRateDetailGraph->replot();

    // Show log detail box
    ui->logDetailBox->show();
    ui->detailSaveDelList->setCurrentRow(0);
}

void MainWindow::updateSession(){
    device.update();
    int recordingCoherenceScore = device.getRecordingCoherenceScore();
    int recordingLength = device.getRecordingLength();
    int recordingAchievementScore = device.getRecordingAchievementScore();

    //logic to get the 5 plot points from the device class
    for (int x = 0; x < 5; x++){
        ui->heartRateGraph->graph(0)->addData(recordingLength - 5 + x, ui->applyToSkinCheckbox->isChecked() ? device.getRecordingDataPoints().at(x) : 0);
    }

    //rescale the graph
    ui->heartRateGraph->rescaleAxes();
    ui->heartRateGraph->replot();

    //turn on an indicator
     int indicator = device.getIndicator(); //gets the indicator number to turn on
    turnOnIndicator(indicator); //changes the indicator colour

    //play a beep
    playBeep(); //plays a beep noise every 5 seconds (console log)
}


void MainWindow::updateBreathPace(){
    int currentValue = ui->breathPacer->value();
    int maxValue = ui->breathPacer->maximum();
    ui->breathPacer->setValue(currentValue == maxValue ? 0 : currentValue + 1);
}

void MainWindow::updateBatteryLevel() {
    int batteryTick = 2;
    if (device.getOnOffState() == true) {
        int currentBattery = device.getBatteryLevel();
        device.setBatteryLevel(currentBattery - batteryTick);
        currentBattery = device.getBatteryLevel();
        if (currentBattery <= 0) {
            ui->batteryBar->setValue(0);
            // turn off device.
            device.setBatteryLevel(1);
            handlePowerButtonPress();
            device.setBatteryLevel(0);
        } else if (currentBattery <= 20) {
            ui->batteryBar->setValue(currentBattery);
            ui->batteryBar->setStyleSheet("QProgressBar::chunk {background-color: rgb(239, 41, 41);}");
        } else {
            ui->batteryBar->setValue(currentBattery);
            ui->batteryBar->setStyleSheet("QProgressBar::chunk {background-color: rgb(138, 226, 52);}");
        }
    }
}

void MainWindow::resetBatteryLevel() {
    device.resetBatteryLevel();
    ui->batteryBar->setValue(device.getBatteryLevel());
    ui->batteryBar->setStyleSheet("QProgressBar::chunk {background-color: rgb(138, 226, 52);}");
}

//turns on specified indicator number
void MainWindow::turnOnIndicator(int indicatorNum){
    resetIndicators();
    if(indicatorNum == 0){
        ui->coherenceRed->setStyleSheet (ui->coherenceRed->styleSheet() + "background-color: #ff5252");
    }
    else if(indicatorNum == 1){
        ui->coherenceBlue->setStyleSheet(ui->coherenceBlue->styleSheet() +"background-color: #27aeff");
    }
    else{
        ui->coherenceGreen->setStyleSheet(ui->coherenceGreen->styleSheet() +"background-color: #4bd67e");
    }
}

//console logs a beep every 5 seconds
void MainWindow::playBeep(){
    cout<<"Beep."<<endl;
}

//changes the indicators back to their default styles
void MainWindow::resetIndicators(){
    ui->coherenceRed->setStyleSheet("border-width: 1; border-radius: 10; border-style: solid; border-color: white;");
    ui->coherenceBlue->setStyleSheet("border-width: 1; border-radius: 10; border-style: solid; border-color: white;");
    ui->coherenceGreen->setStyleSheet("border-width: 1; border-radius: 10; border-style: solid; border-color: white;");
}

//ends the session: stops all timers and resets indicators. called when menu, back, or select button is pressed during active session.
void MainWindow::endSession(){
    sessionTimer->stop();
    breathTimer->stop();
    resetIndicators();
}

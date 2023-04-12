#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Vectors of strings containing menu options for different screens
    homeMenuOptions = {"START NEW SESSION", "SETTINGS", "VIEW HISTORY"};
    sessionOptions = {"Start High Coherence Session Simulation", "Start Medium Coherence Session Simulation", "Start Low Coherence Session Simulation"};
    settingsMenuOptions = {"CHANGE CHALLENGE LEVEL", "CHANGE BREATH PACER INTERVAL", "RESTORE DEVICE"};
    breathPacerOptions = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30"};
    challengeLevelOptions = {"1", "2", "3", "4"};

    // Device initially shows home menu so home menu options are added
    for (string s : homeMenuOptions){
        ui->menuListWidget->addItem(QString::fromStdString(s));
    }

    ui->menuListWidget->setCurrentRow(0);

    // activeSessionBox contains all UI elements related to active session reading
    ui->activeSessionHeartRateGraph->addGraph(); // Graphs from qtcustomplot need to be added manually
    ui->activeSessionBox->hide();

    // logDetailBox contains all UI elements related to log details
    ui->logDetailHeartRateGraph->addGraph();
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

// Start session logic
void MainWindow::startSession(){
    // Start session and breath pacertimer
    sessionTimer->start(5000);
    breathTimer->start(1000);

    // Hide menu list and show graph
    ui->menuListWidget->hide();
    ui->activeSessionBox->show();

    resetActiveSessionGraph();

    // Reset breath pacer
    ui->breathPacer->setValue(0);

    //reset labels
    ui->activeSessionCoherenceScoreLabel->setText(QString::number(0));
    ui->activeSessionLengthLabel->setText(QString::number(0) + " s");
    ui->activeSessionAchievementScoreLabel->setText(QString::number(0));
}

// End session logic
// Stops all timers and resets indicators
// Called when menu, back, or select button is pressed during active session or when
// device is removed from skin during active session.
void MainWindow::endSession(){
    sessionTimer->stop();
    breathTimer->stop();
    resetIndicators();
}

// Turns on specified indicator number
void MainWindow::turnOnIndicator(int indicatorNum){
    resetIndicators();
    if(indicatorNum == 0){
        ui->coherenceRed->setStyleSheet(ui->coherenceRed->styleSheet() + "background-color: #ff5252");
    }
    else if(indicatorNum == 1){
        ui->coherenceBlue->setStyleSheet(ui->coherenceBlue->styleSheet() +"background-color: #27aeff");
    }
    else{
        ui->coherenceGreen->setStyleSheet(ui->coherenceGreen->styleSheet() +"background-color: #4bd67e");
    }
}

// Changes device indicators back to their default styles
void MainWindow::resetIndicators(){
    ui->coherenceRed->setStyleSheet("border-width: 1; border-radius: 10; border-style: solid; border-color: white;");
    ui->coherenceBlue->setStyleSheet("border-width: 1; border-radius: 10; border-style: solid; border-color: white;");
    ui->coherenceGreen->setStyleSheet("border-width: 1; border-radius: 10; border-style: solid; border-color: white;");
}

// Update menu list widget items based on device state
void MainWindow::updateMenuList(DeviceState state){
    // Clear listems for current widget
    ui->menuListWidget->clear();

    // UI menuListWidget items are changed depending on device state
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

    } else if (state == SETTINGS){
        for (string s : settingsMenuOptions){
            ui->menuListWidget->addItem(QString::fromStdString(s));
        }
        ui->menuListWidget->setCurrentRow(0);

    } else if (state == LOGS){
        for (unsigned long x = 0; x < device.getLogs().size(); ++x){
            ui->menuListWidget->addItem(QString::fromStdString(std::to_string(x + 1) + ": ") + device.getLogs().at(x)->getDate());
        }
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

// Reset active session graph and rescale axes
void MainWindow::resetActiveSessionGraph(){
    ui->activeSessionHeartRateGraph->graph(0)->data()->clear();
    ui->activeSessionHeartRateGraph->graph(0)->addData(0, 0);
    ui->activeSessionHeartRateGraph->rescaleAxes();
    ui->activeSessionHeartRateGraph->graph(0)->data()->clear();
    ui->activeSessionHeartRateGraph->replot();
}

// Reset log detail graph
void MainWindow::resetLogGraph(){
    ui->logDetailHeartRateGraph->graph(0)->data()->clear();
    ui->logDetailHeartRateGraph->graph(0)->addData(0, 0);
    ui->logDetailHeartRateGraph->rescaleAxes();
    ui->logDetailHeartRateGraph->graph(0)->data()->clear();
    ui->logDetailHeartRateGraph->replot();
}

// Display log detail view
void MainWindow::displayLog(int logNum){
    // Hide logs list and set menu list back to logs
    ui->menuListWidget->hide();
    ui->activeSessionBox->hide();

    // Get selected log
    Log* currentLog = device.getLogs().at(logNum);

    // Update ui details with log info
    ui->logDetailBox->setTitle("Log summary: " + currentLog->getDate());
    ui->detailChallengeLevelLabel->setText(QString("Challenge level: ") + QString::number(currentLog->getChallengeLevel()+1));
    ui->detailSesLenLabel->setText(QString("Session length: ") + QString::number(currentLog->getLengthOfSession() )+ QString(" sec"));
    ui->detailAchScoreLabel->setText(QString("Achievement score: ") + QString::number(currentLog->getAchievementScore()));
    ui->detailAvgCoherenceLabel->setText(QString("Average coherence: ") + QString::number(currentLog->getAverageCoherence(), 'f', 1));
    ui->detailLowLabel->setText(QString("Low: ") + QString::number(currentLog->getLowPercentage(), 'f', 1) + QString("%"));
    ui->detailMedLabel->setText(QString("Med: ") + QString::number(currentLog->getMediumPercentage(), 'f', 1) + QString("%"));
    ui->detailHighLabel->setText(QString("High: ") + QString::number(currentLog->getHighPercentage(), 'f', 1) + QString("%"));

    // Update detail graph
    resetLogGraph();
    vector<float> currentLogPlotPoints = currentLog->getPlotPoints();

    for (int x = 0; x < currentLogPlotPoints.size(); ++x){
        ui->logDetailHeartRateGraph->graph(0)->addData(x, currentLogPlotPoints.at(x));
    }

    ui->logDetailHeartRateGraph->rescaleAxes();
    ui->logDetailHeartRateGraph->replot();

    // Show log detail box
    ui->logDetailBox->show();
    ui->detailSaveDelList->setCurrentRow(0);
}

// Console logs a beep every 5 seconds during an active session
void MainWindow::playBeep(){
    cout<<"Beep."<<endl;
}


void MainWindow::handleUpButtonPress(){
    if (device.getOnOffState() == false) { return; }
    DeviceState currentState = device.getState();

    int currentRow;
    int lastIndex;

    // Current row index wraps
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
    DeviceState currentState = device.getState();

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

    DeviceState currentState = device.getState();
    int menuListWidgetRow = ui->menuListWidget->currentRow();
    int saveDelListRow = ui->detailSaveDelList->currentRow();

    // Select button behavior changes depending on device state
    if (currentState == HOME){
        switch(menuListWidgetRow){
            case 0: // Start new session
                updateMenuList(SESSION_SELECT);
                device.changeState(SESSION_SELECT);
                break;
            case 1: // Settings
                updateMenuList(SETTINGS);
                device.changeState(SETTINGS);
                break;
            case 2: //View history
                updateMenuList(LOGS);
                device.changeState(LOGS);
                break;
        }
    } else if (currentState == SESSION_SELECT){
        if(ui->applyToSkinCheckbox->isChecked()){
            switch (menuListWidgetRow){
                case 0: // High coherence session
                    device.startSession(0);
                    break;
                case 1: //Medium coherence session
                    device.startSession(1);
                    break;
                case 2: //Low coherence session
                    device.startSession(2);
                    break;
            }

        startSession();

        // Change device state
        device.changeState(ACTIVE_SESSION);

        // Turn on reading indicator
        ui->readingIndicator->setStyleSheet("color: red;");
        }
        else{
            qDebug("Not applied to skin. Cannot start session.");
        }
    }

    else if (currentState == SETTINGS){
        switch(menuListWidgetRow){
            case 0: // Change challenge level
                updateMenuList(CHALLENGE_LEVEL);
                device.changeState(CHALLENGE_LEVEL);
                break;
            case 1: // Breath pacer
                updateMenuList(BREATH_PACER);
                device.changeState(BREATH_PACER);
                break;
            case 2: // restore device
                device.restore();
                updateMenuList(HOME);
                device.changeState(HOME);
                ui->breathPacer->setMaximum(device.getBreathPace());
                break;
        }

    } else if (currentState == CHALLENGE_LEVEL){
         // Update challenge level
         device.setChallengeLevel(menuListWidgetRow);
         updateMenuList(SETTINGS);
         device.changeState(SETTINGS);

    } else if (currentState == BREATH_PACER){
         // Update breath pace rate
         device.setBreathPace(menuListWidgetRow);
         ui->breathPacer->setMaximum(device.getBreathPace());
         updateMenuList(SETTINGS);
         device.changeState(SETTINGS);

    } else if (currentState == LOGS){
        // Display single log
        device.changeState(LOG);
        displayLog(menuListWidgetRow);

    } else if (currentState == ACTIVE_SESSION){
        endSession(); //stops timers and resets indicators
        device.saveRecording();
        displayLog(device.getLogs().size() - 1);
        device.changeState(SESSION_END);
        ui->readingIndicator->setStyleSheet("color: white;");

    } else if (currentState == SESSION_END){
        if (saveDelListRow == 1){ device.deleteLog(device.getLogs().size() - 1); }
        device.changeState(SESSION_SELECT);
        ui->logDetailBox->hide();
        ui->menuListWidget->show();
        updateMenuList(SESSION_SELECT);

    } else if (currentState == LOG){
        QString uiDateStr = ui->logDetailBox->title();
        if (saveDelListRow == 1){ device.deleteLog(device.getLogIndexByDate(uiDateStr)); }
        device.changeState(LOGS);
        ui->logDetailBox->hide();
        ui->menuListWidget->show();
        updateMenuList(LOGS);
    }
}

void MainWindow::handleBackButtonPress(){
    if (device.getOnOffState() == false) { return; }
    DeviceState currentState = device.getState();

    // Every state is only accessible via exactly one other state
    // Because of this, by getting the current state of the device
    // we always know the state before it to revert back to
    if (currentState == SESSION_SELECT || currentState == SETTINGS || currentState == LOGS){
        updateMenuList(HOME);
        device.changeState(HOME);
    } else if (currentState == CHALLENGE_LEVEL || currentState == BREATH_PACER){
        updateMenuList(SETTINGS);
        device.changeState(SETTINGS);
    } else if (currentState == LOG){
        ui->logDetailBox->hide();
        ui->menuListWidget->show();
        updateMenuList(LOGS);
        device.changeState(LOGS);
    } else if (currentState == ACTIVE_SESSION){
        endSession(); //stops timers and resets indicators
        device.saveRecording();
        displayLog(device.getLogs().size() - 1);
        device.changeState(SESSION_END);
        ui->readingIndicator->setStyleSheet("color: white;");
    } else if (currentState == SESSION_END){
        updateMenuList(SESSION_SELECT);
        device.changeState(SESSION_SELECT);
        ui->logDetailBox->hide();
        ui->menuListWidget->show();
    }
}

void MainWindow::handleMenuButtonPress(){
    // Menu button always reverts device back to home state
    if (device.getOnOffState() == false) { return; }
    DeviceState currentState = device.getState();

    // If active session is in progress, session is ended first
    if (currentState == ACTIVE_SESSION){
        endSession(); //stops timers and resets indicators
        device.saveRecording();
        ui->activeSessionBox->hide();
        ui->readingIndicator->setStyleSheet("color: white;");
    } else if (currentState == SESSION_END || currentState == LOG){
        ui->logDetailBox->hide();
    }
    ui->menuListWidget->show();
    updateMenuList(HOME);
    device.changeState(HOME);
}

void MainWindow::handlePowerButtonPress(){
    // Device turns of and reverts back to home state
    if (device.getBatteryLevel() <= 0) { return; }
    device.toggleOnOff();
    DeviceState currentState = device.getState();

    // If device is off, it turns on
    // Otherwise, if device is turned off during an active session
    // session is ended and device turns off
    if (device.getOnOffState()){
       ui->menuListWidget->show();
    }else{
        if (currentState == ACTIVE_SESSION) {
            endSession(); //stops timers and resets indicators
            device.saveRecording();
        }
        updateMenuList(HOME);
        device.changeState(HOME);
        ui->menuListWidget->hide();
        ui->activeSessionBox->hide();
        ui->logDetailBox->hide();
        ui->readingIndicator->setStyleSheet("color: white;");
    }
}

// Called by sessionTimer every 5 seconds during an active session
void MainWindow::updateSession(){
    // If device is not applied to skin on update, session ends
    if(!ui->applyToSkinCheckbox->isChecked()){
        qDebug("Sensor removed from skin. Ending session.");
        if (device.getState() == ACTIVE_SESSION){
                endSession(); //stops timers and resets indicators
                device.saveRecording();
                displayLog(device.getLogs().size() - 1);
                device.changeState(SESSION_END);
                ui->readingIndicator->setStyleSheet("color: white;");
        }
        return;
    }

    // Updates readings in recording
    device.update();

    float recordingCoherenceScore = device.getRecordingCoherenceScore();
    int recordingLength = device.getRecordingLength();
    float recordingAchievementScore = device.getRecordingAchievementScore();


    //logic to get the 5 plot points from the device class
    for (int x = 0; x < 5; x++){
        ui->activeSessionHeartRateGraph->graph(0)->addData(recordingLength - 5 + x,  device.getRecordingDataPoints().at(x));
    }

    //rescale the graph
    ui->activeSessionHeartRateGraph->rescaleAxes();
    ui->activeSessionHeartRateGraph->replot();

    //update labels
    ui->activeSessionCoherenceScoreLabel->setText(QString::number(recordingCoherenceScore, 'f', 1));
    ui->activeSessionLengthLabel->setText(QString::number(recordingLength) + " s");
    ui->activeSessionAchievementScoreLabel->setText(QString::number(recordingAchievementScore, 'f', 1));

    //turn on an indicator
    int indicator = device.getIndicator(); //gets the indicator number to turn on
    turnOnIndicator(indicator); //changes the indicator colour

    //play a beep
    playBeep(); //plays a beep noise every 5 seconds (console log)
}

// Called by breathTimer every x seconds where x is set by the user on the device
void MainWindow::updateBreathPace(){
    int currentValue = ui->breathPacer->value();
    int maxValue = ui->breathPacer->maximum();
    ui->breathPacer->setValue(currentValue == maxValue ? 0 : currentValue + 1);
}

// Called by batteryTimer every 15 seconds
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

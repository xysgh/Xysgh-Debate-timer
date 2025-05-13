#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    labelStage(new QLabel(this)),
    labelSide(new QLabel(this)),
    labelTime(new QLabel(this)),
    buttonStartPause(new QPushButton("开始", this)),
    buttonSwitch(new QPushButton("切换发言方", this)),
    buttonReset(new QPushButton("重置", this)),
    comboStage(new QComboBox(this)),
    timer(new QTimer(this))
{
    setWindowTitle("Xysgh的辩论赛计时器");

    comboStage->addItem("自由辩论");      // 0
    comboStage->addItem("陈词反驳");      // 1
    comboStage->addItem("总结阶段");      // 2
    comboStage->setCurrentIndex(1);       // 默认选“陈词反驳”

    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;

    labelStage->setAlignment(Qt::AlignCenter);
    labelSide->setAlignment(Qt::AlignCenter);
    labelTime->setAlignment(Qt::AlignCenter);

    labelStage->setStyleSheet("font-size: 20px;");
    labelSide->setStyleSheet("font-size: 24px;");
    labelTime->setStyleSheet("font-size: 48px; color: red;");

    layout->addWidget(comboStage);
    layout->addWidget(labelStage);
    layout->addWidget(labelSide);
    layout->addWidget(labelTime);
    layout->addWidget(buttonStartPause);
    layout->addWidget(buttonSwitch);
    layout->addWidget(buttonReset);

    central->setLayout(layout);
    setCentralWidget(central);

    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);
    connect(buttonStartPause, &QPushButton::clicked, this, &MainWindow::startPauseTimer);
    connect(buttonSwitch, &QPushButton::clicked, this, &MainWindow::switchSide);
    connect(buttonReset, &QPushButton::clicked, this, &MainWindow::resetTimer);
    connect(comboStage, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::stageChanged);

    timer->setInterval(1000); // 1秒

    soundEffect.setSource(QUrl("qrc:/sounds/Sounds/Ding.wav"));
    soundEffect.setVolume(1.0);

    statusBar()->showMessage("由Xysgh开发的辩论计时器,本程序使用 MIT License 开源发布");

    updateDisplay();
}

void MainWindow::startPauseTimer() {
    running = !running;
    if (running) {
        timer->start();
        buttonStartPause->setText("暂停");
    } else {
        timer->stop();
        buttonStartPause->setText("开始");
    }
}

void MainWindow::switchSide() {
    sideA = !sideA;
    updateDisplay();
}

void MainWindow::resetTimer() {
    timeFreeA = 180;
    timeFreeB = 180;
    timeSummaryA = 840;
    timeSummaryB = 840;
    timeConclusionA = 120;
    timeConclusionB = 120;
    running = false;
    timer->stop();
    buttonStartPause->setText("开始");
    updateDisplay();
}

void MainWindow::stageChanged(int index) {
    currentStage = (Stage)index;
    updateDisplay();
}

void MainWindow::updateTimer() {
    bool justZero = false;

    if (currentStage == FreeDebate) {
        if (sideA && timeFreeA > 0) timeFreeA--;
        else if (!sideA && timeFreeB > 0) timeFreeB--;
        if ((sideA && timeFreeA == 0) || (!sideA && timeFreeB == 0)) justZero = true;
    } else if (currentStage == Summary) {
        if (sideA && timeSummaryA > 0) timeSummaryA--;
        else if (!sideA && timeSummaryB > 0) timeSummaryB--;
        if ((sideA && timeSummaryA == 0) || (!sideA && timeSummaryB == 0)) justZero = true;
    } else if (currentStage == Conclusion) {
        if (sideA && timeConclusionA > 0) timeConclusionA--;
        else if (!sideA && timeConclusionB > 0) timeConclusionB--;
        if ((sideA && timeConclusionA == 0) || (!sideA && timeConclusionB == 0)) justZero = true;
    }

    if (justZero) soundEffect.play();

    updateDisplay();
}

void MainWindow::updateDisplay() {
    if (currentStage == FreeDebate)
        labelStage->setText("当前阶段：自由辩论");
    else if (currentStage == Summary)
        labelStage->setText("当前阶段：陈词反驳");
    else if (currentStage == Conclusion)
        labelStage->setText("当前阶段：总结阶段");

    labelSide->setText(sideA ? "当前发言方：正方" : "当前发言方：反方");

    int seconds = 0;
    if (currentStage == FreeDebate)
        seconds = sideA ? timeFreeA : timeFreeB;
    else if (currentStage == Summary)
        seconds = sideA ? timeSummaryA : timeSummaryB;
    else if (currentStage == Conclusion)
        seconds = sideA ? timeConclusionA : timeConclusionB;

    int minutes = seconds / 60;
    int secs = seconds % 60;
    labelTime->setText(QString("%1:%2")
                           .arg(minutes, 2, 10, QChar('0'))
                           .arg(secs, 2, 10, QChar('0')));
}

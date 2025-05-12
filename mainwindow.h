#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QTimer>
#include <QSoundEffect>
#include <QStatusBar>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void updateTimer();
    void startPauseTimer();
    void switchSide();
    void resetTimer();
    void stageChanged(int index);

private:
    void updateDisplay();

    QLabel *labelStage;
    QLabel *labelSide;
    QLabel *labelTime;
    QPushButton *buttonStartPause;
    QPushButton *buttonSwitch;
    QPushButton *buttonReset;
    QComboBox *comboStage;
    QTimer *timer;
    QSoundEffect soundEffect;

    enum Stage { FreeDebate, Summary , Conclusion};
    Stage currentStage = Summary;

    int timeFreeA = 180;
    int timeFreeB = 180;
    int timeSummaryA = 720;
    int timeSummaryB = 720;
    int timeConclusionA = 120;  // A方总结时间
    int timeConclusionB = 120;  // B方总结时间
    bool running = false;
    bool sideA = true;
};

#endif // MAINWINDOW_H

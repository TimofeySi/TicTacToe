#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QLayout>
#include <QTimer>
#include <QScreen>
#include <QGroupBox>
#include <QCheckBox>
#include <QLabel>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QStyleFactory>
#include <QLineEdit>
#include <random>
#include <fstream>

#include "ui_mainwindow.h"
#include "sfmltictactoe.h"
#include "leader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QWidget *centralWidget;

    int screenWidth;
    int screenHeight;

    QFont *mainFont;

    QTimer *waitTimer;

    SFMLScreensaver *screenSaver;
    SFMLLeaderBoard *leaderBoard;
    SFMLTicTacToe *ticTacToe;

    QGridLayout *layout;
    QHBoxLayout *mainLayout;
    QVBoxLayout *sideLayout;
    QVBoxLayout *playGroupBoxLayout;
    QHBoxLayout *characterChooseLayout;
    QVBoxLayout *inGameLayout;
    QVBoxLayout *scoreLayout;
    QVBoxLayout *moveLayout;
    QHBoxLayout *scoreIndicatorLayout;
    QHBoxLayout *moveIndicatorLayout;
    QVBoxLayout *yourScoreLayout;
    QVBoxLayout *computerScoreLayout;
    QVBoxLayout *moveYourIndicatorLayout;
    QVBoxLayout *moveComputerIndicatorLayout;
    QHBoxLayout *crossFirstLayout;
    QHBoxLayout *randomLayout;
    QVBoxLayout *saveRecordLayout;

    QGroupBox *playGroupBox;
    QGroupBox *inGameGroupBox;

    QPushButton *launchButton;
    QPushButton *crossButton;
    QPushButton *noughtButton;
    QPushButton *playButton;
    QPushButton *continueButton;
    QPushButton *againButton;
    QPushButton *finishButton;
    QPushButton *saveButton;

    QPushButton *crossLamp;
    QPushButton *noughtLamp;

    QLabel *scoreLabel;
    QLabel *moveLabel;
    QLabel *yourLabel;
    QLabel *computerLabel;
    QLabel *yourMoveLabel;
    QLabel *computerMoveLabel;
    QLabel *yourScoreLabel;
    QLabel *computerScoreLabel;
    QLabel *crossFirstLabel;
    QLabel *randomLabel;
    QLabel *saveRecordLabel;

    QCheckBox *crossFirstCheckBox;
    QCheckBox *randomCheckBox;

    int userCharacter;
    int computerCharacter;

    QString notPressedChooseButton;
    QString enableChooseButton;
    QString disableChooseButton;
    QString crossImageURL;
    QString noughtImageURL;

    QFrame *lineBetweenMoveAndScore;
    QFrame *lineBetweenScoreAndButtons;

    QLineEdit *nameLineEdit;

    QDialog *saveRecordDialog;

    QDialogButtonBox *buttonBox;

    std::map<float, std::map<std::string, std::string>> leaderboardList;
    std::vector<Leader> leadersList;

private slots:
    void launchButton_clicked();
    void prepearingMenu();

    void crossButton_clicked();
    void noughtButton_clicked();
    void playButton_clicked();

    void continueButton_clicked();
    void againButton_clicked();
    void finishButton_clicked();

    void madeMove(int player);

    void victory(int player);

    void saveRecord();

private:
    void constructorProperties();

    int randomInt(int min, int max);

    void deserialization();
    void serialization();
};

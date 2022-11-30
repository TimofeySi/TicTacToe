#include "mainwindow.h"

void MainWindow::constructorProperties()
{
    centralWidget = ui->centralwidget;
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    screenHeight= screenGeometry.height();
    screenWidth = screenGeometry.width();

    mainFont = new QFont("Sylfaen");

    this->resize(QSize(230, 120));
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->move(QPoint((screenWidth - this->width()) / 2, (screenHeight- this->height()) / 2));

    this->setWindowIcon(QIcon("resourse/tic-tac-toe-ICON"));
    this->setWindowTitle("TicTacToe");

    notPressedChooseButton = "background-color: rgb(205, 133, 63);";
    enableChooseButton = "background-color: rgb(244, 164, 96);";
    disableChooseButton = "background-color: rgb(210, 105, 30);";
    crossImageURL = "image: url(resourse/cancel_80.png);";
    noughtImageURL = "image: url(resourse/o_80.png);";

    launchButton = new QPushButton("Запуск", this);
    launchButton->setCursor(Qt::PointingHandCursor);
    launchButton->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
    launchButton->setFont(*mainFont);
    launchButton->setStyleSheet(".QPushButton {"
                                "background-color: rgb(0, 128, 0);"
                                "font: 20px;"
                                "}"
                                ".QPushButton:pressed {"
                                "background-color: rgb(154, 205, 50);"
                                "}");
    connect(launchButton, SIGNAL(clicked()), this, SLOT(launchButton_clicked()));

    layout = new QGridLayout(this);
    centralWidget->setLayout(layout);
    layout->addWidget(launchButton);
}


void MainWindow::prepearingMenu()
{
    this->setWindowFlags(Qt::Window);
    this->resize(QSize(1100, 836));
    this->move(QPoint((screenWidth - this->width()) / 2, (screenHeight- this->height()) / 2));
    this->setStyleSheet("QMainWindow {"
                        "background-image: url(resourse/background1.jpg);"
                        "}");

//    crossFirstLayout = new QHBoxLayout(this);

//    randomLayout = new QHBoxLayout(this);

//    crossFirstCheckBox = new QCheckBox(this);
//    crossFirstCheckBox->setCursor(Qt::PointingHandCursor);

//    crossFirstCheckBox->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
//    crossFirstLabel = new QLabel(this);
//    crossFirstLabel->setText("Крестики ходят первые");
//    crossFirstLabel->setStyleSheet(".QLabel {"
//                                 "font: 28px;"
//                                 "color: white;"
//                                 "}");

//    crossFirstLabel->setFont(*mainFont);
//    crossFirstLabel->setAlignment(Qt::AlignCenter);
//    crossFirstLabel->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);

//    randomCheckBox= new QCheckBox(this);
//    randomCheckBox->setCursor(Qt::PointingHandCursor);
//    randomCheckBox->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
//    randomLabel = new QLabel(this);
//    randomLabel->setText("Случайная очерёдность");
//    randomLabel->setStyleSheet(".QLabel {"
//                                 "font: 28px;"
//                                 "color: white;"
//                                 "}");

//    randomLabel->setFont(*mainFont);
//    randomLabel->setAlignment(Qt::AlignCenter);
//    randomLabel->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);

    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    mainLayout = new QHBoxLayout(this);
    centralWidget->setLayout(mainLayout);

    sideLayout = new QVBoxLayout(this);
    sideLayout->setAlignment(Qt::AlignCenter);

    playGroupBox = new QGroupBox(this);
    playGroupBox->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);

    playGroupBoxLayout = new QVBoxLayout(this);

    characterChooseLayout = new QHBoxLayout(this);

    screenSaver = new SFMLScreensaver(this);
    unsigned screenSaver_height = 780; // 797
    unsigned screenSaver_width = 780; // 989
    screenSaver->setMaximumSize(QSize(screenSaver_width, screenSaver_height));
    screenSaver->setMinimumSize(QSize(screenSaver_width, screenSaver_height));
    screenSaver->sizeHint().setHeight(screenSaver_height);
    screenSaver->sizeHint().setWidth(screenSaver_width);
    screenSaver->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);

    leaderBoard = new SFMLLeaderBoard(this);
    leaderBoard->setMinimumSize(QSize(350, 500));
    leaderBoard->setMaximumSize(QSize(350, 500));
    leaderBoard->sizeHint().setHeight(500);
    leaderBoard->sizeHint().setWidth(350);
    leaderBoard->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
    deserialization();
    leaderBoard->setLeadersList(leadersList);

    crossButton = new QPushButton("");
    crossButton->setFont(*mainFont);
    crossButton->setStyleSheet(".QPushButton {"
                               + crossImageURL
                               + notPressedChooseButton +
                               "}");

    crossButton->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    crossButton->setCursor(Qt::PointingHandCursor);
    connect(crossButton, SIGNAL(clicked()), this, SLOT(crossButton_clicked()));

    noughtButton = new QPushButton("");
    noughtButton->setFont(*mainFont);
    noughtButton->setStyleSheet(".QPushButton {"
                                + noughtImageURL
                                + notPressedChooseButton +
                                "}");
    noughtButton->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    noughtButton->setCursor(Qt::PointingHandCursor);
    connect(noughtButton, SIGNAL(clicked()), this, SLOT(noughtButton_clicked()));

    playButton = new QPushButton("Играть");
    playButton->setFont(*mainFont);
    playButton->setStyleSheet(".QPushButton {"
                              "background-color: rgb(46, 139, 87);"
                              "font: 24px;"
                              "}"
                              ".QPushButton:pressed {"
                              "background-color: rgb(60, 179, 113);"
                              "}");

    playButton->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    playButton->setCursor(Qt::PointingHandCursor);
    connect(playButton, SIGNAL(clicked()), this, SLOT(playButton_clicked()));

    mainLayout->addWidget(screenSaver);
    mainLayout->addLayout(sideLayout);

    sideLayout->addWidget(leaderBoard);
//    sideLayout->addItem(crossFirstLayout);
//    sideLayout->addItem(randomLayout);
    sideLayout->addWidget(playGroupBox);

    playGroupBox->setLayout(playGroupBoxLayout);

    playGroupBoxLayout->addLayout(characterChooseLayout);
    playGroupBoxLayout->addWidget(playButton);

    characterChooseLayout->addWidget(crossButton);
    characterChooseLayout->addWidget(noughtButton);

//    crossFirstLayout->addWidget(crossFirstCheckBox);
//    crossFirstLayout->addWidget(crossFirstLabel);

//    randomLayout->addWidget(randomCheckBox);
//    randomLayout->addWidget(randomLabel);

    userCharacter = int(Character::None);

    this->setVisible(true);
    waitTimer->stop();
    this->update();
}

void MainWindow::launchButton_clicked()
{
    this->setVisible(false);

    delete launchButton;
    delete layout;

    waitTimer = new QTimer(this);
    connect(waitTimer, SIGNAL(timeout()), this, SLOT(prepearingMenu()));
    waitTimer->setInterval(400);
    waitTimer->start();
}

void MainWindow::crossButton_clicked()
{
    if (userCharacter != int(Character::Cross))
    {
        crossButton->setEnabled(false);
        noughtButton->setEnabled(true);

        crossButton->setStyleSheet(".QPushButton {"
                                   "image: url(resourse/cancel_80.png);"
                                   + enableChooseButton +
                                   "}"); // pressed
        noughtButton->setStyleSheet(".QPushButton {"
                                    "image: url(resourse/o_80.png);"
                                    + disableChooseButton +
                                    "}"); // depressed
        userCharacter = int(Character::Cross);
    }
}

void MainWindow::noughtButton_clicked()
{
    if (userCharacter != int(Character::Nought))
    {
        crossButton->setEnabled(true);
        noughtButton->setEnabled(false);

        noughtButton->setStyleSheet(".QPushButton {"
                                    "image: url(resourse/o_80.png);"
                                    + enableChooseButton +
                                    "}"); // pressed
        crossButton->setStyleSheet(".QPushButton {"
                                   "image: url(resourse/cancel_80.png);"
                                   + disableChooseButton +
                                   "}"); // depressed
        userCharacter = int(Character::Nought);
    }
}

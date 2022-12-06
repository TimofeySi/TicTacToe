#include "mainwindow.h"

void MainWindow::constructorProperties()
{
    centralWidget = ui->centralwidget;
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    screenHeight= screenGeometry.height();
    screenWidth = screenGeometry.width();

    mainFont = new QFont("Sylfaen");

    this->setWindowIcon(QIcon("resourse/tic-tac-toe-ICON"));
    this->setWindowTitle("TicTacToe");

    notPressedChooseButton = "background-color: rgb(0, 191, 255);";
    enableChooseButton = "background-color: rgb(135, 206, 250);";
    disableChooseButton = "background-color: rgb(30, 144, 255);";
    crossImageURL = "image: url(resourse/interface_cross.png);";
    noughtImageURL = "image: url(resourse/interface_zero.png);";

    checkURL = "image: url(resourse/check.png);";
    blockURL = "image: url(resourse/block.png);";

    prepearingMenu();
}


void MainWindow::prepearingMenu()
{
    this->setWindowFlags(Qt::Window);
    this->resize(QSize(852, 418));
    this->move(QPoint((screenWidth - this->width()) / 2, (screenHeight- this->height()) / 2));
    this->setStyleSheet("QMainWindow {"
                        "background-image: url(resourse/background1.jpg);"
                        "}");

    crossFirstLayout = new QHBoxLayout(this);
    crossFirstLayout->setAlignment(Qt::AlignCenter);

    randomLayout = new QHBoxLayout(this);
    randomLayout->setAlignment(Qt::AlignCenter);

    crossFirstButton = new QPushButton(this);
    crossFirstButton->setCursor(Qt::PointingHandCursor);
    crossFirstButton->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    crossFirstButton->setStyleSheet(".QPushButton {"
                                    "background-color: rgb(20, 20, 20);"
                                    + checkURL +
                                    "}");
    connect(crossFirstButton, SIGNAL(clicked()), this, SLOT(crossFirstButton_clicked()));

    crossFirstLabel = new QLabel(this);
    crossFirstLabel->setText("Крестики ходят первые");
    crossFirstLabel->setStyleSheet(".QLabel {"
                                 "font: 28px;"
                                 "color: white;"
                                 "}");

    crossFirstLabel->setFont(*mainFont);
    crossFirstLabel->setAlignment(Qt::AlignCenter);
    crossFirstLabel->setMinimumHeight(45);
    crossFirstLabel->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);

    randomButton = new QPushButton(this);
    randomButton->setCursor(Qt::PointingHandCursor);
    randomButton->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    randomButton->setStyleSheet(".QPushButton {"
                                    "background-color: rgb(20, 20, 20);"
                                    + blockURL +
                                    "}");

    connect(randomButton, SIGNAL(clicked()), this, SLOT(randomButton_clicked()));

    randomLabel = new QLabel(this);
    randomLabel->setText("Случайная очерёдность");
    randomLabel->setStyleSheet(".QLabel {"
                                 "font: 28px;"
                                 "color: white;"
                                 "}");

    randomLabel->setFont(*mainFont);
    randomLabel->setAlignment(Qt::AlignCenter);
    randomLabel->setMinimumHeight(45);
    randomLabel->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);

    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    mainLayout = new QHBoxLayout(this);
    centralWidget->setLayout(mainLayout);

    sideLayout = new QVBoxLayout(this);

    playGroupBox = new QGroupBox(this);
    playGroupBox->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);

    playGroupBoxLayout = new QVBoxLayout(this);

    characterChooseLayout = new QHBoxLayout(this);

//    screenSaver = new SFMLScreensaver(this);
//    unsigned screenSaver_height = 780; // 797
//    unsigned screenSaver_width = 780; // 989
//    screenSaver->setMaximumSize(QSize(screenSaver_width, screenSaver_height));
//    screenSaver->setMinimumSize(QSize(screenSaver_width, screenSaver_height));
//    screenSaver->sizeHint().setHeight(screenSaver_height);
//    screenSaver->sizeHint().setWidth(screenSaver_width);
//    screenSaver->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);

    leaderBoard = new SFMLLeaderBoard(this);
    leaderBoard->setMinimumSize(QSize(500, 400));
    leaderBoard->setMaximumSize(QSize(500, 400));
    leaderBoard->sizeHint().setHeight(400);
    leaderBoard->sizeHint().setWidth(500);
    leaderBoard->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
    deserialization();

    for (auto &elem : leadersList)
    {
        float comp_score = 0.7;
        float user_score;
        std::stringstream(elem.getComputerScore()) >> comp_score;
        std::stringstream(elem.getUserScore()) >> user_score;
        float coefficient = user_score / comp_score;

        std::map<std::string, std::string> inner_map = {{"your score", elem.getUserScore()},
                                                        {"computer score", elem.getComputerScore()},
                                                        {"name", elem.getName()}
                                                       };

        while (leaderboardList.find(coefficient) != leaderboardList.end())
            coefficient -= 0.1;

        leaderboardList.insert(std::make_pair(coefficient, inner_map));
    }

    leadersList.clear();
    for (auto it = leaderboardList.rbegin(); it != leaderboardList.rend(); ++it)
    {
        if (std::find(leadersList.begin(), leadersList.end(), Leader(it->second["name"], it->second["your score"], it->second["computer score"])) == leadersList.end())
            leadersList.push_back(Leader(it->second["name"], it->second["your score"], it->second["computer score"]));
        else
            continue;
    }
    leaderBoard->setLeadersList(leadersList);


    crossButton = new QPushButton("");
    crossButton->setFont(*mainFont);
    crossButton->setStyleSheet(".QPushButton {"
                               + crossImageURL
                               + notPressedChooseButton +
                               "border-radius: 20px;"
                               "}");

    crossButton->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    crossButton->setCursor(Qt::PointingHandCursor);
    connect(crossButton, SIGNAL(clicked()), this, SLOT(crossButton_clicked()));

    noughtButton = new QPushButton("");
    noughtButton->setFont(*mainFont);
    noughtButton->setStyleSheet(".QPushButton {"
                                + noughtImageURL
                                + notPressedChooseButton +
                                "border-radius: 20px;"
                                "}");

    noughtButton->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    noughtButton->setCursor(Qt::PointingHandCursor);
    connect(noughtButton, SIGNAL(clicked()), this, SLOT(noughtButton_clicked()));

    playButton = new QPushButton("Играть");
    playButton->setFont(*mainFont);
    playButton->setStyleSheet(".QPushButton {"
                              "background-color: rgb(46, 139, 87);"
                              "border-radius: 10px;"
                              "font: 24px;"
                              "}"
                              ".QPushButton:pressed {"
                              "background-color: rgb(60, 179, 113);"
                              "border-radius: 10px;"
                              "}");

    playButton->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    playButton->setCursor(Qt::PointingHandCursor);
    connect(playButton, SIGNAL(clicked()), this, SLOT(playButton_clicked()));

    mainLayout->addWidget(leaderBoard);
    mainLayout->addLayout(sideLayout);

    sideLayout->addItem(crossFirstLayout);
    sideLayout->addItem(randomLayout);
    sideLayout->addWidget(playGroupBox);

    playGroupBox->setLayout(playGroupBoxLayout);

    playGroupBoxLayout->addLayout(characterChooseLayout);
    playGroupBoxLayout->addWidget(playButton);

    characterChooseLayout->addWidget(crossButton);
    characterChooseLayout->addWidget(noughtButton);

    crossFirstLayout->addWidget(crossFirstButton);
    crossFirstLayout->addWidget(crossFirstLabel);

    randomLayout->addWidget(randomButton);
    randomLayout->addWidget(randomLabel);

    userCharacter = int(Character::None);
    gameMode = int(GameMode::CrossFirst);

    this->setVisible(true);
    this->update();
}

void MainWindow::crossButton_clicked()
{
    if (userCharacter != int(Character::Cross))
    {
        crossButton->setEnabled(false);
        noughtButton->setEnabled(true);

        crossButton->setStyleSheet(".QPushButton {"
                                   + crossImageURL
                                   + enableChooseButton +
                                   "border-radius: 20px;"
                                   "border: 5px solid rgb(128, 0, 128);"
                                   "}"); // pressed
        noughtButton->setStyleSheet(".QPushButton {"
                                    + noughtImageURL
                                    + disableChooseButton +
                                    "border-radius: 20px;"
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
                                    + noughtImageURL
                                    + enableChooseButton +
                                    "border-radius: 20px;"
                                    "border: 5px solid rgb(128, 0, 128);"
                                    "}"); // pressed
        crossButton->setStyleSheet(".QPushButton {"
                                   + crossImageURL
                                   + disableChooseButton +
                                   "border-radius: 20px;"
                                   "}"); // depressed
        userCharacter = int(Character::Nought);
    }
}


void MainWindow::randomButton_clicked()
{
    if (gameMode == int(GameMode::CrossFirst))
    {
        randomButton->setStyleSheet(".QPushButton {"
                                        "background-color: rgb(20, 20, 20);"
                                        + checkURL +
                                        "}");
        crossFirstButton->setStyleSheet(".QPushButton {"
                                        "background-color: rgb(20, 20, 20);"
                                        + blockURL +
                                        "}");

        gameMode = int(GameMode::Random);
    }
}

void MainWindow::crossFirstButton_clicked()
{
    if (gameMode == int(GameMode::Random))
    {
        crossFirstButton->setStyleSheet(".QPushButton {"
                                        "background-color: rgb(20, 20, 20);"
                                        + checkURL +
                                        "}");
        randomButton->setStyleSheet(".QPushButton {"
                                        "background-color: rgb(20, 20, 20);"
                                        + blockURL +
                                        "}");
        gameMode = int(GameMode::CrossFirst);
    }
}

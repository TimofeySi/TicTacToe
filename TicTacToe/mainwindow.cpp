#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    constructorProperties();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete lineBetweenMoveAndScore;
    delete lineBetweenScoreAndButtons;
    delete nameLineEdit;
    delete saveRecordDialog;
    delete buttonBox;
    delete scoreLabel;
    delete moveLabel;
    delete yourLabel;
    delete computerLabel;
    delete yourMoveLabel;
    delete computerMoveLabel;
    delete yourScoreLabel;
    delete computerScoreLabel;
    delete crossFirstLabel;
    delete randomLabel;
    delete saveRecordLabel;
    delete crossButton;
    delete noughtButton;
    delete playButton;
    delete continueButton;
    delete againButton;
    delete finishButton;
    delete saveButton;
    delete crossFirstButton;
    delete randomButton;
    delete crossLamp;
    delete noughtLamp;
    delete layout;
    delete mainLayout;
    delete sideLayout;
    delete playGroupBoxLayout;
    delete characterChooseLayout;
    delete inGameLayout;
    delete scoreLayout;
    delete moveLayout;
    delete scoreIndicatorLayout;
    delete moveIndicatorLayout;
    delete yourScoreLayout;
    delete computerScoreLayout;
    delete moveYourIndicatorLayout;
    delete moveComputerIndicatorLayout;
    delete crossFirstLayout;
    delete randomLayout;
    delete saveRecordLayout;
    delete playGroupBox;
    delete inGameGroupBox;
    delete mainFont;
    delete screenSaver;
    delete leaderBoard;
    delete ticTacToe;
    delete centralWidget;
}


void MainWindow::saveRecord()
{
    std::string name = nameLineEdit->text().toStdString();
    if (name == "")
    {
        saveRecordLabel->setText("Поле не может быть пустым!\n"
                                 "Введите своё имя:");
        return;
    }
    for (auto &elem : name)
        if (elem < 32 || 127 < elem)
        {
            saveRecordLabel->setText("Вы использовали некорректные символы!\n"
                                     "Введите своё имя:");
            return;
        }

    for (auto &elem : leadersList)
        if (elem.getName() == name)
        {
            saveRecordLabel->setText("Такое имя уже присутствует!\n"
                                     "Введите своё имя:");
            return;
        }

    float comp_score = (computerScoreLabel->text() == "0") ? (0.7) : (computerScoreLabel->text().toInt());
    float coefficient = yourScoreLabel->text().toFloat() / comp_score;

    std::map<std::string, std::string> inner_map = {{"your score", yourScoreLabel->text().toStdString()},
                                                    {"computer score", computerScoreLabel->text().toStdString()},
                                                    {"name", name}
                                                   };

    while (leaderboardList.find(coefficient) != leaderboardList.end())
        coefficient -= 0.1;

    leaderboardList.insert(std::make_pair(coefficient, inner_map));

    leadersList.clear();
    for (auto it = leaderboardList.rbegin(); it != leaderboardList.rend(); ++it)
    {
        if (std::find(leadersList.begin(), leadersList.end(), Leader(it->second["name"], it->second["your score"], it->second["computer score"])) == leadersList.end())
            leadersList.push_back(Leader(it->second["name"], it->second["your score"], it->second["computer score"]));
        else
            continue;
    }

    while (leadersList.size() > 10)
        leadersList.erase(leadersList.begin() + 10);
    leaderBoard->setLeadersList(leadersList);
    serialization();


    ticTacToe->QWidget::setVisible(false);
    inGameGroupBox->QWidget::setVisible(false);

    mainLayout->removeWidget(ticTacToe);
    mainLayout->removeItem(sideLayout);
    mainLayout->addWidget(leaderBoard);
    mainLayout->addItem(sideLayout);
    sideLayout->removeWidget(inGameGroupBox);
    sideLayout->addItem(crossFirstLayout);
    sideLayout->addItem(randomLayout);
    sideLayout->addWidget(playGroupBox);

    leaderBoard->QWidget::setVisible(true);
    playGroupBox->QWidget::setVisible(true);
    randomLabel->QWidget::setVisible(true);
    randomButton->QWidget::setVisible(true);
    crossFirstButton->QWidget::setVisible(true);
    crossFirstLabel->QWidget::setVisible(true);

    this->resize(QSize(852, 418));
    this->move(QPoint((screenWidth - this->width()) / 2, (screenHeight- this->height()) / 2));

    crossButton->setStyleSheet(".QPushButton {"
                               + crossImageURL
                               + notPressedChooseButton +
                               "border-radius: 8px;"
                               "}");
    noughtButton->setStyleSheet(".QPushButton {"
                                + noughtImageURL
                                + notPressedChooseButton +
                                "border-radius: 8px;"
                                "}");
    randomButton->setStyleSheet(".QPushButton {"
                                    "background-color: rgb(20, 20, 20);"
                                    + blockURL +
                                    "}");
    crossFirstButton->setStyleSheet(".QPushButton {"
                                    "background-color: rgb(20, 20, 20);"
                                    + checkURL +
                                    "}");
    crossButton->setEnabled(true);
    noughtButton->setEnabled(true);

    ticTacToe->restartGameList();

    userCharacter = int(Character::None);
    gameMode = int(GameMode::CrossFirst);

//    delete saveRecordLayout;
    delete saveRecordDialog;
//    delete buttonBox;
//    delete saveButton;
//    delete nameLineEdit;

    leaderBoard->update();
    this->update();

}

void MainWindow::deserialization()
{
    std::ifstream file("leaderboard.json");
    if (file.is_open())
    {
        if (file.eof())
            return;

        json data;
        file >> data;
        leadersList.clear();
        for (auto elem : data) {
            std::string name = elem.at("Name").get<std::string>();
            std::string author = elem.at("User score").get<std::string>();
            std::string pages = elem.at("Computer score").get<std::string>();


            leadersList.push_back(Leader(name, author, pages));
        }
    }
    else
        leadersList.clear();
    file.close();
}

void MainWindow::serialization()
{
    json leadersList_serialize;
    for (auto &elem : leadersList) {
        json leader_serialize;
        to_json(leader_serialize, elem);
        leadersList_serialize.push_back(leader_serialize);
    }
    std::ofstream file("leaderboard.json");
    if (file.is_open())
    {
        file << leadersList_serialize << std::endl;
    }
    file.close();
}

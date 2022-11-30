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
}

int MainWindow::randomInt(int min, int max)
{
    return (std::rand() % (max - min) + min);
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

    float comp_score = (computerScoreLabel->text() == "0") ? (0.7) : (computerScoreLabel->text().toInt());
    int coefficient = yourScoreLabel->text().toFloat() / comp_score;

    std::map<std::string, std::string> inner_map = {{"your score", yourScoreLabel->text().toStdString()},
                                                    {"computer score", computerScoreLabel->text().toStdString()},
                                                    {"name", name}
                                                   };
    leaderboardList.insert(std::make_pair(coefficient, inner_map));

    for (auto it = leaderboardList.rbegin(); it != leaderboardList.rend(); ++it)
    {
        leadersList.push_back(Leader(it->second["name"], it->second["your score"], it->second["computer score"]));
    }

    if (leadersList.size() > 10)
        leadersList.erase(leadersList.begin() + 10, leadersList.end() - 1);
    leaderBoard->setLeadersList(leadersList);
    serialization();


    ticTacToe->QWidget::setVisible(false);
    inGameGroupBox->QWidget::setVisible(false);

    mainLayout->removeWidget(ticTacToe);
    mainLayout->removeItem(sideLayout);
    mainLayout->addWidget(screenSaver);
    mainLayout->addItem(sideLayout);
    sideLayout->removeWidget(inGameGroupBox);
    sideLayout->addWidget(leaderBoard);
    sideLayout->addWidget(playGroupBox);

    screenSaver->QWidget::setVisible(true);
    leaderBoard->QWidget::setVisible(true);
    playGroupBox->QWidget::setVisible(true);

    crossButton->setStyleSheet(".QPushButton {"
                               "image: url(resourse/cancel_80.png);"
                               + notPressedChooseButton +
                               "}");
    noughtButton->setStyleSheet(".QPushButton {"
                                "image: url(resourse/o_80.png);"
                                + notPressedChooseButton +
                                "}");
    crossButton->setEnabled(true);
    noughtButton->setEnabled(true);

    ticTacToe->restartGameList();

    userCharacter = int(Character::None);

//    delete saveRecordLayout;
    delete saveRecordDialog;
//    delete buttonBox;
//    delete saveButton;
//    delete nameLineEdit;

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

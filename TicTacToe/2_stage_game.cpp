#include "mainwindow.h"

void MainWindow::playButton_clicked()
{
    if (userCharacter == int(Character::None)) {
        QMessageBox::information(this, "Внимание!", "Вы не выбрали чем Вы будете ходить!");
        return;
    }
    computerCharacter = ((userCharacter == int(Character::Cross)) ? (int(Character::Nought)) : (int(Character::Cross)));



    leaderBoard->QWidget::setVisible(false);
    randomLabel->QWidget::setVisible(false);
    randomButton->QWidget::setVisible(false);
    crossFirstButton->QWidget::setVisible(false);
    crossFirstLabel->QWidget::setVisible(false);

//    screenSaver->QWidget::setVisible(false);
    playGroupBox->setVisible(false);
//    mainLayout->removeWidget(screenSaver);
    mainLayout->removeWidget(leaderBoard);
    mainLayout->removeItem(sideLayout);
//    sideLayout->removeWidget(leaderBoard);
    sideLayout->removeWidget(playGroupBox);
    sideLayout->removeItem(crossFirstLayout);
    sideLayout->removeItem(randomLayout);


    ticTacToe = new SFMLTicTacToe(this);
    unsigned screenSaver_height = 780;
    unsigned screenSaver_width = 780;
    ticTacToe->setMaximumSize(QSize(screenSaver_width, screenSaver_height));
    ticTacToe->setMinimumSize(QSize(screenSaver_width, screenSaver_height));
    ticTacToe->sizeHint().setHeight(screenSaver_height);
    ticTacToe->sizeHint().setWidth(screenSaver_width);
    ticTacToe->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
    connect(ticTacToe, SIGNAL(countdownOver(int)), this, SLOT(madeMove(int)));
    connect(ticTacToe, SIGNAL(victory(int)), this, SLOT(victory(int)));
    ticTacToe->setUserCharacter(userCharacter);
    ticTacToe->setComputerCharacter(computerCharacter);

    inGameGroupBox = new QGroupBox(this);
    inGameGroupBox->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);

    inGameLayout = new QVBoxLayout(this);

    scoreLayout = new QVBoxLayout(this);

    moveLayout = new QVBoxLayout(this);

    yourScoreLayout = new QVBoxLayout(this);

    computerScoreLayout = new QVBoxLayout(this);

    moveYourIndicatorLayout = new QVBoxLayout(this);

    moveComputerIndicatorLayout = new QVBoxLayout(this);

    scoreLabel = new QLabel(this);
    scoreLabel->setText("ТЕКУЩИЙ СЧЁТ");
    scoreLabel->setStyleSheet(".QLabel {"
                              "font: 28px;"
                              "color: white;"
                              "}");

    scoreLabel->setFont(*mainFont);
    scoreLabel->setAlignment(Qt::AlignCenter);

    moveLabel = new QLabel(this);
    moveLabel->setText("ХОД");
    moveLabel->setStyleSheet(".QLabel {"
                             "font: 28px;"
                             "color: white;"
                             "}");
    moveLabel->setFont(*mainFont);
    moveLabel->setAlignment(Qt::AlignCenter);

    yourLabel = new QLabel(this);
    yourLabel->setText("ВЫ");
    yourLabel->setStyleSheet(".QLabel {"
                             "font: 28px;"
                             "color: white;"
                             "}");
    yourLabel->setFont(*mainFont);
    yourLabel->setAlignment(Qt::AlignCenter);

    computerLabel = new QLabel(this);
    computerLabel->setText("КОМПЬЮТЕР");
    computerLabel->setStyleSheet(".QLabel {"
                                 "font: 28px;"
                                 "color: white;"
                                 "}");
    computerLabel->setFont(*mainFont);
    computerLabel->setAlignment(Qt::AlignCenter);

    scoreIndicatorLayout = new QHBoxLayout(this);
    scoreIndicatorLayout->addLayout(yourScoreLayout);
    scoreIndicatorLayout->addLayout(computerScoreLayout);

    moveIndicatorLayout = new QHBoxLayout(this);

    continueButton = new QPushButton("Продолжить");
    continueButton->setFont(*mainFont);
    continueButton->setMaximumHeight(90);
    continueButton->setStyleSheet(".QPushButton {"
                                  "font: 24px;"
                                  "background-color: rgb(238, 130, 238);"
                                  "border-radius: 10px;"
                                  "}");
    continueButton->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    continueButton->setCursor(Qt::PointingHandCursor);
    continueButton->setEnabled(false);
    connect(continueButton, SIGNAL(clicked()), this, SLOT(continueButton_clicked()));

    againButton = new QPushButton("Сбросить");
    againButton->setFont(*mainFont);
    againButton->setMaximumHeight(90);
    againButton->setStyleSheet(".QPushButton {"
                               "font: 24px;"
                               "background-color: rgb(255, 165, 0);"
                               "border-radius: 10px;"
                               "}");
    againButton->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    againButton->setCursor(Qt::PointingHandCursor);
    connect(againButton, SIGNAL(clicked()), this, SLOT(againButton_clicked()));

    finishButton = new QPushButton("Закончить");
    finishButton->setFont(*mainFont);
    finishButton->setMaximumHeight(90);
    finishButton->setStyleSheet(".QPushButton {"
                                "font: 24px;"
                                "background-color: rgb(255, 69, 0);"
                                "border-radius: 10px;"
                                "}");
    finishButton->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    finishButton->setCursor(Qt::PointingHandCursor);
    connect(finishButton, SIGNAL(clicked()), this, SLOT(finishButton_clicked()));

    crossLamp = new QPushButton("");
    crossLamp->setStyleSheet(".QPushButton {"
                             + crossImageURL +
                             "background-color: rgb(255, 255, 255);"
                             "border-radius: 8px;"
                             "}");
    crossLamp->setMinimumSize(QSize(150, 150));
    crossLamp->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    crossLamp->setFont(*mainFont);
    crossLamp->setEnabled(false);

    noughtLamp = new QPushButton("");
    noughtLamp->setStyleSheet(".QPushButton {"
                              + noughtImageURL +
                              "background-color: rgb(255, 255, 255);"
                              "border-radius: 8px;"
                              "}");
    noughtLamp->setMinimumSize(QSize(150, 150));
    noughtLamp->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    noughtLamp->setFont(*mainFont);
    noughtLamp->setEnabled(false);

    yourScoreLabel = new QLabel(this);
    yourScoreLabel->setText("0");
    yourScoreLabel->setStyleSheet(".QLabel {"
                                  "font: 24px;"
                                  "color: white;"
                                  "}");
    yourScoreLabel->setFont(*mainFont);
    yourScoreLabel->setAlignment(Qt::AlignCenter);

    yourMoveLabel = new QLabel(this);
    yourMoveLabel->setPixmap(QPixmap("resourse/user_80.png"));
    yourMoveLabel->setAlignment(Qt::AlignCenter);

    computerScoreLabel = new QLabel(this);
    computerScoreLabel->setText("0");
    computerScoreLabel->setStyleSheet(".QLabel {"
                                      "font: 24px;"
                                      "color: white;"
                                      "}");
    computerScoreLabel->setFont(*mainFont);
    computerScoreLabel->setAlignment(Qt::AlignCenter);

    computerMoveLabel = new QLabel(this);
    computerMoveLabel->setPixmap(QPixmap("resourse/computer_80.png"));
    computerMoveLabel->setAlignment(Qt::AlignCenter);

    lineBetweenMoveAndScore = new QFrame(this);
    lineBetweenMoveAndScore->setFrameShape(QFrame::HLine);
    lineBetweenMoveAndScore->setFrameShadow(QFrame::Sunken);
    lineBetweenMoveAndScore->setStyleSheet(QString("background-color: #c255c255c255;"));

    lineBetweenScoreAndButtons = new QFrame(this);
    lineBetweenScoreAndButtons->setFrameShape(QFrame::HLine);
    lineBetweenScoreAndButtons->setFrameShadow(QFrame::Sunken);
    lineBetweenScoreAndButtons->setStyleSheet(QString("background-color: #c255c255c255;"));

    ////////////////////////////////////////////////////////////////////////// add to layouts

    mainLayout->addWidget(ticTacToe);
    mainLayout->addLayout(sideLayout);

    sideLayout->addWidget(inGameGroupBox);

    inGameGroupBox->setLayout(inGameLayout);
    inGameLayout->addLayout(moveLayout);
    inGameLayout->addWidget(lineBetweenMoveAndScore);
    inGameLayout->addLayout(scoreLayout);
    inGameLayout->addWidget(lineBetweenScoreAndButtons);
    inGameLayout->addWidget(continueButton);
    inGameLayout->addWidget(againButton);
    inGameLayout->addWidget(finishButton);

    // add to move

    if (userCharacter == int(Character::Cross)) {
        moveYourIndicatorLayout->addWidget(yourMoveLabel);
        moveYourIndicatorLayout->addWidget(crossLamp);
        moveComputerIndicatorLayout->addWidget(computerMoveLabel);
        moveComputerIndicatorLayout->addWidget(noughtLamp);
    }
    else if (userCharacter == int(Character::Nought)) {
        moveYourIndicatorLayout->addWidget(yourMoveLabel);
        moveYourIndicatorLayout->addWidget(noughtLamp);
        moveComputerIndicatorLayout->addWidget(computerMoveLabel);
        moveComputerIndicatorLayout->addWidget(crossLamp);
    }

    moveIndicatorLayout->addItem(moveYourIndicatorLayout);
    moveIndicatorLayout->addItem(moveComputerIndicatorLayout);

    moveLayout->addWidget(moveLabel);
    moveLayout->addLayout(moveIndicatorLayout);

    // end of adding to move
    // add to score

    scoreLayout->addWidget(scoreLabel);
    scoreLayout->addLayout(scoreIndicatorLayout);

    yourScoreLayout->addWidget(yourLabel);
    yourScoreLayout->addWidget(yourScoreLabel);

    computerScoreLayout->addWidget(computerLabel);
    computerScoreLayout->addWidget(computerScoreLabel);

    // end of adding to score

    ////////////////////////////////////////////////////////////////////////// end of adding to layouts


    //    userCharacter = int(Character::None);

    ticTacToe->show();
    this->update();
    this->move(QPoint((screenWidth - this->width()) / 2, (screenHeight- this->height()) / 2));

    //    inGameGroupBox->setEnabled(false);
    ticTacToe->countdown(gameMode);
    //    inGameGroupBox->setEnabled(true);
}


void MainWindow::continueButton_clicked()
{
    ticTacToe->setEnabled(true);
    ticTacToe->restartGameList();

    crossLamp->setStyleSheet(".QPushButton {"
                             + crossImageURL +
                             "background-color: rgb(255, 255, 255);"
                             "border-radius: 8px;"
                             "}");

    noughtLamp->setStyleSheet(".QPushButton {"
                              + noughtImageURL +
                              "background-color: rgb(255, 255, 255);"
                              "border-radius: 8px;"
                              "}");
    continueButton->setStyleSheet(".QPushButton {"
                                  "font: 24px;"
                                  "background-color: rgb(238, 130, 238);"
                                  "border-radius: 10px;"
                                  "}");
    continueButton->setEnabled(false);

    ticTacToe->countdown(gameMode);
}

void MainWindow::againButton_clicked()
{
    QMessageBox msg_box;
    msg_box.setText("Вы уверены, что хотите сбросить текущий счёт и начать сначала?");
    QPushButton *finish_button = msg_box.addButton(tr("Да"), QMessageBox::YesRole);
    QPushButton *continue_button = msg_box.addButton(tr("Отмена"), QMessageBox::NoRole);

    msg_box.exec();
    if (msg_box.clickedButton() == finish_button)
    {
        yourScoreLabel->setText("0");
        computerScoreLabel->setText("0");

        continueButton->setEnabled(false);

        ticTacToe->restartGameList();

        crossLamp->setStyleSheet(".QPushButton {"
                                 + crossImageURL +
                                 "background-color: rgb(255, 255, 255);"
                                 "border-radius: 8px;"
                                 "}");

        noughtLamp->setStyleSheet(".QPushButton {"
                                  + noughtImageURL +
                                  "background-color: rgb(255, 255, 255);"
                                  "border-radius: 8px;"
                                  "}");

        ticTacToe->countdown(gameMode);
    }
}

void MainWindow::finishButton_clicked()
{
    QMessageBox msg_box;
    msg_box.setText("Вы уверены, что хотите завершить игру?");
    QPushButton *finish_button = msg_box.addButton(tr("Выйти без сохранения"), QMessageBox::YesRole);
    QPushButton *finish_with_save_button = msg_box.addButton(tr("Сохранить и выйти"), QMessageBox::AcceptRole);
    QPushButton *continue_button = msg_box.addButton(tr("Отмена"), QMessageBox::NoRole);


    msg_box.exec();
    if (msg_box.clickedButton() == finish_with_save_button)
    {
                if (yourScoreLabel->text() == "0")
                {
                    QMessageBox::warning(this, "Ошибка", "У Вас отсутсвуют очки! Невозможно сохранить результат!");
                    ticTacToe->QWidget::setVisible(false);
                    inGameGroupBox->QWidget::setVisible(false);

                    mainLayout->removeWidget(ticTacToe);
                    mainLayout->addWidget(leaderBoard);
                    mainLayout->removeItem(sideLayout);
            //                    mainLayout->addWidget(screenSaver);
                    mainLayout->addItem(sideLayout);
                    sideLayout->removeWidget(inGameGroupBox);
            //                    sideLayout->addWidget(leaderBoard);
                    sideLayout->addItem(crossFirstLayout);
                    sideLayout->addItem(randomLayout);
                    sideLayout->addWidget(playGroupBox);

//                    screenSaver->QWidget::setVisible(true);
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
                                               "border-radius: 20px;"
                                               "}");
                    noughtButton->setStyleSheet(".QPushButton {"
                                               + crossImageURL
                                                + notPressedChooseButton +
                                                "border-radius: 20px;"
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

                    this->update();
                }
                else
        {
            saveRecordDialog = new QDialog(this);

            nameLineEdit = new QLineEdit(saveRecordDialog);
            nameLineEdit->setMaxLength(10);

            saveRecordLabel = new QLabel(saveRecordDialog);
            saveRecordLabel->setText("Введите своё имя:");

            saveButton = new QPushButton(tr("Сохранить"));
            connect(saveButton, SIGNAL(clicked()), this, SLOT(saveRecord()));
            saveButton->setDefault(true);

            buttonBox = new QDialogButtonBox(Qt::Horizontal);
            buttonBox->addButton(saveButton, QDialogButtonBox::AcceptRole);

            saveRecordLayout = new QVBoxLayout;
            saveRecordLayout->addWidget(saveRecordLabel);
            saveRecordLayout->addWidget(nameLineEdit);
            saveRecordLayout->addWidget(buttonBox);

            saveRecordDialog->setLayout(saveRecordLayout);

            saveRecordDialog->show();

        }
    }
    else if (msg_box.clickedButton() == finish_button)
    {
        ticTacToe->QWidget::setVisible(false);
        inGameGroupBox->QWidget::setVisible(false);

        mainLayout->removeWidget(ticTacToe);
        mainLayout->addWidget(leaderBoard);
        mainLayout->removeItem(sideLayout);
//                    mainLayout->addWidget(screenSaver);
        mainLayout->addItem(sideLayout);
        sideLayout->removeWidget(inGameGroupBox);
//                    sideLayout->addWidget(leaderBoard);
        sideLayout->addItem(crossFirstLayout);
        sideLayout->addItem(randomLayout);
        sideLayout->addWidget(playGroupBox);

//                    screenSaver->QWidget::setVisible(true);
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
                                   "border-radius: 20px;"
                                   "}");
        noughtButton->setStyleSheet(".QPushButton {"
                                    + noughtImageURL
                                    + notPressedChooseButton +
                                    "border-radius: 20px;"
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

        this->update();
    }
}


void MainWindow::madeMove(int player)
{

    if (player == int(Player::User))
    {
        ticTacToe->setEnabled(true);
        if (userCharacter == int(Character::Cross))
        {
            crossLamp->setStyleSheet(".QPushButton {"
                                     "background-color: rgb(0, 255, 0);"
                                     + crossImageURL +
                                     "border-radius: 8px;"
                                     "}");
            noughtLamp->setStyleSheet(".QPushButton {"
                                      "background-color: rgb(178, 34, 34);"
                                      + noughtImageURL +
                                      "border-radius: 8px;"
                                      "}");
        }
        else if (userCharacter == int(Character::Nought))
        {
            crossLamp->setStyleSheet(".QPushButton {"
                                     "background-color: rgb(178, 34, 34);"
                                     + crossImageURL +
                                     "border-radius: 8px;"
                                     "}");
            noughtLamp->setStyleSheet(".QPushButton {"
                                      "background-color: rgb(0, 255, 0);"
                                      + noughtImageURL +
                                      "border-radius: 8px;"
                                      "}");
        }
    }
    else if (player == int(Player::Computer))
    {
        ticTacToe->setEnabled(false);
        if (computerCharacter == int(Character::Cross))
        {
            crossLamp->setStyleSheet(".QPushButton {"
                                     "background-color: rgb(0, 255, 0);"
                                     + crossImageURL +
                                     "border-radius: 8px;"
                                     "}");
            noughtLamp->setStyleSheet(".QPushButton {"
                                      "background-color: rgb(178, 34, 34);"
                                      + noughtImageURL +
                                      "border-radius: 8px;"
                                      "}");
        }
        else if (computerCharacter == int(Character::Nought))
        {
            crossLamp->setStyleSheet(".QPushButton {"
                                     "background-color: rgb(178, 34, 34);"
                                     + crossImageURL +
                                     "border-radius: 8px;"
                                     "}");
            noughtLamp->setStyleSheet(".QPushButton {"
                                      "background-color: rgb(0, 255, 0);"
                                      + noughtImageURL +
                                      "border-radius: 8px;"
                                      "}");
        }
        ticTacToe->computerQueue();
    }
    //    this->update();
}


void MainWindow::victory(int player)
{
    continueButton->setEnabled(true);
    continueButton->setStyleSheet(".QPushButton {"
                                  "font: 24px;"
                                  "background-color: rgb(255, 0, 255);"
                                  "border-radius: 10px;"
                                  "}");

    if (player == int(Player::Computer))
    {
        int score = computerScoreLabel->text().toInt();
        computerScoreLabel->setText(QString::fromStdString(std::to_string(score + 1)));
    }
    else if (player == int(Player::User))
    {
        int score = yourScoreLabel->text().toInt();
        yourScoreLabel->setText(QString::fromStdString(std::to_string(score + 1)));
    }
}

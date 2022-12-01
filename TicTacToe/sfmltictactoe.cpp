#include "sfmltictactoe.h"

SFMLTicTacToe::SFMLTicTacToe(QWidget *parent, const QPoint &position, const QSize &size)
    : SFMLWidget(parent, position, size) { }

void SFMLTicTacToe::setUserCharacter(int user_character) {
    userCharacter = user_character;
}

void SFMLTicTacToe::setComputerCharacter(int computer_character) {
    computerCharacter = computer_character;
}

void SFMLTicTacToe::updateFrame()
{
    if (paintMode == PaintMode::JustField)
    {
        fieldSprite.setTexture(fieldTexture);
        RenderWindow::draw(fieldSprite);

        for (auto &elem : crossesList)
            RenderWindow::draw(*elem);
        for (auto &elem : noughtList)
            RenderWindow::draw(*elem);

        if (Line != 0)
            RenderWindow::draw(*Line);
    }
    else if (paintMode == PaintMode::Countdown)
    {
        fieldSprite.setTexture(fieldTexture);
        RenderWindow::draw(fieldSprite);

        countdownNumber -= 1;

        if (2000 < countdownNumber && countdownNumber <= 3000)
        {
            threeSprite.setTexture(threeTexture);
            threeSprite.setPosition((780 - 400) / 2, (780 - 400) / 2);
            RenderWindow::draw(threeSprite);
        }
        else if (1000 < countdownNumber && countdownNumber <= 2000)
        {
            twoSprite.setTexture(twoTexture);
            twoSprite.setPosition((780 - 400) / 2, (780 - 400) / 2);
            RenderWindow::draw(twoSprite);
        }
        else if (0 < countdownNumber && countdownNumber <= 1000)
        {
            oneSprite.setTexture(oneTexture);
            oneSprite.setPosition((780 - 400) / 2, (780 - 400) / 2);
            RenderWindow::draw(oneSprite);
        }
        else if (-1000 < countdownNumber && countdownNumber <= 0)
        {
            goSprite.setTexture(goTexture);
            goSprite.setPosition((780 - 512) / 2, (780 - 512) / 2);
            RenderWindow::draw(goSprite);
        }
        else if (countdownNumber == -1000)
        {
            QWidget::setEnabled(true);
            paintMode = PaintMode::JustField;

            int first_move;
            if (gameMode == int(GameMode::Random))
                first_move = std::rand() % ((int(Player::Computer) + 1) - int(Player::User)) + int(Player::User);
            else
            {
                if (int(userCharacter) == int(Character::Cross))
                    first_move = int(Player::User);
                else
                    first_move = int(Player::Computer);
            }

            emit countdownOver(first_move);
        }
    }

}

void SFMLTicTacToe::initialize()
{
    if (!isInit) {
        drawTimer = new QTimer(this);

        computerMoveTimer = new QTimer(this);

        fieldTexture.loadFromFile("resourse/field.png");
        fieldTexture.loadFromFile("resourse/field.png");
        crossTexture.loadFromFile("resourse/cross_40.png");
        noughtTexture.loadFromFile("resourse/zero_40.png");

        oneTexture.loadFromFile("resourse/countdown_numbers/one_400.png");
        twoTexture.loadFromFile("resourse/countdown_numbers/two_400.png");
        threeTexture.loadFromFile("resourse/countdown_numbers/three_400.png");
        goTexture.loadFromFile("resourse/go.png");

        charactersMatrixPosition.assign(19, std::vector<int>(19));
        for (auto &row : charactersMatrixPosition)
            for (auto &elem : row)
                elem = -1;

        cellWeightMatrix.assign(19, std::vector<int>(19));
        for (auto &row : cellWeightMatrix)
            for (auto &elem : row)
                elem = 0;

        connect(drawTimer, SIGNAL(timeout()), this, SLOT(repaint()));
        connect(computerMoveTimer, SIGNAL(timeout()), this, SLOT(computerMove()));

        Line = 0;

        isInit = true;

        paintMode = PaintMode::JustField;
        drawTimer->start();
    }
}

void SFMLTicTacToe::mousePressEvent(QMouseEvent*)
{
    if (!Victory)
    {
        int border_thickness = 10;
        int plates_count = 19;
        int plate_size = 40;

        for (int i = 0; i != plates_count; ++i)
            for (int j = 0; j != plates_count; ++j) {

                int x = sf::Mouse::getPosition().x - RenderWindow::getPosition().x;
                int y = sf::Mouse::getPosition().y - RenderWindow::getPosition().y;

                if (((x >= (border_thickness + j * plate_size)) && (y >= (border_thickness + i * plate_size))) &&
                        ((x < (border_thickness + j * plate_size + plate_size)) && (y < (border_thickness + i * plate_size + plate_size))) &&
                        (charactersMatrixPosition[i][j] == -1))
                {
                    sf::Sprite *sprite = new sf::Sprite;
                    sprite->setPosition(sf::Vector2f(border_thickness + j * plate_size, border_thickness + i * plate_size));

                    if (userCharacter == int(Character::Cross))
                    {
                        sprite->setTexture(crossTexture);
                        crossesList.push_back(sprite);
                        charactersMatrixPosition[i][j] = 1;
                    }
                    else if (userCharacter == int(Character::Nought))
                    {
                        sprite->setTexture(noughtTexture);
                        noughtList.push_back(sprite);
                        charactersMatrixPosition[i][j] = 0;
                    }

                    if (turnPriorityList.find(&(cellWeightMatrix[i][j])) != turnPriorityList.end()) {
                        cellWeightMatrix[i][j] = -10000000;
                        turnPriorityList.erase(turnPriorityList.find(&(cellWeightMatrix[i][j])));
                    }
                    else
                        cellWeightMatrix[i][j] = -10000000;

                    victoryDefinition(i, j);

                    if (Victory)
                    {
                        emit victory(int(Player::User));
                    }


                    reviewAround(i, j);
                    QWidget::update();
                    emit countdownOver(int(Player::Computer));
                }
            }
    }
}

void SFMLTicTacToe::restartGameList()
{
    charactersMatrixPosition.assign(19, std::vector<int>(19));
    for (auto &row : charactersMatrixPosition)
        for (auto &elem : row)
            elem = -1;

    cellWeightMatrix.assign(19, std::vector<int>(19));
    for (auto &row : cellWeightMatrix)
        for (auto &elem : row)
            elem = 0;

    Victory = false;

    Line = 0;

    angle = 0;
    width = 0;
    length = 0;

    crossesList.clear();

    noughtList.clear();

    turnPriorityList.clear();


}


void SFMLTicTacToe::countdown(int game_mode)
{
    paintMode = PaintMode::Countdown;

    Victory = false;

    gameMode = game_mode;

    countdownNumber = 3500;

    QWidget::setEnabled(false);
}

void SFMLTicTacToe::computerQueue()
{
    computerMoveTimer->setInterval(std::rand() % (750 - 500) + 500);
    computerMoveTimer->start();
}


void SFMLTicTacToe::computerMove()
{
    computerMoveTimer->stop();

    int border_thickness = 10;
    int plate_size = 40;

    int row;
    int column;

    computerStrokeCalculation(row, column);

    sf::Sprite *sprite = new sf::Sprite;
    sprite->setPosition(sf::Vector2f(border_thickness + column * plate_size, border_thickness + row * plate_size));

    if (computerCharacter == int(Character::Cross))
    {
        sprite->setTexture(crossTexture);
        crossesList.push_back(sprite);
        charactersMatrixPosition[row][column] = 1;
    }
    else if (computerCharacter == int(Character::Nought))
    {
        sprite->setTexture(noughtTexture);
        noughtList.push_back(sprite);
        charactersMatrixPosition[row][column] = 0;
    }

    if (turnPriorityList.find(&(cellWeightMatrix[row][column])) != turnPriorityList.end()) {
        cellWeightMatrix[row][column] = -10000000;
        turnPriorityList.erase(turnPriorityList.find(&(cellWeightMatrix[row][column])));
    }
    else
        cellWeightMatrix[row][column] = -10000000;

    victoryDefinition(row, column);

    if (Victory)
    {
        emit victory(int(Player::Computer));
    }

    reviewAround(row, column);
    QWidget::update();
    emit countdownOver(int(Player::User));
}


void SFMLTicTacToe::computerStrokeCalculation(int &row, int &column)
{
    int plates_count = 19;

    bool is_empty = true;

    for (int i = 0; i != plates_count; ++i)
        for (int j = 0; j != plates_count; ++j)
        {
            if (charactersMatrixPosition[i][j] != -1)
                is_empty = false;

            if (cellWeightMatrix[i][j] > 0)
            {
                for (int direction = int(Direction::Horizontal); direction <= int(Direction::SecondaryDiagonal); ++direction)
                {
                    std::string self_pattern = "";

                    for (int k = -4; k <= 4; ++k)
                    {
                        if (direction == int(Direction::Horizontal))
                        {
                            if (j + k >= 0 && j + k <= 18)
                            {
                                if (k == 0)
                                    self_pattern += '3';

                                else if (charactersMatrixPosition[i][j + k] == computerCharacter)
                                    self_pattern += '2';

                                else if (charactersMatrixPosition[i][j + k] == userCharacter)
                                    self_pattern += '1';

                                else if (charactersMatrixPosition[i][j + k] == -1)
                                    self_pattern += '0';
                            }
                        }
                        else if (direction == int(Direction::Vectical))
                        {
                            if (i + k >= 0 && i + k <= 18)
                            {
                                if (k == 0)
                                    self_pattern += '3';

                                else if (charactersMatrixPosition[i + k][j] == computerCharacter)
                                    self_pattern += '2';

                                else if (charactersMatrixPosition[i + k][j] == userCharacter)
                                    self_pattern += '1';

                                else if (charactersMatrixPosition[i + k][j] == -1)
                                    self_pattern += '0';
                            }
                        }
                        else if (direction == int(Direction::MainDiagonal))
                        {
                            if (i + k >= 0 && i + k <= 18)
                                if (j + k >= 0 && j + k <= 18)
                                {
                                    if (k == 0)
                                        self_pattern += '3';

                                    else if (charactersMatrixPosition[i + k][j + k] == computerCharacter)
                                        self_pattern += '2';

                                    else if (charactersMatrixPosition[i + k][j + k] == userCharacter)
                                        self_pattern += '1';

                                    else if (charactersMatrixPosition[i + k][j + k] == -1)
                                        self_pattern += '0';
                                }
                        }
                        else if (direction == int(Direction::SecondaryDiagonal))
                        {
                            if (i - k >= 0 && i - k <= 18)
                                if (j + k >= 0 && j + k <= 18)
                                {
                                    if (k == 0)
                                        self_pattern += '3';

                                    else if (charactersMatrixPosition[i - k][j + k] == computerCharacter)
                                        self_pattern += '2';

                                    else if (charactersMatrixPosition[i - k][j + k] == userCharacter)
                                        self_pattern += '1';

                                    else if (charactersMatrixPosition[i - k][j + k] == -1)
                                        self_pattern += '0';
                                }
                        }
                    }
                    for (auto &pattern_class : attac_patterns)
                        for (auto &pattern : pattern_class.second)
                            if (self_pattern.find(pattern) != std::string::npos)
                                cellWeightMatrix[i][j] += ((pattern_class.first) * 1.1 + rand() % 20);

                    for (auto &pattern_class : defence_patterns)
                        for (auto &pattern : pattern_class.second)
                            if (self_pattern.find(pattern) != std::string::npos)
                                cellWeightMatrix[i][j] += (pattern_class.first + rand() % 20);
                }
            }
        }

    if (is_empty)
    {
        row = 9;
        column = 9;
    }
    else
    {
        determiningBestMove(row, column);
    }

}


void SFMLTicTacToe::reviewAround(int i, int j)
{
    for (int m = -2; m <= 2; ++m)
        for (int n = -2; n <= 2; ++n) {
            if (m == 0 && n == 0)
                continue;
            if (i + m < 0 || i + m > 18)
                continue;
            if (j + n < 0 || j + n > 18)
                continue;
            if (charactersMatrixPosition[i + m][j + n] != -1)
                continue;


            if (abs(m) == 1 && abs(n) == 1)
            {
                cellWeightMatrix[i + m][j + n] += 4 + (rand() % 2);
            }
            else if (abs(m) == abs(n) || m * n == 0)
            {
                cellWeightMatrix[i + m][j + n] += 3 + (rand() % 2);
            }
            else
            {
                cellWeightMatrix[i + m][j + n] += 1 + (rand() % 2);
            }

            turnPriorityList.insert(std::make_pair(&cellWeightMatrix[i + m][j + n], std::make_pair(i + m, j + n)));
        }
}


void SFMLTicTacToe::determiningBestMove(int &row, int &column)
{
    int max_score_value = *(turnPriorityList.begin()->first);
    int* max_score_address = turnPriorityList.begin()->first;

    for (auto &elem : turnPriorityList)
    {
        if (*(elem.first) > max_score_value)
        {
            max_score_value = *(elem.first);
            max_score_address = elem.first;
        }
    }

    int i = turnPriorityList.find(max_score_address)->second.first;
    int j = turnPriorityList.find(max_score_address)->second.second;

    if (computerCharacter == int(Character::Cross))
    {
        charactersMatrixPosition[i][j] = 1;
    }
    else if (computerCharacter == int(Character::Nought))
    {
        charactersMatrixPosition[i][j] = 0;
    }

    *(turnPriorityList.find(max_score_address)->first) = -10000000;
    turnPriorityList.erase(turnPriorityList.find(max_score_address));

    row = i;
    column = j;
}


void SFMLTicTacToe::victoryDefinition(int i, int j)
{
    int border_thickness = 10;
    int plate_size = 40;

    for (int direction = int(Direction::Horizontal); direction <= int(Direction::SecondaryDiagonal); ++direction)
    {
        std::string self_pattern = "";

        for (int k = -4; k <= 4; ++k)
        {
            if (direction == int(Direction::Horizontal))
            {
                if (j + k >= 0 && j + k <= 18)
                {
                    if (k == 0)
                        self_pattern += '3';

                    else if (charactersMatrixPosition[i][j + k] == charactersMatrixPosition[i][j])
                        self_pattern += '2';

                    else if (charactersMatrixPosition[i][j + k] == -1)
                        self_pattern += '0';

                    else if (charactersMatrixPosition[i][j + k] != charactersMatrixPosition[i][j])
                        self_pattern += '1';
                }
                else
                    break;
            }
            else if (direction == int(Direction::Vectical))
            {
                if (i + k >= 0 && i + k <= 18)
                {
                    if (k == 0)
                        self_pattern += '3';

                    else if (charactersMatrixPosition[i + k][j] == charactersMatrixPosition[i][j])
                        self_pattern += '2';

                    else if (charactersMatrixPosition[i + k][j] == -1)
                        self_pattern += '0';

                    else if (charactersMatrixPosition[i + k][j] != charactersMatrixPosition[i][j])
                        self_pattern += '1';
                }
                else
                    break;
            }
            else if (direction == int(Direction::MainDiagonal))
            {
                if (i + k >= 0 && i + k <= 18)
                    if (j + k >= 0 && j + k <= 18)
                    {
                        if (k == 0)
                            self_pattern += '3';

                        else if (charactersMatrixPosition[i + k][j + k] == charactersMatrixPosition[i][j])
                            self_pattern += '2';

                        else if (charactersMatrixPosition[i + k][j + k] == -1)
                            self_pattern += '0';

                        else if (charactersMatrixPosition[i + k][j + k] != charactersMatrixPosition[i][j])
                            self_pattern += '1';
                    }
                    else
                        break;
            }
            else if (direction == int(Direction::SecondaryDiagonal))
            {
                if (i - k >= 0 && i - k <= 18)
                    if (j + k >= 0 && j + k <= 18)
                    {
                        if (k == 0)
                            self_pattern += '3';

                        else if (charactersMatrixPosition[i - k][j + k] == charactersMatrixPosition[i][j])
                            self_pattern += '2';

                        else if (charactersMatrixPosition[i - k][j + k] == -1)
                            self_pattern += '0';

                        else if (charactersMatrixPosition[i - k][j + k] != charactersMatrixPosition[i][j])
                            self_pattern += '1';
                    }
                    else
                        break;
            }
        }

        for (auto &pattern : victory_patterns)
            if (self_pattern.find(pattern.first) != std::string::npos)
            {
                if (direction == int(Direction::Horizontal))
                {
                    firstVictoryCoords = std::make_pair(border_thickness + (j + pattern.second.first) * plate_size, border_thickness + i * plate_size + 19);
//                    secondVictoryCoords = std::make_pair(border_thickness + (j + pattern.second.second + 1) * plate_size, border_thickness + i * plate_size + 19);
                    angle = 0;
                    length = 200;
                }
                else if (direction == int(Direction::Vectical))
                {
                    firstVictoryCoords = std::make_pair(border_thickness + j * plate_size + 19, border_thickness + (i + pattern.second.first) * plate_size);
//                    secondVictoryCoords = std::make_pair(border_thickness + j  * plate_size + 19, border_thickness + (i - pattern.second.first) * plate_size);
                    angle = 90;
                    length = 200;
                }
                else if (direction == int(Direction::MainDiagonal))
                {
                    firstVictoryCoords = std::make_pair(border_thickness + (j + pattern.second.first) * plate_size, border_thickness + (i + pattern.second.first) * plate_size);
//                    secondVictoryCoords = std::make_pair(border_thickness + (j + pattern.second.second + 1) * plate_size, border_thickness + (i + pattern.second.second + 1) * plate_size);
                    angle = 45;
                    length = 280;
                }
                else if (direction == int(Direction::SecondaryDiagonal))
                {
                    firstVictoryCoords = std::make_pair(border_thickness + (j + pattern.second.first) * plate_size, border_thickness + (i - pattern.second.first + 1) * plate_size);
//                    secondVictoryCoords = std::make_pair(border_thickness + (j + pattern.second.second + 1) * plate_size, border_thickness + (i - pattern.second.second) * plate_size);
                    angle = 315;
                    length = 280;
                }

                Victory = true;

                width = 5;

                Line = new sf::RectangleShape();
                Line->setSize(sf::Vector2f(length, width));
                Line->setPosition(sf::Vector2f(firstVictoryCoords.first, firstVictoryCoords.second));
                Line->setFillColor(sf::Color::Blue);
                Line->rotate(angle);
            }

    }

}



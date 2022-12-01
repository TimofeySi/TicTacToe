#include "sfmlwidget.h"

SFMLWidget::SFMLWidget(QWidget *parent, const QPoint &position, const QSize &size)
    : QWidget(parent)
{
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
    setFocusPolicy(Qt::StrongFocus);
    move(position);
    resize(size);
    isInit = false;
}

void SFMLWidget::showEvent(QShowEvent*)
{
    sf::RenderWindow::create(reinterpret_cast<sf::WindowHandle>(winId()));
    initialize();
}

QPaintEngine* SFMLWidget::paintEngine() const {
    return 0;
}

void SFMLWidget::paintEvent(QPaintEvent*)
{
    sf::RenderWindow::clear();
    updateFrame();
    sf::RenderWindow::display();
}

void SFMLWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    sf::RenderWindow::setPosition(sf::Vector2i(QWidget::pos().x(), QWidget::pos().y()));
}


SFMLScreensaver::SFMLScreensaver(QWidget *parent, const QPoint &position, const QSize &size)
    : SFMLWidget(parent, position, size) { }

void SFMLScreensaver::updateFrame()
{
    screenSaverSprite.rotate(myClock.getElapsedTime().asSeconds() * 100.f);
    screenSaverSprite.setTexture(texture);
    screenSaverSprite.setOrigin((sf::Vector2f)texture.getSize() / 2.f);
    RenderWindow::draw(screenSaverSprite);
    myClock.restart();
}

void SFMLScreensaver::initialize()
{
    if (!isInit) {
        drawTimer = new QTimer(this);

        if (!texture.loadFromFile("resourse/three-in-a-row.png"))
            qDebug() << "field didnt load";

        screenSaverSprite.setTexture(texture);
        screenSaverSprite.setPosition(820 / 2, 820 / 2);
        connect(drawTimer, SIGNAL(timeout()), this, SLOT(repaint()));
        isInit = true;

        drawTimer->start();
    }

}

SFMLLeaderBoard::SFMLLeaderBoard(QWidget *parent, const QPoint &position, const QSize &size)
    : SFMLWidget(parent, position, size) { }

void SFMLLeaderBoard::updateFrame()
{

    backgroundFrameSprite[frameNumber].setTexture(backgroundFrameTexture[frameNumber]);
    RenderWindow::draw(backgroundFrameSprite[frameNumber]);
    if (frameNumber == backgroundFrameSprite.size() - 1)
        frameNumber = 0;
    else
        frameNumber += 1;

//    RenderWindow::draw(backgroundSprite);

    RenderWindow::draw(leaderboardsText);
    RenderWindow::draw(nameHeaderText);
    RenderWindow::draw(userScoreHeaderText);
    RenderWindow::draw(computerScoreHeaderText);

    for (auto it = leaderRows.rbegin(); it != leaderRows.rend(); ++it)
    {
        RenderWindow::draw(it->second["name"]);
        RenderWindow::draw(it->second["your score"]);
        RenderWindow::draw(it->second["computer score"]);
    }
}

void SFMLLeaderBoard::initialize()
{
    if (!isInit) {
        drawTimer = new QTimer(this);
        drawTimer->setInterval(45);

//        if (!texture.loadFromFile("resourse/0.gif"))
//            qDebug() << "field didnt load";

        backgroundSprite.setTexture(texture);
        connect(drawTimer, SIGNAL(timeout()), this, SLOT(repaint()));

        font.loadFromFile("resourse/sylfaen.ttf");

        frames_loading();

//        backgroundSprite.setTexture(texture);
//        backgroundSprite.setPosition(sf::Vector2f((QWidget::size().width() - 500) / 2, 0));

        leaderboardsText.setString("LEADERBOARDS");
        leaderboardsText.setFont(font);
        leaderboardsText.setCharacterSize(20);
        leaderboardsText.setFillColor(sf::Color::White);
        leaderboardsText.setPosition(180, 0);
        leaderboardsText.setStyle(sf::Text::Bold);
        leaderboardsText.setOutlineColor(sf::Color::Black);
        leaderboardsText.setOutlineThickness(5);

        nameHeaderText.setString("NAME");
        nameHeaderText.setFont(font);
        nameHeaderText.setCharacterSize(20);
        nameHeaderText.setFillColor(sf::Color::White);
        nameHeaderText.setPosition(10, 25);
        nameHeaderText.setStyle(sf::Text::Bold);
        nameHeaderText.setOutlineColor(sf::Color::Black);
        nameHeaderText.setOutlineThickness(5);

        userScoreHeaderText.setString("USER SCORE");
        userScoreHeaderText.setFont(font);
        userScoreHeaderText.setCharacterSize(20);
        userScoreHeaderText.setFillColor(sf::Color::White);
        userScoreHeaderText.setPosition(140, 25);
        userScoreHeaderText.setStyle(sf::Text::Bold);
        userScoreHeaderText.setOutlineColor(sf::Color::Black);
        userScoreHeaderText.setOutlineThickness(5);

        computerScoreHeaderText.setString("COMPUTER SCORE");
        computerScoreHeaderText.setFont(font);
        computerScoreHeaderText.setCharacterSize(20);
        computerScoreHeaderText.setFillColor(sf::Color::White);
        computerScoreHeaderText.setPosition(300, 25);
        computerScoreHeaderText.setStyle(sf::Text::Bold);
        computerScoreHeaderText.setOutlineColor(sf::Color::Black);
        computerScoreHeaderText.setOutlineThickness(5);

        frameNumber = 0;

        isInit = true;

        drawTimer->start();
    }
}


void SFMLLeaderBoard::setLeadersList(std::vector<Leader> leader_list)
{
    leadersList = leader_list;

    for (unsigned i = 0; i != leadersList.size(); ++i)
    {
        int coefficient = stof(leadersList[i].getUserScore()) / stoi(leadersList[i].getComputerScore());

        sf::Text name(leadersList[i].getName(), font, 20);
        name.setFillColor(sf::Color::White);
        name.setPosition(10, 50 + 30 * i);
        name.setStyle(sf::Text::Bold);
        name.setOutlineColor(sf::Color::Black);
        name.setOutlineThickness(5);

        sf::Text user_score(leadersList[i].getUserScore(), font, 20);
        user_score.setFillColor(sf::Color::White);
        user_score.setPosition(200, 50 + 30 * i);
        user_score.setStyle(sf::Text::Bold);
        user_score.setOutlineColor(sf::Color::Black);
        user_score.setOutlineThickness(5);

        sf::Text computer_score(leadersList[i].getComputerScore(), font, 20);
        computer_score.setFillColor(sf::Color::White);
        computer_score.setPosition(380, 50 + 30 * i);
        computer_score.setStyle(sf::Text::Bold);
        computer_score.setOutlineColor(sf::Color::Black);
        computer_score.setOutlineThickness(5);

        std::map<std::string, sf::Text> text_map = {
            {"your score", name},
            {"computer score", user_score},
            {"name", computer_score}
        };

        while (leaderRows.find(coefficient) != leaderRows.end())
            coefficient += 0.1;

        leaderRows.insert(std::make_pair(coefficient, text_map));
    }

}


void SFMLLeaderBoard::frames_loading()
{
    for (int i = 0; true; ++i)
    {
        std::ifstream file("resourse/leaderboard_background/" + std::to_string(i) + ".gif");

        if (file.is_open())
        {
            sf::Texture texture;
            if (!texture.loadFromFile("resourse/leaderboard_background/" + std::to_string(i) + ".gif"))
                qDebug() << "leaderboard_background didnt load";

            sf::Sprite frame;
            frame.setTexture(texture);
            frame.setPosition(sf::Vector2f((QWidget::size().width() - texture.getSize().x) / 2, 0));

            backgroundFrameTexture.push_back(texture);
            backgroundFrameSprite.push_back(frame);

            file.close();
        }
        else
            break;

    }
}

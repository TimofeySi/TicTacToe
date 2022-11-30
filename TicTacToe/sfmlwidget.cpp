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
    backgroundSprite.setTexture(texture);
    backgroundSprite.setPosition(sf::Vector2f((QWidget::size().width() - 500) / 2, 0));

    RenderWindow::draw(backgroundSprite);
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

        if (!texture.loadFromFile("resourse/0.gif"))
            qDebug() << "field didnt load";

        backgroundSprite.setTexture(texture);
        connect(drawTimer, SIGNAL(timeout()), this, SLOT(repaint()));

        font.loadFromFile("resourse/sylfaen.ttf");

        nameHeaderText.setString("NAME");
        nameHeaderText.setFont(font);
        nameHeaderText.setCharacterSize(20);
        nameHeaderText.setFillColor(sf::Color::White);
        nameHeaderText.setPosition(10, 10);

        userScoreHeaderText.setString("USER SCORE");
        userScoreHeaderText.setFont(font);
        userScoreHeaderText.setCharacterSize(20);
        userScoreHeaderText.setFillColor(sf::Color::White);
        userScoreHeaderText.setPosition(100, 10);

        computerScoreHeaderText.setString("COMPUTER SCORE");
        computerScoreHeaderText.setFont(font);
        computerScoreHeaderText.setCharacterSize(20);
        computerScoreHeaderText.setFillColor(sf::Color::White);
        computerScoreHeaderText.setPosition(150, 10);

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
        name.setPosition(10, 30 + 30 * i);

        sf::Text user_score(leadersList[i].getUserScore(), font, 20);
        user_score.setFillColor(sf::Color::White);
        user_score.setPosition(100, 30 + 30 * i);

        sf::Text computer_score(leadersList[i].getComputerScore(), font, 20);
        computer_score.setFillColor(sf::Color::White);
        computer_score.setPosition(150, 30 + 30 * i);

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
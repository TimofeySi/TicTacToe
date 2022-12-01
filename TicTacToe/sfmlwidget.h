#pragma once

#include "SFML/Graphics.hpp"
#include <QWidget>
#include <QEvent>
#include <QTimer>
#include <map>
#include <algorithm>
#include <fstream>

#include "leader.h"

enum class Character {
    None = -1,
    Nought = 0,
    Cross = 1

};

enum class Player {
    User,
    Computer
};

class SFMLWidget : public QWidget, public sf::RenderWindow
{
    Q_OBJECT

public:
    SFMLWidget(QWidget *parent, const QPoint &position, const QSize &size);

public:
    void showEvent(QShowEvent*) override;
    QPaintEngine* paintEngine() const override;
    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent*) override;

protected:
    bool isInit;
    QTimer *drawTimer;
    virtual void updateFrame() = 0;
    virtual void initialize() = 0;

};



class SFMLScreensaver : public SFMLWidget
{
public:
    SFMLScreensaver(QWidget *parent, const QPoint &position = QPoint(0,0), const QSize &size = QSize(0,0));

private:
    void updateFrame() override;
    void initialize() override;

private:
    sf::Sprite screenSaverSprite;
    sf::Texture texture;
    sf::Clock myClock;
};



class SFMLLeaderBoard : public SFMLWidget
{
public:
    SFMLLeaderBoard(QWidget *parent, const QPoint &position = QPoint(0,0), const QSize &size = QSize(0,0));

private:
    unsigned frameNumber;

private:
    void updateFrame() override;
    void initialize() override;

    void frames_loading();

public:
    void setLeadersList(std::vector<Leader> leader_list);

private:
    sf::Sprite backgroundSprite;
    sf::Sprite tableHeaderSprite;

    sf::Texture texture;

    sf::Text leaderboardsText;
    sf::Text nameHeaderText;
    sf::Text userScoreHeaderText;
    sf::Text computerScoreHeaderText;

    sf::Font font;

    std::vector<Leader> leadersList;
    std::map<float, std::map<std::string, sf::Text>> leaderRows;

    std::vector<sf::Texture>backgroundFrameTexture;
    std::vector<sf::Sprite> backgroundFrameSprite;
};

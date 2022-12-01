#pragma once

#include "sfmlwidget.h"
#include "patterns.h"

enum class Direction {
    Horizontal,
    Vectical,
    MainDiagonal,
    SecondaryDiagonal
};

enum class GameMode {
    CrossFirst,
    Random
};

class SFMLTicTacToe : public SFMLWidget
{
    Q_OBJECT

public:
    SFMLTicTacToe(QWidget *parent, const QPoint &position = QPoint(0,0), const QSize &size = QSize(0,0));

public:
    void mousePressEvent(QMouseEvent*) override;

    void countdown(int game_mode);

    void setUserCharacter(int);
    void setComputerCharacter(int);

    void computerQueue();

    void restartGameList();

private:
    void updateFrame() override;
    void initialize() override;

    void computerStrokeCalculation(int &row, int &column);

    void reviewAround(int i, int j);

    void determiningBestMove(int &row, int &column);

    void victoryDefinition(int i, int j);

private slots:
    void computerMove();

signals:
    void countdownOver(int player);

    void victory(int player);

private:
    std::vector<std::vector<int>> charactersMatrixPosition;
    std::vector<std::vector<int>> cellWeightMatrix;

    int gameMode;

    sf::Sprite fieldSprite;
    sf::Sprite crossSprite;
    sf::Sprite noughtSprite;
    sf::Sprite oneSprite;
    sf::Sprite twoSprite;
    sf::Sprite threeSprite;
    sf::Sprite goSprite;

    sf::Texture fieldTexture;
    sf::Texture crossTexture;
    sf::Texture noughtTexture;
    sf::Texture oneTexture;
    sf::Texture twoTexture;
    sf::Texture threeTexture;
    sf::Texture goTexture;

    sf::RectangleShape *Line;

    QTimer *computerMoveTimer;

    std::vector<sf::Sprite*> crossesList;
    std::vector<sf::Sprite*> noughtList;

    std::map<int*, std::pair<int, int>> turnPriorityList;

    short countdownNumber;

    enum class PaintMode {
        JustField,
        Countdown,
    };

    PaintMode paintMode;

    int userCharacter;
    int computerCharacter;

    bool Victory;
    bool Working;

    std::pair<int, int> firstVictoryCoords;
    std::pair<int, int> secondVictoryCoords;
    int angle;
    int length;
    int width;
};

#pragma once
#include "textureManager.h"
#include "GeneralUtilities.hpp"

class Scene
{
private:

    TextureManager txtManager;
    
    sf::Sprite background;
    sf::Sprite tiles;
    sf::Sprite tiles2;
    int tileWidth;
    int max_score = 0;

    std::vector<sf::Vector2f> tilePositions;
    std::vector<sf::Vector2f> tilePositions2;

public:
    void generate_scene();
    void draw_scene(sf::RenderWindow &window);
    void draw_tiles(sf::RenderWindow &window, const std::vector<sf::Vector2f> &positions, sf::Sprite &tileSprite);
    void draw_score(int score, sf::RenderWindow &window);
};
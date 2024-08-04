#include "Headers/Scene.h"

void Scene::generate_scene()
{
    // Background
    background.setTexture(txtManager.background_texture);
    background.setScale(3.f, 3.f);

    // Ground tiles type 1
    tiles.setTexture(txtManager.pipes_tiles_texture);
    tiles.setTextureRect(sf::IntRect(0, 80, 32, 32));
    tiles.setScale(2.f, 2.f);
    tiles.setPosition(0, GROUND_Y);

    tileWidth = tiles.getTextureRect().width * tiles.getScale().x;

    // Ground tiles type 2
    tiles2.setTexture(txtManager.pipes_tiles_texture);
    tiles2.setTextureRect(sf::IntRect(32, 80, 32, 32));
    tiles2.setScale(2.f, 2.f);
    tiles2.setPosition(tileWidth, GROUND_Y);

    // Generate the tiles positions
    for (int x = 0; x < SCREEN_WIDTH; x += tileWidth)
    {
        (rand() % 2 == 0 ? tilePositions : tilePositions2).emplace_back(sf::Vector2f(x, GROUND_Y));
    }
}

void Scene::draw_scene(sf::RenderWindow &window)
{
    window.draw(background);

    draw_tiles(window, tilePositions, tiles);
    draw_tiles(window, tilePositions2, tiles2);
}

void Scene::draw_tiles(sf::RenderWindow &window, const std::vector<sf::Vector2f> &positions, sf::Sprite &tileSprite)
{
    for (const auto &position : positions)
    {
        tileSprite.setPosition(position);
        window.draw(tileSprite);
    }
}

void Scene::draw_score(int score, sf::RenderWindow &window)
{
    max_score = max_score < score ? score : max_score;
    sf::Font font;
    font.loadFromFile("Assets/Karma_Suture.otf");
    sf::Text maxScoreText("High score " + std::to_string(max_score), font, 35);
    maxScoreText.setFillColor(sf::Color::Black);
    maxScoreText.setPosition((SCREEN_WIDTH - maxScoreText.getLocalBounds().width) / 2, 20);

    sf::Text scoreText(std::to_string(score), font, 45);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition((SCREEN_WIDTH - scoreText.getLocalBounds().width) / 2, 65);

    window.draw(maxScoreText);
    window.draw(scoreText);
}
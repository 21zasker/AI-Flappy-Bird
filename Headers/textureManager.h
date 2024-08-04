#pragma once
#include <SFML/Graphics.hpp>

class TextureManager
{
public:
    sf::Texture background_texture;
    sf::Texture bird_texture;
    sf::Texture pipes_tiles_texture;

    TextureManager()
    {
        background_texture.loadFromFile("Assets/background.png");
        bird_texture.loadFromFile("Assets/bird_sprites_14x12.png");
        pipes_tiles_texture.loadFromFile("Assets/pipes_tiles_32x32.png");
    }
};
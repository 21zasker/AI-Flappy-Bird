#include "Headers/Pipes.h"
#include "Headers/GeneralUtilities.hpp"

void Pipes::draw(sf::RenderWindow &window)
{
    pipe_sprite.setTexture(txtManager.pipes_tiles_texture);
    pipe_sprite.setScale(2.f, 2.f);

    float gap = (GAP_SIZE < 122 || GAP_SIZE > 122) ? GAP_SIZE + (122 - GAP_SIZE) : GAP_SIZE;

    // Top Pipe
    pipe_sprite.setPosition(x, static_cast<float>(y - gap));
    pipe_sprite.setTextureRect(greenColor ? sf::IntRect(0, 19, 32, 61) : sf::IntRect(32, 19, 32, 61));

    window.draw(pipe_sprite);

    for (int i = y - 122; i >= -PIPE_HEIGHT; i -= PIPE_HEIGHT)
    {
        pipe_sprite.setTextureRect(greenColor ? sf::IntRect(0, 19, 32, 32) : sf::IntRect(32, 19, 32, 32));
        pipe_sprite.setPosition(x, i);
        window.draw(pipe_sprite);
    }

    // Bottom Pipe
    pipe_sprite.setPosition(x, static_cast<float>(GAP_SIZE + y));
    pipe_sprite.setTextureRect(greenColor ? sf::IntRect(0, 0, 32, 61) : sf::IntRect(32, 0, 32, 61));

    window.draw(pipe_sprite);

    for (int i = y + GAP_SIZE + 122; i < SCREEN_HEIGHT; i += PIPE_HEIGHT)
    {
        pipe_sprite.setTextureRect(greenColor ? sf::IntRect(0, 19, 32, 32) : sf::IntRect(32, 19, 32, 32));
        pipe_sprite.setPosition(x, i);
        window.draw(pipe_sprite);
    }
}

// Moves the pipes up or down until they reach a limit and change direction
void Pipes::update()
{
    x--;
    move_direction = (y >= GROUND_Y - GAP_SIZE - PIPE_LIMIT) ? Up : (y <= PIPE_LIMIT) ? Down
                                                                                      : move_direction;

    y += (move_direction == MoveDirection::Up) ? -1 : 1;
}
#include "Headers/PipesManager.h"

// Generate pipes with random y-coordinate
void PipesManager::generate_pipes(std::mt19937_64 &i_random_engine)
{
    if (++frameCounter >= maxFrames)
    {
        greenColor = !greenColor;
        pipes.emplace_back(SCREEN_WIDTH, y_distribution(i_random_engine), greenColor);
        frameCounter = 0;
    }
}

void PipesManager::update_pipes()
{
    for (Pipes &pipe : pipes)
    {
        pipe.update();
    }

    auto it = std::remove_if(pipes.begin(), pipes.end(), [](Pipes &pipe)
                             { return pipe.get_x() <= -PIPE_WIDTH; });
    pipes.erase(it, pipes.end());
}

void PipesManager::draw_pipes(sf::RenderWindow &window)
{
    for (auto &pipe : pipes)
    {
        pipe.draw(window);
    }
}

void PipesManager::reset_pipes()
{
    pipes.clear();
    frameCounter = 310;
    greenColor = false;
}
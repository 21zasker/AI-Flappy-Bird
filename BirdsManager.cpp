#include "Headers/BirdsManager.h"

bool BirdsManager::all_dead_birds()
{
    for (auto &bird : birds)
    {
        if (bird.get_alive())
        {
            return false;
        }
    }
    return true;
}

void BirdsManager::update_birds(std::vector<Pipes> pipes)
{
    for (auto &bird : birds)
    {
        bird.updateBird(pipes);
    }
}

void BirdsManager::sort_birds()
{
    for (size_t i = 0; i < birds.size() - 1; ++i)
    {
        for (size_t j = 0; j < birds.size() - i - 1; ++j)
        {
            if (birds[j].get_performance_score() < birds[j + 1].get_performance_score())
            {
                std::swap(birds[j], birds[j + 1]);
            }
        }
    }
}

void BirdsManager::evolve_birds(std::mt19937_64 &random_engine)
{
    for (size_t i = 2; i < birds.size(); ++i)
    {
        birds[i].evolve(random_engine, birds[0].get_weights(), birds[1].get_weights());
    }

    for (auto &bird : birds)
    {
        bird.initBird();
    }
}

void BirdsManager::draw_birds(sf::RenderWindow &window)
{
    for (auto &bird : birds)
    {
        bird.drawBird(window);
    }
}

void BirdsManager::next_generation()
{
    current_generation++;
    std::cout << "Generation: " << current_generation << std::endl;
}

int BirdsManager::get_max_score()
{
    int maxScore = birds[0].get_score();

    for (auto &bird : birds)
    {
        int currentScore = bird.get_score();
        if (currentScore > maxScore)
        {
            maxScore = currentScore;
        }
    }

    return maxScore;
}
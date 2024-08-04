#pragma once
#include "textureManager.h"
#include "GeneralUtilities.hpp"
#include "Pipes.h"
#include <vector>
#include <cmath>
#include <random>
#include <SFML/Graphics.hpp>

class FlapBot
{
public:
    FlapBot() : value_distribution(-1, std::nextafter(1, 2)), mutation_distribution(0, 63)
    {
        init_neural_network();
        initBird();
    }

    // Functions
    void initBird();
    void drawBird(sf::RenderWindow &window);
    void updateBird(std::vector<Pipes> pipes);
    void random_weights(std::mt19937_64 &random_engine);
    void evolve(std::mt19937_64 &random_engine, const std::vector<std::vector<std::vector<float>>> &bird1, const std::vector<std::vector<std::vector<float>>> &bird2);

    bool get_alive()
    {
        return alive;
    }

    int get_performance_score()
    {
        return performanceScore;
    }

    int get_score()
    {
        return score;
    }

    std::vector<std::vector<std::vector<float>>> get_weights()
    {
        return weights;
    }

private:
    // Bird parameters
    TextureManager txtManager;
    sf::Sprite bird_sprite;
    bool alive;
    bool flapping;
    float y, x;
    float vertical_speed;
    int score;
    int performanceScore; // How well the bot performed with its weights

    // AI parameters and functions
    std::vector<std::vector<float>> neural_network;
    std::vector<std::vector<std::vector<float>>> weights;

    std::uniform_real_distribution<float> value_distribution;
    std::uniform_int_distribution<int> mutation_distribution;

    void init_neural_network();
    float get_gap(std::vector<Pipes> pipes);
    bool flap_AI(std::vector<Pipes> pipes);

    int flapCounter;
};
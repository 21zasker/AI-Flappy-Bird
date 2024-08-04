#include "Headers/FlapBot.h"
#include "Headers/GeneralUtilities.hpp"
#include <iostream>
#include <algorithm>

void FlapBot::initBird()
{
    alive = true;
    y = 0.5f * (GROUND_Y - BIRD_HEIGHT);
    x = 57;

    score = 0;
    performanceScore = 0;
    vertical_speed = 0;
}

void FlapBot::updateBird(std::vector<Pipes> pipes)
{
    vertical_speed += GRAVITY;
    y += vertical_speed;

    if (alive)
    {
        // AI decides if bird should flap or not
        if (vertical_speed >= 0 && y >= 0 && flap_AI(pipes))
        {
            vertical_speed = FLAP_SPEED;
            flapping = true;
            flapCounter = 0;
        }

        if (flapping)
        {
            flapCounter++;
            flapping = flapCounter >= 10 ? false : true;
        }

        for (auto &pipe : pipes)
        {
            if (x < pipe.get_x() + PIPE_WIDTH && x > pipe.get_x() - BIRD_WIDTH)
            {
                // Detects collision with pipes
                if (y <= pipe.get_y() || y >= (pipe.get_y() + GAP_SIZE) - BIRD_HEIGHT)
                {
                    alive = false;
                    vertical_speed = 0;
                }
            }
            else if (x == pipe.get_x() + PIPE_WIDTH)
            {
                score++;
            }
        }
    }

    // Detects collision with ground
    if (y >= GROUND_Y - BIRD_HEIGHT)
    {
        alive = false;
        vertical_speed = 0;
        y = GROUND_Y - BIRD_HEIGHT;
    }

    // Bird increases its performance if it's still alive
    performanceScore += alive ? 1 : 0;
    // Otherwise it gets dead and left behind
    x = alive ? x : std::max(-BIRD_WIDTH, x - 1);
}

void FlapBot::init_neural_network()
{
    neural_network.resize(3); // 3 layers

    // Input layer
    neural_network[0].resize(INPUT_NEURONS);
    // Hidden layer
    neural_network[1].resize(HIDDEN_NEURONS, 0);
    // Output layer
    neural_network[2].resize(OUTPUT_NEURONS, 0);
}

void FlapBot::random_weights(std::mt19937_64 &random_engine)
{
    // Resize the weights vector to hold the weight matrices between layers
    weights.resize(neural_network.size() - 1);

    for (std::size_t i = 0; i < weights.size(); ++i)
    {
        const std::size_t size = neural_network[i + 1].size();
        weights[i].resize(size);

        for (auto &neuron_weights : weights[i])
        {
            neuron_weights.resize(neural_network[i].size());

            for (auto &weight : neuron_weights)
            {
                weight = value_distribution(random_engine);
            }
        }
    }
}

// Distance between the gap and the bird's height
float FlapBot::get_gap(std::vector<Pipes> pipes)
{
    for (auto &pipe : pipes)
    {
        if (x < pipe.get_x() + PIPE_WIDTH)
            return GAP_SIZE + pipe.get_y() - BIRD_HEIGHT - y;
    }

    return 0;
}

// AI neural network determines if it should flap or not
bool FlapBot::flap_AI(std::vector<Pipes> pipes)
{
    // 3 Inputs
    neural_network[0][0] = vertical_speed;
    neural_network[0][1] = get_gap(pipes);

    for (auto &pipe : pipes)
    {
        if (x < pipe.get_x() + PIPE_WIDTH)
        {
            neural_network[0][2] = (pipe.move_direction == Pipes::MoveDirection::Up) ? -1 : 1;
            break;
        }
    }

    // Neural Network
    for (int i = 0; i < weights.size(); i++)
    {
        for (int j = 0; j < weights[i].size(); j++)
        {
            neural_network[i + 1][j] = 0;

            // Weighted sum calculation
            for (int k = 0; k < weights[i][j].size(); k++)
            {
                // Multiply the inputs by the corresponding weights
                neural_network[i + 1][j] += neural_network[i][k] * weights[i][j][k];
            }

            // Apply the activation function
            neural_network[i + 1][j] = tanh(neural_network[i + 1][j]);
        }
    }
    return neural_network[2][0] >= 0;
}

// Evolves the weights using the ones of the 2 best performers
void FlapBot::evolve(std::mt19937_64 &random_engine, const std::vector<std::vector<std::vector<float>>> &bird1, const std::vector<std::vector<std::vector<float>>> &bird2)
{
    for (size_t i = 0; i < weights.size(); ++i)
    {
        for (size_t j = 0; j < weights[i].size(); ++j)
        {
            for (size_t k = 0; k < weights[i][j].size(); ++k)
            {
                // Randomly reassigns the weights of either the bird1 or bird2
                weights[i][j][k] = (rand() % 2 == 0) ? bird1[i][j][k] : bird2[i][j][k];

                // Randomly mutates the weights
                if (mutation_distribution(random_engine) == 0)
                {
                    weights[i][j][k] = value_distribution(random_engine);
                }
            }
        }
    }
}

void FlapBot::drawBird(sf::RenderWindow &window)
{
    bird_sprite.setPosition(x, round(y));

    bird_sprite.setTexture(txtManager.bird_texture);
    bird_sprite.setTextureRect(!flapping ? sf::IntRect(2, 3, 14, 12) : sf::IntRect(18, 3, 14, 12));
    bird_sprite.setScale(4.f, 4.f);

    window.draw(bird_sprite);
}
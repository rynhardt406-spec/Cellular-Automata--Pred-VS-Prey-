#ifndef PREY_H
#define PREY_H
#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

    class Prey{
        public:
            std::string Name;
            sf::Sprite sprite;
            sf::Vector2f direction;
            float speed;
            
        Prey(std::string name, sf::Texture& texture);
        void setRandomDirection();
        void update();
    };

#endif
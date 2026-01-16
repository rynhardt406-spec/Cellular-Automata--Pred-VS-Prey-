#ifndef PRED_H
#define PRED_H
#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

    class Pred{
        public:
            std::string Name;
            sf::Sprite sprite;
            sf::Vector2f direction;
            float speed;
            
        Pred(std::string name, sf::Texture& texture);
        void setRandomDirection();
        void update();
    };

#endif
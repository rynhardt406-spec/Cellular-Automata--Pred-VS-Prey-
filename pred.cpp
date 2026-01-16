#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "pred.h"

Pred::Pred(std::string name, sf::Texture& texture){
    this->Name = name;
    this->sprite.setTexture(texture);
    this->sprite.setPosition(0.f, 0.f);
    speed = 0.1f;
    setRandomDirection();
}
void Pred::setRandomDirection(){
    int dir = rand() % 4; //getting random direction
    switch(dir){
        case 0: direction = sf::Vector2f(1.f, 0.f); break;   // right
        case 1: direction = sf::Vector2f(-1.f, 0.f); break;  // left
        case 2: direction = sf::Vector2f(0.f, 1.f); break;   // down
        case 3: direction = sf::Vector2f(0.f, -1.f); break;  // up
    }
}
void Pred::update(){
    sprite.move(direction * speed);
    sf::Vector2f pos = sprite.getPosition();
    sf::FloatRect bounds = sprite.getGlobalBounds(); //wall positions

    // Bounce off the edges (flip direction if hitting a wall)
    if (pos.x < 0 && direction.x < 0){direction.x = -direction.x;}           // hit left
    if (pos.x + bounds.width > 800 && direction.x > 0) {direction.x = -direction.x;} // hit right
    if (pos.y < 0 && direction.y < 0){ direction.y = -direction.y;}           // hit top
    if (pos.y + bounds.height > 600 && direction.y > 0) {direction.y = -direction.y;} // hit bottom
    //picks new direction
    if (rand() % 100 < 2){
        setRandomDirection();
    }
}
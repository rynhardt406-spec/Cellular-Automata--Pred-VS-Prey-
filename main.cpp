#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <deque>
#include "prey.h"
#include "pred.h"
using namespace std;

int main(){
//Doing user input
    int presetChoice;
    cout << "Choose simulation preset:\n";
    cout << "1 Covid-19 \n";
    cout << "2 Pred VS Prey\n";
    cout << "3 Fun\n";
    cout << "Enter choice: ";
    cin >> presetChoice;
//Initial values

    int PreyAmount = 100;
    float PreySpawnRate = 1.0f;
    float SpawnTRimer = 1.0f;
    std::string onScreanText = "Default";

    switch(presetChoice){
        case 1:
            PreyAmount = 100;
            PreySpawnRate = 1.0f;
            SpawnTRimer = 1.0f;
            onScreanText = "Covid-19";
            break;
        case 2:
            PreyAmount = 50;
            PreySpawnRate = 2.0f;
            SpawnTRimer = 0.01f;
            onScreanText = "Pred VS Prey";
            break;
        case 3:
            PreyAmount = 1;         
            PreySpawnRate = 0.3f;  
            SpawnTRimer = 0.1f;  
            onScreanText = "Fun";     
            break;
        default:break;
    }

//Getting a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    sf::Clock clock;           //to track elapsed time
//Spawning
    float spawnTimer = SpawnTRimer;    
    float spawnInterval = PreySpawnRate; //i know this makes an extra var but it makes it easy to read
//Loading prey texture
    sf::Texture preyTexture;
    if (!preyTexture.loadFromFile("redcube.png")) {return 1;}
//Loading pred texture
    sf::Texture predTexture;
    if (!predTexture.loadFromFile("bluecube.png")) { return 1; }

//Loading the prey vector
    srand(static_cast<unsigned int>(time(0))); // random seed
    const int PreyNum = PreyAmount;   //amount of prey       
    //std::vector<Prey> allPrey;  
    std::deque<Prey> allPrey;
    
// Spawn prey at random positions
    for (int i = 0; i < PreyNum; i++) {
        float x = 1.f + static_cast<float>(rand()) / RAND_MAX * 799.f; // random x
        float y = 1.f + static_cast<float>(rand()) / RAND_MAX * 599.f; // random y
        Prey p("Prey", preyTexture);
        p.sprite.setPosition(x, y);
        allPrey.push_back(p);
    }
//Loading the pred vector
    std::vector<Pred> predators;
    Pred p("Predator", predTexture);
    p.sprite.setPosition(400.f, 300.f);
    predators.push_back(p);
//Adding text to the screan
    sf::Font font;
    if (!font.loadFromFile("minecraft.ttf")){return 1;}
    sf::Text text;
    text.setFont(font);
    text.setString(onScreanText);
    text.setCharacterSize(25);

//Gameloop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){window.close();}
        }
        float deltaTime = clock.restart().asSeconds();
        spawnTimer += deltaTime;
        if (spawnTimer >= spawnInterval) {
            float x = 1.f + static_cast<float>(rand()) / RAND_MAX * 799.f;
            float y = 1.f + static_cast<float>(rand()) / RAND_MAX * 599.f;
            Prey p("Prey", preyTexture);
            p.sprite.setPosition(x, y);
            allPrey.push_back(p);
            spawnTimer = 0.f;
        }
        window.clear();
        // Draw all prey
        for (auto& prey : allPrey){
            prey.update();
            window.draw(prey.sprite);
        }
        // Predator eats prey
        for (size_t i = 0; i < predators.size(); i++){
            for (size_t j = 0; j < allPrey.size();){
                if (predators[i].sprite.getGlobalBounds().intersects(allPrey[j].sprite.getGlobalBounds())){
                    // Remove prey
                    allPrey.erase(allPrey.begin() + j);
                    Pred newPred("Predator", predTexture);
                    newPred.sprite.setPosition(predators[i].sprite.getPosition());
                    predators.push_back(newPred);
                } else{
                    j++; 
                }
            }
        }
        // Draw all pred
        for (auto& pred : predators){
            pred.update();
            window.draw(pred.sprite);
        }
        // Draw text
        window.draw(text);
        window.display();
    }
    return 0;
}

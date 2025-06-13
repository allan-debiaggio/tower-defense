#include "src/models/GameManager.h"
#include "src/models/LevelManager.h"
#include "src/models/Path.h"
#include "src/models/Enemy.h"
#include "src/models/Tower.h"
#include "src/models/MainMenuState.h"
#include <iostream>
#include <memory>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <optional>

int main()
{
  GameManager manager;

  // --- Level 1: 1 path, 1 wave, 2 enemies per wave, 2 enemy types ---
  std::vector<std::pair<float, float>> waypoints1 = {{0, 2}, {5, 2}, {9, 2}};
  Path path1(waypoints1);
  std::vector<Path> paths1 = {path1};
  int numWaves1 = 1;
  int enemiesPerWave1 = 2;
  auto enemyFactories1 = std::vector<WaveManager::EnemyFactory>{
      [](const Path &p)
      { return std::make_unique<GoombaEnemy>(p); },
      [](const Path &p)
      { return std::make_unique<ParagoombaEnemy>(p); }};
  auto level1 = std::make_unique<LevelManager>(10, 5, paths1, numWaves1, enemiesPerWave1);
  level1->setEnemyFactories(enemyFactories1);
  manager.addLevel(std::move(level1));

  // --- Level 2: 2 paths, 2 waves, 3 enemies per wave, 3 enemy types ---
  std::vector<std::pair<float, float>> waypoints2a = {{0, 1}, {4, 1}, {9, 1}};
  std::vector<std::pair<float, float>> waypoints2b = {{0, 3}, {4, 3}, {9, 3}};
  Path path2a(waypoints2a);
  Path path2b(waypoints2b);
  std::vector<Path> paths2 = {path2a, path2b};
  int numWaves2 = 2;
  int enemiesPerWave2 = 3;
  auto enemyFactories2 = std::vector<WaveManager::EnemyFactory>{
      [](const Path &p)
      { return std::make_unique<GoombaEnemy>(p); },
      [](const Path &p)
      { return std::make_unique<KoopaEnemy>(p); },
      [](const Path &p)
      { return std::make_unique<ParagoombaEnemy>(p); }};
  auto level2 = std::make_unique<LevelManager>(10, 5, paths2, numWaves2, enemiesPerWave2);
  level2->setEnemyFactories(enemyFactories2);
  manager.addLevel(std::move(level2));

  // --- Level 3: 3 paths, 3 waves, 4 enemies per wave, 3 enemy types (Boss in last wave) ---
  std::vector<std::pair<float, float>> waypoints3a = {{0, 0}, {9, 0}};
  std::vector<std::pair<float, float>> waypoints3b = {{0, 2}, {9, 2}};
  std::vector<std::pair<float, float>> waypoints3c = {{0, 4}, {9, 4}};
  Path path3a(waypoints3a);
  Path path3b(waypoints3b);
  Path path3c(waypoints3c);
  std::vector<Path> paths3 = {path3a, path3b, path3c};
  int numWaves3 = 3;
  int enemiesPerWave3 = 4;
  auto enemyFactories3 = std::vector<WaveManager::EnemyFactory>{
      [](const Path &p)
      { return std::make_unique<GoombaEnemy>(p); },
      [](const Path &p)
      { return std::make_unique<KoopaEnemy>(p); },
      [](const Path &p)
      { return std::make_unique<BowserEnemy>(p); }};
  auto level3 = std::make_unique<LevelManager>(10, 5, paths3, numWaves3, enemiesPerWave3);
  level3->setEnemyFactories(enemyFactories3);
  manager.addLevel(std::move(level3));

  // opening a window
  sf::RenderWindow window;
  window.create(sf::VideoMode({1200, 900}), "Fenetre");

  // création du sprite qui correspondent au chemin  
  sf::Texture text_chemin;
    if(! text_chemin.loadFromFile("./../assets/chemin.png"))
    {
      std::cout<< "ERROR ==============" << std::endl;
    }
  sf::Sprite chemin(text_chemin);
  chemin.setPosition({0, 300});

  // création du sprite qui correspond au chateau  
  sf::Texture text_chateau;
  if(!text_chateau.loadFromFile("./../assets/chateau.png"))
  {
    std::cout<< "ERROR ==============" << std::endl;    
  }
  sf::Sprite chateau(text_chateau);
  chateau.setPosition({930, 270});

  // création du sprite qui correspond à la tour  
  sf::Texture text_tour;
  if(!text_tour.loadFromFile("./../assets/tower.png"))
  {
    std::cout<< "ERROR ==============" << std::endl;    
  }
  sf::Sprite tower(text_tour);
  tower.setPosition({250, 500});

  // création du sprite qui correspond à l'ennemi
  sf::Texture text_goomba;
  if(!text_goomba.loadFromFile("./../assets/goomba.png"))
  {
    std::cout<< "ERROR ==============" << std::endl;    
  }
  sf::Sprite goomba(text_goomba);
  goomba.setPosition({0, 320});
  float goombXPos = 0.0f ;

  // Start the game
  manager.setState(std::make_unique<MainMenuState>());

    while (window.isOpen())
    {
        sf::Event event;
        // check all the window's events that were triggered since the last iteration of the loop
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Color lightblue(230, 242, 255);

        // Largeur du sprite pour espacer correctement
        float spriteWidth = static_cast<float>(text_chemin.getSize().x);
        float yPos = 300.f; // position verticale fixe

        window.clear(lightblue);

        goomba.setPosition(goombXPos, 320);
        goombXPos += 0.01 ;

        for (int i = 0; i < 6; ++i)
        {
            chemin.setPosition(i * spriteWidth, yPos);
            window.draw(chemin);
        }
        window.draw(chateau);
        window.draw(tower);
        window.draw(goomba);

        window.display();
    }

  return 0;
}

/**
 * prendre événements sur écran
 * = rendered event
 */
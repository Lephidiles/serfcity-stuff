#include <iostream>
#include <vector>
#include <cmath>

#include "SFML/Graphics.hpp"

#include "data.h"

int main(int argc, char* argv[]) {
  int next=atoi(argv[1]);
  Data gameData;

  gameData.Load();
  
  sf::RenderWindow window(sf::VideoMode(2048, 1536), "Settlers 1 remake");
  window.setFramerateLimit(25);

  Entry e=gameData.GetData(next);
  
  while (window.isOpen()) {
    sf::Event event;
    sf::Texture texture;
    sf::Sprite sprite;
    sprite.setScale(sf::Vector2f(4.f, 4.f));    
    
    while (window.pollEvent(event)) {
     switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;

        case sf::Event::KeyPressed:
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            ++next;
            e=gameData.GetData(next);
            gameData.Print(next);
            if (e.type==1) {
    	      window.clear();
              if (texture.create(e.X, e.Y)) {
                texture.update(&e.data[0]);
                texture.setSmooth(true);
                sprite.setTexture(texture);
              }
            }
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            --next;
            e=gameData.GetData(next);
            gameData.Print(next);
            if (e.type==1) {
              window.clear();
              if (texture.create(e.X, e.Y)) {
                texture.update(&e.data[0]);
                texture.setSmooth(true);
                sprite.setTexture(texture);
              }
            }
          }
          break;

        case sf::Event::MouseButtonPressed:
          if (event.mouseButton.button == sf::Mouse::Right) {
            std::cout << "Right Mouse pressed" << std::endl;
            std::cout << "Mouse x: " << event.mouseButton.x << std::endl;
            std::cout << "Mouse y: " << event.mouseButton.y << std::endl;
          }

        default:
          break;
      }
    }
    window.draw(sprite);
    window.display();
  }
  return 0;
}

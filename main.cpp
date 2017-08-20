#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"

#include "data.h"

int main(int argc, char* argv[]) {
  int next=atoi(argv[1]);
  Data gameData;

  gameData.Load();
  
  sf::RenderWindow window(sf::VideoMode(800, 800), "Settlers 1 remake");
  window.setFramerateLimit(40);

  gameData.Print(next);
  
  sf::Texture texture;
  if (!texture.create(200, 200))
    return 1;

  texture.update(txArray);

  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setScale(sf::Vector2f(4.f, 4.f));

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;

        case sf::Event::KeyPressed:
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            ++next;
            gameData.Print(next);
            txArray=gameData.PixelArray(next);
            texture.update(txArray);
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            --next;
            gameData.Print(next);
            txArray=gameData.PixelArray(next);
            texture.update(txArray);
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

    window.clear();
    window.draw(sprite);
    window.display();
  }
  return 0;
}

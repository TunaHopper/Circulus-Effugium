#include <cmath>
#include <iostream>
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"

int main() {
  sf::RenderWindow window;
  window.create(sf::VideoMode(1280, 720), "Circulus Effugium", sf::Style::Close | sf::Style::Titlebar, sf::ContextSettings(24, 1, 8));
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(false);
  window.setPosition(sf::Vector2i(100, 0));
  sf::Music backgroundMusic;
  sf::Texture floorTexture;
  sf::Texture characterTexture;
  sf::Texture backgroundTexture;
  sf::Font consolasFont;
  if(!backgroundMusic.openFromFile("music/backgroundMusic1.ogg")) {
    std::cout << "Error Code 01: Background music could not be loaded.\n";
    return EXIT_FAILURE;
  }
  if(!backgroundMusic.openFromFile("music/backgroundMusic2.ogg")) {
    std::cout << "Error Code 11: Background music could not be loaded.\n";
    return EXIT_FAILURE;
  }
  if(!floorTexture.loadFromFile("textures/floorTexture.png")) {
    std::cout << "Error Code 12: The floor texture could not be loaded.\n";
    return EXIT_FAILURE;
  }
  if(!characterTexture.loadFromFile("textures/characterTexture.png")) {
    std::cout << "Error Code 22: The character texture could not be loaded.\n";
    return EXIT_FAILURE;
  }
  if(!backgroundTexture.loadFromFile("textures/backgroundTexture.png")) {
    std::cout << "Error Code 02: Background texture could not be loaded.\n";
    return EXIT_FAILURE;
  }
  if(!consolasFont.loadFromFile("fonts/consolasFont.ttf")) {
    std::cout << "Error Code 03: Consolas font could not be loaded.\n";
    return EXIT_FAILURE;
  }
  backgroundMusic.setVolume(50);
  backgroundMusic.setLoop(true);
  backgroundMusic.play();
  sf::Sprite background(backgroundTexture);
  sf::RectangleShape floor(sf::Vector2f(1280, 200));
  floor.setPosition(0, 550);
  floor.setOutlineThickness(2);
  floor.setTexture(&floorTexture);
  floor.setOutlineColor(sf::Color::Black);

  sf::RectangleShape platform(sf::Vector2f(250, 50));
  platform.setPosition(450, 450);
  platform.setOutlineThickness(2);
  platform.setTexture(&floorTexture);
  platform.setOutlineColor(sf::Color::Black);

  const float radius = 30;
  sf::CircleShape character(radius, 36);
  float momentum = 0;
  character.setOutlineThickness(2);
  character.setOrigin(radius, radius);
  character.setTexture(&characterTexture);
  character.setPosition(1280 / 4, 720 / 4);
  character.setOutlineColor(sf::Color::Black);

  sf::Text version;
  version.setPosition(20, 5);
  version.setCharacterSize(16);
  version.setFont(consolasFont);
  version.setOutlineThickness(1);
  version.setString("Version 1.0");
  version.setFillColor(sf::Color::White);
  version.setOutlineColor(sf::Color::Black);
  while(window.isOpen()) {
    for(sf::Event event; window.pollEvent(event);) {
      if(event.type == sf::Event::Closed) {
	return 0;
      }
    }
    const float character_speed = 20.5f;
    const float max_y = (720 - 170 - radius - 2 - 2);
    float x_speed = 0;
    float y_speed = 0;
    if((momentum == 0) && (character.getPosition().y == max_y) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      momentum = 300;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      x_speed = -character_speed;
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      x_speed = character_speed;
    }
    if(x_speed || y_speed) {
      const float angle = std::atan2(y_speed, x_speed);
      character.move(character_speed * std::cos(angle), character_speed * std::sin(angle));
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2i mousePos = sf::Mouse::getPosition(window);
      character.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    }
    if(momentum > 0) {
      character.move(0, -character_speed);
      momentum -= character_speed;
      if(momentum < 0) {
	momentum = 0;
      }
    }
    character.move(0, character_speed / 2);
    //std::cout << momentum << '\n';
    if(character.getPosition().y > max_y) {
      character.setPosition(character.getPosition().x, max_y);
    }
    window.clear();
    window.draw(background);
    window.draw(floor);
    window.draw(platform);
    window.draw(character);
    window.draw(version);
    window.display();
  }
}


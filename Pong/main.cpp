// This example will use SFML libraries to implement
// the game of Pong

// History: 4/16 - Started from the SFML tutorial code that draws
//                a circle in the window.

#include <SFML/Graphics.hpp> 

#include "MainMenu.h"

int main(void){
	const int windowWidth = 960;
	const int windowHeight = 540;
	//make a window
	sf::RenderWindow MENU(sf::VideoMode(windowWidth,windowHeight), "Main Menu", sf::Style::Default);
	MainMenu mainMenu(MENU.getSize().x, MENU.getSize().y);

	//photo to main menu background
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(windowWidth, windowHeight));
	sf::Texture mainBackground;
	mainBackground.loadFromFile("Textures/mainScreen.png");
	background.setTexture(&mainBackground);

	//highscore
	int SCORE = 0;
	int highScore = 0;
	sf::Text text;
	sf::Font font;
	font.loadFromFile("Fonts/Arial.ttf");
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Black);
	text.setFont(font);
	text.setPosition(100.f, 205.f);
	//static "Highscore!"
	sf::Text text2;
	sf::Font font2;
	font2.loadFromFile("Fonts/Freedom.ttf");
	text2.setCharacterSize(50);
	text2.setFillColor(sf::Color::Red);
	text2.setOutlineThickness(1.f);
	text2.setOutlineColor(sf::Color::Yellow);
	text2.setFont(font2);
	text2.setString("High Score!");
	text2.setPosition(10.f, 70.f);
	
	

	while (MENU.isOpen()) {
		sf::Event event;
		while (MENU.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				MENU.close();
			}
			
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::W) {
					mainMenu.MoveUp();
					break;
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::S) {
					mainMenu.MoveDown();
					break;
				}
			}
			if (event.key.code == sf::Keyboard::Return) {
				sf::RenderWindow Host(sf::VideoMode(windowWidth, windowHeight), "Host Menu");
				sf::RenderWindow Join(sf::VideoMode(windowWidth, windowHeight), "Join Menu");

				int x = mainMenu.MainMenuPressed();
				if (x == 0) {
					SCORE = runGame(Host, Join, windowWidth,windowHeight);
					
					//set new high score
					if (SCORE >= highScore) {
						highScore = SCORE;
						std::stringstream ss;
						ss <<  SCORE;
						text.setString(ss.str());
					}
					
				}
				if (x == 1) {
					while (Join.isOpen()) {
						sf::Event aevent;
						while (Join.pollEvent(aevent)) {
							if (aevent.type == sf::Event::Closed) {
								Join.close();
							}

						}
						Host.close();
						Join.clear();
						Join.display();
					}
				}
				if (x == 2) {
					MENU.close();
					break;
				}
			}

		}
		MENU.clear();
		MENU.draw(background);
		mainMenu.draw(MENU);
		MENU.draw(text2);
		MENU.draw(text);
		MENU.display();
	}

	return 0;
}
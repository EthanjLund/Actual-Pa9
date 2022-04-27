#include"MainMenu.h"
#include"character.h"
#include"Coin.h"
#include"Artifact.h"
#include"Particles.h"

MainMenu::MainMenu(float width, float height) {
	
	if (!font.loadFromFile("Fonts/Freedom.ttf")) {
		std::cout << "could not load font\n";
	}
		
	//Host
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(sf::Color::Yellow);
	mainMenu[0].setString("Host");
	mainMenu[0].setOutlineThickness(3.f);
	mainMenu[0].setOutlineColor(sf::Color::Black);
	mainMenu[0].setCharacterSize(64);
	mainMenu[0].setPosition(720, 150);
	//join
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(sf::Color::Yellow);
	mainMenu[1].setString("Join");
	mainMenu[1].setOutlineThickness(3.f);
	mainMenu[1].setOutlineColor(sf::Color::Black);
	mainMenu[1].setCharacterSize(64);
	mainMenu[1].setPosition(720, 225);
	//Exit
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(sf::Color::Yellow);
	mainMenu[2].setString("Exit");
	mainMenu[2].setOutlineThickness(3.f);
	mainMenu[2].setOutlineColor(sf::Color::Black);
	mainMenu[2].setCharacterSize(64);
	mainMenu[2].setPosition(720, 300);

	MainMenuSelected = -1;
}

MainMenu::~MainMenu(){

}

void MainMenu::draw(sf::RenderWindow& window) {
	for (int i = 0; i < MAX_MAIN_MENU; i++) {
		window.draw(mainMenu[i]);
	}
}

void MainMenu::MoveUp() {
	if (MainMenuSelected - 1 >= 0) {
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Yellow);

		MainMenuSelected--;
		if (MainMenuSelected == -1) {
			MainMenuSelected = 2;
		}
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Red);
	}
}

void MainMenu::MoveDown() {
	if (MainMenuSelected + 1 <= MAX_MAIN_MENU) {

		mainMenu[MainMenuSelected].setFillColor(sf::Color::Yellow);

		MainMenuSelected++;
		if (MainMenuSelected == 3) {
			MainMenuSelected = 2;
		}
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Red);
	}
}

int runGame(sf::RenderWindow& window, sf::RenderWindow& window2, int windowWidth, int windowHeight) {
	window2.close();
	//init game 
	float gridSizeF = 64.f;//65
	unsigned girdSizeU = static_cast<unsigned>(gridSizeF);
	float dt = 0.f;
	sf::Clock dtClock;

	//sf::Vector2i mousePosScreen;
	//sf::Vector2i mousePosWindow;
	//sf::Vector2f mousePosView;
	//sf::Vector2u mousePosGrid;

	sf::Vector2f characterPosWindow;
	sf::Vector2i characterPosGrid;

	sf::Text text;
	sf::Font font;
	font.loadFromFile("Fonts/Arial.ttf");
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::Green);
	text.setFont(font);
	text.setPosition(20.f, 20.f);
	text.setString("Test");

	sf::Text textCoin;
	textCoin.setCharacterSize(30);
	textCoin.setFillColor(sf::Color::Green);
	textCoin.setFont(font);
	textCoin.setPosition(20.f, 50.f);
	textCoin.setString("Test");

	sf::Text score;
	score.setCharacterSize(30);
	score.setFillColor(sf::Color::Green);
	score.setFont(font);
	score.setPosition(20.f, 50.f);
	score.setString("Test");

	sf::Text times;
	times.setCharacterSize(30);
	times.setFillColor(sf::Color::Green);
	times.setFont(font);
	times.setPosition(20.f, 20.f);
	times.setString("Test");
	//init window

	window.setFramerateLimit(120);

	sf::View view;
	view.setSize(windowWidth, windowHeight);
	
	

	//view center is like spawn point
	view.setCenter(gridSizeF/2, gridSizeF/2);
	float viewSpeed = 500.f;//how fast the view moves like move speed
	
	const int mapSize = 22;//20 x 20 tiles//22
	//init game elements
	
	//map
	// 
	//map background 
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(gridSizeF * (mapSize - 1), gridSizeF * (mapSize - 1)));
	sf::Texture mainBackground;
	mainBackground.loadFromFile("Textures/mapGame.png");
	background.setTexture(&mainBackground);
	background.setPosition(0, 0);

	//tilemap
	std::vector<std::vector<sf::RectangleShape>> tileMap;

	tileMap.resize(mapSize, std::vector<sf::RectangleShape>());
	
	for (int x = 0; x < mapSize; x++)
	{
		tileMap[x].resize(mapSize, sf::RectangleShape());
		for (int y = 0; y < mapSize; y++)
		{
			if (x % 4 == 0) {
				tileMap[x][y].setSize(sf::Vector2f(gridSizeF, gridSizeF));
				tileMap[x][y].setFillColor(sf::Color::White);
				tileMap[x][y].setOutlineThickness(1.f);
				tileMap[x][y].setOutlineColor(sf::Color::Black);
				tileMap[x][y].setPosition(x * gridSizeF, y * gridSizeF);
			}
			else if(y %4 == 0) {
				tileMap[x][y].setSize(sf::Vector2f(gridSizeF, gridSizeF));
				tileMap[x][y].setFillColor(sf::Color::White);
				tileMap[x][y].setOutlineThickness(1.f);
				tileMap[x][y].setOutlineColor(sf::Color::Black);
				tileMap[x][y].setPosition(x * gridSizeF, y * gridSizeF);
			}
			else {
				tileMap[x][y].setSize(sf::Vector2f(gridSizeF, gridSizeF));
				tileMap[x][y].setFillColor(sf::Color::Red);
				tileMap[x][y].setPosition(x * gridSizeF, y * gridSizeF);
				
			}
			
		}
	}

	int fromX = 0;
	int toX = 0;
	int fromY = 0;
	int toY = 0;

	//character
	int half_Sprite_x = 0, hald_sprite_y = 0;
	bool keyPress = false;

	//create sprite

	Character model({ float(window.getSize().x) / 2 -32  ,float(window.getSize().y) / 2 -32 });

	//coins
	std::vector<Coin> coins;
	sf::Vector2i coinGridPos;
	
	Coin coin;
	coin.spawn();

	coins.push_back(coin); //////////////////////////////////////////////////////////////////////////////////////////////////////////////

	sf::Vector2f NULLCase = { NULL, NULL };

	//tile selctor
	//sf::RectangleShape tileSelector(sf::Vector2f(gridSizeF, gridSizeF));

	//tileSelector.setFillColor(sf::Color::Transparent);
	//tileSelector.setOutlineThickness(1.f);
	//tileSelector.setOutlineColor(sf::Color::Green);
	// 
	//artifact
	sf::Vector2i artifactGridPos;
	Artifact artifact;
	artifact.spawn();
	sf::Clock clock;
	sf::Time elapsed;
	bool hasArtifact = false;
	bool spawnArtifact = false;

	//hiding

	sf::RectangleShape rect;


	//timer
	sf::Clock gameClock;
	sf::Time gameElapsed;

	//Particles
	ParticleSystem speedParticles(10000);
	speedParticles.setScale({ 1,1 });
	sf::Clock particleClock;
	sf::Time particleElapsed;
	bool spawnParticles = false;

	//Time

	sf::Time speedBuffLength = sf::seconds(10.0f);
	sf::Time ArtifactSpawnCooldown = sf::seconds(20.f);
	sf::Time gameLength = sf::seconds(100.f);
	sf::Time timeRemaining = sf::seconds(100.0f);

	//collision

	sf::FloatRect NextPos;

	int SCORE = 0;


	//Time

	sf::Time second = sf::seconds(0.01f);


	gameClock.restart();
	while (window.isOpen())
	{
		//Update dt
		dt = dtClock.restart().asSeconds();
		
		//update mouse positions
	/*	mousePosScreen = sf::Mouse::getPosition();
		mousePosWindow = sf::Mouse::getPosition(window);
		window.setView(view);
		mousePosView = window.mapPixelToCoords(mousePosWindow);
		if (mousePosView.x >= 0.f) {
			mousePosGrid.x = mousePosView.x / gridSizeF;
		}
		if (mousePosView.y >= 0.f) {
			mousePosGrid.y = mousePosView.y / gridSizeF;
		}*/

		//game timer
		gameElapsed = gameClock.getElapsedTime();
		timeRemaining = gameLength;
		timeRemaining -= gameElapsed;
		std::cout << gameElapsed.asSeconds() << std::endl;
		if (gameElapsed.asSeconds() >= gameLength.asSeconds()) {
			break;
		}

		//grid position of view for location of character
		characterPosWindow = view.getCenter();
		
		window.setView(view);
		
		//get character postion
		if (characterPosWindow.x < 0) {
			characterPosWindow.x = -gridSizeF-1;
		}
		characterPosGrid.x = characterPosWindow.x / gridSizeF;
			
		if (characterPosWindow.y < 0) {//componsates for 0,0 logic error with negative numbers
			characterPosWindow.y = -gridSizeF-1;
		}
			characterPosGrid.y = characterPosWindow.y / gridSizeF;
			

		window.setView(window.getDefaultView());
		//update game elements
		/*tileSelector.setPosition(mousePosGrid.x * gridSizeF, mousePosGrid.y * gridSizeF);*/
		sf::Vector2f dir = { 0.0, 0.0 };
		//update ui
		/*std::stringstream ss;
		ss << "Character grid: "<<characterPosGrid.x<<" "<< characterPosGrid.y << "\n";
		text.setString(ss.str());
		
		std::stringstream cs;
		cs << "Coin grid: " << artifactGridPos.x << " " << artifactGridPos.y << "\n";
		textCoin.setString(cs.str()); */

		std::stringstream sss;
		sss << "Score: " << SCORE << "\n";
		score.setString(sss.str());

		std::stringstream ssss;
		ssss << "Time Remaining: " << timeRemaining.asSeconds() << "\n";
		times.setString(ssss.str());

		//events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
				
			}
		}
		//update
		//update input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {//left
			if (characterPosWindow.x-5 < 0) {
				view.move(0.f, 0.f);
			}
			else if (characterPosGrid.y % 4 != 0 && characterPosWindow.x > characterPosGrid.x * gridSizeF + 10) {
				view.move(-viewSpeed * dt, 0.f);
			}
			else if (characterPosGrid.y % 4 == 0) {
				view.move(-viewSpeed * dt, 0.f);
			}
			else {
				view.move(0.f, 0.f);
			}
			
			//character
			dir.x -= 1.0;
			keyPress = true;
			
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {//Right
			if (characterPosWindow.x > (mapSize-1) * gridSizeF  - 15) {// 32 is a static offset do to height of character in pixels
				view.move(0.f, 0.f);
			}
			else if (characterPosGrid.y % 4 != 0 && characterPosWindow.x < characterPosGrid.x * gridSizeF + (gridSizeF-10)) {
				view.move(viewSpeed * dt, 0.f);
			}
			else if (characterPosGrid.y % 4 == 0 ) {
				view.move(viewSpeed * dt, 0.f);
			}
			else {
				view.move(0.f, 0.f);
			}

			dir.x += 1.0;
			keyPress = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {//Up
			if (characterPosWindow.y - 5 < 0) {
				view.move(0.f, 0.f);
			}
			else if (characterPosGrid.x % 4 != 0 && characterPosWindow.y > characterPosGrid.y * gridSizeF  + (10)) {
				view.move(0.f, -viewSpeed * dt);
			}
			else if (characterPosGrid.x  % 4 == 0) {
				view.move(0.f, -viewSpeed * dt);
			}
			else {
				view.move(0.f, 0.f);
			}
			dir.y -= 1.0;
			keyPress = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {//Down
			if (characterPosWindow.y > (mapSize-1) * gridSizeF - 32) {// 32 is a static offset do to height of character in pixels
				view.move(0.f, 0.f);
			}
			else if (characterPosGrid.x % 4 != 0 && characterPosWindow.y<characterPosGrid.y*gridSizeF+(gridSizeF/2)) {
				view.move(0.f, viewSpeed * dt);
			}
			else if (characterPosGrid.x %4 ==0) {
				view.move(0.f, viewSpeed * dt);
			}
			else {
				view.move(0.f, 0.f);
			}
			dir.y += 1.0;
			keyPress = true;
		}
		if (keyPress == true) {
			model.setDirection(dir);

			//update model
			model.update(dt);

			keyPress = false;
		}


		//render
		window.clear();
		window.setView(view);
		
		//render game elements
		window.draw(background);
		//map
		
		fromX = view.getCenter().x / gridSizeF - 8;
		toX = view.getCenter().x / gridSizeF + 9;
		fromY = view.getCenter().y / gridSizeF -5;
		toY = view.getCenter().y / gridSizeF + 6;
		//only loads what is on the view
		if (fromX < 0) {
			fromX = 0;
		}
		else if (fromX >= mapSize) {
			fromX = mapSize - 1;
		}
		if (fromY < 0) {
			fromY = 0;
		}
		else if (fromY >= mapSize) {
			fromY = mapSize - 1;
		}

		if (toX < 0) {
			toX = 0;
		}
		else if (toX >= mapSize) {
			toX = mapSize - 1;
		}
		if (toY < 0) {
			toY = 0;
		}
		else if (toY >= mapSize) {
			toY = mapSize - 1;
		}

		for (int x = fromX; x < toX; x++)
		{
			for (int y = fromY; y < toY; y++)
			{
				window.draw(tileMap[x][y]);
			}
		}
		
		if (coins.size() < 7) {
			coin.spawn();
			coins.push_back(coin);
		}
		//artifactGridPos = artifact.itemGridPos();

		//collision
		for (auto& coin : coins) {


			coinGridPos = coin.itemGridPos();

			if (coinGridPos == characterPosGrid) {
				coin.spawn();
				//coin.deleteItem(); 

				SCORE++;
				std::cout << "COLLISION" << std::endl;
			}

		}



		artifactGridPos = artifact.itemGridPos();

		if (artifactGridPos == characterPosGrid) {
			clock.restart();
			viewSpeed += 150;
			hasArtifact = true;
			spawnArtifact = true;
			artifact.deleteItem();
			spawnParticles = true;

		}

		if (hasArtifact == true) {
			elapsed = clock.getElapsedTime();

			if (elapsed.asSeconds() >= speedBuffLength.asSeconds()) {
				viewSpeed -= 150;
				hasArtifact = false;
				spawnParticles = false;
			}
		}

		if (spawnArtifact == true) {
			elapsed = clock.getElapsedTime();

			if (elapsed.asSeconds() >= ArtifactSpawnCooldown.asSeconds()) {
				artifact.spawn();
				spawnArtifact = false;

			}
		}

		//Particles
		if (spawnParticles == true) {
			speedParticles.setEmitter({ model.getPos().x + 32,model.getPos().y + 32 });
			//speedParticles.setEmitter(view.getCenter());
			particleElapsed = particleClock.restart();
			speedParticles.update(particleElapsed);
		}
		//selector
		/*window.draw(tileSelector);*/
		//draw ui
		window.draw(background);
		for (auto& i : coins) {

			i.draw(window);

		}

		artifact.draw(window);

		rect.setFillColor(sf::Color::Black);
		rect.setPosition(1400, 900);
		rect.setSize({ 64,64 });
		window.draw(rect);
		//selector
		/*window.draw(tileSelector);*/
		//draw ui
		
		window.setView(window.getDefaultView());

		if (spawnParticles == true) {
			window.draw(speedParticles);
		}
		
		model.draw(window);
		//window.draw(text);
		//window.draw(textCoin);
		window.draw(score);
		window.draw(times);
		//finished
		window.display();

		
	}
	return SCORE;
}
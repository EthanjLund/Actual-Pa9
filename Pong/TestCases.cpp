#include"MainMenu.h"
#include"character.h"
#include"Coin.h"
#include"Artifact.h"
#include"Particles.h"

void loadFontsAndTextures() {
	//fonts
	sf::Font font;
	if (font.loadFromFile("Fonts/Freedom.ttf")) {
		std::cout << "loaded Freedom font\n";
	}
	else {
		std::cout << "could not load freedom font\n";
	}
	if (font.loadFromFile("Fonts/Arial.ttf")) {
		std::cout << "loaded Arial font\n";
	}
	else {
		std::cout << "could not load Arial font\n";
	}

	//textures
	sf::Texture tex;
	if (tex.loadFromFile("Textures/mapGame.png")) {
		std::cout << "loaded Map image succesfully\n";
	}
	else {
		std::cout << "could not load map image\n";
	}

	if (tex.loadFromFile("Textures/mainScreen.png")) {
		std::cout << "loaded mainScreen succesfully\n";
	}
	else {
		std::cout << "could not load mainScreen image\n";
	}

	if (tex.loadFromFile("Textures/professor_walk_cycle_no_hat.png")) {
		std::cout << "loaded character image succesfully\n";
	}
	else {
		std::cout << "could not load character image\n";
	}

	if (tex.loadFromFile("Textures/coinSprite.png")) {
		std::cout << "loaded coin image succesfully\n";
	}
	else {
		std::cout << "could not load coin image\n";
	}

	if(tex.loadFromFile("Textures/purple_orb.png")) {
		std::cout << "loaded orb image succesfully\n";
	}
	else {
	std::cout << "could not load orb image\n";
	}
}

void testCharacterBounding() {
	int gridSizeF = 65;
	//up case when in outbounds area
	int y = 2;
	int x = 2;
	float wY = 70;

	bool move = false;
	if (wY - 5 < 0) {
		move = false;
	}
	else if (x % 4 != 0 && y > wY * gridSizeF + (10)) {
		move = true;
	}
	else if (x % 4 == 0) {
		move = true;
	}
	else {
		move = false;
	}

	if (move == false) {
		std::cout << "Prevented movement when inside a bounded area\n";
	}
	else {
		std::cout << "failed to Prevent movement when inside a bounded area\n";
	}


	//downwards movementn when on path
	int mapSize = 22;
	y = 1;
	if (wY > (mapSize - 1) * gridSizeF - 32) {// 32 is a static offset do to height of character in pixels
		move = false;
	}
	else if (x % 4 != 0 && wY < y * gridSizeF + (gridSizeF / 2)) {
		move = true;
	}
	else if (x % 4 == 0) {
		move = true;
	}
	else {
		move = false;
	}

	if(move==false) {
		std::cout << "Prevented movement into a bounded area\n";
	}
	else {
		std::cout << "failed to Prevent movement into a bounded area\n";
	}
}

void testItemCollision(Item& item) {

	sf::Vector2i characterPosGrid = { 0,0 }, itemPosGrid = { 0,0 };

	item.spawn();
	std::cout << "Item pixel position: " << item.getPos().x << ", " << item.getPos().y << std::endl;

	itemPosGrid = item.itemGridPos();
	std::cout << "Item grid position: " << itemPosGrid.x << ", " << itemPosGrid.y << std::endl;

	while (itemPosGrid != characterPosGrid) {
		if (characterPosGrid.x < itemPosGrid.x) {
			characterPosGrid.x += 1;
		}
		if (characterPosGrid.x > itemPosGrid.x) {
			characterPosGrid.x -= 1;
		}
		if (characterPosGrid.y < itemPosGrid.y) {
			characterPosGrid.y += 1;
		}
		if (characterPosGrid.y > itemPosGrid.y) {
			characterPosGrid.y -= 1;
		}
		std::cout << "Character grid position: " << characterPosGrid.x << ", " << characterPosGrid.y << std::endl;
	}
	if (itemPosGrid == characterPosGrid) {
		//cout << "COLLISION" << endl;
		std::cout << "Collision Test Passed!" << std::endl;
	}
}

void testCreationTileMap() {
	std::vector<std::vector<sf::RectangleShape>> tileMap;
	int gridSizeF = 65;
	int mapSize = 22;
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
			else if (y % 4 == 0) {
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

	bool t1 = false, t2 = false;
	if (tileMap[1][1].getFillColor() == sf::Color::Red) {
		std::cout << "top left red zone has been made correctly\n";
		t1 = true;
	}
	else {
		std::cout << "top left red zone has been made incorrectly\n";
	}
	if (tileMap[20][20].getFillColor() == sf::Color::Red) {
		std::cout << "bottom right red zone has been made correctly\n";
		t2 = true;
	}
	else {
		std::cout << "bottom right red zone has been made incorrectly\n";
	}

	if (t1 && t2) {
		std::cout<<"map made correctly\n";
	}
}

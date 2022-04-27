#pragma once



#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string> 

#include "Item.h"

using std::string;

class Coin : public Item {
private:
	string textureName;

public:
	Coin() {
		textureName = "Textures/coinSprite.png";
		loadNewTexture(textureName);
		setSpriteTexture();
		changeSpriteScale({ 0.07, 0.07 });
	}



};
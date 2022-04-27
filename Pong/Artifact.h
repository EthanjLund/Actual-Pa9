#pragma once



#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string> 

#include "Item.h"

using std::string;

class Artifact : public Item {
private:
	string textureName;

public:
	Artifact() {
		textureName = "Textures/purple_orb.png";
		loadNewTexture(textureName);
		setSpriteTexture();
		changeSpriteScale({ 0.1, .10 });
	}



};
#pragma once
#include <SFML/Graphics.hpp>
#include "config.h"

class Bird
{
public:
	Bird();
	~Bird();

	sf::Sprite bird;
	
	void create(sf::Texture&);
	void reset();
	void draw(sf::RenderWindow& window);

	float x() { return bird.getPosition().x; }
	float y() { return bird.getPosition().y; }
	float left() { return x() + 68 * bird.getScale().x; }
	float right() { return x() + (bird.getTexture()->getSize().x - 68) * bird.getScale().x; }
	float top() { return y(); }
	float bottom() { return y() + bird.getTexture()->getSize().y * bird.getScale().y; }
};


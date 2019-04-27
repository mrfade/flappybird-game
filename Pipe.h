#pragma once
#include <SFML/Graphics.hpp>

class Pipe
{
public:
	Pipe();
	~Pipe();

	sf::Sprite pipe;
	bool counted = false;

	void create(sf::Texture&);
	void draw(sf::RenderWindow& window);

	float x() { return pipe.getPosition().x; }
	float y() { return pipe.getPosition().y; }
	float left() { return x(); }
	float right() { return x() + pipe.getTexture()->getSize().x * pipe.getScale().x; }
	float top() { return y(); }
	float bottom() { return y() + pipe.getTexture()->getSize().y * pipe.getScale().y; }
};


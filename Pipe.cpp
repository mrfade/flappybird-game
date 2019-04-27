#include "Pipe.h"


Pipe::Pipe()
{
}

Pipe::~Pipe()
{
}

void Pipe::create(sf::Texture &pipeTexture)
{
	pipe.setTexture(pipeTexture);
	pipe.setPosition(0, 0);
	pipe.setScale(0.15f, 0.15f);
	pipe.move(sf::Vector2f(500.0f, 0.0f));
}

void Pipe::draw(sf::RenderWindow & window)
{
	window.draw(this->pipe);
}

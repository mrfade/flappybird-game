#include "Bird.h"


Bird::Bird()
{
}

Bird::~Bird()
{
}

void Bird::create(sf::Texture & birdTexture)
{
	bird.setTexture(birdTexture);
	bird.setScale(0.1f, 0.1f);
	bird.setPosition(sf::Vector2f(WIN_WIDTH / 2 - bird.getGlobalBounds().width / 2.0f, WIN_HEIGHT / 2));
}

void Bird::reset()
{
	bird.setPosition(sf::Vector2f(WIN_WIDTH / 2 - bird.getGlobalBounds().width / 2.0f, WIN_HEIGHT / 2));
}

void Bird::draw(sf::RenderWindow & window)
{
	window.draw(this->bird);
}

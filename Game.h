#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "config.h"
#include "Pipe.h"
#include "Bird.h"
#include <iostream>

class Game
{
public:
	Game();
	~Game();

	sf::RenderWindow window;
	sf::View view;
	float deltaTime;

	void createWindow();
	void loadResources();
	void initGame();
	void restartGame();
	void update();
	void display();

	float viewSpeed = 0.0f;
	float viewAcc = 0.0f;
	float totalWidth = 0;
	int start = 20;
	int total = 0;

	bool gameRunning = false;
	bool gameLost = false;
	bool hitSoundPlayed = false;

	float rotation = 0;
	sf::Vector2f velocity;

private:
	sf::Texture backgroundTexture, groundTexture, birdTexture, pipeTexture, downsidePipeTexture;
	sf::Sprite background, ground;
	sf::SoundBuffer wingSoundBuffer, pointSoundBuffer, hitSoundBuffer;
	sf::Sound wingSound, pointSound, hitSound;
	std::vector<Pipe> pipes;
	Pipe pipe;
	Pipe downsidePipe;
	Bird bird;

	sf::Font font;
	sf::Text score, genText;

	sf::Vector2f centerTextPosition(sf::Text&);

	void fillPipes(unsigned int, unsigned int);
	template <class T1, class T2> bool testCollision(T1&, T2&);
};

template<class T1, class T2>
inline bool Game::testCollision(T1 & A, T2 & B)
{
	return A.right() >= B.left() && A.left() <= B.right() && A.bottom() >= B.top() && A.top() <= B.bottom();
}

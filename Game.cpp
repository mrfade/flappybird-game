#include "Game.h"


Game::Game()
{
}

Game::~Game()
{
}

void Game::createWindow()
{
	window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "JUMP");
	window.setFramerateLimit(FrameLimit);

	view.setSize(VIEW_HEIGHT, VIEW_HEIGHT);
	view.setCenter(VIEW_HEIGHT / 2, VIEW_HEIGHT / 2);

	sf::Image icon;
	icon.loadFromFile("resources/images/icon.png");
	window.setIcon(32, 23, icon.getPixelsPtr());
	
}

void Game::loadResources()
{
	font.loadFromFile("resources/fonts/font.ttf");

	backgroundTexture.loadFromFile("resources/images/back.png");
	groundTexture.loadFromFile("resources/images/ground.png");
	birdTexture.loadFromFile("resources/images/bird.png");
	pipeTexture.loadFromFile("resources/images/pipe.png");
	downsidePipeTexture.loadFromFile("resources/images/downside-pipe.png");

	backgroundTexture.setRepeated(true);
	groundTexture.setRepeated(true);

	background.setTexture(backgroundTexture);
	background.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(200 * 5 * 5, backgroundTexture.getSize().y)));
	background.setScale(sf::Vector2f(1.0f, (float)WIN_HEIGHT / (backgroundTexture.getSize().y + groundTexture.getSize().y)));
	background.setPosition(-(5 * 200), 0);

	ground.setTexture(groundTexture);
	ground.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(200 * 5 * 5, groundTexture.getSize().y)));
	ground.setScale(sf::Vector2f(1.0f, (float)WIN_HEIGHT / (backgroundTexture.getSize().y + groundTexture.getSize().y)));
	ground.setPosition(-(5 * 200), background.getGlobalBounds().height);

	wingSoundBuffer.loadFromFile("resources/sounds/sfx_wing.wav");
	pointSoundBuffer.loadFromFile("resources/sounds/sfx_point.wav");
	hitSoundBuffer.loadFromFile("resources/sounds/sfx_hit.wav");

	wingSound.setBuffer(wingSoundBuffer);
	pointSound.setBuffer(pointSoundBuffer);
	hitSound.setBuffer(hitSoundBuffer);
}

void Game::initGame()
{
	loadResources();

	score.setFont(font);
	score.setFillColor(sf::Color::White);
	score.setOutlineColor(sf::Color::Black);
	score.setOutlineThickness(3.0f);
	score.setCharacterSize(50);
	score.setPosition(WIN_WIDTH / 2 - 15, 15);

	sf::Vector2f velocity(0.0f, 0.0f);

	pipe.create(pipeTexture);
	downsidePipe.create(downsidePipeTexture);
	bird.create(birdTexture);

	this->fillPipes(5, 15);

	genText.setFont(font);
	genText.setCharacterSize(20);
	genText.setFillColor(sf::Color::White);
	genText.setOutlineColor(sf::Color::Black);
	genText.setOutlineThickness(2.0f);
	genText.setString("Space to start game");
	genText.setPosition((WIN_WIDTH - genText.getGlobalBounds().width) / 2.0f, (WIN_HEIGHT - genText.getGlobalBounds().height) / 2.0f);
}

void Game::restartGame()
{

	view.setCenter(VIEW_HEIGHT / 2, VIEW_HEIGHT / 2);

	velocity.y = -sqrtf(2.0f * 981.0f * 100);

	viewSpeed = 100.0f;
	viewAcc = 1.0f;
	velocity.x = viewSpeed;
	totalWidth = 0;
	start = 20;
	total = 0;
	hitSoundPlayed = false;

	bird.reset();

	score.setString(std::to_string(total / 2));
	score.setPosition(centerTextPosition(score).x, 15);
	genText.setPosition((WIN_WIDTH - genText.getGlobalBounds().width) / 2.0f, (WIN_HEIGHT - genText.getGlobalBounds().height) / 2.0f);

	pipes.clear();
	this->fillPipes(5, 15);
}

void Game::update()
{

	if (!gameRunning && !gameLost && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		viewSpeed = 100.0f;
		viewAcc = 1.0f;
		velocity.x = viewSpeed;
		gameRunning = true;
	}

	if (gameLost && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		restartGame();
		gameLost = false;
		gameRunning = true;
	}

	if (gameRunning) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			velocity.y = -sqrtf(2.0f * 981.0f * 100);
			wingSound.play();
		}

		viewSpeed += viewAcc * deltaTime;

		velocity.y += 2 * 981.0f * deltaTime;
		velocity.x = viewSpeed;
		bird.bird.move(velocity * deltaTime);

		if (bird.bird.getPosition().y > background.getGlobalBounds().height - bird.bird.getGlobalBounds().height) {
			bird.bird.setPosition(bird.bird.getPosition().x, background.getGlobalBounds().height - bird.bird.getGlobalBounds().height);
			gameLost = true;
		}

		if (bird.bird.getPosition().y < 0) {
			bird.bird.setPosition(bird.bird.getPosition().x, bird.bird.getGlobalBounds().height);
			velocity.y = 0.0f;
		}

		if (totalWidth / 200.0f > 10.0f) {

			if (pipes.size() >= 40) pipes.erase(pipes.begin(), pipes.begin() + 20);

			fillPipes(start, 10);

			background.setPosition((start - 15) * 200, 0);
			ground.setPosition((start - 15) * 200, background.getGlobalBounds().height);

			totalWidth = totalWidth - (int)totalWidth;
			start += 10;
		}
	}

	window.draw(background);

	bird.draw(window);

	for (int i = 0; i < pipes.size(); i++)
	{
		if (testCollision(pipes[i], bird)) 
			gameLost = true;

		if (pipes[i].right() - (pipes[i].right() - pipes[i].left()) / 2.0f < bird.left() && !pipes[i].counted) {
			total++;
			pipes[i].counted = true;
			if (total % 2 == 0) pointSound.play();
		}

		pipes[i].draw(window);
	}

	window.draw(ground);

	if (!gameRunning && !gameLost) {
		window.draw(genText);
	}

	if (gameLost) {

		if (!hitSoundPlayed) {
			hitSound.play();
			hitSoundPlayed = true;
		}

		viewSpeed = 0.0f;
		viewAcc = 0.0f;
		velocity.x = 0.0f;

		genText.setCharacterSize(40);
		genText.setFillColor(sf::Color(231, 76, 60));
		genText.setString("YOU LOST!");
		genText.setPosition(centerTextPosition(genText).x, centerTextPosition(genText).y - 100);
		window.draw(genText);
		
		genText.setCharacterSize(20);
		genText.setFillColor(sf::Color::White);
		genText.setString("Enter to restart game");
		genText.move(-25.0f, 80.0f);
		window.draw(genText);

		this->gameRunning = false;
	}

	genText.move(viewSpeed * deltaTime, 0.0f);

	score.setString(std::to_string(total / 2));
	score.setPosition(centerTextPosition(score).x, 15);
	window.draw(score);

	view.move(viewSpeed * deltaTime, 0.0f);

	totalWidth += viewSpeed * deltaTime;
}

void Game::display()
{
	window.setView(view);
	window.display();
}

sf::Vector2f Game::centerTextPosition(sf::Text & text)
{
	return sf::Vector2f(bird.left() + (bird.right() - bird.left()) / 2.0f - text.getGlobalBounds().width / 2, (WIN_HEIGHT - text.getGlobalBounds().height) / 2.0f);
}

void Game::fillPipes(unsigned int start, unsigned int count)
{
	int randomHeight, randomGap;
	for (int i = start; i < start + count; i++)
	{
		randomHeight = rand() % ((int)background.getGlobalBounds().height / 3) + ground.getGlobalBounds().height + 20;
		randomGap = rand() % ((int)background.getGlobalBounds().height / 4) + background.getGlobalBounds().height / 4;
		pipe.pipe.setPosition(i * 200, WIN_HEIGHT - randomHeight);
		pipes.push_back(pipe);
		downsidePipe.pipe.setPosition(i * 200, WIN_HEIGHT - randomHeight - randomGap - downsidePipe.pipe.getTexture()->getSize().y * downsidePipe.pipe.getScale().y);
		pipes.push_back(downsidePipe);
	}
}

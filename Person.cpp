#include "Person.hpp"
#include "SFML/Graphics.hpp"
#include "Settings.hpp"
#include <iostream>

/* 
* Constructor for Player Class 
*/
Person::Person(){
	
	// gets the sprites from the images
	if(!texture.loadFromFile("sprites/player_movement.png")){
		exit(EXIT_FAILURE);
	}
	sprite.setTexture(texture);
	
	// Sets the boundries
	sf::FloatRect spriteSize = sprite.getGlobalBounds();
	sprite.setOrigin(spriteSize.width/2.0, spriteSize.height/2.0);
	
	// Loads sounds
	if(!punchBuffer.loadFromFile("sounds/punch.wav")){
		std::cerr << "Can't load punch sound." << std::endl;
	}
	punch.setBuffer(punchBuffer);
	initialize();
}

/* 
* Creates the size and speed of the player
*/
void Person::initialize(){
	x = WIDTH / 2;
	y = HEIGHT / 2;
	health = STARTING_HEALTH;
    speed = STARTING_SPEED;
	sprite.setPosition(x, y);
}


/* 
* getter for sprite
*/
sf::Sprite Person::getSprite(){
	return this->sprite;
}


/* 
* getter for health 
*/
int Person::getHealth(){
	return this->health;
}


/* 
* setter for health
*/
void Person::setHealth(int health){
	this->health = health;
}

/* 
* Ignore
*/
void Person::updatePosition(int dx, int dy){
    // ignore
}


/* 
* subrtracts health from the player 
*/
void Person::harm(int hp){
	health = health - hp;
	punch.play();
}


/* 
* puts the sprite in the window
*/
void Person::render(sf::RenderTarget& window) {

	
    if (animationClock.getElapsedTime().asMilliseconds() > ANIMATION_SPEED) {
        currentFrame++;
		animationClock.restart();
    }
	
	// if the frame is still running and the amount of frames is greater
	// than the number of frames in the animation then reset the counter
    if (running) {
        if (currentFrame >= runAnim.size()) {
            currentFrame = 0;
        }

    }
    else {
	    
	// if the frame is still running and the amount of frames is greater
	// than the number of frames in the animation then reset the counter
        if (currentFrame >= idleAnim.size()) {
            currentFrame = 0;
        }
    }

    sf::IntRect rect = playerFrameSize;

    if (running) {
        rect.left = rect.width * runAnim[currentFrame];
    } else {
        rect.left = rect.width * idleAnim[currentFrame];
    }

    // If we're facing left, we want to flip the texture coordinates.
	if (facing == PlayerDirection::West) {
        rect.left += rect.width;
		rect.width = -rect.width;
	}

    sprite.setTextureRect(rect);

}
/*
* Updates the hit box of the player so that it moves with the annimation
*/
void Person::update() {
	
	// Creates a variable that finds our change over time
	float delta = (float(movementClock.restart().asMicroseconds()) * float(1e-6));

    running = false;

	// Moves up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		y -= speed * delta;
        running = true;
	}
	// Moves down
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		y += speed * delta;
        running = true;
	}
	
	// Moves left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		x -= speed * delta;
        running = true;
	
	// Makes sure the sprite is faced in the proper direction
        facing = PlayerDirection::West;
	}
	
	// Moves right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		x += speed * delta;
        running = true;
		
	
	// Makes sure the sprite is faced in the proper direction
        facing = PlayerDirection::East;
	}

	sprite.setPosition(x, y);
}

/*
* getter for Speed
*/
float Person::getSpeed() {
	return speed;
}

/*
* setter for Speed
*/
void Person::setSpeed(float pixelsPerSecond) {
	speed = pixelsPerSecond;
}

/*
* getter for Position
*/
sf::Vector2f Person::getPosition() {
    return {x, y};
}

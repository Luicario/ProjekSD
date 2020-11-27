#include "Player.h"

Player::Player() {
	initTexture();
	initSprite();
	initCooldown();
	hit = 0;
	dead = false;
	movementspeed = 4.f;
	health = 30;
}

void Player::initSprite() {
	//Load a texture from file
	sprite.setTexture(texture);
	//Resize
	sprite.scale(1.f, 1.f);
	 
}
void Player::initTexture() {
	//Set the texture to the sprite
	if (!texture.loadFromFile("Texture/ship_lvl_1.png")) {
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file" << std::endl;
	}
}

void Player::initCooldown() {
	attackCooldownMax = 15.f;
	attackCooldown = attackCooldownMax;
}

void Player::changeTexture(int lvl)
{
	
		//Set the texture to the sprite
		if (!texture.loadFromFile("Texture/ship_lvl_" + std::to_string(lvl) +"2.png")) {
			std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file" << std::endl;
		}
		//Load a texture from file
		sprite.setTexture(texture);
		//Resize
		sprite.scale(1.f, 1.f);
	
	
}

void Player::setStatus(bool _dead) {
	dead = _dead;
}

void Player::setHealth(int h) {
	health = h;
}

void Player::setHit(int h) {
	health -= h;
}

void Player::move(const float dirX, const float dirY) {
	sprite.move(movementspeed * dirX, movementspeed * dirY);
}

void Player::render(RenderTarget& target) {
	target.draw(sprite);
}

void Player::updateAttack() {
	if (attackCooldown < attackCooldownMax) {
		attackCooldown += 0.5f;
	}
}

void Player::increaseFireRate() {
	attackCooldownMax -= 0.2f;
}

void Player::addHealth(int h) {
	if (health + h > 30)
		health = 30;
	else
		health += h;
}

void Player::update()
{
	unsigned int ujungKanan = VideoMode::getDesktopMode().width - 150;
	unsigned int batasBawah = VideoMode::getDesktopMode().height / 4 * 3 - 40;
	unsigned int batasAtas = 5;
	unsigned int ujungKiri = 5;

	if (sprite.getPosition().x < ujungKiri) {

		if (sprite.getPosition().x < ujungKiri && sprite.getPosition().y < batasAtas)
			sprite.setPosition(ujungKiri, batasAtas);
		
		else if (sprite.getPosition().x < ujungKiri && sprite.getPosition().y >= batasBawah)
			sprite.setPosition(ujungKiri, batasBawah);
		
		else 
			sprite.setPosition(ujungKiri, sprite.getPosition().y);
			
	}
	else if (sprite.getPosition().x >= ujungKanan) {

		if (sprite.getPosition().x >= ujungKanan && sprite.getPosition().y < 5)
			sprite.setPosition(ujungKanan, 5);
		
		else if (sprite.getPosition().x >= ujungKanan && sprite.getPosition().y >= batasBawah)
			sprite.setPosition(ujungKanan, batasBawah);
		
		else 
			sprite.setPosition(ujungKanan, sprite.getPosition().y);

	}
	else if (sprite.getPosition().y < batasAtas) 
		sprite.setPosition(sprite.getPosition().x, batasAtas);
	
	else if (sprite.getPosition().y >= batasBawah) 
		sprite.setPosition(sprite.getPosition().x, batasBawah);
	
	updateAttack();

	if (getHealth() <= 0) {
		setStatus(true);
	}
}


int Player::getHealth() { return health; }
int Player::getHit() { return hit; }
bool Player::getStatus() { return dead; }

const bool Player::canAttack()
{
	if (attackCooldown >= attackCooldownMax) {
		attackCooldown = 0.f;
		return true;
	}
	return false;
}

const Vector2f Player::getPos() const {
	return sprite.getPosition();
}

const FloatRect Player::getBounds() const {
	return sprite.getGlobalBounds();
}
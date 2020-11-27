#include "Enemy.h"

//base class Enemy
const Vector2f Enemy::getPos() const {
	return sprite.getPosition();
}

const FloatRect Enemy::getBounds() const {
	return sprite.getGlobalBounds();
}

void Enemy::randomPositionY() {
	randomY = rand() % VideoMode::getDesktopMode().height / 2.0;
}

void Enemy::setPosition()
{
	randomPositionY();
	sprite.setPosition(VideoMode::getDesktopMode().width / 8 * 7, randomY);
}

void Enemy::setHit(int h)
{
	health -= h;
	hit += h;
}

void Enemy::setShield(bool _shield) {
	shield = _shield;
}

int Enemy::getHit() { return hit; }
int Enemy::getType() { return type; }
int Enemy::getHealth() { return health; }
bool Enemy::getShield() { return shield; }

//Meteor
Meteor::Meteor()
{
	initTexture();	
	initSprite(); 
	hit = 0;
	type = 1;
	health = 15;
	once = false;
	overRide = false;
	dx = 0;
	dy = 0;
}
Meteor::Meteor(Texture* texture){
	sprite.setTexture(*texture);
}

void Meteor::initSprite() {
	//Load a texture from file
	sprite.setTexture(texture);
	//Resize
	sprite.scale(0.5f, 0.5f);

}
void Meteor::initTexture() {
	//Set the texture to the sprite
	if (!texture.loadFromFile("Texture/Meteor_03.png")) {
		std::cout << "ERROR::ENEMY::INITTEXTURE::Could not load texture file" << std::endl;
	}
}
void Meteor::changeBossTexture(int){}
void Meteor::changeTexture(int){}

void Meteor::move()
{
	if (!overRide)
		sprite.move(-1.0, 1.0);
	else
		sprite.move(dx, dy);
}

void Meteor::updates()
{
	if (hit > 0 && health != 0) {
		texture.loadFromFile("Texture/Meteor/Meteor_2" + to_string(hit) + ".png");

	}
	if (sprite.getPosition().y > VideoMode::getDesktopMode().height / 4 * 3 - 100) {
		dx = -1.0; dy = -1.0;
		overRide = true;
	}
	else if (sprite.getPosition().y <= 5) {
		dx = -1.0; dy = 1.0;
		overRide = true;
	}
	move();
}

// Asterroid
Asteroid::Asteroid()
{
	initTexture();
	initSprite();
	sprite.setPosition(VideoMode::getDesktopMode().width / 2 + 500, VideoMode::getDesktopMode().height / 2);
	hit = 0;
	type = 2;
	health = 15;
	once = false;
	overRide = false;
	dx = 0;
	dy = 0;
}
Asteroid::Asteroid(Texture* texture){
	sprite.setTexture(*texture);
}

void Asteroid::initSprite() {
	//Load a texture from file
	sprite.setTexture(texture);
	//Resize
	sprite.scale(0.5f, 0.5f);

}
void Asteroid::initTexture() {
	//Set the texture to the sprite
	if (!texture.loadFromFile("Texture/Meteor_10.png")) {
		std::cout << "ERROR::ENEMY::INITTEXTURE::Could not load texture file" << std::endl;
	}
}

void Asteroid::changeBossTexture(int) {}
void Asteroid::changeTexture(int){}

void Asteroid::move()
{
	if (!overRide)
		sprite.move(-1.0, -1.0);
	else
		sprite.move(dx, dy);
}

void Asteroid::updates()
{
	if (hit > 0 && health != 0) {
		texture.loadFromFile("Texture/Meteor/Meteor_1" + to_string(hit) + ".png");
	}
	

	if (sprite.getPosition().y > VideoMode::getDesktopMode().height / 4 * 3 - 100) {
		dx = -1.0; dy = -1.0;
		overRide = true;
	}
	else if (sprite.getPosition().y <= 5) {
		dx = -1.0; dy = 1.0;
		overRide = true;
	}
	move();
}

// Boss1
Boss1::Boss1()
{
	initTexture();
	initSprite();
	sprite.setPosition(VideoMode::getDesktopMode().width / 2 + 500, VideoMode::getDesktopMode().height / 2);
	hit = 0;
	type = 3;
	health = 10;
	once = false;
	overRide = false;
	dx = 0;
	dy = 0;
}
Boss1::Boss1(Texture* texture){
	sprite.setTexture(*texture);
}

void Boss1::initSprite() {
	//Load a texture from file
	sprite.setTexture(texture);
	//Resize
	sprite.scale(-0.5f, 0.5f);
}

void Boss1::initTexture() {
	//Set the texture to the sprite
	if (!texture.loadFromFile("Texture/Boss/boss1_lvl_1.png")) {
		std::cout << "ERROR::ENEMY::INITTEXTURE::Could not load texture file" << std::endl;
	}
}

void Boss1::changeTexture(int){}

void Boss1::move()
{
	if (!overRide)
		sprite.move(-1.3, -1.3);
	else
		sprite.move(dx, dy);
}

void Boss1::updates()
{
	if (sprite.getPosition().y > VideoMode::getDesktopMode().height / 4 * 3 - 100) {
		dx = -1.3; dy = -1.3;
		overRide = true;
	}
	else if (sprite.getPosition().y <= 5) {
		dx = -1.3; dy = 1.3;
		overRide = true;
	}
	move();
}

void Boss1::changeBossTexture(int lvl)
{
	if (lvl > 4)lvl = 4;
	if (!texture.loadFromFile("Texture/Boss/boss1_lvl_" + to_string(lvl) + ".png")) {
		std::cout << "ERROR::ENEMY::INITTEXTURE::Could not load texture file" << std::endl;
	}

}

//Boss2 - Shield
Boss2::Boss2()
{
	initTexture();
	initSprite();
	sprite.setPosition(VideoMode::getDesktopMode().width / 2 + 500, VideoMode::getDesktopMode().height / 2);
	hit = 0;
	type = 4;
	health = 10;
	once = false;
	overRide = false;
	shield = false;
}

Boss2::Boss2(Texture* texture){
	sprite.setTexture(*texture);
}

void Boss2::initSprite()
{
	//Load a texture from file
	sprite.setTexture(texture);
	//Resize
	sprite.scale(-0.5f, 0.5f);
}

void Boss2::initTexture()
{
	//Set the texture to the sprite
	if (!texture.loadFromFile("Texture/Boss/boss2_lvl_1.png")) {
		std::cout << "ERROR::ENEMY::INITTEXTURE::Could not load texture file" << std::endl;
	}
}

void Boss2::changeTexture(int lvl)
{
	if (lvl > 4)lvl = 4;

	if (!texture.loadFromFile("Texture/Boss/shield_boss_2_"+ to_string(lvl) +".png")) {
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file" << std::endl;
	}	
}

void Boss2::move(){
	sprite.move(-1.0, 0.0);
}

void Boss2::updates(){
	move();
}

void Boss2::changeBossTexture(int lvl)
{
	if (lvl > 4)lvl = 4;
	if (!texture.loadFromFile("Texture/Boss/boss2_lvl_" + to_string(lvl) + ".png")) {
		std::cout << "ERROR::ENEMY::INITTEXTURE::Could not load texture file" << std::endl;
	}
}

//Boss3

Boss3::Boss3()
{
	initTexture();
	initSprite();
	sprite.setPosition(VideoMode::getDesktopMode().width / 2 + 500, VideoMode::getDesktopMode().height / 2);
	hit = 0;
	type = 5;
	health = 10;
	once = false;
	overRide = false;
	shield = false;
	dx = 0;
	dy = 0;
}

Boss3::Boss3(Texture* texture){
	sprite.setTexture(*texture);
}

void Boss3::initSprite()
{
	//Load a texture from file
	sprite.setTexture(texture);
	//Resize
	sprite.scale(-0.5f, 0.5f);
}

void Boss3::initTexture()
{
	//Set the texture to the sprite
	if (!texture.loadFromFile("Texture/Boss/boss3_lvl_1.png")) {
		std::cout << "ERROR::ENEMY::INITTEXTURE::Could not load texture file" << std::endl;
	}
}

void Boss3::changeTexture(int lvl)
{
	if (lvl > 4)lvl = 4;

	if (!texture.loadFromFile("Texture/Boss/shield_boss_3_"+ to_string(lvl) + ".png")) {
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file" << std::endl;
	}
	
}

void Boss3::move()
{
	if (!overRide)
		sprite.move(-1.0, -2.0);
	else
		sprite.move(dx, dy);
}

void Boss3::updates()
{
	if (sprite.getPosition().y > VideoMode::getDesktopMode().height / 4 * 3 - 100) {
		dx = -1.0; dy = -2.0;
		overRide = true;
	}
	else if (sprite.getPosition().y <= 5) {
		dx = -1.0; dy = 2.0;
		overRide = true;
	}
	move();
}

void Boss3::changeBossTexture(int lvl)
{
	if (lvl > 4)lvl = 4;
	if (!texture.loadFromFile("Texture/Boss/boss3_lvl_" + to_string(lvl) + ".png")) {
		std::cout << "ERROR::ENEMY::INITTEXTURE::Could not load texture file" << std::endl;
	}
}
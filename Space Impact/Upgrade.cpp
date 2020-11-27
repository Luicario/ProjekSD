#include "Upgrade.h"

//upgrade (Base class)

void Upgrade::setPosition(float x, float y){
	sprite.setPosition(x, y);
}

void Upgrade::render(RenderTarget& target) {
	target.draw(sprite);
}

const Vector2f Upgrade::getPos() const {
	return sprite.getPosition();
}

const FloatRect Upgrade::getBounds() const {
	return sprite.getGlobalBounds();
}

//upgrade ship
Upship::Upship()
{
	initTexture();
	initSprite();
}

void Upship::initSprite()
{
	sprite.setTexture(texture);
	sprite.scale(0.055f, 0.055f);
}

void Upship::initTexture()
{
	if (!texture.loadFromFile("Texture/Button/ship_upgrade.png")) {
		cout << "CANT OPEN TEXTURE UPGRADE\n";
	}
}

void Upship::changetexture(int lvl) {
	if (lvl >= 4) {
		//Set the texture to the sprite
		if (!texture.loadFromFile("Texture/Button/ship_upgrade1.png")) {
			cout << "CANT OPEN TEXTURE UPGRADE\n";
		}
	}
}

//upgrade damage
Updamage::Updamage()
{
	initTexture();
	initSprite();
}

void Updamage::initSprite()
{
	sprite.setTexture(texture);
	sprite.scale(0.057f, 0.057f);
}

void Updamage::initTexture()
{
	if (!texture.loadFromFile("Texture/Button/laser_upgrade.png")) {
		cout << "CANT OPEN TEXTURE UPGRADE\n";
	}
}

void Updamage::changetexture(int lvl) {
	if (lvl >= 6) {
		//Set the texture to the sprite
		if (!texture.loadFromFile("Texture/Button/laser_upgrade1.png")) {
			cout << "CANT OPEN TEXTURE UPGRADE\n";
		}
	}
}

FireRate::FireRate()
{
	initTexture();
	initSprite();
}

void FireRate::initSprite()
{
	sprite.setTexture(texture);
	sprite.scale(0.057f, 0.057f);
}

void FireRate::initTexture()
{
	if (!texture.loadFromFile("Texture/Button/laser_firerate_upgrade.png")) {
		cout << "CANT OPEN TEXTURE UPGRADE\n";
	}
}

void FireRate::changetexture(int lvl)
{
	if (lvl == 25) {
		//Set the texture to the sprite
		if (!texture.loadFromFile("Texture/Button/laser_firerate_upgrade1.png")) {
			cout << "CANT OPEN TEXTURE UPGRADE\n";
		}
	}
}

HealthBar::HealthBar()
{
	initTexture();
	initSprite();
}

void HealthBar::initSprite()
{
	sprite.setTexture(texture);
	sprite.scale(1.5f, 1.0f);
}

void HealthBar::initTexture()
{
	if (!texture.loadFromFile("Texture/HP Player/hp player30.png")) {
		cout << "CANT OPEN TEXTURE UPGRADE\n";
	}
}

void HealthBar::changetexture(int lvl)
{
	if (!texture.loadFromFile("Texture/HP Player/hp player" + to_string(lvl)  +".png")) {
		cout << "CANT OPEN TEXTURE UPGRADE\n";
	}
}

EnemyHealthBar::EnemyHealthBar()
{
	initTexture();
	initSprite();
}

void EnemyHealthBar::initSprite()
{
	sprite.setTexture(texture);
	sprite.scale(-1.0f, 1.0f);
}

void EnemyHealthBar::initTexture()
{
	if (!texture.loadFromFile("Texture/Enemy/hp enemy30.png")) {
		cout << "CANT OPEN TEXTURE UPGRADE\n";
	}
}

void EnemyHealthBar::changetexture(int lvl)
{
	
		if (!texture.loadFromFile("Texture/Enemy/hp enemy" + to_string(lvl) + ".png")) {
			cout << "CANT OPEN TEXTURE UPGRADE\n";
		}
	

}

Repair::Repair()
{
	initTexture();
	initSprite();
}

void Repair::initSprite()
{
	sprite.setTexture(texture);
	sprite.scale(0.07f, 0.07f);
}

void Repair::initTexture()
{
	if (!texture.loadFromFile("Texture/Button/repair_ship.png")) {
		cout << "CANT OPEN TEXTURE UPGRADE\n";
	}
}
void Repair::changetexture(int i){}


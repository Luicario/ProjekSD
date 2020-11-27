#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<string>
using namespace sf;
using namespace std;

//base class and abstract class
class Enemy {
protected:
	Sprite sprite;
	Texture texture;
	int hit,type, health;
	bool once,overRide;
	float randomY, dx, dy;
	bool shield;
public:

	const Vector2f getPos() const;
	const FloatRect getBounds() const;

	void randomPositionY();
	void setPosition();
	
	void setHit(int h);
	void setShield(bool _shield);

	int getHit();	
	int getType();
	int getHealth();
	bool getShield();

	virtual void initSprite()=0;
	virtual void initTexture() = 0;
	virtual void render(RenderTarget& target) = 0;
	virtual void move() = 0;
	virtual void updates() = 0;	
	virtual void changeTexture(int) = 0;
	virtual void changeBossTexture(int) = 0;	
};

class Meteor : public Enemy{
public:
	Meteor();
	Meteor(Texture* texture);
	virtual ~Meteor() {

	}
	void initSprite();
	void initTexture();
	void render(RenderTarget& target) {	
		target.draw(sprite);
	}
	void changeTexture(int);
	void move();
	void updates();
	void changeBossTexture(int);
	
};

class Asteroid : public Enemy {
public:
	Asteroid();
	Asteroid(Texture* texture);
	virtual ~Asteroid() {

	}
	void initSprite();
	void initTexture();
	void render(RenderTarget& target) {		
		target.draw(sprite);
	}
	void changeTexture(int);
	void move();
	void updates();
	void changeBossTexture(int);
}; 

class Boss1 : public Enemy {
public:
	Boss1();
	Boss1(Texture* texture);
	virtual ~Boss1() {

	}
	void initSprite();
	void initTexture();
	void render(RenderTarget& target) {
		target.draw(sprite);
	}
	void changeTexture(int);
	void move();
	void updates();
	void changeBossTexture(int);
};
class Boss2 : public Enemy {
public:
	Boss2();
	Boss2(Texture* texture);
	virtual ~Boss2() {

	}
	void initSprite();
	void initTexture();
	void render(RenderTarget& target) {
		target.draw(sprite);
	}
	void changeTexture(int);
	void move();
	void updates();
	void changeBossTexture(int);
};
class Boss3 : public Enemy {
public:
	Boss3();
	Boss3(Texture* texture);
	virtual ~Boss3() {

	}
	void initSprite();
	void initTexture();
	void render(RenderTarget& target) {
		target.draw(sprite);
	}
	void changeTexture(int);
	void move();
	void updates();
	void changeBossTexture(int);
};
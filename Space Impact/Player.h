#include<iostream>
#include <SFML/Graphics.hpp>
#include<string>
using namespace sf;

class Player {
private:
	Sprite sprite;
	Texture texture;
	float movementspeed;
	float attackCooldown;
	float attackCooldownMax;
	int hit,health;
	bool dead;
public:
	Player();
	void initSprite();
	void initTexture();
	void initCooldown();
	void changeTexture(int lvl);

	void setStatus(bool _dead);
	void setHealth(int h);
	void setHit(int h);

	void move(const float dirX, const float dirY);
	void render(RenderTarget& target);
	void updateAttack();
	void increaseFireRate();
	void addHealth(int h);
	void update();

	int getHealth();
	int getHit();
	bool getStatus();
	const bool canAttack();

	const Vector2f getPos() const; //posisi x dan y
	const FloatRect getBounds() const; //ambil bagian terluar

	virtual ~Player() {}	
};

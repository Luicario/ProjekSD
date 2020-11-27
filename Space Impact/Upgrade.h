#include<SFML/Graphics.hpp>
#include<iostream>
using namespace std;
using namespace sf;
class Upgrade
{
protected:
	Sprite sprite;
	Texture texture;
	
public:	
	void setPosition(float x, float y);
	void render(RenderTarget& target);

	const Vector2f getPos() const;
	const FloatRect getBounds() const;

	virtual void initSprite() = 0;
	virtual void initTexture() = 0;
	virtual void changetexture(int i) = 0;
};

class Upship :public Upgrade {
public:
	Upship();
	void initSprite();
	void initTexture();
	void changetexture(int i);
};

class Updamage :public Upgrade {
public:
	Updamage();
	void initSprite();
	void initTexture();
	void changetexture(int i);
};
class FireRate :public Upgrade {
public:
	FireRate();
	void initSprite();
	void initTexture();
	void changetexture(int i);
};
class HealthBar : public Upgrade {
public:
	HealthBar();
	void initSprite();
	void initTexture();
	void changetexture(int i);
};
class EnemyHealthBar : public Upgrade {
public:
	EnemyHealthBar();
	void initSprite();
	void initTexture();
	void changetexture(int i);
};
class Repair : public Upgrade {
public:
	Repair();
	void initSprite();
	void initTexture();
	void changetexture(int i);
};
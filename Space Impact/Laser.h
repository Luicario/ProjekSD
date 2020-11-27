#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
using namespace sf;
class Laser {
private:
	Sprite shape;
	Vector2f direction;
	float movementSpeed;
public:
	Laser();
	Laser(Texture* texture, float pos_x, float pos_y, float _dirX, float _dirY, float _movementSpeed);
	
	//Accessor
	const FloatRect getBounds() const;
	const Vector2f getPos() const;
	void update();
	void render(RenderTarget* target);
	virtual ~Laser() {}	
};

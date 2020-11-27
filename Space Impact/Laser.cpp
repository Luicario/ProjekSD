#include "Laser.h"

Laser::Laser(){}

Laser::Laser(Texture* texture, float pos_x, float pos_y, float _dirX, float _dirY, float _movementSpeed) {
	shape.setTexture(*texture);
	shape.setPosition(pos_x, pos_y);
	direction.x = _dirX;
	direction.y = _dirY;
	movementSpeed = _movementSpeed;
}

const FloatRect Laser::getBounds() const {
	return shape.getGlobalBounds();
}

const Vector2f Laser::getPos() const {
	return shape.getPosition();
}

void Laser::update(){
	//movement
	shape.move(movementSpeed * direction);
}

void Laser::render(RenderTarget* target){
	target->draw(shape);
}
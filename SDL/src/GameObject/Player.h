#pragma once
#include "ResourceManagers.h"
#include "SpriteAnimation.h"
#include "Sprite2D.h"

class Player: public SpriteAnimation {
public:
	Player(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) :
		SpriteAnimation(texture, spriteRow, frameCount, numAction, frameTime), m_isCollision(false), m_v(4.0f) {};
	~Player();

	void MoveUp();
	void MoveDown();
	void Flash();
	bool checkCollision();
	void setV(float m_v);
	float getV();

private:
	float m_v;
	bool m_isCollision;
};


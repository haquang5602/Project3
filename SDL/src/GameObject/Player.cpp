#include "Player.h"

Player::~Player()
{

}

void Player::setV(float v)
{ 
	m_v = v;
}

float Player::getV()
{
	return m_v;
}

void Player::MoveUp()
{
	this->SetRotation(-40);
	this->Set2DPosition(m_position.x, m_position.y - m_v);
}

void Player::MoveDown()
{
	this->SetRotation(40);
	this->Set2DPosition(m_position.x, m_position.y + m_v);
}

void Player::Flash()
{
	auto texture = ResourceManagers::GetInstance()->GetTexture("flash1.png");
	this->SetTexture(texture);
	this->SetSize(50, 44);
	//this->SetRotation(0);
	//this->Set2DPosition(m_position.x, m_position.y);
}

bool Player::checkCollision() {
	return false;
}

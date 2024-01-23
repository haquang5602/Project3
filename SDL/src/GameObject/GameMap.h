#pragma once
#include "Define.h"
#include "Sprite2D.h"
#include "SpriteAnimation.h"
#include "Sound.h"
#include "Map.h"
#include "Player.h"
#include "MouseButton.h"
#include "GameStateMachine.h"
#include "GameManager/ResourceManagers.h"

class GameMap {
public:
	GameMap(std::string backgroud, std::string map1, std::string dataMap1, std::string map2, std::string dataMap2, std::string sound);
	~GameMap();

	void Init(std::string backgroud, std::string map1, std::string dataMap1, std::string map2, std::string dataMap2, std::string sound);
	void Update(float deltaTime);
	void Draw(SDL_Renderer* renderer);
	void HandleEvent();
	void CheckCollision();
	void HandleColision();
	void Restart();
	void Pause();
	void Resume();
	void WinMap();
	void HandleKeyEvents(SDL_Event& e);
	void HandleTouchEvents(SDL_Event& e);

private:
	std::shared_ptr<Sprite2D>	m_background;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::shared_ptr<Player> obj;
	std::shared_ptr<MouseButton> m_btnPause;
	std::shared_ptr<MouseButton> m_btnResume;
	std::shared_ptr<MouseButton> m_btnReplay;
	std::shared_ptr<MouseButton> m_btnHome;
	std::shared_ptr<Sprite2D>	m_map1;
	std::shared_ptr<Sprite2D>	m_map2;
	std::shared_ptr<Sprite2D>	m_win_map;
	std::shared_ptr<Sprite2D>	m_explosion;
	std::shared_ptr<Map>		m_map1_data;
	std::shared_ptr<Map>		m_map2_data;
	std::shared_ptr<Sound>		m_Sound;
	std::shared_ptr<Sound>		m_explosionSfx;
	std::shared_ptr<Sound>		m_clickSfx;
	std::shared_ptr<Sound>		m_flashSfx;

	bool isMoveUp = true;
	bool isPause = false;
	bool isCollision = false;
	bool isWinMap = false;
	bool setMusic = true;
	bool isFlash = false;
	float timeFlash = 0.0f;
	bool usedFlash = false;
	float time = 0.0f;

};
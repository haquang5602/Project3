#include "GSPlay.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Player.h"
#include "GameObject/Camera.h"
#include "KeyState.h"

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_map.png");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	texture = ResourceManagers::GetInstance()->GetTexture("map1.png");
	std::shared_ptr<MouseButton> map1 = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	map1->SetSize(120, 120);
	map1->Set2DPosition((SCREEN_WIDTH - map1->GetWidth())/2 - 130, 200);
	map1->SetOnClick([this]() {
		m_gamePlay = std::make_shared<GameMap>("bg_play1.jpg", "Map/map1_1.png", "Map/map1_1.txt", "Map/map1_2.png", "Map/map1_2.txt", "Game_play1.wav");
		isPlay = true;
		});
	m_listButton.push_back(map1);

	texture = ResourceManagers::GetInstance()->GetTexture("map2.png");
	std::shared_ptr<MouseButton> map2 = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	map2->SetSize(120, 120);
	map2->Set2DPosition((SCREEN_WIDTH - map1->GetWidth()) / 2 + 100, 200);
	map2->SetOnClick([this]() {
		m_gamePlay = std::make_shared<GameMap>("bg_play2.jpg", "Map/map2_1.png", "Map/map2_1.txt", "Map/map2_2.png", "Map/map2_2.txt", "Game_play2.wav");
		isPlay = true;
		});
	m_listButton.push_back(map2);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.png");
	m_btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnClose->SetSize(45, 45);
	m_btnClose->Set2DPosition(SCREEN_WIDTH - 55, 10);
	m_btnClose->SetOnClick([this]() {
		if (isPlay) {
			isPlay = false;
			m_gamePlay = nullptr;
		}
		else {
			GameStateMachine::GetInstance()->PopState();
		}
		});
}

void GSPlay::Exit()
{
}


void GSPlay::Pause()
{
}
void GSPlay::Resume()
{
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(SDL_Event& e)
{
	if (isPlay) {
		m_gamePlay->HandleKeyEvents(e);
	}
}

void GSPlay::HandleTouchEvents(SDL_Event& e)
{
	m_btnClose->HandleTouchEvent(&e);
	if (isPlay) {
		m_gamePlay->HandleTouchEvents(e);
	}
	else {
		for (auto button : m_listButton)
		{
			if (button->HandleTouchEvent(&e))
			{
				break;
			}
		}
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
{
	m_btnClose->Update(deltaTime);
	if (isPlay) {
		m_gamePlay->Update(deltaTime);
	}
	else {
		for (auto it : m_listButton)
		{
			it->Update(deltaTime);
		}
	}
}

void GSPlay::Draw(SDL_Renderer* renderer)
{
	if (isPlay) {
		m_gamePlay->Draw(renderer);
		m_btnClose->Draw(renderer);
	}
	else {
		m_background->Draw(renderer);
		m_btnClose->Draw(renderer);
		for (auto it : m_listButton)
		{
			it->Draw(renderer);
		}
	}
}
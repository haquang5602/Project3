#include "GameMap.h"

GameMap::GameMap(std::string backgroud, std::string map1, std::string dataMap1, std::string map2, std::string dataMap2, std::string sound)
{
	Init(backgroud, map1, dataMap1, map2, dataMap2, sound);
}

GameMap::~GameMap()
{
}

void GameMap::Init(std::string backgroud, std::string map1, std::string dataMap1, std::string map2, std::string dataMap2, std::string sound)
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture(backgroud);

	// background
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	//setmusic
	texture = ResourceManagers::GetInstance()->GetTexture("resumesound.png");
	std::shared_ptr<MouseButton> btnSetting = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnSetting->SetSize(60, 60);
	btnSetting->Set2DPosition((SCREEN_WIDTH - btnSetting->GetWidth()) - 20, (SCREEN_HEIDHT - btnSetting->GetHeight()) - 20);
	btnSetting->SetOnClick([=]() {
		if (!isPause) {
			if (isMoveUp) {
				isMoveUp = false;
			}
			else {
				isMoveUp = true;
			}
		}
		setMusic = !setMusic;
		if (setMusic) {
			btnSetting->SetTexture(ResourceManagers::GetInstance()->GetTexture("resumesound.png"));
			m_Sound->ResumeSound();
		}
		else {
			btnSetting->SetTexture(ResourceManagers::GetInstance()->GetTexture("pausesound.png"));
			m_Sound->PauseSound();
		}
		});
	m_listButton.push_back(btnSetting);

	// map1
	texture = ResourceManagers::GetInstance()->GetTexture(map1);
	m_map1 = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_map1->SetSize(8000, 576);
	m_map1->Set2DPosition(0, 0);
	// load data map1
	std::string fileDataMap1 = ResourceManagers::GetInstance()->GetFileDataMap(dataMap1);
	m_map1_data = std::make_shared<Map>(fileDataMap1);

	// map2
	texture = texture = ResourceManagers::GetInstance()->GetTexture(map2);
	m_map2 = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_map2->SetSize(8000, 576);
	m_map2->Set2DPosition(8000, 0);
	// load data map2
	std::string fileDataMap2 = ResourceManagers::GetInstance()->GetFileDataMap(dataMap2);
	m_map2_data = std::make_shared<Map>(fileDataMap2);

	// button pause
	texture = ResourceManagers::GetInstance()->GetTexture("btn_pause.png");
	m_btnPause = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnPause->SetSize(45, 45);
	m_btnPause->Set2DPosition(SCREEN_WIDTH - 110, 10);
	m_btnPause->SetOnClick([this]() {
		Pause();
		});

	// Animation 
	texture = ResourceManagers::GetInstance()->GetTexture("spaceship1.png");
	obj = std::make_shared<Player>(texture, 1, 15, 1, 0.048f);
	obj->SetFlip(SDL_FLIP_NONE);
	obj->SetSize(50, 42);
	obj->Set2DPosition(-50, 320);
	//Camera::GetInstance()->SetTarget(obj);
	m_listAnimation.push_back(obj);

	// btn_Resume
	texture = ResourceManagers::GetInstance()->GetTexture("btn_play2.png");
	m_btnResume = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnResume->SetSize(90, 90);
	m_btnResume->Set2DPosition((SCREEN_WIDTH - m_btnResume->GetWidth()) / 2, (SCREEN_HEIDHT - m_btnResume->GetHeight()) / 2);
	m_btnResume->SetOnClick([this]() {
		Resume();
		});
	// png win
	texture = ResourceManagers::GetInstance()->GetTexture("win_map.png");
	m_win_map = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_win_map->SetSize(300, 201);
	m_win_map->Set2DPosition((SCREEN_WIDTH - m_win_map->GetWidth()) / 2, (SCREEN_HEIDHT - m_win_map->GetHeight()) / 2 - 50);
	
	texture = ResourceManagers::GetInstance()->GetTexture("btn_return.png");
	m_btnReplay = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnReplay->SetSize(45, 45);
	m_btnReplay->Set2DPosition(450, 290);
	m_btnReplay->SetOnClick([this]() {
		Restart();
		if(setMusic) m_Sound->PlaySound();
		isWinMap = false;
		});
	texture = ResourceManagers::GetInstance()->GetTexture("btn_home.png");
	m_btnHome = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_btnHome->SetSize(45, 45);
	m_btnHome->Set2DPosition(520, 290);
	m_btnHome->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});

	// sound game
	m_Sound = std::make_shared<Sound>();
	m_Sound->LoadSound("Data/Sounds/" + sound);
	m_Sound->PlaySound();

	m_explosionSfx = std::make_shared<Sound>();
	m_explosionSfx->LoadSfx("Data/Sounds/explosion.wav");

	m_clickSfx = std::make_shared<Sound>();
	m_clickSfx->LoadSfx("Data/Sounds/left_click.wav");

	m_flashSfx = std::make_shared<Sound>();
	m_flashSfx->LoadSfx("Data/Sounds/flash.mp3");
}

void GameMap::HandleEvent() {
	if ((m_map2->Get2DPosition().x + m_map2->GetWidth()) < 0)
	{
		WinMap();
		printf("win game");
	}

	m_map1->Set2DPosition(m_map1->Get2DPosition().x - 5, 0);
	m_map2->Set2DPosition(m_map2->Get2DPosition().x - 5, 0);
	if (isMoveUp)
	{
		obj->MoveUp();
		if (256 - m_map1->Get2DPosition().x <= (8000 - 256))
		{
			if ((m_map1_data->checkCollison(obj->Get2DPosition().y + 8, 256 - m_map1->Get2DPosition().x))
				|| (m_map1_data->checkCollison(obj->Get2DPosition().y + 40, 256 + 12 - m_map1->Get2DPosition().x))
				|| (m_map1_data->checkCollison(obj->Get2DPosition().y + 8, 256 + 24 - m_map1->Get2DPosition().x)))
			{	
				if(setMusic) m_explosionSfx->PlaySfx(0, 0);
				HandleColision();
				obj->Set2DPosition(obj->Get2DPosition().x - 20, obj->Get2DPosition().y - 30);
			}
		}
		if (256 - m_map2->Get2DPosition().x <= (8000 - 256))
		{
			if ((m_map2_data->checkCollison(obj->Get2DPosition().y + 8, 256 - m_map2->Get2DPosition().x))
				|| (m_map1_data->checkCollison(obj->Get2DPosition().y + 40, 256 + 12 - m_map1->Get2DPosition().x))
				|| (m_map2_data->checkCollison(obj->Get2DPosition().y + 8, 256 + 24 - m_map2->Get2DPosition().x)))
			{
				if (setMusic) m_explosionSfx->PlaySfx(0, 0);
				HandleColision();
				obj->Set2DPosition(obj->Get2DPosition().x - 20, obj->Get2DPosition().y - 30);
			}
		}

	}
	else
	{
		obj->MoveDown();
		if (256 - m_map1->Get2DPosition().x <= (8000 + 256))
		{
			if ((m_map1_data->checkCollison(obj->Get2DPosition().y + 4, 256 + 12 - m_map1->Get2DPosition().x))
				|| (m_map1_data->checkCollison(obj->Get2DPosition().y + 32, 256 - m_map1->Get2DPosition().x))
				|| (m_map1_data->checkCollison(obj->Get2DPosition().y + 28, 256 + 24 - m_map1->Get2DPosition().x)))
			{
				if (setMusic) m_explosionSfx->PlaySfx(0, 0);
				HandleColision();
				obj->Set2DPosition(obj->Get2DPosition().x - 40, obj->Get2DPosition().y - 40);
			}
		}
		if (256 - m_map2->Get2DPosition().x <= (8000 + 256))
		{
			if ((m_map2_data->checkCollison(obj->Get2DPosition().y + 4, 256 + 12 - m_map2->Get2DPosition().x))
				|| (m_map1_data->checkCollison(obj->Get2DPosition().y + 32, 256 - m_map1->Get2DPosition().x))
				|| (m_map2_data->checkCollison(obj->Get2DPosition().y + 28, 256 + 24 - m_map2->Get2DPosition().x)))
			{
				if (setMusic) m_explosionSfx->PlaySfx(0, 0);
				HandleColision();
				obj->Set2DPosition(obj->Get2DPosition().x - 40, obj->Get2DPosition().y - 40);
			}
		}
	}
}

void GameMap::CheckCollision()
{
}

void GameMap::HandleColision()
{
	isCollision = true;
	auto texture = ResourceManagers::GetInstance()->GetTexture("explosion1.png");
	obj->SetTexture(texture);
	obj->SetSize(100, 100);
	obj->SetRotation(0);
	m_Sound->StopSound();
}

void GameMap::Restart()
{	
	if (setMusic) {
		m_Sound->PlaySound();
	}
	auto texture = ResourceManagers::GetInstance()->GetTexture("spaceship1.png");
	obj->SetTexture(texture);
	obj->SetRotation(0);
	obj->SetSize(50, 42);
	obj->Set2DPosition(100, 320);
	m_map1->Set2DPosition(0, 0);
	m_map2->Set2DPosition(8000, 0);
	usedFlash = false;
}

void GameMap::Pause()
{
	isPause = true;
	m_Sound->PauseSound();
	if (isMoveUp) {
		isMoveUp = false;
	}
	else {
		isMoveUp = true;
	}
}

void GameMap::Resume()
{
	isPause = false;
	if (setMusic) {
		m_Sound->ResumeSound();
	}
}

void GameMap::WinMap()
{
	isWinMap = true;
	obj->SetRotation(0);
	obj->Set2DPosition(obj->Get2DPosition().x, obj->Get2DPosition().y);
}

void GameMap::HandleKeyEvents(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			if (setMusic) m_clickSfx->PlaySfx(0, 0);
			if (isMoveUp) {
				isMoveUp = false;
			}
			else {
				isMoveUp = true;
			}
			break;
		default:
			break;
		}
	}
	if (e.type == SDL_MOUSEBUTTONUP) {
		if (e.button.button == SDL_BUTTON_LEFT) {		
			if (setMusic) m_clickSfx->PlaySfx(0, 0);
			if (!isPause && !isWinMap) {
				if (isMoveUp) {
					isMoveUp = false;
				}
				else {
					isMoveUp = true;
				}
			}
		}
		else {
			if (!usedFlash) {
				m_flashSfx->PlaySfx(0,0);
				if(!isCollision) obj->Flash();
				isFlash = true;
				usedFlash = true;
			}
		}
	}
}

void GameMap::HandleTouchEvents(SDL_Event& e)
{
	if (isPause) {
		m_btnResume->HandleTouchEvent(&e);
	}
	else if (isWinMap) 
	{
		m_btnReplay->HandleTouchEvent(&e);
		m_btnHome->HandleTouchEvent(&e);
	}
	else {
		m_btnPause->HandleTouchEvent(&e);
	}
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GameMap::Update(float deltaTime)
{
	obj->Update(deltaTime);
	if (isCollision) {
		time += deltaTime;
		if (time > 1.5f) {
			isCollision = false;
			time = 0;
		}
		if (!isCollision) Restart();
	}
	else {
		if (!isPause && !isWinMap) {
			if (obj->Get2DPosition().x < 240) {
				isMoveUp = true;
				isFlash = false;
				obj->Set2DPosition(obj->Get2DPosition().x + 6, 350);
			}
			else {
				if (isFlash) {
					obj->SetRotation(0);
					obj->Set2DPosition(obj->Get2DPosition().x, obj->Get2DPosition().y);
					m_map1->Set2DPosition(m_map1->Get2DPosition().x - 13, 0);
					m_map2->Set2DPosition(m_map2->Get2DPosition().x - 13, 0);
					if (256 - m_map1->Get2DPosition().x <= (8000 + 256))
					{
						if ((m_map1_data->checkCollison(obj->Get2DPosition().y, 256 - m_map1->Get2DPosition().x))
							|| (m_map1_data->checkCollison(obj->Get2DPosition().y + 40, 256 - m_map1->Get2DPosition().x))
							|| (m_map1_data->checkCollison(obj->Get2DPosition().y + 20, 256 + 50 - m_map1->Get2DPosition().x)))
						{
							if (setMusic) m_explosionSfx->PlaySfx(0, 0);
							HandleColision();
							obj->Set2DPosition(obj->Get2DPosition().x - 25, obj->Get2DPosition().y - 19);
						}
					}
					if (256 - m_map2->Get2DPosition().x <= (8000 + 256))
					{
						if ((m_map2_data->checkCollison(obj->Get2DPosition().y, 256 - m_map2->Get2DPosition().x))
							|| (m_map1_data->checkCollison(obj->Get2DPosition().y + 40, 256 - m_map1->Get2DPosition().x))
							|| (m_map2_data->checkCollison(obj->Get2DPosition().y + 20, 256 + 50 - m_map2->Get2DPosition().x)))
						{
							if (setMusic) m_explosionSfx->PlaySfx(0, 0);
							HandleColision();
							obj->Set2DPosition(obj->Get2DPosition().x -25, obj->Get2DPosition().y -19);
						}
					}
					timeFlash += deltaTime;
					if (timeFlash > 0.8f) {
						isFlash = false;
						timeFlash = 0;
						auto texture = ResourceManagers::GetInstance()->GetTexture("spaceship1.png");
						obj->SetTexture(texture);
						obj->SetSize(50, 42);
						if (isMoveUp) obj->MoveUp();
						else obj->MoveDown();
					}
				} else {
					HandleEvent();
				}
			}
		}
	}
}

void GameMap::Draw(SDL_Renderer* renderer)
{	
	m_background->Draw(renderer);
	m_map1->Draw(renderer);
	m_map2->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	for (auto it : m_listAnimation)
	{
		it->Draw(renderer);
	}
	if (isPause)
	{
		m_btnResume->Draw(renderer);
	}
	else if (isWinMap)
	{
		m_win_map->Draw(renderer);
		m_btnReplay->Draw(renderer);
		m_btnHome->Draw(renderer);
	}
	else {
		m_btnPause->Draw(renderer);
	}
}

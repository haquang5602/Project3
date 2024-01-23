#include "GSMenu.h"

GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textGameName(nullptr)
{
}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_menu.png");

	// background
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_play.tga");
	std::shared_ptr<MouseButton> btnPlay = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);

	btnPlay->SetSize(220, 60);
	btnPlay->Set2DPosition((SCREEN_WIDTH - btnPlay->GetWidth()) / 2, (SCREEN_HEIDHT - btnPlay->GetHeight()) / 2);
	btnPlay->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(btnPlay);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_exit.tga");
	std::shared_ptr<MouseButton> btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//btnClose = std::make_shared<MouseButton>(texture);
	btnClose->SetSize(220, 60);
	btnClose->Set2DPosition((SCREEN_WIDTH - btnClose->GetWidth()) / 2, (SCREEN_HEIDHT - btnClose->GetHeight()) / 2 + 160);
	btnClose->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(btnClose);
	
	texture = ResourceManagers::GetInstance()->GetTexture("btn_help.tga");
	btnHelp = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnHelp->SetSize(220, 60);
	btnHelp->Set2DPosition((SCREEN_WIDTH - btnHelp->GetWidth()) / 2, (SCREEN_HEIDHT - btnHelp->GetHeight()) / 2 + 80 );
	btnHelp->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_HELP);
		});
	m_listButton.push_back(btnHelp);

	// game title
	///Set Font
	//m_textColor = { 255, 255, 0 };
	//m_textGameName = std::make_shared<Text>("Data/lazy.ttf", m_textColor);
	//m_textGameName->SetSize(300, 50);
	//m_textGameName->Set2DPosition((SCREEN_WIDTH - m_textGameName->GetWidth())/2, SCREEN_HEIDHT / 2 - 300);
	//m_textGameName->LoadFromRenderText("Your Game");
	
	m_Sound = std::make_shared<Sound>();
	m_Sound->LoadSound("Data/Sounds/Game_menu.wav");
	if (playMusic == 1) {
		m_Sound->PlaySound();
	}

	texture = ResourceManagers::GetInstance()->GetTexture("resumesound.png");
	std::shared_ptr<MouseButton> btnSetting = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnSetting->SetSize(60, 60);
	btnSetting->Set2DPosition((SCREEN_WIDTH - btnSetting->GetWidth()) - 50, (SCREEN_HEIDHT - btnSetting->GetHeight()) - 50);
	btnSetting->SetOnClick([=]() {
		playMusic = -playMusic;
		if (playMusic == 1) {
			btnSetting->SetTexture(ResourceManagers::GetInstance()->GetTexture("resumesound.png"));
			m_Sound->PlaySound();
		}
		else {
			btnSetting->SetTexture(ResourceManagers::GetInstance()->GetTexture("pausesound.png"));
			m_Sound->StopSound();
		}
		});
	m_listButton.push_back(btnSetting);
	
}

void GSMenu::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSMenu::Pause()
{
	m_Sound->StopSound();
	// button close
	
}

void GSMenu::Resume()
{
	m_Sound->PlaySound();
}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(SDL_Event& e)
{
}

void GSMenu::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button ->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSMenu::HandleMouseMoveEvents(int x, int y)
{
}

void GSMenu::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	
	//m_textGameName->Draw(renderer);
}

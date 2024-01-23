#include "GSSetting.h"

GSSetting::GSSetting() : GameStateBase(StateType::STATE_SETTING),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textGameName(nullptr)
{
}

GSSetting::~GSSetting()
{
}

void GSSetting::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play1.jpg");

	// background
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// button
	texture = ResourceManagers::GetInstance()->GetTexture("setmusic.png");
	std::shared_ptr<MouseButton> btnmenumusic = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);

	btnmenumusic->SetSize(60, 60);
	btnmenumusic->Set2DPosition((SCREEN_WIDTH - btnmenumusic->GetWidth()) / 2, (SCREEN_HEIDHT - btnmenumusic->GetHeight()) / 2 );
	btnmenumusic->SetOnClick([]() {
		
		});
	m_listButton.push_back(btnmenumusic);

	// button
	texture = ResourceManagers::GetInstance()->GetTexture("setmusic.png");
	std::shared_ptr<MouseButton> btnplaymusic = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);

	btnplaymusic->SetSize(60, 60);
	btnplaymusic->Set2DPosition((SCREEN_WIDTH - btnplaymusic->GetWidth()) / 2, (SCREEN_HEIDHT - btnplaymusic->GetHeight()) / 2 + 100 );
	btnplaymusic->SetOnClick([]() {
		
		});
	m_listButton.push_back(btnplaymusic);

	texture = ResourceManagers::GetInstance()->GetTexture("btn_return.png");
	m_button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_button->SetSize(60, 60);
	m_button->Set2DPosition(900, 25);
	m_button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
}

void GSSetting::Exit()
{
}

void GSSetting::Pause()
{
}

void GSSetting::Resume()
{
}

void GSSetting::HandleEvents()
{
}

void GSSetting::HandleKeyEvents(SDL_Event& e)
{
}

void GSSetting::HandleTouchEvents(SDL_Event& e)
{
	m_button->HandleTouchEvent(&e);
}

void GSSetting::HandleMouseMoveEvents(int x, int y)
{
}

void GSSetting::Update(float deltaTime)
{

}

void GSSetting::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	m_button->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}

	//m_textGameName->Draw(renderer);
}

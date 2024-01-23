#include "GSHelp.h"

GSHelp::GSHelp()
{
}

GSHelp::~GSHelp()
{
}

void GSHelp::Init()
{
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_help.png");
	m_help = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_help->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_help->Set2DPosition(0, 0);

	texture = ResourceManagers::GetInstance()->GetTexture("how_to_play.png");
	m_table = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_table->SetSize(600, 325);
	m_table->Set2DPosition((SCREEN_WIDTH - m_table->GetWidth()) / 2, (SCREEN_HEIDHT - m_table->GetHeight()) / 2);

	texture = ResourceManagers::GetInstance()->GetTexture("btn_return.png");
	m_button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	m_button->SetSize(45, 45);
	m_button->Set2DPosition(740, 155);
	m_button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
}

void GSHelp::Exit()
{
}

void GSHelp::Pause()
{
}

void GSHelp::Resume()
{
}

void GSHelp::HandleEvents()
{
}

void GSHelp::HandleKeyEvents(SDL_Event& e)
{
}

void GSHelp::HandleTouchEvents(SDL_Event& e)
{
	m_button->HandleTouchEvent(&e);
}

void GSHelp::HandleMouseMoveEvents(int x, int y)
{
}

void GSHelp::Update(float deltaTime)
{
}

void GSHelp::Draw(SDL_Renderer* renderer)
{
	m_help->Draw(renderer);
	m_table->Draw(renderer);
	m_button->Draw(renderer);
}

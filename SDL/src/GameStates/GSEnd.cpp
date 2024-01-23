#include "GSEnd.h"

GSEnd::GSEnd()
{
}

GSEnd::~GSEnd()
{
}

void GSEnd::Init()
{
	auto texture = ResourceManagers::GetInstance()->GetTexture("table.png");
	m_table = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_table->SetSize(376, 300);
	m_table->Set2DPosition((SCREEN_WIDTH - m_table->GetWidth()) / 2, (SCREEN_HEIDHT - m_table->GetHeight()) / 2);

	texture = ResourceManagers::GetInstance()->GetTexture("btn_return.png");
	std::shared_ptr<MouseButton> btnReplay = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnReplay->SetSize(45, 45);
	btnReplay->Set2DPosition(SCREEN_WIDTH / 2 - 20, SCREEN_HEIDHT / 2 + 95);
	btnReplay->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});

	m_listButton.push_back(btnReplay);

}

void GSEnd::Exit()
{
}

void GSEnd::Pause()
{
}

void GSEnd::Resume()
{
}

void GSEnd::HandleEvents()
{
}

void GSEnd::HandleKeyEvents(SDL_Event& e)
{
}

void GSEnd::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSEnd::HandleMouseMoveEvents(int x, int y)
{
}

void GSEnd::Update(float deltaTime)
{
}

void GSEnd::Draw(SDL_Renderer* renderer)
{
	m_table->Draw(renderer);
	for (auto button : m_listButton)
	{
		button->Draw(renderer);
	}
}

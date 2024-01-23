#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"

class GSEnd : public GameStateBase
{
public:
	GSEnd();
	~GSEnd();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(SDL_Event& e) override;
	void	HandleTouchEvents(SDL_Event& e) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw(SDL_Renderer* renderer) override;
private:
	std::shared_ptr<Sprite2D> m_table;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
};
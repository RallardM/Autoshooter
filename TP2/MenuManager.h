#pragma once
#include "Enumerations.h"

class MenuManager
{
	friend class Player;
	friend class Game;

private:
	static MenuManager* _Instance;
	EUIMenuType m_currentMenu = EUIMenuType::MAIN_MENU;

public:
	~MenuManager();
	static MenuManager* GetInstance();

private:
	MenuManager(); // Private constructor for singleton pattern https://youtu.be/PPup1yeU45I
	const EUIMenuType GetCurrentMenu() const { return m_currentMenu; }
	void SetCurrentMenu(EUIMenuType menu) { m_currentMenu = menu; }

	void RenderPause();
	void RenderMainMenu();
	void RenderLevelUp();
	void RenderGameOver();

};


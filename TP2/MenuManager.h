#pragma once
#include "Enumerations.h"

class MenuManager
{
	friend class Player;
	friend class Game;

public:  // Public member variables

private: // Private member variables
	static MenuManager* _Instance;
	EUIMenuType m_currentMenu = EUIMenuType::MAIN_MENU;

public: // Public methods
	~MenuManager();
	static MenuManager* GetInstance();

private: // Private methods
	MenuManager(); // Private constructor for singleton pattern https://youtu.be/PPup1yeU45I
	const EUIMenuType GetCurrentMenu() const { return m_currentMenu; }
	void SetCurrentMenu(EUIMenuType menu) { m_currentMenu = menu; }

	void RenderPause();
	void RenderMainMenu();
	void RenderLevelUp();
	void RenderGameOver();

};
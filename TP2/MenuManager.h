#pragma once

class MenuManager
{
	friend class Player;
	friend class Game;

public:
	bool m_isPlayerDeadMenuOn = false;
	bool m_isLevelUpMenuOn = false;

private:
	static MenuManager* _Instance;

public:
	~MenuManager();
	static MenuManager* GetInstance();

private:
	MenuManager(); // Private constructor for singleton pattern https://youtu.be/PPup1yeU45I
	void SetIsPlayerDeadMenuOn() { m_isPlayerDeadMenuOn = !m_isPlayerDeadMenuOn; }
	bool const IsPlayerDead() const { return m_isPlayerDeadMenuOn; }
	void SetLevelUpMenuOn() { m_isLevelUpMenuOn = !m_isLevelUpMenuOn; }
	bool const IsLevelUp() const { return m_isLevelUpMenuOn; }

	void RenderPause();
	void RenderLevelUp();
	void RenderGameOver();

};


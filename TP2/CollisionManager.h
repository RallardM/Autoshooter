#pragma once
class CollisionManager
{

private:
	static CollisionManager* _Instance;

public:
	~CollisionManager();
	static CollisionManager* GetInstance();

private:
	CollisionManager() {} // Private constructor for singleton pattern
};


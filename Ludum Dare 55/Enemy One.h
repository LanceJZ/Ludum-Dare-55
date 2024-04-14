#pragma once
#include "Globals.h"
#include "Enemy.h"

enum State
{
	Dive,
	EnterScreen,
	Jiggle
};

class Enemy_One : public Enemy
{
public:
	Enemy_One();
	virtual ~Enemy_One();

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 position);
	void Destroy();

private:
	size_t JigTimerID = 0;
	size_t DiveTimerID = 0;

	State CurrentState = State::Jiggle;

	float Row = 0.0f;

	bool CheckCollision();

	void TimeToDive();
	void Jiggle();
	void BounceOffSides();
	void Dive();
	void BackToTop();
	void EnterFromTop();
};

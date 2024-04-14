#pragma once
#include "Globals.h"
#include "Enemy.h"

enum StateTwo
{
	ChangeDirection,
	GoFoward
};

enum TwoGoing
{
	Left,
	Right
};

class Enemy_Two : public Enemy
{
public:
	Enemy_Two();
	virtual ~Enemy_Two();

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 position);
	void Destroy();

private:
	size_t TurnTimerID = 0;

	float TurnSpeed = 0.0f;

	StateTwo CurrentState = StateTwo::GoFoward;
	TwoGoing CurrentDirection = TwoGoing::Right;

	void Turn();
};

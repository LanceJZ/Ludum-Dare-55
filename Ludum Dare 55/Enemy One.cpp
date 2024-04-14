#include "Enemy One.h"

Enemy_One::Enemy_One()
{
	JigTimerID = TheManagers.EM.AddTimer(1.0f);
	DiveTimerID = TheManagers.EM.AddTimer(5.0f);
}

Enemy_One::~Enemy_One()
{
}

bool Enemy_One::Initialize(Utilities* utilities)
{
	Enemy::Initialize(utilities);

	Radius = 20.0f;

	return false;
}

bool Enemy_One::BeginRun()
{
	Enemy::BeginRun();

	return false;
}

void Enemy_One::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	if (TheManagers.EM.TimerElapsed(ShotTimerID))
	{
		Shoot();
		TheManagers.EM.ResetTimer(ShotTimerID, GetRandomFloat(0.75f, 2.75f));
	}

	if (ScreenEdgeBoundX()) Jiggle();

	if (TheManagers.EM.TimerElapsed(JigTimerID)) Jiggle();

	if (CurrentState == State::Jiggle) TimeToDive();

	if (CurrentState == State::EnterScreen) EnterFromTop();

	if (ScreenEdgeBoundY(-VerticesSize, -VerticesSize)) BackToTop();

}

void Enemy_One::Draw()
{
	Enemy::Draw();
}

void Enemy_One::Spawn(Vector3 position)
{
	Enemy::Spawn(position);

	Dive();
	BackToTop();
}

void Enemy_One::Destroy()
{
	Enemy::Destroy();

}

bool Enemy_One::CheckCollision()
{
	Enemy::CheckCollision();


	return false;
}

void Enemy_One::TimeToDive()
{
	if (TheManagers.EM.TimerElapsed(DiveTimerID))
	{
		TheManagers.EM.ResetTimer(DiveTimerID, GetRandomFloat(3.0f, 5.0f));

		if (GetRandomValue(0, 1) == 0) Dive();
	}
}

void Enemy_One::Jiggle()
{
	TheManagers.EM.ResetTimer(JigTimerID, GetRandomFloat(0.5f, 2.0f));

	Velocity.x = GetRandomFloat(100.0f, 300.5f);

	if (GetRandomValue(0, 1) == 0)
	{
		Velocity.x *= -1.0f;
	}
}

void Enemy_One::BounceOffSides()
{
	Velocity.x *= -1.0f;
}

void Enemy_One::Dive()
{
	Velocity.y = 150.0f;
}

void Enemy_One::BackToTop()
{
	CurrentState = State::EnterScreen;

	Dive();

	Position.y = -FieldSize.y * 0.5f +VerticesSize;

	Row = GetRandomFloat((-FieldSize.y * 0.5f) + 100, (-FieldSize.y * 0.5f) + 200);
}

void Enemy_One::EnterFromTop()
{
	if (Position.y > Row)
	{
		Velocity.y = 0.0f;

		CurrentState = State::Jiggle;
		TheManagers.EM.ResetTimer(DiveTimerID, GetRandomFloat(3.0f, 5.0f));
	}
}

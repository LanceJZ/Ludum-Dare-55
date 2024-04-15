#include "Enemy Two.h"

Enemy_Two::Enemy_Two()
{
	TurnTimerID = TheManagers.EM.AddTimer();
}

Enemy_Two::~Enemy_Two()
{
}

bool Enemy_Two::Initialize(Utilities* utilities)
{
	Enemy::Initialize(utilities);

	Radius = 20.0f;
	Points = 100;

	return false;
}

bool Enemy_Two::BeginRun()
{
	Enemy::BeginRun();


	return false;
}

void Enemy_Two::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	CheckPlayfieldSidesWarp();

	if (TheManagers.EM.TimerElapsed(TurnTimerID) && CurrentState == StateTwo::GoFoward)
	{
		CurrentState = StateTwo::ChangeDirection;
		TheManagers.EM.ResetTimer(ShotTimerID, GetRandomFloat(0.25f, 0.50f));
		TurnSpeed = GetRandomFloat(1.5f, 1.750f);
	}

	if (CurrentState == StateTwo::ChangeDirection) Turn();

	if (ScreenEdgeBoundY())
	{
		Position.y = -FieldSize.y * 0.5f + 20;
	}
}

void Enemy_Two::Draw()
{
	Enemy::Draw();
}

void Enemy_Two::Spawn(Vector3 position)
{
	Enemy::Spawn(position);

	CurrentState = StateTwo::GoFoward;
	TheManagers.EM.ResetTimer(TurnTimerID, GetRandomFloat(3.5f, 5.0f));
	RotationVelocityZ = 0.0f;
	Velocity.y = 0.0f;

	if (GetRandomValue(0, 1) == 0)
	{
		RotationZ = PI;
		CurrentDirection = TwoGoing::Left;
		Velocity.x = -300.0f;
	}
	else
	{
		RotationZ = 0.0f;
		CurrentDirection = TwoGoing::Right;
		Velocity.x = 300.0f;
	}
}

void Enemy_Two::Destroy()
{
	Enemy::Destroy();

}

void Enemy_Two::Hit()
{
	Enemy::Hit();

	Player->SummonPoints++;
}

void Enemy_Two::Turn()
{
	if (CurrentDirection == TwoGoing::Left)
	{
		RotationVelocityZ = -TurnSpeed;

		if (RotationZ < 0.1f)
		{
			RotationZ = 0.0f;
			CurrentState = StateTwo::GoFoward;
			CurrentDirection = TwoGoing::Right;
			RotationVelocityZ = 0.0f;
			TheManagers.EM.ResetTimer(TurnTimerID, GetRandomFloat(1.5f, 5.0f));
		}
	}
	else if (CurrentDirection == TwoGoing::Right)
	{
		RotationVelocityZ = TurnSpeed;

		if (RotationZ > PI)
		{
			CurrentState = StateTwo::GoFoward;
			CurrentDirection = TwoGoing::Left;
			RotationVelocityZ = 0.0f;
			TheManagers.EM.ResetTimer(TurnTimerID, GetRandomFloat(1.5f, 5.0f));
		}
	}

	Velocity = VelocityFromAngleZ(300);

	if (TheManagers.EM.TimerElapsed(ShotTimerID))
	{
		Shoot(VelocityFromAngleZ(300));
		TheManagers.EM.ResetTimer(ShotTimerID, GetRandomFloat(0.1f, 0.250f));
	}
}

bool Enemy_Two::CheckCollision()
{
	Enemy::CheckCollision();

	return false;
}

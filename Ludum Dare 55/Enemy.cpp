#include "Enemy.h"

Enemy::Enemy()
{
	ShotTimerID = TheManagers.EM.AddTimer();
}

Enemy::~Enemy()
{
}

void Enemy::SetPlayer(ThePlayer* player)
{
	Player = player;
}

void Enemy::SetShotModel(Model model)
{
	ShotModel = model;
}

bool Enemy::Initialize(Utilities* utilities)
{
	Model3D::Initialize(utilities);

	return false;
}

bool Enemy::BeginRun()
{
	Model3D::BeginRun();

	TheManagers.EM.ResetTimer(ShotTimerID, GetRandomFloat(0.75f, 1.5f));

	return false;
}

void Enemy::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

}

void Enemy::Draw()
{
	Model3D::Draw();
}

void Enemy::Spawn(Vector3 position)
{
	Entity::Spawn(position);

}

void Enemy::Destroy()
{
	Entity::Destroy();

	Enabled = false;
}

void Enemy::Shoot()
{
	TheManagers.EM.ResetTimer(ShotTimerID);

	bool spawnNew = true;
	size_t spawnNumber = Shots.size();

	for (size_t check = 0; check < spawnNumber; check++)
	{
		if (!Shots[check]->Enabled)
		{
			spawnNew = false;
			spawnNumber = check;
			break;
		}
	}

	if (spawnNew)
	{
		Shots.push_back(DBG_NEW Shot());
		TheManagers.EM.AddModel3D(Shots[spawnNumber], ShotModel);
		Shots[spawnNumber]->Initialize(TheUtilities);
		Shots[spawnNumber]->BeginRun();
	}

	Shots[spawnNumber]->Spawn(Position);
}

void Enemy::Shoot(Vector3 velocity)
{
	TheManagers.EM.ResetTimer(ShotTimerID);

	bool spawnNew = true;
	size_t spawnNumber = Shots.size();

	for (size_t check = 0; check < spawnNumber; check++)
	{
		if (!Shots[check]->Enabled)
		{
			spawnNew = false;
			spawnNumber = check;
			break;
		}
	}

	if (spawnNew)
	{
		Shots.push_back(DBG_NEW Shot());
		TheManagers.EM.AddModel3D(Shots[spawnNumber], ShotModel);
		Shots[spawnNumber]->Initialize(TheUtilities);
		Shots[spawnNumber]->BeginRun();
	}

	Shots[spawnNumber]->Spawn(Position, velocity);
}

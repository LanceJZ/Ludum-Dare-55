#include "Turret.h"

Turret::Turret()
{
	ShotTimerID = TheManagers.EM.AddTimer();
}

Turret::~Turret()
{
}

void Turret::SetShotModel(Model model)
{
	ShotModel = model;
}

void Turret::SetFireSound(Sound fireSound)
{
	FireSound = fireSound;
}

void Turret::SetEnemies(EnemyControl* enemies)
{
	Enemies = enemies;
}

bool Turret::Initialize(Utilities* utilities)
{
	Model3D::Initialize(utilities);

	return false;
}

bool Turret::BeginRun()
{
	Model3D::BeginRun();

	Enabled = false;

	return true;
}

void Turret::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	SetRotationZFromVectors(Target);

	if (TheManagers.EM.TimerElapsed(ShotTimerID))
	{
		TheManagers.EM.ResetTimer(ShotTimerID, GetRandomFloat(0.75f, 1.5f));
		Shoot();
	}

}

void Turret::Draw()
{
	Model3D::Draw();
}

void Turret::Spawn(Vector3 position)
{
	Entity::Spawn(position);

	Enabled = true;
	Target = { 0.0f, 0.0f, 0.0f };

	TheManagers.EM.ResetTimer(ShotTimerID, GetRandomFloat(0.75f, 1.5f));
}

void Turret::Destroy()
{
	Entity::Destroy();

	for (auto& shot : Shots)
	{
		shot->Destroy();
	}

	Enabled = false;
}

void Turret::Shoot()
{
	PlaySound(FireSound);

	bool spawnNewShot = true;
	size_t spawnNumber = Shots.size();

	for (size_t check = 0; check < spawnNumber; check++)
	{
		if (!Shots[check]->Enabled)
		{
			spawnNewShot = false;
			spawnNumber = check;
			break;
		}
	}

	if (spawnNewShot)
	{
		Shots.push_back(DBG_NEW Shot());
		TheManagers.EM.AddModel3D(Shots[spawnNumber], ShotModel);
		Shots[spawnNumber]->Initialize(TheUtilities);
		Shots[spawnNumber]->BeginRun();
	}

	Vector3 velocity = { 0.0f, 0.0f, 0.0f };

	if (GetRandomValue(0, 1) == 0)
	{
		float distance = -1.0f;

		for (auto& enemy : Enemies->EnemyOnes)
		{
			if (enemy->Enabled)
			{
				float enemyDistance = Vector3Distance(Position, enemy->Position);

				if (enemyDistance < distance || distance < 0.0f)
				{
					distance = enemyDistance;
					Target = enemy->Position;
				}
			}
		}
	}
	else
	{
		Target = { GetRandomFloat(-100, 100), GetRandomFloat(-100, 100) , 0.0f };
	}

	velocity = VelocityFromAngleZ(300);

	Shots[spawnNumber]->Spawn(Position, velocity);
}

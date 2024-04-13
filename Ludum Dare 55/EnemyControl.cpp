#include "EnemyControl.h"

EnemyControl::EnemyControl()
{

}

EnemyControl::~EnemyControl()
{
}

void EnemyControl::SetPlayer(ThePlayer* player)
{
	Player = player;
}

void EnemyControl::SetShotModel(Model model)
{
	ShotModel = model;
}

void EnemyControl::SetEnemyOneModel(Model model)
{
	EnemyOneModel = model;
}

bool EnemyControl::Initialize(Utilities* utilities)
{
	Common::Initialize(utilities);

	return false;
}

bool EnemyControl::BeginRun()
{
	SpawnEnemyOne(12);

	return false;
}

void EnemyControl::Update()
{
	Common::Update();

}

void EnemyControl::Reset()
{
}

void EnemyControl::SpawnEnemyOne(size_t count)
{
	for (size_t i = 0; i < count; i++)
	{
		bool spawnNew = true;
		size_t spawnNumber = EnemyOnes.size();

		for (size_t check = 0; check < spawnNumber; check++)
		{
			if (!EnemyOnes[check]->Enabled)
			{
				spawnNew = false;
				spawnNumber = check;
				break;
			}
		}

		if (spawnNew)
		{
			EnemyOnes.push_back(DBG_NEW Enemy_One());
			TheManagers.EM.AddModel3D(EnemyOnes[spawnNumber], EnemyOneModel);
			EnemyOnes[spawnNumber]->SetPlayer(Player);
			EnemyOnes[spawnNumber]->SetShotModel(ShotModel);
			EnemyOnes[spawnNumber]->Initialize(TheUtilities);
			EnemyOnes[spawnNumber]->BeginRun();
		}

		EnemyOnes[spawnNumber]->Spawn({
			GetRandomFloat(-FieldSize.x * 0.5f, FieldSize.x * 0.5f), 0.0f, 0.0f });
	}
}

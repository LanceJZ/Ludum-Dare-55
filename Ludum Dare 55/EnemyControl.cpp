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

void EnemyControl::SetEnemyTwoModel(Model model)
{
	EnemyTwoModel = model;
}

void EnemyControl::SetEnemyOneFireSound(Sound sound)
{
	EnemyOneFireSound = sound;
}

void EnemyControl::SetEnemyTwoFireSound(Sound sound)
{
	EnemyTwoFireSound = sound;
}

void EnemyControl::SetEnemyOneExplodeSound(Sound sound)
{
	EnemyOneExplodeSound = sound;
}

void EnemyControl::SetEnemyTwoExplodeSound(Sound sound)
{
	EnemyTwoExplodeSound = sound;
}

void EnemyControl::SetNewWaveSound(Sound sound)
{
	NewWaveSound = sound;
}

bool EnemyControl::Initialize(Utilities* utilities)
{
	Common::Initialize(utilities);

	return false;
}

bool EnemyControl::BeginRun()
{
	Common::BeginRun();

	return false;
}

void EnemyControl::Update()
{
	Common::Update();

	if (GameOver) return;

	int numberOfEnemies = 0;

	for (auto& enemy : EnemyOnes)
	{
		if (enemy->Enabled) numberOfEnemies++;
	}

	for (auto& enemy : EnemyTwos)
	{
		if (enemy->Enabled) numberOfEnemies++;
	}

	if (numberOfEnemies == 0)
	{
		Wave++;
		NewWave();
	}
}

void EnemyControl::NewWave()
{
	PlaySound(NewWaveSound);

	SpawnEnemyOne(6 + (3 * Wave));
	SpawnEnemyTwo(Wave + 2);
}

void EnemyControl::ClearField()
{
	for (auto& enemy : EnemyOnes)
	{
		enemy->Reset();
	}

	for (auto& enemy : EnemyTwos)
	{
		enemy->Reset();
	}
}

void EnemyControl::Reset()
{
	int enemyOneCount = 0;
	int enemyTwoCount = 0;

	for (auto& enemy : EnemyOnes)
	{
		if (enemy->Enabled) enemyOneCount++;
	}

	for (auto& enemy : EnemyTwos)
	{
		if (enemy->Enabled) enemyTwoCount++;
	}

	ClearField();

	SpawnEnemyOne(enemyOneCount);
	SpawnEnemyTwo(enemyTwoCount);
}

void EnemyControl::NewGame()
{
	Wave = 0;
	GameOver = false;
	ClearField();
	NewWave();
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
			EnemyOnes[spawnNumber]->SetFireSound(EnemyOneFireSound);
			EnemyOnes[spawnNumber]->SetExplodeSound(EnemyOneExplodeSound);
			EnemyOnes[spawnNumber]->Initialize(TheUtilities);
			EnemyOnes[spawnNumber]->BeginRun();
		}

		EnemyOnes[spawnNumber]->Spawn({
			GetRandomFloat(-FieldSize.x * 0.5f, FieldSize.x * 0.5f), 0.0f, 0.0f });
	}
}

void EnemyControl::SpawnEnemyTwo(size_t count)
{
	for (size_t i = 0; i < count; i++)
	{
		bool spawnNew = true;
		size_t spawnNumber = EnemyTwos.size();

		for (size_t check = 0; check < spawnNumber; check++)
		{
			if (!EnemyTwos[check]->Enabled)
			{
				spawnNew = false;
				spawnNumber = check;
				break;
			}
		}

		if (spawnNew)
		{
			EnemyTwos.push_back(DBG_NEW Enemy_Two());
			TheManagers.EM.AddModel3D(EnemyTwos[spawnNumber], EnemyTwoModel);
			EnemyTwos[spawnNumber]->SetPlayer(Player);
			EnemyTwos[spawnNumber]->SetShotModel(ShotModel);
			EnemyTwos[spawnNumber]->SetFireSound(EnemyTwoFireSound);
			EnemyTwos[spawnNumber]->SetExplodeSound(EnemyTwoExplodeSound);
			EnemyTwos[spawnNumber]->Initialize(TheUtilities);
			EnemyTwos[spawnNumber]->BeginRun();
		}

		EnemyTwos[spawnNumber]->Spawn({ FieldSize.x * 0.5f + 40,
			-FieldSize.y * 0.5f + 40, 0.0f });
	}
}

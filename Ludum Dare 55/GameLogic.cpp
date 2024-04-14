#include "GameLogic.h"

GameLogic::GameLogic()
{
	TheManagers.EM.AddModel3D(TurretLeft = DBG_NEW Turret());
	TheManagers.EM.AddModel3D(TurretRight = DBG_NEW Turret());

	TurretTimerID = TheManagers.EM.AddTimer();
}

GameLogic::~GameLogic()
{
}

void GameLogic::SetPlayer(ThePlayer* player)
{
	Player = player;
}

void GameLogic::SetEnemies(EnemyControl* enemies)
{
	Enemies = enemies;
	TurretLeft->SetEnemies(enemies);
	TurretRight->SetEnemies(enemies);
}

void GameLogic::SetShotModel(Model model)
{
	TurretLeft->SetShotModel(model);
	TurretRight->SetShotModel(model);
}

void GameLogic::SetTurretModel(Model model)
{
	TurretLeft->SetModel(model);
	TurretRight->SetModel(model);
}

bool GameLogic::Initialize(Utilities* utilities)
{
	Common::Initialize(utilities);

	AdjustedFieldSize = Vector2Multiply(FieldSize, { 0.5f, 0.5f });

	return false;
}

bool GameLogic::BeginRun()
{
	Common::BeginRun();

	return false;
}

void GameLogic::Update()
{
	Common::Update();

	if(TurretsActive) UpdateTurrets();

}

void GameLogic::GameInput()
{
	if (State == MainMenu)
	{
		if (IsGamepadAvailable(0))
		{
			if (IsGamepadButtonPressed(0, 15))//Start button
			{
				NewGame();
			}
		}

		if (IsKeyPressed(KEY_N))
		{
			NewGame();
		}

		if (IsKeyPressed(KEY_D))
		{

		}
	}

	if (State == InPlay)
	{
		if (IsGamepadAvailable(0))
		{
			if (IsGamepadButtonPressed(0, 13)) //Menu Button
			{
				State = Pause;
			}

			if (IsGamepadButtonPressed(0, 8)) //X button
			{
				PlayBackgroundMusic = !PlayBackgroundMusic;
			}
		}

		if (IsKeyPressed(KEY_M))
		{
			PlayBackgroundMusic = !PlayBackgroundMusic;
		}


		if (IsKeyPressed(KEY_P))
		{
			State = Pause;
		}

		if (IsKeyPressed(KEY_B))
		{
		}
	}

	if (IsKeyPressed(KEY_LEFT_CONTROL))
	{
		if (Player->Enabled)
		{
			if (Player->SummonPoints > 0)
			{
				Player->SummonPoints--;
				SummonTurrets();
			}
		}
	}
}

void GameLogic::NewGame()
{
}

void GameLogic::UpdateTurrets()
{
	if (TheManagers.EM.TimerElapsed(TurretTimerID))
	{
		TurretsActive = false;
		TurretLeft->Destroy();
		TurretRight->Destroy();
	}

	CheckCollisions();
}

void GameLogic::SummonTurrets()
{
	TurretsActive = true;

	float buffer = 20.0f;

	TurretLeft->Spawn({-FieldSize.x * 0.5f + buffer, FieldSize.y * 0.5f - buffer, 0.0f});
	TurretRight->Spawn({FieldSize.x * 0.5f - buffer, FieldSize.y * 0.5f - buffer, 0.0f});

	TheManagers.EM.ResetTimer(TurretTimerID, GetRandomFloat(10.5f, 20.0f));
}

void GameLogic::UpdateEnemySummonPoints()
{

}

void GameLogic::CheckCollisions()
{
	for (auto& enemy : Enemies->EnemyOnes)
	{
		if (!enemy->Enabled) continue;

		for (auto& shot : TurretLeft->Shots)
		{
			if (shot->Enabled)
			{
				if (shot->CirclesIntersect(*enemy))
				{
					shot->Destroy();
					enemy->Hit();
				}
			}
		}

		for (auto& shot : TurretRight->Shots)
		{
			if (shot->Enabled)
			{
				if (shot->CirclesIntersect(*enemy))
				{
					shot->Destroy();
					enemy->Hit();
				}
			}
		}
	}
}

#include "Game.h"

Game::Game()
{
	//When adding classes to EM, must be pointer to heap,IE: Name = new Class().
	LogicID = TheManagers.EM.AddCommon(Logic = DBG_NEW GameLogic());
	BackGroundID = TheManagers.EM.AddCommon(BackGround = DBG_NEW TheBackground());
	EnemiesID = TheManagers.EM.AddCommon(Enemies = DBG_NEW EnemyControl());
	PlayerID = TheManagers.EM.AddModel3D(Player = DBG_NEW ThePlayer());
}

Game::~Game()
{
}

bool Game::Initialize(Utilities &utilities, GameLogic* gameLogic) //Initialize
{
	TheUtilities = &utilities;

	Common::Initialize(&utilities);

	float multiX = 1.0f;
	float multiY = 1.0f;
	FieldSize = { GetScreenWidth() * multiX, (float)GetScreenHeight() * multiY};

	Logic->SetPlayer(Player);
	Logic->SetEnemies(Enemies);

	Enemies->SetPlayer(Player);

	//Any Entities added after this point need this method fired manually.
	TheManagers.Initialize();
	return true;
}

bool Game::Load()
{
	Model shot = TheManagers.CM.LoadAndGetModel("Shot");

	Player->SetModel(TheManagers.CM.LoadAndGetModel("Player Ship"));
	Player->SetShotModel(TheManagers.CM.LoadAndGetModel("Player Shot"));
	Logic->SetPlayer(Player);
	Logic->SetEnemies(Enemies);
	Logic->SetShotModel(shot);
	Logic->SetTurretModel(TheManagers.CM.LoadAndGetModel("Turret"));
	Enemies->SetShotModel(shot);
	Enemies->SetEnemyOneModel(TheManagers.CM.LoadAndGetModel("Enemy One"));
	Enemies->SetEnemyTwoModel(TheManagers.CM.LoadAndGetModel("Enemy Two"));

	Player->SetFireSound(TheManagers.CM.LoadAndGetSound("Player Fire"));
	Player->SetExplodeSound(TheManagers.CM.LoadAndGetSound("Player Explode"));
	Player->SetExtraLifeSound(TheManagers.CM.LoadAndGetSound("Player Extra Life"));

	Logic->SetEndGameSound(TheManagers.CM.LoadAndGetSound("Game Over"));
	Logic->SetTurretFireSound(TheManagers.CM.LoadAndGetSound("Turret Fire"));

	Enemies->SetEnemyOneFireSound(TheManagers.CM.LoadAndGetSound("Enemy One Fire"));
	Enemies->SetEnemyOneExplodeSound(TheManagers.CM.LoadAndGetSound("Enemy One Explode"));
	Enemies->SetEnemyTwoFireSound(TheManagers.CM.LoadAndGetSound("Enemy Two Fire"));
	Enemies->SetEnemyTwoExplodeSound(TheManagers.CM.LoadAndGetSound("Enemy Two Explode"));
	Enemies->SetNewWaveSound(TheManagers.CM.LoadAndGetSound("Start Of Wave"));

	return true;
}

bool Game::BeginRun()
{
	//Any Entities added after this point need this method fired manually.
	TheManagers.BeginRun();

	return true;
}

void Game::ProcessInput()
{
	GameInput();
	TheManagers.EM.Input();
}


void Game::Update(float deltaTime)
{
	if (Paused)	return;

	TheManagers.EM.Update(deltaTime);
}

void Game::Draw()
{
	BeginMode3D(TheCamera);

	//3D Drawing here.
	Draw3D();

	EndMode3D();

	//2D drawing, fonts go here.

	Draw2D();
}

void Game::Draw3D()
{
	TheManagers.EM.Draw3D();

#ifdef _DEBUG
	int fsx = int(FieldSize.x * 0.5f);
	int fsy = int(FieldSize.y * 0.5f);

	DrawLine(-fsx, -fsy, fsx, -fsy, { DARKBLUE });
	DrawLine(fsx, -fsy, fsx, fsy, { DARKBLUE });
	DrawLine(fsx, fsy - 1, -fsx, fsy, { DARKBLUE });
	DrawLine(-fsx, fsy - 1, -fsx, -fsy, { DARKBLUE });
#endif
}

void Game::Draw2D()
{
	DrawText("Score:", 50, 20, 45, BLUE);
	DrawText(std::to_string(Player->Score).c_str(), 50 + (7 * 25), 20, 45, BLUE);

	DrawText("Summons:", 800, 20, 45, BLUE);
	DrawText(std::to_string(Player->SummonPoints).c_str(), 800 + (9 * 25), 20, 45, BLUE);

	DrawText("Lives:", 50, FieldSize.y - 45, 45, BLUE);
	DrawText(std::to_string(Player->Lives).c_str(), 50 + (6 * 25),
		FieldSize.y - 45, 45, BLUE);

	DrawText("Wave:", 800, FieldSize.y - 45, 45, BLUE);
	DrawText(std::to_string(Enemies->Wave + 1).c_str(), 800 + (6 * 25),
		FieldSize.y - 45, 45, BLUE);
}

void Game::GameInput()
{
	if (IsKeyPressed(KEY_P))
	{
		Paused = !Paused;
	}

	Logic->GameInput();
}
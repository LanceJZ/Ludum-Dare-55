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
	Player->SetModel(TheManagers.CM.LoadAndGetModel("Player Ship"));

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
}

void Game::GameInput()
{
	if (IsKeyPressed(KEY_P))
	{
		Paused = !Paused;
	}

	Logic->GameInput();
}
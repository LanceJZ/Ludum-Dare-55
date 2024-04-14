#include "ThePlayer.h"

ThePlayer::ThePlayer()
{
	for (int i = 0; i < 4; i++)
	{
		TheManagers.EM.AddModel3D(Shots[i] = DBG_NEW Shot());
	}
}

ThePlayer::~ThePlayer()
{
}

void ThePlayer::SetShotModel(Model model)
{
	for (int i = 0; i < 4; i++)
	{
		Shots[i]->SetModel(model);
		Shots[i]->Enabled = false;
		Shots[i]->Radius = 10.0f;
	}
}

bool ThePlayer::Initialize(Utilities* utilities)
{
	Model3D::Initialize(utilities);

	return false;
}

bool ThePlayer::BeginRun()
{
	Model3D::BeginRun();

	Y(FieldSize.y * 0.5f - 60.0f);

	return false;
}

void ThePlayer::Input()
{
	Model3D::Input();

	Keyboard();

	if (IsGamepadAvailable(0))
	{
		Gamepad();
	}
}

void ThePlayer::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	ScreenEdgeBoundX();

	ScreenEdgeBoundY(WindowHeight + 150.0f, 60.0f);
}

void ThePlayer::Draw()
{
	Model3D::Draw();

}

void ThePlayer::Hit()
{
	Acceleration = { 0 };
	Velocity = { 0 };
	Lives--;
	Enabled = false;
}

void ThePlayer::ScoreUpdate(int addToScore)
{
	Score += addToScore;

	if (Score > HighScore)
	{
		HighScore = Score;
	}

	if (Score > NextNewLifeScore)
	{
		NextNewLifeScore += 10000;
		Lives++;
		NewLife = true;
	}
}

void ThePlayer::Reset()
{
	Position = { 0, 0, 0 };
	Velocity = { 0, 0, 0 };
	Enabled = true;
}

void ThePlayer::NewGame()
{
	Lives = 4;
	NextNewLifeScore = 10000;
	Score = 0;
	GameOver = false;
	Reset();
}

void ThePlayer::Shoot()
{
	for (size_t i = 0; i < 4; i++)
	{
		if (!Shots[i]->Enabled)
		{
			Shots[i]->SpawnPlayerShot(Position);
			break;
		}
	}
}

void ThePlayer::Gamepad()
{
	//Button B is 6 for Shield //Button A is 7 for Fire //Button Y is 8 for Hyperspace
	//Button X is 5	//Left bumper is 9 //Right bumper is 11 for Shield //Left Trigger is 10
	//Right Trigger is 12 for Thrust //Dpad Up is 1 for	//Dpad Down is 3 for
	//Dpad Left is 4 for rotate left //Dpad Right is 2 for rotate right
	//Axis 1 is -1 for , 1 for  on left stick.
	//Axis 0 is -1 for Left, 1 for right on left stick.

	if (IsGamepadButtonDown(0, 12))
	{
	}
	else
	{
	}

	if (IsGamepadButtonDown(0, 4) || GetGamepadAxisMovement(0, 0) < -0.25f)
	{
	}
	else if (IsGamepadButtonDown(0, 2) || GetGamepadAxisMovement(0, 0) > 0.25f)
	{
	}

	if (IsGamepadButtonPressed(0, 7))
	{
	}

	if (IsGamepadButtonDown(0, 11) || IsGamepadButtonDown(0, 6))
	{
	}
	else
	{
	}
}

void ThePlayer::Keyboard()
{
	float xSpeed = 180.0f;

	if (IsKeyDown(KEY_RIGHT))
	{
		Velocity.x = xSpeed;
	}
	else if (IsKeyDown(KEY_LEFT))
	{
		Velocity.x = -xSpeed;
	}
	else
	{
		Velocity.x = 0;
	}

	if (IsKeyDown(KEY_UP))
	{
		Velocity.y = -180.0f;
	}
	else if (IsKeyDown(KEY_DOWN))
	{
		Velocity.y = 180.0f;
	}
	else
	{
		Velocity.y = 0;
	}

	if (IsKeyPressed(KEY_RIGHT_CONTROL) || IsKeyPressed(KEY_LEFT_CONTROL) ||
		IsKeyPressed(KEY_SPACE))
	{
	}

	if (IsKeyPressed(KEY_SPACE))
	{
		Shoot();
	}
}
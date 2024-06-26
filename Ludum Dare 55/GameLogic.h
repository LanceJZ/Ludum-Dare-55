#pragma once
#include "Globals.h"
#include "Utilities.h"
#include "ThePlayer.h"
#include "EnemyControl.h"
#include "Turret.h"

enum GameState
{
	PlayerHit,
	Over,
	InPlay,
	Pause,
	HighScores,
	MainMenu
};

class GameLogic : public Common
{
public:
	GameLogic();
	virtual ~GameLogic();

	bool PlayBackgroundMusic = true;
	bool TurretsActive = false;

	GameState State = MainMenu;

	void SetPlayer(ThePlayer* player);
	void SetEnemies(EnemyControl* enemies);
	void SetShotModel(Model model);
	void SetTurretModel(Model model);
	void SetTurretFireSound(Sound sound);
	void SetEndGameSound(Sound sound);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update();
	void GameInput();

private:
	size_t TurretTimerID = 0;

	Vector2 AdjustedFieldSize = {};

	Sound EndGameSound = {};

	ThePlayer* Player = {};
	EnemyControl* Enemies = {};
	Turret* TurretLeft = {};
	Turret* TurretRight = {};

	void NewGame();
	void UpdatePlayer();
	void ResetField();
	void UpdateTurrets();
	void SummonTurrets();
	void UpdateEnemySummonPoints();
	void CheckCollisions();
};


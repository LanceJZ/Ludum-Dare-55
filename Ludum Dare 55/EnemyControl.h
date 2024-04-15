#pragma once
#include "Globals.h"
#include "ThePlayer.h"
#include "Enemy One.h"
#include "Enemy Two.h"

class EnemyControl : public Common
{
public:
	bool GameOver = true;

	EnemyControl();
	virtual ~EnemyControl();

	int Wave = 0;

	std::vector<Enemy_One*> EnemyOnes;
	std::vector<Enemy_Two*> EnemyTwos;

	void SetPlayer(ThePlayer* player);
	void SetShotModel(Model model);
	void SetEnemyOneModel(Model model);
	void SetEnemyTwoModel(Model model);

	void SetEnemyOneFireSound(Sound sound);
	void SetEnemyTwoFireSound(Sound sound);
	void SetEnemyOneExplodeSound(Sound sound);
	void SetEnemyTwoExplodeSound(Sound sound);
	void SetNewWaveSound(Sound sound);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update();

	void Reset();
	void NewGame();

private:
	Model ShotModel = { 0 };
	Model EnemyOneModel = { 0 };
	Model EnemyTwoModel = { 0 };

	Sound EnemyOneFireSound = { 0 };
	Sound EnemyTwoFireSound = { 0 };
	Sound EnemyOneExplodeSound = { 0 };
	Sound EnemyTwoExplodeSound = { 0 };
	Sound NewWaveSound = { 0 };

	ThePlayer *Player = nullptr;

	void NewWave();
	void ClearField();
	void SpawnEnemyOne(size_t count);
	void SpawnEnemyTwo(size_t count);
};


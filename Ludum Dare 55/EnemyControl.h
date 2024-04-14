#pragma once
#include "Globals.h"
#include "ThePlayer.h"
#include "Enemy One.h"
#include "Enemy Two.h"

class EnemyControl : public Common
{
public:
	EnemyControl();
	virtual ~EnemyControl();

	std::vector<Enemy_One*> EnemyOnes;
	std::vector<Enemy_Two*> EnemyTwos;

	void SetPlayer(ThePlayer* player);
	void SetShotModel(Model model);
	void SetEnemyOneModel(Model model);
	void SetEnemyTwoModel(Model model);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update();

private:
	Model ShotModel;
	Model EnemyOneModel;
	Model EnemyTwoModel;

	ThePlayer *Player = nullptr;

	void Reset();
	void SpawnEnemyOne(size_t count);
	void SpawnEnemyTwo(size_t count);
};


#pragma once
#include "Globals.h"
#include "ThePlayer.h"
#include "Enemy One.h"

class EnemyControl : public Common
{
public:
	EnemyControl();
	virtual ~EnemyControl();

	std::vector<Enemy_One*> EnemyOnes;

	void SetPlayer(ThePlayer* player);
	void SetShotModel(Model model);
	void SetEnemyOneModel(Model model);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update();

private:
	Model EnemyOneModel;
	Model ShotModel;

	ThePlayer *Player = nullptr;

	void Reset();
	void SpawnEnemyOne(size_t count);
};


#pragma once
#include "Globals.h"
#include "EnemyControl.h"
#include "Shot.h"

class Turret : public Model3D
{
public:
	std::vector<Shot*> Shots;

	Turret();
	virtual ~Turret();

	void SetShotModel(Model model);
	void SetEnemies(EnemyControl* enemies);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 position);
	void Destroy();

private:
	size_t ShotTimerID = 0;

	Vector3 Target = { 0.0f, 0.0f, 0.0f };

	Model ShotModel;

	EnemyControl* Enemies = nullptr;

	void Shoot();
};

#pragma once
#include "Globals.h"
#include "ThePlayer.h"
#include "Shot.h"

class Enemy : public Model3D
{
public:
	Enemy();
	virtual ~Enemy();

	std::vector<Shot*> Shots;

	void SetPlayer(ThePlayer* player);
	void SetShotModel(Model model);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 position);
	void Destroy();
	void Hit();
	void Reset();

protected:
	size_t ShotTimerID = 0;

	int Points = 0;

	ThePlayer* Player = nullptr;

	void Shoot();
	void Shoot(Vector3 velocity);
	virtual bool CheckCollision();

private:

	Model ShotModel = { 0 };

};

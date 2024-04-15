#pragma once
#include "Globals.h"
#include "Shot.h"
#include "ParticleManager.h"

class ThePlayer : public Model3D
{
public:
	Shot* Shots[4] = { nullptr };

	ThePlayer();
	virtual ~ThePlayer();

	bool NewLife = false;
	bool GameOver = false;

	int Score { 0 };
	int HighScore { 0 };
	int Lives { 0 };
	int SummonPoints { 0 };

	void SetShotModel(Model model);
	void SetFireSound(Sound fireSound);
	void SetExplodeSound(Sound explodeSound);
	void SetExtraLifeSound(Sound extraLifeSound);

	void SetParticleManager(ParticleManager* particleManager);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Input();
	void Update(float deltaTime);
	void Draw();

	void Hit();
	void ScoreUpdate(int addToScore);
	void Reset();
	void NewGame();

private:
	int NextNewLifeScore = 10000;

	Sound FireSound = {};
	Sound ExplodeSound = {};
	Sound ExtraLifeSound = {};

	ParticleManager* PM = nullptr;

	void Shoot();
	void Gamepad();
	void Keyboard();
};

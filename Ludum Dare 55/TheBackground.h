#pragma once
#include "Globals.h"
#include "Common.h"

class TheBackground : public Common
{
public:
	TheBackground();
	virtual ~TheBackground();

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update();

private:


};


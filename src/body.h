#pragma once

#include <string>
class Body
{
public:
	Body(){}

	void updateNeeds();

	std::string toString() const;

private:
	unsigned short mHungryLevel			= 0;	//голод
	unsigned short mThirstLevel			= 0;	//жажда
	unsigned short mRadiationLevel		= 0;	//облучение
	unsigned short mBleadingLevel		= 0;	//кровотечение
	unsigned short mExhaustionLevel		= 0;	//истощение
	unsigned short mStaminaLevel		= 100;	//стамина

	bool mIsAlive						= true;
	bool mIsSleep						= false;
};

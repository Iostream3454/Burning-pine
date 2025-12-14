#pragma once

#include <string>

class NeedsManager
{
public:
	NeedsManager(){}

	void updateNeeds();

	std::string toString() const;

	unsigned short getThirstLevel() const;

	unsigned short getHungryLevel() const;

	unsigned short getRadiationLevel() const;

	unsigned short getBleadingLevel() const;

	unsigned short getExhaustionLevel() const;

	unsigned short getStaminaLevel() const;

	bool isAlive() const;

	bool isSleep() const;

	void goToSleep();

	void breakSleep();

private:
	unsigned short mHungryLevel			= 0;	//голод
	unsigned short mThirstLevel			= 0;	//жажда
	unsigned short mRadiationLevel		= 0;	//облучение
	unsigned short mBleadingLevel		= 0;	//кровотечение
	unsigned short mExhaustionLevel		= 0;	//истощение
	unsigned short mStaminaLevel		= 66;	//стамина

	bool mIsAlive						= true;
	bool mIsSleep						= false;
};

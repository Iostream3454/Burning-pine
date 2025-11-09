#pragma once

#include <string>
class Body
{
public:
	Body()
	{
	}

	void updateNeeds() {
		mHungryLevel += 3;
		if (mHungryLevel > 100) mHungryLevel = 100;
		if (mHungryLevel < 0) mHungryLevel = 0;
		mThirstLevel += 5;
		if (mThirstLevel > 100) mThirstLevel = 100;
		if (mThirstLevel < 0) mThirstLevel = 0;
		mRadiationLevel += 0;
		if (mRadiationLevel < 0) mRadiationLevel = 0;
		mBleadingLevel += 0;
		if (mBleadingLevel < 0) mBleadingLevel = 0;
		mStaminaLevel -= 1;
		if (mStaminaLevel > 100) mStaminaLevel = 100;
		if (mStaminaLevel < 0) mStaminaLevel = 0;
		mExhaustionLevel += 0;
		if (mExhaustionLevel < 0) mExhaustionLevel = 0;
		if (mExhaustionLevel > 125) 
		{
			mExhaustionLevel = 125;
			mIsAlive = false;
		}
	}

	std::string toString() const {
		return "Hungry: " + std::to_string(mHungryLevel) + " Thirst: " + std::to_string(mThirstLevel) + 
			" Doza: " + std::to_string(mRadiationLevel) + " Bleading: " + std::to_string(mBleadingLevel) + 
			" Exhaustion: " + std::to_string(mExhaustionLevel) + " Stamina: " + std::to_string(mStaminaLevel);
	}

private:
	unsigned short mHungryLevel			= 0;	//голод
	unsigned short mThirstLevel			= 0;	//жажда
	unsigned short mRadiationLevel		= 0;	//облучение
	unsigned short mBleadingLevel		= 0;	//кровотечение
	unsigned short mExhaustionLevel		= 0;	//истощение
	unsigned short mStaminaLevel		= 100;	//стамина

	bool mIsAlive = true;
};

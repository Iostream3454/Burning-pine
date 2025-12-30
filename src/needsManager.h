#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include "needs.h"

class NeedsManager
{
public:

	NeedsManager() {}

	void addNeed(const std::string needName, std::unique_ptr<Need> need);

	unsigned short getNeedValue(const std::string& needName);

	void update();

	bool isAlive() const;

	bool isSleep() const;

	void goToSleep();

	void breakSleep();

private: 
	std::unordered_map<std::string, std::unique_ptr<Need>> mListOfNeeds;	//вектор нужд персонажа
	unsigned short mHungryLevel			= 0;			//голод
	unsigned short mThirstLevel			= 0;			//жажда
	unsigned short mRadiationLevel		= 0;			//облучение
	unsigned short mBleadingLevel		= 0;			//кровотечение
	unsigned short mExhaustionLevel		= 0;			//истощение
	unsigned short mStaminaLevel		= 66;			//стамина

	bool mIsAlive						= true;
	bool mIsSleep						= false;
};

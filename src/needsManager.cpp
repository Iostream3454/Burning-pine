#include "needsManager.h"

void NeedsManager::updateNeeds() {
	//Hungry
	mHungryLevel += 3;
	if (mHungryLevel > 100) mHungryLevel = 100;
	if (mHungryLevel < 0) mHungryLevel = 0;
	//Thirst
	mThirstLevel += 5;
	if (mThirstLevel > 100) mThirstLevel = 100;
	if (mThirstLevel < 0) mThirstLevel = 0;
	//Radiation
	mRadiationLevel += 0;
	if (mRadiationLevel < 0) mRadiationLevel = 0;
	//Bleading
	mBleadingLevel += 0;
	if (mBleadingLevel < 0) mBleadingLevel = 0;

	//Stamina
	mStaminaLevel -= 1;

	

	if (mStaminaLevel > 100) mStaminaLevel = 100;
	if(!mIsSleep)
	{
		if (mHungryLevel > 99 && (mStaminaLevel - 2) > 0) mStaminaLevel -= 2;
		if (mThirstLevel > 99 && (mStaminaLevel - 4) > 0) mStaminaLevel -= 4;
		if (mStaminaLevel < 2) mIsSleep = true, mStaminaLevel = 2;
	}
	else {
		if (mThirstLevel > 98 || mHungryLevel > 98 || mStaminaLevel > 99)
		{
			mIsSleep = false;
		}
		mStaminaLevel += 3;
	}
	//mExhaustionLevel
	mExhaustionLevel += 0;
	if (mExhaustionLevel < 0) mExhaustionLevel = 0;
	if (mExhaustionLevel > 125)
	{
		mExhaustionLevel = 125;
		mIsAlive = false;
	}
}

std::string NeedsManager::toString() const {
	return "Hungry: " + std::to_string(mHungryLevel) + " Thirst: " + std::to_string(mThirstLevel) +
		" Doza: " + std::to_string(mRadiationLevel) + " Bleading: " + std::to_string(mBleadingLevel) +
		" Exhaustion: " + std::to_string(mExhaustionLevel) + " Stamina: " + std::to_string(mStaminaLevel);
}

unsigned short NeedsManager::getThirstLevel() const { return mThirstLevel; }

unsigned short NeedsManager::getHungryLevel() const { return mHungryLevel; }

unsigned short NeedsManager::getBleadingLevel() const { return mBleadingLevel; }

unsigned short NeedsManager::getRadiationLevel() const { return mRadiationLevel; }

unsigned short NeedsManager::getExhaustionLevel() const { return mExhaustionLevel; }

unsigned short NeedsManager::getStaminaLevel() const { return mStaminaLevel; }

bool NeedsManager::isAlive() const { return mIsAlive; }

bool NeedsManager::isSleep() const { return mIsSleep; }

void NeedsManager::goToSleep() {
	if(this->mThirstLevel < 99 && this->mHungryLevel < 99)
	{
		this->mIsSleep = true;
	}
}

void NeedsManager::breakSleep() {
	this->mIsSleep = false;
}

NeedsManager::NeedsManager(std::vector<std::unique_ptr<Need>>&& listOfNeeds)
{
	mListOfNeeds = std::move(listOfNeeds);
}

void NeedsManager::addNeed(std::unique_ptr<Need> need) {
	mListOfNeeds.push_back(std::move(need));
}

void NeedsManager::update() {
	for (auto& var : mListOfNeeds)
	{
		var->update();
	}
}
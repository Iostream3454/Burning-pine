#include "body.h"

void Body::updateNeeds() {
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

std::string Body::toString() const {
	return "Hungry: " + std::to_string(mHungryLevel) + " Thirst: " + std::to_string(mThirstLevel) +
		" Doza: " + std::to_string(mRadiationLevel) + " Bleading: " + std::to_string(mBleadingLevel) +
		" Exhaustion: " + std::to_string(mExhaustionLevel) + " Stamina: " + std::to_string(mStaminaLevel);
}

unsigned short Body::getThirstLevel() const { return mThirstLevel; }

unsigned short Body::getHungryLevel() const { return mHungryLevel; }

unsigned short Body::getBleadingLevel() const { return mBleadingLevel; }

unsigned short Body::getRadiationLevel() const { return mRadiationLevel; }

unsigned short Body::getExhaustionLevel() const { return mExhaustionLevel; }

unsigned short Body::getStaminaLevel() const { return mStaminaLevel; }

bool Body::isAlive() const { return mIsAlive; }

bool Body::isSleep() const { return mIsSleep; }

void Body::goToSleep() {
	if(this->mThirstLevel < 99 && this->mHungryLevel < 99)
	{
		this->mIsSleep = true;
	}
}

void Body::breakSleep() {
	this->mIsSleep = false;
}
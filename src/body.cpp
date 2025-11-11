#include "body.h"

void Body::updateNeeds() {
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
	if (mHungryLevel > 99) mStaminaLevel -= 2;
	if (mThirstLevel > 99) mStaminaLevel -= 4;
	if (mStaminaLevel > 100) mStaminaLevel = 100;
	if (mStaminaLevel < 0) mIsSleep = true, mStaminaLevel = 0;

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
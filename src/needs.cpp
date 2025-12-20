#include "needs.h"

#include <algorithm>

Need::Need(short currentLevel, short maxLevel, short minLevel, float changeRate, float criticalRate) :
	mCurrentLevel(currentLevel),
	mMaxLevel(maxLevel),
	mMinLevel(minLevel),
	mChangeRate(changeRate),
	mCriticalRate(criticalRate)
{
}

Thirst::Thirst(short currentLevel, short maxLevel, short minLevel, float changeRate, float criticalRate) :
	Need(currentLevel, maxLevel, minLevel, changeRate, criticalRate)
{
}

void Thirst::update() {
	mCurrentLevel = std::clamp<short>(mCurrentLevel + static_cast<short>(mChangeRate * 12), mMinLevel, mMaxLevel);
}

bool Thirst::isCritical() {
	return mCurrentLevel > static_cast<short>(mCriticalRate * mMaxLevel);
}


Hungry::Hungry(short currentLevel, short maxLevel, short minLevel, float changeRate, float criticalRate) :
	Need(currentLevel, maxLevel, minLevel, changeRate, criticalRate)
{
}

void Hungry::update() {
	mCurrentLevel = std::clamp<short>(mCurrentLevel + static_cast<short>(mChangeRate * 12), mMinLevel, mMaxLevel);
}

bool Hungry::isCritical() {
	return mCurrentLevel > static_cast<short>(mCriticalRate * mMaxLevel);
}


Stamina::Stamina(short currentLevel, short maxLevel, short minLevel, float changeRate, float criticalRate) :
	Need(currentLevel, maxLevel, minLevel, changeRate, criticalRate)
{
}

void Stamina::update() {
	mCurrentLevel = std::clamp<short>(mCurrentLevel - static_cast<short>(mChangeRate * 12), mMinLevel, mMaxLevel);
}

bool Stamina::isCritical() {
	return mCurrentLevel < static_cast<short>(mCriticalRate * mMaxLevel);
}


Bleading::Bleading(short currentLevel, short maxLevel, short minLevel, float changeRate, float criticalRate) :
	Need(currentLevel, maxLevel, minLevel, changeRate, criticalRate)
{
}

void Bleading::update() {
	mCurrentLevel = std::clamp<short>(mCurrentLevel - static_cast<short>(mChangeRate * 12), mMinLevel, mMaxLevel);
}

bool Bleading::isCritical() {
	return mCurrentLevel > static_cast<short>(mCriticalRate * mMaxLevel);
}


Exhaustion::Exhaustion(short currentLevel, short maxLevel, short minLevel, float changeRate, float criticalRate) :
	Need(currentLevel, maxLevel, minLevel, changeRate, criticalRate)
{
}

void Exhaustion::update() {
	mCurrentLevel = std::clamp<short>(mCurrentLevel - static_cast<short>(mChangeRate * 12), mMinLevel, mMaxLevel);
}

bool Exhaustion::isCritical() {
	return mCurrentLevel > static_cast<short>(mCriticalRate * mMaxLevel);
}
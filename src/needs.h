#pragma once

#include <algorithm>

class Need {
public:
	Need(short currentLevel, short maxLevel = 100, short minLevel = 0, float changeRate = 1.3f, float criticalRate = 0.8f) :
		mCurrentLevel(currentLevel),
		mMaxLevel(maxLevel),
		mMinLevel(minLevel),
		mChangeRate(changeRate),
		mCriticalRate(criticalRate)
	{
	}

	virtual void update() = 0;
	virtual bool isCritical() = 0;

	virtual ~Need() = default;
protected:
	short mCurrentLevel = 0;	//текущий уровень
	short mMaxLevel = 0;	//верхний предел
	short mMinLevel = 0;	//нижний предел
	float mChangeRate = 0.f;	//модификатор изменения
	float mCriticalRate = 0.f;	//модификатор изменения
};

class Thirst : public Need {
public:
	Thirst(short currentLevel, short maxLevel = 100, short minLevel = 0, float changeRate = 1.8f, float criticalRate = 0.8f) :
		Need(currentLevel, maxLevel, minLevel, changeRate, criticalRate)
	{
	}

	void update() override {
		mCurrentLevel = std::clamp<short>(mCurrentLevel + static_cast<short>(mChangeRate * 12), mMinLevel, mMaxLevel);
	}

	bool isCritical() override {
		return mCurrentLevel > static_cast<short>(mCriticalRate * mMaxLevel);
	}

	Thirst() = default;
};

class Hungry : public Need {
public:
	Hungry(short currentLevel, short maxLevel = 100, short minLevel = 0, float changeRate = 1.3f, float criticalRate = 0.8f) :
		Need(currentLevel, maxLevel, minLevel, changeRate, criticalRate)
	{
	}

	void update() override {
		mCurrentLevel = std::clamp<short>(mCurrentLevel + static_cast<short>(mChangeRate * 12), mMinLevel, mMaxLevel);
	}

	bool isCritical() override {
		return mCurrentLevel > static_cast<short>(mCriticalRate * mMaxLevel);
	}

	Hungry() = default;
};

class Stamina : public Need {
public:
	Stamina(short currentLevel, short maxLevel = 100, short minLevel = 0, float changeRate = 1.7f, float criticalRate = 0.1f) :
		Need(currentLevel, maxLevel, minLevel, changeRate, criticalRate)
	{
	}

	void update() override {
		mCurrentLevel = std::clamp<short>(mCurrentLevel - static_cast<short>(mChangeRate * 12), mMinLevel, mMaxLevel);
	}

	bool isCritical() override {
		return mCurrentLevel < static_cast<short>(mCriticalRate * mMaxLevel);
	}

	Stamina() = default;
};
#pragma once


class Need {
public:
	Need(short currentLevel, short maxLevel = 100, short minLevel = 0, float changeRate = 1.3f, float criticalRate = 0.8f);

	virtual void update() = 0;
	virtual bool isCritical() = 0;
	short getValue() { return mCurrentLevel;}

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
	Thirst(short currentLevel, short maxLevel = 100, short minLevel = 0, float changeRate = 1.8f, float criticalRate = 0.8f);

	void update() override;

	bool isCritical() override;

	Thirst() = default;
};

class Hungry : public Need {
public:
	Hungry(short currentLevel, short maxLevel = 100, short minLevel = 0, float changeRate = 1.3f, float criticalRate = 0.8f);

	void update() override;

	bool isCritical() override;

	Hungry() = default;
};

class Stamina : public Need {
public:
	Stamina(short currentLevel, short maxLevel = 100, short minLevel = 0, float changeRate = 1.7f, float criticalRate = 0.1f);

	void update() override;

	bool isCritical() override;

	Stamina() = default;
};

class Bleading : public Need {
public:
	Bleading(short currentLevel, short maxLevel = 100, short minLevel = 0, float changeRate = 1.7f, float criticalRate = 0.1f);

	void update() override;

	bool isCritical() override;

	Bleading() = default;
};

class Exhaustion : public Need {
public:
	Exhaustion(short currentLevel, short maxLevel = 100, short minLevel = 0, float changeRate = 1.7f, float criticalRate = 0.1f);

	void update() override;

	bool isCritical() override;

	Exhaustion() = default;
};
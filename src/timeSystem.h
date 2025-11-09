#pragma once


class TimeSystem
{
public:
	TimeSystem() {}

	bool increaseByMinutes(float& deltaMinutes);
	std::string show() const;

private:
	unsigned short int mMinutes = 43;
	unsigned short int mHours = 6;
	unsigned short int mDays = 29;
	unsigned short int mMonths = 6;
	unsigned short int mYears = 1991;
	unsigned short int mDeltaTime = 0;

	unsigned short int mTicksPerSecond = 75;
	bool mHourPassed = false;
};

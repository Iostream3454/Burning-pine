#pragma once


class TimeSystem
{
public:
	TimeSystem() {}

	void increaseByMinutes(float& deltaMinutes);
	std::string show();

private:
	unsigned short int mMinutes = 0;
	unsigned short int mHours = 0;
	unsigned short int mDays = 0;
	unsigned short int mMonths = 0;
	unsigned short int mYears = 0;
	unsigned short int mDeltaTime = 0;

	unsigned short int mTicksPerSecond = 100;
};

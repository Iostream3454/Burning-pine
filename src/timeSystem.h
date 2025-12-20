#pragma once


class TimeSystem
{
public:
	TimeSystem() {}

	bool increaseByMinutes(float& deltaMinutes);
	std::string show() const;

private:
	unsigned short int	mMinutes		= 43;		//минуты
	unsigned short int	mHours			= 6;		//часы
	unsigned short int	mDays			= 29;		//дни
	unsigned short int	mMonths			= 6;		//мес€цы
	unsigned short int	mYears			= 1991;		//годы
	unsigned short int	mDeltaTime		= 0;		//дельта времени от тпс

	unsigned short int	mTicksPerSecond = 75;		//модификатор прироста времени
	bool				mHourPassed		= false;
};

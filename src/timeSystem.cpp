#include <string>
#include "timeSystem.h"

bool TimeSystem::increaseByMinutes(float& deltaMinutes) {
	mDeltaTime += static_cast<unsigned short>(deltaMinutes * mTicksPerSecond);
	if (mDeltaTime < 1.f) return false;

	unsigned short deltaInMinutes = mDeltaTime;
	mDeltaTime	-= deltaInMinutes;

	mMinutes	+= deltaInMinutes;
	if (mMinutes / 60 > 0) mHours += mMinutes / 60, mHourPassed = true;
	else mHourPassed = false;
	mDays		+= mHours / 24;
	mMonths		+= mDays / 30;
	mYears		+= mMonths / 12;

	mMinutes	 = mMinutes % 60;
	mHours		 = mHours %  24;
	mDays		 = mDays % 30;
	mMonths		 = mMonths % 12;

	/*if (mMinutes > 59) {
		++mHours;
		mMinutes %= 60;
		if (mHours > 24) {
			++mDays;
			mDays %= 24;
			if (mDays > 30) {
				++mMonths;
				mMonths %= 30;
				if (mMonths > 12) {
					++mYears;
					mMonths %= 12;
				}
			}
		}
	}*/
	return mHourPassed;
}

std::string TimeSystem::show() const {
	return  std::to_string(mHours) + " : " + std::to_string(mMinutes) + '\n' + std::to_string(mDays) + "." + std::to_string(mMonths) + "." + std::to_string(mYears);
}
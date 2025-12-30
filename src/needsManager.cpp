#include "needsManager.h"

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

void NeedsManager::addNeed(const std::string needName, std::unique_ptr<Need> need) {
	mListOfNeeds.insert({ needName ,std::move(need) });
}

unsigned short NeedsManager::getNeedValue(const std::string& needName) { return mListOfNeeds.find(needName)->second->getValue(); }

void NeedsManager::update() {
	for (auto& var : mListOfNeeds)
	{
		var.second->update();
	}
}
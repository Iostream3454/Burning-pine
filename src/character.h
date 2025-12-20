#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "camera.h"
#include "needsManager.h"
#include "movementSystem.h"
#include "arrowBuilder.h"
#include "shapeTypes.h"



class MainCharacter final : public sf::Drawable, public sf::Transformable
{
public:

	MainCharacter();

	
	bool getIsDoSomthing() const;
	void commandToMove();

	void trySleep();

	void updateState(float& dt, bool timeStepIsPass);

	void setPositionGoal(sf::Vector2f& goalPosition);

	void zoomCamera(const float wheelDelta);

	NeedsManager& getBody();

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	MovementSystem	mMovement;								//модуль дл€ передвижени€ объекта
	CircleType		mCirclePresent;
	ArrowLineSystem mLineBuilder;							//строитель линий со стрелкой
	Camera			mPlayerCamera;							//камера игрока
	NeedsManager	mPersonBody;							//тело персонажа

	bool			mIs_doSomthing				= false;
};
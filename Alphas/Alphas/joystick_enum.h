#pragma once
#include <SFML/Window/Joystick.hpp>

enum class JoystickButton
{
	A = sf::Joystick::X,
	B = sf::Joystick::Y,
	X = sf::Joystick::Z,
	Y = sf::Joystick::R,
	LB = sf::Joystick::U,
	RB = sf::Joystick::V,
	START = sf::Joystick::PovY,
	BACK = sf::Joystick::PovX
};

enum class JoystickPad {
	LEFT_X = sf::Joystick::X,
	LEFT_Y = sf::Joystick::Y,
	RIGHT_X = sf::Joystick::U,
	RIGHT_Y = sf::Joystick::V,
	LT = sf::Joystick::Z,
	RT = sf::Joystick::Z
};
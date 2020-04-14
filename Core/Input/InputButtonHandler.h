#pragma once

#include <unordered_map>

namespace DonkeyKong
{
	enum class ButtonName { Move_Left, Move_Right, Jump, Climb_Up, Climb_Down };

	class InputButtonHandler
	{
	public:
		InputButtonHandler();
		virtual ~InputButtonHandler() = default;
		virtual void UpdateStatus() = 0;

		static const bool IsButtonPressed(const ButtonName buttonName);

	protected:
		static std::unordered_map<ButtonName, bool> buttonPressed;
	};
}
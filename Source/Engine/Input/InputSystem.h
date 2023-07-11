#pragma once
#include <vector>
#include <array>
#include "Core/Vector2.h"
#include <SDL2-2.28.1/include/SDL.h>


namespace kiko
{
	class InputSystem
	{
	public:
		InputSystem() = default;
		~InputSystem() = default;

		bool Initialize();
		void Shutdown();

		void Update(); //??? problems with this initializing in main\

		bool GetKeyDown(uint32_t key) const { return m_keyboardState[key];  }
		bool GetPreviousKeyDown(uint32_t key) const { return m_prevKeyBoardState[key];  }

		const Vector2& GetMousePosition() const { return m_mousePosition; }

		bool GetMouseButtonDown(uint32_t button) { return m_mouseButtonState[button]; }
		bool GetMousePreviousButtonDown(uint32_t button) { return m_prevMouseButtonState[button]; }

	private:
		std::vector<uint8_t> m_keyboardState;
		std::vector<uint8_t> m_prevKeyBoardState;
	
		kiko::Vector2 m_mousePosition;
		std::array<uint8_t, 3> m_mouseButtonState;
		std::array<uint8_t, 3> m_prevMouseButtonState;

		
	};

}
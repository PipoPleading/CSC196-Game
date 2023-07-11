#include "InputSystem.h"

namespace kiko
{
	bool InputSystem::Initialize()
	{
		int numKeys;
		// get pointer to sdl keyboard states and number of keys
		const uint8_t* keyboardState = SDL_GetKeyboardState(&numKeys);

		//resize of keyboard state vector using numKeys for size
		m_keyboardState.resize(numKeys);

		// copy the sdl states to keyboard state
		std::copy(keyboardState, keyboardState + numKeys, m_keyboardState.begin());

		//set the previous keyboard sttate to current keyboard state
		

		return true;
	}
	void InputSystem::Shutdown()
	{
		//
	}
	void InputSystem::Update()
	{
		// update sdl events
		SDL_Event event;
		SDL_PollEvent(&event);

		//save previous keyboard state
		m_prevKeyBoardState = m_keyboardState;

		// get sdl keyboard state
		const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
		// copy sdl keyboard state to input system keyboard state
		std::copy(keyboardState, keyboardState + m_keyboardState.size(), m_keyboardState.begin());

		int x, y;
		uint32_t buttons = SDL_GetMouseState(&x, &y);
		m_prevMouseButtonState = m_mouseButtonState;
		m_mouseButtonState[0] = buttons & SDL_BUTTON_LMASK;
		m_mouseButtonState[1] = buttons & SDL_BUTTON_MMASK;
		m_mouseButtonState[2] = buttons & SDL_BUTTON_RMASK;
	}


}
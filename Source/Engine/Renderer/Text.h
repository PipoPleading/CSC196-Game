#pragma once
#include "Renderer.h"
#include "Font.h"
#include "Core/Color.h"
#include <string>
#include <memory>
namespace kiko
{
	class Text
	{
	public:
		//<create a default constructor>
		Text() = default;
		Text(std::shared_ptr<Font> font) : m_font{ font } { }
		
			//Text(<a shared pointer of Font type> font) : m_font{ font } { }
		~Text();
		void Create(Renderer& renderer, const std::string& text, const Color& color);
		void Draw(Renderer& renderer, int x, int y);
	private:
		std::shared_ptr<Font> m_font;
		struct SDL_Texture* m_texture = nullptr;
	};
}

//Make the Text class a friend of the Font class.This will give the Text class access to the private m_ttfFont
//member.
//Make the Text class a friend of the Renderer class.This will give the Text class access to the private
//m_renderer member


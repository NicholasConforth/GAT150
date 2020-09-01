#pragma once
#include "Math/Vector2.h"
#include "Resources/Resource.h"
#include <SDL.h>
#include <string>

namespace nc
{
	class Texture : public Resource
	{
	public:
		bool Create(const std::string& name, void* renderer) override;
		void Destroy() override;

		void Draw(const Vector2& position, float angle, const Vector2& scale, const Vector2& origin, bool flip = false);
		void Draw(const SDL_Rect& source, const Vector2& position, float angle, const Vector2& scale, const Vector2& origin, bool flip = false);
		Vector2 GetSize();
	private:
		SDL_Texture* m_texture{ nullptr };
		SDL_Renderer* m_renderer{ nullptr };
	};
}
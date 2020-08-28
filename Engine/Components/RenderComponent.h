#pragma once
#include "Components/Component.h"

namespace nc
{
	class RenderComponent : public Component
	{
	public:
		virtual void Draw() = 0;
	};
}
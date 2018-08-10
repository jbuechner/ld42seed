#pragma once

#include <memory>

#include "ld42m/engine/aloo/drawable.h"

namespace engine
{
	namespace drawables
	{
		class fps_counter : public engine::aloo::drawable
		{
		};

		std::shared_ptr<fps_counter> create_fps_counter();
	}
}
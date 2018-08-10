#pragma once

#include <memory>

#include "ld42m/engine/aloo/drawable.h"

namespace engine
{
	namespace drawables
	{
		class stage : public engine::aloo::drawable
		{
		};

		std::shared_ptr<stage> create_stage();
	}
}
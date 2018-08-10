#pragma once

#include <memory>

namespace engine
{
	namespace aloo
	{
		class environment
		{
		protected:
			virtual ~environment() {};
		};

		std::shared_ptr<environment> create_environment();
	}
}
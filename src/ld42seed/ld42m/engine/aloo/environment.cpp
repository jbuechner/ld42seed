#include "pch_allegro.h"
#pragma hdrstop

#include "environment.h"

namespace
{
	using namespace engine::aloo;

	void void_fn()
	{
	}

	template <bool init()>
	class al_system
	{
	public:
		al_system(std::string const& initialization_error_msg)
		{
			if (!init())
			{
				throw std::exception{ initialization_error_msg.c_str() };
			}
		}
	};

	class environment_internal : public environment
	{
	public:
		~environment_internal()
		{
			al_shutdown_ttf_addon();
			al_shutdown_font_addon();
			al_shutdown_primitives_addon();

		}
		environment_internal()
		{
			bool success = al_init();
			_ASSERT(success);
			if (!success)
			{
				throw std::exception{ "unable to initialize allegro." };
			}

			al_system<&al_init_primitives_addon>{ "unable to initializes primitives addon." };
			al_system<&al_init_font_addon>{ "unable to initializes font addon." };
			al_system<&al_init_ttf_addon>{ "unable to initializes ttf addon." };

		}
	};
}

namespace engine
{
	namespace aloo
	{
		std::shared_ptr<environment> create_environment()
		{
			return std::make_shared<environment_internal>();
		}
	}
}
#include "pch_allegro.h"
#pragma hdrstop

#include <atomic>
#include <thread>
#include <chrono>

#include "ld42m/engine/aloo/environment.h"
#include "ld42m/engine/aloo/font_manager.h"
#include "ld42m/engine/aloo/keyboard.h"
#include "ld42m/engine/aloo/display.h"
#include "ld42m/engine/aloo/display_loop.h"
#include "ld42m/engine/drawables/stage.h"
#include "ld42m/engine/drawables/fps_counter.h"
#include "ld42m/engine/drawables/label.h"

#include "app.h"

namespace
{
	using namespace engine::aloo;
	using namespace engine::drawables;

	class app_internal : public engine::app
	{
	public:
		app_internal()
		{
			_keyboard = std::move(create_keyboard(_environment));
			_display = std::move(create_display(_environment));
		}

	private:
		void run_and_wait_internal() const override
		{
			auto& display = *_display;
			auto loop = display.create_loop();

			auto const defaultFont = _environment->get_font_manager()->get_font({ "hack-regular.ttf" }, 14);

			auto stage = create_stage();
			loop->set_root_drawable(stage);
			stage->append(create_fps_counter(defaultFont));

			std::shared_ptr<label> label{ nullptr };;
			stage->append(label = create_label());
			label->set_font(defaultFont);

			label->set_text("Hallo");

			while ((*loop)() && _continueRendering.load())
			{
				_keyboard->process_events();
				// todo: less stupid key handling required
				if (_keyboard->is_key_down(ALLEGRO_KEY_ESCAPE))
				{
					_continueRendering.store(false);
				}
			}
		}

		mutable std::atomic<bool> _continueRendering { true };
		std::shared_ptr<environment> const _environment{ std::move(create_environment()) };
		std::shared_ptr<display> _display{ nullptr };
		std::shared_ptr<keyboard> _keyboard{ nullptr };
	};
}

namespace engine
{
	std::shared_ptr<app> create_app()
	{
		return std::move(std::make_shared<app_internal>());
	}
}
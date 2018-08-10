#include "pch_allegro.h"
#pragma hdrstop

#include <memory>

#include "ld42m/engine/aloo/utils.h"
#include "ld42m/engine/aloo/draw_context.h"
#include "ld42m/engine/aloo/font.h"
#include "ld42m/os/os.h"

#include "details/drawables_parental.h"

#include "fps_counter.h"

namespace
{
	using namespace engine::aloo;
	using namespace engine::drawables;

	class fps_counter_internal : public fps_counter
	{
	public:
		fps_counter_internal(std::shared_ptr<font> const& font)
			: _font{ font }
		{
		}
	private:
		void draw_internal(draw_context& context) override
		{
			al_draw_text(static_cast<ALLEGRO_FONT*>(_font->get_native_ptr()), al_map_rgb(0xff, 0xff, 0xff), 5, 5, allegro_draw_text_flags(), &context.fps_as_string()[0]);
		}

		bool draw_requested_internal(draw_context& context) const override
		{
			return std::get<0>(context.fps_measure_result());
		}

		std::weak_ptr<drawable>& parent_internal() override
		{
			return _parental.parent();
		}

		engine::drawables::details::drawables_parental<fps_counter_internal> _parental{};
		std::shared_ptr<font> const _font;
	};
}

namespace engine
{
	namespace drawables
	{
		std::shared_ptr<fps_counter> create_fps_counter(std::shared_ptr<font> const& font)
		{
			return std::make_shared<fps_counter_internal>(font);
		}
	}
}
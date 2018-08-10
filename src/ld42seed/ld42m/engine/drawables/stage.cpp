#include "pch_allegro.h"
#pragma hdrstop

#include <memory>

#include "ld42m/engine/aloo/display.h"
#include "ld42m/engine/aloo/render_texture.h"
#include "ld42m/engine/aloo/draw_context.h"

#include "details/drawables_hierarchical.h"

#include "stage.h"

namespace
{
	using namespace engine::aloo;
	using namespace engine::drawables;

	class stage_internal : public stage, public std::enable_shared_from_this<stage_internal>
	{
	public:
		stage_internal()
			: _hierarchical { *this }
		{
		}

	private:
		bool draw_requested_internal(draw_context& context) const override
		{
			for (auto const& child : _hierarchical.children())
			{
				if (child->draw_requested(context))
				{
					return true;
				}
			}

			return false;
		}

		void draw_internal(draw_context& context) override
		{
			auto& display = context.get_display();
			auto& backbuffer = display->get_backbuffer();

			{
				auto const target = backbuffer.make_render_target();

				for (auto& child : _hierarchical.children())
				{
					child->draw(context);
				}
			}

			if (display->backbuffer_and_frontbuffer_are_perfect())
			{
				al_draw_bitmap(reinterpret_cast<ALLEGRO_BITMAP*>(backbuffer.get_native_ptr()), 0, 0, 0);
			}
			else
			{
				auto const& sourceSize = display->backbuffer_size();
				auto const& targetSize = display->display_size();
				al_draw_scaled_bitmap(reinterpret_cast<ALLEGRO_BITMAP*>(backbuffer.get_native_ptr()), 0, 0, sourceSize.x, sourceSize.y, 0, 0, targetSize.x, targetSize.y, 0);
			}
		}

		std::weak_ptr<drawable>& parent_internal() override
		{
			return _hierarchical.parent();
		}

		std::list<std::shared_ptr<drawable>> const& children_internal() const
		{
			return _hierarchical.children();
		}

		void append_internal(std::shared_ptr<drawable> const& drawable) override
		{
			_hierarchical.append(drawable);
		}

	private:
		engine::drawables::details::drawables_hierarchical<stage_internal> _hierarchical;
	};
}

namespace engine
{
	namespace drawables
	{
		std::shared_ptr<stage> create_stage()
		{
			return std::make_shared<stage_internal>();
		}
	}
}
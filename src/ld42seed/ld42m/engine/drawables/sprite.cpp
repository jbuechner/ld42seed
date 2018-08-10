#include "pch_allegro.h"
#pragma hdrstop

#include "ld42m/engine/aloo/render_texture.h"

#include "sprite.h"

namespace
{
	using namespace engine::aloo;
	using namespace engine::drawables;

	class sprite_internal : public sprite, std::enable_shared_from_this<sprite_internal>
	{
	private:
		virtual void draw_internal(draw_context& context) override
		{
			if (_texture)
			{
				al_draw_tinted_bitmap_region(reinterpret_cast<ALLEGRO_BITMAP*>(_texture->get_native_ptr()), _tint, _source_region.x, _source_region.y, _source_region.z, _source_region.w, _position.x, _position.y, 0);
			}
			_is_dirty = false;
		}

		std::weak_ptr<drawable>& parent_internal() override
		{
			return _parent;
		}

		virtual bool draw_requested_internal(draw_context& context) const override
		{
			return _is_dirty;
		}

		void set_render_texture_internal(std::shared_ptr<render_texture> const& texture) override
		{
			_texture = texture;
			_is_dirty = true;
		}

		void set_position_internal(glm::vec2 const& position) override
		{
			_position = position;
			_is_dirty = true;
		}

		void set_source_region_internal(glm::vec4 const& region) override
		{
			_source_region = region;
			_is_dirty = true;
		}

		void set_tint_internal(glm::lowp_vec4 const& color) override
		{
			_tint.r = color.r;
			_tint.g = color.g;
			_tint.b = color.b;
			_tint.a = color.a;
			_is_dirty = true;
		}

		ALLEGRO_COLOR _tint{ al_map_rgba(0xff, 0xff, 0xff, 0xff) };
		glm::vec2 _position{};
		glm::vec4 _source_region{ 0, 0, 0, 0 };
		std::weak_ptr<drawable> _parent{};
		bool _is_dirty{ false };
		std::shared_ptr<render_texture> _texture{ nullptr };
	};
}

namespace engine
{
	namespace drawables
	{
		std::shared_ptr<sprite> create_sprite()
		{
			return std::move(std::make_shared<sprite_internal>());
		}
	}
}
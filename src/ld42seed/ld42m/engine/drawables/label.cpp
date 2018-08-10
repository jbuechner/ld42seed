#include "pch_allegro.h"
#pragma hdrstop

#include "ld42m/os/os.h"
#include "ld42m/engine/aloo/utils.h"
#include "ld42m/engine/aloo/font.h"

#include "details/drawables_parental.h"

#include "label.h"

namespace
{
	using namespace engine::aloo;
	using namespace engine::drawables;

	class label_internal : public label, std::enable_shared_from_this<label_internal>
	{
	public:
		label_internal()
		{
			auto const filePath = os::get_process_module_path() / "hack-regular.ttf";
			_font = std::move(create_font(filePath, 14));
		}
	private:
		virtual bool draw_requested_internal(draw_context& context) const override
		{
			return _is_dirty;
		}

		virtual void draw_internal(draw_context& context) override
		{
			al_draw_text(reinterpret_cast<ALLEGRO_FONT*>(_font->get_native_ptr()), _color, _position.x, _position.y, allegro_draw_text_flags(), _text.c_str());
			_is_dirty = false;
		}

		virtual std::weak_ptr<drawable>& parent_internal() override
		{
			return _parental.parent();
		}

		void set_text_internal(std::string&& text) override
		{
			_text = std::move(text);
		}

		void set_position_internal(glm::vec2 const& position) override
		{
			_position = position;
			_is_dirty = true;
		}

		ALLEGRO_COLOR _color{ al_color_name("white") };
		bool _is_dirty{ true };
		std::string _text{};
		engine::drawables::details::drawables_parental<label_internal> _parental{};
		std::shared_ptr<font> _font{ nullptr };
		glm::vec2 _position{};
	};
}

namespace engine
{
	namespace drawables
	{
		std::shared_ptr<label> create_label()
		{
			return std::make_shared<label_internal>();
		}
	}
}
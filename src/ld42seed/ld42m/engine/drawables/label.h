#pragma once

#include <memory>

#include "ld42m/engine/aloo/drawable.h"

namespace engine
{
	namespace aloo
	{
		class font;
	}

	namespace drawables
	{
		class label : public engine::aloo::drawable
		{
		public:
			virtual ~label() {}

			inline void set_text(std::string&& text)
			{
				set_text_internal(std::move(text));
			}

			inline void set_font(std::shared_ptr<aloo::font> const& font)
			{
				set_font_internal(font);
			}
		private:
			virtual void set_text_internal(std::string&& text) = 0;
			virtual void set_font_internal(std::shared_ptr<aloo::font> const& font) = 0;
		};

		std::shared_ptr<label> create_label();
	}
}
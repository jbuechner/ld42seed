#pragma once

#include <memory>

#include "ld42m/engine/aloo/drawable.h"

namespace engine
{
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
		private:
			virtual void set_text_internal(std::string&& text) = 0;
		};

		std::shared_ptr<label> create_label();
	}
}
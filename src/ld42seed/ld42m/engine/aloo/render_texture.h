#pragma once

#include <memory>

#include "render_target_op.h"

namespace engine
{
	namespace aloo
	{
		enum class render_texture_flags
		{
			memory = 1,
			no_preserve = 8,
			alpha_test = 16,
			min_linear = 64,
			mag_linear = 128,
			mipmap = 256,
			video = 1024,
			convert = 4096
		};

		enum class render_texture_format
		{
			best = 0,
			abgr_8888_le = 25
		};

		class render_texture_lock_op;
		class render_target_op;

		class render_texture
		{
		public:
			inline void* get_native_ptr() const
			{
				return get_native_ptr_internal();
			}

			inline std::shared_ptr<render_texture_lock_op> lock()
			{
				return lock_internal();
			}

			inline render_target_op make_render_target() const
			{
				return std::move(make_render_target_internal());
			}

			inline std::shared_ptr<render_texture> make_hardware_texture() const
			{
				return std::move(make_hardware_texture_internal());
			}
		protected:
			virtual ~render_texture() {};
		private:
			virtual void* get_native_ptr_internal() const = 0;
			virtual std::shared_ptr<render_texture_lock_op> lock_internal() = 0;
			virtual render_target_op make_render_target_internal() const = 0;
			virtual std::shared_ptr<render_texture> make_hardware_texture_internal() const = 0;
		};

		std::shared_ptr<render_texture> create_render_texture(size_t const& width, size_t const& height, render_texture_flags const& flags, render_texture_format const& format);
	}
}
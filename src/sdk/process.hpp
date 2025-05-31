#pragma once

#include <string_view>
#include <optional>
#include <cstddef>
#include <cstdint>
#include <span>
#include <stdexcept>
#include <utility>
#include <type_traits>

#include <libhat/scanner.hpp>

#ifdef SELAURA_WINDOWS
#include <Windows.h>
#include <Psapi.h>
#include <string>
#include <string_view>
#else
#include <dlfcn.h>
#include <link.h>
#endif

namespace selaura {
	struct process {
		std::byte* base;
		std::size_t size;

		void* native;

		std::byte* get_process_base();
		std::size_t get_process_size();
	};

	process get_process_handle();
}
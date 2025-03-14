#pragma once
#include <source_location>

namespace utils::source
{
    const char* function(std::source_location source = std::source_location::current());
    const char* filename(std::source_location source = std::source_location::current());
}

#include "source-utils.h"

#include <cstring>
#include <filesystem>

namespace utils::source
{
    const char* filename(std::source_location source)
    {
        return strrchr(source.file_name(), std::filesystem::path::preferred_separator) + 1;
    }

    const char* function(std::source_location source)
    {
        return source.function_name();
    }
}
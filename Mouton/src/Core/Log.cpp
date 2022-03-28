#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Mouton {
    std::shared_ptr<spdlog::logger> Log::s_Logger;

    void Log::Init()
    {
        auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        sink->set_pattern("%^[%H:%M:%S] %n %l : %v%$");

        s_Logger = std::make_shared<spdlog::logger>("Mouton", sink);

        spdlog::register_logger(s_Logger);
        s_Logger->set_level(spdlog::level::trace);
        s_Logger->flush_on(spdlog::level::trace);
    }

} // namespace Mouton
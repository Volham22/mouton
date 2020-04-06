#ifndef LOG_H
#define LOG_H

#include <memory>

#include <spdlog/spdlog.h>

namespace Mouton
{

    class Log
    {
    public:
        static void Init();
        static inline std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; };
    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
    };

}

#define MTN_TRACE(...) ::Mouton::Log::GetLogger()->trace(__VA_ARGS__);
#define MTN_INFO(...)  ::Mouton::Log::GetLogger()->info(__VA_ARGS__);
#define MTN_WARN(...)  ::Mouton::Log::GetLogger()->warn(__VA_ARGS__);
#define MTN_ERROR(...) ::Mouton::Log::GetLogger()->error(__VA_ARGS__);
#define MTN_FATAL(...) ::Mouton::Log::GetLogger()->critical(__VA_ARGS__);

#endif
#ifndef LOG_H
#define LOG_H

#include <memory>

#include <spdlog/spdlog.h>

namespace Mouton {

    class Log
    {
      public:
        static void Init();
        static inline std::shared_ptr<spdlog::logger>& GetLogger()
        {
            return s_Logger;
        };

      private:
        static std::shared_ptr<spdlog::logger> s_Logger;
    };

} // namespace Mouton

#define MTN_TRACE(...) ::Mouton::Log::GetLogger()->trace(__VA_ARGS__);
#define MTN_INFO(...)  ::Mouton::Log::GetLogger()->info(__VA_ARGS__);
#define MTN_WARN(...)  ::Mouton::Log::GetLogger()->warn(__VA_ARGS__);
#define MTN_ERROR(...) ::Mouton::Log::GetLogger()->error(__VA_ARGS__);
#define MTN_FATAL(...) ::Mouton::Log::GetLogger()->critical(__VA_ARGS__);

#define MTN_ASSERT(x, ...) \
    if (!x) \
        MTN_ERROR( \
            "Assertion Failed at {0} : {1} with the following message : {2}", \
            __FILE__, __LINE__, __VA_ARGS__);

#endif
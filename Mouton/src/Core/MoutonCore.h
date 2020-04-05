/*
 * Mouton Core header
 * Includes all Mouton requirements
 */

// Platform check
#ifdef _WIN32
    #define MTN_PLATFORM WIN32
    #error Windows is not supported !
#elif defined(__APPLE__)
    #define MTN_PLATFORM MACOS
    #error Macos is not supported
#elif defined(__linux__)
    #define MTN_PLATFORM LINUX
#else
    #defined MTN_PLATFORM UNKNOWN
    #error Build platform unknown !
#endif


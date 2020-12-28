#ifndef STRING_HASH_H
#define STRING_HASH_H

#include "MoutonPch.h"

namespace Mouton::Utils
{

    class StringHash
    {
    public:
        // Hash Functions from the following question on StackOverflow
        // https://stackoverflow.com/questions/48896142/is-it-possible-to-get-hash-values-as-compile-time-constants
        template <typename Str>
        static constexpr size_t HashString(const Str& toHash)
        {
            // For this example, I'm requiring size_t to be 64-bit, but you could
            // easily change the offset and prime used to the appropriate ones
            // based on sizeof(size_t).
            static_assert(sizeof(size_t) == 8);
            // FNV-1a 64 bit algorithm
            size_t result = 0xcbf29ce484222325; // FNV offset basis

            for (char c : toHash) {
                result ^= c;
                result *= 1099511628211; // FNV prime
            }

            return result;
        }

        template <size_t N>
        static constexpr size_t HashString(char const (&toHash)[N])
        {
            return HashString(std::string_view(toHash));
        }
    };

} // namespace Mouton::Utils


#endif
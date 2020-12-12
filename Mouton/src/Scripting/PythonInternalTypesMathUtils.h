#ifndef PYTHON_INTERNAL_TYPE_MATH_H
#define PYTHON_INTERNAL_TYPE_MATH_H

#include "MoutonPch.h"

namespace Mouton
{
    template<typename T>
    struct Ret;

    // Retrieve type of function pointer
    template<typename T, typename... Args>
    struct Ret<T(*)(Args...)> {
        using type = T;
    };

    class PythonInternalMath
    {
    public:
        template<
            typename Func,
            typename Return = typename Ret<Func>::type,
            typename... Args
        >
        static Return CallFunction(const Func& call, Args... args)
        {
            return call(args...);
        }
    };

} // namespace Mouton


#endif
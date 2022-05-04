#ifndef UTIL_FUNC_H
#define UTIL_FUNC_H

template<class X, class M>
inline X clamp(X x, M min, M max)
{
    if (x < min)
    {
        return min;
    }
    else if (x > max)
    {
        return max;
    }
    else
    {
        return x;
    }
}

#endif
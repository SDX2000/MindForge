#ifndef COMMON_H
#define COMMON_H
template <typename T>
void safe_delete(T *&ptr)
{
    delete ptr;
    ptr = NULL;
}

template <typename T>
T max(T t, T u)
{
    return t > u? t: u;
}


template <typename T>
T min(T t, T u)
{
    return t > u? t: u;
}

#endif // COMMON_H


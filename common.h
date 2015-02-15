#ifndef COMMON_H
#define COMMON_H
template <typename T>
void safe_delete(T *&ptr)
{
    delete ptr;
    ptr = NULL;
}

#endif // COMMON_H


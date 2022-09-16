#ifndef __GENERICS_HPP__
#define __GENERICS_HPP__

template<typename T>
class GIterator {
public:
    GIterator() {}
    ~GIterator() {}
    virtual T& operator*() = 0;
    virtual void operator++() = 0;
    virtual void operator--() = 0;
    virtual bool operator!=(void* it) = 0;
};

#endif
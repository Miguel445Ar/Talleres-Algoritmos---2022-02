#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <functional>
#include <vector>

#define __VERSION__ 2


namespace AED {
    #if __VERSION__ == 1
        template<class T>
        class Vector {
        public:
            Vector();
            ~Vector();
            Vector(size_t size);
            void pushBack(T value);
            void popBack();
            void insertAt(T value, size_t pos);
            void eraseAt(size_t pos);
            void resize(size_t newSize);
            T& operator[](size_t index); // arr[i]
        private:
            size_t _size;
            T* _arr;
        private:
            bool _isFull();
            void _resize();
        };
    #endif
    #if __VERSION__ == 2
        template<class T>
        class Vector {
            using DeleterFunc = void (*)(T);
        public:
            Vector(DeleterFunc = nullptr);
            ~Vector();
            Vector(size_t size,void (*deleter)(T) = nullptr);
            void pushBack(T value);
            void popBack();
            void insertAt(T value, size_t pos);
            void eraseAt(size_t pos);
            void resize(size_t newSize);
            T& operator[](size_t index);
        private:
            struct Entity {
                T value;
                DeleterFunc deleter;
                Entity(T value, DeleterFunc = nullptr): value(value), deleter(deleter) {}
                ~Entity();
            };
            size_t _size;
            Entity** _arr;
            DeleterFunc deleter;
        private:
            bool _isFull();
            void _resize();
        };
    #endif
}
#endif
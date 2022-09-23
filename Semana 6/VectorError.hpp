
template<class T>
class Vector {
    using DeleterFunc = void (*)(T); // Podríamos usar std::function
public:
    Vector(DeleterFunc deleter = nullptr): _deleter(deleter) {
        this->_arr = nullptr;
        _capacity = _size = 0;
    }
    ~Vector() {
        for(size_t i = 0ll; i < _size; ++i) {
            if(this->_deleter) _deleter(_arr[i]);
        }
        delete[] _arr;
    }
    Vector(size_t size, DeleterFunc deleter = nullptr): _arr(new T[size]), _capacity(size), _size(size) {}
    void pushBack(T value) {
        if(_isEmpty() || _isFull()) _resize();
        this->_arr[_size++] = value;
    }
    void popBack() {
        if(_isEmpty()) throw "Vector is empty :(";
        if(_deleter) _deleter(this->_arr[_size - 1]);
        --_size;
    }
    void insertAt(T value, size_t pos) {

    }
    void eraseAt(size_t pos) {

    }
    void resize(size_t newSize) {
        T* newArr = new T[newSize];
        for(size_t i = 0ll; i < _size; ++i)
            newArr[i] = _arr[i];
        if(_arr) delete[] _arr;
        _arr = newArr;
    }
    bool isEmpty() {
        return _isEmpty();
    }
    T& operator[](size_t index) {
        if(index <= _size)
            throw "Index out of range :(";
        return _arr[index];
    }
    size_t size() {
        return this->_size;
    }
private:
    size_t _size;
    size_t _capacity;
    T* _arr;
    DeleterFunc _deleter;
private:
    bool _isFull() {
        return _capacity == _size;
    }
    void _resize() {
        _capacity = (!_capacity)? 1: _capacity * 2;
        T* newArr = new T[_capacity];
        for(size_t i = 0ll; i < _size; ++i)
            newArr[i] = _arr[i];
        if(_arr) delete[] _arr;
        _arr = newArr;
    }
    bool _isEmpty() {
        return _size == 0;
    }
};
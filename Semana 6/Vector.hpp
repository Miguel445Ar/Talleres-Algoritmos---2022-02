
template<class T>
class Vector {
    using DeleterFunc = void (*)(T); // Podríamos usar std::function // void (*f)(T);
public:
    Vector(DeleterFunc deleter = nullptr): _deleter(deleter) {
        this->_arr = nullptr;
        _capacity = _size = 0;
    }
    ~Vector() {
        for(size_t i = 0ll; i < _size; ++i) delete _arr[i];
        delete[] _arr;
    }
    Vector(size_t size, DeleterFunc deleter = nullptr): _capacity(size), _size(size) {
        this->_arr = new Entity*[size];
        for(size_t i = 0; i < _size; ++i) this->_arr[i] = nullptr;
    }
    void pushBack(T value) {
        if(_isEmpty() || _isFull()) _resize();
        this->_arr[_size++] = new Entity(value,_deleter);
    }
    void popBack() {
        if(_isEmpty()) throw "Vector is empty :(";
        delete _arr[_size - 1];
        _arr[_size - 1] = nullptr;
        --_size;
    }
    void insertAt(T value, size_t pos) {

    }
    void eraseAt(size_t pos) {

    }
    void resize(size_t newSize) {
        Entity** newArr = new Entity*[newSize];
        for(size_t i = 0ll; i < _size; ++i)
            newArr[i] = _arr[i];
        if(_arr) delete[] _arr;
        _arr = newArr;
    }
    bool isEmpty() {
        return _isEmpty();
    }
    T& operator[](size_t index) {
        if(index >= _size)
            throw "Index out of range :(";
        return _arr[index]->value;
    }
    size_t size() {
        return this->_size;
    }
private:
    struct Entity {
        T value;
        DeleterFunc deleter;
        Entity(T value, DeleterFunc deleter): value(value), deleter(deleter) {}
        ~Entity() {
            if(deleter) deleter(value);
        }
    };
    size_t _size;
    size_t _capacity;
    Entity** _arr;
    T* arr;
    DeleterFunc _deleter;
private:
    bool _isFull() {
        return _capacity == _size;
    }
    void _resize() {
        _capacity = (!_capacity)? 1: _capacity * 2;
        Entity** newArr = new Entity*[_capacity];
        for(size_t i = 0ll; i < _size; ++i)
            newArr[i] = _arr[i];
        if(_arr) delete[] _arr;
        _arr = newArr;
    }
    bool _isEmpty() {
        return _size == 0;
    }
};
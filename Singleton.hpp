//
// Created by Bourne on 2018/3/27.
//

#ifndef MATRIX_UTIL_SINGLETON_HPP
#define MATRIX_UTIL_SINGLETON_HPP

// thread safe
// 以下代码虽然是C++ 11的，但是你可以把它理解非C++ 11，如果是C++ 11的话，从标准上就保证 静态初始化就是线程安全的，完全没必要像下面这样做了
class singleton {
private:
    static atomic < singleton* > p{nullptr};
public:
    static std::mutex m_mutex;
    static singleton* getInstance();
public:
    singleton(const singleton& s) = delete;
};

singleton* singleton:: getInstance() {
    // double-check locker
    if (p == nullptr) { // first check
        {
            std::lock_guard<std::mutex> lock(m_mutex); // lock
            if (p == nullptr)   // second check
                p = new singleton();
        }
    }
    return p;
}

// 如果编译器支持 c++11， c++标准保证这是线程安全的
/*
singleton*& singleton::getInstance() {
    static singleton* p = new singleton();
    return p;
}
 */

#endif //MATRIX_UTIL_SINGLETON_HPP

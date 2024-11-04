#pragma once
#include <memory>

template <typename Derived>
class Singleton {
public:
    // Prevent access
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // Truy cập instance duy nhất
    static Derived& GetInstance() {
        static Derived instance;
        return instance;
    }

protected:
    Singleton() {} // Only derived class can access
};

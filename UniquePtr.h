#pragma once

template<typename T>
class UniquePtr {
public:
    UniquePtr(): ptr_(nullptr) {}

    explicit UniquePtr(T* ptr): ptr_(ptr) {}

    UniquePtr(UniquePtr&& obj) noexcept : ptr_(obj.ptr_) {
        obj.ptr_ = nullptr;
    }

    UniquePtr& operator= (UniquePtr&& obj) noexcept {
        if (this == &obj) {
            return *this;
        }
        delete ptr_;
        ptr_ = obj.ptr_;
        obj.ptr_ = nullptr;
        return *this;
    }

    ~UniquePtr() {
        delete ptr_;
    }

    T* get() const {
        return ptr_;
    }

    T* operator-> () const {
        return ptr_;
    }

    T& operator* () const {
        return *ptr_;
    }

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator= (const UniquePtr&) = delete;

private:
    T* ptr_;
};


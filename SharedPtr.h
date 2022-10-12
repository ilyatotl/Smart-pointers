#pragma once

#include <cstdint>

template<typename T>
class SharedPtr {
public:
    SharedPtr(): ptr_(nullptr), refCount_(new uint32_t(0)) {}

    explicit SharedPtr(T* x): ptr_(x), refCount_(new uint32_t(1)) {}

    SharedPtr(const SharedPtr &obj) {
        ptr_ = obj.ptr_;
        refCount_ = obj.refCount_;
        if (ptr_ != nullptr) {
            (*refCount_)++;
        }
    }

    SharedPtr(SharedPtr &&obj) noexcept {
        ptr_ = obj.ptr_;
        refCount_ = obj.refCount_;
        obj.ptr_ = obj.refCount_ = nullptr;
    }

    ~SharedPtr() {
        _cleanup_();
    }

    SharedPtr& operator= (const SharedPtr& obj) {
        if (this == &obj) {
            return *this;
        }
        _cleanup_();

        ptr_ = obj.ptr_;
        refCount_ = obj.refCount_;
        if (ptr_ != nullptr) {
            (*refCount_)++;
        }
        return *this;
    }

    SharedPtr& operator= (SharedPtr&& obj)  noexcept {
        _cleanup_();
        ptr_ = obj.ptr_;
        refCount_ = obj.refCount_;
        obj.ptr_ = obj.refCount_ = nullptr;
        return *this;
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

private:
    T* ptr_;
    uint32_t* refCount_;

    void _cleanup_() {
        if (ptr_ == nullptr) {
            delete refCount_;
            return;
        }
        (*refCount_)--;
        if (*refCount_ == 0) {
            delete refCount_;
            delete ptr_;
        }
    }
};
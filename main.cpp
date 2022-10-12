#include "iostream"

#include "SharedPtr.h"
#include "UniquePtr.h"

int main() {
    UniquePtr<int> a(new int(5));
    UniquePtr<int> b(new int(3));
    a = std::move(b);
    return 0;
}

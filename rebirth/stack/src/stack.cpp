#define STACK_USE_CPP
#include <stack.h>

namespace stack {

template <typename T>
container<T>::container(void) : _handler({0}) {}

template <typename T>
container<T>::container(size_t initial_size) : container() {
    create(initial_size);
}

template <typename T>
error container<T>::create(size_t initial_size) {

    return error::ERROR_ALLOCATION;
}

}


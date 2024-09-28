#ifndef STACK_HPP_
#define STACK_HPP_

/**************************************************************************//**
 * @file     stack.hpp
 * @brief    Stack. C++ version.
 * @version  V0.0.1
 * @date     24. Sep 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

// C++ 2011 reuires
#if __cplusplus >= 201103L

#include <cstdlib>

class stack {
private:
    const size_t INITIAL_BUFFER_SIZE = 4096UL;
    void* _data;
    size_t _size;
public:
    stack(void) {}
};

#else
#   error "<stack.hpp> ERROR: C++ 2011 requres!"
#endif 

#endif // STACK_HPP_
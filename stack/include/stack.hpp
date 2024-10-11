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
#include <cstdint>

class stack {
private:
    uint64_t _stack;

public:

    struct dump_conf_t {
        enum class output_type {
            FILE,
            CONSOLE
        } output;
        const char* const filename;
    };

    // General
    void init(void);
    void init(size_t size);
    void deinit(void);

    void clear();

    template <typename T>
    void push(T data);

    template <typename T>
    T pop(void);

    size_t size(void);
    size_t lenght(void);

    // Additional
    bool is_empty(void);
    void dump(dump_conf_t _conf);

};

#else
#   error "<stack.hpp> ERROR: C++ 2011 requres!"
#endif 

#endif // STACK_HPP_
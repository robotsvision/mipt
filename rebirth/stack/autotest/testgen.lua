
local TEST_C_HEAD = [[
#ifdef USE_STACK_CPP
#   undef USE_STACK_CPP
#endif
#include <stack.h>
#include <stdio.h>
#include <stddef.h>

int main(int argc, char* argv[]) {
]]

local TEST_CPP_HEAD = [[
#ifndef USE_STACK_CPP
#   define USE_STACK_CPP
#endif
#include <stack.hpp>
#include <stdio.h>
#include <stddef.h>

int main(int argc, char* argv[]) {
]]

local TEST_TAIL = [[
    return EXIT_SUCCESS;
}
]]



-- Генератор тестов для стека "git@github.com:robotsvision/mipt.git"

function GenerateTestsC(filename, overflow, underflow, num_of_tests)
    local file = io.open(filename, "w")

    if not file then
        error(string.format("[testgen.lua]: Cannot open file %s", filename))
    end

    file:write(TEST_C_HEAD);

end

function GenerateTestsCPP(filename, overflow, underflow, num_of_tests)

end

-- Запуск


GenerateTests()


testHeadC = [[
#ifdef USE_STACK_CPP
#   undef USE_STACK_CPP
#endif
#include <stack.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
]]
#ifndef AKINATOR_H_
#define AKINATOR_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define AKINATOR_MAIN(argc, argv) int main(int argc, const char* argv[]) 

extern int akinator_open(void);
extern int akinator_get_operation(void);
extern int akinator_get_answer(void);
extern int akinator_close(void);

#endif // AKINATOR_H_
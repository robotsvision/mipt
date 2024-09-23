#ifndef STACK_CONF_H_
#define STACK_CONF_H_

/**************************************************************************//**
 * @file     stack_conf.h
 * @brief    MIPT project 3. Stack configuration file.
 * @version  V0.0.1
 * @date     20. Sep 2024
 * @author   Matvey Rybalkin
******************************************************************************/

#define STACK_CLASTER_SIZE 4096     // size in bytes.
#define STACK_CLEAR_DELTA  3        // if the actual memory consumption is less than `STACK_CLEAR_DELTA` times

// []     [][]  []   []
// [type][data][type][data]

#endif // STACK_CONF_H_
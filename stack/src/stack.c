#include <stack.h>
#include <stack_conf.h>

/*************************************************************
 * Private
 ************************************************************/

/**
 * @brief Initialize stack, and allocate basic claster.
 * 
 */
int _stack_init(stack_t* stack){
    void* data = calloc(STACK_CLASTER_SIZE, 1ULL);
    if (data == NULL) {
        return -1;
    }
    stack->sp = data;
    stack->size = STACK_CLASTER_SIZE;
    
}

/*************************************************************
 * Private / Stack pushes
 ************************************************************/

/**
 * @brief Add one byte element to stack with typization
 * signed/unsigned.
 * 
 * @param[out] stack stack structure
 * @param[out] data data (must be (unsigned) char, uint8_t or int8_t or a constant)
 * @param[out] type `STACK_U8_TYPE` or `STACK_I8_TYPE`
 * @returns 
 */
int _stack_push1   (
                    stack_t* stack,
                    const int8_t data, 
                    stack_data_type_t type
                    ){}

/**
 * @brief Add two byte element to stack with typization
 * signed/unsigned.
 * 
 * @param[out] stack stack structure
 * @param[out] data data (must be (unsigned) short, uint16_t or int16_t or a constant)
 * @param[out] type `STACK_U16_TYPE` or `STACK_I16_TYPE`
 * @returns `0` in success, or `-1` if an error occurs
 */
int _stack_push2   (
                    stack_t* stack, 
                    const int16_t data, 
                    stack_data_type_t type
                    ){}

/**
 * @brief Add four byte element to stack with typization
 * signed/unsigned.
 * 
 * @param[out] stack stack structure
 * @param[out] data data (must be (unsigned) int, uint32_t or int32_t or a constant)
 * @param[out] type `STACK_U32_TYPE` or `STACK_I32_TYPE`
 * @returns `0` in success, or `-1` if an error occurs
 */
int _stack_push4   (
                    stack_t* stack, 
                    int32_t data, 
                    stack_data_type_t type
                    ){}

/**
 * @brief Add eight byte element to stack with typization
 * signed/unsigned.
 * 
 * @param[out] stack stack structure
 * @param[out] data data (must be long long , uint64_t or int64_t or a constant)
 * @param[out] type `STACK_U64_TYPE` or `STACK_I64_TYPE`
 * @returns `0` in success, or `-1` if an error occurs
 */
int _stack_push8   (
                    stack_t* stack, 
                    const int64_t data, 
                    stack_data_type_t type
                    ){}

/**
 * @brief Add pointer for any data. 
 * 
 * @param[out] stack stack structure
 * @param[out] data data pointer
 * @param[out] type
 * @returns `0` in success, or `-1` if an error occurs
 */
int _stack_push_ptr(stack_t* stack, void* data, stack_data_type_t type){}

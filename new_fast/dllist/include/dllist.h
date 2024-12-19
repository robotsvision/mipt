
/**
 * @file dllist.h
 * @brief Doubly linked list implementation.
 * 
 * @version 1.0.0
 * @date 15.12.24
 * @author Matvey Rybalkin
*/

#ifndef DLLIST_H_
#define DLLIST_H_

/* ==================== Includes ==================== */

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/* ==================== Type definitions ==================== */

/**
 * @file dllist.h
 * @brief Double Linked List (DLL) Library
 *
 * This file provides the API for a dynamic double linked list implementation.
 */

/**
 * @struct dllist_t
 * @brief Represents a double linked list structure.
 *
 * This structure contains metadata about the list, pointers to its elements,
 * and information for efficient navigation and management of list contents.
 */
typedef struct {
    /**
     * @brief Size of each element in bytes.
     */
    size_t size_of_element;

    struct {
        /**
         * @brief Index of the last allocated element.
         */
        size_t _last_allocated_element;

        /**
         * @brief Total number of elements currently in the list.
         */
        size_t num_of_elements;

        /**
         * @brief Index of the last valid element in the list.
         */
        size_t last_index;
    } meta;

    struct {
        union {
            uint8_t*     data_8bit;       ///< Pointer to 8-bit elements.
            uint16_t*    data_16bit;      ///< Pointer to 16-bit elements.
            uint32_t*    data_32bit;      ///< Pointer to 32-bit elements.
            uint64_t*    data_64bit;      ///< Pointer to 64-bit elements.
            double*      data_double;     ///< Pointer to double elements.
            long double* data_long_double; ///< Pointer to long double elements.
        } list_elements; ///< Union storing pointers to different data types.

        /**
         * @brief Index of the first element in the list.
         */
        size_t first_element;

        /**
         * @brief Array of indices pointing to the next elements.
         */
        size_t* next_elements;

        /**
         * @brief Array of indices pointing to the previous elements.
         */
        size_t* prev_elements;
    } content;
} dllist_t;

/**
 * @brief Creates a new double linked list.
 *
 * @param num_of_elements Initial number of elements to allocate.
 * @param size_of_element Size of each element in bytes.
 * @return Pointer to the newly created dllist_t instance.
 */
extern dllist_t* dllist_create(size_t num_of_elements, size_t size_of_element);

/**
 * @brief Destroys a double linked list and frees its memory.
 *
 * @param list Pointer to the double linked list to destroy.
 */
extern void dllist_destroy(dllist_t* list);

/**
 * @brief Checks if the list is empty.
 *
 * @param list Pointer to the double linked list.
 * @return True if the list is empty, false otherwise.
 */
extern bool dllist_is_empty(dllist_t* list);

/**
 * @brief Gets the memory used by the list in bytes.
 *
 * @param list Pointer to the double linked list.
 * @return Size of the used memory in bytes.
 */
extern size_t dllist_get_size_used_memory(dllist_t* list);

/**
 * @brief Gets the total allocated memory for the list in bytes.
 *
 * @param list Pointer to the double linked list.
 * @return Size of the allocated memory in bytes.
 */
extern size_t dllist_get_size_allocated_memory(dllist_t* list);

/**
 * @brief Gets the number of elements in the list.
 *
 * @param list Pointer to the double linked list.
 * @return Number of elements in the list.
 */
extern size_t dllist_get_length(dllist_t* list);

/**
 * @brief Inserts an element at the front of the list.
 *
 * @param list Pointer to the double linked list.
 * @param new_element Pointer to the element to insert.
 * @return True if the operation was successful, false otherwise.
 */
extern bool dllist_push_front(dllist_t* list, void* new_element);

/**
 * @brief Inserts an element after a specified element in the list.
 *
 * @param list Pointer to the double linked list.
 * @param num_of_element Index of the element after which to insert.
 * @param new_element Pointer to the element to insert.
 * @return True if the operation was successful, false otherwise.
 */
extern bool dllist_push_after(dllist_t* list, size_t num_of_element, void* new_element);

/**
 * @brief Inserts an element before a specified element in the list.
 *
 * @param list Pointer to the double linked list.
 * @param num_of_element Index of the element before which to insert.
 * @param new_element Pointer to the element to insert.
 * @return True if the operation was successful, false otherwise.
 */
extern bool dllist_push_before(dllist_t* list, size_t num_of_element, void* new_element);

/**
 * @brief Inserts an element at the back of the list.
 *
 * @param list Pointer to the double linked list.
 * @param new_element Pointer to the element to insert.
 * @return True if the operation was successful, false otherwise.
 */
extern bool dllist_push_back(dllist_t* list, void* new_element);

/**
 * @brief Removes the front element of the list.
 *
 * @param list Pointer to the double linked list.
 * @param dest_element Pointer to store the removed element.
 * @return True if the operation was successful, false otherwise.
 */
extern bool dllist_pop_front(dllist_t* list, void* dest_element);

/**
 * @brief Removes an element after a specified element in the list.
 *
 * @param list Pointer to the double linked list.
 * @param num_of_element Index of the element after which to remove.
 * @param dest_element Pointer to store the removed element.
 * @return True if the operation was successful, false otherwise.
 */
extern bool dllist_pop_after(dllist_t* list, size_t num_of_element, void* dest_element);

/**
 * @brief Removes an element before a specified element in the list.
 *
 * @param list Pointer to the double linked list.
 * @param num_of_element Index of the element before which to remove.
 * @param dest_element Pointer to store the removed element.
 * @return True if the operation was successful, false otherwise.
 */
extern bool dllist_pop_before(dllist_t* list, size_t num_of_element, void* dest_element);

/**
 * @brief Removes the back element of the list.
 *
 * @param list Pointer to the double linked list.
 * @param dest_element Pointer to store the removed element.
 * @return True if the operation was successful, false otherwise.
 */
extern bool dllist_pop_back(dllist_t* list, void* dest_element);

/**
 * @brief Retrieves an element from the list.
 *
 * @param list Pointer to the double linked list.
 * @param num_of_element Index of the element to retrieve.
 * @param dest_element Pointer to store the retrieved element.
 * @return True if the operation was successful, false otherwise.
 */
extern bool dllist_get_element(dllist_t* list, size_t num_of_element, void* dest_element);


#endif // DLLIST_H_
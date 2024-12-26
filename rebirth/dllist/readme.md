# Doubly Linked List `dllist.h` Library

## Overview

The `dllist.h` library provides a robust implementation of a dynamic doubly linked list in C. This library supports efficient storage and manipulation of various data types, making it suitable for a wide range of applications.

### Key Features

- **Flexible Data Storage**: Supports multiple data types, including integers, floating-point numbers, and custom structures.
- **Dynamic Memory Management**: Allocates and frees memory as needed to ensure optimal resource utilization.
- **Bidirectional Traversal**: Enables forward and backward navigation through the list.
- **Efficient Indexing**: Provides quick access to elements using indices.

---

## Getting Started

### Prerequisites

To use this library, ensure you have a C compiler and the standard C library available.

### Installation

Include the `dllist.h` file in your project and link the corresponding implementation during compilation.

---

## API Reference

### Data Structure

The `dllist_t` structure represents a doubly linked list with metadata and storage for list elements.

```c
typedef struct {
    /**
     * @brief Size of each element in bytes.
     */
    size_t element_size;

    struct {
        /**
         * @brief Total capacity of the list (maximum number of elements).
         */
        size_t capacity;

        /**
         * @brief Current size of the list (number of used elements).
         */
        size_t size;

        /**
         * @brief Index of the last used element.
         */
        size_t last_used_index;
    } meta;

    struct {
        union {
            uint8_t*     data_8bit;       ///< Pointer to 8-bit elements.
            uint16_t*    data_16bit;      ///< Pointer to 16-bit elements.
            uint32_t*    data_32bit;      ///< Pointer to 32-bit elements.
            uint64_t*    data_64bit;      ///< Pointer to 64-bit elements.
            double*      data_double;     ///< Pointer to double elements.
            long double* data_long_double; ///< Pointer to long double elements.
        } elements; ///< Union storing pointers to different data types.

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
```

### Functions

#### Create a New List

```c
dllist_t* dllist_create(size_t num_of_elements, size_t size_of_element);
```

- **Description**: Creates a new doubly linked list.
- **Parameters**:
  - `num_of_elements`: Initial number of elements to allocate.
  - `size_of_element`: Size of each element in bytes.
- **Returns**: Pointer to the newly created `dllist_t` structure.

#### Destroy a List

```c
void dllist_destroy(dllist_t* list);
```

- **Description**: Frees all memory associated with the list.
- **Parameters**:
  - `list`: Pointer to the list to be destroyed.

#### Check if the List is Empty

```c
bool dllist_is_empty(dllist_t* list);
```

- **Description**: Checks whether the list contains any elements.
- **Parameters**:
  - `list`: Pointer to the list.
- **Returns**: `true` if the list is empty, `false` otherwise.

#### Get the Number of Elements

```c
size_t dllist_get_length(dllist_t* list);
```

- **Description**: Retrieves the number of elements in the list.
- **Parameters**:
  - `list`: Pointer to the list.
- **Returns**: Number of elements in the list.

#### Insert an Element

```c
bool dllist_push_front(dllist_t* list, void* new_element);
```

- **Description**: Adds an element to the front of the list.
- **Parameters**:
  - `list`: Pointer to the list.
  - `new_element`: Pointer to the element to insert.
- **Returns**: `true` if the operation was successful, `false` otherwise.

#### Retrieve an Element

```c
bool dllist_get_element(dllist_t* list, size_t num_of_element, void* dest_element);
```

- **Description**: Retrieves an element by its index.
- **Parameters**:
  - `list`: Pointer to the list.
  - `num_of_element`: Index of the element to retrieve.
  - `dest_element`: Pointer to store the retrieved element.
- **Returns**: `true` if the operation was successful, `false` otherwise.

---

## Example Usage

```c
#include <stdio.h>
#include "dllist.h"

int main() {
    dllist_t* list = dllist_create(10, sizeof(int));
    if (!list) {
        printf("Failed to create list\n");
        return -1;
    }

    int value = 42;
    if (!dllist_push_front(list, &value)) {
        printf("Failed to insert element\n");
        dllist_destroy(list);
        return -1;
    }

    int retrieved_value;
    if (dllist_get_element(list, 0, &retrieved_value)) {
        printf("Retrieved value: %d\n", retrieved_value);
    }

    dllist_destroy(list);
    return 0;
}
```

---

## Limitations

- **Thread Safety**: The library is not thread-safe. Use synchronization mechanisms for concurrent operations.
- **Memory Management**: Ensure `size_of_element` matches the size of the data being stored to avoid memory corruption.

---

## License

This library is distributed under the MIT License. See `LICENSE` for more details.

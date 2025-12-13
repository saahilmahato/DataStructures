cmake_minimum_required(VERSION 4.1)
project(DSA C)

set(CMAKE_C_STANDARD 23)

add_executable(DSA main.c
        linked_list/circular_linked_list/list.c
        linked_list/circular_linked_list/test.c
        linked_list/doubly_linked_list/list.c
        linked_list/doubly_linked_list/test.c
        linked_list/singly_linked_list/list.c
        linked_list/singly_linked_list/test.c
        queue/array_queue/queue.c
        queue/array_queue/test.c
        queue/linked_list_queue/queue.c
        queue/linked_list_queue/test.c
        stack/array_stack/stack.c
        stack/array_stack/test.c
        stack/linked_list_stack/stack.c
        stack/linked_list_stack/test.c
        tree/test.c
        tree/tree.c)

cmake_minimum_required(VERSION 4.1)
project(DSA C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(DSA main.c
        linked_list/circular_linked_list/circular_linked_list.c
        linked_list/doubly_linked_list/doubly_linked_list.c
        linked_list/singly_linked_list/singly_linked_list.c
        queue/array_queue/array_queue.c
        queue/linked_list_queue/linked_list_queue.c
        stack/array_stack/array_stack.c
        stack/linked_list_stack/linked_list_stack.c
        tree/tree.c
        test/test.h
        linked_list/circular_linked_list/main.c
        linked_list/doubly_linked_list/main.c
        linked_list/singly_linked_list/main.c
        queue/array_queue/main.c
        queue/linked_list_queue/main.c
        stack/array_stack/main.c)

## Linked List

A **linked list** is a linear data structure consisting of a sequence of **nodes**, where each node contains an element (data) and a reference (pointer/link) to the **next** node in the sequence. The list is accessed through a **head** pointer to the first node; the last node's next reference is `null` (or `nullptr`).

### Core Intuition
- Imagine a chain of people holding hands facing forward: you can only move forward from one person to the next, but not backward. To reach someone in the middle, you must start from the beginning and follow the chain.
- Unlike arrays, memory is not contiguous—nodes can be scattered—and the structure grows/shrinks dynamically without resizing or shifting large blocks of elements.
- Excels when insertions/deletions occur at known positions (especially the head) or when size is unpredictable.

### Formal Operations
Standard operations on a singly linked list (assuming only a head pointer unless noted):

| Operation              | Description                                                                 | Typical Runtime |
|------------------------|-----------------------------------------------------------------------------|-----------------|
| `insertFirst(e)` / `prepend(e)` | Insert element `e` as the new head.                                         | O(1)            |
| `insertLast(e)` / `append(e)`   | Insert element `e` at the end (traverse to find last node).                 | O(n)            |
| `insertAfter(node, e)`          | Insert `e` immediately after a given node reference.                        | O(1)            |
| `deleteFirst()`                 | Remove and return the head element.                                         | O(1)            |
| `deleteLast()`                  | Remove and return the last element.                                         | O(n)            |
| `deleteNode(node)`              | Remove a node given a direct reference to it (or previous node).            | O(1)            |
| `search(key)`                   | Return node containing key (or boolean). Traverses from head.               | O(n)            |
| `isEmpty()`                     | Return true if head is null.                                                | O(1)            |
| `size()`                        | Return number of elements (O(1) if counter maintained; otherwise O(n)).     | O(1) or O(n)    |
| `traverse()` / iteration        | Visit all elements in order from head to tail.                              | O(n)            |

**Note**: Maintaining a **tail** pointer makes `insertLast` and `deleteLast` O(1). Many practical implementations (e.g., for queues) include both head and tail.

### Error Handling Conventions
- Operations like `deleteFirst()` or accessing the head on an empty list are undefined.
- Common conventions:
    - Throw an exception (e.g., `NoSuchElementException` in Java, custom `EmptyListError` in Python).
    - Return `null`/sentinel with a status flag (common in low-level C implementations).

## 2. Variants and Extensions

### Doubly Linked List
Each node has **prev** and **next** pointers.
- Allows bidirectional traversal.
- `insertBefore`, `deleteNode` remain O(1) with direct node reference.
- Extra space per node; useful for deque implementations or when frequent backward traversal is needed.

### Circular Linked List
Last node points back to the first (single or doubly linked).
- No explicit "end"—traversal can loop indefinitely.
- Useful for round-robin scheduling, Josephus problem, or buffers where wrapping is natural.

## 3. Time and Space Complexity Guarantees

A correct singly linked list implementation guarantees:
- Head operations (`insertFirst`, `deleteFirst`): **O(1)** worst-case.
- Search, insertLast/deleteLast (without tail): **O(n)** worst-case.
- Space usage: Θ(n) for n elements (data + one pointer per node; ~1.5–2× overhead vs. arrays).
- With tail pointer: tail operations also O(1).

No amortization is needed—runtimes are worst-case (no resizing). Random access (get by index) is always O(n).

## 4. Key Theoretical Properties

- **Dynamic Allocation**: Nodes allocated individually; no capacity/resizing issues.
- **No Random Access**: Must traverse sequentially; poor cache locality compared to arrays.
- **Pointer Overhead**: Each element costs extra memory for links.
- **Fragmentation Resistance**: Works well in fragmented memory (unlike contiguous arrays).
- **Immutability Variants**: Persistent linked lists (functional style) share nodes across versions, enabling O(1) "modifications" with structural sharing.
- **No Built-in Bounds**: Unbounded by default; bounded variants possible but rare.

## 5. Classic Applications (Theoretical Significance)

Linked lists are foundational for building higher-level structures and solving problems requiring flexible sequencing:

1. **Implementation of Abstract Data Types**
    - Stack (using head only).
    - Queue (head + tail pointers for O(1) enqueue/dequeue).
    - Deque (doubly linked).

2. **Adjacency Lists in Graphs**  
   Represent edges from each vertex as a linked list—efficient for sparse graphs and dynamic edge addition.

3. **Hash Table Chaining**  
   Collision resolution: each bucket is a linked list of entries.

4. **Polynomial Representation**  
   Store terms as nodes sorted by exponent for efficient addition/multiplication.

5. **Memory Management**  
   Free-list allocation: available blocks linked together.

6. **Undo/Redo Functionality**  
   Command pattern history or text editor operations (though often combined with stacks).

7. **Music/Video Playlists**  
   Next/previous navigation (doubly linked for bidirectional).

8. **Josephus Problem & Round-Robin Scheduling**  
   Circular linked lists efficiently eliminate every k-th element.

9. **Mergeable Sequences in Algorithms**  
   Bottom-up merge sort uses linked lists naturally (O(n log n) with no extra space for merging).

## 6. Comparison with Similar Structures

| Feature                  | Singly Linked List          | Doubly Linked List          | Array / Dynamic Array       | Stack (Linked)             |
|--------------------------|-----------------------------|-----------------------------|-----------------------------|----------------------------|
| Insertion at head        | O(1)                        | O(1)                        | O(n)                        | O(1)                       |
| Insertion at tail        | O(n) or O(1) w/tail         | O(1)                        | O(1) amortized              | N/A (top only)             |
| Deletion with node ref   | O(1)                        | O(1)                        | O(n)                        | O(1) (pop)                 |
| Random access (index)    | O(n)                        | O(n)                        | O(1)                        | N/A                        |
| Memory overhead          | 1 pointer/node              | 2 pointers/node             | Minimal (capacity)          | 1 pointer/node             |
| Cache performance        | Poor (scattered)            | Poor                        | Excellent (contiguous)      | Poor                       |
| Typical use              | Dynamic sequences, graphs   | Deques, bidirectional       | General-purpose lists       | LIFO recursion/DFS         |

These theoretical foundations make linked lists essential for building efficient, flexible data structures in systems where insertion/deletion patterns outweigh the need for random access.
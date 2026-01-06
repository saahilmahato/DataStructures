## Abstract Data Type: Stack

A **stack** is a linear abstract data type (ADT) that models a collection of elements with a **Last-In-First-Out (LIFO)** discipline. Elements are inserted and removed only from one end, called the **top** of the stack.

### Core Intuition
- Think of a stack as a physical stack of plates: you add (push) a plate only to the top, and you remove (pop) only the topmost plate.
- The most recently added element is the first one that can be removed.

### Formal Operations
The standard interface for a stack ADT consists of the following operations:

| Operation     | Description                                                                 | Typical Runtime (Amortized) |
|---------------|-----------------------------------------------------------------------------|----------------------------|
| `push(e)`     | Insert element `e` at the top of the stack.                                  | O(1)                       |
| `pop()`       | Remove and return the top element. Throws exception if stack is empty.      | O(1)                       |
| `top()` / `peek()` | Return (without removing) the top element. Throws exception if empty.  | O(1)                       |
| `isEmpty()`   | Return true if the stack contains no elements.                              | O(1)                       |
| `size()`      | Return the number of elements in the stack.                                  | O(1)                       |

Some implementations also provide auxiliary operations such as `clear()` or iteration (though iteration typically violates LIFO purity and is rarely supported in pure stack ADTs).

### Error Handling Conventions
- Attempting `pop()` or `top()` on an empty stack is undefined behavior.
- Common conventions:
    - Throw an exception (e.g., `EmptyStackException` in Java).
    - Return a sentinel value + boolean flag (less common in modern typed languages).

## 2. Formal Specification (Algebraic)

A stack can be formally specified using an algebraic ADT definition with constructors and observers.

Let `S` be a stack of elements from type `E`.

**Constructors**:
- `empty(): → Stack<E>`                     // creates an empty stack
- `push(s: Stack<E>, e: E): → Stack<E>`      // adds e to top of s

**Observers**:
- `isEmpty(s: Stack<E>): → Boolean`
- `top(s: Stack<E>): → E`                    // precondition: ¬isEmpty(s)
- `pop(s: Stack<E>): → Stack<E>`             // precondition: ¬isEmpty(s)

**Axioms** (defining behavior):

1. `isEmpty(empty()) = true`
2. `isEmpty(push(s, e)) = false`
3. `top(push(s, e)) = e`
4. `pop(push(s, e)) = s`
5. For any non-empty stack `s` that is not created by a single `push`, the axioms hold recursively.

These five axioms completely characterize the LIFO behavior.

## 3. Time and Space Complexity Guarantees

Any correct implementation of the stack ADT must support:
- `push`, `pop`, `top`, `isEmpty`, `size` in **O(1)** worst-case or amortized time.
- Space usage Θ(n) where n is the number of elements currently stored.

Deviations from O(1) per operation indicate either a flawed implementation or an extended structure (e.g., persistent stacks).

## 4. Key Theoretical Properties

- **LIFO Discipline**: The order of removal is the reverse of the order of insertion.
- **No Random Access**: Unlike arrays or lists, stacks provide no indexing operation `get(i)`.
- **Bounded vs. Unbounded**: Some implementations have a fixed maximum capacity (bounded stacks); others grow dynamically (unbounded).
- **Immutability Variants**: Persistent (functional) stacks allow versions to share structure, supporting O(1) “modification” via path copying (common in functional languages).

## 5. Classic Applications (Theoretical Significance)

Stacks appear ubiquitously due to their simplicity and the natural recursion/LIFO patterns in computation:

1. **Call Stack / Recursion**  
   Procedure calls and returns form a stack: activation records are pushed on entry, popped on return. Recursion depth = stack size.

2. **Expression Evaluation**
    - Postfix (Reverse Polish) notation evaluation uses a single stack.
    - Infix → postfix conversion (Shunting Yard algorithm) uses a stack for operators.

3. **Depth-First Search (DFS)**  
   DFS traversal of graphs/trees uses a stack (explicit or via recursion) to explore as far as possible along each branch.

4. **Undo/Redo Mechanisms**  
   Command pattern with stacks for reversible operations.

5. **Syntax Analysis**  
   Parsing context-free languages (e.g., balanced parentheses, XML tags) via stack-based pushdown automata.

6. **Backtracking Algorithms**  
   Maze solving, N-queens, Sudoku: stack stores partial solutions.

## 6. Comparison with Similar ADTs

| Feature              | Stack (LIFO)          | Queue (FIFO)          | Deque (Double-Ended) |
|----------------------|-----------------------|-----------------------|----------------------|
| Insertion end        | Top only              | Rear only             | Both ends            |
| Removal end          | Top only              | Front only            | Both ends            |
| Typical use          | Recursion, DFS        | BFS, scheduling       | Sliding window, palindrome checks |
| Theoretical model    | Pushdown automaton    | Turing machine (restricted) | More flexible than both |


These theoretical foundations are prerequisite for understanding correct and efficient stack implementations.
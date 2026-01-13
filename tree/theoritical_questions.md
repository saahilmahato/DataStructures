## Interview Preparation: Tree Theoretical Questions

Theoretical questions on trees test deep understanding of hierarchical structures, traversals, properties, variants, and their role in efficient algorithms. Trees (especially binary trees, BSTs, and heaps) are among the most frequently asked topics at companies like Google, Meta, Amazon, Microsoft, Apple, and startups (e.g., Databricks, Rippling). Interviewers look for clarity on definitions, ability to distinguish variants, complexity reasoning, traversal intuition, and real-world connections.

Top performers:
- Start with a precise definition and key properties.
- Use clear terminology (height, depth, balanced, etc.).
- Compare variants and trade-offs explicitly.
- Connect to applications (search, priority queues, file systems, parsing).
- Mention edge cases (empty tree, skewed tree, single node).
- Draw small examples on whiteboard when possible.

Below are the most important theoretical tree questions, with **model answers** crafted to impress. Practice delivering them in 2–5 minutes verbally.

## 1. What is a tree data structure? Explain its core properties and key terminology.

**Model Answer**:
A tree is a hierarchical, acyclic, connected abstract data structure with a distinguished **root** node, where every other node has exactly one **parent** and zero or more **children**. There is exactly one unique path between any two nodes.

Key properties:
- **Acyclic and connected** → exactly n−1 edges for n nodes.
- **Rooted** → single node with no parent.
- **No cycles** → enables efficient recursion and unique paths.

Important terms:
- **Leaf**: node with no children.
- **Internal node**: node with at least one child.
- **Depth** of a node: number of edges from root.
- **Height** of a node: longest path to a leaf; height of tree = height of root.
- **Level**: nodes at same depth.
- **Subtree**: tree rooted at any node.
- **Degree**: number of children (binary tree: max degree 2).

Trees model natural hierarchies and enable divide-and-conquer algorithms.

## 2. Explain the different variants of binary trees (full, complete, perfect, balanced, skewed).

**Model Answer**:
Binary trees restrict each node to at most two ordered children (left/right). Variants are defined by structural constraints:

- **Full (proper/strict)**: Every node has 0 or exactly 2 children (no single-child nodes).
- **Complete**: All levels fully filled except possibly the last, which is filled left-to-right (ideal for array representation, e.g., heaps).
- **Perfect**: Both full and complete—all levels completely filled (exactly 2^{h+1}−1 nodes).
- **Balanced**: Height is O(log n); typically, heights of left/right subtrees differ by at most a constant (e.g., ≤1 in AVL trees). Guarantees O(log n) operations.
- **Skewed/degenerate**: All nodes have only one child → behaves like a linked list, height = n−1, worst-case O(n) operations.

Skewed trees degrade performance in search trees; balancing (AVL, Red-Black) prevents this in practice.

## 3. Describe the standard tree traversal algorithms and their use cases.

**Model Answer**:
Traversals visit each node exactly once in a defined order:

1. **Depth-First (DFS)** – recursive, O(h) stack space:
    - **Preorder** (root → left → right): copy tree, prefix notation, serialization.
    - **Inorder** (left → root → right): yields sorted order in BSTs.
    - **Postorder** (left → right → root): delete tree (children first), postfix evaluation.

2. **Breadth-First / Level Order** – uses queue, O(n) space worst-case: level-by-level processing (e.g., shortest path in unweighted tree, printing levels).

All are O(n) time. DFS can be implemented iteratively with an explicit stack; level order requires a queue.

Inorder is unique to ordered binary trees and critical for BST validation.

## 4. Compare recursive and iterative implementations of tree traversals.

**Model Answer**:
Recursive traversals are concise and natural:
- Leverage call stack for backtracking.
- Code is short and readable.
- Drawback: O(h) implicit stack space; risk of stack overflow on deep/skewed trees (h ≈ n).

Iterative traversals use explicit data structures:
- Pre/in/postorder: use stack (mimics recursion).
- Level order: use queue.
- Pros: Avoids recursion depth limits, often required in interviews.
- Cons: More code, harder to implement correctly (e.g., Morris traversal for O(1) space inorder).

In production, recursion is fine for balanced trees (h ≈ log n); iterative preferred for robustness in unknown cases. Many interviewers ask for both.

## 5. What is a Binary Search Tree (BST)? Explain properties and operation complexities.

**Model Answer**:
A BST is a binary tree where for every node:
- Left subtree values < node value.
- Right subtree values > node value.
- No duplicates (or defined policy).

Properties:
- Inorder traversal gives sorted order.
- Enables efficient search, insert, delete.

Complexities (average case, random insertions):
- Search/insert/delete: O(log n) time, O(log n) space (recursion).

Worst case (skewed): O(n) → defeated by self-balancing variants (AVL, Red-Black trees, used in std::set/map in C++, TreeMap in Java).

BSTs are foundational for ordered collections and range queries.

## 6. Why do we need balanced binary search trees? Briefly explain AVL and Red-Black trees.

**Model Answer**:
Standard BSTs can become skewed with sorted insertions → O(n) operations, defeating the purpose of logarithmic performance.

Balanced trees guarantee O(log n) height:
- **AVL trees**: Strict balance—left/right height differ by at most 1. Uses rotations (single/double) on insert/delete to restore balance. Fewer rotations on lookup, very balanced (height ≤ 1.44 log n).
- **Red-Black trees**: Relaxed balance via coloring (red/black) and rules. Guarantees height ≤ 2 log n. Fewer rotations on modifications → faster inserts/deletes.

Red-Black preferred in practice (std::set/map, Java HashMap backing, Linux kernel). Trade-off: AVL faster lookups, Red-Black faster modifications.

## 7. What are real-world and algorithmic applications of trees?

**Model Answer**:
Trees are ubiquitous due to hierarchical modeling and divide-and-conquer:

1. **File systems** – directories as general trees.
2. **Expression/parsing** – ASTs in compilers, evaluation.
3. **Heaps** – complete binary tree for priority queues (O(log n) insert/extract).
4. **Databases** – B-trees/B+ trees for indexed storage (disk-friendly).
5. **Search/ordered sets** – balanced BSTs (std::map, Java TreeSet).
6. **DOM in browsers** – HTML as tree, traversal for rendering/events.
7. **Decision/game trees** – AI, minimax with alpha-beta pruning.
8. **Huffman coding** – full binary tree for compression.
9. **Segment/Fenwick trees** – range queries/updates.

In systems, the heap memory allocator uses tree-like structures, and routing tables use tries (prefix trees).

## 8. How does a binary heap work, and how is it represented?

**Model Answer**:
A binary heap is a **complete** binary tree satisfying the heap property:
- **Min-heap**: parent ≤ children.
- **Max-heap**: parent ≥ children.

Representation: Stored in array (no pointers):
- Root at index 1 (or 0).
- Children of i: 2i and 2i+1.
- Parent of i: floor(i/2).

Operations via **heapify** (sift up/down):
- Insert: add at end, sift up – O(log n)
- Extract-min/max: swap root with last, remove last, sift down – O(log n)
- Build-heap: O(n)

Used for priority queues, Dijkstra’s, heapsort (O(n log n)). Complete structure ensures O(log n) height and efficient array access.

These questions cover ~90% of tree theory asked in interviews. When answering, always draw a small example tree, label heights/levels, and mention time/space complexities. Relate to coding problems (e.g., “This traversal idea is key in LeetCode 94/144/145”). Practice transitioning to implementation questions smoothly. Good luck!
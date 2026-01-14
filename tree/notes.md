## Tree

A **tree** is a hierarchical, non-linear abstract data type (ADT) that models a collection of **nodes** connected by **edges**, forming an acyclic, connected structure with a distinguished **root** node. Each node (except the root) has exactly one **parent**, and zero or more **children**. Trees generalize linear structures by allowing branching and are fundamental for representing hierarchies, ordered data, and efficient search/update operations.

### Core Intuition
- Visualize a natural tree (inverted): a single **root** at the top, branching downward through **internal nodes** to **leaves** (nodes with no children).
- Represents natural hierarchies: family trees, organization charts, file systems, parse trees for expressions/programs, or decision processes.
- Unlike linear structures, access follows parent-child relationships; there is exactly one path between any two nodes.

### Key Terminology
- **Node**: Basic unit storing data.
- **Root**: The unique top node with no parent.
- **Leaf**: Node with no children (external node).
- **Internal node**: Node with at least one child.
- **Edge**: Directed connection from parent to child.
- **Parent / Child / Sibling**: Immediate ancestor / descendants / nodes sharing a parent.
- **Ancestor / Descendant**: Nodes on the path upward/downward from a node (including itself or not, depending on strict definition).
- **Subtree**: Tree formed by a node and all its descendants.
- **Depth of a node**: Number of edges from root to the node.
- **Level**: All nodes at the same depth (root at level 0).
- **Height of a node**: Number of edges on the longest path to a leaf.
- **Height of the tree**: Height of the root.
- **Path**: Sequence of nodes connected by edges from ancestor to descendant.
- **Degree of a node**: Number of children (maximum degree bounds the tree type).

### Tree Variants and Classifications
Trees are classified by structural constraints:

| Term              | Definition                                                                 | Properties / Implications                                      |
|-------------------|----------------------------------------------------------------------------|----------------------------------------------------------------|
| **General (n-ary) Tree** | No restriction on number of children per node.                             | Flexible hierarchies (e.g., file systems).                     |
| **Binary Tree**   | Each node has **at most 2** children (left/right, ordered).                | Foundation for BSTs, heaps, expression trees.                  |
| **Strictly Binary** | Each internal node has **exactly 2** children.                             | All leaves at the same level in full trees.                     |
| **Full Binary Tree** | Every node has 0 or 2 children (no node has exactly 1 child).           | Leaves are the only nodes with degree 0.                       |
| **Complete Binary Tree** | All levels are fully filled except possibly the last, which is filled left-to-right. | Efficient array representation; basis for heaps.            |
| **Perfect Binary Tree** | All levels completely filled (full + complete).                          | Exactly 2^{h+1}-1 nodes; height h.                              |
| **Balanced Tree** | Height is O(log n); subtrees of any node differ in height by at most a small constant (e.g., ≤1 in AVL). | Guarantees O(log n) operations in search trees.                |
| **Skewed / Degenerate Tree** | All nodes have only one child (behaves like a linked list).            | Height = n-1; worst-case O(n) operations.                      |
| **Ordered Tree**  | Children of each node are ordered (left-to-right significance).            | Essential for binary trees and search properties.               |
| **Plane Tree**    | Ordered + drawn in a plane with consistent child ordering.                | Visual representation standard.                                |

### Formal Operations
General tree operations focus on structure and traversal. Binary trees are similar but with fixed child access.

| Operation              | Description                                                                 | Typical Runtime (Linked) |
|------------------------|-----------------------------------------------------------------------------|--------------------------|
| `isEmpty()`            | Return true if no nodes.                                                    | O(1)                     |
| `size()`               | Number of nodes.                                                            | O(n)                     |
| `height()`             | Height of the tree.                                                         | O(n)                     |
| `root()`               | Return root node.                                                           | O(1)                     |
| `children(node)`       | Return list/sequence of child nodes (general tree).                         | O(degree)                |
| `left(node)` / `right(node)` | For binary trees only.                                              | O(1)                     |
| `parent(node)`         | Return parent (optional).                                                   | O(1)                     |
| `preorder()`           | Root → subtrees.                                                            | O(n)                     |
| `postorder()`          | Subtrees → root.                                                            | O(n)                     |
| `levelorder()`         | Breadth-first, level by level (uses queue).                                 | O(n)                     |
| `inorder()`            | Left → root → right (binary trees only).                                    | O(n)                     |

Construction is explicit (recursive node creation). Specialized trees (BST, heap) add `insert`, `delete`, `search`.

### Error Handling Conventions
- Accessing root/children on empty tree throws exception.
- Traversals on empty trees yield empty sequence.

## Formal Specification (Algebraic)

Trees are defined recursively.

Let `T` be a tree of elements type `E`.

**Constructors** (general tree):
- `empty(): → Tree<E>`
- `node(value: E, children: List<Tree<E>>): → Tree<E>`

For **binary tree**:
- `node(value: E, left: Tree<E>, right: Tree<E>): → BinaryTree<E>`

**Observers** (general):
- `isEmpty(t)`, `rootValue(t)`, `children(t)`

**Axioms** (binary example):
1. `isEmpty(empty()) = true`
2. `isEmpty(node(v, l, r)) = false`
3. `rootValue(node(v, l, r)) = v`
4. `left(node(v, l, r)) = l`
5. `right(node(v, l, r)) = r`

Traversals defined recursively (e.g., preorder):
- `preorder(empty()) = []`
- `preorder(node(v, children)) = [v] + concat(preorder(c) for c in children)`

## Time and Space Complexity Guarantees
- Structural access: O(1) per child/parent.
- Traversals, size, height: O(n).
- Space: Θ(n) nodes + edges (n-1 edges).
- Balanced variants maintain O(log n) height.

## Key Theoretical Properties
- **Acyclic & Connected**: Exactly one path between any two nodes.
- **Node-edge relation**: n nodes ⇒ n-1 edges.
- **Height bounds**: log(n+1) ≤ height ≤ n-1.
- **No cycles**: Fundamental for recursion and unique paths.
- **Inorder traversal** of ordered binary trees (BST) yields sorted order.

## Classic Applications (Theoretical Significance)
1. **File Systems / Hierarchies** – General trees for directories.
2. **Expression / Parse Trees** – Binary trees for arithmetic/compiler syntax.
3. **Binary Search Trees (BST)** – Ordered search/insert/delete.
4. **Heaps** – Complete binary tree for priority queues.
5. **Traversal Algorithms** – DFS (pre/postorder), BFS (levelorder).
6. **Tree-based Search** – Decision trees, game trees (minimax).
7. **Huffman / Trie** – Variable-degree for compression/prefix search.
8. **Self-balancing Trees** – AVL, Red-Black for guaranteed performance.

## Comparison with Similar Structures

| Feature                  | General Tree             | Binary Tree              | Graph                    | Linear List              |
|--------------------------|--------------------------|--------------------------|--------------------------|--------------------------|
| Max children             | Unlimited                | 2                        | Unlimited (edges)        | N/A                      |
| Child ordering           | Often ordered            | Always ordered           | No inherent order        | Sequential               |
| Cycles allowed           | No                       | No                       | Yes                      | No                       |
| Rooted                   | Yes                      | Yes                      | Optional                 | No                       |
| Typical traversals       | Pre/post/level           | Pre/in/post/level        | DFS/BFS                  | Sequential               |
| Common use               | Hierarchies, DOM         | BST, heap, expressions   | Networks                 | Simple access            |

These foundations underpin advanced structures (B-trees, tries, segment trees, etc.).
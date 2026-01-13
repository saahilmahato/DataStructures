## Interview Preparation: Tree Problems

Trees (especially binary trees, BSTs, and traversals) are one of the most heavily tested topics in coding interviews at top tech companies (Google, Meta, Amazon, Apple, Microsoft) and deep tech startups. Interviewers evaluate recursion intuition, traversal mastery (DFS/BFS), understanding of tree properties (height, balance, BST invariants), and ability to solve problems with optimal time/space using divide-and-conquer or iterative techniques.

Below is a curated list of classic tree problems, ordered roughly by increasing difficulty. For each:

- Problem statement (paraphrased LeetCode-style)
- Key insight and approach
- Time and space complexity
- Clean pseudocode

Mastering these demonstrates strong command of recursion, tree traversals, BST properties, and path-based reasoning.

## 1. Maximum Depth of Binary Tree (LeetCode 104, Easy)

**Problem**: Given the root of a binary tree, return its maximum depth (number of nodes along the longest path from root to leaf).

**Approach**: Use recursion: depth of tree = 1 + max(depth of left subtree, depth of right subtree). Base case: empty tree has depth 0. Alternatively, BFS level-order counts levels.

**Complexity**: Time O(n), Space O(h) recursion (O(n) worst-case skewed)

**Pseudocode** (recursive):
```
function maxDepth(root):
    if root is null:
        return 0
    
    left_depth = maxDepth(root.left)
    right_depth = maxDepth(root.right)
    
    return 1 + max(left_depth, right_depth)
```

## 2. Invert Binary Tree (LeetCode 226, Easy)

**Problem**: Given the root of a binary tree, invert the tree (swap every left and right child) and return the new root.

**Approach**: Recursively swap left and right subtrees at every node. Base case: null node returns null. Postorder-style: invert children first, then swap.

**Complexity**: Time O(n), Space O(h) recursion

**Pseudocode**:
```
function invertTree(root):
    if root is null:
        return null
    
    // Swap children
    temp = root.left
    root.left = root.right
    root.right = temp
    
    invertTree(root.left)
    invertTree(root.right)
    
    return root
```

## 3. Validate Binary Search Tree (LeetCode 98, Medium)

**Problem**: Given the root of a binary tree, determine if it is a valid BST: left subtree < node < right subtree (all nodes), no duplicates.

**Approach**: Recursively check each node stays within valid range (min, max). Pass bounds down: left child < node, right child > node. Initial call: (-inf, +inf).

**Complexity**: Time O(n), Space O(h)

**Pseudocode**:
```
function isValidBST(root):
    return helper(root, -infinity, +infinity)

function helper(node, min_val, max_val):
    if node is null:
        return true
    
    if node.val <= min_val or node.val >= max_val:
        return false
    
    return helper(node.left, min_val, node.val) and 
           helper(node.right, node.val, max_val)
```

## 4. Binary Tree Level Order Traversal (LeetCode 102, Medium)

**Problem**: Given the root of a binary tree, return the level-order traversal (values level by level, left to right).

**Approach**: BFS using a queue. Process nodes level by level: enqueue root, then while queue not empty, dequeue current level size, process each node and enqueue children.

**Complexity**: Time O(n), Space O(w) where w is max width (O(n) worst-case)

**Pseudocode**:
```
function levelOrder(root):
    if root is null:
        return []
    
    result = []
    queue = deque([root])
    
    while queue not empty:
        level_size = queue.size()
        current_level = []
        
        for i in 0 to level_size-1:
            node = queue.popleft()
            current_level.append(node.val)
            
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)
        
        result.append(current_level)
    
    return result
```

## 5. Lowest Common Ancestor of a Binary Tree (LeetCode 236, Medium)

**Problem**: Given a binary tree root and two nodes p and q, return their lowest common ancestor (first common ancestor from root).

**Approach**: Recursion: if node is null, return null. If node is p or q, return node. Recurse on left/right. If both sides return non-null, current node is LCA. If only one side, return that side.

**Complexity**: Time O(n), Space O(h)

**Pseudocode**:
```
function lowestCommonAncestor(root, p, q):
    if root is null:
        return null
    if root == p or root == q:
        return root
    
    left = lowestCommonAncestor(root.left, p, q)
    right = lowestCommonAncestor(root.right, p, q)
    
    if left and right:
        return root
    if left:
        return left
    if right:
        return right
    return null
```

## 6. Kth Smallest Element in a BST (LeetCode 230, Medium)

**Problem**: Given root of a BST and integer k, return the kth smallest element (1-indexed).

**Approach**: Inorder traversal of BST gives sorted order. Use iterative inorder with stack to find kth element without storing full list.

**Complexity**: Time O(h + k), Space O(h)

**Pseudocode** (iterative inorder):
```
function kthSmallest(root, k):
    stack = empty
    node = root
    
    while true:
        while node:
            stack.push(node)
            node = node.left
        
        node = stack.pop()
        k -= 1
        if k == 0:
            return node.val
        
        node = node.right
```

## 7. Construct Binary Tree from Preorder and Inorder Traversal (LeetCode 105, Medium)

**Problem**: Given preorder and inorder traversals (no duplicates), construct and return the binary tree.

**Approach**: Preorder first element is root. Find root index in inorder → left subtree size. Recurse on left/right portions of both arrays.

**Complexity**: Time O(n), Space O(n) (with hashmap for inorder indices)

**Pseudocode**:
```
function buildTree(preorder, inorder):
    inorder_map = {val: idx for idx, val in enumerate(inorder)}
    return helper(0, 0, len(inorder)-1)

function helper(pre_start, in_start, in_end):
    if in_start > in_end:
        return null
    
    root_val = preorder[pre_start]
    root = Node(root_val)
    in_root_idx = inorder_map[root_val]
    
    left_size = in_root_idx - in_start
    
    root.left = helper(pre_start + 1, in_start, in_root_idx - 1)
    root.right = helper(pre_start + left_size + 1, in_root_idx + 1, in_end)
    
    return root
```

## 8. Binary Tree Maximum Path Sum (LeetCode 124, Hard)

**Problem**: A path is a sequence of nodes connected by edges. Return the maximum path sum of any non-empty path (can start/end anywhere).

**Approach**: Recursion returns max gain if path goes through current node as single branch. Track global max considering paths that split at node (left + right + node).

**Complexity**: Time O(n), Space O(h)

**Pseudocode**:
```
function maxPathSum(root):
    global_max = -infinity
    
    function gain(node):
        if node is null:
            return 0
        
        left_gain = max(gain(node.left), 0)
        right_gain = max(gain(node.right), 0)
        
        // Path through current node (splitting)
        current_path = node.val + left_gain + right_gain
        global_max = max(global_max, current_path)
        
        // Return max gain for upward path
        return node.val + max(left_gain, right_gain)
    
    gain(root)
    return global_max
```

These problems cover core tree skills: basic recursion, BFS, BST validation/usage, LCA, reconstruction, and advanced path problems. Practice both recursive and iterative approaches, handle edge cases (empty tree, single node), and be ready to discuss optimizations. Good luck!
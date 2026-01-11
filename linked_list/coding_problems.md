## Interview Preparation: Linked List Problems

Linked lists are a core topic in coding interviews at top tech companies (Google, Meta, Amazon, Apple, Microsoft, ByteDance) and systems/design roles (e.g., Uber, Bloomberg, Jane Street). Interviewers focus on pointer manipulation, edge-case handling (empty lists, single node, cycles), in-place operations, and classic patterns: **fast-slow pointers**, **reversal**, **dummy nodes**, **recursive merging**, and **doubly-linked splicing** (e.g., LRU).

Below is a curated list of classic linked list problems, ordered roughly by increasing difficulty. For each:

- Problem statement
- Key insight and approach
- Time and space complexity
- Clean pseudocode (assuming `class ListNode { val, next }`)

### 1. Reverse Linked List (LeetCode 206, Easy)

**Problem**: Given the head of a singly linked list, reverse the list and return the new head.

**Approach**: Iterative pointer reversal with three pointers (prev, curr, next). Recursive version also common but uses O(n) stack space.

**Complexity**: Time O(n), Space O(1) iterative

**Pseudocode** (iterative):
```python
function reverseList(head):
    prev = null
    curr = head
    
    while curr is not null:
        next_temp = curr.next
        curr.next = prev
        prev = curr
        curr = next_temp
    
    return prev
```

### 2. Linked List Cycle (LeetCode 141, Easy)

**Problem**: Given head, return true if the linked list has a cycle.

**Approach**: Floyd’s tortoise and hare (fast-slow pointers). Slow moves 1 step, fast moves 2. They meet only if cycle exists.

**Complexity**: Time O(n), Space O(1)

**Pseudocode**:
```python
function hasCycle(head):
    if head is null or head.next is null:
        return false
    
    slow = head
    fast = head
    
    while fast is not null and fast.next is not null:
        slow = slow.next
        fast = fast.next.next
        if slow == fast:
            return true
    
    return false
```

### 3. Merge Two Sorted Lists (LeetCode 21, Easy)

**Problem**: Merge two sorted linked lists into one sorted list. Return the head of the merged list.

**Approach**: Use a dummy node, iterate with two pointers, always append the smaller current node.

**Complexity**: Time O(n + m), Space O(1) iterative

**Pseudocode**:
```python
function mergeTwoLists(l1, l2):
    dummy = ListNode(0)
    tail = dummy
    
    while l1 is not null and l2 is not null:
        if l1.val <= l2.val:
            tail.next = l1
            l1 = l1.next
        else:
            tail.next = l2
            l2 = l2.next
        tail = tail.next
    
    tail.next = l1 if l1 is not null else l2
    
    return dummy.next
```

### 4. Remove Nth Node From End of List (LeetCode 19, Medium)

**Problem**: Given head and integer n, remove the nth node from the end and return the new head.

**Approach**: One-pass: fast pointer moves n steps ahead, then slow and fast move together until fast reaches end—slow is at node before target.

**Complexity**: Time O(n), Space O(1)

**Pseudocode**:
```python
function removeNthFromEnd(head, n):
    dummy = ListNode(0)
    dummy.next = head
    fast = dummy
    slow = dummy
    
    for i in 0 to n:
        fast = fast.next
    
    while fast is not null:
        slow = slow.next
        fast = fast.next
    
    slow.next = slow.next.next
    
    return dummy.next
```

### 5. Add Two Numbers (LeetCode 2, Medium)

**Problem**: Two non-empty linked lists represent two non-negative integers (digits reversed, least significant first). Add them and return sum as linked list.

**Approach**: Iterate both lists, add digits + carry, create new nodes. Handle remaining nodes and final carry.

**Complexity**: Time O(max(n,m)), Space O(max(n,m))

**Pseudocode**:
```python
function addTwoNumbers(l1, l2):
    dummy = ListNode(0)
    tail = dummy
    carry = 0
    
    while l1 is not null or l2 is not null or carry > 0:
        val1 = l1.val if l1 else 0
        val2 = l2.val if l2 else 0
        total = val1 + val2 + carry
        carry = total // 10
        tail.next = ListNode(total % 10)
        tail = tail.next
        
        if l1: l1 = l1.next
        if l2: l2 = l2.next
    
    return dummy.next
```

### 6. Linked List Cycle II (LeetCode 142, Medium)

**Problem**: Given head, return the node where the cycle begins (or null if no cycle).

**Approach**: First detect cycle with Floyd’s. Once tortoise and hare meet, reset tortoise to head and move both one step—they meet at cycle entry.

**Complexity**: Time O(n), Space O(1)

**Pseudocode**:
```python
function detectCycle(head):
    if head is null or head.next is null:
        return null
    
    slow = head
    fast = head
    
    while fast is not null and fast.next is not null:
        slow = slow.next
        fast = fast.next.next
        if slow == fast:
            break
    
    if fast is null or fast.next is null:
        return null
    
    slow = head
    while slow != fast:
        slow = slow.next
        fast = fast.next
    
    return slow
```

### 7. LRU Cache (LeetCode 146, Hard)

**Problem**: Design LRU cache with get(key) and put(key, value). Both O(1).

**Approach**: Hash map + doubly linked list. Map stores key → node. List ordered most-recent (head) to least-recent (tail). On access/move to head, on put evict tail if full.

**Complexity**: Time O(1) per operation, Space O(capacity)

**Pseudocode** (high-level):
```python
class LRUCache:
    capacity
    map = {}  # key → node
    dll = DoublyLinkedList with head and tail sentinels
    
    function get(key):
        if key not in map:
            return -1
        node = map[key]
        dll.moveToHead(node)
        return node.value
    
    function put(key, value):
        if key in map:
            node = map[key]
            node.value = value
            dll.moveToHead(node)
        else:
            if dll.size == capacity:
                tail_node = dll.removeTail()
                del map[tail_node.key]
            new_node = Node(key, value)
            dll.addToHead(new_node)
            map[key] = new_node
```

These problems span the full range of linked list techniques. Practice implementing cleanly, explain pointer updates clearly, and handle all edge cases. Good luck!
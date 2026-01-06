## Interview Preparation: Queue Problems

Queues are a staple in coding interviews at top tech companies (Google, Meta, Amazon, Apple, Microsoft, ByteDance) and systems-focused roles (e.g., Uber, Roblox, Jane Street). Interviewers test not only correct queue implementation but also creative applications: BFS for shortest paths/level-order processing, simulation with multiple queues, circular buffers for efficiency, and **monotonic deques** for O(n) sliding-window optimizations where naive approaches are O(nk).

Below is a curated list of classic queue problems, ordered roughly by increasing difficulty. For each:

- Problem statement (paraphrased LeetCode-style)
- Key insight and approach
- Time and space complexity
- Clean pseudocode

Mastering this demonstrates mastery of FIFO semantics, BFS modeling, amortization, and advanced deque techniques.

## 1. Implement Stack using Queues (LeetCode 225, Easy)

**Problem**: Implement a stack using only queues. Support push, pop, top, and empty.

**Approach**: Use a single queue. On push(x), enqueue x, then rotate the queue (dequeue and enqueue existing elements) to bring the newest element to the front (which acts as the stack top).

**Complexity**: push O(n) worst-case (amortized lower in mixed ops), others O(1). Space O(n)

**Pseudocode**:
```
class MyStack:
    q = empty queue
    
    function push(x):
        q.enqueue(x)
        for i in 1 to q.size() - 1:
            q.enqueue(q.dequeue())
    
    function pop():
        return q.dequeue()
    
    function top():
        return q.front()
    
    function empty():
        return q.isEmpty()
```

## 2. Number of Recent Calls (LeetCode 933, Easy)

**Problem**: Design a class RecentCounter with method ping(t) that returns the number of pings in the range [t - 3000, t] inclusive. Pings arrive in increasing t.

**Approach**: Maintain a queue of timestamps. On each ping(t), enqueue t and dequeue old timestamps < t - 3000. Queue size is the answer.

**Complexity**: Amortized O(1) per ping, Space O(W) where W ≈ 3001 worst-case

**Pseudocode**:
```
class RecentCounter:
    q = empty queue
    
    function ping(t):
        q.enqueue(t)
        while not q.isEmpty() and q.front() < t - 3000:
            q.dequeue()
        return q.size()
```

## 3. Design Circular Queue (LeetCode 622, Medium)

**Problem**: Design a fixed-size circular queue supporting enqueue, dequeue, Front, Rear, isEmpty, isFull.

**Approach**: Use a fixed array with front/rear indices and modulo arithmetic. Track size separately to distinguish full vs empty (or waste one slot).

**Complexity**: All operations O(1), Space O(k)

**Pseudocode** (using size counter):
```
class MyCircularQueue:
    arr = array of size k
    front = 0
    rear = 0
    size = 0
    
    function enQueue(value):
        if isFull(): return false
        arr[rear] = value
        rear = (rear + 1) % k
        size += 1
        return true
    
    function deQueue():
        if isEmpty(): return false
        front = (front + 1) % k
        size -= 1
        return true
    
    function Front():
        if isEmpty(): return -1
        return arr[front]
    
    function Rear():
        if isEmpty(): return -1
        return arr[(rear - 1 + k) % k]
    
    function isEmpty():
        return size == 0
    
    function isFull():
        return size == k
```

## 4. Dota2 Senate (LeetCode 649, Medium)

**Problem**: Given string senate of 'R' and 'D', simulate round-based voting where the winner bans the next opponent’s senator. Return "Radiant" or "Dire" for the winner.

**Approach**: Use two queues storing indices of R and D senators. In each round, compare front indices: the smaller (earlier) wins, bans the loser, and reenqueues itself at index + n (next round).

**Complexity**: Time O(n), Space O(n)

**Pseudocode**:
```
function predictPartyVictory(senate):
    n = length(senate)
    qR = queue of indices where senate[i] == 'R'
    qD = queue of indices where senate[i] == 'D'
    
    while not qR.isEmpty() and not qD.isEmpty():
        r = qR.dequeue()
        d = qD.dequeue()
        if r < d:
            qR.enqueue(r + n)   // R bans D, comes back later
        else:
            qD.enqueue(d + n)
    
    return "Radiant" if not qR.isEmpty() else "Dire"
```

## 5. Rotten Oranges (LeetCode 994, Medium)

**Problem**: In a grid, 0=empty, 1=fresh, 2=rotten. Every minute, rotten oranges infect adjacent fresh ones. Return minimum minutes until no fresh remain, or -1 if impossible.

**Approach**: Multi-source BFS. Queue all initial rotten positions with time 0. BFS to spread rot, track remaining fresh count and max time.

**Complexity**: Time O(mn), Space O(mn)

**Pseudocode**:
```
function orangesRotting(grid):
    rows, cols = grid dimensions
    q = empty queue
    fresh = 0
    for each cell (i,j):
        if grid[i][j] == 2: q.enqueue((i,j,0))
        if grid[i][j] == 1: fresh += 1
    
    minutes = 0
    directions = [(-1,0),(1,0),(0,-1),(0,1)]
    
    while not q.isEmpty() and fresh > 0:
        i, j, time = q.dequeue()
        minutes = max(minutes, time)
        for di, dj in directions:
            ni, nj = i+di, j+dj
            if valid(ni,nj) and grid[ni][nj] == 1:
                grid[ni][nj] = 2
                fresh -= 1
                q.enqueue((ni,nj,time+1))
    
    return minutes if fresh == 0 else -1
```

## 6. Open the Lock (LeetCode 752, Medium)

**Problem**: Start from "0000", turn one wheel +1 or -1 per move. Given deadends and target, return minimum turns to reach target (-1 if impossible).

**Approach**: BFS treating each lock state as a node. Queue states with distance, use set for visited/deadends.

**Complexity**: Time O(10000) = O(1) effectively (4^4 states), Space O(10000)

**Pseudocode**:
```
function openLock(deadends, target):
    if "0000" in deadends: return -1
    visited = set including deadends + "0000"
    q = queue with ("0000", 0)  // state, turns
    
    while not q.isEmpty():
        state, turns = q.dequeue()
        if state == target: return turns
        
        for wheel in 0 to 3:
            for delta in [-1, 1]:
                new_digit = (int(state[wheel]) + delta + 10) % 10
                new_state = state with wheel changed to new_digit
                if new_state not in visited:
                    visited.add(new_state)
                    q.enqueue((new_state, turns + 1))
    
    return -1
```

## 7. Sliding Window Maximum (LeetCode 239, Hard)

**Problem**: Given array nums and integer k, return array of maximum values in each window of size k.

**Approach**: Monotonic decreasing deque of indices. Maintain front as index of current window maximum. Remove out-of-window and smaller elements from back.

**Complexity**: Time O(n) amortized (each index entered/exited ≤1 time), Space O(k)

**Pseudocode**:
```
function maxSlidingWindow(nums, k):
    n = length(nums)
    if n == 0: return []
    deque = empty deque  // stores indices, decreasing nums values
    result = []
    
    for i in 0 to n-1:
        // remove out-of-window
        if not deque.isEmpty() and deque.front() == i - k:
            deque.pop_front()
        
        // remove smaller than nums[i]
        while not deque.isEmpty() and nums[deque.back()] < nums[i]:
            deque.pop_back()
        
        deque.push_back(i)
        
        if i >= k - 1:
            result.append(nums[deque.front()])
    
    return result
```

These problems span the full range: queue-based stack simulation, circular buffers, time-window tracking, multi-queue simulation, multi-source BFS, state-space BFS, and monotonic deques. Practice implementing cleanly in your preferred language, explain amortization and edge cases, and be ready for follow-ups (e.g., “Make it thread-safe” or “Handle larger state space”). Good luck!
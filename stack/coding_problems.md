## Interview Preparation: Stack Problems**

Stacks are a frequent topic in coding interviews at top companies (Google, Meta, Amazon, Apple, Microsoft, etc.) and deep tech startups. Interviewers test not only correct implementation of the ADT but also creative use of stacks to solve problems efficiently—often involving **O(n)** time solutions where naive approaches are quadratic.

Below is a curated list of classic stack problems, ordered roughly by increasing difficulty. For each:

- Problem statement (paraphrased from common LeetCode-style)
- Key insight and approach
- Time and space complexity
- Clean pseudocode

Mastering this demonstrates deep understanding of stacks, monotonic stacks, and auxiliary stack techniques.

## 1. Valid Parentheses (LeetCode 20, Easy)

**Problem**: Given a string containing only '(', ')', '{', '}', '[', ']', determine if it is valid. Parentheses must close in correct order.

**Approach**: Use a stack to track opening brackets. For each closing bracket, check if stack top matches the corresponding opening. Push openings, pop on matching close.

**Complexity**: Time O(n), Space O(n)

**Pseudocode**:
```
function isValid(s):
    stack = empty stack
    mapping = {')':'(', '}':'{', ']':'['}
    
    for char in s:
        if char in mapping.values():          // opening
            stack.push(char)
        else if char in mapping:              // closing
            if stack.isEmpty() or stack.pop() != mapping[char]:
                return false
        else:
            return false                      // invalid char (though problem guarantees valid chars)
    
    return stack.isEmpty()
```

## 2. Min Stack (LeetCode 155, Medium)

**Problem**: Design a stack that supports push, pop, top, and getMin() in O(1) time.

**Approach**: Use two stacks: main stack for elements, min_stack to track current minimum. On push, push value to main and min(current_min, value) to min_stack. On pop, pop both.

**Complexity**: All operations O(1) time, O(n) space

**Pseudocode**:
```
class MinStack:
    main = empty stack
    min_stack = empty stack
    
    function push(val):
        main.push(val)
        if min_stack.isEmpty():
            min_stack.push(val)
        else:
            min_stack.push(min(val, min_stack.top()))
    
    function pop():
        main.pop()
        min_stack.pop()
    
    function top():
        return main.top()
    
    function getMin():
        return min_stack.top()
```

## 3. Evaluate Reverse Polish Notation (LeetCode 150, Medium)

**Problem**: Evaluate value of arithmetic expression in Reverse Polish Notation (postfix). Tokens are integers or operators +, -, *, /.

**Approach**: Use stack for operands. On operator, pop two operands, apply operation, push result.

**Complexity**: Time O(n), Space O(n)

**Pseudocode**:
```
function evalRPN(tokens):
    stack = empty stack
    operators = {'+', '-', '*', '/'}
    
    for token in tokens:
        if token not in operators:
            stack.push(integer(token))
        else:
            b = stack.pop()
            a = stack.pop()
            if token == '+': result = a + b
            else if token == '-': result = a - b
            else if token == '*': result = a * b
            else: result = truncate(a / b toward zero)  // integer division
            stack.push(result)
    
    return stack.pop()
```

## 4. Daily Temperatures (LeetCode 739, Medium)

**Problem**: Given array temperatures where temperatures[i] is daily temperature, return array where answer[i] is number of days until a warmer temperature. If none, use 0.

**Approach**: Monotonic decreasing stack of indices. Iterate right to left (or left to right with while loop). For each day, pop cooler previous days, compute distance to nearest warmer.

**Complexity**: Time O(n), Space O(n) amortized (each index pushed/popped ≤1 time)

**Pseudocode** (right-to-left):
```
function dailyTemperatures(T):
    n = length(T)
    answer = array of zeros size n
    stack = empty stack  // indices, decreasing temperatures
    
    for i from n-1 downto 0:
        while not stack.isEmpty() and T[stack.top()] <= T[i]:
            stack.pop()
        if not stack.isEmpty():
            answer[i] = stack.top() - i
        stack.push(i)
    
    return answer
```

## 5. Largest Rectangle in Histogram (LeetCode 84, Hard)

**Problem**: Given array heights of bar heights, find area of largest rectangle in histogram.

**Approach**: Monotonic increasing stack of indices. For each bar, pop taller previous bars, compute area with popped bar as smallest height. Use sentinel -1 height at ends.

**Complexity**: Time O(n), Space O(n)

**Pseudocode**:
```
function largestRectangleArea(heights):
    n = length(heights)
    stack = empty stack  // indices, increasing heights
    heights = heights + [-1]  // sentinel
    max_area = 0
    
    for i in 0 to n:  // includes sentinel
        while not stack.isEmpty() and heights[stack.top()] >= heights[i]:
            h = heights[stack.pop()]
            w = i - (stack.top() if not empty else -1) - 1
            max_area = max(max_area, h * w)
        stack.push(i)
    
    return max_area
```

## 6. Trapping Rain Water (LeetCode 42, Hard)

**Problem**: Given array height representing elevation map, compute how much water it can trap after raining.

**Approach**: Monotonic decreasing stack of indices. When a taller bar is found, compute trapped water in "valley" formed by previous bars.

Alternative two-pointer is common, but stack solution is elegant.

**Complexity**: Time O(n), Space O(n)

**Pseudocode**:
```
function trap(height):
    n = length(height)
    stack = empty stack  // indices, decreasing heights
    water = 0
    
    for i in 0 to n-1:
        while not stack.isEmpty() and height[i] > height[stack.top()]:
            top = stack.pop()
            if stack.isEmpty(): break
            left = stack.top()
            bounded_h = min(height[i], height[left]) - height[top]
            width = i - left - 1
            water += bounded_h * width
        stack.push(i)
    
    return water
```

## 7. Implement Queue using Stacks (LeetCode 232, Easy)

**Problem**: Implement a queue using only two stacks. Support enqueue, dequeue, peek, empty.

**Approach**: Use input stack for enqueue. For dequeue/peek, if output stack empty, transfer all from input to output (reversing order).

**Complexity**: Amortized O(1) per operation, worst-case O(n)

**Pseudocode**:
```
class MyQueue:
    in_stack = empty stack
    out_stack = empty stack
    
    function enqueue(x):
        in_stack.push(x)
    
    function transfer_if_needed():
        if out_stack.isEmpty():
            while not in_stack.isEmpty():
                out_stack.push(in_stack.pop())
    
    function dequeue():
        transfer_if_needed()
        return out_stack.pop()
    
    function peek():
        transfer_if_needed()
        return out_stack.top()
    
    function empty():
        return in_stack.isEmpty() and out_stack.isEmpty()
```

These problems cover the spectrum: basic stack usage, auxiliary stacks, monotonic stacks, and amortized analysis. Practice implementing in your language of choice (Python/Java/C++) under time pressure, and be ready to discuss trade-offs and edge cases. Good luck!
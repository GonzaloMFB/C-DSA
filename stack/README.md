# Stack

A stack is a linear data structure that follows the Last In, First Out (LIFO) principle. This implementation uses a dynamic array with automatic resizing to provide efficient stack operations with unlimited capacity.

## Data Structure Overview

A stack operates like a stack of plates where you can only:
- **Push**: Add elements to the top
- **Pop**: Remove elements from the top
- **Peek**: Look at the top element without removing it

The most recently added element is the first one to be removed, making it perfect for scenarios requiring reverse order processing.

## Stack Structure

```c
typedef struct Stack {
    int max_length;  // Current capacity of the stack
    int count;       // Number of elements currently in stack
    int* array;      // Dynamic array storing the elements
} Stack;
```

## Time Complexity

| Operation | Time Complexity | Description |
|-----------|----------------|-------------|
| Push | O(1) amortized | Add element to top |
| Pop | O(1) | Remove element from top |
| Peek | O(1) | View top element |
| Is Empty | O(1) | Check if stack is empty |
| Resize | O(n) | Only when capacity exceeded |

## Space Complexity
- **Memory**: O(n) where n is the maximum capacity
- **Dynamic Growth**: Automatically doubles when full

## Core Functions

### Memory Management
- `create_stack(int size)` - Creates stack with initial capacity
- `destroy(Stack* stack)` - Frees memory used by the stack
- `resize(Stack* stack)` - Doubles capacity when needed (internal function)

### Stack Operations
- `push(int val, Stack* stack)` - Adds element to top of stack
- `pop(Stack* stack)` - Removes top element from stack
- `peek(Stack* stack)` - Returns pointer to top element (NULL if empty)
- `is_empty(Stack* stack)` - Returns 1 if empty, 0 otherwise

## Usage Examples

### Basic Stack Operations

```c
#include "stack.h"
#include <stdio.h>

int main() {
    // Create stack with initial capacity of 5
    Stack* stack = create_stack(5);
    
    // Push elements onto stack
    push(10, stack);
    push(20, stack);
    push(30, stack);
    push(40, stack);
    push(50, stack);
    
    printf("Stack count: %d\n", stack->count);  // Output: 5
    
    // Peek at top element
    int* top = peek(stack);
    if (top) {
        printf("Top element: %d\n", *top);  // Output: 50
    }
    
    // Pop elements (LIFO order)
    printf("Popping elements: ");
    while (!is_empty(stack)) {
        int* val = peek(stack);
        if (val) {
            printf("%d ", *val);
        }
        pop(stack);
    }
    printf("\n");  // Output: 50 40 30 20 10
    
    // Clean up
    destroy(stack);
    return 0;
}
```

### Dynamic Resizing Example

```c
void resize_demo() {
    // Create small stack to demonstrate resizing
    Stack* stack = create_stack(2);
    
    printf("Initial capacity: %d\n", stack->max_length);  // Output: 2
    
    // Fill stack beyond initial capacity
    for (int i = 1; i <= 5; i++) {
        push(i * 10, stack);
        printf("Pushed %d, capacity: %d, count: %d\n", 
               i * 10, stack->max_length, stack->count);
    }
    // Stack automatically resizes: 2 -> 4 -> 8
    
    destroy(stack);
}
```

### Practical Applications

```c
// Parentheses matching
int is_balanced(char* expression) {
    Stack* stack = create_stack(100);
    
    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];
        
        if (ch == '(' || ch == '[' || ch == '{') {
            push(ch, stack);
        }
        else if (ch == ')' || ch == ']' || ch == '}') {
            if (is_empty(stack)) {
                destroy(stack);
                return 0;  // Unmatched closing bracket
            }
            
            int* top = peek(stack);
            char opening = *top;
            pop(stack);
            
            if ((ch == ')' && opening != '(') ||
                (ch == ']' && opening != '[') ||
                (ch == '}' && opening != '{')) {
                destroy(stack);
                return 0;  // Mismatched brackets
            }
        }
    }
    
    int balanced = is_empty(stack);
    destroy(stack);
    return balanced;
}

// Reverse a string using stack
void reverse_string(char* str) {
    Stack* stack = create_stack(100);
    int len = strlen(str);
    
    // Push all characters onto stack
    for (int i = 0; i < len; i++) {
        push(str[i], stack);
    }
    
    // Pop characters back to string (reversed order)
    for (int i = 0; i < len; i++) {
        int* ch = peek(stack);
        if (ch) {
            str[i] = *ch;
        }
        pop(stack);
    }
    
    destroy(stack);
}

// Evaluate postfix expression
int evaluate_postfix(char* expression) {
    Stack* stack = create_stack(100);
    
    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];
        
        if (isdigit(ch)) {
            push(ch - '0', stack);  // Convert char to int
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            if (stack->count < 2) {
                destroy(stack);
                return -1;  // Invalid expression
            }
            
            int* b = peek(stack); pop(stack);
            int* a = peek(stack); pop(stack);
            
            int result;
            switch (ch) {
                case '+': result = *a + *b; break;
                case '-': result = *a - *b; break;
                case '*': result = *a * *b; break;
                case '/': result = *a / *b; break;
            }
            push(result, stack);
        }
    }
    
    int* final_result = peek(stack);
    int result = final_result ? *final_result : 0;
    destroy(stack);
    return result;
}
```

## Building and Testing

Compile the test program:
```bash
gcc -o test_stack test_stack.c stack.c
```

Run the tests:
```bash
./test_stack
```

## Dynamic Resizing

The stack automatically grows when needed:
1. **Initial Capacity**: Set during creation
2. **Growth Trigger**: When push() is called on full stack
3. **Growth Strategy**: Double the current capacity
4. **Memory Management**: Old array is freed after copying

### Resize Process
```c
// Conceptual resize operation
void resize(Stack* stack) {
    int new_capacity = stack->max_length * 2;
    int* new_array = malloc(new_capacity * sizeof(int));
    
    // Copy existing elements
    for (int i = 0; i < stack->count; i++) {
        new_array[i] = stack->array[i];
    }
    
    free(stack->array);
    stack->array = new_array;
    stack->max_length = new_capacity;
}
```

## Applications

Stacks are fundamental in many computing scenarios:

### System Software
- **Function Call Stack**: Managing function calls and local variables
- **Expression Parsing**: Converting infix to postfix notation
- **Compiler Design**: Syntax analysis and code generation
- **Memory Management**: Stack-based allocation

### Algorithm Implementation
- **Depth-First Search**: Graph and tree traversal
- **Backtracking**: N-Queens, maze solving, Sudoku
- **Recursion Simulation**: Convert recursive to iterative
- **Undo Operations**: Editor applications, game states

### Web Development
- **Browser History**: Back button functionality
- **Call Stack**: JavaScript execution context
- **Expression Evaluation**: Calculator implementations
- **Template Processing**: Nested tag matching

## Advantages

1. **Simple Implementation**: Easy to understand and implement
2. **Efficient Operations**: All main operations are O(1)
3. **Memory Efficient**: Only allocates space for stored elements
4. **Dynamic Size**: Grows automatically as needed
5. **LIFO Access**: Perfect for reverse-order processing

## Disadvantages

1. **Limited Access**: Can only access the top element
2. **No Random Access**: Cannot access arbitrary elements
3. **Memory Overhead**: Dynamic resizing may allocate unused space
4. **Stack Overflow**: Recursive usage can exceed memory limits

## Comparison with Other Data Structures

| Feature | Stack | Queue | Array | Linked List |
|---------|-------|-------|-------|-------------|
| Insert | O(1) top only | O(1) rear only | O(1) end, O(n) middle | O(1) head, O(n) middle |
| Delete | O(1) top only | O(1) front only | O(1) end, O(n) middle | O(1) head, O(n) middle |
| Access | O(1) top only | O(1) front/rear | O(1) random | O(n) sequential |
| Memory | Contiguous | Contiguous/Linked | Contiguous | Fragmented |
| Use Case | LIFO operations | FIFO operations | Random access | Dynamic insertion |

## Memory Management Notes

- Always check `is_empty()` before calling `pop()` or `peek()`
- `peek()` returns a pointer - check for NULL before dereferencing
- Use `destroy()` to prevent memory leaks
- Stack automatically handles capacity management
- Elements are stored by value, not reference

## Common Stack Patterns

### Stack as Function Call Simulator
```c
// Simulate recursive factorial using stack
int factorial_iterative(int n) {
    Stack* stack = create_stack(n);
    push(n, stack);
    
    int result = 1;
    while (!is_empty(stack)) {
        int* val = peek(stack);
        result *= *val;
        pop(stack);
    }
    
    destroy(stack);
    return result;
}
```

### Stack for Backtracking
```c
// Use stack to track path in maze solving
typedef struct {
    int x, y;
} Point;

// Stack would store Point structures for path tracking
// Push when moving forward, pop when backtracking
```
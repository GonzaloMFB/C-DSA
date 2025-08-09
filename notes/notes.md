# C Data Structures: Study Notes

---

## 1. Hash Map

### Core Concepts
- **Purpose:** Key-value store for fast lookup, insertion, and deletion.
- **Implementation:** Array of buckets (entries), each holding a key-value pair. Uses a hash function to map keys to buckets.
- **Collision Handling:** Often uses open addressing (probing) or chaining (linked lists in buckets).

### Key Operations
- **Insert:** Hash the key, find a bucket, handle collisions, store key-value.
- **Get:** Hash the key, probe for the key, return value or sentinel if not found.
- **Delete:** Hash the key, probe, remove entry, handle tombstones if open addressing.
- **Resize:** When load factor exceeds a threshold, double the array size and rehash all entries.
- **Cleanup:** Free all allocated memory for entries and the hash map itself.

### C-Specific Lessons
- Always check `malloc` results for `NULL`.
- Free all allocated memory to avoid leaks.
- Use clear error messages and sentinel values for error signaling.

---

## 2. Dynamic Array (Vector)

### Core Concepts
- **Purpose:** Array that resizes automatically as elements are added.
- **Implementation:** Struct with a pointer to a heap-allocated array, a count of elements, and a capacity (max size).

### Key Operations
- **Create:** Allocate initial array, set count to 0, set initial capacity.
- **Append:** Add element at end, resize if count exceeds threshold (commonly 0.7 * capacity).
- **Insert:** Insert at index, shift elements to make space, resize if needed.
- **Pop:** Remove last element, decrement count.
- **Get/Set:** Access/modify elements by index with bounds checking.
- **Resize:** Allocate a larger array, copy elements, free old array.
- **Clear:** Reset count to 0, optionally zero out array for debugging.
- **Destroy:** Free the array.

### C-Specific Lessons
- Use pointers for heap memory, not stack arrays.
- Always check for out-of-bounds access.
- Memory safety: free arrays, check `malloc`, avoid buffer overruns.

---

## 3. Singly Linked List

### Core Concepts
- **Purpose:** Sequence of nodes, each pointing to the next; allows efficient insertion/removal at the head.
- **Implementation:** Each node has a value and a pointer to the next node. The list is referenced by a pointer to the head node.

### Key Operations
- **Create Node:** Allocate with `malloc`, set value and next pointer.
- **Prepend:** Insert at head; requires a pointer to the head pointer (`Node**`) to update it.
- **Append:** Traverse to last node and add new node. For empty lists, may require special handling.
- **Insert at Index:** Traverse to node before index, insert new node. Use `Node**` for head updates.
- **Remove at Index:** Traverse to node before index, remove node, free memory. Use `Node**` for head removal.
- **Get at Index:** Traverse to index, return value or sentinel if out of bounds.
- **Find by Value:** Traverse, return pointer to node or `NULL`.
- **Length:** Traverse and count nodes.
- **Destroy:** Traverse, free each node.

### Pointer Semantics
- Use `Node*` for traversing and modifying node contents.
- Use `Node**` when you may need to update the head pointer in the caller.
- Operator precedence: always use [(*list)->next](cci:1://file:///home/gmfb/dev/c_projects/dsl/s_linked_list/test_s_linked_list.c:33:0-39:1), not `*list->next`.

### C-Specific Lessons
- Always check for `NULL` before dereferencing.
- Free all nodes to avoid memory leaks.
- Handle edge cases: empty list, out-of-bounds indices, head insertion/removal.

---

## General C Data Structure Best Practices

- **Memory Management:** Always pair `malloc`/`calloc` with `free`. Check for allocation failures.
- **Defensive Programming:** Check for `NULL` pointers, invalid indices, and handle errors gracefully.
- **Testing:** Write comprehensive tests for all operations, including edge cases.
- **API Design:** Use clear function signatures. Use pointer-to-pointer or return new head when the head may change.
# D-ary Post-order Heap

C++ library implementing the post-order heap as described by:

Nicholas J. A. Harvey and Kevin C. Zatloukal. 
The post-order heap.
In Proc. Third International Conference on Fun with Algorithms
(FUN), 2004.
http://people.csail.mit.edu/nickh/Publications/PostOrderHeap/FUN04-PostOrderHeap.pdf

This implementation is adapted to support heaps of any degree.

## Usage

The interface, and template, is designed to mimic that of the [C++ standard priority_queue](https://en.cppreference.com/w/cpp/container/priority_queue)
```cpp
template <
          class T, 
          class Container = std::vector<T>, 
          class Compare = std::less<typename Container::value_type>
> class post_order_heap
```
#### Template parameters
  1. **T** - Element type, must equal Container::value_type.
  3. **Container** - The type of the container. Must satisfy the requirements of SequenceContainer, and its iterator must satisfy the requirements of LegacyRandomAccessIterator.
  4. **Compare** - A compare type providing strict weak ordering. ***NOTE***: The heap outputs smallest elements first, unlike std::priority_queue. That is, the front/root of the heap contains the "first" element according to the weak ordering imposed by Compare.

### Construction

Construction of heaps can happen using the following three kinds of constructors:

**The explicit constructor**

```cpp
    auto comparator = [](int left, int right) {
        return left < right;
    };
    int heap_degree = 4;
    post_order_heap<int, std::vector<int>, decltype(comparator)> heap(comparator, heap_degree);
```

All necessary parameters are supplied. Creates a post-order heap with the specified degree, and a custom comparator.

**The binary constructor with custom comparator**

```cpp
    auto comparator = [](int left, int right) {
        return left < right;
    };
    post_order_heap<int, std::vector<int>, decltype(comparator)> heap(comparator);
```

Creates a post-order heap with degree two, and a custom comparator.

**The implicit constructor**

```cpp
    post_order_heap<int, std::vector<int>, std::less<>> heap{};
```
Creates a post-order heap with degree two, using std::less<> as the comparator.

### Push, Poll, Pop & Top

```cpp
    post_order_heap<int, std::vector<int>, std::less<>> heap{};
    
    heap.push(7);
    heap.push(33);
    heap.push(13);
    heap.push(42);
    
    int pop = heap.pop(); // pop = 7
    int top = heap.top(); // top = 13
    heap.pop();
    top = top(); // top = 33;
```

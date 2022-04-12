//
// Created by nicolaj on 3/27/22.
//
// Inspired by:
// Nicholas J. A. Harvey and Kevin C. Zatloukal.
// The post-order heap.
// In Proc. Third International Conference on Fun with Algorithms
// (FUN), 2004.
// http://people.csail.mit.edu/nickh/Publications/PostOrderHeap/FUN04-PostOrderHeap.pdf
//
// Adapted by Nicolaj Kuno Bræmhøj for variable degree.
// Contact: nicolaj (at) braemhoej (dot) me
//
#ifndef POSTORDER_HEAP_LIBRARY_HPP
#define POSTORDER_HEAP_LIBRARY_HPP

#include <vector>
#include <functional>

template <class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type>> class postorder_heap {
    typedef typename Container::size_type size_type;
    typedef typename Container::value_type value_type;
    typedef typename Container::const_reference const_reference;
private:
    // The underlying container
    Container _container;
    // Comparator used for comparisons
    Compare _comparator;
    // The degree of the implicit heaps.
    int _degree;
    // Sizes of the implicit heaps.
    std::vector<int> _sizes;
    /**
     *
     * @param index
     * @param size
     */
    void heapify(int index, int size_of_subtree) {
        T initial_root = _container[index];
        while (size_of_subtree > 1) {
            size_of_subtree /= _degree;
            int right_child_index = (index - 1);
            int prioritised_child_index = right_child_index;
            T prioritised_child = _container[right_child_index];
            for (int child_offset = 1; child_offset < _degree; child_offset++) {
                int childIndex = right_child_index - (child_offset * size_of_subtree);
                T child = _container[childIndex];
                if (_comparator(child, prioritised_child)) {
                    prioritised_child_index = childIndex;
                    prioritised_child = child;
                }
            }
            if (!_comparator(prioritised_child, initial_root))
                break;
            _container[index] = prioritised_child;
            index = prioritised_child_index;
        }
        _container[index] = initial_root;
    }
public:
    /**
     * Trivial destructor.
     */
    ~postorder_heap() = default;
    /**
     * Default constructor, degree = 2 and standard '<' comparator is used.
     */
    explicit postorder_heap() : postorder_heap(Compare(), 2) // Constructor delegation
    { }
    /**
     * Constructor with custom comparator and degree = 2;
     * @param comparator
     */
    postorder_heap(Compare comparator) : postorder_heap(comparator, 2) // Constructor delegation
    { }
    /**
     * Constructor with custom comparator and specified degree.
     * @param comparator
     * @param degree
     */
    postorder_heap(Compare comparator, int degree) :
    _container(Container()),
                                                               _comparator(comparator),
                                                               _degree(degree),
                                                               _sizes(std::vector<int>())
    { }

    /**
     * Pushes and element to the back of the container and ensures that post-order heap-ordering is preserved.
     * @param element to insert
     */
    void push(const value_type &element) {
        _container.push_back(element);
        if (_sizes.size() >= _degree) {
            bool should_merge_trees = true;
            for (int offset = 1; offset < _degree; offset++) {
                int tree_index = _sizes.size() - offset;
                should_merge_trees &= _sizes[tree_index] == _sizes[tree_index - 1];
            }
            if (should_merge_trees) {
                int size_of_subtree = 1 + (_degree * _sizes.back());
                int root_of_subtree = _container.size() - 1;
                for (int index = 0; index < _degree; index++)
                    _sizes.pop_back();
                _sizes.push_back(size_of_subtree);
                heapify(root_of_subtree, size_of_subtree);
                return;
            }
        }
        _sizes.push_back(1);
    }
    /**
     * Removes the top element.
     */
    void pop() {
        poll();
    }
    /**
     * Returns, and remove, the top element.
     * @return top element.
     */
    T poll() {
        // Initialise prioritised_root_index as root of rightmost heap, size of rightmost heap, and root cursor as second rightmost heap
        int prioritised_root_index = _container.size() - 1;
        int size = _sizes.back();
        int root_cursor = prioritised_root_index - size;
        T prioritised_root = _container[prioritised_root_index];

        // Reverse scan the roots of the forest ...
        for (int size_index = _sizes.size() - 2; size_index >= 0; size_index--) {
            int next_size = _sizes[size_index];
            T element = _container[root_cursor];
            if (_comparator(element, prioritised_root)) {
                prioritised_root = element;
                prioritised_root_index = root_cursor;
                size = next_size;
            }
            root_cursor -= next_size;
        }

        // Split rightmost heap at root.
        int size_of_subtree = _sizes.back() / _degree;
        _sizes.pop_back();

        // If rightmost heap > 1.
        if (size_of_subtree) {
            for (int index = 0; index < _degree; index++)
                _sizes.push_back(size_of_subtree);
        }
        // Remove root of rightmost heap.
        T last = _container.back();
        _container.pop_back();
        // If identified top is not root of rightmost heap...
        if (prioritised_root_index < _container.size()) {
            _container[prioritised_root_index] = last;
            heapify(prioritised_root_index, size);
        }

        return prioritised_root;
    }
    /**
     * Returns the top element.
     * @return top element
     */
    const_reference top() {
        // Initialise prioritised_root_index as root of rightmost heap, size of rightmost heap, and root cursor as second rightmost heap
        int prioritised_root_index = _container.size() - 1;
        int size = _sizes.back();
        int root_cursor = prioritised_root_index - size;
        T prioritised_root = _container[prioritised_root_index];

        // Reverse scan the roots of the forest ...
        for (int size_index = _sizes.size() - 2; size_index >= 0; size_index--) {
            int next_size = _sizes[size_index];
            T element = _container[root_cursor];
            if (_comparator(element, prioritised_root)) {
                prioritised_root = element;
                prioritised_root_index = root_cursor;
            }
            root_cursor -= next_size;
        }
        return _container[prioritised_root_index];
    }
    /**
     * Checks whether the underlying container is empty.
     * @return
     */
    bool empty() {
        return _container.empty();
    }
    /**
     * Returns the size of the underlying container.
     * @return
     */
    size_type size() {
        return _container.size();
    }
};

#endif //DARYPOSTORDERHEAP_LIBRARY_HPP


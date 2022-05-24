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

template <int degree, class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type>> 
class postorder_heap {
    typedef typename Container::size_type size_type;
    typedef typename Container::value_type value_type;
    typedef typename Container::const_reference const_reference;
private:
    // The underlying container
    Container container_;
    // Comparator used for comparisons
    Compare comparator_;
    // Sizes of the implicit heaps.
    std::vector<int> sizes_;
    /**
     *
     * @param index
     * @param size
     */
    void heapify(int index, int size_of_subtree) {
        T initial_root = std::move(container_[index]);
        while (size_of_subtree > 1) {
            size_of_subtree /= degree;
            int right_child_index = (index - 1);
            int prioritised_child_index = right_child_index;
            T prioritised_child = std::move(container_[right_child_index]);
            for (int child_offset = 1; child_offset < degree; child_offset++) {
                int childIndex = right_child_index - (child_offset * size_of_subtree);
                const_reference child = container_[childIndex];
                if (comparator_(child, prioritised_child)) {
                    prioritised_child_index = childIndex;
                    prioritised_child = std::move(child);
                }
            }
            if (!comparator_(prioritised_child, initial_root))
                break;
            container_[index] = std::move(prioritised_child);
            index = prioritised_child_index;
        }
        container_[index] = std::move(initial_root);
    }
public:
    /**
     * Trivial destructor.
     */
    ~postorder_heap() = default;
    /**
     * Default constructor, degree = 2 and standard '<' comparator is used.
     */
    explicit postorder_heap() : postorder_heap(Compare()) // Constructor delegation
    { }
    /**
     * Constructor with custom comparator and specified degree.
     * @param comparator
     * @param degree
     */
    postorder_heap(Compare comparator) :
    container_(Container()),
                                                               comparator_(comparator),
                                                               sizes_(std::vector<int>())
    { }

    /**
     * Pushes and element to the back of the container and ensures that post-order heap-ordering is preserved.
     * @param element to insert
     */
    void push(const value_type &element) {
        container_.push_back(element);
        if (sizes_.size() >= degree) {
            bool should_merge_trees = true;
            for (int offset = 1; offset < degree; offset++) {
                int tree_index = sizes_.size() - offset;
                should_merge_trees &= sizes_[tree_index] == sizes_[tree_index - 1];
            }
            if (should_merge_trees) {
                int size_of_subtree = 1 + (degree * sizes_.back());
                int root_of_subtree = container_.size() - 1;
                for (int index = 0; index < degree; index++)
                    sizes_.pop_back();
                sizes_.push_back(size_of_subtree);
                heapify(root_of_subtree, size_of_subtree);
                return;
            }
        }
        sizes_.push_back(1);
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
        int prioritised_root_index = container_.size() - 1;
        int size = sizes_.back();
        int root_cursor = prioritised_root_index - size;
        T prioritised_root = container_[prioritised_root_index];

        // Reverse scan the roots of the forest ...
        for (int size_index = sizes_.size() - 2; size_index >= 0; size_index--) {
            int next_size = sizes_[size_index];
            const_reference root = container_[root_cursor];
            if (comparator_(root, prioritised_root)) {
                prioritised_root = root;
                prioritised_root_index = root_cursor;
                size = next_size;
            }
            root_cursor -= next_size;
        }

        // Split rightmost heap at root.
        int size_of_subtree = sizes_.back() / degree;
        sizes_.pop_back();

        // If rightmost heap > 1.
        if (size_of_subtree) {
            for (int index = 0; index < degree; index++)
                sizes_.push_back(size_of_subtree);
        }
        // Remove root of rightmost heap.
        T last = container_.back();
        container_.pop_back();
        // If identified top is not root of rightmost heap...
        if (prioritised_root_index < container_.size()) {
            container_[prioritised_root_index] = std::move(last);
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
        int prioritised_root_index = container_.size() - 1;
        int size = sizes_.back();
        int root_cursor = prioritised_root_index - size;
        T prioritised_root = container_[prioritised_root_index];

        // Reverse scan the roots of the forest ...
        for (int size_index = sizes_.size() - 2; size_index >= 0; size_index--) {
            int next_size = sizes_[size_index];
            const_reference root = container_[root_cursor];
            if (comparator_(root, prioritised_root)) {
                prioritised_root = root;
                prioritised_root_index = root_cursor;
            }
            root_cursor -= next_size;
        }
        return container_[prioritised_root_index];
    }
    /**
     * Checks whether the underlying container is empty.
     * @return
     */
    bool empty() {
        return container_.empty();
    }
    /**
     * Returns the size of the underlying container.
     * @return
     */
    size_type size() {
        return container_.size();
    }

    void reserve(size_type new_cap) {
        container_.reserve(new_cap);
    }

    void clear() {
        container_.clear();
    }
};

#endif //DARYPOSTORDERHEAP_LIBRARY_HPP


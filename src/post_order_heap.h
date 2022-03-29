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
#ifndef DARYPOSTORDERHEAP_LIBRARY_HPP
#define DARYPOSTORDERHEAP_LIBRARY_HPP

#include <vector>
#include <functional>

template <class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type>> class post_order_heap {
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
    void heapify( int index,  int size);
public:
    /**
     * Trivial destructor.
     */
    ~post_order_heap() = default;
    /**
     * Default constructor, degree = 2 and standard '<' comparator is used.
     */
    explicit post_order_heap();
    /**
     * Constructor with custom comparator and degree = 2;
     * @param comparator
     */
    post_order_heap(Compare comparator);
    /**
     * Constructor with custom comparator and specified degree.
     * @param comparator
     * @param degree
     */
    post_order_heap(Compare comparator, int degree);
    /**
     * Pushes and element to the back of the container and ensures that post-order heap-ordering is preserved.
     * @param element to insert
     */
    void push(const value_type& element);
    /**
     * Removes the top element.
     */
    void pop();
    /**
     * Returns, and remove, the top element.
     * @return top element.
     */
    T poll();
    /**
     * Returns the top element.
     * @return top element
     */
    const_reference top();
    /**
     * Checks whether the underlying container is empty.
     * @return
     */
    bool empty();
    /**
     * Returns the size of the underlying container.
     * @return
     */
    size_type size();
};

#endif //DARYPOSTORDERHEAP_LIBRARY_HPP


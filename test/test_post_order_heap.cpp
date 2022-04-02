//
// Created by nicolaj on 3/27/22.
//
#include <chrono>
#include <queue>
#include "gtest/gtest.h"
#include "../src/postorder_heap.cpp"

TEST(PostOrderHeap, TestPostOrderHeapCanPdddush) {
    auto comparator = [](int left, int right) {
        return left < right;
    };
    postorder_heap<int, std::vector<int>, decltype(comparator)> heap(comparator, 2);
    for (int index = 0; index < 30; index++) {
        heap.push(index);

    }
    for (int index = 0; index < 30; index++)
        std::cout << std::to_string(heap.poll()) << '\n';
}
TEST(PostOrderHeapTest, TestInsertAndPop1) {
    auto comparator = [](int left, int right) {
        return left < right;
    };
    postorder_heap<int, std::vector<int>, decltype(comparator)> heap(comparator, 2);
    for (int index = 0; index<1000; index++) {
        heap.push(index);
    }
    for (int index = 0;index < 1000; index++)
        EXPECT_EQ(index, heap.poll());
}
TEST(PostOrderHeapTest, TestInsertAndPop2) {
    auto comparator = [](int left, int right) {
        return left < right;
    };
    postorder_heap<int, std::vector<int>, decltype(comparator)> heap(comparator, 2);
    for (int index = 10000; index > 0; index--) {
        heap.push(rand());
    }
    int last = std::numeric_limits<int>::min();
    for (int index = 0; index < 10000; index++) {
        int popped = heap.poll();
        EXPECT_TRUE(last <= popped);
        last = popped;
    }
}


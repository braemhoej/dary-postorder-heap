//
// Created by nicolaj on 3/27/22.
//
#include "gtest/gtest.h"
#include "../src/post_order_heap.cpp"

TEST(PostOrderHeap, TestPostOrderHeapCanPush) {
    post_order_heap<int, std::vector<int>, std::greater<>> heap{};
    for (int index = 0; index < 30; index++) {
        heap.insert(index);

    }
}
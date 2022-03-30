//
// Created by nicolaj on 3/27/22.
//
#include <chrono>
#include <queue>
#include "gtest/gtest.h"
#include "../src/post_order_heap.cpp"

TEST(PostOrderHeap, TestPostOrderHeapCanPush) {
    auto comparator = [](int left, int right) {
        return left < right;
    };
    post_order_heap<int, std::vector<int>, decltype(comparator)> heap(comparator,2);
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
    post_order_heap<int, std::vector<int>, decltype(comparator)> heap(comparator,2);
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
    post_order_heap<int, std::vector<int>, decltype(comparator)> heap(comparator, 2);
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

TEST(PostOrderHeapTest, ExpectBetterSequentialPushPerformance) {
    auto comparator = [](int left, int right) {
        return left < right;
    };
    post_order_heap<int, std::vector<int>, decltype(comparator)> heap(comparator, 2);
    std::priority_queue<int, std::vector<int>, decltype(comparator)> queue(comparator);

    // Generate numbers
    int* numbers = new int[200000000];
    srand(426086546);
    for (int index = 0; index < 200000000; index++) {
        numbers[index] = rand();
    }

    // Push to heap...
    auto startHeap = std::chrono::high_resolution_clock::now();
    for (int index = 0; index < 2000000; index++)
        heap.push(numbers[index]);
    auto stopHeap = std::chrono::high_resolution_clock::now();
    auto deltaHeap = duration_cast<std::chrono::microseconds>(stopHeap - startHeap);

    // Push to queue
    auto startQueue = std::chrono::high_resolution_clock::now();
    for (int index = 0; index < 2000000; index++)
        queue.push(numbers[index]);
    auto stopQueue = std::chrono::high_resolution_clock::now();
    auto deltaQueue = duration_cast<std::chrono::microseconds>(stopQueue - startQueue);

    EXPECT_TRUE(deltaQueue > deltaHeap);

    std::cout << "Delta heap: " << deltaHeap.count() << " ms" <<'\n';
    std::cout << "Delta queue: " << deltaQueue.count() << " ms" <<'\n';
}

TEST(PostOrderHeapTest, ExpectBetterSequentialPopPerformance) {
    auto comparator = [](int left, int right) {
        return left < right;
    };
    post_order_heap<int, std::vector<int>, decltype(comparator)> heap(comparator, 3);
    std::priority_queue<int, std::vector<int>, decltype(comparator)> queue(comparator);

    // Generate numbers & push
    int* numbers = new int[200000000];
    srand(4260876546);
    for (int index = 0; index < 200000000; index++) {
        numbers[index] = rand();
    }
    for (int index = 0; index < 2000000; index++) {
        heap.push(numbers[index]);
        queue.push(numbers[index]);
    }

    // Pop from heap...
    auto startHeap = std::chrono::high_resolution_clock::now();
    for (int index = 0; index < 2000000; index++)
        heap.pop();
    auto stopHeap = std::chrono::high_resolution_clock::now();
    auto deltaHeap = duration_cast<std::chrono::microseconds>(stopHeap - startHeap);

    // Pop from queue
    auto startQueue = std::chrono::high_resolution_clock::now();
    for (int index = 0; index < 2000000; index++)
        queue.pop();
    auto stopQueue = std::chrono::high_resolution_clock::now();
    auto deltaQueue = duration_cast<std::chrono::microseconds>(stopQueue - startQueue);

    EXPECT_TRUE(deltaQueue > deltaHeap);

    std::cout << "Delta heap: " << deltaHeap.count() << " microseconds" <<'\n';
    std::cout << "Delta queue: " << deltaQueue.count() << " microseconds" <<'\n';
}
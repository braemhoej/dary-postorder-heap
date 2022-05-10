//
// Created by nicolaj on 4/2/22.
//
#include <chrono>
#include <queue>
#include "gtest/gtest.h"
#include "../src/post-order_heap.hpp"

TEST(PerformanceTest, ExpectBetterSequentialPushPerformance) {
    auto comparator = [](int left, int right) {
        return left < right;
    };
    postorder_heap<int, std::vector<int>, decltype(comparator)> heap(comparator, 2);
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
}

TEST(PerformanceTest, ExpectBetterSequentialPopPerformance) {
    auto comparator = [](int left, int right) {
        return left < right;
    };
    postorder_heap<int, std::vector<int>, decltype(comparator)> heap(comparator, 3);
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
}

TEST(PerformanceTest, ExpectBetterSequentialPollVsTopPopPerformance) {
    auto comparator = [](int left, int right) {
        return left < right;
    };
    postorder_heap<int, std::vector<int>, decltype(comparator)> heap(comparator, 2);
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
        int poll = heap.poll();
    auto stopHeap = std::chrono::high_resolution_clock::now();
    auto deltaHeap = duration_cast<std::chrono::microseconds>(stopHeap - startHeap);

    // Pop from queue
    auto startQueue = std::chrono::high_resolution_clock::now();
    for (int index = 0; index < 2000000; index++) {
        int top = queue.top();
        queue.pop();
    }
    auto stopQueue = std::chrono::high_resolution_clock::now();
    auto deltaQueue = duration_cast<std::chrono::microseconds>(stopQueue - startQueue);

    EXPECT_TRUE(deltaQueue > deltaHeap);
}
TEST(PerformanceTest, ExpectBetterSequentialTopPopPerformance) {
    auto comparator = [](int left, int right) {
        return left < right;
    };
    postorder_heap<int, std::vector<int>, decltype(comparator)> heap(comparator, 2);
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
    for (int index = 0; index < 2000000; index++) {
        int top = heap.top();
        heap.pop();
    }
    auto stopHeap = std::chrono::high_resolution_clock::now();
    auto deltaHeap = duration_cast<std::chrono::microseconds>(stopHeap - startHeap);

    // Pop from queue
    auto startQueue = std::chrono::high_resolution_clock::now();
        for (int index = 0; index < 2000000; index++) {
        int top = queue.top();
        queue.pop();
    }
    auto stopQueue = std::chrono::high_resolution_clock::now();
    auto deltaQueue = duration_cast<std::chrono::microseconds>(stopQueue - startQueue);

    EXPECT_GT(deltaQueue, deltaHeap);
}
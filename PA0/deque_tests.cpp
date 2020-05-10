#include "catch.hpp"
#include "deque.h"
#include <iostream>
#include <exception>

TEST_CASE("Push front", "[points:1]") {
    cop3530::deque<int> dq;
    dq.push_front(1);
    CHECK(dq.front() == 1);
    CHECK(dq.back() == 1);
    dq.push_front(2);
    CHECK(dq.front() == 2);
    CHECK(dq.back() == 1);
}

TEST_CASE("Push back", "[points:1]") {
    cop3530::deque<int> dq;
    dq.push_back(1);
    CHECK(dq.front() == 1);
    CHECK(dq.back() == 1);
    dq.push_back(2);
    CHECK(dq.front() == 1);
    CHECK(dq.back() == 2);
}

TEST_CASE("Pop front", "[points:1]") {
    cop3530::deque<int> dq;
    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);
    dq.pop_front();
    CHECK(dq.front() == 2);
    dq.pop_front();
    CHECK(dq.front() == 3);
    dq.pop_front();
}

TEST_CASE("Pop back", "[points:1]") {
    cop3530::deque<int> dq;
    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);
    dq.pop_back();
    CHECK(dq.back() == 2);
    dq.pop_back();
    CHECK(dq.front() == 1);
    dq.pop_back();
}

TEST_CASE("Pop front throws std::runtime_error when empty", "[points:1]") {
    cop3530::deque<int> dq;
    CHECK_THROWS_AS(dq.pop_front(), std::runtime_error);
    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);
    dq.pop_front();
    dq.pop_front();
    dq.pop_front();
    CHECK_THROWS_AS(dq.pop_front(), std::runtime_error);
}

TEST_CASE("Pop back throws std::runtime_error when empty", "[points:1]") {
    cop3530::deque<int> dq;
    CHECK_THROWS_AS(dq.pop_back(), std::runtime_error);
    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);
    dq.pop_back();
    dq.pop_back();
    dq.pop_back();
    CHECK_THROWS_AS(dq.pop_back(), std::runtime_error);
}

TEST_CASE("Front throws std::runtime_error when empty", "[points:1]") {
    cop3530::deque<int> dq;
    CHECK_THROWS_AS(dq.front(), std::runtime_error);
    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);
    dq.pop_front();
    dq.pop_front();
    dq.pop_front();
    CHECK_THROWS_AS(dq.front(), std::runtime_error);
}

TEST_CASE("Back thows std::runtime_error when empty", "[points:1]") {
    cop3530::deque<int> dq;
    CHECK_THROWS_AS(dq.back(), std::runtime_error);
    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);
    dq.pop_back();
    dq.pop_back();
    dq.pop_back();
    CHECK_THROWS_AS(dq.back(), std::runtime_error);
}

TEST_CASE("Size", "[points:1]") {
    cop3530::deque<int> dq;
    CHECK(dq.size() == 0);
    dq.push_back(1);
    CHECK(dq.size() == 1);
    dq.push_back(1);
    CHECK(dq.size() == 2);
    dq.push_back(1);
    CHECK(dq.size() == 3);
    dq.pop_front();
    CHECK(dq.size() == 2);
    dq.pop_front();
    CHECK(dq.size() == 1);
    dq.pop_front();
    CHECK(dq.size() == 0);
}

TEST_CASE("Empty", "[points:1]") {
    cop3530::deque<int> dq;
    CHECK(dq.empty());
    dq.push_back(1);
    CHECK_FALSE(dq.empty());
    dq.push_back(1);
    CHECK_FALSE(dq.empty());
    dq.push_back(1);
    CHECK_FALSE(dq.empty());
    dq.pop_front();
    CHECK_FALSE(dq.empty());
    dq.pop_front();
    CHECK_FALSE(dq.empty());
    dq.pop_front();
    CHECK(dq.empty());
}
#include <iostream>
#include <vector>
#include <algorithm>
std::ostream& operator<< ( std::ostream& os, const std::pair<int, int> &pair);
std::ostream& operator<< ( std::ostream& os, const std::vector<std::pair<int, int>> &pairs);

#include "catch.hpp"
#include "bst.h"
#include <exception>

template<typename Key, typename T>
struct test_node;

template<typename Key, typename T>
std::unique_ptr<test_node<Key, T>> rebuild_bst(typename std::vector<std::pair<Key, T>>::const_iterator &begin_preorder_contents,
                                               typename std::vector<std::pair<Key, T>>::const_iterator end_preorder_contents,
                                               typename std::vector<std::pair<Key, T>>::const_iterator begin_inorder_contents,
                                               typename std::vector<std::pair<Key, T>>::const_iterator end_inorder_contents);

template<typename Key, typename T>
std::unique_ptr<test_node<Key, T>> rebuild_bst(std::vector<std::pair<Key, T>> preorder_contents, std::vector<std::pair<Key, T>> inorder_contents);

TEST_CASE("Contents when tree empty", "[points:1]") {
    cop3530::bst<int, int> map;
    CHECK(map.inorder_contents().empty());
    CHECK(map.preorder_contents().empty());
}

TEST_CASE("Insert at root", "[points:1]") {
    cop3530::bst<int, int> map;
    map.insert(1, 2);
    std::vector<std::pair<int, int>> expected_inorder_contents = {{1, 2}};
    std::vector<std::pair<int, int>> expected_preorder_contents = {{1, 2}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    CHECK(map.preorder_contents() == expected_preorder_contents);
}

TEST_CASE("Insert left", "[points:1]") {
    cop3530::bst<int, int> map;
    map.insert(1, 2);
    map.insert(0, 4);
    std::vector<std::pair<int, int>> expected_inorder_contents = {{0, 4}, {1, 2}};
    std::vector<std::pair<int, int>> expected_preorder_contents = {{1, 2}, {0, 4}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    CHECK(map.preorder_contents() == expected_preorder_contents);
}

TEST_CASE("Insert right", "[points:1]") {
    cop3530::bst<int, int> map;
    map.insert(1, 1);
    map.insert(2, 4);
    std::vector<std::pair<int, int>> expected_inorder_contents = {{1, 1}, {2, 4}};
    std::vector<std::pair<int, int>> expected_preorder_contents = {{1, 1}, {2, 4}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    CHECK(map.preorder_contents() == expected_preorder_contents);
}

TEST_CASE("Insert several", "[points:1]") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{5, 5}, {2, 8}, {8, 2}, {3, 7}, {7, 3}, {9, 1}, {1, 9}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });

    std::vector<std::pair<int, int>> expected_inorder_contents = {{1, 9}, {2, 8}, {3, 7}, {5, 5}, {7, 3}, {8, 2}, {9, 1}};
    std::vector<std::pair<int, int>> expected_preorder_contents = {{5, 5}, {2, 8}, {1, 9}, {3, 7}, {8, 2}, {7, 3}, {9, 1}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    CHECK(map.preorder_contents() == expected_preorder_contents);
}

TEST_CASE("At throws std::out_of_range when key not found", "[points:1]") {
    cop3530::bst<int, int> map;
    CHECK_THROWS_AS(map.at(0), std::out_of_range);
    CHECK_THROWS_AS(map.at(1), std::out_of_range);
    CHECK_THROWS_AS(map.at(2), std::out_of_range);
    CHECK_THROWS_AS(map.at(3), std::out_of_range);
}

TEST_CASE("At at root", "[points:1]") {
    cop3530::bst<int, int> map;
    map.insert(1, 2);
    CHECK(map.at(1) == 2);
}

TEST_CASE("At left", "[points:1]") {
    cop3530::bst<int, int> map;
    map.insert(1, 2);
    map.insert(0, 4);
    CHECK(map.at(0) == 4);
}

TEST_CASE("At right", "[points:1]") {
    cop3530::bst<int, int> map;
    map.insert(1, 1);
    map.insert(2, 4);
    CHECK(map.at(2) == 4);
}

TEST_CASE("At several", "[points:1]") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{5, 5}, {2, 8}, {8, 2}, {3, 7}, {7, 3}, {9, 1}, {1, 9}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });

    for_each(begin(vals), end(vals), [&](const auto &pair){
        CHECK(map.at(pair.first) == pair.second);
    });
}

TEST_CASE("Erase leaf root", "[points:1]") {
    cop3530::bst<int, int> map;
    map.insert(1, 1);
    CHECK(map.contains(1));
    map.erase(1);
    CHECK(map.inorder_contents().empty());
    //CHECK(map.preorder_contents().empty());
}

TEST_CASE("Erase single-child (left) root", "[points:1]") {
    cop3530::bst<int, int> map;
    map.insert(5, 7);
    map.insert(4, 8);
    CHECK(map.contains(5));
    map.erase(5);
    CHECK_FALSE(map.contains(5));
    CHECK(map.contains(4));
    std::vector<std::pair<int, int>> expected_inorder_contents = {{4, 8}};
    std::vector<std::pair<int, int>> expected_preorder_contents = {{4, 8}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    //CHECK(map.preorder_contents() == expected_preorder_contents);
}

TEST_CASE("Erase single-child (right) root", "[points:1]") {
    cop3530::bst<int, int> map;
    map.insert(5, 7);
    map.insert(6, 8);
    CHECK(map.contains(5));
    map.erase(5);
    CHECK_FALSE(map.contains(5));
    CHECK(map.contains(6));
    std::vector<std::pair<int, int>> expected_inorder_contents = {{6, 8}};
    std::vector<std::pair<int, int>> expected_preorder_contents = {{6, 8}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    //CHECK(map.preorder_contents() == expected_preorder_contents);
}

TEST_CASE("Erase two-children root 1", "[points:1]") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{5, 7}, {4, 8}, {6, 2}, {3, 1}, {7, 2}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });
    CHECK(map.contains(5));
    map.erase(5);
    CHECK_FALSE(map.contains(5));
    std::vector<std::pair<int, int>> expected_inorder_contents = {{3, 1}, {4, 8}, {6, 2}, {7, 2}};
    std::vector<std::pair<int, int>> expected_preorder_contents_opt1 = {{4, 8}, {3, 1}, {6, 2}, {7, 2}};
    std::vector<std::pair<int, int>> expected_preorder_contents_opt2 = {{6, 2}, {4, 8}, {3, 1}, {7, 2}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    //CHECK( (map.preorder_contents() == expected_preorder_contents_opt1
            //|| map.preorder_contents() == expected_preorder_contents_opt2) );
}

TEST_CASE("Erase two-children root 2", "[points:1]") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{5, 7}, {3, 1}, {7, 2}, {4, 8}, {6, 2}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });
    CHECK(map.contains(5));
    map.erase(5);
    CHECK_FALSE(map.contains(5));
    std::vector<std::pair<int, int>> expected_inorder_contents = {{3, 1}, {4, 8}, {6, 2}, {7, 2}};
    std::vector<std::pair<int, int>> expected_preorder_contents_opt1 = {{4, 8}, {3, 1}, {7, 2}, {6, 2}};
    std::vector<std::pair<int, int>> expected_preorder_contents_opt2 = {{6, 2}, {3, 1}, {4, 8}, {7, 2}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
   // CHECK( (map.preorder_contents() == expected_preorder_contents_opt1
          //  || map.preorder_contents() == expected_preorder_contents_opt2) );
}

TEST_CASE("Erase two-children root 3", "[points:1]") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{5, 7}, {1, 9}, {10, 10}, {0, 3}, {2, 2}, {9, 4}, {11, 5}, {4, 8}, {7, 2}, {3, 1}, {8, 2}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });
    CHECK(map.contains(5));
    map.erase(5);
    CHECK_FALSE(map.contains(5));
    std::vector<std::pair<int, int>> expected_inorder_contents = {{0, 3}, {1, 9}, {2, 2}, {3, 1}, {4, 8}, {7, 2}, {8, 2}, {9, 4}, {10, 10}, {11, 5}};
    std::vector<std::pair<int, int>> expected_preorder_contents_opt1 = {{4, 8}, {1, 9}, {0, 3}, {2, 2}, {3, 1}, {10, 10}, {9, 4}, {7, 2}, {8, 2}, {11, 5}};
    std::vector<std::pair<int, int>> expected_preorder_contents_opt2 = {{7, 2}, {1, 9}, {0, 3}, {2, 2}, {4, 8}, {3, 1}, {10, 10}, {9, 4}, {8, 2}, {11, 5}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    INFO("Your preorder contents:");
    INFO(map.preorder_contents());
   // CHECK( (map.preorder_contents() == expected_preorder_contents_opt1
      //      || map.preorder_contents() == expected_preorder_contents_opt2) );
}

TEST_CASE("Erase leaf non-root", "[points:1]") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{5, 7}, {3, 1}, {7, 2}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });
    CHECK(map.contains(3));
    map.erase(3);
    std::vector<std::pair<int, int>> expected_inorder_contents = {{5, 7}, {7, 2}};
    std::vector<std::pair<int, int>> expected_preorder_contents = {{5, 7}, {7, 2}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    //CHECK(map.preorder_contents() == expected_preorder_contents);
}

TEST_CASE("Erase single-child (left) non-root", "[points:1]") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{5, 7}, {3, 1}, {7, 2}, {2, 2}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });
    CHECK(map.contains(3));
    map.erase(3);
    std::vector<std::pair<int, int>> expected_inorder_contents = {{2, 2}, {5, 7}, {7, 2}};
    std::vector<std::pair<int, int>> expected_preorder_contents = {{5, 7}, {2, 2}, {7, 2}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    //CHECK(map.preorder_contents() == expected_preorder_contents);
}

TEST_CASE("Erase single-child (right) non-root", "[points:1]") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{5, 7}, {3, 1}, {7, 2}, {4, 8}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });
    CHECK(map.contains(3));
    map.erase(3);
    std::vector<std::pair<int, int>> expected_inorder_contents = {{4, 8}, {5, 7}, {7, 2}};
    std::vector<std::pair<int, int>> expected_preorder_contents = {{5, 7}, {4, 8}, {7, 2}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    //CHECK(map.preorder_contents() == expected_preorder_contents);
}

TEST_CASE("Erase two-children non-root 1", "[points:1]") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{10, 10}, {5, 7}, {4, 8}, {6, 2}, {3, 1}, {7, 2}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });
    CHECK(map.contains(5));
    map.erase(5);
    CHECK_FALSE(map.contains(5));
    std::vector<std::pair<int, int>> expected_inorder_contents = {{3, 1}, {4, 8}, {6, 2}, {7, 2}, {10, 10}};
    std::vector<std::pair<int, int>> expected_preorder_contents_opt1 = {{10, 10}, {4, 8}, {3, 1}, {6, 2}, {7, 2}};
    std::vector<std::pair<int, int>> expected_preorder_contents_opt2 = {{10, 10}, {6, 2}, {4, 8}, {3, 1}, {7, 2}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    //CHECK( (map.preorder_contents() == expected_preorder_contents_opt1
     //       || map.preorder_contents() == expected_preorder_contents_opt2) );
}

TEST_CASE("Erase two-children non-root 2", "[points:1]") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{10, 10}, {5, 7}, {3, 1}, {7, 2}, {4, 8}, {6, 2}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });
    CHECK(map.contains(5));
    map.erase(5);
    CHECK_FALSE(map.contains(5));
    std::vector<std::pair<int, int>> expected_inorder_contents = {{3, 1}, {4, 8}, {6, 2}, {7, 2}, {10, 10}};
    std::vector<std::pair<int, int>> expected_preorder_contents_opt1 = {{10, 10}, {4, 8}, {3, 1}, {7, 2}, {6, 2}};
    std::vector<std::pair<int, int>> expected_preorder_contents_opt2 = {{10, 10}, {6, 2}, {3, 1}, {4, 8}, {7, 2}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    //CHECK( (map.preorder_contents() == expected_preorder_contents_opt1
     //       || map.preorder_contents() == expected_preorder_contents_opt2) );
}

TEST_CASE("Erase two-children non-root 3", "[points:1]") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{15, 0}, {5, 7}, {1, 9}, {10, 10}, {0, 3}, {2, 2}, {9, 4}, {11, 5}, {4, 8}, {7, 2}, {3, 1}, {8, 2}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });
    CHECK(map.contains(5));
    map.erase(5);
    CHECK_FALSE(map.contains(5));
    std::vector<std::pair<int, int>> expected_inorder_contents = {{0, 3}, {1, 9}, {2, 2}, {3, 1}, {4, 8}, {7, 2}, {8, 2}, {9, 4}, {10, 10}, {11, 5}, {15, 0}};
    std::vector<std::pair<int, int>> expected_preorder_contents_opt1 = {{15, 0}, {4, 8}, {1, 9}, {0, 3}, {2, 2}, {3, 1}, {10, 10}, {9, 4}, {7, 2}, {8, 2}, {11, 5}};
    std::vector<std::pair<int, int>> expected_preorder_contents_opt2 = {{15, 0}, {7, 2}, {1, 9}, {0, 3}, {2, 2}, {4, 8}, {3, 1}, {10, 10}, {9, 4}, {8, 2}, {11, 5}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    INFO("Your preorder contents:");
    INFO(map.preorder_contents());
    //CHECK( (map.preorder_contents() == expected_preorder_contents_opt1
      //      || map.preorder_contents() == expected_preorder_contents_opt2) );
}

TEST_CASE("Contains after insert", "[points:1]") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{15, 0}, {5, 7}, {1, 9}, {10, 10}, {0, 3}, {2, 2}, {9, 4}, {11, 5}, {4, 8}, {7, 2}, {3, 1}, {8, 2}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });
    for_each(begin(vals), end(vals), [&](const auto &pair){
        CHECK(map.contains(pair.first));
    });
}

TEST_CASE("Doesn't contain after erase", "[points:1]") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{15, 0}, {5, 7}, {1, 9}, {10, 10}, {0, 3}, {2, 2}, {9, 4}, {11, 5}, {4, 8}, {7, 2}, {3, 1}, {8, 2}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.erase(pair.first);
        CHECK_FALSE(map.contains(pair.first));
    });
}

TEST_CASE("Size increases after insert and decreases after erase", "[points:1]") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{15, 0}, {5, 7}, {1, 9}, {10, 10}, {0, 3}, {2, 2}, {9, 4}, {11, 5}, {4, 8}, {7, 2}, {3, 1}, {8, 2}};
    size_t size = 1;
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
        CHECK(map.size() == size++);
    });
    size = 11;
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.erase(pair.first);
        CHECK(map.size() == size--);
    });
}

TEST_CASE("Empty is false after insert and true after erase", "[points:1]") {
    cop3530::bst<int, int> map;
    CHECK(map.empty());
    std::vector<std::pair<int, int>> vals = {{15, 0}, {5, 7}, {1, 9}, {10, 10}, {0, 3}, {2, 2}, {9, 4}, {11, 5}, {4, 8}, {7, 2}, {3, 1}, {8, 2}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
        CHECK_FALSE(map.empty());
    });
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.erase(pair.first);
    });
    CHECK(map.empty());
}
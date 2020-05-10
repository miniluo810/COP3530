#include <iostream>
#include <vector>
#include <algorithm>
std::ostream& operator<< ( std::ostream& os, const std::pair<int, int> &pair);
std::ostream& operator<< ( std::ostream& os, const std::vector<std::pair<int, int>> &pairs);

#include "catch.hpp"
#include "bst.h"
#include <exception>

TEST_CASE("Insert LL Rotation Root 1") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{10, 1}, {5, 2}, {2, 5}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });

    std::vector<std::pair<int, int>> expected_inorder_contents = {{2, 5}, {5, 2}, {10, 1}};
    std::vector<std::pair<int, int>> expected_preorder_contents = {{5, 2}, {2, 5}, {10, 1}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    CHECK(map.preorder_contents() == expected_preorder_contents);
}

TEST_CASE("Insert LL Rotation Non-Root 1") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{15, 16}, {10, 1}, {16, 13}, {5, 2}, {2, 5}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });

    std::vector<std::pair<int, int>> expected_inorder_contents = {{2, 5}, {5, 2}, {10, 1}, {15, 16}, {16, 13}};
    std::vector<std::pair<int, int>> expected_preorder_contents = {{15, 16}, {5, 2}, {2, 5}, {10, 1}, {16, 13}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    CHECK(map.preorder_contents() == expected_preorder_contents);
}

TEST_CASE("Insert LR Rotation Root 1") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{10, 1}, {5, 2}, {8, 5}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });

    std::vector<std::pair<int, int>> expected_inorder_contents = {{5, 2}, {8, 5}, {10, 1}};
    std::vector<std::pair<int, int>> expected_preorder_contents = {{8, 5}, {5, 2}, {10, 1}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    CHECK(map.preorder_contents() == expected_preorder_contents);
}

TEST_CASE("Insert LR Rotation Non-Root 1") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{15, 16}, {10, 1}, {16, 13}, {5, 2}, {8, 5}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });

    std::vector<std::pair<int, int>> expected_inorder_contents = {{5, 2}, {8, 5}, {10, 1}, {15, 16}, {16, 13}};
    std::vector<std::pair<int, int>> expected_preorder_contents = {{15, 16}, {8, 5}, {5, 2}, {10, 1}, {16, 13}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    CHECK(map.preorder_contents() == expected_preorder_contents);
}

TEST_CASE("Insert RL Rotation Root 1") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{10, 1}, {15, 2}, {12, 5}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });

    std::vector<std::pair<int, int>> expected_inorder_contents = {{10, 1}, {12, 5}, {15, 2}};
    std::vector<std::pair<int, int>> expected_preorder_contents = {{12, 5}, {10, 1}, {15, 2}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    CHECK(map.preorder_contents() == expected_preorder_contents);
}

TEST_CASE("Insert RL Rotation Non-Root 1") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{5, 2}, {3, 5}, {10, 1}, {15, 16}, {12, 5}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });

    std::vector<std::pair<int, int>> expected_inorder_contents = {{3, 5}, {5, 2}, {10, 1}, {12, 5}, {15, 16}};
    std::vector<std::pair<int, int>> expected_preorder_contents = {{5, 2}, {3, 5}, {12, 5}, {10, 1}, {15, 16}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    CHECK(map.preorder_contents() == expected_preorder_contents);
}

TEST_CASE("Insert RR Rotation Root 1") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{10, 1}, {15, 2}, {17, 5}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });

    std::vector<std::pair<int, int>> expected_inorder_contents = {{10, 1}, {15, 2}, {17, 5}};
    std::vector<std::pair<int, int>> expected_preorder_contents = {{15, 2}, {10, 1}, {17, 5}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    CHECK(map.preorder_contents() == expected_preorder_contents);
}

TEST_CASE("Insert RR Rotation Non-Root 1") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{5, 2}, {3, 5}, {10, 1}, {15, 16}, {17, 5}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });

    std::vector<std::pair<int, int>> expected_inorder_contents = {{3, 5}, {5, 2}, {10, 1}, {15, 16}, {17, 5}};
    std::vector<std::pair<int, int>> expected_preorder_contents = {{5, 2}, {3, 5}, {15, 16}, {10, 1}, {17, 5}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    CHECK(map.preorder_contents() == expected_preorder_contents);
}

TEST_CASE("Delete LL Rotation Root 1") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{10, 1}, {5, 2}, {15, 16}, {2, 5}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });

    map.erase(15);

    std::vector<std::pair<int, int>> expected_inorder_contents = {{2, 5}, {5, 2}, {10, 1}};
    std::vector<std::pair<int, int>> expected_preorder_contents = {{5, 2}, {2, 5}, {10, 1}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    CHECK(map.preorder_contents() == expected_preorder_contents);
}

TEST_CASE("Delete LL Rotation Non-Root 1") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{20, 20}, {10, 1}, {25, 25}, {5, 2}, {15, 16}, {30, 30}, {2, 5}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });

    map.erase(15);

    std::vector<std::pair<int, int>> expected_inorder_contents = {{2, 5}, {5, 2}, {10, 1}, {20, 20}, {25, 25}, {30, 30}};
    std::vector<std::pair<int, int>> expected_preorder_contents = {{20, 20}, {5, 2}, {2, 5}, {10, 1}, {25, 25}, {30, 30}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    CHECK(map.preorder_contents() == expected_preorder_contents);
}

TEST_CASE("Delete LR Rotation Root 1") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{10, 1}, {5, 2}, {15, 16}, {8, 5}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });

    map.erase(15);

    std::vector<std::pair<int, int>> expected_inorder_contents = {{5, 2}, {8, 5}, {10, 1}};
    std::vector<std::pair<int, int>> expected_preorder_contents = {{8, 5}, {5, 2}, {10, 1}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    CHECK(map.preorder_contents() == expected_preorder_contents);
}

TEST_CASE("Delete LR Rotation Non-Root 1") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{20, 20}, {10, 1}, {25, 25}, {5, 2}, {15, 16}, {30, 30}, {8, 5}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });

    map.erase(15);

    std::vector<std::pair<int, int>> expected_inorder_contents = {{5, 2}, {8, 5}, {10, 1}, {20, 20}, {25, 25}, {30, 30}};
    std::vector<std::pair<int, int>> expected_preorder_contents = {{20, 20}, {8, 5}, {5, 2}, {10, 1}, {25, 25}, {30, 30}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    CHECK(map.preorder_contents() == expected_preorder_contents);
}

TEST_CASE("Delete RL Rotation Root 1") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{10, 1}, {5, 2}, {15, 16}, {12, 5}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });

    map.erase(5);

    std::vector<std::pair<int, int>> expected_inorder_contents = {{10, 1}, {12, 5}, {15, 16}};
    std::vector<std::pair<int, int>> expected_preorder_contents = {{12, 5}, {10, 1}, {15, 16}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    CHECK(map.preorder_contents() == expected_preorder_contents);
}

TEST_CASE("Delete RL Rotation Non-Root 1") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{3, 3}, {2, 2}, {10, 1}, {1, 1}, {5, 2}, {15, 16}, {12, 5}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });

    map.erase(5);

    std::vector<std::pair<int, int>> expected_inorder_contents = {{1, 1}, {2, 2}, {3, 3}, {10, 1}, {12, 5}, {15, 16}};
    std::vector<std::pair<int, int>> expected_preorder_contents = {{3, 3}, {2, 2}, {1, 1}, {12, 5}, {10, 1}, {15, 16}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    CHECK(map.preorder_contents() == expected_preorder_contents);
}

TEST_CASE("Delete RR Rotation Root 1") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{10, 1}, {5, 2}, {15, 16}, {17, 5}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });

    map.erase(5);

    std::vector<std::pair<int, int>> expected_inorder_contents = {{10, 1}, {15, 16}, {17, 5}};
    std::vector<std::pair<int, int>> expected_preorder_contents = {{15, 16}, {10, 1}, {17, 5}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    CHECK(map.preorder_contents() == expected_preorder_contents);
}

TEST_CASE("Delete RR Rotation Non-Root 1") {
    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{3, 3}, {2, 2}, {10, 1}, {1, 1}, {5, 2}, {15, 16}, {17, 5}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });

    map.erase(5);

    std::vector<std::pair<int, int>> expected_inorder_contents = {{1, 1}, {2, 2}, {3, 3}, {10, 1}, {15, 16}, {17, 5}};
    std::vector<std::pair<int, int>> expected_preorder_contents = {{3, 3}, {2, 2}, {1, 1}, {15, 16}, {10, 1}, {17, 5}};
    CHECK(map.inorder_contents() == expected_inorder_contents);
    CHECK(map.preorder_contents() == expected_preorder_contents);
}
TEST_CASE("Custom NS 1", "[points:1]") {
cop3530::bst<int, int> map;
std::vector<std::pair<int, int>> vals = {{5, 5}, {1, 8}, {8, 2}, {9, 7}, {7, 3}, {2, 1}, {3, 9}};
for_each(begin(vals), end(vals), [&](const auto &pair){
map.insert(pair.first, pair.second);
});
for_each(begin(vals), end(vals), [&](const auto &pair){
CHECK(map.at(pair.first) == pair.second);
});
}
TEST_CASE("Custom NS 2", "[points:1]") {
cop3530::bst<int, int> map;
std::vector<std::pair<int, int>> vals = {{5, 5}, {0, 8}, {8, 2}, {9, 7}, {7, 3}, {2, 1}, {1, 9}};
for_each(begin(vals), end(vals), [&](const auto &pair){
map.insert(pair.first, pair.second);
});
for_each(begin(vals), end(vals), [&](const auto &pair){
CHECK(map.at(pair.first) == pair.second);
});
}
TEST_CASE("Custom NS 3", "[points:1]") {
cop3530::bst<int, int> map;
std::vector<std::pair<int, int>> vals = {{1, 5}, {15, 8}, {5, 2}, {0, 7}, {2, 3}, {10, 1}, {9, 9}};
for_each(begin(vals), end(vals), [&](const auto &pair){
map.insert(pair.first, pair.second);
});
for_each(begin(vals), end(vals), [&](const auto &pair){
CHECK(map.at(pair.first) == pair.second);
});
}
TEST_CASE("Custom NS 4", "[points:1]") {
cop3530::bst<int, int> map;
std::vector<std::pair<int, int>> vals = {{15, 5}, {5, 8}, {10, 2}, {2, 7}, {4, 20}};
for_each(begin(vals), end(vals), [&](const auto &pair){
map.insert(pair.first, pair.second);
});
for_each(begin(vals), end(vals), [&](const auto &pair){
CHECK(map.at(pair.first) == pair.second);
});
}
TEST_CASE("Custom NS 5", "[points:1]") {
cop3530::bst<int, int> map;
std::vector<std::pair<int, int>> vals = {{5, 5}, {1, 8}, {8, 2}, {0, 7}, {2, 3}, {6, 1}, {7, 9}};
for_each(begin(vals), end(vals), [&](const auto &pair){
map.insert(pair.first, pair.second);
});
for_each(begin(vals), end(vals), [&](const auto &pair){
CHECK(map.at(pair.first) == pair.second);
});
}
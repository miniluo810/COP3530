#pragma once

#include "frequency_table.h"
#include <queue>
#include <vector>
#include <unordered_map>
#include <fstream>
// struct for the nodes of the tree?
using namespace std;

struct node {
    char sym;
    int weight;
    node *left;
    node *right;
    bool leaf;

    node() {
        left = nullptr;
        right = nullptr;

    }

    node(char c, int i) {
        sym = c;
        weight = i;
        leaf = true;
        left = nullptr;
        right = nullptr;
    }

    node(node *l, node *r, int w) {
        left = l;
        right = r;
        weight = w;
        leaf = false;
    }

    int getWeight() {
        return weight;
    }

    bool isLeaf() {
        return leaf;
    }
};

class compare {
public:
    bool operator()(node *node1, node *node2) {
        return node1->getWeight() > node2->getWeight();
    }

};

class huffman_encoder {
    node *root;
    unordered_map<char, string> charMap;
public:
    huffman_encoder(const frequency_table &table);

    ~huffman_encoder();

    void recursiveDelete(node *rootNode);

    void recursiveEncoder(node *parent, std::string tempString);

    std::string get_character_code(char c) const;

    std::string encode(const std::string &file_name) const;

    std::string decode(const std::string &string_to_decode) const;
};

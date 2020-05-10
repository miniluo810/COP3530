#include "huffman_encoder.h"


huffman_encoder::huffman_encoder(const frequency_table &table) {

    priority_queue < node * , vector < node * >, compare > pq;
    node *temp;
    node *temp2;
    for (auto it = table.freq.begin(); it != table.freq.end(); it++) {
        node *newNode = new node(it->first, it->second);
        pq.push(newNode);
    }
    while (pq.size() > 1) {
        temp = pq.top();
        pq.pop();
        temp2 = pq.top();
        pq.pop();
        node *newRoot = new node(temp, temp2, temp->getWeight() + temp2->getWeight());
        pq.push(newRoot);
    }
    root = pq.top();
    if(root->isLeaf()){
        charMap[root->sym]='0';
    }else {
        recursiveEncoder(root, "");
    }



}

huffman_encoder::~huffman_encoder() {
    recursiveDelete(this->root);

}

void huffman_encoder::recursiveDelete(node *rootNode) {
    if (rootNode != nullptr) {

        if (rootNode->left != nullptr) {
            recursiveDelete(rootNode->left);
        }
        if (rootNode->right != nullptr) {
            recursiveDelete(rootNode->right);
        }
        delete rootNode;
    }

}

std::string huffman_encoder::get_character_code(char c) const {
    if(charMap.find(c)==charMap.end()){
        return "";
    }
    return charMap.at(c);
}

void huffman_encoder::recursiveEncoder(node *parent, std::string tempString) {
    if (parent != nullptr) {
        if (parent->isLeaf()) {
            charMap[parent->sym] = tempString;
        }
        recursiveEncoder(parent->right, tempString + "1");
        recursiveEncoder(parent->left, tempString + "0");
    } else {
        return;
    }

}

std::string huffman_encoder::encode(const std::string &file_name) const {
    std::string dataString;
    std::ifstream file(file_name);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot be opened");
    } else {

        char c = file.get();
        while (c != EOF) {
            dataString += get_character_code(c);
            c = file.get();
        }
    }
    file.close();
    return dataString;
}

std::string huffman_encoder::decode(const std::string &string_to_decode) const {
    node *start = root;
    std::string msg;
    if(string_to_decode.size()==1){
        return msg+=start->sym;
    }

    for (int i = 0; string_to_decode[i] != '\0'; i++) {
        if (string_to_decode[i] != '1' && string_to_decode[i] != '0') {
            return "";
        } else {
            if (string_to_decode[i] == '0') {
                if (!start->left->isLeaf()) {
                    start = start->left;
                } else {
                    msg += start->left->sym;
                    start = root;
                }

            } else if (string_to_decode[i] == '1') {
                if (!start->right->isLeaf()) {
                    start = start->right;
                } else {
                    msg += start->right->sym;
                    start = root;
                }

            }

        }

    }
    return msg;
}

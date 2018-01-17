//
// Created by blazeq on 2018. 1. 15..
//

#include "catch.hpp"
#include <iostream>
#include <memory>

namespace {

using namespace std;

struct Node {
    int value;
    shared_ptr<Node> left{nullptr};
    shared_ptr<Node> right{nullptr};

    static shared_ptr<Node> create(int value) {
        return shared_ptr<Node>(new Node(value));
    }

private:
    explicit Node(int value): value(value){}
};

using NodePtr = shared_ptr<Node>;

NodePtr insert(NodePtr node, int value) {
    if (node == nullptr) {
        return Node::create(value);
    }

    if (value <= node->value) {
        node->left = insert(node->left, value);
    } else  {
        node->right = insert(node->right, value);
    }

    return node;
}

void printInorderTraversal(NodePtr node) {
    if (node == nullptr)
        return;

    printInorderTraversal(node->left);
    cout << node->value << " ";
    printInorderTraversal(node->right);
}

int countInRange(NodePtr node, int lower, int upper) {
    if (node == nullptr)
        return 0;

    if (lower > upper)
        return 0;

    int count = 0;
    if (lower <= node->value && node->value <= upper) {
        count += 1;
    }

    count += countInRange(node->left, lower, min(node->value, upper));
    count += countInRange(node->right, max(node->value + 1, lower), upper);

    return count;
}

} // namespace

TEST_CASE("Count BST nodes in given range", "[count bst nodes in given range]") {
    int values[] = {8, 4, 4, 12, 2, 6, 10, 14};
    NodePtr node;
    for (int value : values) {
        node = insert(node, value);
    }

    printInorderTraversal(node);

    REQUIRE(3 == countInRange(node, 5, 11));
    REQUIRE(5 == countInRange(node, 4, 11));
    REQUIRE(1 == countInRange(node, 14, 14));
    REQUIRE(8 == countInRange(node, 1, 14));
}
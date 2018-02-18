//
// Created by blazeq on 2018. 2. 11..
//

#include "catch.hpp"
#include <iostream>
#include <stack>

using namespace std;

namespace {

/*
 * 40, 30, 35, 20, 80, 100
 *            40
 *         /       \
 *        30
 *          \
 *           35
 *
 * 40, 30, 35, 20, 80, 100
 *          i
 * Root: 30
 * Stack: 40, 35,
 *
 *
 *                40
 *           /           \
 *          30           80
 *         /  \         /
 *        20  32       70
 *              \        \
 *              35       75
 *
 *
 * 40, 30, 20, 32, 35, 80, 70, 75, 73, 100
 *                                  i
 * Root: 70
 * Stack: 80, 75, 73
 *
 *
 * 오른쪽으로 꺾인 순간 방금 넣은 것의 부모보다 작은게 오면 안된다!
 *
 * 현재 보고 있는 preorder 값의 직전 작은 값을 루트로 유지한다.
 * 이미 오른쪽으로 갔으므로 왼쪽으로 올 수는 없다.
 *
 * O(N)이다. 한번에 스택에 들어가고 한 번에 빠지니깐.
 *
 *
 * preorder 순열을 가지고 BST를 만들 수 있다. O(N)에!
 *
 *
 * 중복된 원소가 있는 경우 어떻게 할래?
 * BST에서 중복된 원소를 앞에 둔다고 하자.
 *                  40
 *             /
 *            30
 *           /  \
 *          20  32
 *              / \
 *             32 35
 *
 *
 *
 * 40, 30, 20, 32, 32, 35, 80, 70, 75, 73, 100
 *                      i
 * Root: 30, 32
 * Stack: 40, 35
 *
 */


bool canRepresentBst(int preorder[], int n) {
    stack<int> st;

    int root = INT_MIN;

    for (int i = 0; i < n; ++i) {
        if (preorder[i] < root) {
            return false;
        }

        while (!st.empty() && st.top() < preorder[i]) {
            root = st.top();
            st.pop();
        }

        st.push(preorder[i]);
    }

    return true;
}

/*
 *                  40
 *             /           \
 *            30           80
 *           /  \         /  \
 *          20  32       70  100
 *              / \        \
 *             32 35       75
 *                        /
 *                       73
 *
 *
 * 40, 30, 20, 32, 32, 35, 80, 70, 75, 73, 100
 *
 * {30, 20, 32, 32, 35} 40 {80, 70, 75, 73, 100}
 * {20} 30 {32, 32, 35}    {70, 75, 73} 80 {100}
 *  20     {32} 32 {35}     70 {75, 73}     100
 *                             {73} 75
 */

struct Node {
    int value;
    shared_ptr<Node> left;
    shared_ptr<Node> right;
    Node(int value):value(value){}
};
using NodePtr = shared_ptr<Node>;

ostream& operator<<(ostream& o, const Node& node) {



    return o;
}



void calcNextGreaterElements(int arr[], int n, int nextGreater[]) {
    stack<int> st;
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && arr[st.top()] < arr[i]) {
            int j = st.top();
            st.pop();
            nextGreater[j] = i;
        }
        st.push(i);
    }

    while (!st.empty()) {
        int j = st.top();
        st.pop();
        nextGreater[j] = -1;
    }
}

NodePtr buildBstFromPreorder(int preorder[], int s, int e, int nextGreater[]) {
    if (s > e)
        return nullptr;

    NodePtr node = make_shared<Node>(preorder[s]);
    int j = nextGreater[s];
    if (j != -1) {
        node->left = buildBstFromPreorder(preorder, s + 1, j - 1, nextGreater);
        node->right = buildBstFromPreorder(preorder, j, e, nextGreater);
    }

    return node;
}

NodePtr buildBstFromPreorder(int preorder[], int n) {
    int nextGreater[n];
    calcNextGreaterElements(preorder, n, nextGreater);
    return buildBstFromPreorder(preorder, 0, n - 1, nextGreater);
}

void inorderTraverse(NodePtr tree) {
    if (tree == nullptr) return;

    inorderTraverse(tree->left);
    cout << tree->value << " ";
    inorderTraverse(tree->right);
}

void preorderTraverse(NodePtr tree) {
    if (tree == nullptr) return;

    cout << tree->value << " ";
    preorderTraverse(tree->left);
    preorderTraverse(tree->right);
}

bool isBst(NodePtr node, int lower, int upper) {
    if (node == nullptr)
        return true;

    bool valid = lower < node->value && node->value <= upper;
    if (!valid)
        return false;

    if (node->left != nullptr && !isBst(node->left, lower, node->value)) {
        return false;
    }

    if (node->right != nullptr && !isBst(node->right, node->value, upper)) {
        return false;
    }

    return true;
}

bool isBst(NodePtr node) {
    return isBst(node, INT_MIN, INT_MAX);
}

vector<NodePtr> constructBst(int s, int e) {
    vector<NodePtr> nodes;

    if (s > e) {
        nodes.push_back(nullptr);
        return nodes;
    }

    for (int i = s; i <= e; ++i) {
        vector<NodePtr> lefts = constructBst(s, i - 1);
        vector<NodePtr> rights  = constructBst(i + 1, e);

        for (auto left : lefts) {
            for (auto right : rights) {
                NodePtr node = make_shared<Node>(i);
                node->left = left;
                node->right = right;
                nodes.push_back(node);
            }
        }
    }

    return nodes;
}

void constructBst(int n) {
    vector<NodePtr> trees = constructBst(1, n);

    for (auto tree : trees) {
        preorderTraverse(tree);
        cout << endl;
    }
}

} // namespace

TEST_CASE("Binary search tree", "[bst]") {
//    SECTION("Build BST from a valid preorder traversal") {
//        int preorder[] = {40, 30, 20, 32, 32, 35, 80, 70, 75, 73, 100};
//        int n = sizeof(preorder)/sizeof(int);
//
//        REQUIRE(canRepresentBst(preorder, n));
//        NodePtr root = buildBstFromPreorder(preorder, n);
//        REQUIRE(isBst(root));
//    }
//
//    SECTION("Build BST from a invalid preorder traversal") {
//        int preorder[] = {40, 30, 20, 32, 32, 35, 80, 70, 23, 75, 73, 100};
//        int n = sizeof(preorder)/sizeof(int);
//
//        REQUIRE(!canRepresentBst(preorder, n));
//    }

    SECTION("Build all BST with n") {
        constructBst(3);
    }
}
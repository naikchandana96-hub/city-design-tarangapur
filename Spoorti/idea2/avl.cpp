#include <emscripten.h>
#include <string>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

struct Node {
    int rank;
    string name;
    Node *left, *right;
    int height;
};

int height(Node* n) {
    return n ? n->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* newNode(string name, int rank) {
    Node* node = new Node();
    node->name = name;
    node->rank = rank;
    node->left = node->right = nullptr;
    node->height = 1;
    return node;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

Node* insert(Node* node, string name, int rank) {
    if (!node)
        return newNode(name, rank);

    if (rank < node->rank)
        node->left = insert(node->left, name, rank);
    else if (rank > node->rank)
        node->right = insert(node->right, name, rank);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && rank < node->left->rank)
        return rightRotate(node);

    if (balance < -1 && rank > node->right->rank)
        return leftRotate(node);

    if (balance > 1 && rank > node->left->rank) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && rank < node->right->rank) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inorder(Node* root, stringstream& ss) {
    if (root) {
        inorder(root->left, ss);
        ss << root->name << " (Rank " << root->rank << ")\n";
        inorder(root->right, ss);
    }
}

extern "C" {

EMSCRIPTEN_KEEPALIVE
const char* run_avl2(const char* jsonStr) {
    static string result;
    stringstream ss;

    json j = json::parse(jsonStr);
    Node* root = nullptr;

    for (auto& loc : j["eco_locations"]) {
        root = insert(root, loc["name"], loc["rank"]);
    }

    ss << "AVL Tree (Sorted by Eco Rank):\n";
    inorder(root, ss);

    result = ss.str();
    return result.c_str();
}

}

#include <iostream>
#include <queue>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int nlp; // node level pointer (used for balancing)

public:
    Node(int val) {
        this->key = val;
        this->left = nullptr;
        this->right = nullptr;
        this->nlp = 0;
    }
};

Node* merge(Node* h1, Node* h2) {
    if (h1 == nullptr) {
        return h2;
    }

    if (h2 == nullptr) {
        return h1;
    }

    if (h1->key > h2->key) {
        int temp = h1->key;
        h1->key = h2->key;
        h2->key = temp;
    }

    h1->right = merge(h1->right, h2);

    if (h1->left != nullptr && (h1->right == nullptr || h1->left->nlp < h1->right->nlp)){
        int temp = h1->left->key;
        h1->left->key = h1->right->key;
        h1->right->key = temp;
    }

    h1->nlp = h1->right->nlp + 1;
    
    return h1;
}

Node* insert(Node* heap, int key) {
    Node* newNode = new Node(key);
    return merge(heap, newNode);
}

Node* deleteMin(Node* heap) {
    if (heap == nullptr) {
        return nullptr;
    }
    Node* leftHeap = heap->left;
    Node* rightHeap = heap->right;
    delete heap;
    if (leftHeap != nullptr) {
        leftHeap->nlp = 0; // Reset nlp since the root of leftHeap becomes the new root
    }
    return merge(leftHeap, rightHeap);
}


int findMin(Node* heap) {
    if (heap == nullptr) {
        cout << "Heap is empty" << endl;
        return -1; // Or any valid return value to indicate empty heap
    }
    return heap->key;
}

void printLevelOrder(Node* heap) {
    if (heap == nullptr)
        return;

    queue<Node*> q;
    q.push(heap);
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            Node* curr = q.front();
            q.pop();
            cout << curr->key << " ";
            if (curr->left != nullptr)
                q.push(curr->left);
            if (curr->right != nullptr)
                q.push(curr->right);
        }
        if (!q.empty()) // Check if the queue is empty before printing a new line
            cout << endl;
    }
}

int main() {
    Node* heap = nullptr;

    heap = insert(heap, 5);
    heap = insert(heap, 3);
    heap = insert(heap, 8);
    heap = insert(heap, 2);
    heap = insert(heap, 4);
    heap = insert(heap, 1);
    heap = insert(heap, 10);
    heap = insert(heap, 20);
    heap = insert(heap, 69);
    heap = insert(heap, 48);
    heap = insert(heap, 11);

    cout << findMin(heap);
    cout << endl;
    deleteMin(heap);
    cout << findMin(heap);

    return 0;
}

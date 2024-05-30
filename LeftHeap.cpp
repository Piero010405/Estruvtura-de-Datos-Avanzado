#include <iostream>
#include <vector>


using namespace std;  


struct Node{
    int key;
    Node* left;
    Node* right;
    int npl; // null path length


    Node(int value){
        key = value;
        left = nullptr;
        right = nullptr;
        npl = 0;
    }
};


Node* merge(Node* h1, Node* h2){
    if(h1 == nullptr){
        return h2;
    }
    if(h2 == nullptr){
        return h1;
    }


    if(h1->key > h2->key){
        swap(h1, h2);
    }


    h1->right = merge(h1->right, h2);
   
    if (h1->left == nullptr || (h1->right != nullptr && h1->left->npl < h1->right->npl)) {
        swap(h1->left, h1->right);
    }


    if (h1->right == nullptr) {
        h1->npl = 0;
    } else {
        h1->npl = h1->right->npl + 1;
    }
   
    return h1;
}


Node* insert(Node* heap, int key){
    Node* newNode = new Node(key);
    return merge(heap, newNode);
}


Node* deleteMin(Node* heap){
    if(heap == nullptr) return nullptr;
    Node* leftHeap = heap->left;
    Node* rightHeap = heap->right;
    delete heap;
    return merge(leftHeap, rightHeap);
}


int findMin(Node* heap){
    if(heap == nullptr) throw "Empty heap";
    return heap->key;
}


int main() {
    Node* heap = nullptr;


    // Insert elements into the heap
    vector<int> elements = {10, 5, 20, 3, 8, 15};
    for (int elem : elements) {
        heap = insert(heap, elem);
        cout << "Se ha insertado " << elem << ", el minimo es " << findMin(heap) << endl;
    }


    // Find minimum element
    cout << "El minimo elemento es: " << findMin(heap) << endl;


    // Delete minimum element
    heap = deleteMin(heap);
    cout << "Minimo eliminado, el nuevo minimo es: " << findMin(heap) << endl;


    // Continue deleting until the heap is empty
    while (heap != nullptr) {
        heap = deleteMin(heap);
        if (heap != nullptr) {
            cout << "Minimo eliminado, el nuevo minimo es: " << findMin(heap) << endl;
        } else {
            cout << "El heap se encuentra vacio." << endl;
        }
    }
    return 0;
}

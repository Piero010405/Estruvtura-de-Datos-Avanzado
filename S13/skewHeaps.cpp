#include <iostream>
using namespace std;

struct SkewHeap
{
    int key;
    SkewHeap *right;
    SkewHeap *left;

    // constructor to make a new
    // node of heap
    SkewHeap()
    {
        key = 0;
        right = NULL;
        left = NULL;
    }

    // the special merge function that's
    // used in most of the other operations
    // also
    SkewHeap *merge(SkewHeap *h1, SkewHeap *h2)
    {
        // If one of the heaps is empty
        if (h1 == NULL)
            return h2;
        if (h2 == NULL)
            return h1;

        // Make sure that h1 has smaller
        // key.
        if (h1->key > h2->key)
            swap(h1, h2);

        // Swap h1->left and h1->right
        swap(h1->left, h1->right);

        // Merge h2 and h1->left and make
        // merged tree as left of h1.
        h1->left = merge(h2, h1->left);

        return h1;
    }

    // function to construct heap using
    // values in the array
    SkewHeap *construct(SkewHeap *root,
                        int heap[], int n)
    {
        SkewHeap *temp;
        for (int i = 0; i < n; i++)
        {
            temp = new SkewHeap;
            temp->key = heap[i];
            root = merge(root, temp);
        }
        return root;
    }

    // function to print the Skew Heap,
    // as it is in form of a tree so we use
    // tree traversal algorithms
    void inorder(SkewHeap *root)
    {
        if (root == NULL)
            return;
        else
        {
            inorder(root->left);
            cout << root->key << " ";
            inorder(root->right);
        }
        return;
    }
};

// Driver Code
int main()
{
    // Construct two heaps
    SkewHeap heap, *temp1 = NULL,
                   *temp2 = NULL;
    /*
            5
        / \
        / \
        10 12 */
    int heap1[] = {12, 5, 10};
    /*
            3
        / \
        / \
        7	 8
        /
    /
    14 */
    int heap2[] = {3, 7, 8, 14};
    int n1 = sizeof(heap1) / sizeof(heap1[0]);
    int n2 = sizeof(heap2) / sizeof(heap2[0]);
    temp1 = heap.construct(temp1, heap1, n1);
    temp2 = heap.construct(temp2, heap2, n2);

    // Merge two heaps
    temp1 = heap.merge(temp1, temp2);
    /*
            3
        / \
        / \
        5	 7
        / \ /
    8 10 14
    /
    12 */
    cout << "Merged Heap is: " << endl;
    heap.inorder(temp1);
}


#include <iostream>

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

template <typename DataType>
class BST
{
public:
    /***** Function Members *****/
    BST();

    bool empty() const;


    bool search(const DataType& item) const;

    void insert(const DataType& item);

    void remove(const DataType& item);

    void preorder(ostream& out) const;

    void leafcount(void) const;

    void nodesibling(const DataType& item) const;



private:
    /***** Node class *****/
    class BinNode
    {
    public:
        DataType data;
        BinNode* left;
        BinNode* right;

        BinNode() //binnode constructor
            : left(0), right(0)
        {}

        // Explicit Value
        BinNode(DataType item)
            : data(item), left(0), right(0)
        {}

    };// end of class BinNode declaration

    typedef BinNode* BinNodePointer;

    /***** Private Function Members *****/
    void search2(const DataType& item, bool& found,
        BinNodePointer& locptr, BinNodePointer& parent) const;


    void preorderAux(ostream& out,
        BST<DataType>::BinNodePointer subtreePtr) const;

    void leafcountaux(BST<DataType>::BinNodePointer subtreePtr, int& counter) const;

    BinNodePointer myRoot;

}; // end of class template declaration

// Definition of constructor
template <typename DataType>
inline BST<DataType>::BST()
    : myRoot(0)
{}

//Definition of empty
template <typename DataType>
inline bool BST<DataType>::empty() const
{
    return myRoot == 0;
}

// Definition of search
template <typename DataType>
bool BST<DataType>::search(const DataType& item) const
{
    BST<DataType>::BinNodePointer locptr = myRoot;
    bool found = false;
    while (!found && locptr != 0)
    {
        if (item < locptr->data)       // descend left
            locptr = locptr->left;
        else if (locptr->data < item)  // descend right
            locptr = locptr->right;
        else                           // item found
            found = true;
    }
    return found;
}

//--- Definition of insert()
template <typename DataType>
inline void BST<DataType>::insert(const DataType& item)
{
    BST<DataType>::BinNodePointer
        locptr = myRoot,   // search pointer
        parent = 0;        // pointer to parent of current node
    bool found = false;     // indicates if item already in BST
    while (!found && locptr != 0)
    {
        parent = locptr;
        if (item < locptr->data)       // descend left
            locptr = locptr->left;
        else if (locptr->data < item)  // descend right
            locptr = locptr->right;
        else                           // item found
            found = true;
    }
    if (!found)
    {                                 // construct node containing item
        locptr = new BST<DataType>::BinNode(item);
        if (parent == 0)               // empty tree
            myRoot = locptr;
        else if (item < parent->data)  // insert to left of parent
            parent->left = locptr;
        else                           // insert to right of parent
            parent->right = locptr;
    }
    else
        cout << "Item already in the tree\n";
}

//--- Definition of remove()
template <typename DataType>
void BST<DataType>::remove(const DataType& item)
{
    bool found;                      // checks if item is found
    BST<DataType>::BinNodePointer
        x,                       // pointing to node that will be deleted
        parent;                //    "    " parent of x and xSucc
    search2(item, found, x, parent);

    if (!found)
    {
        cout << "Item not found in the BST\n";
        return;
    }
    //else
    if (x->left != 0 && x->right != 0)
    {                                // node has 2 children
       // Find x's preorder and parent
        BST<DataType>::BinNodePointer xSucc = x->right;
        parent = x;
        while (xSucc->left != 0)       // descend left
        {
            parent = xSucc;
            xSucc = xSucc->left;
        }

        // moving xsucc to x
        // point to successor to be removed
        x->data = xSucc->data;
        x = xSucc;
    } // if node has 2 child end

    // node has 0 or 2 child
    BST<DataType>::BinNodePointer
        subtree = x->left;             // subtree to x pointer
    if (subtree == 0)
        subtree = x->right;
    if (parent == 0)                  // remove root
        myRoot = subtree;
    else if (parent->left == x)       // left child of parent
        parent->left = subtree;
    else                              // right child of parent
        parent->right = subtree;
    delete x;
}

//--- Definition of preorder()
template <typename DataType>
inline void BST<DataType>::preorder(ostream& out) const
{
    preorderAux(out, myRoot);
}

//--- Definition of search2()
template <typename DataType>
void BST<DataType>::search2(const DataType& item, bool& found,
    BST<DataType>::BinNodePointer& locptr,
    BST<DataType>::BinNodePointer& parent) const
{
    locptr = myRoot;
    parent = 0;
    found = false;
    while (!found && locptr != 0)
    {
        if (item < locptr->data)       // descend left
        {
            parent = locptr;
            locptr = locptr->left;
        }
        else if (locptr->data < item)  // descend right
        {
            parent = locptr;
            locptr = locptr->right;
        }
        else                           // item found
            found = true;
    }
}

//--- Definition of preorderAux()
template <typename DataType>
void BST<DataType>::preorderAux(ostream& out,
    BST<DataType>::BinNodePointer subtreeRoot) const
{
    if (subtreeRoot != 0)
    {
        out << subtreeRoot->data << "  ";      // V operation

        if (subtreeRoot->left != 0)
            cout << "\t\t " << subtreeRoot->left->data;
        else
            cout << "\t\tNIL ";
        if (subtreeRoot->right != 0)
            cout << "\t\t " << subtreeRoot->right->data << endl;
        else
            cout << "\t\tNIL " << endl;

        preorderAux(out, subtreeRoot->left);    // L operation
        preorderAux(out, subtreeRoot->right);   // R operation
    }
}

template <typename DataType>
void BST<DataType>::leafcountaux(BinNodePointer subtreePtr, int& counter) const {
    if (subtreePtr != 0) {
        if (subtreePtr->right == 0 && subtreePtr->left == 0 && subtreePtr != myRoot) //checking if 0
            ++counter;


        leafcountaux(subtreePtr->left, counter); //decending left and right
        leafcountaux(subtreePtr->right, counter);
    }

}

template <typename DataType>
void BST<DataType>::leafcount(void) const {
    int leaf = 0;

    leafcountaux(myRoot, leaf); //calling leaf count function
    cout << leaf << " leaves in the tree." << endl;
}

template <typename DataType>
void BST<DataType>::nodesibling(const DataType& item) const {

    BST<DataType>::BinNodePointer
        findptr = myRoot,
        parent = 0;

    bool found = false;

    while (!found && findptr != 0) { //checking down list right
        if (item < findptr->data) { 
            parent = findptr;
            findptr = findptr->left;
        }
        else if (locptr->data < item) //checking down list left
            parent = findptr;
            findptr = findptr->right;
        }
        else {
            found = true; //letter found
    }
    if (found) { 
        if (parent == 0) //if item is current root no sibling
            cout << "" << item << " is the current root" << endl;
        else if (parent->left != 0 && parent->right != 0) { //if it has siblings
            if (item == parent->left->data)
                cout << parent->right->data << " is the sibling of " << item << endl;
            if (item == parent->right->data)
                cout << parent->left->data << " is the sibling of " << item << endl;
        }
        else
            cout << "There is no sibling of " << item << endl;
    }
    else
        cout << item << " not in the BST, invalid entry." << endl; //if item not in  bst
    }

#endif

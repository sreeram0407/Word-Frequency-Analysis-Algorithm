using namespace std;

#ifndef KONDAPALLI_SREERAM_HW5_KONDAPALLI_BST_H
#define KONDAPALLI_SREERAM_HW5_KONDAPALLI_BST_H
template <class T>
class Node {
private:
    T data;
    Node *left;
    Node *right;
public:
    Node();

    ~Node();

    Node(T data);

    void setLeft(Node *left);

    void setRight(Node *right);

    Node *getLeft();

    Node *getRight();

    T &getData();


};
template <class T>
class BinarySearchTree {
private:
    Node<T> *root;
    int unique;
    int size;
public:
    BinarySearchTree();

    ~BinarySearchTree();

    Node<T> *getRoot();

    bool Insert(T data);

    bool Remove(T data);

    Node<T> *successor(Node<T> *node);

    Node<T> *findParent(T data);

    bool deleteNode(Node<T> *toDelete);

    bool ElementExists(T data);

    Node<T> *Find(T data);

    Node<T> *finder(Node<T> *node, T data);

    int ToArray(T *output);

    int adder(Node<T> *node, T *output, int i);

    void Empty();

    int Count();

};
//Node Constructor
template <class T>
Node<T>::Node() {

    this->left = NULL;
    this->right = NULL;
}
//Node Destructor
template <class T>
Node<T>::~Node() {
    this->left = NULL;
    this->right = NULL;
}
//Node Modified Constructor
template <class T>
Node<T>::Node(T data){
    this->data = data;
    this->left = NULL;
    this->right = NULL;
}
//Node Left Setter
template <class T>
void Node<T>::setLeft(Node* left){
    this->left = left;
}
//Node Right Setter
template <class T>
void Node<T>::setRight(Node* right){
    this->right = right;
}
//Node Left Getter
template <class T>
Node<T>* Node<T>::getLeft(){
    return this->left;
}
//Node Right Getter
template <class T>
Node<T>* Node<T>::getRight(){
    return this->right;
}
//Node Data Getter
template <class T>
T& Node<T>::getData()
{
    return this->data;
}
//BinarySearchTree Constructor
template <class T>
BinarySearchTree<T>::BinarySearchTree()
{
    root = NULL;
    unique = 0;
    size = 0;
}
//BinarySearchTree Destructor
template <class T>
BinarySearchTree<T>::~BinarySearchTree(){
    if(root!=NULL){
        delete root;
        root = NULL;
    }
}
//BinarySearchTree Root Getter
template <class T>
Node<T>* BinarySearchTree<T>::getRoot(){
    return this->root;
}
//BinarySearchTree Insert Method
template <class T>
bool BinarySearchTree<T>::Insert(T data) {

//if the root is null then create new node and adding it to the root
    if(this->root == NULL){
        this->root = new Node<T>(data);
        this->size++;
        return true;
    }

    Node<T> * current = root;
    while(true){
//if the data is less than the left node then replace it
        if (data < current->getData()){
            if(current->getLeft()!= NULL){
                current = current->getLeft();
            }
            else{
                current->setLeft( new Node<T>(data));
                size++;
                return true;
            }
        }
//if the data is greater than the right node then replace it
        else if (data > current->getData()){
            if(current->getRight() != NULL){

                current = current->getRight();

            }
            else{
                current-> setRight(new Node<T>(data));
                size++;
                return true;
            }
        }
//otherwise just return false if it isnt any of the previous stated cases
        else{
            return false;
        }
    }
}
//BinarySearchTree Remove Data Method
template <class T>
bool BinarySearchTree<T>::Remove(T data){
//returns null if root is false
    if(root == NULL){
        return false;
    }

    Node<T>* toDelete = Find(data);
//returns null if toDelete is false
    if (toDelete == NULL){
        return false;
    }

    bool result = deleteNode(toDelete);
    if(result) size--;
    return result;

}
//BinarySearchTree Successor Method
template <class T>
Node<T>* BinarySearchTree<T>::successor(Node<T>* node){
    if(node == NULL){
        return NULL;
    }
    if(node->getLeft()==NULL){
        return node->getRight();
    }
    if(node->getRight()==NULL){
        return node->getLeft();
    }

    Node<T>* parent = node->getRight();
    Node<T>*cur = parent->getLeft();
    while(cur != NULL){
        parent = cur;
        cur = cur->getLeft();
    }
    return parent;
}
//BinarySearchTree Find Parent Method
template <class T>
Node<T>* BinarySearchTree<T>::findParent(T data){
    Node<T>* parent = NULL;
    Node<T>* node = root;

    if (node==NULL){
        return NULL;
    }


    while(node != NULL){
        if(data ==node->getData()) return parent;

        if (data < node->getData()){
            parent = node;
            node = node->getLeft();

        }
        else if(data > node->getData()){
            parent = node;
            node = node->getRight();

        }

    }
    return NULL;
}
//BinarySearchTree Delete Node Method
template <class T>
bool BinarySearchTree<T>::deleteNode(Node<T> * toDelete){
    if (toDelete==root){

        if(root->getLeft()==NULL){
            this->root = root->getRight();
            // size--;
            delete toDelete;
            return true;
        }
        if(root->getRight()==NULL){
            this->root = root->getLeft();
            // size--;
            delete toDelete;
            return true;
        }
        Node<T>* newNode = successor(toDelete);

        if(newNode!=NULL){
            Node<T>* nodeParent = findParent(newNode->getData());

            if( nodeParent != NULL){
                if(nodeParent!=toDelete)
                    newNode->setRight(toDelete->getRight());

                newNode->setLeft(toDelete->getLeft());
                if(nodeParent->getLeft()==newNode){
                    nodeParent->setLeft(NULL);
                }
                else if(nodeParent->getRight()==newNode){
                    nodeParent->setRight(NULL);
                }
            }

        }

        this->root = newNode;
        // size--;
        if(toDelete != NULL) delete toDelete;
        return true;
    }

    Node<T>* parent = findParent(toDelete->getData());
    if(parent == NULL) return false;
    if(parent->getRight()==toDelete){
        if(toDelete->getLeft()==NULL){
            parent->setRight(toDelete->getRight());
            //size--;
            if(toDelete!=NULL) delete toDelete;
            return true;
        }
        if(toDelete->getRight()==NULL){
            parent->setRight(toDelete->getLeft());
            //size--;
            if(toDelete!=NULL) delete toDelete;
            return true;
        }
        Node<T>* newNode = successor(toDelete);

        if(newNode!=NULL){
            Node<T>* nodeParent = findParent(newNode->getData());

            if(nodeParent != NULL){
                if(nodeParent!=toDelete)
                    newNode->setRight(toDelete->getRight());
                newNode->setLeft(toDelete->getLeft());
                if(nodeParent->getLeft()==newNode){
                    nodeParent->setLeft(NULL);
                }
                else if(nodeParent->getRight()==newNode){
                    nodeParent->setRight(NULL);
                }
            }
        }
        parent->setRight(newNode);
        //size--;
        if(toDelete != NULL){
            delete toDelete;
        }
        return true;
    }

    if(parent->getLeft()==toDelete){
        if(toDelete->getLeft()==NULL){
            parent->setLeft(toDelete->getRight());
            //size--;
            if(toDelete!=NULL) delete toDelete;
            return true;
        }
        if(toDelete->getRight()==NULL){
            parent->setLeft(toDelete->getLeft());
            //size--;
            if(toDelete!=NULL) delete toDelete;
            return true;
        }
        Node<T>* newNode = successor(toDelete);

        if(newNode!=NULL){
            Node<T>* nodeParent = findParent(newNode->getData());

            if( nodeParent != NULL){
                if(nodeParent!=toDelete)
                    newNode->setRight(toDelete->getRight());
                newNode->setLeft(toDelete->getLeft());
                if(nodeParent->getLeft()==newNode){
                    nodeParent->setLeft(NULL);
                }
                else if(nodeParent->getRight()==newNode){
                    nodeParent->setRight(NULL);
                }
            }
        }

        parent->setRight(newNode);
        //size--;
        if(toDelete != NULL){
            delete toDelete;
        }
        return true;
    }

    return false;

}
//BinarySearchTree Element Exists Method
template <class T>
bool BinarySearchTree<T>::ElementExists(T data){
    return Find(data) != NULL;
}
//BinarySearchTree Find Method
template <class T>
Node<T>* BinarySearchTree<T>::Find(T data){
    if (root ==NULL){
        return NULL;
    }
    return finder(root, data);

}
//BinarySearchTree Finder Method
template <class T>
Node<T>* BinarySearchTree<T>::finder(Node<T>* node, T data){
    if (node == NULL) return NULL;
    if (node->getData()==data){
        return node;
    }
    if(data < node->getData()){
        return finder(node->getLeft(), data);
    }

    return finder(node->getRight(), data);
}


//BinarySearchTree To Array Method
template <class T>
int BinarySearchTree<T>::ToArray(T* output){

    if(root == NULL){
        return 0;
    }
    return adder(root, output, 0);


}
//BinarySearchTree Adder tMethod
template <class T>
int BinarySearchTree<T>::adder(Node<T>* node, T* output, int i){
    if (node == NULL) return i;
    int t = adder(node->getLeft(), output, i);
    output[t] = node->getData();
    t++;
    t = adder(node->getRight(), output, t);
    return t;
}
//BinarySearchTree Empty Method
template <class T>
void BinarySearchTree<T>::Empty(){
    while(this->root != NULL){
        cout<<"Root->getData():"<<root->getData()<<endl;
        cout<<"Empty Count: "<<size<<endl;
        Remove(this->root->getData());

    }
    cout<<root<<endl;
    cout<<"Empty Count: "<<size<<endl;
    //size = 0;
}
//BinarySearchTree Count Method
template <class T>
int BinarySearchTree<T>::Count(){
    return size;
}

#endif //KONDAPALLI_SREERAM_HW5_KONDAPALLI_BST_H

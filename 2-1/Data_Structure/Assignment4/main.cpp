#include <iostream>
using namespace std;

template <class T>
class TreeNode {
    template<class K, class E>
    friend class Tree;
private:
    T data;
    TreeNode<T>* leftChild;
    TreeNode<T>* rightChild;
public:
    TreeNode(T data = 0, TreeNode<T>* leftChild = nullptr, TreeNode<T>* rightChild = nullptr)
    {
        this->data = data;
        this->leftChild = leftChild;
        this->rightChild = rightChild;
    }
};
template<class K, class E>
class Tree {
public:
    Tree(TreeNode<pair<K, E>>* root = nullptr)
    {
        this->root = root;
    }

    void Inorder();
    void Inorder(TreeNode<pair<K, E>>*);
    void Visit(TreeNode<pair<K, E>>*);
    pair<K, E>* Get(const K&);
    pair<K, E>* Get(TreeNode<pair<K, E>>*, const K&);
    void Insert(const pair<K, E>&);
    void Delete(const K&);

private:
    TreeNode<pair<K,E>>* root;
};
template <class K, class E>
void Tree<K,E>::Inorder()
{
    Inorder(root);
}

template <class K, class E>
void Tree<K, E>::Inorder(TreeNode<pair<K, E>>* currentNode)
{
    if (currentNode) {
        Inorder(currentNode->leftChild);
        Visit(currentNode);
        Inorder(currentNode->rightChild);
    }
}

template <class K, class E>
void Tree<K, E>::Visit(TreeNode<pair<K, E>>* currentNode)
{
    cout << "학번 : " << currentNode->data.first << ", 점수 : " << currentNode->data.second << "\n";
}


template <class K, class E>
pair<K, E>* Tree<K, E>::Get(const K& k)
{
    return Get(root, k);
}

template <class K, class E>
pair<K, E>* Tree<K, E>::Get(TreeNode<pair<K, E> >* p, const K& k)
{
    if (!p) return 0;
    if (k < p->data.first) return Get(p->leftChild, k);
    if (k > p->data.first) return Get(p->rightChild, k);
    return &p->data;
}

template <class K, class E>
void Tree<K, E>::Insert(const pair<K, E>& thePair)
{
    TreeNode<pair<K, E> >* p = root, * pp = 0;
    while (p) {
        pp = p;
        if (thePair.first < p->data.first) p = p->leftChild;
        else if (thePair.first > p->data.first) p = p->rightChild;
        else
        {
            p->data.second = thePair.second; return;
        }
    }

    p = new TreeNode<pair<K,E>> (thePair);
    if (root)
        if (thePair.first < pp->data.first) pp->leftChild = p;
        else pp->rightChild = p;
    else root = p;
}
template <class K,class E>
void Tree<K,E>::Delete(const K& x){
    TreeNode<pair<K,E>> *p = root, *pp = p;
    while(p)    {
        if(x < p->data.first)        {            
            pp = p;
            p = p->leftChild;
        }
        else if( x > p->data.first)        {
            pp = p;
            p = p->rightChild;
        }
        else        {
            if(p->leftChild == nullptr && p->rightChild ==nullptr)            {
                if(p == pp->rightChild)
                    pp->rightChild = nullptr;
                else if(p == pp->leftChild)
                    pp->leftChild = nullptr;
                delete p;
                return;
            }
            else if(p->leftChild && p->rightChild)            {
                TreeNode<pair<K,E>>* min = nullptr;
                TreeNode<pair<K,E>>* pLeft = p->leftChild;
                TreeNode<pair<K,E>>* pRight = p->rightChild;
                TreeNode<pair<K,E>>* parent = nullptr;
                int flag = 1;
                parent = p;
                min = p->rightChild;
                while(min->leftChild)                {
                    flag = 0;
                    parent = min;
                    min = min->leftChild;
                }
                if(flag)
                    p->rightChild = nullptr;
                else                    parent->leftChild = nullptr;                              
                if(p == pp->rightChild)
                    pp->rightChild = min;
                else if(p == pp->leftChild)
                    pp->leftChild = min;
                min->leftChild = pLeft;
                min->rightChild = pRight;
                delete p;
                return;
            }
            else
            {
                TreeNode<pair<K,E>>* temp = p;
                if(p->leftChild)
                {
                    temp = p->leftChild;

                }
                else    temp = p->rightChild;
                
                if(pp->leftChild == p)
                    pp->leftChild = temp;
                else pp->rightChild = temp;

                delete p;
                return;
            }
        }
    }
}

int main(void)
{
    Tree<int, int> tree;
    cout << "Insert Nodes in Tree.." << endl;
    tree.Insert(pair<int, int>(20220033, 90));
    tree.Insert(pair<int, int>(20220050, 73));
    tree.Insert(pair<int, int>(20220043, 99));
    tree.Insert(pair<int, int>(20220011, 82));
    tree.Insert(pair<int, int>(20220024, 78));
    tree.Insert(pair<int, int>(20220046, 96));
    tree.Insert(pair<int, int>(20220001, 72));
    tree.Insert(pair<int, int>(20220008, 88));
    tree.Insert(pair<int, int>(20220036, 77));
    tree.Insert(pair<int, int>(20220056, 93));
    tree.Insert(pair<int, int>(20220053, 82));
    tree.Insert(pair<int, int>(20220059, 100));

    
    tree.Inorder();

    cout << "Delete 20220050.." << endl;
    tree.Delete(20220050);

    tree.Inorder();

    cout << "Delete 20220008.." << endl;
    tree.Delete(20220008);

    tree.Inorder();

    cout << "Delete 20220056.." << endl;
    tree.Delete(20220056);

    tree.Inorder();

    if(tree.Get(20220056) == nullptr)
        cout << "20220056 is null" << endl;
    else
        cout << tree.Get(20220056)->first << ", " << tree.Get(20220056)->second << endl;

    if(tree.Get(20220043) == nullptr)
        cout << "20220043 is null" << endl;
    else
        cout << tree.Get(20220043)->first << ", " << tree.Get(20220043)->second << endl;

    
    cout << "prog end.." << endl;
    return 0;
}
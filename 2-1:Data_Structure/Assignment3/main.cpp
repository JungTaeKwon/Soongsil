#include <iostream>
#include <numeric>
using namespace std;
template <class T> class Chain;

template <class T>
class ChainNode {
friend class Chain<T>;
private:
  T data;
  ChainNode<T> *link;
public:
  ChainNode(){}
  ChainNode(int data)
  {
    this->data = data;
  }
};

class Number
{
private:
  int num;
public:
  Number(int n = 0) :num(n){}
  Number& operator=(const Number& ref)
  {
    num = ref.num;
    return *this;
  }
  operator int()
  {
    return num;
  }
  void ShowNumber() { cout << num << endl; }
};


template <class T>
class Chain {
class ChainIterator {
  friend Chain<T>;
public:  
    ChainIterator(ChainNode<T>* startNode = 0)
    {current = startNode;}
  
  T& operator*() const {return current->data;}
  T* operator->() const {return &current->data;}
  
  ChainIterator& operator++()   
    {current = current->link; return *this;}
  ChainIterator operator++(int) 
    {
      ChainIterator old = *this;
      current = current->link;
      return old;
    }
  
  bool operator!=(const ChainIterator right) const
    {return current != right.current;}
  bool operator==(const ChainIterator right) const
    {return current == right.current;}
  private:
    ChainNode<T>* current;
};
public:
  Chain() {
      first = nullptr;
      last = nullptr;
  }; 
  ~Chain()
  {
      if(first)        
      {
          ChainNode<T> *delNode = nullptr;
          while(first)
          {
              delNode = first;
              first = first->link;
              delete delNode;
            }
        }
  }
  void InsertFront(ChainNode<T>* i)
  {
      i->link = first;
      first = i;
  }
  void InsertBack(ChainNode<T>* i)
  {
      if(first)
      {
          last->link = i;
          last = last->link;
      }
      else first=last=i;
  }
  ChainNode<T>& Front()
  {
    return *first;
  }
  ChainNode<T>& Back()
  {
    return *last;
  }
  ChainNode<T>& Get(int i)
  {
    ChainIterator c = this->Begin();
    while(i>0)
    {
      i--;
      c++;
    }
    return *(c.current);
  }
  void DeleteFront()
  {
    ChainNode<T>* delNode = first;
    first = first->link;
    delete delNode;
  }
  void DeleteBack()
  {
    ChainNode<T>* delNode = first;
    while(delNode->link != last)
    {
      delNode = delNode->link;
    }
    delete last;
    last = delNode;
  }
  void InsertI(ChainNode<T>* index, int i)
  {
    ChainIterator c = this->Begin();
    while(i>0)
    {
      c++;
      i--;
    }
    index->link = c.current->link;
    c.current->link = index;
  }
  void DeleteI(int i)
  {
    ChainNode<T>* delNode = first->link;
    ChainNode<T>* preNode = first;
    while(i>1)
    {
      delNode = delNode->link;
      preNode = preNode->link;
      i--;
    }
    preNode->link = delNode->link;
    delete delNode;
  }
  ChainIterator Begin() { return ChainIterator(first); }
  ChainIterator End() { return ChainIterator(last = last->link); }
  void showTotalNode()
  {
    ChainIterator c = Begin();
    while(c.current != last)
    {
      cout << c.current->data << " ";
      c++;
    }
    cout << last->data << " ";
    cout << endl;
  }
  void ShowExNode(ChainNode<T>& c)
  {
    cout << c.data << endl;
  }
  void ShowSumofNodes()
  {
  this->InsertBack(new ChainNode<Number>(0));
    int sum = accumulate(Begin(),End(),0);
    cout << "sum = " << sum << endl;
    this->DeleteBack();
  }
private:
  ChainNode<T> *first;
  ChainNode<T> *last;
};


int main(void)
{
  Chain<Number> chain;
  chain.InsertBack(new ChainNode<Number>(1));
  chain.InsertBack(new ChainNode<Number>(2));
  chain.InsertBack(new ChainNode<Number>(3));
  chain.InsertBack(new ChainNode<Number>(4));
  chain.InsertBack(new ChainNode<Number>(5));
  chain.InsertBack(new ChainNode<Number>(6));
  chain.InsertBack(new ChainNode<Number>(7));
  chain.InsertBack(new ChainNode<Number>(8));
  chain.InsertBack(new ChainNode<Number>(9));
  cout << "Added 1~9 Nodes.." << endl;
  chain.showTotalNode();

  chain.InsertFront(new ChainNode<Number>(0));
  cout << "Add Node 0.." << endl;
  chain.showTotalNode();

  chain.InsertBack(new ChainNode<Number>(10));
  cout << "Add Node 10.." << endl;
  chain.showTotalNode();

  cout << "Show Front Node.." << endl;
  chain.ShowExNode(chain.Front());
  
  cout << "Show Back Node.." << endl;
  chain.ShowExNode(chain.Back());

  cout << "Show 2nd Node.." << endl;
  chain.ShowExNode(chain.Get(2));

  chain.DeleteFront();
  cout << "Delete Front Node.." << endl;
  chain.showTotalNode();

  chain.DeleteBack();
  cout << "Delete Back Node.." << endl;
  chain.showTotalNode();

  chain.InsertI(new ChainNode<Number>(100),2);
  cout << "Insert Node 100 between 3,4.." << endl;
  chain.showTotalNode();

  chain.DeleteI(6);
  cout << "Delete 6th Node.." << endl;
  chain.showTotalNode();
  
  cout << "Show Sum of Nodes.." << endl;
  chain.ShowSumofNodes();
  
  return 0;
}

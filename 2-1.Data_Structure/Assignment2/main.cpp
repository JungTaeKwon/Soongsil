#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
 
using namespace std;
 
class Bizcard {
private:
    char* name;
    char* address;
    long long office_phone;
    long long mobile_phone;
public:
    Bizcard() {}
    Bizcard(const char* name, const char* address, long long office_phone, long long mobile_phone) : office_phone(office_phone), mobile_phone(mobile_phone)
    {
        this->name = new char[strlen(name) + 1];
        this->address = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->address, address);
    }
    Bizcard(const Bizcard& copy) : office_phone(copy.office_phone), mobile_phone(copy.mobile_phone)
    {
        this->name = new char[strlen(copy.name) + 1];
        this->address = new char[strlen(copy.name) + 1];
        strcpy(this->name, copy.name);
        strcpy(this->address, copy.address);
    }
    Bizcard& operator=(const Bizcard& ref)
    {
        delete[] name;
        delete[] address;
        this->name = new char[strlen(ref.name) + 1];
        this->address = new char[strlen(ref.name) + 1];
        strcpy(this->name, ref.name);
        strcpy(this->address, ref.address);
        this->office_phone = ref.office_phone;
        this->mobile_phone = ref.mobile_phone;
        return *this;
    }   
    ~Bizcard()
    {
        delete[] this->name;
        delete[] this->address;
    }
    void Showinfo(void) const;
};
 
void Bizcard::Showinfo(void) const
{
    cout << "이름 : " << this->name << endl;
    cout << "주소 : " << this->address << endl;
    cout << "업무 핸드폰 번호 : " << this->office_phone << endl;
    cout << "개인 핸드폰 번호 : " << this->mobile_phone << endl;
    return;
}
 
template<class T>
class Bag
{
public:
    Bag(int bagCapacity = 3);
    ~Bag();

    int Size() const;
    bool IsEmpty() const;
    T& Element() const;
 
    void Push(const T&);
    void Pop();
    void ChangeSize1D(T*& a, const int oldSize, const int newSize);
 
private:
    T* array;
    int capacity;
    int top;
};
 
template <class T>
Bag<T>::Bag(int bagCapacity) : capacity(bagCapacity) {
    if (capacity < 1) throw "Capacity must be > 0";
    array = new T[capacity];
    top = -1;
}
 
template <class T>
Bag<T>::~Bag() { cout << "Bag destructor.." << endl; delete[] array; }
 
template <class T>
int Bag<T>::Size() const
{
    return this->top + 1;

}
template <class T>
bool Bag<T>::IsEmpty() const
{
    return this->Size() == 0;
}
 
template <class T>
T& Bag<T>::Element() const
{
    if (IsEmpty()) throw "Bag is empty (from Element())";
    return array[rand() % (this->top + 1)];
}
 
template <class T>
void Bag<T>::Push(const T& x) {
    if (capacity == top + 1)
    {
        ChangeSize1D(array, capacity, 2 * capacity);
        capacity *= 2;
    }
    array[++top] = x;
}
 
template <class T>
void Bag<T>::Pop()
{
    if (IsEmpty()) throw "Bag is empty, cannot delete";
    int deletePos = rand() % (this->Size());
    copy(array + deletePos + 1, array + top + 1, array + deletePos);
    top--;
}
 
template <class T>
void Bag<T>::ChangeSize1D(T*& a, const int oldSize, const int newSize)
{
    if (newSize < 0) throw "New length must be >= 0";
 
    T* temp = new T[newSize];
    int number = min(oldSize, newSize);
    copy(a, a + number, temp);
    delete[] a;
    a = temp;
    cout << endl << "Bag capacity doubled..." << endl << endl;
}
 
template <class T>
void ShowBagState(Bag<T>& b)
{
    cout << "Bag state>>" << endl;
    cout << "Bag current size : " << b.Size() << endl;
    if (b.IsEmpty())
        cout << "The bag is empty (from IsEmpty())" << endl;
    try {
        b.Element().Showinfo();
    }
    catch (const char* exp)
    {
        cout << exp << endl;
    }
    cout << endl;
}
int main(void)
{
    srand((unsigned)time(NULL));
    Bag<Bizcard> b;
 
    ShowBagState(b);
 
    Bizcard b1("가나", "가나로 12길", 11111111111, 10101010101);
    Bizcard b2("다라", "다라로 34길", 22222222222, 20202020202);
    Bizcard b3("마바", "마바로 56길", 33333333333, 30303030303);
 
    b.Push(b1);
    cout << "Push Bizcard1.." << endl;
    b.Push(b2);
    cout << "Push Bizcard2.." << endl;
    b.Push(b3);
    cout << "Push Bizcard3.." << endl << endl;
 
    ShowBagState(b);
    
    Bizcard b4("사자", "사자로 78길", 44444444444, 40404040404);
    Bizcard b5("아차", "아자로 910길", 55555555555, 50505050505);
    Bizcard b6("차카", "차카로 1011길", 66666666666, 60606060606);
    Bizcard b7("타파", "타파로 1213길", 77777777777, 70707070707);
 
    b.Push(b4);
    cout << "Push Bizcard4.." << endl;
    b.Push(b5);
    cout << "Push Bizcard5.." << endl;
    b.Push(b6);
    cout << "Push Bizcard6.." << endl;
    b.Push(b7);
    cout << "Push Bizcard7.." << endl << endl;
 
    ShowBagState(b);
 
    b.Pop();
    cout << "Pop random Bizcard.." << endl;
    b.Pop();
    cout << "Pop random Bizcard.." << endl << endl;
 
    ShowBagState(b);
    
    cout << "end of prog.." << endl;
    return 0;
} 
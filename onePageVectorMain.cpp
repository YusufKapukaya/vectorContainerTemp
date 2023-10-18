#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;



template<typename T>
class VectorCont
{
private:
    T* contents;
    int size;
    int capacity;
public:
    VectorCont();
    VectorCont(int capacity);
    VectorCont(T* contents, int size, int capacity);
    ~VectorCont();
    void intArrayAppend(T value);
    void operator=(const VectorCont& r);
    void intArrayInsert(int index, T value);
    void intArrayremoveAt(int index);
    void intArrayremove(T value);
    T intArrayGet(int index, T* value);
    T* intArrayGetRef(int index);
    void intArraySet(int index, T value);
    void printCont();

//friend ostream& operator<<(ostream& os, const VectorCont& r);


};

template<typename T>
VectorCont<T>::VectorCont()
{
    capacity=10;
    contents= new T[capacity];
    size=0;
    cout<<"Default Ctor cagirildi."<<endl;
}

template<typename T>
VectorCont<T>::VectorCont(int capacity): capacity(capacity)
{
    if(capacity>0)
    {
        contents= new T[capacity];
        size=0;
        cout<<"Capacity parameter Ctor cagirildi."<<endl;
    }
    else
    {
        throw exception();
    }
}

template<typename T>
VectorCont<T>::VectorCont(T* contents, int size, int capacity):contents(contents),size(size),capacity(capacity)
{
    if(capacity>=1 && size>=0 && size<=capacity)
    {
        cout<<"All of the Parameter Ctor cagirildi."<<endl;
    }
    else
    {
        throw exception();
    }

}

template<typename T>
VectorCont<T>::~VectorCont()
{
    cout<<"Destructor has been called called"<<endl;
}


template<typename T>
void VectorCont<T>::operator=(const VectorCont& r)
{
    delete[] contents;
    contents= new T [r.capacity];
    size=r.size;
    capacity=r.capacity;
    for(int i=0; i<size; i++)
    {
        contents[i]=r.contents[i];
    }

    cout<<"Copy Assightmend cagirildi."<<endl;

}



template<typename T>
void VectorCont<T>::intArrayAppend(T value)
{
    if(size>=capacity)
    {
        capacity*=2;
        T* temp=new T[capacity];
        for(int i=0; i<size; i++)
        {
            temp[i]=this->contents[i];
        }
        delete[] contents;
        this->contents=temp;

    }
    this->contents[size]=value;
    size++;
}
template<typename T>
void VectorCont<T>::intArrayInsert(int index, T value)
{

    if(size>=capacity)
    {
        capacity*=2;
        T* temp=new T [capacity];
        delete[] contents;
        contents=temp;
    }
    /*for(int i=size;i==index;i--)
    {
        this->contents[i+1]=this->contents[i];
    }

    contents[index]=value;
    */
    int i=0;
    T* temp=new T [capacity];
    while(i<size)
    {
        if(i<index)
        {
            temp[i]=contents[i];
        }
        else
        {
            temp[i+1]=contents[i];
        }
        i++;
    }
    temp[index]=value;
    delete[] contents;
    contents=temp;
    size++;
}
template<typename T>
void VectorCont<T>::intArrayremoveAt(int index)
{
    int i=0;
    size--;
    if(size<(capacity/2))
    {
        capacity/=2;
    }
    T* temp=new T [capacity];
    while(i<size)
    {
        if(i<index)
        {
            temp[i]=contents[i];
        }
        else
        {
            temp[i]=contents[i+1];
        }
        i++;
    }

    delete[] contents;
    contents=temp;
}

template<typename T>
void VectorCont<T>::intArrayremove(T value)
{
    int i=0;
    bool increas=false;
    bool flag=true;
    while(flag)
    {
        if(contents[i]==value)
        {
            while(i<size)
            {
                contents[i]=contents[i+1];
                i++;
            }
            flag=false;
            increas=true;
        }
        i++;
        if(i>size) break;
    }
    if(increas)
    {
        size--;
        if(size<(capacity/2))
        {
            capacity/=2;
        }
    }
}
template<typename T>
T VectorCont<T>::intArrayGet(int index, T* value)
{
    if(index>=0 && index<size)
    {

        value=contents+index;
        return *value;

    }
    else
    {
        return 0;
    }
}

template<typename T>
T* VectorCont<T>::intArrayGetRef(int index)
{
    return contents+=index;
}

template<typename T>
void VectorCont<T>::intArraySet(int index, T value)
{
    contents[index]=value;
}

template<typename T>
void VectorCont<T>::printCont()
{
    for(int i=0; i<size; i++)
    {
        //classimiz generic (template) kurgulu oldugu icin cout ile content arrayin icindeki
        //bir elemani yazdirmak istiyorsak bu arrayin icinde ki elemanin tipiyle ilgili olarak
        //cout<< icin operator overloading yapilmali.
        //cout<<ögrenci objekti ise yapmamiz gerekir.
        //Iterator destegi ile bu sorunu cözebiliriz
        cout<<contents[i]<<"  ";
    }
    cout<<endl;
}


/*ostream& operator<<(ostream& os, const VectorCont& r)
{
    return os<<r.capacity<<" Capacity and "<<r.size<<" Size"<<endl;
}*/


int main()
{

    VectorCont<float> a;
    int choice;
    cout<<"Which operation do you want? \n"
        <<" intArrayAppend(1);"
        <<" operator=(2);"
        <<" intArrayInsert(3);"
        <<" intArrayremoveAt(4);"
        <<" intArrayremove(5); \n"<<endl
        <<" intArrayGet(6);"
        <<" intArrayGetRef(7);"
        <<" intArraySet(8);"
        <<" printCont(9)"
        <<"to Exit Press (10)\n";
    cin>>choice;
    while(choice!=10)
    {
        if(choice==1)
        {
            float value;
            cout<<"Give a number "<<endl;
            cin>>value;
            a.intArrayAppend(value);
        }
        else if (choice==2)
        {
            VectorCont<float> b;
            b=a;
            b.printCont();
        }
        else if (choice==3)
        {
            int index;
            float value;
            cout<<"Give a index "<<endl;
            cin>>index;
            cout<<"and a value"<<endl;
            cin>>value;
            a.intArrayInsert(index,value);
        }
        else if (choice==4)
        {
            int index;
            cout<<"Which index do you want to delete?"<<endl;
            cin>>index;
            a.intArrayremoveAt(index);
        }
        else if(choice==5)
        {
            cout<<"Which value do you want to delete?"<<endl;
            float value;
            cin>>value;
            a.intArrayremove(value);
        }
        else if(choice==6)
        {
            cout<<"Which index"<<endl;
            int index;
            float result;
            cin>>index;
            float* value;
            result=a.intArrayGet(index,value);
            cout<<result;
        }
        else if (choice==7)
        {
            cout<<"Which index"<<endl;
            int index;
            float* result;
            cin>>index;
            result=a.intArrayGetRef(index);
            cout<<"The Result is "<<*result<<endl;
        } else if (choice==8){
            int index;
            float value;
            cout<<"Give a index of array?"<<endl;
            cin>>index;
            cout<<"and a value?"<<endl;
            cin>>value;
            a.intArraySet(index,value);
        } else if(choice==9){
            a.printCont();
        }else if(choice==10){
            return 0;
        }
        cout<<"Your choice again"<<endl;
        cin>>choice;
    }

    //cout<<a;

    /*int* k=new int;
    *k=a.intArrayGet(4,k);
    cout<<*k<<endl;             ArrayGet fonksiyonunu cagirma islemi*/



    return 0;
}


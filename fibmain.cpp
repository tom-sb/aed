#include <iostream>
#include "myfib.cpp"
#include "stdlib.h"

using namespace std;
int main(){
    FibonacciHeap<int> fib;
    fib.fib_insert(15);
    //fib.fib_insert(11);
    fib.fib_insert(11);
    fib.fib_insert(2);
    fib.fib_insert(6);
    fib.fib_insert(108);
    fib.fib_insert(88);
    //fib.deleteMin();
    fib.fib_insert(9);
    fib.fib_insert(38);
    fib.fib_insert(45);
    fib.fib_insert(1);
    cout<<fib.getMin()<<endl;
    fib.deleteMin();
    cout<<fib.getMin()<<endl;
    fib.decreaseKey(9,1);
    //fib.deleteMin();
    cout<<fib.getMin()<<endl;
    // fib.deleteMin();
    // cout<<fib.getMin()<<endl;
    // fib.deleteMin();
    // cout<<fib.getMin()<<endl;
    // // cout<<fib.fib_find(15)<<endl;
    // cout<<fib.fib_find(5)<<endl;
    fib.print();
    return 0;
}

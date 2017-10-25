#include<iostream>
#include<climits>
using namespace std;

void swap(int* x, int* y){
	int temp = *x;
	*x = *y;
	*y = temp;
}

//template <class T>
class MaxHeap{
		int *pArray;
		int capacity;
		int heap_size;
	public:
		MaxHeap(int tam);
		int parent(int i);
		int left(int i);
		int right(int i);
        void insertKey(int k);
		int extractMax();
        void Heapify(int i);
		void increaseKey(int i, int new_val);
		int getMax();
		void deleteKey(int i);

};

//template <class T>
MaxHeap::MaxHeap(int tam){
    capacity = tam;
    heap_size = 0;
    pArray = new int[tam];
}

//template <class T>
void MaxHeap::insertKey(int k){
    if (heap_size == capacity){
		cout<<"el heap esta lleno"<<endl;
		return;
	}

	heap_size++;
	int i = heap_size -1;
	pArray[i] = k;

	while (i != 0 && pArray[parent(i)] < pArray[i]){
		swap(&pArray[i], &pArray[parent(i)]);
		i = parent(i);
	}
}

//template <class T>
int MaxHeap::parent(int i){
	return ((i-1)/2);
}

//template <class T>
int MaxHeap::left(int i){
	return (2*i + 1);
}

//template <class T>
int MaxHeap::right(int i){
	return (2*i + 2);
}

void MaxHeap::Heapify(int i){
	int l = left(i);
	int r = right(i);
	int biggest = i;

	if (l < heap_size && pArray[l] > pArray[i])
		biggest =l;
	if (r < heap_size && pArray[r] > pArray[biggest])
		biggest = r;
	if (biggest == i)
		return;
	swap(&pArray[i], &pArray[biggest]);
	Heapify(biggest);
}

//template <class T>
int MaxHeap::extractMax(){
	if (heap_size == 0)
	   return 0;
	if (heap_size == 1){
		heap_size--;
		return pArray[0];
	}

	int root = pArray[0];
	pArray[0] = pArray[heap_size-1];
	heap_size--;
	Heapify(0);

	return root;
}

//template <class T>
void MaxHeap::increaseKey(int i, int new_val){
	pArray[i] = new_val;

	while(i != 0 && pArray[parent(i)] < pArray[i]){
		swap(&pArray[i], &pArray[parent(i)]);
		i = parent(i);
	}
}

//template <class T>
int MaxHeap::getMax(){
	return pArray[0];
}

//template <class T>
void MaxHeap::deleteKey(int i){
	increaseKey(i, INT_MAX);
	extractMax();
}

int main(){
	MaxHeap maxh1(11);

	maxh1.insertKey(3);
	maxh1.insertKey(2);
	maxh1.deleteKey(1);
	maxh1.insertKey(15);
	maxh1.insertKey(5);
	maxh1.insertKey(4);
	maxh1.insertKey(45);
	cout<<maxh1.extractMax()<< " - ";
	cout<<maxh1.getMax()<< " - ";
	maxh1.increaseKey(2,1);
	cout<<maxh1.getMax()<<endl;
	return 0;
}

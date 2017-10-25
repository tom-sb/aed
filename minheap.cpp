#include<iostream>
#include<climits>
using namespace std;

void swap(int* x, int* y){
	int temp = *x;
	*x = *y;
	*y = temp;
}

//template <class T>
class MinHeap{
		int *pArray;
		int capacity;
		int heap_size;
	public:
		MinHeap(int tam);
		void Heapify(int i);
		int parent(int i);
		int left(int i);
		int right(int i);
		int extractMin();
		void decereaseKey(int i, int new_val);
		int getMin();
		void deleteKey(int i);
		void insertKey(int k);
};

//template <class T>
MinHeap::MinHeap(int tam){
	heap_size = 0;
	capacity = tam;
	pArray = new int[tam];
}

//template <class T>
int MinHeap::parent(int i){
	return ((i-1)/2);
}

//template <class T>
int MinHeap::left(int i){
	return (2*i + 1);
}

//template <class T>
int MinHeap::right(int i){
	return (2*i + 2);
}

//template <class T>
void MinHeap::insertKey(int k){
	if (heap_size == capacity){
		cout<<"no se puede insertar key"<<endl;
		return;
	}

	heap_size++;
	int i = heap_size -1;
	pArray[i] = k;

	while (i != 0 && pArray[parent(i)] > pArray[i]){
		swap(&pArray[i], &pArray[parent(i)]);
		i = parent(i);
	}
}

//template <class T>
void MinHeap::Heapify(int i){
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (l < heap_size && pArray[l] < pArray[i])
		smallest =l;
	if (r < heap_size && pArray[r] < pArray[smallest])
		smallest = r;
	// if (smallest != i){
	// 	swap(&pArray[i], &pArray[smallest]);
	// 	Heapify(smallest);
	// }
	if (smallest == i)
		return;
	swap(&pArray[i], &pArray[smallest]);
	Heapify(smallest);


	// int Minimo = i;
	// if (pArray[i] < pArray[left(pArray[i])])
	// 	Minimo = pArray[left(pArray[i])];
	// if (Minimo < pArray[right(pArray[i])])
	// 	Minimo = pArray[right(pArray[i])];
	// if (Minimo == i) return;
	// swap(pArray[i], pArray[Minimo]);
	// Heapify(Minimo);

}

//template <class T>
int MinHeap::extractMin(){
	if (heap_size <= 0)
		return 0;//INT_MAX;
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
void MinHeap::decereaseKey(int i, int new_val){
	pArray[i] = new_val;
	while(i != 0 && pArray[parent(i)] > pArray[i]){
		swap(&pArray[i], &pArray[parent(i)]);
		i = parent(i);
	}
}

//template <class T>
int MinHeap::getMin(){
	return pArray[0];
}

//template <class T>
void MinHeap::deleteKey(int i){
	decereaseKey(i, INT_MIN);
	extractMin();
}


int main(){
	MinHeap minh1(11);
	minh1.insertKey(3);
	minh1.insertKey(2);
	minh1.deleteKey(1);
	minh1.insertKey(15);
	minh1.insertKey(5);
	minh1.insertKey(4);
	minh1.insertKey(45);
	cout<<minh1.extractMin()<< " - ";
	cout<<minh1.getMin()<< " - ";
	minh1.decereaseKey(2,1);
	cout<<minh1.getMin()<<endl;
	return 0;
}

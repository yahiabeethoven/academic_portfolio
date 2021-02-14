#include<iostream>
#include<cstdlib>
#include<utility>
#include<algorithm>
#include<iomanip>
#include<time.h>
#include<vector>


using namespace std;


template <typename T> void selectionSort(T A[], int n);
template <typename T> void bubbleSort(T A[], int n);
template <typename T> void mergeSort(T A[], int left, int right);
template <typename T> void merge(T A[], int left, int right, int mid);
template <typename T> void quickSort(T A[], int left, int right);
template <typename T> int partition(T A[], int left, int right);
template <typename T> void print(T A[], int n);

int main() {
	int n = 10000;
	int range = 500000;
	srand(unsigned (time(NULL))); 
	int A[n];
	for (int i = 0; i < n; i++) {
		A[i] = rand() % range;
	}
	cout<<endl;
	int begin1 = clock();
	selectionSort(A, n);
	int end1 = clock();
	cout << "Selection Sort runtime: "<< (float)(end1 - begin1) / CLOCKS_PER_SEC * 1000 << " milliseconds." << endl;
	cout<<endl;

	random_shuffle(A, A + n);
	int begin2 = clock();
	bubbleSort(A, n);
	int end2 = clock();
	cout << "Bubble Sort runtime: "<< (float)(end2 - begin2) / CLOCKS_PER_SEC * 1000 << " milliseconds." << endl;
	cout<<endl;

	random_shuffle(A, A + n);
	int begin3 = clock();
	mergeSort(A, 0, n -1);
	int end3 = clock();
	cout << "Merge Sort runtime: "<< (float)(end3 - begin3) / CLOCKS_PER_SEC * 1000 << " milliseconds." << endl;
	cout<<endl;

	random_shuffle(A, A + n);
	int begin4 = clock();
	quickSort(A, 0, n - 1);
	int end4 = clock();
	cout << "Quick Sort runtime: "<< (float)(end4 - begin4) / CLOCKS_PER_SEC * 1000 << " milliseconds." << endl;
	cout<<endl;

	return 0;
}

template <typename T> void selectionSort(T A[], int n) {
	
	int min;

	for (int i = 0; i < n; i++) {
		min = i;
		for (int j = i+1; j < n; j++) {
			if (A[j] < A[min]) {
				min = j;
			}	
		}
		swap(A[min], A[i]); 
	}
	// print(A, n);
}

template <typename T> void bubbleSort(T A[], int n) {

	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (A[j+1] < A[j]) {
				swap(A[j], A[j+1]);
			}
		}
	}
	// print(A, n);
}

template <typename T> void print(T A[], int n) {
	cout << "{";
	for (int i = 0; i < n; i++) {
		cout << A[i] << endl;  
	} 
	cout << "}" << endl;      
}

template <typename T> void mergeSort(T A[], int left, int right) {
	if (left >= right) {
		return;
	}	
	int mid = (left + right)/2;
	mergeSort(A, left, mid);
	mergeSort(A, mid + 1, right);
	merge(A, left, right, mid);
}
template <typename T> void merge(T A[], int left, int right, int mid) {
	int n1 = mid - left + 1;
	int n2 = right - mid;

	T L[n1];
	T R[n2];

	for (int i = 0; i < n1; i++) {
		L[i] = A[left + i];
	}
	for (int j = 0; j < n2; j++) {
		R[j] = A[mid + 1 + j];
	}
	int i = 0;
	int j = 0;
	int k = left;

	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
            A[k++] = L[i++];
            // i++;
        }
        else {
            A[k++] = R[j++];
            // j++;
        }
        // k++;
	}

	while (i < n1) {
        A[k++] = L[i++];
        // i++;
        // k++;
    }

    while (j < n2) {
        A[k++] = R[j++];
        // j++;
        // k++;
    }
}
template <typename T> void quickSort(T A[], int left, int right) {
	if (left < right)  
    {  
        int pi = partition(A, left, right);  
 
        quickSort(A, left, pi - 1);  
        quickSort(A, pi + 1, right);  
    } 	
}
template <typename T> int partition(T A[], int left, int right) {
	int pivot = A[right];   
    int j = left - 1;  
  
    for (int i = left; i <= right - 1; i++)  
    {  
  
        if (A[i] < pivot)  
        {  
            j++;   
            swap(A[i], A[j]);  
        }  
    }  
    swap(A[j + 1], A[right]);  
    return (j + 1);
}




#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

void swap(unsigned int arr[], int i, int j){
	unsigned int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void selectionSort(unsigned int arr[], int n){
	for(int i = 0; i < n - 1; ++i){
    	int min = i;
    	for(int j = i + 1; j < n; ++j){
        	if(arr[min] > arr[j]){
            	min = j;
        	}
    	}
    	swap(arr, min, i);
	}
}

void bubbleSort(unsigned int arr[], int n){
	for(int pass = 0; pass < n - 1; ++pass){
    	int swapped = 0;
    	for(int i = 0, j = i + 1; i < n - 1 - pass; ++i, ++j){
        	if(arr[i] > arr[j]){
            	swap(arr, i, j);
            	swapped = 1;
        	}
    	}
    	if(swapped == 0){
        	break;
    	}
	}
}

void insertionSort(unsigned int arr[], int n){
	for(int i = 1; i < n; ++i){
    	unsigned int key = arr[i];
    	int j = i - 1;
    	while(j >= 0 && arr[j] > key){
        	arr[j + 1] = arr[j];
        	--j;
    	}
    	arr[j + 1] = key;
	}
}

void merge(unsigned int arr[], int start, int mid, int end){
	int n1 = mid - start + 1;
	int n2 = end - mid;
    
	unsigned int left[n1];
	unsigned int right[n2];
    
	for(int i = 0; i < n1; ++i){
    	left[i] = arr[start + i];
	}
	for(int i = 0; i < n2; ++i){
    	right[i] = arr[mid + 1 + i];
	}
    
	int i = 0;
	int j = 0;
	int k = start;
	while(i < n1 && j < n2){
		if(left[i] < right[j])
			arr[k++] = left[i++];
		else
			arr[k++] = right[j++];
	}
    
	while(i < n1){
    	arr[k++] = left[i++];
	}
    
	while(j < n2){
    	arr[k++] = right[j++];
	}
}

void mergeSort(unsigned int arr[], int start, int end){
	int mid = start + (end - start) / 2;
	
	if(start < end){
		mergeSort(arr, start, mid);
		mergeSort(arr, mid + 1, end);
		merge(arr, start, mid, end);
	}
}

int partition(unsigned int arr[], int start, int end){
	int pivot = end;
	int i = start;
	int j = i - 1;

	for(; i < end; ++i){
		if(arr[i] < arr[pivot]){
			++j;
			swap(arr, i, j);
		}
	}

	++j;
	swap(arr, j, pivot);
	return j;
}

void quickSort(unsigned int arr[], int start, int end){
	if(start < end){
		int pivot = partition(arr, start, end);
		quickSort(arr, start, pivot - 1);
		quickSort(arr, pivot + 1, end);
	}
}

void reverseMerge(unsigned int arr[], int start, int mid, int end){
	int n1 = mid - start + 1;
	int n2 = end - mid;

	unsigned int left[n1];
	unsigned int right[n2];

	for(int i = 0; i < n1; ++i)
		left[i] = arr[start + i];

	for(int i = 0; i < n2; ++i)
		right[i] = arr[mid + 1 + i];

	int k = start;
	int i = 0, j = 0;

	while(i < n1 && j < n2){
		if(left[i] > right[j])
			arr[k++] = left[i++];
		else
			arr[k++] = right[j++];
	}

	while(i < n1)
		arr[k++] = left[i++];

	while(j < n2)
		arr[k++] = right[j++];

}

void reverseMergeSort(unsigned int arr[], int start, int end){
	if(start < end){
		int mid = start + (end - start) / 2;
		reverseMergeSort(arr, start, mid);
		reverseMergeSort(arr, mid + 1, end);
		reverseMerge(arr, start, mid, end);
	}
}

void printOrNot(unsigned int p, unsigned int temp[], int n){
	if(p == 1 || p == 2){
		if(n < 50){
		for(int i = 0; i < n; ++i){
    			printf("%d  ", temp[i]);
			}	
	}
	else{
		for(int i = 0; i < 50; ++i){
    			printf("%d  ", temp[i]);
			}	
		}
	}
	printf("\n\n");
}

// void copyArray(unsigned int temp[], unsigned int arr[], int n){
// 	for(int i = 0; i < n; ++i)
// 		temp[i] = arr[i];
// }

int main() {

	time_t rawtime;
   	struct tm * timeinfo;


   	time ( &rawtime );
   	timeinfo = localtime(&rawtime);

   	clock_t start, end;
 	double total_time_consumed, t1, t2, t3, t4, t5;


	int t;
	// printf("Test Cases: ");
	scanf("%d", &t);
    
	for(int i = 0; i < t; ++i){
    	int N;
    	// printf("Enter array size: ");
    	scanf("%d", &N);

    	int S;		//choice
    	scanf("%d", &S);

    	int k;
    	int p;

    	scanf("%d", &k);		// 0 - random, 1 - sorted, 2 - reverse sorted
    	scanf("%d", &p);		// 0 - no i/p arr no o/p arr, 1 - only o/p arr, 2 - both i/p and o/p arr
   	 
    	unsigned int arr[N];

   	 	srand(time(0));
    	for(int j = 0; j < N; ++j){
        	arr[j] = (rand() % 10000000);
    	}


    	// printf("Current Array: ");
    	// printarr(arr, N);

    	if(k == 1){
    		mergeSort(arr, 0, N - 1);
    	}
    	else if(k == 2){
    		reverseMergeSort(arr, 0, N - 1);
    	}

    	// unsigned int temp[N];

    	// copyArray(temp, arr, N);
    	if(p == 2)
    		printOrNot(p, arr, N);


    	if(S == 0){
    		start = clock(); // start time
    		bubbleSort(arr, N);
    		end = clock();               // end time
   			total_time_consumed = ((double) (end - start)) / CLOCKS_PER_SEC;
   			t1 = total_time_consumed;
   			printOrNot(p, arr, N);
   			printf("%f", t1);
    	}
    	else if(S == 1){
    		start = clock(); // start time
    		selectionSort(arr, N);
    		end = clock();               // end time
   			total_time_consumed = ((double) (end - start)) / CLOCKS_PER_SEC;
   			t2 = total_time_consumed;
   			printOrNot(p, arr, N);
   			printf("%f", t2);
    	}
    	else if(S == 2){
    		start = clock(); // start time
    		insertionSort(arr, N);
    		end = clock();
   			total_time_consumed = ((double) (end - start)) / CLOCKS_PER_SEC;
   			t3 = total_time_consumed;
   			printOrNot(p, arr, N);
   			printf("%f", t3);	
    	}
    	else if(S == 3){
    		start = clock(); // start time
    		mergeSort(arr, 0, N - 1);
    		end = clock();               // end time
   			total_time_consumed = ((double) (end - start)) / CLOCKS_PER_SEC;
   			t4 = total_time_consumed;
   			printOrNot(p, arr, N);
   			printf("%f", t4);	
    	}
    	else{
    		start = clock(); // start time
    		quickSort(arr, 0, N - 1);
    		end = clock();               // end time
   			total_time_consumed = ((double) (end - start)) / CLOCKS_PER_SEC;
   			t5 = total_time_consumed;
   	    	printOrNot(p, arr, N);
   	    	printf("%f", t5);	
    	}
    	printf("\n");
	}

	return 0;
}

#include <stdio.h>
//kontrol amaçlı print fonksiyonu
printArray(int* arr, int size){
	int i;
	printf("\n");
	for(i = 0; i < size; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}
////////////////////////////////////////////////////////////////////////////////////////////////////

int find_majority_brute_force(int arr[], int size){
	int counter = 0, i, j;
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++)
			if(arr[i] == arr[j])
				counter++;
		if(counter > size/2) return arr[i];
		counter = 0;
	}
	return -1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////

int find_maj_insertion_sort(int arr[], int size){
	int i;
	for (i = 1; i < size; i++){
		int min = arr[i];
		int j = i - 1;
		while(j >= 0 && arr[j] > min){
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = min;
	}
	return arr[size/2];
}
////////////////////////////////////////////////////////////////////////////////////////////////////

int merge(int* merged, int* rightSubArray, int right_size, int* leftSubArray, int left_size){
	int ax = 0; int bx = 0; int x = 0;     //right, left and merged arrays indexes
	while(ax < right_size && bx < left_size){
		if(rightSubArray[ax] <= leftSubArray[bx])
			merged[x++] = rightSubArray[ax++];
		else
			merged[x++] = leftSubArray[bx++];
	}
	if(ax >= right_size)
		while(bx < left_size) 
			merged[x++] = leftSubArray[bx++];
	else
		while(ax < right_size)
			merged[x++] = rightSubArray[ax++];
}

copyArr(int* arr, int size, int* rightSubArray, int right_size, int* leftSubArray){
	int i;
	for(i = 0; i < size; i++){
		if(i < right_size) rightSubArray[i] = arr[i];
		else leftSubArray[i-right_size] = arr[i];
	}
}

int find_maj_merge_sort(int arr[], int size){
	if(size==1) return arr[0];
	else{
		int left_size = size/2;
		int leftSubArray[left_size];
		int right_size = (size%2) ? size/2+1 : size/2;
		int rightSubArray[right_size];
		
		copyArr(arr, size, rightSubArray, right_size, leftSubArray);
		
		find_maj_merge_sort(rightSubArray, right_size);
		find_maj_merge_sort(leftSubArray, left_size);
		
		merge(arr, rightSubArray, right_size, leftSubArray, left_size);
	}
	return arr[size/2];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////

int partition(int* arr, int start, int end) {
    int pivot = arr[start];
    int i = start + 1, j = end;

    while (i <= j) {
        while (i <= end && arr[i] < pivot)
            i++;
        while (j >= start+1 && arr[j] > pivot)
            j--;

        if (i < j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        } else {
            break;
        }
    }
    arr[start] = arr[j];
    arr[j] = pivot;
    return j;
}

int find_maj_quick_sort(int arr[], int start, int end, int size){
	if (start >= end) return arr[size/2];
	int m = partition(arr, start ,end);
	find_maj_quick_sort(arr, start, m-1, size);
	find_maj_quick_sort(arr, m+1, end, size);			
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

int find_maj_divide_conquer(int arr[], int start, int end, int size){
	if (start >= end) return arr[start];
	int mid = (start + end) / 2;
	int m1 = find_maj_divide_conquer(arr, start, mid, size);
	int m2 = find_maj_divide_conquer(arr, mid+1, end, size);
	if (m1 == m2)  return m1;
	else{
		int i, m1count = 0, m2count = 0;
		for(i = 0; i < size; i++){
			if(arr[i] == m1) m1count++;
			if(arr[i] == m2) m2count++;
		}
		return (m1count > m2count) ? m1 : m2;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int find_maj_hashing(int arr[], int size){
	int max = arr[0], i;
	for(i = 1; i < size; i++)
		if (arr[i] > max) max = arr[i];
		 
	int* hashTable;
	hashTable = malloc(sizeof(int)*(max+1));
	for(i = 0; i < size; i++)
		hashTable[arr[i]] = 0; 
		
	max = arr[0]; 
	for(i = 0; i < size; i++)
		if(++hashTable[arr[i]] > hashTable[max]) max = arr[i];
		
	if(hashTable[max] > size/2) return max;
	else return -1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
	int arr[] = {0,1,1,1,2};
	int size = sizeof(arr)/4;
	puts("'majorities according to different algorithms'");
	printf("brute force: %d\n", find_majority_brute_force(arr,size));
	printf("insertion sort: %d\n", find_maj_insertion_sort(arr,size));
	printf("merge sort: %d\n", find_maj_merge_sort(arr,size));
	printf("quick sort: %d\n", find_maj_quick_sort(arr, 0, size-1, size));
	printf("divide & conquer: %d\n", find_maj_divide_conquer(arr, 0, size-1, size));
	printf("hashing: %d\n", find_maj_hashing(arr,size));
}

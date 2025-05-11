#include <stdio.h>
#include <time.h>
void print_array(int *arr, int size) {
	int i;
	puts(" ");
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void read_array(FILE *fp, int *arr, int size) {
    char ch;
    int i = 0;
    while ((ch = fgetc(fp)) != '[' && ch != EOF);

    while (i < size && fscanf(fp, "%d", &arr[i]) == 1) {
        i++;
        while ((ch = fgetc(fp)) != ',' && ch != ']' && ch != EOF);
        if (ch == ']') break;
    }
}



int checkIfMaj(int* arr, int size, int candidate){
	int i, count = 0;
	for(i = 0; i < size; i++)
		if(arr[i] == candidate) count++;
		
	if (count > size/2) return candidate;
	else return -1;
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

typedef struct {
    int value;
    int freq;
} HashCell;

int isPrime(int n) {
    if (n <= 1) return 0;
	int i;
    for (i = 2; i*i <= n; i++)
        if (n % i == 0) return 0;
    return 1;
}
int nextPrime(int n) {
    while (!isPrime(n)) n++;
    return n;
}

void addToHash(HashCell *hashTable, int hashSize,int value) {
    int index = value % hashSize;
    while (hashTable[index].freq >= 1) {
        if (hashTable[index].value == value) {
            hashTable[index].freq++;
            return;
        }
        index = (index + 1) % hashSize;
    }
    hashTable[index].value = value;
    hashTable[index].freq = 1;
}

int find_maj_hash(int arr[], int arr_size) {
	int i;
    int hashSize = nextPrime(arr_size * 2);
    HashCell *hashTable = calloc(hashSize, sizeof(HashCell));
    if (hashTable == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }

    for (i = 0; i < arr_size; i++) {
        addToHash(hashTable, hashSize, arr[i]);
    }
    for (i = 0; i < hashSize; i++) {
        if (hashTable[i].freq > arr_size / 2) {
            int majority = hashTable[i].value;
            free(hashTable);
            return majority;
        }
    }
    free(hashTable);
    return -1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int boyer_moore_majorty_vote(int arr[], int size){
	int currentNumber = arr[0];
	int counter = 0;
	int i;
	for(i = 0; i < size; i++){
		if(currentNumber == arr[i]) counter++;
		else{
			counter--;
			if(counter <= 0){
				if(i == size-1) return -1;
				else currentNumber = arr[i+1];
			}
		}
	}
	int controllMaj = 0;
	for(i = 0; i < size; i++){
		if(arr[i] == currentNumber) controllMaj++;
	}
	if(controllMaj > size/2) return currentNumber;
	return -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
	    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }
        FILE* f = fopen("output.txt", "w");
    if (f == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    fclose(f);
        f = fopen("output.txt", "a");
    if (f == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    int size = 0;
    char ch;
    while (fscanf(file, "size= %d", &size) == 1) {
        int *arr = malloc(size * sizeof(int));
        if (!arr) {
            printf("Memory allocation failed\n");
            fclose(file);
            return 1;
        }
        read_array(file, arr, size);
        //print_array(arr, size); 
		
		
		
		clock_t start, end;
	
		start = clock();
		int i;
		for(i = 0; i < 1000000; i++)
			find_maj_hash(arr,size);			//our algorithm runs here
	
		end = clock();

    	double elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    	printf("Elapsed CPU time: %.6f seconds\n", elapsed);
		fprintf(f, "size: %d, %.6f\n", size, elapsed);
		
		
		
        free(arr);  
        while ((ch = fgetc(file)) != '\n' && ch != EOF);
    }

    fclose(file);
	fclose(f);
	
	
	
	//printf("brute force: %d\n", find_majority_brute_force(arr,size));
	//printf("insertion sort: %d\n", checkIfMaj(arr, size, find_maj_insertion_sort(arr,size)));
	//printf("merge sort: %d\n", checkIfMaj(arr, size, find_maj_merge_sort(arr,size)));
	//printf("quick sort: %d\n", checkIfMaj(arr, size, find_maj_quick_sort(arr, 0, size-1, size)));
	//printf("divide & conquer: %d\n", checkIfMaj(arr, size, find_maj_divide_conquer(arr, 0, size-1, size)));
	//printf("hashing: %d\n", find_maj_hash(arr,size));
	//printf("Boyer Moore Majority Vote: %d\n", boyer_moore_majorty_vote(arr,size));
}

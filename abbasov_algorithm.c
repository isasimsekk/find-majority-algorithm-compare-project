#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

struct StNode{
	int data;
	int freq;
	struct StNode *parent;
	struct StNode *left;
	struct StNode *right;
};
typedef struct StNode StNode;
typedef StNode *StNodePtr;

StNodePtr Insert(StNodePtr, int, StNodePtr *);
void Splay(StNodePtr *, StNodePtr *);
void leftRotation(StNodePtr *, StNodePtr *);
void rightRotation(StNodePtr *, StNodePtr *);

int main(int argc, char *argv[]){
	int inNumber, i;
	FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
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
		for(i = 0; i < 100; i++){
			StNodePtr modRoot = NULL;
			StNodePtr modLastAdded = NULL;

			for (i = 0; i < size; i++){
				modRoot = Insert(modRoot, arr[i], &modLastAdded);
				if (modRoot->freq < modLastAdded->freq)
					Splay(&modRoot, &modLastAdded);
				}
			
			//printf("Majority Element:");
			//if(modRoot->freq > size/2) printf(" %d", modRoot->data); 
			//else puts(" -1");
			freeBST(modRoot);
		}
			
	
		end = clock();

    	double elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    	printf("Elapsed CPU time: %.6f seconds\n", elapsed);
		
		
		
		
        free(arr);  
        while ((ch = fgetc(file)) != '\n' && ch != EOF);
    }

    fclose(file);
	
}

void leftRotation(StNodePtr *lastAdded, StNodePtr *root){
	// to perform left rotation lastAdded must be right child of its parent.
	(*lastAdded)->parent->right = (*lastAdded)->left;	 // the left child of lastAdded is in the right of the parent of the lastAdded. After rotation its right child must be on the right of the former parent of lastAdded.
	(*lastAdded)->left = (*lastAdded)->parent;			 // lastAdded will become the root of the subtree so its left child must be its former parent.
	(*lastAdded)->parent = (*lastAdded)->parent->parent; // parent of the lastAdded must be its former grandparent at the end of the rotation
	if ((*lastAdded)->left->right != NULL)
		(*lastAdded)->left->right->parent = (*lastAdded)->left;

	(*lastAdded)->left->parent = (*lastAdded); // we denote parent of the former parent of lastAdded as lastAdded since the former parent is left child of lastAdded now.

	if ((*lastAdded)->parent == NULL) // if lastAdded don't have a parent no longer. It means that it is root now
		*root = *lastAdded;
	else{ // In this statement we confirm the subtree in where we perform the rotation is on the left of the grandparent or on the right
		if (((*lastAdded)->parent->left != NULL) && (*lastAdded)->parent->left->data == (*lastAdded)->left->data)
			(*lastAdded)->parent->left = (*lastAdded);
		else if (((*lastAdded)->parent->right != NULL) && (*lastAdded)->parent->right->data == (*lastAdded)->left->data)
			(*lastAdded)->parent->right = (*lastAdded);
	}
}
void rightRotation(StNodePtr *lastAdded, StNodePtr *root){
	// clockwise rotation.
	(*lastAdded)->parent->left = (*lastAdded)->right;
	(*lastAdded)->right = (*lastAdded)->parent;
	(*lastAdded)->parent = (*lastAdded)->parent->parent;

	if ((*lastAdded)->right->left != NULL)
		(*lastAdded)->right->left->parent = (*lastAdded)->right;

	(*lastAdded)->right->parent = *lastAdded;

	if ((*lastAdded)->parent == NULL)
		*root = *lastAdded;
	else
	{
		if ((*lastAdded)->parent->left != NULL && (*lastAdded)->parent->left->data == (*lastAdded)->right->data)
			(*lastAdded)->parent->left = (*lastAdded);
		else if ((*lastAdded)->parent->right != NULL && (*lastAdded)->parent->right->data == (*lastAdded)->right->data)
			(*lastAdded)->parent->right = (*lastAdded);
	}
}
void Splay(StNodePtr *root, StNodePtr *lastAdded){
	if ((*lastAdded)->parent != NULL){
		if ((*lastAdded)->parent->parent == NULL){ // For zig rotation
			if ((*lastAdded)->parent->left != NULL && (*lastAdded)->parent->left->data == (*lastAdded)->data){
				rightRotation(lastAdded, root);
			}
			else if ((*lastAdded)->parent->right != NULL && (*lastAdded)->parent->right->data == (*lastAdded)->data){
				leftRotation(lastAdded, root);
			}
		}
		else if ((*lastAdded)->parent->parent->left != NULL && (*lastAdded)->parent->parent->left->left != NULL && (*lastAdded)->parent->parent->left->left->data == (*lastAdded)->data){ // If lastAdded, parent and grandparent construct successive right directed line perform zigzig
			rightRotation(&((*lastAdded)->parent), root);
			rightRotation(lastAdded, root);
			Splay(root, lastAdded);
		}
		else if ((*lastAdded)->parent->parent->right != NULL && (*lastAdded)->parent->parent->right->right != NULL && (*lastAdded)->parent->parent->right->right->data == (*lastAdded)->data){ // If lastAdded, parent and grandparent construct successive left directed line perform zigzig
			leftRotation(&((*lastAdded)->parent), root);
			leftRotation(lastAdded, root);
			Splay(root, lastAdded);
		}
		// check if it provides the condition for zigzag case
		else if ((*lastAdded)->parent->parent->left != NULL && (*lastAdded)->parent->parent->left->right != NULL && (*lastAdded)->parent->parent->left->right->data == (*lastAdded)->data){
			leftRotation(lastAdded, root);
			rightRotation(lastAdded, root);
			Splay(root, lastAdded);
		}
		else if ((*lastAdded)->parent->parent->right != NULL && (*lastAdded)->parent->parent->right->left != NULL && (*lastAdded)->parent->parent->right->left->data == (*lastAdded)->data){
			rightRotation(lastAdded, root);
			leftRotation(lastAdded, root);
			Splay(root, lastAdded);
		}
	}
}
StNodePtr Insert(StNodePtr root, int data, StNodePtr *lastAdded){
	if (root == NULL){
		StNodePtr newNode = malloc(sizeof(StNode));
		newNode->data = data;
		newNode->freq = 1;
		newNode->left = newNode->right = newNode->parent = NULL;
		*lastAdded = newNode;
		return newNode;
	}
	else if(data < root->data){
		root->left = Insert(root->left, data, lastAdded);
		root->left->parent = root;
	}
	else if (data > root->data){
		root->right = Insert(root->right, data, lastAdded);
		root->right->parent = root;
	}
	else if (data == root->data){
		(root->freq)++;
		*lastAdded = root;
	}
	return root;
}
void freeBST(StNodePtr root) {
    if (root == NULL) {
        return;
    }
    freeBST(root->left);
    freeBST(root->right);
	
    free(root);
}

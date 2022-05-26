#include <stdlib.h>
#include <stdio.h>
#define T char
#define true 1==1
#define false 1!=1
typedef int bool;

typedef struct Node {
	struct Node *pNext;
	T data;
} Node;

typedef struct List {
	Node* head;
	int size;
} List;

void initList(List *list) {
	list->head = NULL;
	list->size = 0;
}

bool push(List *list, T value) {
	Node *temp = (Node*) malloc(sizeof(Node));
	if(temp == NULL)
		return false;
	temp->pNext = list->head;
	temp->data = value;
	list->head = temp;
	list->size++;
	return true;
}

T pop(List *list){
	if(list->size == 0){
		printf("Stack is empty\n");
		return -1;
	}
	Node *temp = list->head;
	T data = list->head->data;
	list->head = list->head->pNext;
	list->size--;
	free(temp);
	return data;
}

void printList(List *list) {
	Node *pCurrent = list->head;
	for(int i = 0; i < list->size; ++i){
		printf("%c ", pCurrent->data);
		pCurrent = pCurrent->pNext;
	}
}
// task 1
int bracesCheck(char* str) {
	char arrOpenBraces[] = {'(','{','['};
	char arrCloseBraces[] = {')','}',']'};
	List *list = (List*) malloc(sizeof(List));
    initList(list);
    int counter = 0;
    while(*str != '\0'){
    	for(int i = 0; i < sizeof(arrOpenBraces)/sizeof(char); ++i){
    		if(*str == arrOpenBraces[i])
    			push(list, arrOpenBraces[i]);
		}
		for(int i = 0; i < sizeof(arrCloseBraces)/sizeof(char); ++i){
			if(*str == arrCloseBraces[i]){
				if(list->size == 0)
					return counter;
				if(list->head->data == arrOpenBraces[i])
					pop(list);
				else return counter;
			}
		}
		str++;
		counter++;
	}
	if(list->size != 0)
		return 0;
	
	return -1;
}

// task 2
void copyList(List* from, List* to) {
	int size = from->size;
	Node *current = from->head;
	while(size != 0) {
		for(int i = 0; i < size-1; ++i){
			current = current->pNext;
		}
		push(to, current->data);
		size--;
		current = from->head;
	}
}

// task 3
bool isSorted(List* list) {
	Node *current = list->head;
	while(current->pNext != NULL){
		if(current->data > current->pNext->data)
			return false;
		current = current->pNext;
	}
	return true;
}
int main() {
// task 1
    printf("(): %d \n", bracesCheck("()"));
    printf("(: %d \n", bracesCheck("("));
    printf("])}): %d \n", bracesCheck("])})"));
    printf("(2+(2*2)): %d \n", bracesCheck("(2+(2*2))"));
    printf("[2/{5*(4+7)}]: %d \n", bracesCheck("[2/{5*(4+7)}]"));
    
    // task 2
    List *first = (List*) malloc(sizeof(List));
    initList(first);
    printf("\nFill the first stack: \n");
    char a = getchar();
    while(a != '\n'){
    	push(first, a);
    	a = getchar();
	}
    List *second = (List*) malloc(sizeof(List));
    initList(second);
    copyList(first, second);
    printf("second stack: \n");
    printList(second);
    
    // task 3
    printf("\nfirst stack sorted? \n");
    printf("%s \n", isSorted(first) ? "yes" : "no");
	
    return 0;
}
#include<stdio.h>
#include<stdlib.h>
 
struct Node {
    int data;
    struct Node* next;
};
typedef struct Node Node;

void printList(Node* head){
    Node* current = head;
    while(current != NULL){
        printf("%d ", current->data);
        current = current->next;
        if(current != NULL){
            printf("-> ");
        }
    }
    printf("\n");
}

Node* createNode(int data){
    Node* result = malloc(sizeof(Node));
    result->data = data;
    result->next = NULL;
    return result;
}

int main(){
    Node* head = NULL;
    Node* tmp;

    int n, d;
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        scanf("%d", &d);
        tmp = createNode(d);
        tmp->next = head;
        head = tmp;
    }
    printList(head);
    return 0;
}

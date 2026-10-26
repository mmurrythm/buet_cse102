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

Node* insertNode(Node** head, Node* insertedNode){
    insertedNode->next = *head;
    *head = insertedNode;
    return insertedNode;
}

Node* findNode(Node* head, int data){
    Node* tmp = head;
    while(tmp != NULL){
        if(tmp->data == data) return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

Node* deleteNode(Node** head, int data){
    Node* tmp = *head;
    Node* prev = NULL;

    while(tmp != NULL){
        if(tmp->data == data){
            if(prev == NULL){
                *head = tmp->next;
            } else {
                prev->next = tmp->next;
            }
            free(tmp);
            return *head;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    return *head;
}

int main(){
    Node* head = NULL;
    Node* tmp;

    int n, d;
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        scanf("%d", &d);
        tmp = createNode(d);
        insertNode(&head, tmp);
    }

    printList(head);

    scanf("%d", &d);
    tmp = findNode(head, d);
    if(tmp != NULL){
        printf("Found: %d\n", tmp->data);
    } else {
        printf("Not found: %d\n", d);
    }

    scanf("%d", &d);
    tmp = deleteNode(&head, d);
    printList(tmp);
    
    return 0;
}

/*
    tmp->next = head;
    head = tmp;

    n[0] = malloc(sizeof(Node));
    n[1] = malloc(sizeof(Node));
    n[2] = malloc(sizeof(Node));
    n[3] = malloc(sizeof(Node));
    n[4] = malloc(sizeof(Node));

    n[0]->data = 10;
    n[1]->data = 45;
    n[2]->data = 8;
    n[3]->data = 32;


    //link them up
    head = n[0];
    n[0]->next = n[1];
    n[1]->next = n[2];
    n[2]->next = n[3];
    n[3]->next = NULL;// so we know when to stop traversing the list
    // if we've used &n[0]; the it would create a circular list with no ending;
    n[4]->data = 13;
    n[4]->next = n[1]; // insert n4 between n[0] and n[1]
    n[0]->next = n[4];

    head = head->next; // move head to n[1] so we can print the list starting from n[1]
*/

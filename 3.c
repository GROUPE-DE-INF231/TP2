#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    struct Node *next;
} Node;


Node* createNode(int value) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if (!newNode) {
        printf("Erreur d'allocation memoire\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}


void insertSorted(Node **head, int value) {
    Node* newNode = createNode(value);

    
    if (*head == NULL || (*head)->data >= value) {
        newNode->next = *head;
        *head = newNode;
    } else {
        Node* temp = *head;
        
        while (temp->next != NULL && temp->next->data < value) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void displayList(Node *head) {
    Node* temp = head;
    printf("Liste triee : ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    Node *head = NULL;
    int n, value;

    printf("Combien d'entiers voulez-vous saisir ? ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Entier %d : ", i + 1);
        scanf("%d", &value);
        insertSorted(&head, value);  
    }

    displayList(head);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* head = NULL;
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

void insertTail(int value) {
    Node* newNode = createNode(value);

    if (head == NULL) {
        head = newNode;
        newNode->next = head;
    } else {
        Node* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = head;
    }
}

void insertHead(int value) {
    Node* newNode = createNode(value);

    if (head == NULL) {
        head = newNode;
        newNode->next = head;
    } else {
        Node* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        newNode->next = head;
        temp->next = newNode;
        head = newNode;
    }
}

void displayList() {
    if (head == NULL) {
        printf("Liste vide\n");
        return;
    }

    Node* temp = head;
    printf("Liste circulaire : ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

int main() {
    int n, i, val, choix;

    printf("Combien de valeurs voulez-vous dans la liste initiale ? ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Entrez la valeur %d : ", i + 1);
        scanf("%d", &val);
        insertTail(val);
    }

    printf("\nListe initiale :\n");
    displayList();

    do {
        printf("\n=== MENU ===\n");
        printf("1. Insertion en tete\n");
        printf("2. Insertion en queue\n");
        printf("3. Afficher la liste\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Entrez la valeur a inserer en tete : ");
                scanf("%d", &val);
                insertHead(val);
                break;

            case 2:
                printf("Entrez la valeur a inserer en queue : ");
                scanf("%d", &val);
                insertTail(val);
                break;

            case 3:
                displayList();
                break;

            case 0:
                printf("Fin du programme.\n");
                break;

            default:
                printf("Choix invalide !\n");
        }
    } while (choix != 0);

    return 0;
}

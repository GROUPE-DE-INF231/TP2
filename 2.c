#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertSorted(struct Node** head, int data) {
    struct Node* newNode = createNode(data);

    if (*head == NULL || (*head)->data >= data) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    struct Node* current = *head;
    while (current->next != NULL && current->next->data < data) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

void printList(struct Node* head) {
    if (head == NULL) {
        printf("La liste est vide.\n");
        return;
    }
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void freeList(struct Node* head) {
    struct Node* tmp;
    while (head) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int readYesNo() {
    int c;
    while ((c = getchar()) != EOF) {
        if (c == '\n' || c == ' ' || c == '\t' || c == '\r') continue;
        c = toupper(c);
        int d;
        while ((d = getchar()) != EOF && d != '\n') {}
        return (c == 'O' || c == 'Y');
    }
    return 0;
}

int main(void) {
    struct Node* head = NULL;
    int n = 0;
    int valeur;

    printf("Programme : Insertion dans une liste simplement chaînée triée\n");

    printf("Combien de valeurs initiales voulez-vous insérer ? ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Entrée invalide. Fin du programme.\n");
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        printf("Entrez la valeur %d : ", i + 1);
        if (scanf("%d", &valeur) != 1) {
            printf("Entrée invalide. Arrêt de la saisie initiale.\n");
            int ch;
            while ((ch = getchar()) != EOF && ch != '\n') {}
            break;
        }
        insertSorted(&head, valeur);
    }

    int ch;
    while ((ch = getchar()) != EOF && ch != '\n') {}

    printf("\nListe triée initiale :\n");
    printList(head);

    for (;;) {
        printf("\nVoulez-vous insérer une nouvelle valeur ? (O/N) : ");
        int yes = readYesNo();
        if (!yes) break;

        printf("Entrez la valeur à insérer : ");
        if (scanf("%d", &valeur) != 1) {
            printf("Entrée invalide. Annulation de l'insertion.\n");
            while ((ch = getchar()) != EOF && ch != '\n') {}
            continue;
        }
        while ((ch = getchar()) != EOF && ch != '\n') {}

        insertSorted(&head, valeur);
        printf("Valeur insérée. Liste actuelle :\n");
        printList(head);
    }

    printf("\nFin du programme. Mémoire libérée.\n");
    freeList(head);
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    int data;
    struct node*next;
}node;
// Création d'un nouveau noeud
node*createnode(int value){
    node*newnode=(node*)malloc(sizeof(node));
    if(newnode==NULL){
        printf("Erreur d'allocation de mémoire\n");
        exit(1);
    }
    newnode->data=value;
    newnode->next=NULL;
    return newnode;
}
//Ajouter l'élément en fin de liste
void add(node**head, int value){
    node*newnode=createnode(value);
    if(*head==NULL){
        *head=newnode;
    }else{
        node*temp=*head;
        while(temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=newnode;
    }
}
//Affiche la liste
void affiche(node*head){
    if(head==NULL){
        printf("La liste est vide \n");
        return;
    }
    node*temp=head;
    printf("Liste :");
    while(temp!=NULL){
        printf("%d ->", temp->data);
        temp=temp->next;
    }
    printf("NULL\n");
}
//Supprimer toutes les occurences d'une valeur
void del(node **head, int value){
    node*temp;
    //Supprimer au debut de la liste
    while(*head!=NULL && (*head)->data==value){
        temp=*head;
        *head=(*head)->next;
        free(temp);
    }
    //Dans le reste de la liste
    node*current=*head;
    while(current!=NULL && current->next!=NULL){
        if(current->next->data==value){
            temp=current->next;
            current->next=current->next->next;
            free(temp);
        }else{
            current=current->next;
        }
    }
}
//Liberer la mémoire
void freeL(node*head){
    node*temp;
    while(head!=NULL){
        temp=head;
        head=head->next;
        free(temp);
    }
}
//Programme main
int main(){
    node*head=NULL;
    int n,value,element;
    printf("combien de nombre voulez-vous ajouter ?");
    scanf("%d",&n);
    //Lecture des élément de la liste
    for(int i=0; i<n;i++){
        printf("Entrez l'élément %d :",i+1);
        scanf("%d",&value);
        add(&head, value);
    }
    printf("\nListe initiale :\n");
    affiche(head);
    //Lire l'élément à supprimer
    printf("\nEntrez la valeur à supprimer :");
    scanf("%d",&element);
    del(&head, element);
    printf("\nListe après la suppression des occurences de %d\n",element);
    affiche(head);
    //Libérer la mémoire
    freeL(head);
    return 0;
}
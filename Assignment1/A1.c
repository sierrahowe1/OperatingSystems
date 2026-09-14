#include <stdio.h>
#include <stdlib.h> //For malloc and free

typedef struct _node
{
    struct _node *next_elem; // A pointer to another node
    char *data;              // A pointer to the first character of a string
} Node;                      // giving it a name

Node *create_node(char *data)
{
    Node *new_node = malloc(sizeof(Node)); // Allocate memory for a new node
    if (new_node == NULL)
    { // malloc returns NULL if memory allocation fails
        fprintf(stderr, "Memmory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    new_node->data = data;      // Assign the data to the new node
    new_node->next_elem = NULL; // Initialize the next_elem pointer to NULL
    return new_node;            // Return the pointer to the new node so that it can be used in the calling function
}

void add(Node **head, char *data)
{
    Node *new_node = create_node(data); // Create a new node with the given data
    if (*head == NULL)
    {
        *head = new_node;           // If the list is empty, set the new node to be the head
        new_node->next_elem = NULL; // Make the new node point to NULL
    }
}

void delete(Node **head, char *data)
{
    if (*head == NULL)
    {
        return; // If the list is empty, do nothing
    }
    if (strcmp((*head)->data, data) == 0)
    {
        Node *p = (*head)->next_elem; // Storing the next element of the head node in a temp variable
        free(*head);
        *head = p; // Upadting the variable in head to equal the next element of the deleted head node
    }

    Node *p = *head;
    Node *q = (*head)->next_elem;
    while (q != NULL && strcmp(q->data, data) != 0)
    { // if the data in the current node is not equal to the desired data, move to the next node
        p = q;
        q = q->next_elem;
    }
    if (q != NULL)
    { // Once the desired data is found, free the memory of the node and update the next element
        p->next_elem = q->next_elem;
        free(q);
    }
}

void order(Node *) {}

int hasItem(Node *, char *) {}

void findAndReplace(Node *, char *, char *) {}

void print(Node *) {}

int stop(Node **) {}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        fprintf(stderr, "Memory alloc ation failed!\n");
        exit(EXIT_FAILURE);
    }

    new_node->data = malloc(strlen(data) + 1); // Assign the data to the new node
    if (new_node->data == NULL)
    {
        fprintf(stderr, "Memory allocation failed for data!\n");
        free(new_node); // Free the previously allocated node memory before exiting
        exit(EXIT_FAILURE);
    }
    strcpy(new_node->data, data); // Copy the string data into the new node's data field
    new_node->next_elem = NULL;   // Initialize the next_elem pointer to NULL
    return new_node;              // Return the pointer to the new node so that it can be used in the calling function
}

void add(Node **head, char *data)
{
    Node *new_node = create_node(data); // Create a new node with the given data
    Node *current = *head;
    if (*head == NULL)
    {
        *head = new_node;           // If the list is empty, set the new node to be the head
        new_node->next_elem = NULL; // Make the new node point to NULL
    }
    else if (current->next_elem == NULL)
    {
        current->next_elem = new_node;
    }
    else
    {
        while (current->next_elem != NULL)
        {
            current = current->next_elem;
        }
        current->next_elem = new_node;
    }
}

void delete(Node **head, char *data) // first instance
{
    if (*head == NULL)
    {
        return;
    }

    if (strcmp((*head)->data, data) == 0)
    {
        Node *p = (*head)->next_elem; // Storing the next element of the head node in a temp variable
        free((*head)->data);
        free(*head);
        *head = p; // Updating the variable in head to equal the next element of the deleted head node
        return;
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
        free(q->data);
        free(q);
        return;
    }
}

int length(Node *head)
{
    int length = 0;
    Node *current = head;
    while (current != NULL)
    {
        length++;
        current = current->next_elem;
    }
    return length;
}

void order(Node *head)
{
    if (head == NULL || head->next_elem == NULL)
    {
        return; // If the list is empty or only has one element, it is already ordered
    }

    for (int i = 0; i < length(head) - 1; ++i)
    {
        Node *current = head;
        ; // Resetting current to the front of the list after each iteration so all element are compared
        while (current != NULL && current->next_elem != NULL)
        {
            if (strcmp(current->data, current->next_elem->data) > 0)
            {
                char *temp = current->data;
                current->data = current->next_elem->data;
                current->next_elem->data = temp;
            }
            current = current->next_elem;
        }
    }
}

int hasItem(Node *head, char *data)
{
    Node *current = head;
    while (current != NULL)
    {
        if (strcmp(current->data, data) == 0)
        {
            return 1; // Item was found
        }
        else
        {
            current = current->next_elem; // Move to the next node if the current node's data does not match the one we are looking for
        }
    }
    return 0; // Item was not found
}

void findAndReplace(Node *head, char *old_data, char *new_data)
{
    Node *current = head;
    while (current != NULL)
    {
        if (strcmp(current->data, old_data) == 0)
        {
            char *temp = current->data;
            char *new_data_temp = malloc(strlen(new_data) + 1); // Allocate memory for the new data

            if (new_data_temp == NULL)
            {
                free(temp);
                fprintf(stderr, "Memory allocation failed for data!\n");
                exit(EXIT_FAILURE);
            }
            strcpy(new_data_temp, new_data);
            free(temp);
            current->data = new_data_temp;
            break;
        }
        current = current->next_elem;
    }
}

void print(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        printf("%s \n", current->data);
        current = current->next_elem;
    }
}

int stop(Node **head)
{
    while (*head != NULL)
    {
        if ((*head)->next_elem == NULL)
        { // If the head is the only node in the list we can just free it and set the head to NULL
            free((*head)->data);
            free(*head);
            *head = NULL;
        }
        else
        {                               // Otherwise
            Node *p = *head;            // we set a temporary variable to the head node
            *head = (*head)->next_elem; // We update the head to point to the next node in the list
            free(p->data);
            free(p); // And we free the memory of the node that stores the data of the previous head node
        }
    }
    return 0;
}

int main()
{
    Node *head = NULL;
    char data[100];
    char input[2];
    char new_data[100];
    int looping = 1;

    while (looping)
    {
        int result = scanf("%1s", input); // checking if the input is valid (should be 1 character)
        if (result != 1)
        {
            fprintf(stderr, "No input has been given.\n");
            break;
        }

        if (input[0] == 'a')
        {
            scanf("%99s", data); // reading the string input up to 99 characters
            add(&head, data);    // adding the string to the linked list using the add function
        }
        if (input[0] == 'd')
        {
            scanf("%99s", data);
            delete(&head, data);
        }
        if (input[0] == 'p')
        {
            print(head);
        }
        if (input[0] == 's')
        {
            looping = stop(&head);
        }
        if (input[0] == 'f')
        {
            scanf("%99s", data);
            scanf("%99s", new_data);
            findAndReplace(head, data, new_data);
        }
        if (input[0] == 'h')
        {
            scanf("%99s", data);
            printf("%d\n", hasItem(head, data));
        }
        if (input[0] == 'o')
        {
            order(head);
        }
    }
}

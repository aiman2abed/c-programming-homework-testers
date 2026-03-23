#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node* next;
}Node;

void print_list(Node const* head);

Node* allocate_node(int value, Node* next);

Node* push(int value, Node* head);

void free_list(Node* head);

Node* EvenOdd(Node* head);

int main()
{
    Node* head = NULL;

    int number_imput = 0;

    printf("Original Linked list:\n");
    scanf("%d", &number_imput);
    while (number_imput >= 0)
    {
        head = push(number_imput, head);
        scanf("%d", &number_imput);
    }
    printf("Input phase done \n");
    head = EvenOdd(head);

    printf("Modified Linked list:\n");
    print_list(head);
    free_list(head);


    return 0;
}


void print_list(Node const* head)
{
    for (; head; head = head->next)
        printf("%d ", head->value);
    printf("\n");
}


Node* push(int value, Node* head)
{
    return allocate_node(value, head);
}

void free_list(Node* head)
{
    while (head) {
        Node* old = head;
        head = head->next;
        free(old);
    }
}

Node* allocate_node(int value, Node* next)
{
    Node* new_node = malloc(sizeof(Node));
    assert(new_node != NULL);
    new_node->value = value;
    new_node->next  = next;
    return new_node;
}

Node* EvenOdd(Node* head)
{
    Node *even_head = NULL, *even_tail = NULL;
    Node *odd_head  = NULL, *odd_tail  = NULL;
    Node *cur = head;

    while (cur) {
        Node* nxt = cur->next;
        cur->next = NULL;          // detach

        if (cur->value % 2 == 0) {
            // append to even list
            if (!even_head) {
                even_head = even_tail = cur;
            } else {
                even_tail->next = cur;
                even_tail = cur;
            }
        } else {
            // append to odd list
            if (!odd_head) {
                odd_head = odd_tail = cur;
            } else {
                odd_tail->next = cur;
                odd_tail = cur;
            }
        }

        cur = nxt;
    }

    // stitch even list to odd list (or just return odd if no evens)
    if (even_tail) {
        even_tail->next = odd_head;
        return even_head;
    } else {
        return odd_head;
    }
}

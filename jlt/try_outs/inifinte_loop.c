#include "common.h"

struct node;
typedef struct node
{
    struct node     *next;
    uint32_t        id;
} node_t;

typedef struct list
{
    node_t *first;
    node_t *last;
} list_t;

void add_node(list_t *list, node_t *node)
{
    node->next = NULL;
    if (list->first == NULL)
    {
        list->first = node;
    }
    else
    {
        list->last->next = node;
    }

    list->last = node;
}

void add_node_2(list_t *list, node_t *node)
{
    if (list->first == NULL)
    {
        list->first = node;
        list->last  = node;
    }
    else
    {
        list->last->next = node;
        list->last       = node;
    }
}

node_t *pop_node(list_t *list)
{
    node_t *result = NULL;
    if (list->first != NULL)
    {
        result      = list->first;
        list->first = result->next;
    }

    if (list->first == NULL)
    {
        list->last = NULL;
    }
    return result;
}

void free_list(list_t *list)
{
    node_t *next = list->first;
    while (next != NULL)
    {
        node_t *temp = next;
        next = next->next;
        free(temp);
    }
}

void main()
{
    list_t list_1 = {.first = NULL, .last = NULL};
    list_t list_2 = {.first = NULL, .last = NULL};

    for (uint32_t i = 0; i < 5; i++)
    {
        node_t *node = malloc(sizeof(node_t));
        node->id = i;
        add_node(&list_1, node);
    }

    node_t *process_node = pop_node(&list_1);
    add_node_2(&list_2, process_node);

    uint32_t counter = 0;
    node_t *delayed_node, *next_node;
    delayed_node = list_2.first;
    while (delayed_node != NULL)
    {
        counter++;
        printf("iter %d: delayed_node: 0x%08x id - %d, next_node: 0x%08x\n", counter, (uint32_t)delayed_node, delayed_node->id, (uint32_t)next_node);
        next_node = delayed_node->next;
        add_node(&list_1, delayed_node);
        delayed_node = next_node;
    }

    free_list(&list_1);
}

#include "common.h"

struct my_node;
typedef struct my_node my_node_t;

struct my_node
{
    my_node_t *next;

    uint32_t data;
};

my_node_t *my_list = NULL;

void add_node(uint32_t data)
{
    my_node_t *node = malloc(sizeof(my_node_t));

    node->data = data;
    node->next = my_list;
    my_list = node;
}

void del_node(uint32_t data)
{
    my_node_t *node = my_list;
    my_node_t *prev = NULL;
    while (node)
    {
        if (node->data == data)
        {
            if (prev)
            {
                prev->next = node->next;
            }
            else
            {
                my_list = node->next;
            }
            free(node);
        }

        prev = node;
        node = node->next;
    }
}

void print_list(my_node_t *list)
{
    while (list)
    {
        printf("node 0x%08x: %d\n", (uint32_t)list, list->data);
        list = list->next;
    }
}

int main()
{
    add_node(10);
    add_node(128);
    add_node(1024);
    add_node(500);

    printf("my_list 0x%08x\n", (uint32_t)my_list);

    print_list(my_list);

    printf("my_list 0x%08x\n", (uint32_t)my_list);

    return 0;
}

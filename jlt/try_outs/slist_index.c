#include "common.h"

typedef struct node_s node_t;

struct node_s
{
    node_t *next;

    uint32_t  index;
    uint32_t  data;
};

typedef struct list_s
{
    node_t *head;
    node_t *tail;
    uint32_t  count;
} list_t;

list_t my_list = {0};

node_t *find_index_in_list(uint32_t index)
{
    for (node_t *entry = my_list.head; entry != NULL; entry = entry->next)
    {
        if (entry->index == index)
        {
            return entry;
        }
    }

    return NULL;
}

uint32_t get_unused_index()
{
    for (uint32_t i = 0; i < my_list.count; i++)
    {
        if (find_index_in_list(i) == NULL)
        {
            return i;
        }
    }

    return my_list.count;
}

node_t *find_in_list(uint32_t data)
{
    for (node_t *entry = my_list.head; entry != NULL; entry = entry->next)
    {
        if (entry->data == data)
        {
            return entry;
        }
    }

    return NULL;
}

void add_to_list(uint32_t data)
{
    node_t *node = malloc(sizeof(node_t));

    node->data = data;
    node->index = get_unused_index();

    node->next = my_list.head;
    my_list.head = node;
    my_list.count++;

    printf("%d added\n", data);
}

void del_from_list(uint32_t data)
{
    node_t *entry = NULL;
    node_t *prev = NULL;
    for (entry = my_list.head; entry != NULL; prev = entry, entry = entry->next)
    {
        if (entry->data == data)
        {
            if (prev)
            {
                prev->next = entry->next;
            }
            else
            {
                my_list.head = entry->next;
            }
            free(entry);
            my_list.count--;
            break;
        }
    }
}

void print_list()
{
    printf("\n");
    for (node_t *entry = my_list.head; entry != NULL; entry = entry->next)
    {
        printf("%d: %d\n", entry->index, entry->data);
    }
    printf("\n");
}

int main()
{
    uint32_t new_num = 0;
    bool user_continue = true;
    int in_char;

    while (user_continue)
    {
add:
        printf("Add a number to list: ");
        scanf("%u", &new_num);
        add_to_list(new_num);
        print_list();
        goto ask;

del:
        printf("Number to delete: ");
        scanf("%u", &new_num);
        del_from_list(new_num);
        print_list();

ask:
        printf("Add/Delete/Exit [a/d/^]: ");
        while ((in_char = getchar()) == '\n' || in_char == EOF){}
        if (in_char == 'a' || in_char == 'A')
        {
            goto add;
        }
        else if (in_char == 'd' || in_char == 'D')
        {
            goto del;
        }
        else
        {
            user_continue = false;
            printf("Exiting\n");
        }
    }

    return 0;
}

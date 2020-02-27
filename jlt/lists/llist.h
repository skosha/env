#ifndef __LLIST_H__
#define __LLIST_H__

typedef (*llist_free_fn_t)(void *ptr);

#define llist_next_var(type)        \
        type *next;

#define llist_type_declare(list_type, node_type)    \
    list_type {                 \
        node_type   *head;      \
        uint32_t    count;      \
        llist_free_fn_t free;   \
    }

struct _llist_node
{
    llist_next_var(struct _llist_node);
};
llist_type_declare(struct _llist_list, struct _llist_node);

#define llist_list(list)    ((struct _llist_list *)(list))
#define llist_node(node)    ((struct _llist_node *)(node))

#define llist_init(list, free_fn)   \
    do                              \
    {                               \
        memset(list, sizeof(list)); \
        (list)->free = free_fn;     \
    } while (0)

#define llist_count(list)       ((list)->count)
#define llist_head(list)        ((list)->head)
#define llist_is_empty(list)    ((list)->head == NULL)
#define llist_next(node)        ((node)->next)

#define llist_insert_head(list, node)                           \
    do                                                          \
    {                                                           \
        typeof(node) _n = (node);                               \
        _llist_insert_head(llist_list(list), llist_node(_n));   \
    } while (0)

#define llist_insert(list, node)                                \
    do                                                          \
    {                                                           \
        typeof(node) _n = (node);                               \
        _llist_insert(llist_list(list), llist_node(_n));        \
    } while (0)

#define llist_insert_after(list, node, after)                   \
    do                                                          \
    {                                                           \
        typeof(node) _n = (node);                               \
        typeof(node) _a = (after);                              \
        _llist_insert_after(llist_list(list), llist_node(_n), llist_node(_a)); \
    } while (0)

#define llist_insert_sorted(list, node, type, member)           \
    do                                                          \
    {                                                           \
        _llist_insert_sorted(llist_list(list), llist_node(node), offsetof(type, member)
    } while (0)


#define llist_sort_list_by(list, type, member)                  \
    do                                                          \
    {                                                           \
        _llist_sort_list_by(llist_list(list), type, member)     \
    } while (0)

#define llist_for_each(list, node)                              \
    typeof(node) _n;
    for ((node) = ((list)->head), (_n) = NULL;                  \
         (node) != NULL && ((_n) = (typeof((list)->head)) llist_node(node)->next), true;
         (node) = (_n))
    do                                                          \
    {                                                           \
    } while (0)

#endif /* !__LLIST_H__ */

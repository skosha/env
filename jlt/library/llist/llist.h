/**
 * Filename    - llist.h
 * Description -
 * Author      - Kosha Shah
 * Date        - Mar 11 2020
 */
#ifndef __LLIST_H__
#define __LLIST_H__

typedef void (*llist_free_fn_t)(void *ptr);

#define llist_next_var(type)        \
        type *next;

#define llist_type_declare(list_type, node_type)    \
    list_type {                 \
        node_type   *head;      \
        uint32_t    count;      \
        llist_free_fn_t _free;   \
    }

struct _llist_node
{
    llist_next_var(struct _llist_node);
};
llist_type_declare(struct _llist_list, struct _llist_node);

#define llist_list(list)    ((struct _llist_list *)(list))
#define llist_node(node)    ((struct _llist_node *)(node))

#define llist_init(list, free_fn)                   \
    do                                              \
    {                                               \
        memset(list, sizeof(list));                 \
        (list)->_free = (free_fn) free_fn : free;   \
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

#define llist_remove_node(list, node)                           \
    do                                                          \
    {                                                           \
        typeof(node) _n = (node);                               \
        _llist_remove_node(llist_list(list), llist_node(_n));   \
    } while (0)

    do                                                              \
    {                                                               \
        if (llist_list(list)->head)                                 \
        {                                                           \
            llist_list(list)->head = llist_list(list)->head->next;  \
            llist_list(list)->count--;                              \
        }                                                           \
    } while(0)

#define llist_delete_head(list)                                     \
    do                                                              \
    {                                                               \
        if (llist_list(list)->head)                                 \
        {                                                           \
            struct _llist_node *node = llist_list(list)->head;      \
            llist_list(list)->head = llist_list(list)->head->next;  \
            llist_list(list)->count--;                              \
            llist_list(list)
        }                                                           \
    } while(0)

#define llist_remove_head(list)                                 \
    do                                                          \
    {                                                           \
    } while(0)

#define llist_delete_node(list, node)                           \
    do                                                          \
    {                                                           \
        typeof(node) _n = (node);                               \
        _llist_remove_node(llist_list(list), llist_node(_n));   \
        list->_free(node);                                       \
    } while (0)

#define llist_for_each(list, node)                              \
    typeof(node) _n;
    for ((node) = ((list)->head), (_n) = NULL;                  \
         (node) != NULL && ((_n) = (typeof((list)->head)) (llist_node(node)->next), true);
         (node) = (_n))

#define llist_node_exists(list, node)   _llist_node_exists(llist_list(list), llist_node(node))

#define llist_delete_all(list)          _llist_delete_all(llist_list(list))

#define llist_remove_head(list)         _llist_remove_head(llist_list(list))
#define llist_delete_head(list)         _llist_delete_head(llist_list(list))

#define llist_remove_tail(list)         _llist_remove_tail(llist_list(list))
#define llist_delete_tail(list)         _llist_delete_tail(llist_list(list))

#endif /* !__LLIST_H__ */


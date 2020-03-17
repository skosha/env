/**
 * Filename    - llist.c
 * Description -
 * Author      - Kosha Shah
 * Date        - Mar 11 2020
 */
#include "common.h"
#include "llist.h"

/**
 * @function: _llist_insert_head
 * <<Description>>
 *
 * @param list
 * @param node
 */
void _llist_insert_head(struct _llist_list *list, struct _llist_node *node)
{
    node->next = list->head;
    list->head = node;
    list->count++;
}

/**
 * @function: _llist_insert
 * <<Description>>
 *
 * @param list
 * @param node
 */
void _llist_insert(struct _llist_list *list, struct _llist_node *node)
{
    struct _llist_list *tail = list->head;
    if (tail == NULL)
    {
        list->head = node;
    }
    else
    {
        /* Find the tail of the list */
        for (; tail->next != NULL; tail = tail->next);
        tail->next = node;
    }
    list->count++;
}

/**
 * @function: _llist_insert_after
 * <<Description>>
 *
 * @param list
 * @param node
 * @param after
 */
void _llist_insert_after(struct _llist_list *list, struct _llist_node *node, struct _llist_node *after)
{
    node->next = after->next;
    after->next = node;
    list->count++;
}

/**
 * @function: _llist_remove_node
 * <<Description>>
 *
 * @param list
 * @param node
 */
void _llist_remove_node(struct _llist_list *list, struct _llist_node *node)
{
    struct _llist_node *n = list->head;
    struct _llist_node *p = NULL;

    if (node == n)      /* Node is the head */
    {
        list->head = list->head->next;
        list->count--;
        return;
    }

    for (; n != NULL; p = n, n = n->next)
    {
        if (n == node)
        {
            break;
        }
    }

    if (n && p)
    {
        p->next = n->next;
        list->count--;
    }
}

/**
 * @function: _llist_node_exists
 * <<Description>>
 *
 * @param list
 * @param node
 *
 * @return bool
 */
bool _llist_node_exists(struct _llist_list *list, struct _llist_node *node)
{
    for (struct _llist_node *n = list->head; n != NULL; n = n->next)
    {
        if (node == n)
        {
            return true;
        }
    }

    return false;
}

/**
 * @function: _llist_delete_all
 * <<Description>>
 *
 * @param list
 */
void _llist_delete_all(struct _llist_list *list)
{
    struct _llist_node *node;
    llist_for_each(list, node)
    {
        list->_free(node);
    }

    list->head = NULL;
    list->count = 0;
}

/**
 * @function: _llist_remove_head
 * <<Description>>
 *
 * @param list
 *
 * @return struct _llist_node*
 */
struct _llist_node* _llist_remove_head(struct _llist_list *list)
{
    struct _llist_node *r_node = NULL;
    if (list->head)
    {
        r_node = list->head;
        list->head = list->head->next;
        list->count--;
    }

    return r_node;
}

/**
 * @function: _llist_delete_head
 * <<Description>>
 *
 * @param list
 */
void _llist_delete_head(struct _llist_list *list)
{
    struct _llist_node *head = _llist_remove_head(list);
    if (head)
    {
        list->_free(head);
    }
}

/**
 * @function: _llist_remove_tail
 * <<Description>>
 *
 * @param list
 *
 * @return struct _llist_node*
 */
struct _llist_node* _llist_remove_tail(struct _llist_list *list)
{
    struct _llist_node *r_node = NULL;
    if (list->head)
    {
        struct _llist_node *tail = list->head;
        struct _llist_node *p = NULL;
        for (; tail->next != NULL; p = tail, tail = tail->next);
        r_node = tail;
        p->next = NULL;
        list->count--;
    }

    return r_node;
}

/**
 * @function: _llist_delete_tail
 * <<Description>>
 *
 * @param list
 */
void _llist_delete_tail(struct _llist_list *list)
{
    struct _llist_node *tail = _llist_remove_tail(list);
    if (tail)
    {
        list->_free(tail);
    }
}

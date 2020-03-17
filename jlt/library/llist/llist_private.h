/**
 * Filename    - llist_private.h
 * Description -
 * Author      - Kosha Shah
 * Date        - Mar 11 2020
 */
#ifndef __LLIST_PRIVATE_H__
#define __LLIST_PRIVATE_H__


/**
 * @function: _llist_insert_head
 * <<Description>>
 *
 * @param list
 * @param node
 */
void _llist_insert_head(struct _llist_list *list, struct _llist_node *node);

/**
 * @function: _llist_insert
 * <<Description>>
 *
 * @param list
 * @param node
 */
void _llist_insert(struct _llist_list *list, struct _llist_node *node);

/**
 * @function: _llist_insert_after
 * <<Description>>
 *
 * @param list
 * @param node
 * @param after
 */
void _llist_insert_after(struct _llist_list *list, struct _llist_node *node, struct _llist_node *after);

/**
 * @function: _llist_remove_node
 * <<Description>>
 *
 * @param list
 * @param node
 */
void _llist_remove_node(struct _llist_list *list, struct _llist_node *node);

/**
 * @function: _llist_node_exists
 * <<Description>>
 *
 * @param list
 * @param node
 *
 * @return bool
 */
bool _llist_node_exists(struct _llist_list *list, struct _llist_node *node);

/**
 * @function: _llist_delete_all
 * <<Description>>
 *
 * @param list
 */
void _llist_delete_all(struct _llist_list *list);

/**
 * @function: _llist_remove_head
 * <<Description>>
 *
 * @param list
 *
 * @return struct _llist_node*
 */
struct _llist_node* _llist_remove_head(struct _llist_list *list);

/**
 * @function: _llist_delete_head
 * <<Description>>
 *
 * @param list
 */
void _llist_delete_head(struct _llist_list *list);

/**
 * @function: _llist_remove_tail
 * <<Description>>
 *
 * @param list
 *
 * @return struct _llist_node*
 */
struct _llist_node* _llist_remove_tail(struct _llist_list *list);

/**
 * @function: _llist_delete_tail
 * <<Description>>
 *
 * @param list
 */
void _llist_delete_tail(struct _llist_list *list);

#endif /* !__LLIST_PRIVATE_H__ */

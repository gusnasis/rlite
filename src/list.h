#ifndef _LIST_H
#define _LIST_H

struct rl_list;
struct rl_list_node;

typedef struct {
	int element_size;
	long (*serialize_length)(struct rl_list *list);
	long (*serialize)(struct rl_list *list, struct rl_list_node *node, unsigned char **data, long *data_size);
	long (*deserialize)(struct rl_list *list, unsigned char *data, struct rl_list_node **node);
	int (*cmp)(void *v1, void *v2);
	void (*formatter)(void *v, char **str, int *size);
} rl_list_type;

rl_list_type long_list;

void init_long_list();

typedef struct rl_list_node {
	long size;
	long left;
	long right;
	void **elements;
} rl_list_node;

typedef struct rl_accessor {
	void *context;
	long (*commit)(struct rl_list *list);
	long (*discard)(struct rl_list *list);
	struct rl_list_node *(*select)(struct rl_list *list, long number);
	long (*update)(struct rl_list *list, long *number, struct rl_list_node *node);
	long (*insert)(struct rl_list *list, long *number, struct rl_list_node *node);
	long (*remove)(struct rl_list *list, struct rl_list_node *node);
	long (*list)(struct rl_list *list, rl_list_node *** nodes, long *size);
} rl_accessor;

typedef struct rl_list {
	long max_node_size; // maximum number of elements in a node
	long size;
	rl_list_type *type;
	long left;
	long right;
	rl_accessor *accessor;
} rl_list;

rl_list *rl_list_create(rl_list_type *type, long max_size, rl_accessor *accessor);
int rl_list_destroy(rl_list *list);
long rl_list_node_destroy(rl_list *list, rl_list_node *node);
int rl_list_add_element(rl_list *list, void *element, long position);
int rl_list_remove_element(rl_list *list, long position);
int rl_list_find_element(rl_list *list, void *element, long *position);
void rl_print_list(rl_list *list);
int rl_list_is_balanced(rl_list *list);
void rl_flatten_list(rl_list *list, void *** elements);

#endif

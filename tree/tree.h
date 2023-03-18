#ifndef TREE_
#define TREE_

#include<stdlib.h>
#include"../linkedlist/linkedlist.h"

struct tree_node{
    struct tree_node* parent;
    void* data;
    struct LinkedList* children;
};

struct tree{
    struct tree_node* root;
    int number_of_nodes;
};

struct tree_node* add_child(struct tree_node* node, void* data);
struct tree_node* remove_node(struct tree_node* node);
struct tree* make_tree();
struct tree_node* get_root_node(struct tree_node* node);
void prune_node(struct tree_node* node);
void purge_node(struct tree_node* node);
void graft(struct tree_node* nod, struct tree_node* parent);
struct tree_node* cdsc_tree_naive_lca(struct tree_node* nod1, struct tree_node* nod2);
int get_depth(struct tree_node *nod);
#endif

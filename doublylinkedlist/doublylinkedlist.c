#include "doublylinkedlist.h"

// Create and init double linked list
struct cdsc_doublylinkedlist *cdsc_doublylinkedlist_make_dll() {
    struct cdsc_doublylinkedlist *ret =
	malloc(sizeof(struct cdsc_doublylinkedlist));
    ret->size = 0;
    ret->head = NULL;
    ret->tail = NULL;
    return ret;
}


// Zeroes a cdsc_doublylinkedlist, mainly used internally.
void cdsc_doublylinkedlist_zero(struct cdsc_doublylinkedlist *ll) {
    ll->head = NULL;
    ll->tail = NULL;
    ll->size = 0;

}

// Add new node at the head, replacing it.
void cdsc_doublylinkedlist_inserthead(struct cdsc_doublylinkedlist *list,
				      void *data) {
    struct cdsc_doublylinkedlist_node *ins =
	malloc(sizeof(struct cdsc_doublylinkedlist_node));
    ins->data = data;
    ins->previous = NULL;
    if (list->size == 0) {
	ins->next = NULL;

	list->tail = ins;
    } else {
	ins->next = list->head;
	list->head->previous = ins;
    }
    list->head = ins;
    list->size++;
}

// Add new node at the tail, replacing it.
void cdsc_doublylinkedlist_inserttail(struct cdsc_doublylinkedlist *list,
				      void *data) {
    struct cdsc_doublylinkedlist_node *ins =
	malloc(sizeof(struct cdsc_doublylinkedlist_node));
    ins->data = data;
    ins->next = NULL;
    if (list->size == 0) {
	ins->previous = NULL;
	list->head = ins;

    } else {
	ins->previous = list->tail;
	list->tail->next = ins;
    }
    list->tail = ins;
    list->size++;


}

// Remove the list's tail replacing it by the node before it
void *cdsc_doublylinkedlist_poptail(struct cdsc_doublylinkedlist *list) {
    struct cdsc_doublylinkedlist_node *newtail = list->tail->previous;
    void *ret = list->tail->data;
    //We need to free the node struct that was allocated in inserttail or inserthead
    free(list->tail);
    if (list->size > 1) {
	newtail->next = NULL;
	list->tail = newtail;
	list->size--;
    } else {
	cdsc_doublylinkedlist_zero(list);
    }
    return ret;

}

// Remove the list's head replacing it with the next node
void *cdsc_doublylinkedlist_pophead(struct cdsc_doublylinkedlist *list) {
    struct cdsc_doublylinkedlist_node *newhead = list->head->next;
    void *ret = list->head->data;
    //We need to free the node struct that was allocated in inserttail or inserthead
    free(list->head);

    if (list->size > 1) {
	newhead->previous = NULL;
	list->head = newhead;
	list->size--;

    } else {
	cdsc_doublylinkedlist_zero(list);
    }
    return ret;

}

// Get data by index starting at the heazd
void *cdsc_doublylinkedlist_getindexfromhead(struct cdsc_doublylinkedlist
					     *list, int index) {

    int i;
    struct cdsc_doublylinkedlist_node *cur = list->head;

    for (i = 0; i < index; i++) {
	cur = cur->next;
	if (cur == NULL) {
	    return NULL;
	}
    }

    return cur->data;
}

// Get data by index starting at the tail
void *cdsc_doublylinkedlist_getindexfromtail(struct cdsc_doublylinkedlist
					     *list, int index) {
    int i;
    struct cdsc_doublylinkedlist_node *cur = list->tail;

    for (i = 0; i < index; i++) {
	cur = cur->previous;
	if (cur == NULL) {
	    return NULL;
	}
    }

    return cur->data;
}


// Completely wipe a doubly linked list
void cdsc_doublylinkedlist_nuke(struct cdsc_doublylinkedlist *list) {
    struct cdsc_doublylinkedlist_node *cur;
    cur = list->head;
    if (list->size == 0) {
	return NULL;
    }
    if (list->head == list->tail) {
	free(list->head);

    } else {
	while (1) {
	    struct cdsc_doublylinkedlist_node *nxt = cur->next;
	    if (cur == list->tail) {
		free(cur);
		break;
	    } else {
		free(cur);
		cur = nxt;
	    }

	}

    }
    cdsc_doublylinkedlist_zero(list);
}

// Sets the data of a DoublyLinkedList's certain index, starting from the head.
void cdsc_doublylinkedlist_setdata(struct cdsc_doublylinkedlist *list,
				   void *data, int index) {
    int i;
    struct cdsc_doublylinkedlist_node *cur = list->head;
    for (i = 0; i < index; i++) {
	cur = cur->next;
	if (cur == NULL) {
	    return NULL;
	}
    }
    cur->data = data;
}

void cdsc_doublylinkedlist_reverse(struct cdsc_doublylinkedlist *list) {
    if (list->size < 2) {
	return NULL;
    }
    struct cdsc_doublylinkedlist_node *prev = NULL;
    struct cdsc_doublylinkedlist_node *formerhead = list->head;
    list->tail = formerhead;
    struct cdsc_doublylinkedlist_node *current = list->head;
    struct cdsc_doublylinkedlist_node *next;

    while (current != NULL) {
	next = current->next;
	current->next = prev;
	prev = current;
	current = next;
    }
    list->head = prev;
}
void cdsc_doublylinkedlist_appendnode(struct cdsc_doublylinkedlist *list,
				      struct cdsc_doublylinkedlist_node
				      *node) {
    if (list->size == 0) {
	list->head = node;
	list->tail = node;
    } else {
	list->tail->next = node;
	list->tail = node;
    }

}

void cdsc_doublylinkedlist_merge(struct cdsc_doublylinkedlist *list1,
				 struct cdsc_doublylinkedlist *list2) {
    list1->tail->next = list2->head;
    list2->head->previous = list1->tail;
    list1->size += list2->size;
}

bool cdsc_doublylinkedlist_contains(struct cdsc_doublylinkedlist *list,
				    void *data) {
    int i;
    struct cdsc_doublylinkedlist_node *cur = list->head;
    for (i = 0; i < list->size; i++) {
	if (cur->data == data) {
	    return true;
	} else {;
	    cur = cur->next;
	}

    }
    return false;
}

struct cdsc_doublylinkedlist_node *cdsc_doublylinkedlist_find(struct
							      cdsc_doublylinkedlist
							      *list,
							      void *key) {
    if (list->head == NULL) {
	return NULL;
    }
    struct cdsc_doublylinkedlist_node *current = list->head;
    while (current->data != key) {
	if (current->next == NULL) {
	    return NULL;
	} else {
	    current = current->next;
	}
    }
    return current;
}

int cdsc_doublylinkedlist_findindex(struct cdsc_doublylinkedlist *list,
				    void *key) {
    if (list->head == NULL) {
	return NULL;
    }
    struct cdsc_doublylinkedlist_node *current = list->head;
    int i = 0;
    while (current->data != key) {
	if (current->next == NULL) {
	    return NULL;
	} else {
	    current = current->next;
	    i++;
	}
    }
    return i;
}

// Run a function for each member of a doublylinkedlist.
void cdsc_doublylinkedlist_foreach(struct cdsc_doublylinkedlist *list,
				   void (*action)(), void *param) {
    struct cdsc_doublylinkedlist_node *cur = list->head;
    while (cur != NULL) {
	action(cur, param);
	cur = cur->next;
    }
}

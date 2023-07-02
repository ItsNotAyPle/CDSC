#include<stdio.h>
#include<stdlib.h>
#include"unionfind.h"

int cdsc_union_find_find(union_find *set, int a);
void cdsc_union_find_uni(union_find *set, int a, int b);
bool cdsc_union_find_same(union_find *set, int a, int b);

// initialize new set with parent list and element ranking for merging sets
union_find *cdsc_union_find_init(int a) {
	union_find *set = (union_find*)malloc(sizeof(union_find));

	set->par = (int*)malloc((a+1) * sizeof(int));
	set->rank = (int*)malloc((a+1) * sizeof(int));

	for(int i = 0; i<= a; i++) {
		set->par[i] = i;
		set->rank[i] = 0;
	}

	return set;
}

// destroy the entire set after freeing both lists
void nuke(union_find *set) {
	if(set != NULL) {
		free(set->par);
		free(set->rank);
		free(set);
	}
}

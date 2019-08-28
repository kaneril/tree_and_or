#ifndef TREE_AND_OR_H_
#define TREE_AND_OR_H_
#include "stdafx.h"

typedef struct tree
{
	char name[20];
	int level;
	int maxWeight;
	int minWeight;
	int elemWeight;
	bool status;
	tree *ptrFath;
	tree *ptrBro;
	tree *ptrSon;
} Tree;

int init_tree(FILE *, Tree *&);
void calc_min_maxWeight(Tree *);
void calc_permissWeight(Tree *,int);
void print_tree(FILE *, Tree *);

#endif
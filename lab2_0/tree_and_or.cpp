#include "tree_and_or.h"

int init_tree(FILE *input, Tree *&root)
{
	int weight=0;
	int tempLevel = 0;
	Tree *temp0;//fath
	Tree *temp1=NULL;//son
	Tree *temp2=NULL;//bro
	char str[20];
	while (!feof(input))
	{
		str[0] = '\0';
		fgets(str, 20, input);
		if (strlen(str) == 0)
		{
			continue;
		}
		int level = 0;
		temp0 = (Tree*)malloc(sizeof(Tree));
		temp0->level = 0;
		while (str[level] == '.')
		{
			level++;
			temp0->level++;
		}
		
		int j = level;
		int i = 0;
		while (str[j]!=' ')
		{
			temp0->name[i] = str[j];
			i++;
			j++;
		}
		temp0->name[i] = '\0';
		temp0->elemWeight = atoi(str+j);
		temp0->maxWeight=0;
		temp0->minWeight=100000;
		temp0->status = TRUE;
		temp0->ptrBro = NULL;
		temp0->ptrSon = NULL;
		if (level == 0)
		{
			root = temp0;
			temp1 = root;
			continue;
		}
		if (level > tempLevel)
		{
			temp1->ptrSon = temp0;
			temp0->ptrFath = temp1;
		}
		else if (level == tempLevel)
		{
			temp1->ptrBro = temp0;
			temp0->ptrFath = temp1->ptrFath;
		}
		else        
		{
			temp2 = temp1;
			for (int i = 0; i < tempLevel - level; i++)
			{
				temp2 = temp2->ptrFath;
			}
			temp0->ptrFath = temp2->ptrFath;   
			temp2->ptrBro = temp0;
		}
		tempLevel = level;      
		temp1 = temp0;
	}
	if (temp1->name == temp1->ptrBro->name)
	{
		temp1->ptrBro = NULL;
	}
	return 0;
}

void calc_min_maxWeight(Tree *head)
{
	if (head)
	{
		calc_min_maxWeight(head->ptrSon);
		calc_min_maxWeight(head->ptrBro);
		if (head->elemWeight >= 0)
		{
			head->maxWeight = head->elemWeight;
			head->minWeight = head->elemWeight;
		}
		if (head->level != 0)
		{
			if (head->ptrFath->elemWeight == -1)
			{
				head->ptrFath->maxWeight = head->ptrFath->maxWeight + head->maxWeight;
				if (head->ptrFath->minWeight == 100000)
				{
					head->ptrFath->minWeight = 0;
				}
				head->ptrFath->minWeight = head->ptrFath->minWeight + head->minWeight;
			}
			if (head->ptrFath->elemWeight == -2)
			{
				if (head->ptrFath->maxWeight < head->maxWeight)
				{
					head->ptrFath->maxWeight = head->maxWeight;
				}
				if (head->ptrFath->minWeight > head->minWeight)
				{
					head->ptrFath->minWeight = head->minWeight;
				}
			}
		}
					
	}	
}

void calc_permissWeight(Tree *head, int weight)
{		
	if (head)
	{
		if (head->level == 0)
		{			
			if (head->minWeight > weight)
			{
				head->status = FALSE;
			}
			else if (head->maxWeight < weight)
			{
				
			}
			else 
			{
				calc_permissWeight(head->ptrSon, weight);
			}
		}
		else
		{
			if (head->ptrFath->elemWeight == -1)
			{
				int weight1 = weight - (head->ptrFath->minWeight - head->minWeight);
				if (head->minWeight > weight1)
				{
					head->status = FALSE;
				}
				else
				{
					calc_permissWeight(head->ptrSon, weight1);
				}
				calc_permissWeight(head->ptrBro, weight);
			}
			else
			{
				if (head->minWeight > weight)
				{
					head->status = FALSE;
				}
				else
				{
					calc_permissWeight(head->ptrSon, weight);
				}
				calc_permissWeight(head->ptrBro, weight);
			}
		}
	}

	
}

void print_tree(FILE *output, Tree *root)
{
	int i, j;
	char str[20];
	if (root)
	{
		for (i = 0; i < root->level; i++) 
		{ 
			str[i] = '.'; 
		}
		j = 0;
		while (str[i++] = (root->name)[j++]); 
		str[i-1] = '\n';
		str[i] = '\0';
		if (root->status==TRUE)
		{
			fputs(str, output);	
			print_tree(output, root->ptrSon);
			print_tree(output, root->ptrBro);
		}
		else
		{
			print_tree(output, root->ptrBro);
		}
	}
}

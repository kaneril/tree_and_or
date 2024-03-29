// lab2_0.cpp: определяет точку входа для консольного приложения.
//
/*В  листьях  И-ИЛИ  дерева,  соответствующего некоторому
множеству  конструкций,  заданы   значения   массы.   Известно
максимально допустимое значение массы изделия. Требуется усечь
дерево   так,   чтобы   дерево    включало    все    элементы,
соответствующие  допустимым  значениям массы,  но не содержало
"лишних" вершин.  Конечное дерево выдать на экран в  наглядном
виде*/

#include "stdafx.h"
#include "file_funct.h"
#include "tree_and_or.h"

FILE *input;
FILE *output;

int main(int argc, char* argv[])
{
	//Подключаем русский язык
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	if (argc != 4)
	{
		printf_s("\nОшибка ввода имен файла");
		_getch();
		return -1;
	}
	//Открываем файлы
	input = open_file(input, argv[1], "r");
	if (input == NULL)
	{
		_getch();
		return 0;
	};
	output = open_file(output, argv[2], "w");
	
	Tree *root=NULL;
	init_tree(input, root);
	close_file(input, argv[1]);
	calc_min_maxWeight(root);
	/*int weight = 0;
	printf_s("Введите максимально допустимое значение массы изделия: ");
	scanf_s("%d", &weight);*/
	calc_permissWeight(root, atoi(argv[3]));
	if (root->status == TRUE)
	{
		print_tree(output, root);
	}
	else
	{
		fputs("Пустое дерево", output);
	}	
	close_file(output, argv[2]);
	return 0;
}


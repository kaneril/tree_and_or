#include "file_funct.h"

FILE* open_file(FILE*f, const char*s, const char*a)
{
	fopen_s(&f, s, a);
	if (f == NULL)
	{
		printf_s("Ошибка открытия файла %s\n", s);
	}
	else
	{
		printf_s("Файл %s открыт\n", s);
	};
	return (f);
}

int close_file(FILE*f, const char*s)
{
	fclose(f);
	printf_s("Файл %s закрыт \n",s);
	return 0;
}
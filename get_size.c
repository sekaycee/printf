#include "main.h"

/**
 * get_size - computes the size to cast the argument
 * @format: formatted string to print the args
 * @n: buffer limit
 * Return: size
 */
int get_size(const char *format, int *n)
{
	int c = *n + 1;
	int size = 0;

	if (format[c] == 'l')
		size = S_LONG;
	else if (format[c] == 'h')
		size = S_SHORT;

	if (size == 0)
		*n = c - 1;
	else
		*n = c;
	return (size);
}


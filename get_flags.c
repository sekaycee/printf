#include "main.h"

/**
 * get_flags - compute active flags
 * @format: formatted string to print the args
 * @n: buffer limit
 * Return: Flags:
 */
int get_flags(const char *format, int *n)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int i, c;
	int flags = 0;
	const char F_CHAR[] = {'-', '+', '0', '#', ' ', '\0'};
	const int F_INT[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (c = *n + 1; format[c] != '\0'; c++)
	{
		for (i = 0; F_CHAR[i] != '\0'; i++)
			if (format[c] == F_CHAR[i])
			{
				flags |= F_INT[i];
				break;
			}

		if (F_CHAR[i] == 0)
			break;
	}

	*n = c - 1;

	return (flags);
}


#include "main.h"

/**
 * get_width - computes the width for printing
 * @format: formatted string to print the args
 * @n: buffer limit
 * @al: list of arguments
 * Return: width
 */
int get_width(const char *format, int *n, va_list al)
{
	int c;
	int width = 0;

	for (c = *n + 1; format[c] != '\0'; c++)
	{
		if (is_digit(format[c]))
		{
			width *= 10;
			width += format[c] - '0';
		}
		else if (format[c] == '*')
		{
			c++;
			width = va_arg(al, int);
			break;
		}
		else
			break;
	}

	*n = c - 1;
	return (width);
}


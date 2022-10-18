#include "main.h"

/**
 * get_precision - computes the precision for printing
 * @format: formatted string to print the args
 * @i: buffer limit
 * @al: list of arguments
 * Return: precision
 */
int get_precision(const char *format, int *i, va_list al)
{
	int c = *i + 1;
	int p = -1;

	if (format[c] != '.')
		return (p);

	p = 0;

	for (c += 1; format[c] != '\0'; c++)
	{
		if (is_digit(format[c]))
		{
			p *= 10;
			p += format[c] - '0';
		}
		else if (format[c] == '*')
		{
			c++;
			p = va_arg(al, int);
			break;
		}
		else
			break;
	}

	*i = c - 1;

	return (p);
}


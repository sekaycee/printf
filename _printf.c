#include "main.h"

void print_b(char *, int *);

/**
 * _printf - custom printf function
 * @format: print format
 * @Return: count of printed chars
 */
int _printf(const char *format, ...)
{
	int i, ib = 0; p = 0, pc = 0;
	int flags, width, precision, size;
	va_list al;
	char b[BUFF_SIZE];

	if (!format)
		return (-1);

	va_start(al, format);
	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			b[ib++] = format[i];
			if (ib == BUFF_SIZE)
				print_buffer(b, &ib);
			/* write(1, &format[i], 1);*/
			pc++;
		}
		else
		{
			print_buffer(b, &ib);
			size = get_size(format, &i);
			flags = get_flags(format, &i);
			width = get_width(format, &i, al);
			precision = get_precision(format, &i, al);
			++i;
			p = handle_print(format, &i, al, b,
				flags, width, precision, size);
			if (p == -1)
				return (-1);
			pc += p;
		}
	}

	print_buffer(b, &ib);

	va_end(al);
	return (pc);
}

/**
 * print_buffer - print contents of buffer if exists
 * @b: array of chars
 * @i: index of next char.. same as buffer length
 */
void print_buffer(char *b, int *i)
{
	if (*i > 0)
		write(1, &b[0], *i);
	*i = 0;
}


#include "main.h"

/**
 * handle_print - print an argument based on its type
 * @fmt: formatted string to print the args
 * @list: List of arguments to be printed
 * @ind: buffer index
 * @b: buffer array to handle print
 * @f: computes active flags
 * @w: get width
 * @p: precision specification
 * @s: size specifier
 * Return: 1 or 2
 */
int handle_print(const char *fmt, int *ind, va_list list, char *b, int f, int w, int p, int s)
{
	int i, ul = 0, pc = -1;
	print_t at[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_bin},
		{'u', print_unsgnd}, {'o', print_oct}, {'x', print_uhex},
		{'X', print_hex_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13}, {'\0', NULL}
	};
	for (i = 0; at[i].format != '\0'; i++)
		if (fmt[*ind] == at[i].format)
			return (at[i].fn(list, b, f, w, p, s));

	if (at[i].format == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		ul += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			ul += write(1, " ", 1);
		else if (w)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		ul += write(1, &fmt[*ind], 1);
		return (ul);
	}
	return (pc);
}


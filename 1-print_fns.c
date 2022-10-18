#include "main.h"

/**
 * print_unsgnd - print an unsigned number
 * @al: list of arguments
 * @b: buffer to handle print
 * @f: compute active flags
 * @w: get width
 * @p: precision specification
 * @s: size specifier
 * Return: number of chars printed
 */
int print_unsgnd(va_list al, char *b, int f, int w, int p, int s)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(al, unsigned long int);

	num = convert_size_unsgnd(num, s);

	if (num == 0)
		b[i--] = '0';

	b[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		b[i--] = (num % 10) + '0';
		num /= 10;
	}
	i++;
	return (write_unsgnd(0, i, b, f, w, p, s));
}

/**
 * print_oct - print an unsigned number in octal notation
 * @al: list of arguments
 * @b: buffer to handle print
 * @f: compute active flags
 * @w: get width
 * @p: precision specification
 * @s: size specifier
 * Return: number of chars printed
 */
int print_oct(va_list al, char *b, int f, int w, int p, int s)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(al, unsigned long int);
	unsigned long int n = num;

	UNUSED(w);

	num = convert_size_unsgnd(num, s);

	if (num == 0)
		b[i--] = '0';

	b[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		b[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (f & F_HASH && n != 0)
		b[i--] = '0';

	i++;

	return (write_unsgnd(0, i, b, f, w, p, s));
}

/**
 * print_uhex - prints an unsigned number in hexadecimal notation
 * @al: list of arguments
 * @b: buffer to handle print
 * @f: compute active flags
 * @w: get width
 * @p: precision specification
 * @s: size specifier
 * Return: number of chars printed
 */
int print_uhex(va_list al, char *b, int f, int w, int p, int s)
{
	return (print_hex(al, "0123456789abcdef", b, f, 'x', w, p, s));
}

/**
 * print_hex_upper - print an unsigned number in upper hex notation
 * @al: list of arguments
 * @b: buffer to handle print
 * @f: compute active flags
 * @w: get width
 * @p: precision specification
 * @s: size specifier
 * Return: number of chars printed
 */
int print_hex_upper(va_list al, char *b, int f, int w, int p, int s)
{
	return (print_hex(al, "0123456789ABCDEF", b, f, 'X', w, p, s));
}

/**
 * print_hex - print a hex number in lower or uppercase
 * @al: list of arguments
 * @m: array of values to map the number to
 * @b: buffer to handle print
 * @f: compute active flags
 * @fc: compute active flags char
 * @w: get width
 * @p: precision specification
 * @s: size specifier
 * Return: number of chars printed
 */
int print_hex(va_list al, char *m, char *b, int f, char fc, int w, int p, int s)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(al, unsigned long int);
	unsigned long int n = num;

	UNUSED(w);

	num = convert_size_unsgnd(num, s);
	if (num == 0)
		b[i--] = '0';

	b[BUFF_SIZE - 1] = '\0';
	while (num > 0)
	{
		b[i--] = m[num % 16];
		num /= 16;
	}

	if (f & F_HASH && n != 0)
	{
		b[i--] = fc;
		b[i--] = '0';
	}

	i++;
	return (write_unsgnd(0, i, b, f, w, p, s));
}


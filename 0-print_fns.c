#include "main.h"

/**
 * print_char - print a char
 * @al: list of arguments
 * @b: buffer to handle print
 * @f: compute active flags
 * @w: get width
 * @p: precision specification
 * @s: size specifier
 * Return: number of chars printed
 */
int print_char(va_list al, char *b, int f, int w, int p, int s)
{
	char c = va_arg(al, int);

	return (write_char_handler(c, b, f, w, p, s));
}

/**
 * print_string - print a string
 * @al: list of arguments
 * @b: buffer to handle print
 * @f: compute active flags
 * @w: get width
 * @p: precision specification
 * @s: size specifier
 * Return: number of chars printed
 */
int print_string(va_list al, char *b, int f, int w, int p, int s)
{
	int l = 0, i;
	char *str = va_arg(al, char *);

	UNUSED(b);
	UNUSED(f);
	UNUSED(w);
	UNUSED(p);
	UNUSED(s);
	if (!str)
	{
		str = "(null)";
		if (p >= 6)
			str = "      ";
	}

	while (str[l] != '\0')
		l++;

	if (p >= 0 && p < l)
		l = p;

	if (w > l)
	{
		if (f & F_MINUS)
		{
			write(1, &str[0], l);
			for (i = w - l; i > 0; i--)
				write(1, " ", 1);
			return (w);
		}
		else
		{
			for (i = w - l; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], l);
			return (w);
		}
	}

	return (write(1, str, l));
}

/**
 * print_percent - print a percent symbol
 * @al: list of arguments
 * @b: buffer to handle print
 * @f: compute active flags
 * @w: get width
 * @p: precision specification
 * @s: size specifier
 * Return: number of chars printed
 */
int print_percent(va_list al, char *b, int f, int w, int p, int s)
{
	UNUSED(al);
	UNUSED(b);
	UNUSED(f);
	UNUSED(w);
	UNUSED(p);
	UNUSED(s);
	return (write(1, "%%", 1));
}

/**
 * print_int - print integer
 * @al: list of arguments
 * @b: buffer to handle print
 * @f: compute active flags
 * @w: get width
 * @p: precision specification
 * @s: size specifier
 * Return: number of chars printed
 */
int print_int(va_list al, char *b, int f, int w, int p, int s)
{
	int i = BUFF_SIZE - 2;
	int neg = 0;
	long int n = va_arg(al, long int);
	unsigned long int num;

	n = convert_size_number(n, s);

	if (n == 0)
		b[i--] = '0';

	b[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;
	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		neg = 1;
	}

	while (num > 0)
	{
		b[i--] = (num % 10) + '0';
		num /= 10;
	}
	i++;

	return (write_num(neg, i, b, f, w, p, s));
}

/**
 * print_bin - print an unsigned number
 * @al: list of arguments
 * @b: buffer to handle print
 * @f: compute active flags
 * @w: get width
 * @p: precision specification
 * @s: size specifier
 * Return: number of char printed
 */
int print_bin(va_list al, char *b, int f, int w, int p, int s)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int c;

	UNUSED(b);
	UNUSED(f);
	UNUSED(w);
	UNUSED(p);
	UNUSED(s);

	n = va_arg(al, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, c = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			c++;
		}
	}
	return (c);
}


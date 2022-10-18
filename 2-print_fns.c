#include "main.h"

/**
 * print_pointer - print the value of a mem address
 * @al: list of arguments
 * @b: buffer to handle print
 * @f: compute active flags
 * @w: get width
 * @p: precision specification
 * @s: size specifier
 * Return: number of chars printed
 */
int print_pointer(va_list al, char *b, int f, int w, int p, int s)
{
	char xc = 0, pa = ' ';
	int i = BUFF_SIZE - 2, l = 2, ps = 1; /* l=2, for '0x' */
	unsigned long na;
	char m[] = "0123456789abcdef";
	void *a = va_arg(al, void *);

	UNUSED(w);
	UNUSED(s);

	if (!a)
		return (write(1, "(nil)", 5));

	b[BUFF_SIZE - 1] = '\0';
	UNUSED(p);

	na = (unsigned long)a;
	while (na > 0)
	{
		b[i--] = m[na % 16];
		na /= 16;
		l++;
	}

	if ((f & F_ZERO) && !(f & F_MINUS))
		pa = '0';
	if (f & F_PLUS)
		xc = '+', l++;
	else if (f & F_SPACE)
		xc = ' ', l++;

	i++;
	/*return (write(1, &b[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(b, i, l, w, f, pa, xc, ps));
}

/**
 * print_non_printable - print ascii in hex of non-printable chars
 * @al: list of arguments
 * @b: buffer to handle print
 * @f: compute active flags
 * @w: get width
 * @p: precision specification
 * @s: size specifier
 * Return: number of chars printed
 */
int print_non_printable(va_list al, char *b, int f, int w, int p, int s)
{
	int i = 0, o = 0;
	char *str = va_arg(al, char *);

	UNUSED(f);
	UNUSED(w);
	UNUSED(p);
	UNUSED(s);

	if (!str)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			b[i + o] = str[i];
		else
			o += append_hex(str[i], b, i + o);

		i++;
	}

	b[i + o] = '\0';
	return (write(1, b, i + o));
}

/**
 * print_reverse - print reverse string
 * @al: list of arguments
 * @b: buffer to handle print
 * @f: compute active flags
 * @w: get width
 * @p: precision specification
 * @s: size specifier
 * Return: number of chars printed
 */
int print_reverse(va_list al, char *b, int f, int w, int p, int s)
{
	char *str;
	int i, c = 0;

	UNUSED(b);
	UNUSED(f);
	UNUSED(w);
	UNUSED(s);

	str = va_arg(al, char *);

	if (str == NULL)
	{
		UNUSED(p);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		c++;
	}
	return (c);
}

/**
 * print_rot13 - print a string in rot13
 * @al: list of arguments
 * @b: buffer to handle print
 * @f: compute active flags
 * @w: get width
 * @p: precision specification
 * @s: size specifier
 * Return: number of chars printed
 */
int print_rot13(va_list al, char *b, int f, int w, int p, int s)
{
	char x;
	char *str;
	unsigned int i, j;
	int c = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(al, char *);
	UNUSED(b);
	UNUSED(f);
	UNUSED(w);
	UNUSED(p);
	UNUSED(s);

	if (!str)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				c++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			c++;
		}
	}
	return (c);
}


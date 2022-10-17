#include "main.h"

/**
 * write_char_handler - print a string
 * @c: char types
 * @b: b to handle print
 * @f: computes active f
 * @w: get w
 * @p: precision specifier
 * @s: size specifier
 * Return: number of chars printed
 */
int write_char_handler(char c, char b[],
	int f, int w, int p, int s)
{ /* char is stored at left and pading at b's right */
	int i = 0;
	char pad = ' ';

	UNUSED(p);
	UNUSED(s);

	if (f & F_ZERO)
		pad = '0';

	b[i++] = c;
	b[i] = '\0';

	if (w > 1)
	{
		b[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < w - 1; i++)
			b[BUFF_SIZE - i - 2] = pad;

		if (f & F_MINUS)
			return (write(1, &b[0], 1) +
					write(1, &b[BUFF_SIZE - i - 1], w - 1));
		else
			return (write(1, &b[BUFF_SIZE - i - 1], w - 1) +
					write(1, &b[0], 1));
	}

	return (write(1, &b[0], 1));
}

/**
 * write_num - print a number to stdout
 * @neg: list of arguments
 * @n: b limit
 * @b: b to handle print
 * @f:  compute active f
 * @w: get w
 * @p: precision specifier
 * @s: size specifier
 * Return: number of chars printed
 */
int write_num(int neg, int n, char *b, int f, int w, int p, int s)
{
	int l = BUFF_SIZE - n - 1;
	char pad = ' ', xc = 0;

	UNUSED(s);

	if ((f & F_ZERO) && !(f & F_MINUS))
		pad = '0';
	if (neg)
		xc = '-';
	else if (f & F_PLUS)
		xc = '+';
	else if (f & F_SPACE)
		xc = ' ';

	return (write_num_helper(n, b, f, w, p, l, pad, xc));
}

/**
 * write_num - Write a number using a bufffer
 * @n: Index at which the number starts on the b
 * @b: Buffer
 * @f: Flags
 * @w: w specifier
 * @p: Precision specifier
 * @l: Number l
 * @pad: Pading char
 * @xc: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int n, char b[],
	int f, int w, int prec,
	int l, char pad, char xc)
{
	int i, ps = 1;

	if (p == 0 && n == BUFF_SIZE - 2 && b[n] == '0' && w == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (p == 0 && n == BUFF_SIZE - 2 && b[n] == '0')
		b[n] = pad = ' '; /* w is displayed with pading ' ' */
	if (p > 0 && p < l)
		pad = ' ';
	while (p > l)
		b[--n] = '0', l++;
	if (xc != 0)
		l++;
	if (w > l)
	{
		for (i = 1; i < w - l + 1; i++)
			b[i] = pad;
		b[i] = '\0';
		if (f & F_MINUS && pad == ' ')/* Asign extra char to left of b */
		{
			if (xc)
				b[--n] = xc;
			return (write(1, &b[n], l) + write(1, &b[1], i - 1));
		}
		else if (!(f & F_MINUS) && pad == ' ')/* extra char to left of buff */
		{
			if (xc)
				b[--n] = xc;
			return (write(1, &b[1], i - 1) + write(1, &b[n], l));
		}
		else if (!(f & F_MINUS) && pad == '0')/* extra char to left of pad */
		{
			if (xc)
				b[--ps] = xc;
			return (write(1, &b[ps], i - ps) +
				write(1, &b[n], l - (1 - ps)));
		}
	}
	if (xc)
		b[--n] = xc;
	return (write(1, &b[n], l));
}



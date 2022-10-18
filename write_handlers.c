#include "main.h"

/**
 * write_char_handler - write a string
 * @c: char types
 * @b: buffer to handle print
 * @f: computes active flags
 * @w: get width
 * @p: precision specifier
 * @s: size specifier
 * Return: number of chars written
 */
int write_char_handler(char c, char b[],
	int f, int w, int p, int s)
{ /* char is stored at left and padding at b's right */
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
 * write_num - write a number to stdout
 * @neg: check if num is negative
 * @n: buffer limit
 * @b: buffer to handle print
 * @f: compute active flags
 * @w: get width
 * @p: precision specifier
 * @s: size specifier
 * Return: number of chars written
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
 * write_num_helper - helper function for write_num
 * @n: buffer index
 * @b: buffer
 * @f: flags
 * @w: width specifier
 * @p: precision specifier
 * @l: number length
 * @pad: padding char
 * @xc: extra char
 * Return: number of written chars
 */
int write_num_helper(int n, char *b, int f, int w, int p,
	       int l, char pad, char xc)
{
	int i, ps = 1;

	if (p == 0 && n == BUFF_SIZE - 2 && b[n] == '0' && w == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (p == 0 && n == BUFF_SIZE - 2 && b[n] == '0')
		b[n] = pad = ' '; /* w is displayed with padding ' ' */
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
		if (f & F_MINUS && pad == ' ')/* extra char to left of b */
		{
			if (xc)
				b[--n] = xc;
			return (write(1, &b[n], l) + write(1, &b[1], i - 1));
		}
		else if (!(f & F_MINUS) && pad == ' ')/* extra char to left of b */
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

/**
 * write_unsgnd - write an unsigned number
 * @neg: check if the num is negative
 * @n: buffer index
 * @b: array of chars
 * @f: flags specifiers
 * @w: width specifier
 * @p: precision specifier
 * @s: size specifier
 * Return: number of written chars
 */
int write_unsgnd(int neg, int n, char *b, int f, int w, int p, int s)
{
	/* The number is stored at the buffer's right and starts at position i */
	int l = BUFF_SIZE - n - 1, i = 0;
	char pad = ' ';

	UNUSED(neg);
	UNUSED(s);

	if (p == 0 && n == BUFF_SIZE - 2 && b[n] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (p > 0 && p < l)
		pad = ' ';

	while (p > l)
	{
		b[--n] = '0';
		l++;
	}

	if ((f & F_ZERO) && !(f & F_MINUS))
		pad = '0';

	if (w > l)
	{
		for (i = 0; i < w - l; i++)
			b[i] = pad;

		b[i] = '\0';
		if (f & F_MINUS) /* extra char to left of b [b>pad] */
			return (write(1, &b[n], l) + write(1, &b[0], i));
		else /* extra char to left of padding [pad>b] */
			return (write(1, &b[0], i) + write(1, &b[n], l));
	}

	return (write(1, &b[n], l));
}

/**
 * write_pointer - write a memory address
 * @b: array of chars
 * @n: buffer index
 * @l: length of number
 * @w: width specifier
 * @f: flags specifier
 * @pad: char representing the padding
 * @xc: char representing extra char
 * @ps: index at which padding should start
 * Return: number of written chars
 */
int write_pointer(char *b, int n, int l, int w, int f,
		char pad, char xc, int ps)
{
	int i;

	if (w > l)
	{
		for (i = 3; i < w - l + 3; i++)
			b[i] = pad;
		b[i] = '\0';
		if (f & F_MINUS && pad == ' ')/* extra char to left of b */
		{
			b[--n] = 'x';
			b[--n] = '0';
			if (xc)
				b[--n] = xc;
			return (write(1, &b[n], l) + write(1, &b[3], i - 3));
		}
		else if (!(f & F_MINUS) && pad == ' ')/* extra char to left of b */
		{
			b[--n] = 'x';
			b[--n] = '0';
			if (xc)
				b[--n] = xc;
			return (write(1, &b[3], i - 3) + write(1, &b[n], l));
		}
		else if (!(f & F_MINUS) && pad == '0')/* extra char to left of pad */
		{
			if (xc)
				b[--ps] = xc;
			b[1] = '0';
			b[2] = 'x';
			return (write(1, &b[ps], i - ps) +
					write(1, &b[n], l - (1 - ps) - 2));
		}
	}
	b[--n] = 'x';
	b[--n] = '0';
	if (xc)
		b[--n] = xc;
	return (write(1, &b[n], BUFF_SIZE - n - 1));
}


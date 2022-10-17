#include "main.h"

/**
 * write_char_handler - print a string
 * @c: char types
 * @b: buffer to handle print
 * @f: computes active flags
 * @w: get width
 * @p: precision specifier
 * @s: size specifier
 * Return: number of chars printed
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



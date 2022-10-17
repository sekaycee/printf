#include "main.h"

/**
 * is_digit - check if c is a digit
 * @c: input char
 * Return: 1 if c is a digit, 0 otherwise
 */
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/**
 * is_printable - check if c is printable
 * @c: input char
 * Return: 1 if c is printable, 0 otherwise
 */
int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);
	return (0);
}

/**
 * append_hex - append ascii in hexadecimal code to b
 * @b: array of chars
 * @i: index to start appending
 * @ascii: ASCII CODE
 * Return: Always 3
 */
int append_hex(char ascii, char b[], int i)
{
	char map[] = "0123456789ABCDEF";
	/* The hex code is always 2 digits long */
	if (ascii < 0)
		ascii *= -1;

	b[i++] = '\\';
	b[i++] = 'x';
	b[i++] = map[ascii / 16];
	b[i] = map[ascii % 16];

	return (3);
}

/**
 * convert_size_number - cast n to the specified size
 * @n: cast number
 * @s: type cast indicator
 * Return: cast of n
 */
long int convert_size_number(long int n, int s)
{
	if (s == S_LONG)
		return (n);
	else if (s == S_SHORT)
		return ((short)n);
	return ((int)n);
}

/**
 * convert_size_unsgnd - cast n to the specified size
 * @n: cast number
 * @s: type cast indicator
 * Return: cast of n
 */
long int convert_size_unsgnd(unsigned long int n, int s)
{
	if (s == S_LONG)
		return (n);
	else if (s == S_SHORT)
		return ((unsigned short)n);
	return ((unsigned int)n);
}


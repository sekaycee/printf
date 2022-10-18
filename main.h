#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* SIZES */
#define S_LONG 2
#define S_SHORT 1

/**
 * struct print - struct op
 * @format: print format
 * @fn: synonymous function
 */
typedef struct print
{
	char format;
	int (*fn)(va_list, char[], int, int, int, int);
} print_t;

int _printf(const char *format, ...);
int handle_print(const char *, int *, va_list, char *, int, int, int, int);

/* functions to print chars and strings */
int print_char(va_list, char *, int, int, int, int);
int print_string(va_list, char *, int, int, int, int);
int print_percent(va_list, char *, int, int, int, int);

/* functions to print numbers */
int print_int(va_list, char *, int, int, int, int);
int print_bin(va_list, char *, int, int, int, int);
int print_unsgnd(va_list, char *, int, int, int, int);
int print_oct(va_list, char *, int, int, int, int);
int print_hex(va_list, char *, char *, int, char, int, int, int);
int print_uhex(va_list, char *, int, int, int, int);
int print_hex_upper(va_list, char *, int, int, int, int);

/* function to print non-printable characters */
int print_non_printable(va_list, char *, int, int, int, int);

/* function to print memory address */
int print_pointer(va_list, char *, int, int, int, int);

/* functions to handle other specifiers */
int get_flags(const char *, int *);
int get_width(const char *, int *, va_list);
int get_precision(const char *, int *, va_list);
int get_size(const char *, int *);

/* function to print string in reverse */
int print_reverse(va_list, char *, int, int, int, int);

/* function to print a string in rot 13 */
int print_rot13(va_list, char *, int, int, int, int);

/* write handlers */
int write_char_handler(char c, char *, int, int, int, int);
int write_num(int, int, char *, int, int, int, int);
int write_num_helper(int, char *, int, int, int, int, char, char);
int write_pointer(char *, int, int, int, int, char, char, int);
int write_unsgnd(int, int, char *, int, int, int, int);

/* utility functions */
int is_digit(char);
int is_printable(char);
int append_hex(char, char *, int);
long int convert_size_number(long int, int);
long int convert_size_unsgnd(unsigned long int, int);

#endif /* MAIN_H */


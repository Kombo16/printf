#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFFER 1024

int _printf(const char *format, ...);
int handle_print(const char *fmt, int *i,va_list list, char buffer[], int flags, int width, int precision, int size);
int _print_char(va_list types, char buffer[], int flags, int width, int precision, int size);
int _print_string(va_list types, char buffer[], int flags, int width, int precision, int size);
int _print_percent(va_list types, char buffer[], int flags, int width, int precision, int size);
int _print_int(va_list types, char buffer[], int flags, int width, int precision, int size);
int _print_binary(va_list types, char buffer[], int flags, int width, int precision, int size);
int _print_unsigned(va_list types, char buffer[], int flags, int width, int precision, int size);
int _print_octal(va_list types, char buffer[], int flags, int width, int precision, int size);
int _print_hexadecimal(va_list types, char buffer[], int flags, int width, int precision, int size);
int _print_hex_upper(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_hexa(va_list types, char map_to[],char buffer[], int flags, char flag_ch, int width, int precision, int size);

int _print_pointer(va_list types, char buffer[], int flags, int width, int precision, int size);
int non_printable(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_reverse(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_in_rot13(va_list types, char buffer[], int flags, int width, int precision, int size);

/*FLAGS*/
#define MINUS 1
#define PLUS 2
#define ZERO 4
#define HASH 8
#define SPACE 16

/*Function to handle specifiers*/
int get_flags(const char *format, int *i);
int get_width(const char *format,int *i, va_list list);
int get_precision(const char *format, int *i, va_list list);
int get_size(const char *format, int *i);


int handle_write_char(char c, char buffer[], int flags, int width, int precision, int size);
int write_number(int is_positive, int ind, char buffer[], int flags, int width, int precision, int size);
int write_unsgnd(int is_negative, int ind, char buffer[], int flags, int width, int precision, int size);

int hexa_append_code(char, char[], int);
long int convert_size_number(long int num, int size);
long int convert_size_unsgnd(unsigned long int num, int size);

#endif

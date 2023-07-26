#include "main.h"

/**
 *_print_unsigned - Function that prints an unsigned number
 *@types: List of arguments
 *@buffer: a buffer of characters
 *@flags: Calculates active flags
 *@width: Width
 *@precision: precision specifier
 *@size: size specifier
 *Return: number of chars printed
 *
 */

int _print_unsigned(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	int i = BUFFER - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFFER - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}
	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**
 *_print_octal - Function to print number in octal
 *@types: List of arguments
 *@buffer: a buffer of characters
 *@flags: Calculates active flags
 *@width: width
 *@precision: precision specifier
 *@size: size specifier
 *Return: number of chars printed
 *
 */

int _print_octal(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	int i = BUFFER - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFFER - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}
	if (flags & HASH && init_num != 0)
		buffer[i--] = '\0';
	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**
 *_print_hexadecimal - Function that prints an unsigned
 *number in hexadecimal
 *@types: List of arguments
 *@buffer: buffer array
 *@flags: Calculates active flags
 *@width: width
 *@precision: precision specifier
 *@size: size specifier
 *Return: number of chars printed
 *
 *
 */
int _print_hexadecimal(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
				flags, 'x', width, precision, size));
}

/**
 *_print_hex_upper - Function that prints an unsigned
 *number in upper hexadecimal
 *@types: List of arguments
 *@buffer: buffer array
 *@flags: Calculate active flags
 *@width: width
 *@precision: precision specifier
 *@size: size specifier
 *Return: number of chars printed
 *
 */
int _print_hex_upper(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
				flags, 'X', width, precision, size));
}

/**
 *print_hexa - prints a hexadecimal
 *in lower or uppercase
 *@types: List of arguments
 *@map_to: Array of values to map values to
 *@buffer: buffer array
 *@flags: Calculate active flags
 *@flag_ch: Calculate active flags
 *@width: width
 *@precision: precision specifier
 *@size: size specifier
 *Return: number of chars printed
 *
 */
int print_hexa(va_list types, char map_to[], char buffer[],
		int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFFER - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);
	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';
	buffer[BUFFER - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;

		if (flags & HASH && init_num != 0)
		{
			buffer[i--] = flag_ch;
			buffer[i--] = '0';
		}
	}
	i++;
	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

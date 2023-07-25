#include "main.h"

/**
 *print_char - Function that prints a single char
 *@types: List of arguments
 *@buffer: buffer array
 *@flags: calculates active flags
 *@width: width
 *@precision: precision specifier
 *@size: size specifier
 *Return: numbers of chars printed
 *
 *
 */
int print_char(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/**
 *print_string - Function that prints stirng of chars
 *@types: List of arguments
 *@buffer: buffer arrays
 *@flags: Calculates active flags
 *@width: width
 *@precision: precision specifier
 *@size: size specifier
 *Return: Length of string
 *
 */
int print_string(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == 0)
	{
		str = "(nil)";
		if (precision >= 6)
			str = "      ";
	}
	while (str[length] != '\0')
		length++;
	if (precision >= 0 && precision <= length)
		length = precision;
	if (width > length)
	{
		if (flags & MINUS)
		{
			write(1, &str[0], 1);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}
	return (write(1, str, length));
}

/**
 *print_percent - Function that prints the percent sign
 *@types: List of arguments
 *@buffer: buffer array
 *@flags: Calculates active flags
 *@width: Width
 *@precision: precision specifier
 *@size: size specifier
 *Return: Percent sign
 *
 */
int print_percent(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(width);

	return (write(1, "%%", 1));
}

/**
 *print_int - Function that deals with integers
 *@types: List of arguments
 *@buffer: buffer array
 *@flags: calculates active flags
 *@width: Width
 *@precision: Precision specifier
 *@size: size specifier
 *Return: number of chars printed
 *
 */
int print_int(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(width);

	int i = BUFFER - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
	{
		buffer[i--] = '0';
	}
	buffer[BUFFER - 1] = '\0';
	num = (unsigned long int)((-1) * n);
	is_negative = 1;

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}
	i++;
	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/**
 *print_binary - Function that prints number in binary
 *@types: List of arguments
 *@buffer: buffer array
 *@flags: calculates active flags
 *@width: width
 *@precision: precision specifier
 *@size: size specifier
 *Return: numbdr of chars printed
 *
 */

int print_binary(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648;
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
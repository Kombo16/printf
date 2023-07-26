#include "main.h"

/**
 *handle_write_char - Function that handles
 *printing of chars
 *@c: character to be printed
 *@buffer: buffer that temporarily stores chars
 *@flags: Calculates active flags
 *@width: Width
 *@precision: precision specifier
 *@size: size specifier
 *Return: Number of chars printed
 *
 */
int handle_write_char(char c, char buffer[], int flags,
		int width, int precision, int size)
{
	int i = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & ZERO)
	{
		padd = '0';
	}

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFFER - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFFER - i - 2] = padd;
		if (flags & MINUS)
		{
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFFER - i - 1], width - 1));
		}
		else
		{
			return (write(1, &buffer[BUFFER - i - 1], width - 1) +
					write(1, &buffer[0], 1));
		}

	}
	return (write(1, &buffer[0], 1));
}

/**
 *write_number - Function that prints string
 *@is_negative: Flag that checks if num is negative
 *@ind: index of last char
 *@buffer: Buffer array to handle printf
 *@flags: Calculates active flags
 *@width: width
 *@precision: precision specifier
 *@size: size specifier
 *Return: Number of chars printed
 *
 */
int write_number(int is_negative, int ind, char buffer[], int flags,
		int width, int precision, int size)
{
	int length = BUFFER - ind - 1;
	char padd = ' ', extra_ch = '0';

	UNUSED(size);

	if ((flags & ZERO) && !(flags & MINUS))
		extra_ch = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & PLUS)
		extra_ch = '+';
	else if (flags & SPACE)
		extra_ch = ' ';
	return (write_num(ind, buffer, flags, width,
				precision, length, padd, extra_ch));
}

/**
 *write_num - Function that writes number using a buffer
 *@ind: Index of first num on buffer
 *@buffer: Buffer array to handle printf
 *@flags: Calculates active flags
 *@width: width
 *@precision: precision specifier
 *@length: Number length
 *@padd: padding char
 *@extra_c: Extra char
 *Return: Number of chars printed
 *
 */
int write_num(int ind, char buffer[], int flags, int width,
		int precision, int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (precision == 0 && ind == BUFFER - 2 && buffer[ind] == '0'
			&& width == 0)
	{
		return (0); /*for a ".0d" scenario*/
	}
	if (precision == 0 && ind == BUFFER - 2 && buffer[ind] == '0')
	{
		buffer[ind] = padd = ' ';
	}
	if (precision > 0 && precision < length)
		padd = ' ';
	while (precision > length)
	{
		/*padding with 0 when precision is greater than length*/
		buffer[--ind] = '0';
		length++;
	}
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
		{
			buffer[i] = padd;
		}
		buffer[i] = '\0';
		/*assign extra char to left buffer*/
		if (flags & MINUS && padd == ' ')
		{
			if (extra_c)
			{
				buffer[--ind] = extra_c;
			}
			return (write(1, &buffer[ind], length) +
					write(1, &buffer[1], i - 1));
		}
		else if (!(flags & MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], i - 1) +
					write(1, &buffer[ind], length));
		}
		else if (!(flags & MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], i - padd_start) +
					write(1, &buffer[ind],
						length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 *write_unsgnd - Function that prints an
 *unsigned number
 *@is_negative: Number indicating if num is negative
 *@ind: index which number starts in buffer
 *@buffer: A temporary buffer of chars
 *@flags: Calculate active flags
 *@width: width
 *@precision: precision specifier
 *@size: size specifier
 *Return: Number of chars printed
 *
 */
int write_unsgnd(int is_negative, int ind, char buffer[], int flags,
		int width, int precision, int size)
{
	int length = BUFFER - ind - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFFER - 2 &&  buffer[ind] == '0')
		return (0);
	if (precision > 0 && precision < length)
		padd = ' ';
	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}
	if ((flags & ZERO) && !(flags & MINUS))
		padd = '0';
	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & MINUS)
		{
			return (write(1, &buffer[ind], length) +
					write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) +
					write(1, &buffer[ind], length));
		}
	}
	return (write(1, &buffer[ind], length));
}

/**
 *write_pointer - Function that prints memory address
 *@buffer: A temporary buffer of chars
 *@ind: index which number starts in buffer
 *@length: length of number
 *@width: width
 *@flags: Calculates active flags
 *@padd: padding character
 *@extra_c: char representing extra character
 *@padd_start: index which padding should start
 *Return: Number of written chars
 *
 */
int write_pointer(char buffer[], int ind, int length,
		int width, int flags, char padd, char extra_c, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & MINUS && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) +
					write(1, &buffer[3], i - 3));
		}
		else if (!(flags & MINUS) && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], i - 3) +
					write(1, &buffer[ind], length));
		}
		else if (!(flags & MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
					write(1, &buffer[ind],
						length - (1 - padd_start) - 2));

		}
	}	
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFFER - ind - 1));
}

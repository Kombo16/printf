#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 *_printf - Function that prints to standard output
 *@format: format
 *Return: printed characters
 *
 */

int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;

	va_list list;
	char buffer[BUFFER];

	if (format == NULL)
		return (-1);
	va_start(list, format);
	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFFER)
				print_buffer(buffer, &buff_ind);
			printed_chars++;
		}
		else
		{
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, list, buffer, flags,
					width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}
	print_buffer(buffer, &buff_ind);
	va_end(list);
	return (printed_chars);
}

/**
 *print_buffer - Function that prints contents of buffer
 *@buffer: An array of chars
 *@buff_ind: Index to add next character
 *
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], 1);
	*buff_ind = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:38:10 by itsiros           #+#    #+#             */
/*   Updated: 2024/11/07 19:26:04 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static int	ft_putchar_fd(char c, int fd, int count)
{
		if (count < 0)
			return (count);
	if (write(fd, &c, 1) == -1)
		return (-1);
	count++;
	return (count);
}

static int	ft_putnbr_fd(int n, int fd, int count)
{
	unsigned int	i;

	if (n < 0)
	{
		count = ft_putchar_fd('-', fd, count);
		n *= -1;
	}
	i = n;
	if (i > 9)
	{
		count = ft_putnbr_fd(i / 10, fd, count);
		count = ft_putnbr_fd(i % 10, fd, count);
	}
	else
		count = ft_putchar_fd(i + '0', fd, count);
	return (count);
}

static int	ft_putstr_fd(char *s, int fd, int count)
{
	size_t	i;

	i = 0;
	if (!s)
	{
		write(fd, "(null)", 6);
		return (count + 6);
	}
	while (s[i])
		count = ft_putchar_fd(s[i++], fd, count);
	return (count);
}

static int	print_pointer_hex(void *ptr, int count)
{
	char		buffer[20];
	int			index;
	uintptr_t	address;
	int			start;
	int			nibble;

	index = 0;
	buffer[index++] = '0';
	buffer[index++] = 'x';
	address = (uintptr_t)ptr;
	start = (sizeof(address) * 2) - 1;
	while (start > 0 && ((address >> (start * 4)) & 0xF) == 0)
		start--;
	while (start >= 0)
	{
		nibble = (address >> (start * 4)) & 0xF;
		buffer[index++] = (nibble < 10) ? ('0' + nibble) : ('a' + nibble - 10);
		start--;
	}
	write(1, buffer, index);
	return (count + index);
}

static int	unsigned_casting(int i, int fd, int count)
{
	unsigned int	u;

	u = (unsigned int) i;
	if (i >= 0)
		return (ft_putnbr_fd(i, fd, count));
	else
	{
		if (u > 10)
		{
			count = unsigned_casting(u / 10, fd, count);
			count = ft_putnbr_fd(u % 10, fd, count);
		}
		return (count);
	}
}

static int	convert_to_hex(int i, int fd, int count)
{
	unsigned int	u;
	char			*hex;

	u = (unsigned int) i;
	hex = "0123456789abcdef";
	if (u / 16 > 0)
		count = convert_to_hex(u / 16, fd, count);
	count = ft_putchar_fd(hex[u % 16], fd, count);
	return (count);
}

static int	convert_to_HEX(int i, int fd, int count)
{
	unsigned int	u;
	char			*hex;

	u = (unsigned int) i;
	hex = "0123456789ABCDEF";
	if (u / 16 > 0)
		count = convert_to_HEX(u / 16, fd, count);
	count = ft_putchar_fd(hex[u % 16], fd, count);
	return (count);
}

static int	ft_conversions(const char *str, va_list args, int count)
{
	if (*str == '%')
		return (ft_putchar_fd('%', 1, count));
	if (*str == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1, count));
	if (*str == 's')
		return (ft_putstr_fd(va_arg(args, char *), 1, count));
	if (*str == 'p')
		return (print_pointer_hex(va_arg(args, char *), count));
	if (*str == 'd' || *str == 'i')
		return (ft_putnbr_fd(va_arg(args, int), 1, count));
	if (*str == 'u')
		return (unsigned_casting(va_arg(args, int), 1, count));
	if (*str == 'x')
		return (convert_to_hex(va_arg(args, int), 1, count));
	if (*str == 'X')
		return (convert_to_HEX(va_arg(args, int), 1, count));
	return (-1);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;

	va_start(args, str);
	i = 0;
	while (*str != '\0')
	{
		if (*str != '%')
			i = ft_putchar_fd(*str, 1, i);
		else
		{
			str++;
			i = ft_conversions(str, args, i);
		}
		str++;
	}
	va_end (args);
	return (i);
}
// int main ()
// {
// 	//char *s = "SDFASFAAS";
// 	int a = -1;
// 	// int b;
// 	// a = ft_printf("Hellopplee%seeeeee\n", s);
// 	// printf ("%i\n", a);
// 	// a = printf("Hellopplee%seeeeee\n", s);
// 	// printf ("%i\n", a);
// 	// a = ft_printf("%s", (char *)NULL);
// 	// printf ("%i\n", a);
// 	// a = printf("%s", (char *)NULL);
// 	// printf ("%i\n", a);
// 	// a = -10;
// 	// b = ft_printf ("%u", a);
// 	// printf ("\n%i\n", b);
// 	// b = printf ("%u", a);
// 	// printf ("\n%i\n", b);
// 	// ft_printf ("%x\n", a);
// 	// printf ("%x\n", a);
// 	// printf ("%d", 15 % 16);
// 	a = ft_printf("\"\001\002\007\v\010\f\r\n\"");
// 	printf ("%i\n", a);
// 	a = printf("\"\001\002\007\v\010\f\r\n\"");
// 	printf ("%i\n", a);
// 	return (0);
// }
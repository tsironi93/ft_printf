/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:38:10 by itsiros           #+#    #+#             */
/*   Updated: 2024/11/08 17:46:43 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putchar_fd(char c, int fd, int count)
{
	if (count < 0)
		return (count);
	if (write(fd, &c, 1) == -1)
		return (-1);
	return (count + 1);
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
		if (write(fd, "(null)", 6) == -1)
			return (-1);
		return (count + 6);
	}
	while (s[i])
		count = ft_putchar_fd(s[i++], fd, count);
	return (count);
}

// static int	unsigned_casting(int i, int fd, int count)
// {
// 	unsigned int	u;

// 	u = (unsigned int) i;
// 	if (i >= 0)
// 		return (ft_putnbr_fd(i, fd, count));
// 	else
// 	{
// 		if (u > 10)
// 		{
// 			count = unsigned_casting(u / 10, fd, count);
// 			count = ft_putnbr_fd(u % 10, fd, count);
// 		}
// 		return (count);
// 	}
// }

// static int	convert_to_hex(int i, int fd, int count)
// {
// 	unsigned int	u;
// 	char			*hex;

// 	u = (unsigned int) i;
// 	hex = "0123456789abcdef";
// 	if (u / 16 > 0)
// 		count = convert_to_hex(u / 16, fd, count);
// 	count = ft_putchar_fd(hex[u % 16], fd, count);
// 	return (count);
// }

static int	convert_pto_hex(long int i, int fd, int count)
{
	uintptr_t	u;
	char		*hex;

	u = (uintptr_t) i;
	hex = "0123456789abcdef";
	if (u / 16 > 0)
		count = convert_pto_hex(u / 16, fd, count);
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

static int	print_pointer_hex(void *ptr, int fd, int count)
{
	uintptr_t	address;
	char		*hex;

	hex = "0123456789abcdef";
	address = (uintptr_t)ptr;
	count = ft_putchar_fd('0', 1, count);
	count = ft_putchar_fd('x', 1, count);
	count = convert_pto_hex(address, fd, count);
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
		return (print_pointer_hex(va_arg(args, char *), 1, count));
	if (*str == 'd' || *str == 'i')
		return (ft_putnbr_fd(va_arg(args, int), 1, count));
	if (*str == 'u')
		return (unsigned_casting(va_arg(args, int), 1, count));
	if (*str == 'x')
		return (convert_to_hex(va_arg(args, int), 1, count));
	if (*str == 'X')
		return (convert_to_HEX(va_arg(args, int), 1, count));
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;

	va_start(args, str);
	count = 0;
	while (*str != '\0')
	{
		if (*str != '%')
			count = ft_putchar_fd(*str, 1, count);
		else
		{
			str++;
			count = ft_conversions(str, args, count);
		}
		str++;
	}
	va_end (args);
	return (count);
}

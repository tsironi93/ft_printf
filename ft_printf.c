/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:38:10 by itsiros           #+#    #+#             */
/*   Updated: 2024/11/05 17:18:17 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

// int	count_occurences(const char *str)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '%' && str[i + 1] != '%')
// 			count++;
// 		else if (str[i + 1] == '%')
// 		{
// 			count++;
// 			i++;
// 		}
// 		i++;
// 	}
// 	return (count);
// }

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i])
		ft_putchar_fd(s[i++], fd);
}

void	print_pointer_hex(void *ptr)
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
}

void	ft_conversions(const char *str, va_list args)
{
	if (*str == '%')
		ft_putchar_fd('%', 1);
	if (*str == 'c')
		ft_putchar_fd(va_arg(args, int), 1);
	if (*str == 's')
		ft_putstr_fd(va_arg(args, char *), 1);
	if (*str == 'p')
		print_pointer_hex(va_arg(args, char *));
	//if (str == 'i')
	return ;
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
			ft_putchar_fd(*str, 1);
		else
		{
			str++;
			ft_conversions(str, args);
		}
		str++;
		i++;
	}
	va_end (args);
	return (i);
}
// int main ()
// {
// 	int a = 42;
//     void *c = &a;
// 	ft_printf("Helloppl%p\n", c);
// 	printf("Helloppl%p\n", c);
// 	return (0);
// }

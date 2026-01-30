/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 17:05:16 by saibelab          #+#    #+#             */
/*   Updated: 2026/01/29 17:50:39 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_whitespace(char s)
{
	if (s == 0)
		return (0);
	if (s == ' ' || (s >= 9 && s <= 13))
		return (1);
	return (0);
}

int	is_whitespace(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (!(s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
			return (0);
		i++;
	}
	return (1);
}

void skip_whitespace(char *s, int *i)
{
	if (!s)
		return ;
	while (ft_is_whitespace(s[*i]))
		(*i)++;
	return ;
}

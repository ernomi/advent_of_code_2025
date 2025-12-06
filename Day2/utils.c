#include "utils.h"
#include <unistd.h>
#include <string.h>

void	free_arr(char **tofree)
{
	int	i;

	i = -1;
	while (tofree[++i])
		free(tofree[i]);
	free(tofree);
}

static size_t	string_nbr(const char *str, char c)
{
	int	count;
	int	skip;

	count = 0;
	skip = 0;
	while (*str)
	{
		if (*str != c && skip == 0)
		{
			skip = 1;
			count++;
		}
		else if (*str == c)
			skip = 0;
		str++;
	}
	return (count);
}

static char	**freestr(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static void	new_string(char **str, size_t *len, char c)
{
	size_t	i;

	*str += *len;
	*len = 0;
	i = 0;
	while (**str && **str == c)
		(*str)++;
	while ((*str)[i])
	{
		if ((*str)[i] == c)
			return ;
		(*len)++;
		i++;
	}
}

char	**split(char const *s, char c)
{
	char	**tab;
	char	*str;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (string_nbr(s, c) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	str = (char *)s;
	s_len = 0;
	while (i < string_nbr(s, c))
	{
		new_string(&str, &s_len, c);
		tab[i] = malloc(sizeof(char) * (s_len + 1));
		if (!tab[i])
			return (freestr(tab));
		strlcpy(tab[i], str, s_len + 1);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
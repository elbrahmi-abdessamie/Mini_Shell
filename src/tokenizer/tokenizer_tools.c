/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:40:17 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/14 18:09:11 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"
t_arguments	*arguments_constructor(t_arguments *arguments, char *str, unsigned short type);
void	arguments_destructor(t_arguments **arguments);

void	something_wrong(char *error, void *to_free)
{
	free(to_free);
	ft_putendl_fd(error, 2);
	set__get_option_variables(0, FREE);
	exit(1);
}

void	check_out_of_quotes(char c, t_var *var)
{
	if (c == '\"' && !(var->quote))
			(var->dquote) = !(var->dquote);
	if (c == '\'' && !(var->dquote))
		(var->quote) = !(var->quote);
}
void	transform_dollar(char *line, int *i, int *k, char **tmp)
{
	if (ft_isdigit(line[*i + 1]))
		*i += 2;
	else if (line[*i] == '$' && (!line[*i + 1] || ft_isspace(line[*i + 1])))
		(*tmp)[(*k)++] = line[(*i)++];
	else if (line[*i] == '$' && line[*i + 1] == '$')
		(*tmp)[(*k)++] = line[(*i)++];
	else if (line[*i] == '$')
	{
		(*i)++;
		(*tmp)[(*k)++] = '\"';
		while (ft_isalnum(line[*i]) || line[*i] == '_')
			(*tmp)[(*k)++] = line[(*i)++];
		(*tmp)[(*k)++] = '\"';
	}
}

int	delete_quotes(char *line, char **tmp, int i, int is_word)
{
	t_var	var;
	int		k;

	k = 0;
	set_zero_var(&var);
	while (line[i])
	{
		check_out_of_quotes(line[i], &var);
		if (!var.quote && !var.dquote && ft_isspace(line[i]))
		{
			if (is_word)
				break ;
			(*tmp)[k++] = line[i];
		}
		else if ((line[i] == '\"' && var.quote) || (line[i] == '\'' && var.dquote))
			(*tmp)[k++] = line[i];
		else if (line[i] == '$' && (var.dquote || (!var.dquote && !var.quote)))
		{
			transform_dollar(line, &i, &k, tmp);
			continue ;
		}
		else if (line[i] != '\'' && line[i] != '\"')
			(*tmp)[k++] = line[i];
		i++;
	}
	return (i);
}

int	count_dollars(char *line, int *i, int j)
{
	int begin;
	int dollars;
	
	if (i)
		begin = *i;
	else
		begin = j;
	dollars = 0;
	while (line[begin])
	{
		if (line[begin] == '$')
			dollars++;
		begin++;
	}
	return (begin);
}

void	get_dollars(t_arguments	**arguments, char *line, int *i, int *j)
{
	int	k;

	k = 1;
	*i += *j;
	*j = 0;
	if (ft_isdigit(line[*i + 1]))
		*i += 2;
	// else if (line[*i] == '$'  && line[*i + k] == '\"')
	// 	(*i)++;
	else if (line[*i] == '$'  && !(ft_isalnum(line[*i + k]) || line[*i + k] == '_'))
		(*j)++;
	else if (line[*i] == '$' && line[*i + 1] == '$')
		(*j)++;
	else if (line[*i] == '$' && (ft_isalnum(line[*i + k]) || line[*i + k] == '_'))
	{
		while (ft_isalnum(line[*i + k]) || line[*i + k] == '_')
			k++;
		*arguments = arguments_constructor(*arguments, ft_substr(line, *i, k), IS_VARIABLE);
		*i += k;
	}
}

t_arguments	*get_arguments(char *line, int *i, int is_word)
{
	t_arguments	*arguments;
	t_var		var;
	int			j;

	set_zero_var(&var);
	arguments = NULL;
	j = 0;
	while (line[*i + j])
	{
		check_out_of_quotes(line[*i + j], &var);
		if ((var.dquote && line[*i + j] == '\"') || (var.quote && line[*i + j] == '\''))
		{
			if (j)
				arguments = arguments_constructor(arguments, ft_substr(line, *i, j), IS_STR );
			*i += j + 1;
			j = 0;
			continue ;
		}
		if (!var.quote && !var.dquote && ft_isspace(line[*i + j]))
		{
			if (is_word)
				break;
			if (j)
				arguments = arguments_constructor(arguments, ft_substr(line, *i, j), IS_STR);
			*i += j + 1;
			j = 0;
			continue ;
		}
		else if ((line[*i + j] == '\"' && var.quote) || (line[*i + j] == '\'' && var.dquote))
			j++;
		else if (!var.dquote && !var.quote && (line[*i + j] == '\'' || line[*i + j] == '\"'))
		{
			if (j)
				arguments = arguments_constructor(arguments, ft_substr(line, *i, j), IS_STR | DONT_EXPAND_WILD_CARDS);
			*i += j + 1;
			j = 0;
			continue ;
		}
		else if (line[*i + j] == '$' && (var.dquote || (!var.dquote && !var.quote)))
		{
			if (j)
				arguments = arguments_constructor(arguments, ft_substr(line, *i, j), IS_STR);
			get_dollars(&arguments, line, i, &j);
			continue ;
		}
		else if (line[*i + j] && line[*i + j] != '\'' && line[*i + j] != '\"')
			j++;
	}
	if (j)
	{
		arguments = arguments_constructor(arguments, ft_substr(line, *i, j), IS_STR);
		*i += j;
	}
	
	return (arguments);
}

t_arguments	*split_merged(t_arguments *arguments)
{
	char	**str;
	int		len;
	int		i;
	t_arguments	*head;
	t_arguments	*new = NULL;
	t_arguments	*tmp;

	i = 0;
	head = arguments;
	if (head->type == 1)
	{
		str = ft_split(head->str, ' ');
		len = ft_double_strlen(str);
		tmp = head->next;
		free(head->str);
		free (head);
		while (i < len)
				new = arguments_constructor(new, str[i++], IS_STR | MERGED);
		free (str);
		head = new;
		while (new->next)
			new = new->next;
		new->next = tmp;
		arguments = head;
	}
	while (head->next)
	{
		new = NULL;
		i = 0;
		if (head->next->type == 1)
		{

			str = ft_split(head->next->str, ' ');
			len = ft_double_strlen(str);
			if (len == 1)
			{
				free (str[i]);
				free (str);
				head = head->next;
				continue ;
			}
			while (i < len)
				new = arguments_constructor(new, str[i++], IS_STR | MERGED);
			free (str);
			tmp = (head->next)->next;
			free(head->next->str);
			free (head->next);
			head->next = new;
			while (new->next)
				new = new->next;
			new->next = tmp;
		}
		head = head->next;
	}
	return (arguments);
}

t_arguments	*merge_arguments(t_arguments *arguments)
{
	t_arguments	*head;
	t_arguments	*tmp;

	if (!arguments)
		return (NULL);
	head = arguments;
	while (head->next)
	{
		if (head->type == head->next->type && head->type != 0)
		{
			tmp = head->next;
			head->str = ft_strjoin_free(head->str, ft_strdup(" "));
			head->str = ft_strjoin_free(head->str, (head->next)->str);
			head->next = (head->next)->next;
			free (tmp);
		}
		else
			head = head->next;
	}
	return (split_merged(arguments));
}

t_arguments	*get_argument(char *line, int *j, int i, int is_word)
{
	t_arguments	*arguments;
	
	arguments = NULL;
	if (is_word)
		arguments = get_arguments(line, j, is_word);
	else
		arguments = get_arguments(line, &i, is_word);
	arguments = merge_arguments(arguments);
	return (arguments);
}

char	*skip_quotes(char *line, int *i, int j, int is_word)
{
	char		*tmp;
	int			a;
	t_arguments	*arguments;

	a = count_dollars(line, i, j);
	if (is_word)
		tmp = ft_calloc(1, ft_strlen(line + *i) + a + 1);
	else
		tmp = ft_calloc(1, ft_strlen(line + j) + a + 1);
	if (!tmp)
		return (NULL);
	if (is_word)
		*i = delete_quotes(line, &tmp, *i, is_word);
	else
		delete_quotes(line, &tmp, j, is_word);
	return (tmp);
}

int	skip_spaces_front(char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	return (i);
}

void	pr_custom_err(char *error, void *ptr, char *custom)
{
	char	*msg;

	msg = ft_strjoin(error, custom);
	ft_putendl_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	free(msg);
	free (ptr);
}
void	panic_recursive(char *error, char **ptr)
{
	ft_putendl_fd(error, 2);
	free (ptr);
	ptr = NULL;
}

unsigned short	check_wild_cards(char *str, unsigned short type)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
		{
			i = -1;
			break ;
		}
		i++;
	}
	if (type == 3 && i != -1)
		type = 1;
	return (type);
}

t_arguments	*arguments_constructor(t_arguments *arguments, char *str, unsigned short type)
{
	t_arguments	*new;
	t_arguments	*tmp;

	new = malloc(sizeof(t_arguments));
	if (!new)
		return (NULL);
	// type = check_wild_cards(str, type);
	new->str = str;
	new->type = type;
	new->next = NULL;
	if (!arguments)
		return (new);
	tmp = arguments;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (arguments);
}

void	arguments_destructor(t_arguments **arguments)
{
	t_arguments	*tmp;
	t_arguments	*head;

	tmp = *arguments;
	head = *arguments;
	while (head)
	{
		tmp = head;
		head = head->next;
		free (tmp->str);
		free (tmp);
	}
	*arguments = NULL;
}
#include <unistd.h>
#include <string.h>
#include <stdio.h>
 #include <fcntl.h>
 
void	mydup2(int fd1, int fd2)
{
	close(fd2);
	open("amine", O_CREAT | O_APPEND | O_RDWR, 511);
}

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	echo_has_option(char *line)
{
	int	i;
	int	has_option;

	i = 0;
	has_option = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (line[i] == '-' && line[i + 1] == 'n')
		{
			i++;
			while (line[i] == 'n')
				i++;
		}
		else if (line[i] == '\"' && line[i + 1] == '-' && line[i + 2] == 'n')
		{
			i += 2;
			while (line[i] == 'n')
				i++;
			if (line[i] == '\"')
				i++;
		}
		if (ft_isspace(line[i]) || !line[i])
			has_option = 1;
		else
			break ;
	}
	return (has_option);
}

#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[], char **envp)
{
	// printf("%d\n", echo_has_option("-n  \"   -sn\" -n -n \"-n\""));
	printf("%d\n", access("//", X_OK));
	char	**a;
	a = malloc(sizeof (char *) * 2);
	a[0] = malloc(10);
	a[0][0] = '~';
	a[0][1] = '/';
	a[0][2] = 'D';
	a[0][3] = 'e';
	a[0][4] = 's';
	a[0][5] = 'k';
	a[0][6] = 't';
	a[0][7] = 'o';
	a[0][8] = 'p';
	a[0][9] = 0;
	a[1] = NULL;
	if (execve("~/Desktop", a, envp) == -1)
		perror("");
	return 0;
}


// char	**ft_joindstrs(char **ds1, char* *ds2)
// {
// 	char	**words;
// 	int		ds1_len;	
// 	int		ds2_len;
// 	int		i;
// 	int		j;
	
// 	ds1_len = ft_double_strlen(ds1);
// 	ds2_len = ft_double_strlen(ds2);
// 	i = -1;
// 	j = 0;
// 	words = malloc(sizeof(char *) * (ds1_len + ds2_len + 1));
// 	if (!words)
// 		return (NULL);
// 	while (ds1[++i])
// 		words[i] = ds1[i];
// 	while (ds2[j])
// 		words[i++] = ds2[j++];
// 	words[i] = NULL;
// 	free(ds1);
// 	free(ds2);
// 	return (words);
// }


// size_t	args_cmd_len(t_arguments *args)
// {
// 	t_arguments	*tmp;
// 	size_t		len;

// 	len = 0;
// 	tmp = args;
// 	while (tmp)
// 	{
// 		if (!(tmp->type & IS_SEPARTOR))
// 		len++;
// 		tmp = tmp->next;
// 	}
// 	return (len);
// }

// char	**args_to_cmd_dstr(t_arguments *args, char *cmd)
// {
// 	t_arguments	*tmp;
// 	char		**str;
// 	size_t		len;

// 	tmp = args;
// 	len = args_len(args);
// 	if (!len)
// 		return (NULL);
// 	str = malloc(sizeof(char *) * (len + 2));
// 	if (!str)
// 	{
// 		perror("");
// 		return (NULL);
// 	}
// 	len = 0;
// 	str[len++] = cmd;
// 	while (tmp)
// 	{
// 		if (tmp->type & IS_SEPARTOR)
// 			;
// 		else if ((tmp->type & IS_STR || tmp->type & IS_VARIABLE))
// 			str[len++] = ft_strdup(tmp->str);
// 		else
// 			str[len++] = args_to_str(tmp->down);
// 		tmp = tmp->next;
// 	}
// 	str[len] = NULL;
// 	return (str);
// }



// t_arguments	*transform_new_files(char **str)
// {
// 	t_arguments	*files;
// 	int	i;

// 	i = 0;
// 	files = NULL;
// 	while (str[i])
// 	{
// 		files = arguments_constructor(files, str[i], IS_STR);
// 		i++;
// 	}
// 	free (str);
// 	return (files);
// }

// void	*wild_cards(t_arguments *args, char *word)
// {
// 	t_arguments	*head;
// 	t_arguments	*tmp;
// 	t_arguments	*tmp2;
// 	char		*files;
// 	int 		a;

// 	// if (word)
// 	// {
// 	// 	if (ft_strchr(word, '*'))
// 	// 		word = find_files(word);
// 	// 	return (word);
// 	// }
// 	head = args;
// 	while (args)
// 	{
// 		a = 0;
// 		if ((args->type & IS_STR) && ft_strchr(args->str, '*'))
// 		{
// 			files = find_files(args->str);
// 			if (files != args->str)
// 			{
// 				tmp = args->next;
// 				if (args == head)
// 					a = -1;
// 				free (args->str);
// 				free (args);
// 				args = transform_new_files(ft_split(files, ' '));
// 				if (a == -1)
// 					head = args;
// 				else
// 					tmp2->next = args;
// 				while (args->next)
// 					args = args->next;
// 				args->next = tmp;
// 			}
// 		}
// 		tmp2 = args;
// 		args = args->next;
// 	}
// 	args = head;
// 	return (args);
// }

// char	*find_files(char *files)
// {
// 	DIR				*directory;
// 	struct dirent	*dir;
// 	char			*result;
// 	int				i;
// 	int				j;

// 	result = NULL;
// 	directory = opendir(".");
// 	if (directory)
// 	{
// 		dir = readdir(directory);
// 		while (dir != NULL)
// 		{
// 			i = 0;
// 			j = 0;
// 			if ((*dir->d_name == '.' && !*(dir->d_name + 1)) || \
// 			(*dir->d_name == '.' && *(dir->d_name + 1) == '.' && !*(dir->d_name + 2)) || \
// 			(*files != '.' && *dir->d_name == '.'))
// 			{
// 				dir = readdir(directory);
// 				continue ;
// 			}
// 			while (dir->d_name[i])
// 			{
// 				while (files[i] && dir->d_name[j] && files[i] != '*' && files[i] == dir->d_name[j])
// 				{
// 					i++;
// 					j++;
// 				}
// 				if (files[i] == '*')
// 				{
// 					i++;
// 					if (!files[i])
// 					{
// 						if (result)
// 							result = ft_strjoin_free(result, ft_strdup(" "));
// 						result = ft_strjoin_free(result, ft_strdup(dir->d_name));
// 						break ;
// 					}
// 					while (dir->d_name[j] && files[i] != dir->d_name[j])
// 						j++;
// 				}
// 				if (!files[i] && !dir->d_name[j])
// 				{
// 					if (result)
// 						result = ft_strjoin_free(result, ft_strdup(" "));
// 					result = ft_strjoin_free(result, ft_strdup(dir->d_name));
// 					break ;
// 				}
// 				else if (files[i] != dir->d_name[j])
// 					break ;
// 			}
// 			dir = readdir(directory);
// 		}
// 		closedir(directory);
// 	}
// 	if (result)
// 		return (result);
// 	else
// 		return (files);
// }
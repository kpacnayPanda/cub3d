// int		find_right_border(char *line)
// {
// 	int end;
// 	int len;
// 	int flag;

// 	len = ft_strlen(line);
// 	end = 0;
// 	flag = 0;
// 	len--;

// 	while (len != -1)
// 	{
// 		if (line[len] != ' ' && flag == 0)
// 		{
// 			flag = 1;
// 			end = len;
// 		}
// 		len--;
// 	}
// 	return (end);
// }

// int		find_left_border(char *line)
// {
// 	int i;
// 	int start;
// 	int flag;

// 	i = 0;
// 	flag = 0;
// 	start = 0;

// 	while (line[i] != '\0')
// 	{
// 		if (line[i] != ' ' && flag == 0)
// 		{
// 			flag = 1;
// 			start = i;
// 		}
// 		i++;
// 	}
// 	return (start);
// }

// char	*del_whitespaces(char *line)
// {
// 	int i;
// 	int start;
// 	int end;
// 	char *newstr;

// 	i = 0;
// 	start = 0;

// 	start = find_left_border(line);
// 	end = find_right_border(line);

// 	newstr = copy(line, start, end);
// 	return (newstr);
// }

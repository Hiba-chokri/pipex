//strjoin function is used to join the path with the command,Protect strjoin with a condition to check if the first argument is not NULL
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		s1_len;
	int		s2_len;

	if (!s1 && !s2)
		return (ft_strdup(""));
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join = (char *)malloc(s1_len + s2_len + 1);
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, s1_len + 1);
	ft_strlcat(join, s2, s1_len + s2_len + 1);
	return (join);
}
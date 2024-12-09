/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulba <sabdulba@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:03:53 by sabdulba          #+#    #+#             */
/*   Updated: 2024/12/09 05:58:20 by sabdulba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

// static char	*copy_words(const char *start, const char *end);
// static int	count_word(const char *s, char c);
// static void	freeup(char **word, int len);
// static int	process_word(const char **s, char c, char **splitted, int i);
// static const char	*skip_quoted(const char *s, char quote);

// /**
//  * Splits a string into an array of words, considering spaces as delimiters,
//  * but respecting quoted segments as single words.
//  */
// char	**ft_splitplus(char const *s, char c)
// {
// 	int		i;
// 	char	**splitted;
// 	int		count;

// 	if (!s)
// 		return (NULL);
// 	count = count_word(s, c);
// 	splitted = (char **)malloc((count + 1) * sizeof(char *));
// 	if (!splitted)
// 		return (NULL);
// 	i = 0;
// 	while (*s != '\0')
// 	{
// 		if (*s != c)
// 		{
// 			if (!process_word(&s, c, splitted, i))
// 			{
// 				freeup(splitted, i);
// 				return (NULL);
// 			}
// 			i++;
// 		}
// 		else
// 			s++;
// 	}
// 	splitted[i] = 0;
// 	return (splitted);
// }

// /**
//  * Processes a single word, respecting quoted segments.
//  */
// static int	process_word(const char **s, char c, char **splitted, int i)
// {
// 	const char	*start;

// 	start = *s;
// 	if (**s == '\'' || **s == '\"')
// 		*s = skip_quoted(*s, **s); // Skip quoted section
// 	else
// 		while (**s != '\0' && **s != c && **s != '\'' && **s != '\"')
// 			(*s)++;
// 	splitted[i] = copy_words(start, *s);
// 	if (!splitted[i])
// 		return (0);
// 	if (**s == '\'' || **s == '\"')
// 		(*s)++; // Skip closing quote if present
// 	return (1);
// }

// /**
//  * Counts the number of words, respecting quoted segments.
//  */
// static int	count_word(const char *s, char c)
// {
// 	int	count = 0;
// 	int	in_word = 0;

// 	while (*s)
// 	{
// 		if (*s == '\'' || *s == '\"')
// 			s = skip_quoted(s, *s);
// 		else if (*s != c)
// 		{
// 			if (!in_word)
// 			{
// 				count++;
// 				in_word = 1;
// 			}
// 			s++;
// 		}
// 		else
// 		{
// 			in_word = 0;
// 			s++;
// 		}
// 	}
// 	return (count);
// }

// /**
//  * Copies characters from `start` to `end` into a newly allocated string.
//  */
// static char	*copy_words(const char *start, const char *end)
// {
// 	int		length = end - start;
// 	char	*dest = (char *)malloc(length + 1);
// 	if (!dest)
// 		return (NULL);
// 	while (start < end)
// 		*dest++ = *start++;
// 	*dest = '\0';
// 	return (dest - length);
// }

// /**
//  * Frees up allocated memory in case of failure.
//  */
// static void	freeup(char **word, int len)
// {
// 	int	i;

// 	for (i = 0; i < len; i++)
// 		free(word[i]);
// 	free(word);
// }

// /**
//  * Skips over a quoted section of the string.
//  */
// static const char	*skip_quoted(const char *s, char quote)
// {
// 	s++; // Skip the opening quote
// 	while (*s && *s != quote)
// 		s++;
// 	return (*s == quote ? s + 1 : s);
// }

// int main(void)
// {
// 	int i = 0;
// 	char **result = ft_splitplus("awk '{print $1}' wc -l", ' ');
// 	while(result[i] != NULL)
// 	{
// 		printf("%s\n", result[i]);
// 		free(result[i]);
// 		i++;
// 	}
// 	free(result);
// 	return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	count_word(const char *s, char c);
static int	process_word(const char **s, char c, char **splitted, int i);
static char	*copy_words(const char *start, const char *end);
static void	freeup(char **word, int len);
static const char *skip_quoted(const char *s, char quote);

char **ft_splitpls(char const *s, char c)
{
    int i;
    char **splitted;
    int count;

    if (!s)
        return (NULL);
    
    count = count_word(s, c);
    splitted = (char **)malloc((count + 1) * sizeof(char *));
    if (!splitted)
        return (NULL);

    i = 0;
    while (*s != '\0')
    {
        if (*s != c)
        {
            if (!process_word(&s, c, splitted, i))
            {
                freeup(splitted, i);
                return (NULL);
            }
            i++;
        }
        else
            s++;
    }
    
    splitted[i] = NULL;  // Ensure the array is NULL-terminated
    return (splitted);
}

/**
 * Processes a single word, respecting quoted segments.
 */
static int process_word(const char **s, char c, char **splitted, int i)
{
    const char *start;

    start = *s;
    if (**s == '\'' || **s == '\"')
        *s = skip_quoted(*s, **s); // Skip quoted section
    else
        while (**s != '\0' && **s != c && **s != '\'' && **s != '\"')
            (*s)++;
    
    splitted[i] = copy_words(start, *s);
    if (!splitted[i])
        return (0);
    
    if (**s == '\'' || **s == '\"')
        (*s)++; // Skip closing quote if present
    return (1);
}

/**
 * Counts the number of words, respecting quoted segments.
 */
static int count_word(const char *s, char c)
{
    int count = 0;
    int in_word = 0;

    while (*s)
    {
        if (*s == '\'' || *s == '\"')
            s = skip_quoted(s, *s);
        else if (*s != c)
        {
            if (!in_word)
            {
                count++;
                in_word = 1;
            }
            s++;
        }
        else
        {
            in_word = 0;
            s++;
        }
    }
    return (count);
}

/**
 * Copies characters from `start` to `end` into a newly allocated string.
 */
static char *copy_words(const char *start, const char *end)
{
    int length = end - start;
    char *dest = (char *)malloc(length + 1);
    if (!dest)
        return (NULL);
    
    while (start < end)
        *dest++ = *start++;
    *dest = '\0';
    
    return (dest - length);  // Return the original pointer to the start of the string
}

/**
 * Frees up allocated memory in case of failure.
 */
static void freeup(char **word, int len)
{
    for (int i = 0; i < len; i++)
        free(word[i]);
    free(word);
}

/**
 * Skips over a quoted section of the string.
 */
static const char *skip_quoted(const char *s, char quote)
{
    s++; // Skip the opening quote
    while (*s && *s != quote)
        s++;
    return (*s == quote ? s + 1 : s);  // Skip closing quote if present
}

/* int main(void)
{
    int i = 0;
    char **result = ft_splitpls("awk '{print $1}' wc -l", ' ');
    if (result == NULL) {
        printf("Error: Failed to split the string.\n");
        return 1;
    }

    while(result[i] != NULL)
    {
        printf("%s\n", result[i]);
        free(result[i]);
        i++;
    }
    free(result);  // Don't forget to free the array itself
    return 0;
} */

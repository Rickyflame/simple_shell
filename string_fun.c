#include "main.h"

/**
 * _strchr - locates a character in a string
 * @s: string to be searched
 * @c: character to be located
 * Return: if C is found a pointer, otherwise NULL
 */
char *_strchr(char *s, char c)
{
	int index;

	for (index = 0; s[index]; index++)
	{
		if (s[index] == c)
			return (s + index);
	}

return (NULL);
}
/**
 * _strspn - gets the length of a prefix substring
 * @s: string to be searched
 * @accept: prefix to be measured
 * Return: returns number of bytes in s
 */
int _strspn(char *s, char *accept)
{
	int bytes = 0;
	int index;

	while (*s)
	{
		for (index = 0; accept[index]; index++)
		{
			if (*s == accept[index])
			{
				bytes++;
				break;
			}
		}
		s++;
	}
	return (bytes);
}
/**
 * _strcmp - compares two strings
 * @s1: first string to be compared
 * @s2: second string to be compared to
 * Return: postive byte difference and negative byte difference
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}
/**
 * _strncmp - compare two strings
 * @s1: pointer to a string
 * @s2: pointer to a string
 * @n: first n bytes of the string to compare
 * Return: less than 0 if s1 is shorter than s2
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; s1[i] && s2[i] && i < n; i++)
	{
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}

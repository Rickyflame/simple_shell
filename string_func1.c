#include "main.h"

/**
 * _strlen - returns the length of a string
 * @s: pointer to the character string
 * Return: length of the character string
 */
int _strlen(const char *s)
{
	int length = 0;

	if (!s)
		return (length);
	for (length = 0; s[length]; length++)
		;
	return (length);
}
/**
 * _strcpy - copies the string pointed to by src
 * @dest: pointer to the destination of the copied string
 * @src: pointer to the src of the source string
 * Return: pointer to dest
 */
char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}
/**
 * _strcat - concatenates two strings
 * @dest: pointer to destination string
 * @src: pointer to source string
 * Return: pointer to destination string
 */
char *_strcat(char *dest, const char *src)
{
	char *destTemp;
	const char *srcTemp;

	destTemp = dest;
	srcTemp =  src;
	while (*destTemp != '\0')
		destTemp++;
	while (*srcTemp != '\0')
		*destTemp++ = *srcTemp++;
	*destTemp = '\0';
	return (dest);
}
/**
 * _strncat - concatenates two strings where n number of bytes are
 * copied
 * @dest: pointer to destination string
 * @src: pointer to source string
 * @n: n bytes to copy fron src
 * Return: pointer to destination string
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = _strlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';
	return (dest);
}

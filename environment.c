#include "main.h"

/**
 * _copyenv - creates a copy of the environment
 * Return: if error occure NULL otherwise a double pointer to the copy
 */
char **_copyenv(void)
{
	char **new_environ;
	size_t size;
	int index;

	for (size = 0; environ[size]; size++)
		;
	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);
	for (index = 0; environ[index]; index++)
	{
		new_environ[index] = malloc(_strlen(environ[index]) + 1);

		if (!new_environ[index])
		{
			for (index--; index >= 0; index--)
				free(new_environ[index]);
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[index], environ[index]);
	}
	new_environ[index] = NULL;
	return (new_environ);
}
/**
 * free_env - frees the environment copy
 * Return: void has no return value
 */
void free_env(void)
{
	int index;

	for (index = 0; environ[index]; index++)
		free(environ[index]);
	free(environ);
}
/**
 * _getenv - gets an enviromental variable from the PATH
 * @var: name of the environmental variable
 * Return: if variable does not exist NULL otherwise a pointer
 */
char **_getenv(const char *var)
{
	int index, len;

	len = _strlen(var);
	for (index = 0; environ[index]; index++)
	{
		if (_strncmp(var, environ[index], len) == 0)
			return (&environ[index]);
	}
	return (NULL);
}

#include "main.h"

/**
 * error_env - creates a nerror message for shellby_env
 * @args: array of arguments passed to the commands
 * Return: returns the error string
 */
char *error_env(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	args--;
	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 45;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}
	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Unable tp add/remove from enviroment\n");
	free(hist_str);
	return (error);
}
/**
 * error_1 - create an error message for shellby_alias errors
 * @args: array of arguments passsed to the command
 * Return: returns the error string
 */
char *error_1(char **args)
{
	char *error;
	int len;

	len = _strlen(name) + _strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);
	_strcpy(error, "alias: ");
	_strcat(error, args[0]);
	_strcat(error, " not found\n");
	return (error);
}
/**
 * error_2_exit - creates an error message for shellby_exit errors
 * @args: array of arguments passed to the command
 * Return: returns the error string
 */
char *error_2_exit(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);
	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}
	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": exit: Illegal number: ");
	_strcat(error, args[0]);
	_strcat(error, "\n");
	free(hist_str);
	return (error);
}
/**
 * error_2_cd - creates an error message for shellby_cd errors
 * @args: array of arguments passed to the command
 * Return: returns the errors string
 */
char *error_2_cd(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);
	if (args[0][0] == '-')
		args[0][2] = '\0';
	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}
	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	if (args[0][0] == '-')
		_strcat(error, ": cd: Illegal optin ");
	else
		_strcat(error, ": cd: can't cd to ");
	_strcat(error, args[0]);
	_strcat(error, "\n");
	free(hist_str);
	return (error);
}
/**
 * error_2_syntax - create an error message for syntax errors
 * @args: array of arguments passed to the command
 * Return: returns the error string
 */
char *error_2_syntax(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);
	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}
	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Syntax error: \"");
	_strcat(error, args[0]);
	_strcat(error, "\" unexpected\n");
	free(hist_str);
	return (error);
}

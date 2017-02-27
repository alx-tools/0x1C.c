#include <stdio.h>
#include "binary_trees.h"

/* Original code from http://stackoverflow.com/a/13755911/5184480 */

/**
 * print_t - Stores recursively each level in an array of strings
 *
 * @tree: Pointer to the node to print
 * @offset: Offset to print
 * @depth: Depth of the node
 * @s: Buffer
 *
 * Return: length of printed tree after process
 */
int print_t(const binary_tree_t *tree, int is_left, int offset, int depth, char s[20][255])
{
	char b[20];
	int width, left, right;

	if (!tree)
		return (0);
	width = sprintf(b, "(%03d)", tree->val);
	left = print_t(tree->left, 1, offset, depth + 1, s);
	right = print_t(tree->right, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
	for (int i = 0; i < width; i++)
		s[depth][offset + left + i] = b[i];

	if (depth && is_left)
	{
		for (int i = 0; i < width + right; i++)
			s[depth - 1][offset + left + width / 2 + i] = '-';
		s[depth - 1][offset + left + width / 2] = '.';
	}
	else if (depth && !is_left)
	{
		for (int i = 0; i < left + width; i++)
			s[depth - 1][offset - width / 2 + i] = '-';
		s[depth - 1][offset + left + width / 2] = '.';
	}
#else
	for (int i = 0; i < width; i++)
		s[2 * depth][offset + left + i] = b[i];
	if (depth && is_left)
	{
		for (int i = 0; i < width + right; i++)
			s[2 * depth - 1][offset + left + width / 2 + i] = '-';
		s[2 * depth - 1][offset + left + width / 2] = '+';
		s[2 * depth - 1][offset + left + width + right + width / 2] = '+';
	}
	else if (depth && !is_left)
	{
		for (int i = 0; i < left + width; i++)
			s[2 * depth - 1][offset - width / 2 + i] = '-';
		s[2 * depth - 1][offset + left + width / 2] = '+';
		s[2 * depth - 1][offset - width / 2 - 1] = '+';
	}
#endif
	return (left + width + right);
}

/**
 * binary_tree_print - Prints a binary tree
 *
 * @tree: Pointer to the root node of the tree to print
 */
void binary_tree_print(const binary_tree_t *tree)
{
	char s[20][255];

	for (int i = 0; i < 20; i++)
	{
		sprintf(s[i], "%80s", " ");
	}
	print_t(tree, 0, 0, 0, s);
	for (int i = 0; i < 20; i++)
	{
		printf("%s\n", s[i]);
	}
}

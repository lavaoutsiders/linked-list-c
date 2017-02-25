#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "list.h"

// ==================== Dubbel Gelinkte Lijst ====================
struct DListNode * dlist_node_create(int value, struct DListNode *prev, struct DListNode *next);
int is_number_valid(struct DList *list, int index);
struct DListNode * go_to_node_index(struct DList *dlist, int index);
void append_empty_node(struct DList *dlist, int value);
// Create an empty list
//
// Python: list = []
struct DList * dlist_create()
{
	struct DList *dlist = (struct DList *) malloc(sizeof(struct DList));
	dlist->first = NULL;
	dlist->last = NULL;
	dlist->length = 0;
	return dlist;
}
/// <Summary> Create a listNode with specified values and pointers to prev and next node
/// <Returns> Pointer to the new created DListNode 
struct DListNode * dlist_node_create(int value, struct DListNode *prev, struct DListNode *next){
	struct DListNode *dlistNode = (struct DListNode *) malloc(sizeof(struct DListNode));
	dlistNode->value = value;
	dlistNode->prev = prev;
	dlistNode->next = next;
	return dlistNode;
}

/// <Summary> Returns the pointer of the node in the desired index
struct DListNode * go_to_node_index(struct DList *dlist, int index){
	struct DListNode *currentNode = dlist->first;
	for (int i = 0; i < index; i++){
		// Go to the desired index
		currentNode = currentNode->next;
	}
	return currentNode;
}

// Print a human-readable representation of the given list
//
// Python: print(list)
void dlist_print(struct DList *dlist)
{
	printf("[");

	struct DListNode *current = dlist->first;

	while (current != NULL)
	{
		printf("%d", current->value);

		// no comma after last value
		if (current->next != NULL)
			printf(", ");

		current = current->next;
	}

	printf("]\n");
}

// Delete the given list
//
// Python: del list
void dlist_delete(struct DList *dlist)
{
	struct DListNode *curr = dlist->first;

	while (curr != NULL) {
		struct DListNode* todel = curr;
		curr = curr->next;
		free(todel);
	}
	
	free(dlist);
}

// Print the elements of the list in reverse order. For example, if the list contains
// the numbers 3, 7, and 1, it should print "[1, 7, 3]\n".
//
// Python: print(list[::-1])
void dlist_print_reverse(struct DList *dlist)
{
	printf("[");

	struct DListNode *current = dlist->last;

	while (current != NULL)
	{
		printf("%d", current->value);

		// no comma after last value
		if (current->prev != NULL)
			printf(", ");

		current = current->prev;
	}

	printf("]\n");
}

// Return the length of the given list (i.e., the number of values in it)
//
// Python: length = len(list)
int dlist_length(struct DList *dlist)
{
	/*
	int lenght = 0;
	struct DListNode *current = dlist->first;
	while (current != NULL){
		length++;
		current = current->next;
		//TODO Check if this function is right
	}*/
	return dlist->length;
}
/// Checks if the given index is valid in the range
//  @Param index: the given index to be checked
int is_number_valid(struct DList *list, int index){
	if (index < 0 || index > dlist_length(list)){
		return 0;
	}
	return 1;
}
// Return the value of the element at the given index. If the given index is out of
// range, the memory location pointed to by error is set to 1 (and the value zero
// is returned), otherwise the memory location pointed to by error is set to 0.
//
// Python: value = list[i]
// (An IndexError would correspond to a return value of 0)
int dlist_get(struct DList *list, int index, int *error)
{
	// 0 = false
	if (is_number_valid(list,index) == 0 || dlist_length(list) == 0){
		*error = 1;
		return 0;
	}
	else{
		*error = 0;
		struct DListNode *currentNode = list->first;
		for (int i = 0; i < index; i++){
			currentNode = currentNode->next;
		}
		//TODO check if the right element is returned
		return currentNode->value;
	}
}
// Append an empty node (with no pointers)
void append_empty_node(struct DList *dlist,int value){
	dlist->length++;
	dlist->first = dlist_node_create(value, NULL, NULL);
	dlist->last = dlist->first;
}

// Append the given value to the given list
//
// Python: list.append(value)
void dlist_append(struct DList *dlist, int value)
{
	if (dlist_length(dlist) == 0){
		append_empty_node(dlist, value);
	}
	else{
	dlist->length++;
	dlist->last->next = dlist_node_create(value, dlist->last, NULL);	
	dlist->last = dlist->last->next;
	}
}

// Prepend the value to the front of the list.
//
// Python: list.insert(0, value)
void dlist_prepend(struct DList *dlist, int value)
{
	if (dlist_length(dlist) == 0){
		append_empty_node(dlist, value);
	}
	else{
		dlist->first->prev = dlist_node_create(value, NULL, dlist->first);
		dlist->first = dlist->first->prev;
		dlist->length++;
	}
}


// Insert the element before the given index in the list. A negative index
// means the element should be added to the front (prepended). An index that
// is too high means the element should be added to the back (appended).
//
// Python: list.insert(index, value)
// (Note that the behavior for negative indices differs slightly in Python)
void dlist_insert(struct DList *dlist, int index, int value)
{
	if (index <= 0){
		dlist_prepend(dlist,value);
	}
	else if(index > dlist_length(dlist)){
		dlist_append(dlist,value);
	}
	else{
		
		if (dlist_length(dlist) == 0){
			append_empty_node(dlist, value);
		}
		else{
		struct DListNode *currentNode = go_to_node_index(dlist,index);
		struct DListNode *newNode = dlist_node_create(value, currentNode->prev, currentNode);
		currentNode->prev->next = newNode;
		currentNode->prev = newNode;

		dlist->length++;
		}
	}
}

// Remove the element at the given index from the given list. If the given index
// is out of range, 0 is returned, otherwise 1 is returned.
//
// Python: del list[i]
// (An IndexError would correspond to a return value of 0)
int dlist_remove(struct DList *dlist, int index)
{
	int lenDlist = dlist_length(dlist);
	if (is_number_valid(dlist,index) == 0 || lenDlist == 0){
		return 0;
	}
	dlist->length--;

	struct DListNode *nodeToDelete = go_to_node_index(dlist, index);

	// If the index to be removed is the total length of the dlist
	if (index >= 1){
		// Make sure that the previous node has the correct next pointer
		nodeToDelete->prev->next = nodeToDelete->next;
	
		// If the length of the dlist is same as the index
		if (lenDlist == index + 1){
			// Then make sure that the last of dlist is set point to the previous element

			dlist->last = go_to_node_index(dlist, index-1);
		}
	}
	// index = 0 
	else{
		if (lenDlist == 1){
			dlist->first = NULL;
			dlist->last = NULL;
			free(nodeToDelete);
			return 1;
		}
		if (nodeToDelete->next != NULL){
			dlist->first = nodeToDelete->next;
			nodeToDelete->next->prev = NULL;
		}
		else{
			dlist->first = dlist->first->next;
		}
		free(nodeToDelete);
		return 1;
	}

	if (nodeToDelete->next != NULL){
		// Make sure that the next node has the correct prev pointer
		nodeToDelete->next->prev = nodeToDelete->prev;
		free(nodeToDelete);
	}
	else{
		nodeToDelete->prev->next = NULL;
		free(nodeToDelete);
	}
	return 1;
}

// Insert the value at the correct position in a sorted list. Assume that the list
// is sorted from lowest to highest (ascending). The list must remain sorted!
void dlist_insert_sorted(struct DList *dlist, int value)
{
	int lenDlist = dlist_length(dlist);
	if (lenDlist == 0){
		dlist_prepend(dlist,value);
		return;
	}
	else if (lenDlist == 1){
		if (value >= dlist->first->value){
			dlist_append(dlist, value);
		}
		else{
			dlist_prepend(dlist, value);
		}
		return;
	}
	else if (lenDlist == 2){
		if (dlist->first->value >= value){
			dlist_prepend(dlist,value);
		}
		else if (dlist->first->value <= value && value <= dlist->first->next->value){
			dlist_insert(dlist, 1, value);
		}
		else{
			dlist_append(dlist,value);
		}
		return;

	}
	struct DListNode *currentNode = dlist->first;
	for (int i = 0; i < dlist_length(dlist); i++){
		
		// if the current value is smaller, and the next value is greater
		if (currentNode->value <= value && currentNode->next->value >= value){
			dlist_insert(dlist, i + 1, value);
			return;
		}

		currentNode = currentNode->next;
	}
}

// Remove all values in the list that lie between lower and upper. That is, every value
// for which `lower <= value <= upper` is true, is removed from the list.
void dlist_remove_valuerange(struct DList *dlist, int lower, int upper)
{
	//struct DListNode *currentNode = dlist->first;
	int indexLower = -1;
	int indexUpper = -1;
	if (lower > upper){
		return;
	}
	// Find the lower index
	for (int i = 0; i < dlist_length(dlist);i++){
		if (go_to_node_index(dlist,i)->value >= lower){
			indexLower = i;
			break;
		}
	}
	// Find the higher index
	for(int i = indexLower; i < dlist_length(dlist);i++){
		int indexValue = go_to_node_index(dlist,i)->value;
		if (indexValue == upper){
			indexUpper = i;
			break;
		}
		else if (indexValue > upper){
			indexUpper = i - 1;
			break;
		}
		else{
			// if upper not found
			indexUpper = -2;
		}
	}
	// if there is no element with lower value
	// then delete nothing
	if (indexLower == -1){
		return;
	}
	// if the given value is greater than all element
	// then delete all elements from the lowerindex
	if (indexUpper == -2){
		indexUpper = dlist_length(dlist)-1;
	}

	int indexToRemove = indexLower;
	for (int i = indexLower; i <= indexUpper; i++){
		// Delete the same index, because the list is shifted to left
		dlist_remove(dlist, indexToRemove);
	}
}

// ==================== Binaire boom ====================
struct TreeNode * empty_tree_node_create(char operator, int value);
struct TreeNode * tree_node_create(char operator, int value, struct TreeNode * leftNode, struct TreeNode * rightNode);
struct TreeNode * tree_node_copy(struct TreeNode *treeNode);
struct Tree * tree_create(struct TreeNode *topNode)
{
	struct Tree *tree = (struct Tree *)malloc(sizeof(struct Tree));
	tree->top = topNode;
	return tree;
}

// Print the TreeNode as an infix expression using recursion
static void tree_print_node(struct TreeNode *node)
{
	if (node == NULL){
		return;
	}
	if (node->operator == '\0')
	{
		printf("%d", node->value);
	}
	else
	{
		printf("(");
		tree_print_node(node->left);
		printf(" %c ", node->operator);
		tree_print_node(node->right);
		printf(")");
	}
}

// Print the binary tree as an infix pression
void tree_print(struct Tree *tree)
{
	tree_print_node(tree->top);
	printf("\n");
}

// Delete the TreeNode and all its children, children of children, and so on
//
// Hint: This is somewhat similar to the function tree_print_node, where the function
//       recursively calls itself to print the left and right nodes (if not equal to NULL).
static void tree_delete_node(struct TreeNode *node){

	if (node == NULL){
		return;
	}
	tree_delete_node(node->left);
	tree_delete_node(node->right);
	free(node);
	node = NULL;
}

// Creates a tree node without pointing left and right tree node
struct TreeNode * empty_tree_node_create(char operator, int value){
	struct TreeNode * newTreeNode = (struct TreeNode *) malloc(sizeof(struct TreeNode));
	if (operator == '\0'){
		newTreeNode->value = value;
		newTreeNode->operator = operator;
	}
	else{
		newTreeNode->operator = operator;
		newTreeNode->value = 0;
	}
	newTreeNode->left = NULL;
	newTreeNode->right = NULL;
	return newTreeNode;
}
// Creates a tree node with the specified values and points to the left and right tree nodes
struct TreeNode * tree_node_create(char operator, int value, struct TreeNode * leftNode, struct TreeNode * rightNode){
	struct TreeNode * newTreeNode = empty_tree_node_create(operator, value);
	newTreeNode->left = leftNode;
	newTreeNode->right = rightNode;
	return newTreeNode;
}
// Delete the binary tree and all its children, children of children, and so on.
void tree_delete(struct Tree *tree)
{
	tree_delete_node(tree->top);
	free(tree);
	tree = NULL;
}
// Copies all under nodes from the given tree node
struct TreeNode * tree_node_copy(struct TreeNode *treeNode){
	if (treeNode == NULL){
		return NULL;
	}
	struct TreeNode * newTreeNode = empty_tree_node_create(treeNode->operator, treeNode->value);
	newTreeNode->left = tree_node_copy(treeNode->left);
	newTreeNode->right = tree_node_copy(treeNode->right);
	return treeNode;
}
// Make a copy of the tree and return this copy. Remember that, for all functions you have
// to implement, you are allowed to use helper functions and recursion.
struct Tree * tree_copy(struct Tree *tree)
{

	struct Tree * treeCopy = malloc(sizeof(struct Tree));
	treeCopy->top = tree_node_copy(tree->top);
	return treeCopy;

	
}

// Create a node from a value. The fields left and right must be set so NULL. The field
// operator must be set to '\0'.
struct TreeNode * tree_node_from_value(int value)
{
	return empty_tree_node_create('\0', value);
}

// Create a node from an operator and it's two operands. The operator is given as an ASCII character,
// while the operands are given as nodes.
//
// Note that the newly created node becomes owner of the left and right nodes. That is, when the
// created (returned) node is freed, the given left and right node will also be freed.
struct TreeNode * tree_node_from_operator(char operator, struct TreeNode *left, struct TreeNode *right)
{
	return tree_node_create(operator, 0, left, right);
}
// Evaluates the tree
int tree_node_evaluate(struct TreeNode *treeNode, int *error){
	*error = 0;
	if (treeNode->operator == '\0'){
		return treeNode->value;
	}
	switch (treeNode->operator){
		
		case '+':
			return tree_node_evaluate(treeNode->left, error) + tree_node_evaluate(treeNode->right, error);
		case '-':
			return tree_node_evaluate(treeNode->left, error) - tree_node_evaluate(treeNode->right, error);
		case '/':
			if (treeNode->right->value == 0){
		 		*error = 1;
		 		return 0;
		 	}
			return tree_node_evaluate(treeNode->left, error) / tree_node_evaluate(treeNode->right, error);
		case '*':
			return tree_node_evaluate(treeNode->left, error) * tree_node_evaluate(treeNode->right, error);
		default:
			// if the symbol is not one of the above defined symbol, then there is an error. 
			*error = 1;
			return 0;
	}
}


// Evaluate the binary expression tree given in parameter `tree`.
//
// Returns the value of the expression. If there was an error while evaluating the
// expression, zero is returned, and the memory pointed to by error is set to one.
// If there were no errors, the memory pointed to by error is set to zero.
int tree_evaluate(struct Tree *tree, int *error)
{
	return tree_node_evaluate(tree->top, error);
}
// ==================== Stacks ====================
struct StackNode * stack_node_empty_create(struct TreeNode * treeNode);;
void stack_node_delete(struct StackNode *stackNode);
// Create an empty stack
struct Stack * stack_create()
{
	struct Stack * newStack = (struct Stack *) malloc(sizeof(struct Stack));
	newStack->top = NULL;
	return newStack;
}
// Creates a new stack with the pointer to the next stack node
struct StackNode * stack_node_create(struct TreeNode * treeNode, struct StackNode * stackNode){
	struct StackNode * newStackNode = (struct StackNode *) malloc(sizeof(struct StackNode));
	newStackNode->node = treeNode;
	newStackNode->next = stackNode;
	return newStackNode;
}
// Push a TreeNode on the stack
void stack_push(struct Stack* stack, struct TreeNode *node)
{
	// if there is no element is the stack
	if (stack_isempty(stack)){
		stack->top = stack_node_create(node, NULL);
		return;
	}
	stack->top = stack_node_create(node, stack->top);
}

// Get the last TreeNode that was added to the stack and return it. If the stack is empty
// the memory location pointed to by error is set to 1 and NULL is returned. Otherwise the
// memory location pointed to by error is set to 0 and the last added node is returned.
struct TreeNode * stack_pop(struct Stack *stack, int *error)
{
	if (stack_isempty(stack)){
		*error = 1;
		return NULL;
	}
	*error = 0;
	struct TreeNode *topStackNode = stack->top->node;
	stack->top = stack->top->next;
	return topStackNode;
}

// Returns 1 if the stack is empty (i.e. there are no nodes to pop).
// Otherwise it returns 0.
int stack_isempty(struct Stack *stack)
{
	if (stack->top == NULL){
		return 1;
	}
	return 0;
}
void stack_node_delete(struct StackNode *stackNode){
	if (stackNode == NULL){
		return;
	}
	stack_node_delete(stackNode->next);
	free(stackNode);
	stackNode = NULL;
}
// Delete the given stack. When deleting a TreeNode, all its descendants (children nodes,
// children of children nodes, and so on) must also be deleted.
void stack_delete(struct Stack *stack)
{
	stack_node_delete(stack->top);
	free(stack);
	stack = NULL;
}

// Convert the postfix expression given in parameter `formula` to a binary expression tree.
//
// Returns NULL if `formula` is an invalid postfix expression. Otherwise it returns the binary
// tree representing the expression.

int count_int_length(int value);
int simple_calculator(int rightOperand, int leftOperand, char operator, int * error);
int simple_calculator(int rightOperand, int leftOperand, char operator, int * error){
	switch(operator){
		 case '+':
		 	return leftOperand + rightOperand;
		 case '-':
		 	return leftOperand - rightOperand;
		 case '*':
		 	return leftOperand * rightOperand;
		 case '/':
		 	if (rightOperand == 0){
		 		*error = 1;
		 		return 0;
		 	}
		 	return leftOperand / rightOperand;
		 default:
		 	*error = 1;
		 	return -1;	
		 }
}
int count_int_length(int value){
	int count = 0;
	if (value < 0){
		count++;
	}
	while(value != 0)
    {
        value /= 10;
        count++;
    }
    return count;
}


// Convert the postfix expression given in parameter `formula` to a binary expression tree.
//
// Returns NULL if `formula` is an invalid postfix expression. Otherwise it returns the binary
// tree representing the expression.
struct Tree * tree_from_expression(const char *formula)
{	
	int error = 0;
	if (strlen(formula) == 0){
		return NULL;
	}
	struct Tree * expressionTree = tree_create(NULL);
	struct Stack * expressionStack = stack_create();
	int i = 0;
	while (i < strlen(formula)){
		
		if (isdigit((int)formula[i])){
			int formulaInt = atoi(&formula[i]);
			// if the formula int is 0
			if (formulaInt == 0){
					i++;
			}
			i += count_int_length(formulaInt) - 1; // -1 because at the end, i will be added with 1 
			struct TreeNode * expressionTreeNode = tree_node_from_value(formulaInt);
			stack_push(expressionStack, expressionTreeNode);
		}
		else if (formula[i] == ' '){
			// Ignore spaces
		}
		// if it is a negative number
		else if ((formula[i] == '-' && formula[i+1]!= ' ' ) && (formula[i] == '-' && formula[i+1]!= '\0')){
				int formulaInt = atoi(&formula[i]);
				if (formulaInt == 0){
					i++;
				}
				i += count_int_length(formulaInt) - 1; // -1 because at the end, i will be added with 1 
				struct TreeNode * expressionTreeNode = tree_node_from_value(formulaInt);
				stack_push(expressionStack, expressionTreeNode);
		
		}
		else if (formula[i] == '+' || formula[i] == '-'|| formula[i] == '*' || formula[i] == '/'){
			
			if (stack_isempty(expressionStack)){
				tree_delete(expressionTree);
				return NULL;
			}
			struct TreeNode * secondValueNode = stack_pop(expressionStack,&error);
			// checks if the stack is empty before the second pop operation
			if (stack_isempty(expressionStack)){
				tree_delete(expressionTree);
				return NULL;
			}
			struct TreeNode * operatorNode = tree_node_from_operator(formula[i],stack_pop(expressionStack, &error),secondValueNode);
			stack_push(expressionStack, operatorNode);
		}
		else if (formula[i] !='\0'){
			// If other symbol is filled in, then return NULL;
			tree_delete(expressionTree);
			return NULL;
		}
		i++;
	}
	expressionTree->top = stack_pop(expressionStack, &error);
	if (stack_isempty(expressionStack) != 1){
		// after pop the last element, the stack should be empty
		tree_delete(expressionTree);
		return NULL;
	}
	return expressionTree;
}
void tree_node_simplify(struct TreeNode *treeNode, int *error){
	if (treeNode == NULL){
		return;
	}
	if (treeNode->operator != '\0'){
		if (treeNode->left->operator == '\0' && treeNode->right->operator == '\0'){
			int value = simple_calculator(treeNode->right->value, treeNode->left->value,treeNode->operator, error);
			if (*error == 1){
				return;
			}
			struct TreeNode * newNode = tree_node_from_value(value);
			tree_delete_node(treeNode->left);
			tree_delete_node(treeNode->right);
			*treeNode = *newNode;
			return;
			}		
	}
	tree_node_simplify(treeNode->left, error);
	tree_node_simplify(treeNode->right, error);

}
// Simplify the binary expression tree by replacing all operations on leaf nodes (i.e. values) by
// the result of the expression. For example, the expression `(1+(1+(1+1)))` is simplified to
// `(1+(1+2))`. Similarly, the expression `(1+((1+1)+1))` is simplified to `(1+(2+1))`. It can
// also happen that multiple operations can be simplified (i.e. there are multiple nodes where both
// the left and right node are values). For example, the expression `(((1+1)+1)+(1+(1+1)))` should
// be simplified to `((2+1)+(1+2))`.
//
// The tree is left unmodified if it cannot be simplified.
void tree_simplify_onestep(struct Tree *tree)
{
	int error = 0;
	tree_node_simplify(tree->top, &error);
	// If there is a calculation error, e.g. division by 0
	if (error == 1){
		tree = NULL;
	}
}

// Simplify the binary expression tree until it can no longer be simplified. Print out the tree after
// after each simplification. For example, when given the tree `(((1+1)+1)+(1+(1+1)))`, it should print:
//
//		(((1+1)+1)+(1+(1+1)))
//		((2+1)+(1+2))
//		(3+3)
//		6
//
// The tree given in the parameter `tree` should not be modified!
// Hint: use functions that you previously created/implemented.
void tree_evaluate_showsteps(struct Tree *tree, int *error)
{
	while (tree->top->operator != '\0'){
		tree_node_simplify(tree->top, error);
		tree_print(tree);
	}
}




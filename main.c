#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
int test_dlist()
{
	int error = 0;
	struct DList *dlist = dlist_create();

	if (dlist_length(dlist) != 0) {
		printf("dlist_length of empty dlist should be zero\n");
		return 0;
	}


	// Insert value 101 and test functions
	dlist_insert(dlist, 0, 101);
	if (dlist_length(dlist) != 1) {
		printf("dlist_length should be 1\n");
		return 0;
	}

	if (dlist_get(dlist, 0, &error) != 101) {
		printf("dlist_get should return value 101E\n");
		return 0;
	}
	if (error != 0) {
		printf("error in dlist_get (1)\n");
		return 0;
	}


	// Insert value 202 and test functions
	dlist_insert(dlist, 0, 202);
	if (dlist_length(dlist) != 2) {
		printf("dlist_length should return 2\n");
		return 0;
	}

	if (dlist_get(dlist, 0, &error) != 202) {
		printf("dlist_get should return 202\n");
		return 0;
	}
	if (error != 0) {
		printf("Error in dlist_length (2)\n");
		return 0;
	}


	// Test remove function
	if (dlist_remove(dlist, 1) == 0) {
		printf("Error in dlist_remove\n");
		return 0;
	}
	if (dlist_length(dlist) != 1) {
		printf("dlist_length should return 1 (after remove)\n");
		return 0;
	}

	

	// Test prepend function
	dlist_prepend(dlist, 34);
	if (dlist_length(dlist) != 2) {
		printf("dlist_length should return 2 (after prepend)\n");
		return 0;
	}
	if (dlist_get(dlist, 0, &error) != 34) {
		printf("dlist_get should return 34 (after prepend)\n");
		return 0;
	}
	if (error != 0) {
		printf("Error in dlist_prepend (could not get value)\n");
		return 0;
	}

	// Test insert sorted function
	dlist_insert_sorted(dlist, 25);
	if (dlist_get(dlist, 0, &error) != 25){
		printf("dlist_insert_sorted should return 25 (after insert value 25), get %d\n",dlist_get(dlist, 0, &error));
	}
	dlist_insert_sorted(dlist, 200);
	if (dlist_get(dlist, 2, &error) != 200){
		printf("dlist_insert_sorted should return 200 (after insert value 200), get %d\n",dlist_get(dlist, 2, &error));
	}

	// Test remove value range function
	dlist_remove_valuerange(dlist, 34, 200);
	if (dlist_length(dlist) != 2){
		printf("after dlist_remove_valuerange, there should be 2 elements in the list (after removing value between 34 and 200), get %d\n",dlist_length(dlist));
	}
	if (dlist_get(dlist, 1, &error) != 202){
		printf("after dlist_remove_valuerange, the element with index 1 should be 202 (after removing value between 34 and 200), get %d\n",dlist_get(dlist, 1, &error));
	}
	dlist_remove_valuerange(dlist, 203, 400);
	if (dlist_length(dlist) != 2){
		printf("after dlist_remove_valuerange, there should be 2 elements in the list (after removing value between 203 and 400), get %d\n",dlist_length(dlist));
	}
	dlist_remove_valuerange(dlist, -5, 400);
	if (dlist_length(dlist) != 0){
		printf("after dlist_remove_valuerange, there should be 0 elements in the list (after removing value between -5 and 400), get %d\n",dlist_length(dlist));
	}
	// Test insert function
	// Negative index
	dlist_insert(dlist,-1,2);
	if (dlist_length(dlist) != 1){
		printf("after dlist_insert, there should be 1 elements in the list (after inserting 2 in index -1), got %d\n",dlist_length(dlist));
	}
	if (dlist_get(dlist, 0, &error) != 2){
		printf("after dlist_insert, the element with index 0 should be 2 (after inserting 2 in index -1), got %d\n",dlist_get(dlist, 1, &error));
	}

	dlist_insert_sorted(dlist, -6);
	if (dlist_get(dlist, 0, &error) != -6){
		printf("dlist_insert_sorted should return -6 (after insert value -6), got %d\n",dlist_get(dlist, 0, &error));
	}

	dlist_insert_sorted(dlist, 70);
	if (dlist_get(dlist, 2, &error) != 70){
		printf("dlist_insert_sorted should return 70 (after insert value 70), got %d\n",dlist_get(dlist, 2, &error));
	}
	dlist_insert_sorted(dlist, 8);
	if (dlist_get(dlist, 2, &error) != 8){
		printf("dlist_insert_sorted should return 8 (after insert value 8), got %d\n",dlist_get(dlist, 2, &error));
	}
	dlist_print(dlist);
	dlist_print_reverse(dlist);
	// Testing deleting -6 and 2
	dlist_remove_valuerange(dlist, -8,7);
	if (dlist_get(dlist, 1, &error) != 70){
		printf("after dlist_remove_valuerange, the element with index 1 should be 70 (after removing value between -8 and 7), got %d\n",dlist_get(dlist, 1, &error));
	}
	// Repeat action
	dlist_remove_valuerange(dlist, -8,7);
	if (dlist_get(dlist, 1, &error) != 70){
		printf("after dlist_remove_valuerange, the element with index 1 should be 70 (after removing value between -8 and 7), got %d\n",dlist_get(dlist, 1, &error));
	}
	dlist_insert_sorted(dlist, -7);
	if (dlist_get(dlist, 0, &error) != -7){
		printf("dlist_insert_sorted should return -7 (after insert value -7), got %d\n",dlist_get(dlist, 0, &error));
	}
	// dlist bevat -7 8 70
	dlist_remove_valuerange(dlist,7,69);
	if (dlist_get(dlist, 1, &error) != 70){
		printf("after dlist_remove_valuerange, the element with index 1 should be 70 (after removing value between -8 and 7), got %d\n",dlist_get(dlist, 1, &error));
	}
	if (dlist_length(dlist) != 2){
		printf("after dlist_remove_valuerange, there should be 2 elements in the list\n");
	}
	dlist_print(dlist);
	dlist_print_reverse(dlist);
	

	return 1;
}


int test_tree()
{
	int value, error;

	struct TreeNode *valueNode1 = tree_node_from_value(6);
	struct TreeNode *valueNode2 = tree_node_from_value(10);
	struct TreeNode *operatorNode = tree_node_from_operator('+', valueNode1, valueNode2);
	struct Tree *tree = tree_create(operatorNode);

	tree_print(tree);
	value = tree_evaluate(tree, &error);
	if (error != 0) {
		printf("An error occurred while evaluting the example tree\n");
		return 0;
	}
	if (value != 16) {
		printf("Error while evaluating value of example tree: got %d but expected 16\n", value);
		return 0;
	}
	struct TreeNode *rightValueLeft = tree_node_from_value(8);
	struct TreeNode *rightValueRight = tree_node_from_value(-4);
	struct TreeNode *leftNode = tree_node_create('*','0',valueNode1,valueNode2);
	struct TreeNode *rightNode = tree_node_create('/','0',rightValueLeft,rightValueRight);
	struct TreeNode *topNode = tree_node_create('-','0',leftNode,rightNode);
	struct Tree *evaluatingTree = tree_create(topNode);
	tree_print(evaluatingTree);
	value = tree_evaluate(evaluatingTree, &error);
	if (error != 0) {
		printf("An error occurred while evaluting the example tree\n");
		return 0;
	}
	if (value != 62) {
		printf("Error while evaluating value of example tree: got %d but expected 62\n", value);
		return 0;
	}
	// Testing tree copy function
	struct Tree *treeCopy = tree_copy(evaluatingTree);
	if (value != tree_evaluate(treeCopy, &error)){
		printf("Error while evaluating value of the copied tree: got %d but expected 62\n", value);
		return 0;
	}

	return 1;
}

int test_stack()
{
	int error = 0;
	struct Stack * testStack = stack_create();
	struct TreeNode *firstValueNode = tree_node_from_value(8);
	struct TreeNode *secondValueNode = tree_node_from_value(9);

	if (stack_isempty(testStack) != 1){
		printf("Error while testing with function stack_isempty, testStack should be empty, got not empty.\n");
	}

	// Testing push stack
	stack_push(testStack, firstValueNode);
	if (testStack->top->node != firstValueNode){
		printf("Error while pushing on stack, the top node of the stack should be %p, got %p\n", 
			firstValueNode, testStack->top->node); 
	}
	stack_push(testStack, secondValueNode);
	if (testStack->top->node != secondValueNode){
		printf("Error while pushing on stack, the top node of the stack should be %p, got %p\n", 
			secondValueNode, testStack->top->node); 
	}
	if (testStack->top->next->node != firstValueNode){
		printf("Error while pushing on stack, the second/ last node of the stack should be %p, got %p\n", 
			firstValueNode, testStack->top->next->node); 
	}

	if (stack_isempty(testStack) != 0){
		printf("Error while testing with function stack_isempty, testStack should not be empty, got empty.\n");
	}
	// Testing pop stack
	struct TreeNode *popTreeNode = stack_pop(testStack, &error);
	if (popTreeNode != secondValueNode){
		printf("Error while testing with function stack_pop, the return node should be %p, got %p\n", 
			secondValueNode, popTreeNode);
	}
	popTreeNode = stack_pop(testStack, &error);
	if (popTreeNode != firstValueNode){
		printf("Error while testing with function stack_pop, the return node should be %p, got %p\n", 
			firstValueNode, popTreeNode);
	}

	if (stack_isempty(testStack) != 1){
		printf("Error while testing with function stack_pop, testStack should be empty, got not empty.\n");
	}
	popTreeNode = stack_pop(testStack, &error);
	if (error != 1){
		printf("Error while testing with function stack_pop, the error code should be 1, because it is an empty stack, got %d\n", error);
	}

	// Testing stack_delete function
	stack_push(testStack, firstValueNode);
	if (testStack->top->node != firstValueNode){
		printf("Error while pushing on stack, the top node of the stack should be %p, got %p\n", 
			firstValueNode, testStack->top->node); 
	}
	stack_delete(testStack);
	return 1;
}
int test_expression(const char *expression, int expected)
{
	struct Tree *tree;
	int value, error;

	printf(">>> Testing expression: %s\n", expression);

	// Constructing tree and evaluating it
	tree = tree_from_expression(expression);
	if (tree == NULL) {
		printf("Failed to construct expression tree for %s\n", expression);
		return 0;
	}

	tree_print(tree);
	value = tree_evaluate(tree, &error);
	if (error != 0) {
		printf("Error argument set on evaluation of %s\n", expression);
		tree_delete(tree);
		return 0;
	}
	if (value != expected) {
		printf("Failed to evaluate %s to %d (got %d instead)\n", expression, expected, value);
		tree_delete(tree);
		return 0;
	}

	// Simplify until the top of the tree does not contain operator anymore (contains the result)
	
	while (tree->top->operator != '\0'){
		tree_simplify_onestep(tree);
		tree_print(tree);
		value = tree_evaluate(tree, &error);
		if (error != 0) {
			printf("Error argument set on evaluation of %s after simplifying tree\n", expression);
			tree_delete(tree);
			return 0;
		}
		if (value != expected) {
			printf("Failed to evaluate %s to %d after simplifying tree (got %d instead)\n",
				expression, expected, value);

			tree_delete(tree);
			return 0;
		}
	}

	tree_delete(tree);
	return 1;
}


int test_many_expressions()
{
	if (!test_expression("10", 10))
		return 0;

	if (!test_expression("6 4 +", 10))
		return 0;

	if (!test_expression("6 4 + 10 *", 100))
		return 0;

	if (!test_expression("6 4 + 10 * 1 -", 99))
		return 0;

	if (!test_expression("6 4 + -10 * 1 -", -101))
		return 0;

	// Testing multipication with 0
	if (!test_expression("6 4 + -1 + 0 *", 0))
		return 0;

	if (!test_expression("6 4 + 0 + 1 -", 9))
		return 0;

	
	if (!test_expression("1 1 + 1 + 1 1 1 + + +", 6))
		return 0;

	if (!test_expression("-1 1 + -1 + 1 1 1 + + +", 2))
		return 0;

	// Testing devision by 0
	// Gives error argument set on evaluation of 6 4 + 10 * 0 / which is great

	if (!test_expression("6 4 + 10 * 0 /", 0));
	// Testing invalid expression
	if (!test_expression("6 4 + -10 * 1 - - - - -", 0));
	if (!test_expression("a-1 1 + a1 + 1 1 1 + + +", 0))
		return 0;

	return 1;
}
int main(int argc, char *argv[])
{
	test_dlist();
	test_tree();
	test_stack();
	test_many_expressions();
	return 0;
}
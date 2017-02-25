// ==================== Dubbel Gelinkte Lijst ====================

struct DListNode {
	int value;
	struct DListNode *prev;
	struct DListNode *next;
};

struct DList {
	struct DListNode *first;
	struct DListNode *last;
	int length;
};

struct DList * dlist_create();
void dlist_print(struct DList *dlist);
void dlist_delete(struct DList *dlist);

void dlist_print_reverse(struct DList *dlist);
int dlist_length(struct DList *dlist);
int dlist_get(struct DList *list, int index, int *error);
void dlist_append(struct DList *dlist, int value);
void dlist_prepend(struct DList *dlist, int value);
void dlist_insert(struct DList *dlist, int index, int value);
int dlist_remove(struct DList *dlist, int index);

void dlist_insert_sorted(struct DList *list, int value);
void dlist_remove_valuerange(struct DList *list, int lower, int upper);



// ==================== Binaire boom ====================

struct TreeNode {
	// This field contains the operator character (e.g. '-' or '+'). If the TreeNode
	// represents a value, this field should be equal to '\0' (= ascii value zero).
	char operator;
	// Value of the node. If the node is an operator, this field should should be zero.
	int value;

	// Left and right childern of an operator. If the operator field is equal to '\0' then
	// both left and right should be NULL.
	struct TreeNode *left;
	struct TreeNode *right;
};

struct Tree {
	struct TreeNode *top;
};

struct Tree * tree_create(struct TreeNode *topNode);
void tree_print(struct Tree *tree);
void tree_delete(struct Tree *tree);
struct Tree * tree_copy(struct Tree *tree);

struct TreeNode * tree_node_from_value(int value);
struct TreeNode * tree_node_from_operator(char operator, struct TreeNode *left, struct TreeNode *right);

int tree_evaluate(struct Tree *tree, int *error);



// ==================== Stacks ====================

struct StackNode {
	struct TreeNode *node;
	struct StackNode *next;
};

struct Stack {
	struct StackNode *top;
};

struct Stack * stack_create();
void stack_push(struct Stack *stack, struct TreeNode *node);
struct TreeNode * stack_pop(struct Stack *stack, int *error);
int stack_isempty(struct Stack *stack);
void stack_delete(struct Stack *stack);



// ==================== Postfix Expression ====================

struct Tree * tree_from_expression(const char *formula);

void tree_simplify_onestep(struct Tree *tree);
void tree_evaluate_showsteps(struct Tree *tree, int *error);


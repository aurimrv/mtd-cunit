
struct stack_node
{
    struct stack_node *above;
    int data;
    struct stack_node *below;
};

typedef struct stack_node stack_list;
typedef stack_list *stack_link;

void join(stack_link above, stack_link below);
int push(int value);
int pop(void);
int isEmpty(void);
int removeBottom(void);
void print_stack(void);

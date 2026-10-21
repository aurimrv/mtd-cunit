int push(int value)
{
 stack_link new_node;
 size++;
 new_node = (stack_link) malloc(sizeof(stack_list));
 if (!new_node) {@
return 0;@
}
 if (size == 1)
  bottom = new_node;
 new_node->data = value;
 join(new_node, top);
 top = new_node;
 return 1;
}
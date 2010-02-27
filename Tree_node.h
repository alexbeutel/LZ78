
class Tree_node {
public:
	Tree_node();
	Tree_node(char c, int l, Tree_node* par);
	Tree_node* find_child(char c);
	Tree_node* insert_child(char byte, int label);
	void printAll();
	int label; 
	char byte;
	Tree_node *parent;
	Tree_node *first_child;
	Tree_node *sibling;
	bool initialized;
	//Tree_node *children[256];
};
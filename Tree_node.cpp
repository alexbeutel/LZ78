
Tree_node::Tree_node() {
	initialized = false;
	sibling = NULL;
	first_child = NULL;
}
Tree_node::Tree_node(char c, int l, Tree_node* par) {
	initialized = true;
	byte = c;
	label = l;
	parent = par;
	sibling = NULL;
	first_child = NULL;
}

// Tree_node * Tree_node::getLastChild(){
// 	if(first_child == NULL || (&first_child) == NULL) return NULL;
// 	
// 	Tree_node * cur = first_child;
// 	whil(cur != NULL) {
// 		if(cur->byte == c)
// 			return cur;
// 		cur = cur->sibling;
// 	}
// }

Tree_node* Tree_node::find_child(char c){
	if((&first_child) == NULL) return NULL;
	Tree_node * cur = first_child;
	while(cur != NULL) {
		if(cur->byte == c)
			return cur;
		cur = cur->sibling;
	}
	return NULL;
}

Tree_node* Tree_node::insert_child(char byte, int label){
	if(first_child == NULL || !first_child->initialized) {
		first_child = new Tree_node(byte,label,this);
		return first_child;
	} else {
		Tree_node * cur = first_child;
		while(cur->sibling != NULL && cur->sibling->initialized) {
			cur = cur->sibling;
		}
		cur->sibling = new Tree_node(byte,label,this);
		return cur->sibling;
	}
}

void Tree_node::printAll() {
	cout << "label = " << label << "\n";
	cout << "byte = " << byte << "\n";
	cout << "parent = " << (long)parent << "\n";
	cout << "first_child = " << (long)first_child << "\n";
}
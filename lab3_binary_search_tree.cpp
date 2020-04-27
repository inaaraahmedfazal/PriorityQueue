// Inaara Ahmed-Fazal   20821562
// Kayla Jetha          20822795
// Meghan LaCoste       20845775

#include <iostream>
#include <queue>
#include "lab3_binary_search_tree.hpp"

using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree(): root(NULL), size(0){}

// PURPOSE: Explicit destructor of the class BinarySearchTree
BinarySearchTree::~BinarySearchTree() {
	clean_up(root);
	root = NULL;
	size = 0;
}

//PURPOSE: deletes all TaskItems in tree using PostOrder traversal
void BinarySearchTree :: clean_up(BinarySearchTree :: TaskItem* T) {
	if (T == NULL) return;
	clean_up(T->left);
	clean_up(T->right);
	delete T;
}

// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const {
	return size;
}

// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::max() const {
	if(!root)
		return BinarySearchTree::TaskItem(-1, "N/A");
		
	TaskItem* cur = root;
	while(cur && cur -> right){
		cur = cur -> right;
	}
	return *cur;
}

// PURPOSE: Returns the minimum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::min() const {
	if(!root)
		return BinarySearchTree::TaskItem(-1, "N/A");
		
	TaskItem* cur = root;
	while(cur && cur -> left){
		cur = cur -> left;
	}
	return *cur;
}

// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height() const {
	if(!root) return 0;
	//TaskItem* T = root;
	unsigned int h = get_node_depth(root);
	return h;
}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {
	if(root) {
		print_in_order(root);
	}else {
		cout << " " << endl;
	}
}

// PURPOSE: prints all TaskItems with priority and description using InOrder traversal
void BinarySearchTree :: print_in_order(BinarySearchTree :: TaskItem* cur) const{
	if (cur == NULL) return;
	print_in_order(cur -> left);
	cout << "Priority: " << cur -> priority << endl;
	cout << "Description: " << cur -> description << endl;	
	print_in_order(cur -> right);
}

// PURPOSE: Returns true if a node with the value val exists in the tree	
// otherwise, returns false
bool BinarySearchTree::exists( BinarySearchTree::TaskItem val ) const {
	TaskItem* cur = root;
	while(cur) {
		if(*cur == val) return true;
		if(val.priority < cur -> priority) cur = cur -> left;
		else cur = cur -> right;
	}
	return false;
}

// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::TaskItem* BinarySearchTree::get_root_node() {
	if(!root) return NULL;
	TaskItem* cur = root;
	return cur;
}

// PURPOSE: Optional helper function that returns the root node pointer address
BinarySearchTree::TaskItem** BinarySearchTree::get_root_node_address() {
	if(!root) return NULL;
	else return &root;
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth( BinarySearchTree::TaskItem* n ) const {
	if(!n) return -1;
	else return 1 + std :: max(BinarySearchTree :: get_node_depth(n -> left), BinarySearchTree :: get_node_depth(n -> right));
}

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert( BinarySearchTree::TaskItem val ) {
    TaskItem** cur = &root;
    while(*cur) {
    	//avoid duplicates
    	if(**cur == val) return false;
    	
    	if(val.priority < (*cur) -> priority) cur = &((*cur) -> left);
    	else cur = &((*cur) -> right);
	}
	*cur = new TaskItem(val);
	++size;
	return true;
}

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise

//use cases in note (leaf node, node with 1 child, node with 2 children)
bool BinarySearchTree::remove( BinarySearchTree::TaskItem val ) {
	TaskItem* cur = root;
	TaskItem* parent = NULL;
	bool found = false;
	while(cur && !found) { //iterates downward until cur points to node that equals val
		//update cur and parent(?) as you are traversing through tree
		if(val.priority == cur -> priority) found = true;
		else if(val.priority < cur -> priority) {
			parent = cur;
			cur = cur -> left;
		}
		else{
			parent = cur;
			cur = cur -> right;
		}
	}
	if(!cur) return false;
	
	//divide code into cases
	//CASE 1: remove leaf node
	if(!cur -> left && !cur -> right) {
		if(parent) {
			if(parent -> left && parent -> left == cur) {
				parent -> left = NULL;
			}
			else if (parent -> right) {
				parent -> right = NULL;
			}
		}
		else root = NULL;
		delete cur;
		cur = NULL;
		
	//CASE 2: remove node with one child
	} else if (!cur -> left) {
		if(parent) {
			if(parent -> left && parent -> left == cur) {
				parent -> left = cur -> right;
			}
			else if(parent -> right) {
				parent -> right = cur -> right;
			}
		}
		else root = cur -> right;
		delete cur;
		cur = NULL;
	} else if (!cur -> right) {
		if(parent) {
			if(parent -> right && parent -> right == cur) parent -> right = cur -> left;
			else if(parent -> left) parent -> left = cur -> left;
		}
		else root = cur -> left;
		delete cur;
		cur = NULL;
	}
	
	//CASE: remove node with 2 children
	//Use predecessor consistently
	else {
		//find predecessor
		TaskItem* pre = cur -> left;
		TaskItem* pre_parent = cur;
		while(pre && pre -> right) {
			pre_parent = pre;
			pre = pre -> right;
		}
		
		if(cur == root) root = pre;
		
		TaskItem** cur_p = &cur;
		TaskItem** parent_p = &parent;
		TaskItem** pre_p = &pre;
		TaskItem** pre_parent_p = &pre_parent;
		
		//swap node to be removed with predecessor
		swap(cur_p, parent_p, pre_p, pre_parent_p);
		
		//CASE 3.1: remove node with no children
		if(!cur -> left && !cur -> right) {
			if(pre_parent) {
				if(pre_parent -> left && pre_parent -> left == cur) {
					pre_parent -> left = NULL;
				}
				else if (pre_parent -> right) {
					pre_parent -> right = NULL;
				}
			}
			else root = NULL;
			delete cur;
			cur = NULL;
		
		//CASE 3.2: remove node with one child
		} else if (!cur -> left) {
			if(pre_parent) {
				if(pre_parent -> left && pre_parent -> left == cur) {
					pre_parent -> left = cur -> right;
				}
				else if(pre_parent -> right) {
					pre_parent -> right = cur -> right;
				}
			}
			else root = cur -> right;
			delete cur;
			cur = NULL;
		} else if (!cur -> right) {
			if(pre_parent) {
				if(pre_parent -> right && pre_parent -> right == cur) pre_parent -> right = cur -> left;
				else if(pre_parent -> left) pre_parent -> left = cur -> left;
			}
			else root = cur -> left;
			delete cur;
			cur = NULL;
		}
	}
	size--;
    return true;
}

//PURPOSE: swaps two nodes in a bindary tree, given that one is above another in the tree
void BinarySearchTree :: swap (BinarySearchTree :: TaskItem** u, BinarySearchTree :: TaskItem** u_parent, BinarySearchTree :: TaskItem** l, BinarySearchTree :: TaskItem** l_parent) {
	TaskItem* temp_l_left;
	TaskItem* temp_l_right;
	TaskItem* temp_u_left;
	TaskItem* temp_u_right;
	temp_l_left = (*l) -> left;
	temp_l_right = (*l) -> right;
	if((*u) -> left && (*u) -> left != *l) temp_u_left = (*u) -> left;
	else if((*u) -> left) temp_u_left = *u;
	if((*u) -> right) temp_u_right = (*u) -> right;
	if(*u_parent) {
		if((*u_parent) -> left == *u) (*u_parent) -> left = *l;
		else (*u_parent) -> right = *l;
	}
	if((*l_parent) != *u) {
		if((*l_parent) -> left == *l) (*l_parent) -> left = *u;
		else (*l_parent) -> right = *u;
	}
	else *l_parent = *l;
	
	(*l) -> left = temp_u_left;
	(*l) -> right = temp_u_right;	
	(*u) -> left = temp_l_left;
	(*u) -> right = temp_l_right;
	
}

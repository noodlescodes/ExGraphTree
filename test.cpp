#include <cstdlib>
#include <iostream>
#include <ctime>
#include "BTNode.h"
#include "Matrix.h"
#include "Explorer.h"
#include "simpleExplorer.h"

using namespace std;
using namespace VAN_MAASTRICHT;

void generate_children(BTNode<int> *node) {
	node->set_left(new BTNode<int>(node->data() * 10));
	node->set_right(new BTNode<int>(node->data() * 10 + 1));
}

void explore(BTNode<int> *node, int depth) {
	if(node->data() == 100) {
		clear_tree(node->left());
		clear_tree(node->right());
	}
	else {
		generate_children(node);
		if(depth < 3) {
			explore(node->left(), depth + 1);
			explore(node->right(), depth + 1);
		}
	}
}

void print_tree(BTNode<int> *node, int pos) {
	if(node == NULL) {
		for(int i = 0; i < pos; i++) {
			cout << "\t";
		}
		cout << "*" << endl;
	}
	else {
		print_tree(node->right(), pos + 1);
		for(int i = 0; i < pos; i++) {
			cout << "\t";
		}
		cout << node->data() << endl;
		print_tree(node->left(), pos + 1);
	}
}

int main() {
	time_t start = time(NULL);
	Matrix b = Matrix();
	b.set_size(5);
	Explorer *a = new Explorer(new BTNode<Matrix>(b));

	a->explore(a->get_root(), 0, 1, 0);
	cout << "Number of solutions: " << a->get_number_solutions() << endl;
	delete a;
	cout << "Time taken: " << time(NULL) - start << endl;

	//simpleExplorer *b = new simpleExplorer(new BTNode<int>(1));
	//b->explore(b->get_root(), 1);
	//b->print_tree(b->get_root(), 0);
	//clear_tree(b->get_root()->left());
	//clear_tree(b->get_root()->left()->left());
	//clear_tree(b->get_root()->right()->right());
	//b->print_tree(b->get_root(), 0);
	//delete b;

	//BTNode<int> *node = new BTNode<int>(1);
	
	//explore(node, 1);

	//print_tree(node, 0);

	//clear_tree(node);

	return 0;
}

#include "simpleExplorer.h"
#include "BTNode.h"
#include <cstdlib>
#include <iostream>
#include <cmath>

using namespace std;
using VAN_MAASTRICHT::BTNode;

namespace VAN_MAASTRICHT {
	simpleExplorer::simpleExplorer(BTNode<int> *rt) {
		root = rt;
		explored = 0;
		number_of_solutions = 0;
		print_check = print_inc;
		max_to_explore = 0;
	}

	simpleExplorer::~simpleExplorer() {
		clear_tree(root);
	}

	void simpleExplorer::set_root_data(int &m) {
		root->set_data(m);
	}

	BTNode<int>* simpleExplorer::get_root() {
		return root;
	}

	void simpleExplorer::explore(BTNode<int> *node, int depth) {
		generate_children(node);
		if(depth <= 3) {
			explore(node->left(), depth + 1);
			clear_tree(node->left());
			explore(node->right(), depth + 1);
			clear_tree(node->right());
		}
	}

	void simpleExplorer::generate_children(BTNode<int> *node) {
		node->set_left(new BTNode<int>(node->data() * 10));
		node->set_right(new BTNode<int>(node->data() * 10 + 1));
	}

	void simpleExplorer::print() {
		cout << "\t" << root->right()->data() << endl;
		cout << root->data() << endl;
		cout << "\t" << root->left()->data() << endl;
	}

	void simpleExplorer::print_tree(BTNode<int> *node, int pos) {
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
}

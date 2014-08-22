#include "Explorer.h"
#include "BTNode.h"
#include <cstdlib>
#include <iostream>
#include <cmath>

namespace VAN_MAASTRICHT {
	Explorer::Explorer(BTNode<Matrix> *rt) {
		root = rt;
		explored = 1;
		number_of_solutions = 0;
		print_check = print_inc;
		max_edges = 2 * 5;
		if(root->data().size() != 0) {
			max_to_explore = pow(2,(rt->data().size() - 1) * (rt->data().size()) / 2);
		}
	}

	Explorer::~Explorer() {
		clear_tree(root);
	}

	void Explorer::set_root_matrix(Matrix &m) {
		root->set_data(m);
	}

	BTNode<Matrix>* Explorer::get_root() {
		return root;
	}

	unsigned long long Explorer::get_number_solutions() {
		return number_of_solutions;
	}

	void Explorer::explore(BTNode<Matrix> *node, int i, int j, int depth) {
		if(check_valid(node) && continue_heuristics(node, i * node->data().size() + j)) {
			// cout << depth << endl;
			int size = node->data().size();
			if((i * size + j) < (size * size)) {
				int j_d = (j + 1) % size;
				int i_d = i;
				if (j_d == 0) {
					i_d++;
					j_d = i_d + 1;
				}
				explored++;
				generate_children(node, i, j);
				explore(node->left(), i_d, j_d, depth + 1);
				clear_tree(node->left());
				explore(node->right(), i_d, j_d, depth + 1);
				clear_tree(node->right());
			}
			else {
				if(node->data().get_number_edges() > 5) {
					cout << "edges: " <<  node->data().get_number_edges() << endl;
					cout << node->data() << endl;
				}
				if(node->data().get_number_edges() == max_edges) {
					number_of_solutions++;
				}
				//cout << "Have solution" << endl;
				//cout << node->data() << endl;
			}
		}
		else {
			explored += pow(2, (node->data().size() - 1) * node->data().size() - depth) - 1;
		}
		if(explored > print_check) {
			//cout << "Explored: " << explored << " / " << max_to_explore << " " << (double)explored / max_to_explore * 100 << "%" << endl;
			//cout << "Number solutions: " << number_of_solutions << endl;
			print_check += print_inc;
		}
	}

	void Explorer::generate_children(BTNode<Matrix> *node, unsigned int i, unsigned int j) {
		Matrix m(node->data());
		node->set_left(new BTNode<Matrix>(m));
		m.set_entry(i, j, 1);
		m.set_entry(j, i, 1);
		node->set_right(new BTNode<Matrix>(m));
	}

	bool Explorer::continue_heuristics(BTNode<Matrix> *node, int current) {
		//if(max_edges < node->data().get_number_edges()) {
		//	return false;
		//}

		// Also need to make sure I can reach the max number of edges we want
		// Something with the degree 6 and degree 5 stuff can be done, although that may go into check_valid(const BTNode<Matrix>*)

		return true;
	}

	bool Explorer::check_valid(const BTNode<Matrix> *node) {
		if(node->data().get_number_edges() == 0) {
			return true;
		}
		if(triangles_exist(node->data())) {		
			return false;
		}
		if(squares_exist(node->data())) {
			return false;
		}
		return true;
	}

	bool Explorer::symmetric(const Matrix &m) {
		bool sym = true;
		for(unsigned int i = 0; i < m.size(); i++) {
			for(unsigned int j = i; j < m.size(); j++) {
				if(m.get_entry(i, j) != m.get_entry(j, i)) {
					sym = false;
					break;
				}
			}
		}
		return sym;
	}

	bool Explorer::triangles_exist(const Matrix &m) {
		Matrix mm = m * m;
		Matrix mmm = m * mm;
		if(mmm.trace() == 0) {
			return false;
		}
		return true;
	}

	bool Explorer::squares_exist(const Matrix &m) {
		Matrix mm = m * m;
		Matrix mmmm = mm * mm;
		int sum = mmmm.trace();
		for(unsigned int i = 0; i < m.size(); i++) {
			for(unsigned int j = 0; j < m.size(); j++) {
				sum -= mm.get_entry(i, j);
			}
		}
		for(unsigned int i = 0; i < m.size(); i++) {
			int s = 0;
			for(unsigned int j = 0; j < m.size(); j++) {
				s += m.get_entry(i, j);
			}
			if(s > 1) {
				sum -= (s * (s - 1)) / 2;
			}
			//else if (s == 1) {
			//sum--;
			//}
		}

		if(m.get_number_edges() > 8) {
			cout << "Sum: " << sum << endl;
		}

		if(sum <= 0) {
			return false;
		}

		return true;
	}

	void Explorer::print() {
		BTNode<Matrix> *a = root;
		cout << a->right()->right()->data() << endl;
	}

	void Explorer::print_tree(BTNode<Matrix> *node, int pos) {
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

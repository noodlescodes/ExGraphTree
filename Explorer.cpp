#include "Explorer.h"
#include <cstdlib>
#include <iostream>
#include <cmath>

namespace VAN_MAASTRICHT {
	Explorer::Explorer(BTNode<Matrix> *rt) {
		root = rt;
		explored = 0;
		number_of_solutions = 0;
		print_check = print_inc;
		if(root->data().size() != 0) {
			max_to_explore = (unsigned long long) pow(2, root->data().size() * root->data().size());
		}
	}

	Explorer::~Explorer() {
		delete root;
		root = NULL;
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
		if(check_valid(node)) {
			// cout << depth << endl;
			int size = root->data().size();
			if((i * size + j) < (size * size)) {
				explored++;
				int j_d = (j + 1) % size;
				int i_d = i;
				if(j_d == 0) {
					i_d++;
				}				
				generate_children(node, i, j);
				explore(node->left(), i_d, j_d, depth + 1);
				explore(node->right(), i_d, j_d, depth + 1);
				node->data().set_size(0);
			}
			else if(symmetric(node->data())) {
				number_of_solutions++;
				//cout << "Have solution" << endl;
				//cout << node->data() << endl;
			}
		}
		else {
			explored += pow(2, root->data().size() * root->data().size() - depth) - 1;
			node->data().set_size(0);
		}
		if(explored > print_check) {
			cout << "Explored: " << explored << " / " << max_to_explore << " " << (double)explored / max_to_explore * 100 << "%" << endl;
			cout << "Number solutions: " << number_of_solutions << endl;
			print_check += print_inc;
		}
	}

	void Explorer::generate_children(BTNode<Matrix> *node, unsigned int i, unsigned int j) {
		Matrix m = node->data();
		node->set_left(new BTNode<Matrix>(m));
		m.set_entry(i, j, 1);
		node->set_right(new BTNode<Matrix>(m));
	}

	bool Explorer::check_valid(const BTNode<Matrix> *node) {
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
		//if(!symmetric(m)) {
		//	return false;
		//}
		Matrix mm = m * m;
		Matrix mmm = m * mm;
		if(mmm.trace() == 0) {
			return false;
		}
		return true;
	}

	bool Explorer::squares_exist(const Matrix &m) {
		if(!symmetric(m)) {
			return false;
		}
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
			else if (s == 1) {
				sum--;
			}
		}
		if(sum == 0) {
			return false;
		}

		return true;
	}

	void Explorer::print() {
		BTNode<Matrix> *a = root;
		cout << a->right()->right()->data() << endl;
	}
}

#include "Explorer.h"
#include "BTNode.h"
#include <cstdlib>
#include <iostream>
#include <cmath>

namespace VAN_MAASTRICHT {
	Explorer::Explorer(BTNode<Matrix> *rt) {
		max_edges_set();
		root = rt;
		explored = 1;
		number_of_solutions = 0;
		print_check = print_inc;
		max_edges = 2 * max_edges_array[rt->data().size()];
		max_depth = (rt->data().size() - 1) * rt->data().size() / 2;
		if(root->data().size() != 0) {
			max_to_explore = pow(2, max_depth);
		}
		cout << "Max to explore: " << max_to_explore << endl;
	}

	Explorer::~Explorer() {
		clear_tree(root);
	}
	
	void Explorer::max_edges_set() {
		max_edges_array.push_back(0); // 0
		max_edges_array.push_back(0); // 1
		max_edges_array.push_back(1); // 2
		max_edges_array.push_back(2); // 3
		max_edges_array.push_back(3); // 4
		max_edges_array.push_back(5); // 5
		max_edges_array.push_back(6); // 6
		max_edges_array.push_back(8); // 7
		max_edges_array.push_back(10); // 8
		max_edges_array.push_back(12); // 9
		max_edges_array.push_back(15); // 10
		max_edges_array.push_back(16); // 11
		max_edges_array.push_back(18); // 12
		max_edges_array.push_back(21); // 13
		max_edges_array.push_back(23); // 14
		max_edges_array.push_back(26); // 15
		max_edges_array.push_back(28); // 16
		max_edges_array.push_back(31); // 17
		max_edges_array.push_back(34); // 18
		max_edges_array.push_back(38); // 19
		max_edges_array.push_back(41); // 20
		max_edges_array.push_back(44); // 21
		max_edges_array.push_back(47); // 22
		max_edges_array.push_back(50); // 23
		max_edges_array.push_back(54); // 24
		max_edges_array.push_back(57); // 25
		max_edges_array.push_back(61); // 26
		max_edges_array.push_back(65); // 27
		max_edges_array.push_back(68); // 28
		max_edges_array.push_back(72); // 29
		max_edges_array.push_back(76); // 30
		max_edges_array.push_back(80); // 31
		max_edges_array.push_back(85); // 32
		max_edges_array.push_back(88); // 33
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
		if(check_valid(node) && continue_heuristics(node, depth)) {
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
			else if(max_edges == node->data().get_number_edges()) {
				cout << "edges: " << node->data().get_number_edges() << endl;
				cout << "depth: " << depth << endl;
				cout << node->data() << endl;
				number_of_solutions++;
				//cout << "Have solution" << endl;
				//cout << node->data() << endl;
			}
		}
		else {
			explored += pow(2, max_depth - depth) - 1;
		}
		if(explored > print_check) {
			cout << "Explored: " << explored << " / " << max_to_explore << " " << explored / max_to_explore * 100 << "%" << endl;
			cout << "Number solutions: " << number_of_solutions << endl;
			print_check += print_inc;
		}
	}

	void Explorer::generate_children(BTNode<Matrix> *node, unsigned int i, unsigned int j) {
		Matrix m(node->data());
		node->set_left(new BTNode<Matrix>(m));
		m.set_entry_symm(i, j, 1);
		node->set_right(new BTNode<Matrix>(m));
	}

	bool Explorer::continue_heuristics(BTNode<Matrix> *node, int depth) {
		if(max_edges < node->data().get_number_edges()) {
			return false;
		}
		// I'm not sure why +2 works here, need to give it some thought.
		if(max_depth - depth + 2 < max_edges - node->data().get_number_edges()) {
			return false;
		}

		// Something with the degree 6 and degree 5 stuff can be done, although that may go into check_valid(const BTNode<Matrix>*)
		// regarding comment above. Find out formula for maximum degree and maximum number of vertices with that degree instead.

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
				sum -= (s * (s - 1));
			}
			//else if(s == 1) {
			//sum--;
			//}
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

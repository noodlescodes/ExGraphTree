#ifndef NATHAN_VAN_MAASTRICHT_EXPLORER
#define NATHAN_VAN_MAASTRICHT_EXPLORER

#include "BTNode.h"
#include "Matrix.h"

using VAN_MAASTRICHT::BTNode;
using VAN_MAASTRICHT::Matrix;

namespace VAN_MAASTRICHT {
	class Explorer {
	public:
		Explorer(BTNode<Matrix> *rt = new BTNode<Matrix>());
		~Explorer();

		// getters
		BTNode<Matrix>* get_root();
		unsigned long long get_number_solutions();
		unsigned long long get_max_nodes();

		// setters
		void set_root_matrix(Matrix &m);

		// modifiers
		void explore(BTNode<Matrix> *node, int i, int j, int depth);
		void generate_children(BTNode<Matrix> *node, unsigned int i, unsigned int j);

		// exploring specific
		bool check_valid(const BTNode<Matrix> *node);
		bool symmetric(const Matrix &m);
		bool triangles_exist(const Matrix &m);
		bool squares_exist(const Matrix &m);

		// additional functions for debugging
		void print();
		void print_tree(BTNode<Matrix> *node, int pos); // do not use yet

	private:
		BTNode<Matrix>* root;
		unsigned long long explored;
		unsigned long long max_to_explore;
		unsigned long long number_of_solutions;
		unsigned long long print_check;
		unsigned long long max_nodes;
		const static unsigned long long print_inc = 1000000;
	};
}

#endif

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

		// setters
		void set_root_matrix(Matrix &m);

		// modifiers
		void explore(BTNode<Matrix> *node, int i, int j, int depth);
		void explore_random(BTNode<Matrix> *node, int i, int j, int depth);
		void generate_children(BTNode<Matrix> *node, unsigned int i, unsigned int j);

		// exploring specific
		bool continue_heuristics(BTNode<Matrix> *node, int depth);
		bool degree_sat(const Matrix &m);
		bool check_valid(const BTNode<Matrix> *node);
		bool symmetric(const Matrix &m);
		bool triangles_exist(const Matrix &m);
		bool squares_exist(const Matrix &m);

		// additional functions for debugging
		void print();
		void print_tree(BTNode<Matrix> *node, int pos); // do not use yet

	private:
		void max_edges_set();
		
		BTNode<Matrix>* root;
		double explored; // change to double
		double max_to_explore; // change to double
		unsigned long long number_of_solutions;
		double print_check;
		unsigned long long max_edges;
		unsigned long long max_depth;
		unsigned int max_degree;
		unsigned int min_degree;
		double print_inc;
		vector<unsigned int> max_edges_array;
	};
}

#endif

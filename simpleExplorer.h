#ifndef NATHAN_VAN_MAASTRICHT_SIMPLEEXPLORER
#define NATHAN_VAN_MAASTRICHT_SIMPLEEXPLORER

#include "BTNode.h"

using VAN_MAASTRICHT::BTNode;

namespace VAN_MAASTRICHT {
	class simpleExplorer {
	public:
		simpleExplorer(BTNode<int> *rt = new BTNode<int>());
		~simpleExplorer();

		// getters
		BTNode<int>* get_root();
		unsigned long long get_number_of_solutions();

		// setters
		void set_root_data(int &m);

		// modifiers
		void explore(BTNode<int> *node, int depth);
		void generate_children(BTNode<int> *node);

		// additional functions for debugging
		void print();
		void print_tree(BTNode<int> *node, int pos);

	private:
		BTNode<int>* root;
		unsigned long long explored;
		unsigned long long max_to_explore;
		unsigned long long number_of_solutions;
		unsigned long long print_check;
		const static unsigned long long print_inc = 0;
	};
}

#endif

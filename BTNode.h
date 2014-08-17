#ifndef NATHAN_VAN_MAASTRICHT_BTNODE
#define NATHAN_VAN_MAASTRICHT_BTNODE

#include <cstdlib>

using namespace std;

namespace VAN_MAASTRICHT {

	template <class Item>

	class BTNode {
	public:
		BTNode(const Item& init_data = Item(), BTNode<Item> *left = NULL, BTNode<Item> *right = NULL) {
			data_field = init_data;
			left_child = left;
			right_child = right;
		}
		
		//modifcation member functions
		Item& data() {return data_field;}
		BTNode<Item>*& left() {return left_child;}
		BTNode<Item>*& right() {return right_child;}
		void set_data(const Item& data) {data_field = data;}
		void set_left(BTNode<Item> *left) {left_child = left;}
		void set_right(BTNode<Item> *right) {right_child = right;}
		
		// constant member functions
		const Item& data() const {return data_field;}
		const BTNode<Item>* left() const {return left_child;}
		const BTNode<Item>* right() const {return right_child;}
		bool is_leaf() const {return (left_child == NULL) && (right_child == NULL);}

	private:
		Item data_field;
		BTNode *left_child;
		BTNode *right_child;
	};

	template <class Item>
	void clear_tree(BTNode<Item>*& root_ptr);

	template <class Item>
	size_t tree_size(const BTNode<Item> *root_ptr);
}

#include "BTree.template"
#endif

#ifndef NATHAN_VAN_MAASTRICHT_BTREE
#define NATHAN_VAN_MAASTRICHT_BTREE

#include "BTNode.h"

namespace VAN_MAASTRICHT {
	template <class Item>
	class BTree {
	public:
		BTree(BTNode<Item>* rt = BTNode<Item>());
		~BTree();

		// getters
		BTNode<Item> *get_root();
		const BTNode<Item> *get_root() const;

		// setters
		void set_root(BTNode<Item>* rt);

	private:
		BTNode<Item>* root;
	};
}
#include "BTree.template"
#endif

#include <cstdlib>

template <class Item>

class BTNode {
public:
	// type def
	typedef Item value_type;

	// cosntructor
	BTNode(const Item& initData = Item(), BTNode *left = NULL, BTNode *right = NULL)
	{
		data_field = initData;
		left_child = left;
		right_child = right;
	}

	// Modification functions
	Item& data() {return data_field;}
	BTNode*& left() {return left_child;}
	BTNode*& right() {return right_child;}
	void set_data(const Item& new_data) {data_field = new_data;}
	void set_left(BTNode *new_left) {left_child = new_left;}
	void set_right(BTNode *new_right) {right_child = new_right;}
	
	// constant member functions
	const Item& data() const {return data_field;}
	const BTNode* left() const {return left_child;}
	const BTNode* right() const {return right_child;}
	const bool is_leaf() const {return (left_child == NULL) && (right_child == NULL);}
	
private:
	Item data_field;
	BTNode *left_child;
	BTNode *right_child;
};

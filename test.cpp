#include <cstdlib>
#include <iostream>
#include "BTNode.h"
#include "Matrix.h"

using namespace std;
using namespace VAN_MAASTRICHT;

int main() {
	BTNode<int>* a = new BTNode<int>(2);

	cout << a->data() << endl;
	if(a->is_leaf()) {
		cout << "T" << endl;
	}
	else {
		cout << "F" << endl;
	}
	a->set_data(3);
	cout << a->data() << endl;
	a->set_left(new BTNode<int>(4));
	if(a->is_leaf()) {
		cout << "T" << endl;
	}
	else {
		cout << "F" << endl;
	}
	cout << a->left()->data() << endl;

	delete a;

	Matrix b = Matrix();
	b.set_size(2);
	cout << b.size() << endl;
	b.set_entry(0, 0, 1);
	b.set_entry(1, 1, 1);
	b.set_entry(0, 1, 1);
	
	cout << b << endl;
	cout << b * b << endl;
	cout << b + b << endl;
	cout << b % b << endl;
	return 0;
}

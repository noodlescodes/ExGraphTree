#include <cstdlib>
#include <iostream>
#include <ctime>
#include "BTNode.h"
#include "Matrix.h"
#include "BTree.h"
#include "Explorer.h"

using namespace std;
using namespace VAN_MAASTRICHT;

int squares(const Matrix &m) {
	Matrix mm = m * m;
	Matrix mmmm = mm * mm;
	int sum = mmmm.trace();
	int s2 = 0;
	for(unsigned int i = 0; i < m.size(); i++) {
		for(unsigned int j = 0; j < m.size(); j++) {
			s2 += mm.get_entry(i, j);
		}
	}
	cout << s2 << endl;
	int s3 = 0;
	for(unsigned int i = 0; i < m.size(); i++) {
		int s = 0;
		for(unsigned int j = 0; j < m.size(); j++) {
			s += m.get_entry(i, j);
		}
		if(s > 1) {
			s3 += ((s * (s - 1)) / 2);
		}
		else {
			s3++;
		}
	}
	sum = sum - s2 - s3;
	return sum;
}

int main() {
	/* BTNode<int>* a = new BTNode<int>(2);
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
	b.set_size(2);E

	cout << b.size() << endl;

	b.set_entry(0, 0, 1);
	b.set_entry(1, 1, 1);
	b.set_entry(0, 1, 1);

	cout << b << endl;
	cout << b * b << endl;
	cout << b + b << endl;
	cout << b % b << endl;

	BTree<int> c = BTree<int>(a); */

	time_t start = time(NULL);
	Matrix b = Matrix();
	b.set_size(6);
	Explorer *a = new Explorer(new BTNode<Matrix>(b));

	a->explore(a->get_root(), 0, 0, 0);
	cout << "Number of solutions: " << a->get_number_solutions() << endl;
	delete a;
	cout << "Time taken: " << time(NULL) - start << endl;

	/*Matrix b = Matrix();
	b.set_size(4);
	b.set_entry(0,1,1);
	b.set_entry(0,2,1);
	b.set_entry(0,3,1);
	b.set_entry(1,0,1);
	b.set_entry(2,0,1);
	b.set_entry(3,0,1);

	cout << b << endl;

	cout << squares(b) << endl;*/

	return 0;
}

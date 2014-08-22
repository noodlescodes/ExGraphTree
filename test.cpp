#include <cstdlib>
#include <iostream>
#include <ctime>
#include "BTNode.h"
#include "Matrix.h"
#include "Explorer.h"
#include "simpleExplorer.h"

using namespace std;
using namespace VAN_MAASTRICHT;

bool squares_exist(const Matrix &m) {

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
	}

	cout << sum << endl;

	if(sum == 0) {
		return false;
	}

	return true;
}

int main() {
	time_t start = time(NULL);
	Matrix b = Matrix();
	b.set_size(8);
	Explorer *a = new Explorer(new BTNode<Matrix>(b));

	a->explore(a->get_root(), 0, 1, 0);
	cout << "Number of solutions: " << a->get_number_solutions() << endl;
	delete a;
	cout << "Time taken: " << time(NULL) - start << endl;

	/*Matrix b = Matrix();
	b.set_size(5);
	b.set_entry(0, 1, 1);
	b.set_entry(0, 2, 1);
	b.set_entry(0, 3, 1);
	b.set_entry(0, 4, 1);
	b.set_entry(1, 0, 1);
	b.set_entry(2, 0, 1);
	b.set_entry(3, 0, 1);
	b.set_entry(4, 0, 1);

	cout << squares_exist(b) << endl;*/

	return 0;
}

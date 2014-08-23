#include <cstdlib>
#include <iostream>
#include <ctime>
#include <sstream>
#include "BTNode.h"
#include "Matrix.h"
#include "Explorer.h"
#include "simpleExplorer.h"

using namespace std;
using namespace VAN_MAASTRICHT;

int main(int argc, char* argv[]) {
	if(argc < 2) {
		cout << "Need an argument for the order of the graph" << endl;
		return 1;
	}
	if(argc > 2) {
		cout << "Only provide one argument" << endl;
	}

	stringstream str;
	str << argv[1];
	int order;
	str >> order;

	time_t start = time(NULL);
	Matrix b = Matrix();
	b.set_size(order);
	Explorer *a = new Explorer(new BTNode<Matrix>(b));

	a->explore(a->get_root(), 0, 1, 0);
	cout << "Number of solutions: " << a->get_number_solutions() << endl;
	delete a;
	cout << "Time taken: " << time(NULL) - start << endl;

	return 0;
}

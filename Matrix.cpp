#include "Matrix.h"

namespace VAN_MAASTRICHT {
	Matrix::Matrix(const vector<vector<int> > mat) {
		matrix = mat;
		s = mat.size();
	}

	int Matrix::set_entry(unsigned int i, unsigned int j, int data) {
		if((i >= matrix.size()) || (j >= matrix.size())) {
			return -1;
		}
		else {
			matrix[i][j] = data;
		}

		return 1;
	}

	void Matrix::set_matrix(const vector<vector<int> > mat) {
		matrix = mat;
	}

	void Matrix::set_size(const int size) {
		matrix.resize(size);
		for(unsigned int i = 0; i < matrix.size(); i++) {
			matrix[i].resize(size);
		}
		s = size;
	}

	const int Matrix::trace() const {
		int trace = 0;
		for(unsigned int i = 0; i < matrix.size(); i++) {
			trace += matrix[i][i];
		}
		return trace;
	}

	const unsigned int Matrix::size() const {
		return s;
	}

	const int Matrix::get_entry(unsigned int i, unsigned int j) const {
		if((i >= matrix.size()) && j >= matrix.size()) {
			return -1;
		}
		return matrix[i][j];		
	}

	ostream& operator <<(ostream& outs, const Matrix& mat) {
		for(unsigned int i = 0; i < mat.size(); i++) {
			for(unsigned int j = 0; j < mat.size(); j++) {
				outs << mat.get_entry(i, j) << ", ";
			}
			outs << endl;
		}

		return outs;
	}

	Matrix operator +(const Matrix& m1, const Matrix& m2) {
		if(m1.size() != m2.size()) {
			return Matrix();
		}
		vector<vector<int> > mat = vector<vector<int> >(m1.size());
		for(unsigned int i = 0; i < mat.size(); i++) {
			mat[i].resize(mat.size());
		}
		for(unsigned int i = 0; i < mat.size(); i++) {
			for(unsigned int j = 0; j < mat.size(); j++) {
				mat[i][j] = m1.get_entry(i, j) + m2.get_entry(i, j);
			}
		}

		return Matrix(mat);
	}

	Matrix operator *(const Matrix& m1, const Matrix& m2) {
		if(m1.size() != m2.size()) {
			return Matrix();
		}
		vector<vector<int> > mat = vector<vector<int> >(m1.size());
		for(unsigned int i = 0; i < mat.size(); i++) {
			mat[i].resize(mat.size());
		}
		for(unsigned int i = 0; i < mat.size(); i++) {
			for(unsigned int j = 0; j < mat.size(); j++) {
				for(unsigned int k = 0; k < mat.size(); k++) {
					mat[i][j] += m1.get_entry(i, k) * m2.get_entry(k, j);
				}
			}
		}

		return Matrix(mat);
	}

	Matrix operator %(const Matrix& m1, const Matrix& m2) {
		if(m1.size() != m2.size()) {
			return Matrix();
		}
		vector<vector<int> > mat = vector<vector<int> >(m1.size());
		for(unsigned int i = 0; i < mat.size(); i++) {
			mat[i].resize(mat.size());
		}
		for(unsigned int i = 0; i < mat.size(); i++) {
			for(unsigned int j = 0; j < mat.size(); j++) {
				mat[i][j] = m1.get_entry(i, j) * m2.get_entry(i, j);
			}
		}

		return Matrix(mat);
	}
}

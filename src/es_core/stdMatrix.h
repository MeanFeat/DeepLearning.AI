#pragma once
#include "es_core_pch.h"

typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic > MatrixDynamic;
namespace Eigen {
	template<class Matrix>
	void write_binary(const char* filename, const Matrix& matrix) {
		std::ofstream out(filename, ios::out | ios::binary | ios::trunc);
		typename Matrix::Index rows = matrix.rows(), cols = matrix.cols();
		out.write((char*)(&rows), sizeof(typename Matrix::Index));
		out.write((char*)(&cols), sizeof(typename Matrix::Index));
		out.write((char*)matrix.data(), rows*cols * sizeof(typename Matrix::Scalar));
		out.close();
	}
	template<class Matrix>
	void read_binary(const char* filename, Matrix& matrix) {
		std::ifstream in(filename, ios::in | std::ios::binary);
		typename Matrix::Index rows = 0, cols = 0;
		in.read((char*)(&rows), sizeof(typename Matrix::Index));
		in.read((char*)(&cols), sizeof(typename Matrix::Index));
		matrix.resize(rows, cols);
		in.read((char *)matrix.data(), rows*cols * sizeof(typename Matrix::Scalar));
		in.close();
	}
	template<class Matrix>
	void write_csv(const char* filename, Matrix& matrix) {
		std::ofstream file;
		file.open(filename);
		for (int i = 0; i < matrix.rows() * matrix.cols(); ++i) {
			file << (*(matrix.data() + i));
			if ((i % matrix.rows()) == matrix.rows() - 1) {
				file << std::endl;
			}
			else {
				file << ',';
			}
		}
		file.close();
	}
	Eigen::MatrixXf BuildMatFromFile(std::string fName) {
		std::vector<std::vector<float>> tempMat;
		std::ifstream file(fName);
		std::string line;
		int count = 0;
		float temp;
		int row = 0;
		while (file.good()) {
			std::vector<float> row;
			std::getline(file, line);
			std::stringstream iss(line);
			std::string val;
			while (iss.good()) {
				std::getline(iss, val, ',');
				std::stringstream convertor(val);
				convertor >> temp;
				row.push_back(temp);
			}
			tempMat.push_back(row);
		}
		Eigen::MatrixXf outMat(tempMat.size(), tempMat[0].size());
		for (int i = 0; i < (int)tempMat.size(); i++) {
			for (int j = 0; j < (int)tempMat[i].size(); j++) {
				outMat(i, j) = tempMat[i][j];
			}
		}
		return outMat;
	}

	const static IOFormat CSVFormat(StreamPrecision, DontAlignCols, ", ", "\n");
	void writeToCSVfile(std::string name, Eigen::MatrixXf matrix) {
		std::ofstream file(name.c_str());
		file << matrix.format(CSVFormat);
	}

	void removeColumn(Eigen::MatrixXf& matrix, unsigned int colToRemove) {
		unsigned int numRows = (unsigned int)matrix.rows();
		unsigned int numCols = (unsigned int)matrix.cols() - 1;

		if (colToRemove < numCols)
			matrix.block(0, colToRemove, numRows, numCols - colToRemove) = matrix.rightCols(numCols - colToRemove);

		matrix.conservativeResize(numRows, numCols);
	}
}
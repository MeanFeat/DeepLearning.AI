#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <Eigen/dense>
#include "stdNet.h"
#include "d_Matrix.h"
#include "d_Math.h"

using namespace Eigen;
using namespace std;

struct d_NetTrainParameters {
	vector<d_Matrix> d_W;
	vector<d_Matrix> d_b;
	double learningRate;
	double learningMod;
	double regTerm;
	double regMod;
	double coefficiant;
	unsigned int trainExamplesCount;
};

struct d_NetTrainDerivatives {
	vector<d_Matrix> d_dW;
	vector<d_Matrix> d_db;
};

struct d_NetCache {
	vector<d_Matrix> d_A;
	vector<d_Matrix> d_dZ;
	double cost;
	float stepTime;
};

class d_NetTrainer {
public:
	d_NetTrainer();
	d_NetTrainer(Net *net, MatrixXd *data, MatrixXd *labels, double weightScale, double learnRate, double regTerm);
	~d_NetTrainer();
	
	d_NetTrainParameters GetTrainParams();
	d_NetCache GetCache();
	Net *network;
	d_Matrix d_trainLabels;

	void BuildVisualization(MatrixXd screen, int * buffer, int m, int k);
	void Visualization(int * buffer, int m, int k, bool discrete);
	void UpdateHostNetwork();
	void UpdateSingleStep();
	double CalcCost();

	double GetCost() {
		return GetCache().cost;
	}

	double Coeff() {
		return trainParams.coefficiant;
	}

	inline void ModifyLearningRate(double m) {
		trainParams.learningMod = max(DBL_EPSILON, trainParams.learningMod + m);
	}
	inline void ModifyRegTerm(double m) {
		trainParams.regMod = max(DBL_EPSILON, trainParams.regMod + m);
	}

	unsigned int TrainExamplesCount() {
		return trainParams.trainExamplesCount;
	}
	
protected:
	d_NetCache cache;
	d_NetTrainParameters trainParams;
	d_NetTrainDerivatives derivative;
	d_NetTrainDerivatives momentum;
	d_NetTrainDerivatives momentumSqr;
	int *d_Buffer;
	vector<d_Matrix> d_VisualA;

private:
	void AddLayer(int A, int B);
	void ForwardTrain();
	void BackwardPropagation();
	void UpdateParameters();
	void UpdateParametersADAM();
};



/*
High Dimensional Model Representation
======================================
This class is intended to be used in conjunction with the AdaptiveSparseGrid library of "Xiang Ma, xm25@cornell.edu".
The interface of the two class are through SGwrite & SGread.
Status Note: Work in progress.
aryan.eftekhari@usi.ch/gmail.com
*/

#ifndef HDMR_h_is_included
#define HDMR_h_is_included

#include "SparseGrid.h"
#include "SGread.h"
#include "SGwrite.h"

class HDMR {
  public:

	// Properties
	void (*problemFunc)(double*, int, double*);

	SGread** sgread;
	SGwrite** sgwrite;

	string folderName;
	double l2convergence = -1;

	struct ProbParam {
		int dim = -1;
		int dof = -1;
	} probParam;

	struct SgParam {
		int maxLevel = -1;
		int gridType = -1;
		double cutOff = -1.0;
	} sgParam;

	struct HdmrParam {
		vector<double> xBar;
		vector<double> fxBar;
		int maxOrder = -1;
		double cutOff = -1.0;
	} hdmrParam;

	struct ComputePool {

		// Node
		int nodeRank = -1;
		int nodeSize = -1;
		int processPerNode = -1;

		// Local
		int rank = -1;
		int size = -1;

		// GLOBAL
		int grank = -1;
		int gsize = -1;

		MPI_Comm subComm = MPI_COMM_WORLD;
	} computePool;

	struct Job {
		vector <vector<vector<int>>> all;
		int all_size = 0;
		vector <vector<vector<int>>> active;
		int active_size = 0;
		vector <list<vector<int>>> full;
	} job;

	struct RunTime {
		int verbose = 0;
		string mode = "";
		double time = 0;
		double avgTime = 0;
		double maxTime = 0;
		double minTime = 0;
		unsigned int interpolationPoints = 0;
	} runTime;

	// Methods
	HDMR(int verbose_ = 0);
	~HDMR();
	void clear();


	int write( // Write HDMR
	    void (*problemFunc_)(double*, int, double*),
	    int problemDim_,
	    int problemDoF_ ,
	    int sgMaxLevel_ ,
	    double sgCutOff_ ,
	    int sgGridType_ ,
	    int hmdrMaxOrder_ ,
	    double hdmrCutOff_ ,
	    vector<double>xBar_,
	    int processPerNode_ = -1,
	    string folderName_ = "surplusHDMR/"
	);

	int write( // Write SG
	    void (*problemFunc_)(double*, int, double*),
	    int problemDim_,
	    int problemDoF_ ,
	    int sgMaxLevel_ ,
	    double sgCutOff_ ,
	    int sgGridType_ ,
	    string folderName_ = "surplusSG/"
	);

	int read(string folderName_);

	void interpolate(double* xSet, double* valSet , int pointCount);
	void debug(string heading, int rankToShow = 0, int showRunTime = 1, int showComputePool = 0, int showProb = 0 , int showSG_HDMRparam = 0, int showJob = 0);


  private:
	string hline = "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

	void interpolate_SG(double* xSet, double* valSet , int pointCount);
	void interpolate_HDMR(double* xSet, double* valSet , int pointCount);

	void setAllJobs();
	int setActiveJobs_noAdaptivity();
	int setActiveJobs_integralAdaptivty();
	void removeDimFromJobs(vector<int>& activeDim, int d_start);

	void setComputePool();

	void writeIndexFile();
	void readIndexFile();

	void startTimer();
	void endTimer();

	void err(string message) {
		string line = "";
		int grank;
		MPI_Comm_rank(MPI_COMM_WORLD, &grank);
		line.insert(0, message.length(), '=');
		if (grank == 0) {
			cout << "\n" + line + "\n" << message << "\n" + line + "\n";
		}
		MPI_Barrier(MPI_COMM_WORLD);
		exit(1);
	}
};

#endif
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <sstream>
#include <cfloat>
#include <cmath>

typedef unsigned int uint;

void processForSum(std::vector<std::string> data, uint queryStart) {
	std::vector<uint> tsMap;
	std::vector<uint> whichSym;
	std::vector<std::vector<std::pair<uint, uint> > > fnfv;

	for(uint i=0; i<queryStart; ++i) {
		std::string x=data[i];
		std::stringstream ss;
		ss << x;

		uint tStamp;
		uint sym;
		char c1;
		ss >> tStamp >> c1 >> sym;
		tsMap.push_back(tStamp);

		whichSym.push_back(sym);

		std::vector<std::pair<uint, uint> > temp;

		char c;
		uint fnum, fval;
		while(ss >> c >> fnum >> fval) {
			temp.push_back(std::make_pair(fnum, fval));
			//std::cout << c << fnum << " " << fval << std::endl;
		}

		fnfv.push_back(temp);
	}

	/*
	for(int i=0; i<fnfv.size(); ++i) {
		std::cout << tsMap[i] << " " << whichSym[i] << " ";
		for(int j=0; j<fnfv[i].size(); ++j) {
			std::cout << fnfv[i][j].first << " " << fnfv[i][j].second << " ";
		}
		std::cout << std::endl;
	}
	*/

	for(uint i=queryStart; i<data.size(); ++i) {
		//std::cout << "Processing query: " << i-queryStart << std::endl;
		std::string x=data[i];
		std::stringstream ss;
		ss << x;

		char c;
		uint startT, endT;
		uint sym, fnum;
		ss >> x >> startT >> endT >> c >> sym >> c >> fnum;

		std::vector<uint>::iterator l, u;
		if(binary_search(tsMap.begin(), tsMap.end(), startT))
			l=std::lower_bound(tsMap.begin(), tsMap.end(), startT);
		else
			l=std::upper_bound(tsMap.begin(), tsMap.end(), startT);
		if(binary_search(tsMap.begin(), tsMap.end(), endT))
			u=std::upper_bound(l, tsMap.end(), endT);
		else
			u=std::lower_bound(l, tsMap.end(), endT);
		long long sum=0;
		for(;l<u;++l) {
			uint l_=l-tsMap.begin();
			if(whichSym[l_]==sym) {
				std::vector<std::pair<uint, uint> > temp=fnfv[l_];
				for(uint j=0; j<temp.size(); ++j) {
					if(temp[j].first==fnum) {
						sum+=temp[j].second;
					}
				}
			}
		}
		std::cout << sum << std::endl;
	}
}

void processForProduct(std::vector<std::string> data, uint queryStart) {
	std::vector<uint> tsMap;
	std::vector<uint> whichSym;
	std::vector<std::vector<std::pair<uint, uint> > > fnfv;

	for(uint i=0; i<queryStart; ++i) {
		std::string x=data[i];
		std::stringstream ss;
		ss << x;

		uint tStamp;
		uint sym;
		char c1;
		ss >> tStamp >> c1 >> sym;
		tsMap.push_back(tStamp);

		whichSym.push_back(sym);

		std::vector<std::pair<uint, uint> > temp;

		char c;
		uint fnum, fval;
		while(ss >> c >> fnum >> fval) {
			temp.push_back(std::make_pair(fnum, fval));
			//std::cout << c << fnum << " " << fval << std::endl;
		}

		fnfv.push_back(temp);
	}

	/*
	for(int i=0; i<fnfv.size(); ++i) {
		std::cout << tsMap[i] << " " << whichSym[i] << " ";
		for(int j=0; j<fnfv[i].size(); ++j) {
			std::cout << fnfv[i][j].first << " " << fnfv[i][j].second << " ";
		}
		std::cout << std::endl;
	}
	*/

	for(uint i=queryStart; i<data.size(); ++i) {
		//std::cout << "Processing query: " << i-queryStart << std::endl;
		std::string x=data[i];
		std::stringstream ss;
		ss << x;

		char c;
		uint startT, endT;
		uint sym, fnum, fnum2;
		ss >> x >> startT >> endT >> c >> sym >> c >> fnum >> c >> fnum2;

		std::vector<uint>::iterator l, u;
		if(binary_search(tsMap.begin(), tsMap.end(), startT))
			l=std::lower_bound(tsMap.begin(), tsMap.end(), startT);
		else
			l=std::upper_bound(tsMap.begin(), tsMap.end(), startT);
		if(binary_search(tsMap.begin(), tsMap.end(), endT))
			u=std::upper_bound(l, tsMap.end(), endT);
		else
			u=std::lower_bound(l, tsMap.end(), endT);
		//std::cout << tsMap[(int)(l-tsMap.begin())] << " " << tsMap[(int)(u-tsMap.begin())] << std::endl;
		long long sum=0;
		for(;l<u;++l) {
			uint l_=l-tsMap.begin();
			if(whichSym[l_]==sym) {
				std::vector<std::pair<uint, uint> > temp=fnfv[l_];
				bool toBreak=false;
				for(uint j=0; j<temp.size() && !toBreak; ++j) {
					if(temp[j].first==fnum) {
						for(uint k=0; k<temp.size() && !toBreak; ++k) {
							if(temp[k].first==fnum2) {
								//std::cout << tsMap[l_] << " " << fnum << " " << fnum2 << " " << temp[j].second << " " << temp[k].second << std::endl;
								sum+=temp[j].second*temp[k].second;
								toBreak=true;
							}
						}
					}
				}
			}
		}
		std::cout << sum << std::endl;
	}
}

bool cmp(uint a, uint b) {
	return a>b;
}

void processForMax(std::vector<std::string> data, uint queryStart) {
	std::vector<uint> tsMap;
	std::vector<uint> whichSym;
	std::vector<std::vector<std::pair<uint, uint> > > fnfv;

	for(uint i=0; i<queryStart; ++i) {
		std::string x=data[i];
		std::stringstream ss;
		ss << x;

		uint tStamp;
		uint sym;
		char c1;
		ss >> tStamp >> c1 >> sym;
		tsMap.push_back(tStamp);

		whichSym.push_back(sym);

		std::vector<std::pair<uint, uint> > temp;

		char c;
		uint fnum, fval;
		while(ss >> c >> fnum >> fval) {
			temp.push_back(std::make_pair(fnum, fval));
			//std::cout << c << fnum << " " << fval << std::endl;
		}

		fnfv.push_back(temp);
	}

	/*
	for(int i=0; i<fnfv.size(); ++i) {
		std::cout << tsMap[i] << " " << whichSym[i] << " ";
		for(int j=0; j<fnfv[i].size(); ++j) {
			std::cout << fnfv[i][j].first << " " << fnfv[i][j].second << " ";
		}
		std::cout << std::endl;
	}
	*/

	for(uint i=queryStart; i<data.size(); ++i) {
		//std::cout << "Processing query: " << i-queryStart << std::endl;
		std::string x=data[i];
		std::stringstream ss;
		ss << x;

		char c;
		uint startT, endT;
		uint sym, fnum, K;
		ss >> x >> startT >> endT >> c >> sym >> c >> fnum >> K;

		std::vector<uint>::iterator l, u;
		if(binary_search(tsMap.begin(), tsMap.end(), startT))
			l=std::lower_bound(tsMap.begin(), tsMap.end(), startT);
		else
			l=std::upper_bound(tsMap.begin(), tsMap.end(), startT);
		if(binary_search(tsMap.begin(), tsMap.end(), endT))
			u=std::upper_bound(l, tsMap.end(), endT);
		else
			u=std::lower_bound(l, tsMap.end(), endT);
		std::vector<uint> fVec;
		for(;l<u;++l) {
			uint l_=l-tsMap.begin();
			if(whichSym[l_]==sym) {
				std::vector<std::pair<uint, uint> > temp=fnfv[l_];
				for(uint j=0; j<temp.size(); ++j) {
					if(temp[j].first==fnum) {
						fVec.push_back(temp[j].second);
					}
				}
			}
		}
		sort(fVec.begin(), fVec.end(), cmp);
		for(uint j=0; j<std::min((uint)fVec.size(), K); ++j) {
			std::cout << fVec[j] << " ";
		}
		std::cout << std::endl;
	}
}

long double getCost(std::vector<uint> x, std::vector<uint> y) {
	/*
	std::cout << "DATA" << std::endl;
	for(int i=0; i<x.size(); ++i) {
		std::cout << x[i] << " " << y[i] << std::endl;
	}
	*/
	long double y_mu=0, x_mu=0, x_2=0, xy=0;
	uint n=x.size();
	for(uint i=0; i<n; ++i) {
		y_mu+=y[i];
		x_mu+=x[i];
		x_2+=x[i]*x[i];
		xy+=x[i]*y[i];
	}
	x_mu/=n;
	y_mu/=n;

	long double a,b;
	b=(y_mu*x_2-x_mu*xy)/(x_2-n*x_mu*x_mu);
	a=(xy-n*x_mu*y_mu)/(x_2-n*x_mu*x_mu);

	//std::cout << a << " " << b << std::endl;

	long double cost=0;
	for(uint i=0; i<n; ++i) {
		long double temp=(1.0*y[i]-a*x[i]-b);
		cost+=temp*temp;
	}
	return cost;
}

void processForDelta(std::vector<std::string> data, uint queryStart) {
	std::vector<uint> tsMap;
	std::vector<uint> whichSym;
	std::vector<std::vector<std::pair<uint, uint> > > fnfv;

	for(uint i=0; i<queryStart; ++i) {
		std::string x=data[i];
		std::stringstream ss;
		ss << x;

		uint tStamp;
		uint sym;
		char c1;
		ss >> tStamp >> c1 >> sym;
		tsMap.push_back(tStamp);

		whichSym.push_back(sym);

		std::vector<std::pair<uint, uint> > temp;

		char c;
		uint fnum, fval;
		while(ss >> c >> fnum >> fval) {
			temp.push_back(std::make_pair(fnum, fval));
			//std::cout << c << fnum << " " << fval << std::endl;
		}

		fnfv.push_back(temp);
	}

	/*
	for(int i=0; i<fnfv.size(); ++i) {
		std::cout << tsMap[i] << " " << whichSym[i] << " ";
		for(int j=0; j<fnfv[i].size(); ++j) {
			std::cout << fnfv[i][j].first << " " << fnfv[i][j].second << " ";
		}
		std::cout << std::endl;
	}
	*/

	for(uint i=queryStart; i<data.size(); ++i) {
		//std::cout << "Processing query: " << i-queryStart << std::endl;
		std::string x=data[i];
		std::stringstream ss;
		ss << x;

		char c;
		uint startT, endT;
		uint sym, fnum, K;
		ss >> x >> c >> sym >> c >> fnum >> K;

		std::vector<uint>::iterator l=tsMap.begin(), u=tsMap.end();
		std::vector<uint> fVec, tStmpVec;
		for(;l<u;++l) {
			uint l_=l-tsMap.begin();
			if(whichSym[l_]==sym) {
				std::vector<std::pair<uint, uint> > temp=fnfv[l_];
				for(uint j=0; j<temp.size(); ++j) {
					if(temp[j].first==fnum) {
						fVec.push_back(temp[j].second);
						tStmpVec.push_back(tsMap[l_]);
					}
				}
			}
		}
		
		uint N=fVec.size();
		long double cost[N+1];
		cost[0]=0;
		//std::cout << "CASE: " << i << std::endl;
		for(uint tau_s=0; tau_s<N; ++tau_s) {
			//std::cout << "TAU_STAR " << tau_s << std::endl;
			long double optCost=LDBL_MAX;

			std::vector<uint> xx, yy;
			xx.push_back(tStmpVec[tau_s]);
			yy.push_back(fVec[tau_s]);

			for(long int tau=(long int)tau_s-1; tau>=-1; --tau) {
				long double tempCost;
				if(xx.size()==1) {
					tempCost=cost[tau+1]+0+K;
				} else {
					tempCost=cost[tau+1]+getCost(xx,yy)+K;
				}
				//std::cout << tempCost << std::endl;
				if(tempCost < optCost) {
					optCost=tempCost;
				}
				if(tau!=-1) {
					xx.push_back(tStmpVec[tau]);
					yy.push_back(fVec[tau]);
				}
			}

			/*
			long double tempCost=LDBL_MAX, optCost=LDBL_MAX;
			int opt_tau;
			
			for(;tau>=0; --tau) {
				//std::cout << "TAU " << tau << std::endl;
				xx.push_back(tStmpVec[tau]);
				yy.push_back(fVec[tau]);
				if(tau==tau_s-1) {
					tempCost=cost[tau]+K;
					if(optCost > tempCost) {
						optCost=tempCost;
						opt_tau=tau;
					}
				} else {
					tempCost=getCost(xx, yy);
					//std::cout << "TEMP " << tempCost << " " << K << std::endl;
					tempCost+=(K+cost[tau]);
					if(tempCost < optCost) {
						optCost=tempCost;
						opt_tau=tau;
						ttt=0;
					}
				}
			}*/
			//std::cout << "TAU_S " << tau_s << " " << N << " " << optCost << std::endl;
			cost[tau_s+1]=optCost;
		}
		//if(ttt==0)
			if(N==1) {
				std::cout << 0 << std::endl;
			} else {
				std::cout << std::ceil(cost[N]) << std::endl;
			}
		//else
		//	std::cout << cost[N-1]-K << std::endl;
	}
}


int main() {
	std::string tf;
	uint n;
	std::cin >> tf >> n;
	std::getline(std::cin, tf);
	std::vector<std::string> data;

	uint queryStart=n;

	std::string x;
	uint i=0;		
	while(std::getline(std::cin, x)) {
		data.push_back(x);
	}

	std::cout << "tickfile completed" << std::endl;
	switch(data[queryStart][0]) {
		case 's':
			processForSum(data, queryStart);
		break;
		case 'p':
			processForProduct(data, queryStart);
		break;
		case 'm':
			processForMax(data, queryStart);
		break;
		case 'd':
			processForDelta(data, queryStart);
		break;
	}

	return 0;
}

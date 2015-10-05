#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <sstream>
#include <cfloat>
#include <cmath>
#include <climits>

typedef unsigned int uint;

/** NOTE: For clarity and simplicity in code, we have made the functions
	* for each of the query types independent and self sufficient, although
	* that leads to a little duplication in code.
	*/

/** Function processForSum:
  * Process the sum queries
	* For each query, performs a Binary Search for the start_time
	* and end_time indices in the list in O(lg(n)) time,
	* and a scan over the entries in between to add.
	*
	* Total worst case time: O(lg(n)) + O(N)  = O(N)
	* Space complexity: O(N+S+F)
	* N - no. of rows, F: no. of fields, S: no. of symbols
	*/
void processForSum(std::vector<std::string> data, long long queryStart) {
	std::vector<long long> tsMap;
	std::vector<long long> whichSym;
	std::vector<std::vector<std::pair<long long, long long> > > fnfv;

	/* Parse the rows of Tickfile into timestamp (tsMap), symbol (whichSym)
	 * and field name, value pairs (fnfv)
	 * Time: O(N), Space: O(N + F + S)
	 */
	for(long long i=0; i<queryStart; ++i) {
		std::string x=data[i];
		std::stringstream ss;
		ss << x;

		long long tStamp;
		long long sym;
		char c1;
		ss >> tStamp >> c1 >> sym;
		tsMap.push_back(tStamp);

		whichSym.push_back(sym);

		std::vector<std::pair<long long, long long> > temp;

		char c;
		long long fnum, fval;
		while(ss >> c >> fnum >> fval) {
			temp.push_back(std::make_pair(fnum, fval));
		}

		fnfv.push_back(temp);
	}

	/* Process the Queries */
	for(long long i=queryStart; i<data.size(); ++i) {
		std::string x=data[i];
		std::stringstream ss;
		ss << x;

		char c;
		long long startT, endT;
		long long sym, fnum;
		ss >> x >> startT >> endT >> c >> sym >> c >> fnum;

		std::vector<long long>::iterator l, u;

		/* Binary search for the start and end times */
		if(binary_search(tsMap.begin(), tsMap.end(), startT))
			l=std::lower_bound(tsMap.begin(), tsMap.end(), startT);
		else
			l=std::upper_bound(tsMap.begin(), tsMap.end(), startT);
		if(binary_search(tsMap.begin(), tsMap.end(), endT))
			u=std::upper_bound(l, tsMap.end(), endT);
		else
			u=std::lower_bound(l, tsMap.end(), endT);

		/* Add the field values for the rows that match */
		long long sum=0;
		for(;l<u;++l) {
			long long l_=l-tsMap.begin();
			if(whichSym[l_]==sym) {
				std::vector<std::pair<long long, long long> > temp=fnfv[l_];
				for(long long j=0; j<temp.size(); ++j) {
					if(temp[j].first==fnum) {
						sum+=temp[j].second;
					}
				}
			}
		}
		std::cout << sum << std::endl;
	}
}

/** Function processForProduct:
  * Process the product queries
	* For each query, performs a Binary Search for the start_time
	* and end_time indices in the list in O(lg(n)) time,
	* and a scan over the entries in between to add O(n).
	* 
	* Total worst case time: O(lg(n)) + O(n)  = O(n)
	* Space complexity: O(N+S+F)
	* N - no. of rows, F: no. of fields, S: no. of symbols
	*/
void processForProduct(std::vector<std::string> data, long long queryStart) {
	std::vector<long long> tsMap;
	std::vector<long long> whichSym;
	std::vector<std::vector<std::pair<long long, long long> > > fnfv;

	/* Parse the rows of Tickfile into timestamp (tsMap), symbol (whichSym)
	 * and field name, value pairs (fnfv)
	 * Time: O(N), Space: O(N + F + S)
	 */
	for(long long i=0; i<queryStart; ++i) {
		std::string x=data[i];
		std::stringstream ss;
		ss << x;

		long long tStamp;
		long long sym;
		char c1;
		ss >> tStamp >> c1 >> sym;
		tsMap.push_back(tStamp);

		whichSym.push_back(sym);

		std::vector<std::pair<long long, long long> > temp;

		char c;
		long long fnum, fval;
		while(ss >> c >> fnum >> fval) {
			temp.push_back(std::make_pair(fnum, fval));
		}

		fnfv.push_back(temp);
	}

	/* Process the Queries */
	for(long long i=queryStart; i<data.size(); ++i) {
		std::string x=data[i];
		std::stringstream ss;
		ss << x;

		char c;
		long long startT, endT;
		long long sym, fnum, fnum2;
		ss >> x >> startT >> endT >> c >> sym >> c >> fnum >> c >> fnum2;

		/* Binary Search for the queries */
		std::vector<long long>::iterator l, u;
		if(binary_search(tsMap.begin(), tsMap.end(), startT))
			l=std::lower_bound(tsMap.begin(), tsMap.end(), startT);
		else
			l=std::upper_bound(tsMap.begin(), tsMap.end(), startT);
		if(binary_search(tsMap.begin(), tsMap.end(), endT))
			u=std::upper_bound(l, tsMap.end(), endT);
		else
			u=std::lower_bound(l, tsMap.end(), endT);

		/* Add all field values that match the given query */
		long long sum=0;
		for(;l<u;++l) {
			long long l_=l-tsMap.begin();
			if(whichSym[l_]==sym) {
				std::vector<std::pair<long long, long long> > temp=fnfv[l_];
				bool toBreak=false;
				for(long long j=0; j<temp.size() && !toBreak; ++j) {
					if(temp[j].first==fnum) {
						for(long long k=0; k<temp.size() && !toBreak; ++k) {
							if(temp[k].first==fnum2) {
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


/* Comparision function for decreasing sort */
bool cmp(long long a, long long b) {
	return a>b;
}

/** Function processForMax:
  * Process the MAX queries
	* For each query, performs a Binary Search for the start_time
	* and end_time indices in the list in O(lg(n)) time,
	* and a scan over the entries in between. Then we sort the
	* obtained rows to obtain k maximum values. O(nlg(n))
	* 
	* Total worst case time: O(lg(n)) + O(nlg(n))  = O(nlg(n))
	* Space complexity: O(N+S+F)
	* N - no. of rows, F: no. of fields, S: no. of symbols
	*/
void processForMax(std::vector<std::string> data, long long queryStart)
{
	std::vector<long long> tsMap;
	std::vector<long long> whichSym;
	std::vector<std::vector<std::pair<long long, long long> > > fnfv;

	/* Parse the rows of Tickfile into timestamp (tsMap), symbol (whichSym)
	 * and field name, value pairs (fnfv)
	 * Time: O(n), Space: O(N + F + S)
	 */
	for(long long i=0; i<queryStart; ++i) {
		std::string x=data[i];
		std::stringstream ss;
		ss << x;

		long long tStamp;
		long long sym;
		char c1;
		ss >> tStamp >> c1 >> sym;
		tsMap.push_back(tStamp);

		whichSym.push_back(sym);

		std::vector<std::pair<long long, long long> > temp;

		char c;
		long long fnum, fval;
		while(ss >> c >> fnum >> fval) {
			temp.push_back(std::make_pair(fnum, fval));
		}

		fnfv.push_back(temp);
	}

	/* Process the Queries */
	for(long long i=queryStart; i<data.size(); ++i) {
		std::string x=data[i];
		std::stringstream ss;
		ss << x;

		char c;
		long long startT, endT;
		long long sym, fnum;
		int K;
		ss >> x >> startT >> endT >> c >> sym >> c >> fnum >> K;

		/* Binary search for the start and end time */
		std::vector<long long>::iterator l, u;
		if(binary_search(tsMap.begin(), tsMap.end(), startT))
			l=std::lower_bound(tsMap.begin(), tsMap.end(), startT);
		else
			l=std::upper_bound(tsMap.begin(), tsMap.end(), startT);
		if(binary_search(tsMap.begin(), tsMap.end(), endT))
			u=std::upper_bound(l, tsMap.end(), endT);
		else
			u=std::lower_bound(l, tsMap.end(), endT);

		/* Push all field values that match the given query */
		std::vector<long long> fVec;
		for(;l<u;++l) {
			long long l_=l-tsMap.begin();
			if(whichSym[l_]==sym) {
				std::vector<std::pair<long long, long long> > temp=fnfv[l_];
				for(long long j=0; j<temp.size(); ++j) {
					if(temp[j].first==fnum) {
						fVec.push_back(temp[j].second);
					}
				}
			}
		}

		/* Sort the field values vector and return k maximum */
		sort(fVec.begin(), fVec.end(), cmp);
		for(int j=0; j<std::min((int)fVec.size(), K); ++j) {
			std::cout << fVec[j] << " ";
		}
		std::cout << std::endl;
	}
}

/* Cost of linear regression calculated and returned.
 * We use the formula for Least Square Regression for
 * calculating the value of slope (a) and intercept (b)
 * We then use it to calculate the Residual Sum of Square errors.
 */
long double getCost(std::vector<long long> x, std::vector<long long> y) {
	long double y_mu=0, x_mu=0, x_2=0, xy=0;
	long long n=x.size();
	for(long long i=0; i<n; ++i) {
		y_mu+=y[i];
		x_mu+=x[i];
		x_2+=(long double)x[i]*(long double)x[i];
		xy+=(long double)x[i]*(long double)y[i];
	}
	x_mu/=n;
	y_mu/=n;

	long double a,b,denom;
	denom=(x_2-n*x_mu*x_mu);
	b=(y_mu*x_2-x_mu*xy);
	a=(xy-n*x_mu*y_mu);

	long double cost=0;
	for(long long i=0; i<n; ++i) {
		long double temp=(1.0*(long double)y[i]*denom-(a*(long double)x[i]+b));
		cost+=temp*temp;
	}
	return cost/(denom*denom);
}

/** Function processForDelta::
  * Process the DELTA queries
	* Scan over the entries in between.
	* 
		TODO
	*/
void processForDelta(std::vector<std::string> data, long long queryStart) {
	std::vector<long long> tsMap;
	std::vector<long long> whichSym;
	std::vector<std::vector<std::pair<long long, long long> > > fnfv;

	/* Parse the rows of Tickfile into timestamp (tsMap), symbol (whichSym)
	 * and field name, value pairs (fnfv)
	 * Time: O(n), Space: O(N + F + S)
	 */
	for(long long i=0; i<queryStart; ++i) {
		std::string x=data[i];
		std::stringstream ss;
		ss << x;

		long long tStamp;
		long long sym;
		char c1;
		ss >> tStamp >> c1 >> sym;
		tsMap.push_back(tStamp);

		whichSym.push_back(sym);

		std::vector<std::pair<long long, long long> > temp;

		char c;
		long long fnum, fval;
		while(ss >> c >> fnum >> fval) {
			temp.push_back(std::make_pair(fnum, fval));
		}

		fnfv.push_back(temp);
	}

	for(long long i=queryStart; i<data.size(); ++i) {
		std::string x=data[i];
		std::stringstream ss;
		ss << x;

		char c;
		long long startT, endT;
		long long sym, fnum;
		int K;
		ss >> x >> c >> sym >> c >> fnum >> K;

		

		std::vector<long long>::iterator l=tsMap.begin(), u=tsMap.end();
		std::vector<long long> fVec, tStmpVec;
		for(;l<u;++l) {
			long long l_=l-tsMap.begin();
			if(whichSym[l_]==sym) {
				std::vector<std::pair<long long, long long> > temp=fnfv[l_];
				for(long long j=0; j<temp.size(); ++j) {
					if(temp[j].first==fnum) {
						fVec.push_back(temp[j].second);
						tStmpVec.push_back(tsMap[l_]);
					}
				}
			}
		}

		long long N=fVec.size();
		long double cost[N+1];

		cost[0]=0;
			cost[1]=K;
		for(long int r=1; r<N; ++r) {
			std::vector<long long> xx, yy;
			xx.push_back(tStmpVec[r]);
			yy.push_back(fVec[r]);

			long double optCost=cost[r]+K;
			for(long int j=r-1; j>=0; --j) {
				xx.push_back(tStmpVec[j]);
				yy.push_back(fVec[j]);
				long double tempCost=getCost(xx,yy)+cost[j]+K;
				if(tempCost<optCost)
					optCost=tempCost;
			}
			cost[r+1]=optCost;
		}
		std::cout << std::ceil(cost[N]) << std::endl;
	}
	
}

int main() {
	std::string tf;
	long long n;
	// Read the first line
	std::cin >> tf >> n;			
	std::getline(std::cin, tf);
	std::vector<std::string> data;

	long long queryStart=n;

	/* We buffer the entire tickfile and process
	   separately for each type of query */
	std::string x;
	long long i=0;		
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

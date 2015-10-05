#include<map>
#include<utility>
#include<string>
#include<iostream>
#include<sstream>
#include<unordered_map>
#include<cstring>
#include<vector>
using namespace std;

// data structure to store each row of the TickFile
class Tick
{
	public:
	int time;
	int symbol; //TODO: ASSUMPTION: s1 s2 ... etc.
	// TODO: ds? maybe vector?
	vector<pair<int, int> > fields;
	//int parse(string str) {
	pair<int, int> parse(string str) {
		istringstream ss(str);
		int name, val, fmax=-1;
		char c;

		ss>>time>>c>>symbol;

		while(ss>>c>>name>>val) {
			fmax = max(fmax, name);
			fields.push_back(pair<int, int> (name, val));
		}

		//return this->time;
		return (pair<int, int>(symbol, fmax));

	}

	void display() {
		//cout<<this->time<<" "<<this->symbol<<" ";
		for(auto kv : fields) {
			//cout<<kv.first<<" " << kv.second<<" "; 
		}
		//cout<<endl;
	}
};

void find_sum()
{

	cout<<"sum branch\n";
	int name, val, fmax=-1;
	char c;
	
	long long sum[N][smax][fmax];
	std::memset(&sum[0][0], 0, smax*fmax*sizeof(long long));
	
	for(int i=0; i<N; ++i) {
		//if (i>0) std::memcpy(&sum[i][0], &sum[i-1][0], fmax*smax*sizeof(long long));
	
		istringstream ss(lines[i]);
	
		ss>>time>>c>>symbol;
	
		while(ss>>c>>name>>val) {
			fmax = max(fmax, name);
			fields.push_back(pair<int, int> (name, val));
		}
	
		//return (pair<int, int>(symbol, fmax));
	
	
		//for(auto kv : ticks[i].fields) {
		//	sum[i][ticks[i].symbol - 1][kv.first - 1] += kv.second;
		//}
	}
	//delete [] ticks;
	cout<<"tickfile completed\n";
	
	//cout<<endl<<endl;
	for(int i=0; i<N; ++i) {
		for(int j=0; j<smax; ++j) {
			for(int l=0; l<fmax; ++l) {
				//cout<<sum[i][j][l]<<" ";
			}
			//cout<<endl;
		}
		//cout<<endl;
	}
	//cout<<endl;
		
	
	// NOTE THAT IT IS NOT NECESSARY THAT A TEST TIMESTAMP BE IN DATA
	// Read and answer queries!
	int t1, t2, f1, sym;
	long long s; char c;
	//while(getline(std::cin, line)) {
	//	//cout<<line<< endl;
	//	istringstream is(line);
	//	s = 0;
	
	//	is>>temp>>t1>>t2>>c>>sym>>c>>f1;
	//	//cout<<t1<<" "<<t2<<" "<<sym<<" "<<f1<<" "<<endl;
	
	//	pair<multimap<int, int>::iterator, multimap<int, int>::iterator> start = index.equal_range(t1);
	//	//start.second --;
	//	// Key not found
	//	if(start.first->second == start.second->second) {
	//		// t1 is greater than maximum key present, it returns N, first element
	//		if (start.first->first == N) {
	//			cout<<"0\n";
	//			continue;
	//		}
	
	//	}
	//	// t2 is less than min key present
	//	pair<multimap<int, int>::iterator, multimap<int, int>::iterator> last = index.equal_range(t2);
	//	// when key t2 is less than min key present, it returns first element
	//	if(last.first->second == last.second->second && last.first->second == 0) {
	//		cout<<"0\n";
	//		continue;
	//	}
	//	// if found, [1..n), if not found, first element after this
	//	last.second--;
	
	//	// end time less than start time
	//	if (last.second->second < start.first->second) {
	//		cout<<"0\n";
	//		continue;
	//	}
	
	//	s = sum[last.second->second][sym - 1][f1 - 1];
	//	if(start.first->second != 0) {
	//		start.first--;
	//		s = s- sum[start.first->second][sym - 1][f1 - 1];
	//	}
	
	//	//cout<<start.first->second<<" - "<<last.second->second<<endl;
	//	cout<<s<<endl;
	//}
}

int main()
{
	cin.sync_with_stdio(false);

	// Read and store N
	string temp; int N;
	cin>>temp>>N;

	//cout<<N<<endl;

	//TODO: USE read!
	// Store the tickfile entries in a buffer
	vector<string> lines;
	//stringstream ss;
	string line;
	//ostringstream tickfile;
	getline(std::cin, line);
	for(int i=0; i<N; ++i) {
		getline(std::cin, line);
		lines.push_back(line);
		//tickfile<<line<<endl;
	}
	//istringstream stream(tickfile.str()); //TODO: clear and reuse
	//ss.str(tickfile.str());
	//cout<<ss.str()<<endl;


	// Read TickFile from string stream and parse each line
	Tick *ticks = new Tick[N]; 	// TODO: remove
	multimap<int, int> index; //TODO: EQ order only in C++11
	int fmax=-1, smax=-1;

	//getline(std::cin, line);
	//for(int i=0; i<N; ++i) {
	//	getline(std::cin, line);
	//	//cout<<line<<endl;
	//	//TODO: don't need a class
	//	//		timestamp in map, rest in an array
	//	pair<int, int> p = ticks[i].parse(line);
	//	fmax = max(fmax, p.second); smax = max(smax, p.first);
	//	index.insert(pair<int, int>(ticks[i].time, i));
	//	ticks[i].display();
	//	//pair<multimap<int, int>::iterator, multimap<int, int>::iterator> ret = index.equal_range(1009);
	//	//ret.second --;
	//	//cout<<ret.first->second<<" - "<<ret.second->second<<endl;
	//}

	//cout<<smax<<endl<<fmax<<endl;

	// Read Type of Query
	char q_type; cin.get(q_type);
	//cout<<endl<<tickfile.str()[0]<<endl;


	switch (q_type) {
		case 's': {
		} break;

		case 'p': {
			//cout<<"product branch\n";
			long long sum[N][smax][fmax][fmax], size = smax*fmax*fmax*sizeof(long long);
			//long long ***sum[N], size = smax*fmax*fmax*sizeof(long long);
			std::memset(&sum[0][0], 0, size);

			for(int i=0; i<N; ++i) {
				if (i>0) std::memcpy(&sum[i][0], &sum[i-1][0], size);
				for(auto kv : ticks[i].fields) {
					for(auto iv : ticks[i].fields) {
						sum[i][ticks[i].symbol - 1][kv.first - 1][iv.first -1] += kv.second * iv.second;
					}
				}
			}
			delete [] ticks;
			cout<<"tickfile completed\n";

			//cout<<endl<<endl;
			//for(int i=0; i<N; ++i) {
			//	for(int j=0; j<smax; ++j) {
			//		for(int l=0; l<fmax; ++l) {
			//			//cout<<sum[i][j][l]<<" ";
			//		}
			//		//cout<<endl;
			//	}
			//	//cout<<endl;
			//}
			//cout<<endl;
				
		
			//// NOTE THAT IT IS NOT NECESSARY THAT A TEST TIMESTAMP BE IN DATA
			//// Read and answer queries!
			int t1, t2, f1, f2, sym;
			long long s; char c;
			while(getline(std::cin, line)) {
				//cout<<line<< endl;
				istringstream is(line);
				s = 0;

				is>>temp>>t1>>t2>>c>>sym>>c>>f1>>c>>f2;
				//cout<<t1<<" "<<t2<<" "<<sym<<" "<<f1<<" "<<endl;

				pair<multimap<int, int>::iterator, multimap<int, int>::iterator> start = index.equal_range(t1);
				//start.second --;
				// Key not found
				if(start.first->second == start.second->second) {
					// t1 is greater than maximum key present, it returns N, first element
					if (start.first->first == N) {
						cout<<"0\n";
						continue;
					}

				}
				// t2 is less than min key present
				pair<multimap<int, int>::iterator, multimap<int, int>::iterator> last = index.equal_range(t2);
				// when key t2 is less than min key present, it returns first element
				if(last.first->second == last.second->second && last.first->second == 0) {
					cout<<"0\n";
					continue;
				}
				// if found, [1..n), if not found, first element after this
				last.second--;

				// end time less than start time
				if (last.second->second < start.first->second) {
					cout<<"0\n";
					continue;
				}

				s = sum[last.second->second][sym - 1][f1 - 1][f2 -1];
				if(start.first->second != 0) {
					start.first--;
					s = s- sum[start.first->second][sym - 1][f1 - 1][f2 -1];
				}

				//cout<<start.first->second<<" - "<<last.second->second<<endl;
				cout<<s<<endl;
			}
		} break;

		case 'm': {

		} break;

		case 'd': {

		} break;
	}

	return 0;
}

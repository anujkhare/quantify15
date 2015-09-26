#include<map>
#include<utility>
#include<string>
#include<iostream>
#include<sstream>
#include<unordered_map>
using namespace std;

// data structure to store each row of the TickFile
class Tick
{
	public:
	int time;
	string symbol; //TODO this!
	// TODO: ds? maybe vector?
	unordered_map<string, int> fields;

	//int parse(string str) {
	void parse(string str) {
		istringstream ss(str);
		string name; int val;

		ss>>time;
		ss>>symbol;

		while(ss>>name>>val) {
			fields.insert(pair<string, int> (name, val));
		}

		//return this->time;

	}

	void display() {
		cout<<this->time<<" "<<this->symbol<<" ";
		for(auto kv : fields) {
			cout<<kv.first<<" " << kv.second<<" "; 
		}
		cout<<endl;
	}
};

//void parse_max(
//{
//}

int main()
{
	cin.sync_with_stdio(false);

	// Read and store N
	istringstream ss;
	string line;

	getline(std::cin, line);
	ss.str(line);

	string temp; int N;
	ss>>temp>>N;

	cout<<N<<endl;

	//TODO: USE a REALLY fast input method
	//TODO: scanf's cin
	// Store the tickfile entries in a buffer
	ostringstream tickfile;
	for(int i=0; i<N; ++i) {
		getline(std::cin, line);
		tickfile<<line<<endl;
	}
	istringstream stream(tickfile.str()); //TODO: clear and reuse
	//ss.str(tickfile.str());
	//cout<<ss.str()<<endl;

	// Read Type of Query
	char q_type; cin.get(q_type);
	//cout<<endl<<tickfile.str()[0]<<endl;

	// Read TickFile from string stream and parse each line
	Tick ticks[N];
	multimap<int, int> index; //TODO: EQ order only in C++11

	switch (q_type) {
		case 's': {
			// TODO: NOTE THAT IT IS NOT NECESSARY THAT A TEST TIMESTAMP BE IN DATA
			cout<<"sum branch\n";

			for(int i=0; i<N; ++i) {
				getline(stream, line);
				//cout<<line<<endl;
				//TODO: don't need to store this
				ticks[i].parse(line);
				index.insert(pair<int, int>(ticks[i].time, i));
				ticks[i].display();
				//pair<multimap<int, int>::iterator, multimap<int, int>::iterator> ret = index.equal_range(1009);
				//ret.second --;
				//cout<<ret.first->second<<" - "<<ret.second->second<<endl;
			}
		
			// Read and answer queries!
			int t1, t2; string f1, sym;
			long long sum = 0;
			while(getline(std::cin, line)) {
				//cout<<line<< endl;
				istringstream is(line);
				sum = 0;

				is>>temp>>t1>>t2>>sym>>f1;
				//cout<<" "<<temp<<" "<<t1<<" "<<t2<<" "<<sym<<" "<<f1<<" "<<endl;
				cout<<t1<<endl;

				pair<multimap<int, int>::iterator, multimap<int, int>::iterator> ret = index.equal_range(t1);
				//ret.second --;
				// when key t1 is greater than maximum key present, it returns N, first element
				if(ret.first->second == ret.second->second && ret.first->first == N)
					sum = 0;
					
				// when key t2 is less than min key present, it returns 
				cout<<ret.first->first<<" - "<<ret.first->second<<endl;
				cout<<ret.second->first<<" - "<<ret.second->second<<endl;
				//cout<<ret.first->second<<" - "<<ret.first->secondret.second->second<<endl;
			}
		} break;

		case 'p': {

		} break;

		case 'm': {

		} break;

		case 'd': {

		} break;
	}

	return 0;
}

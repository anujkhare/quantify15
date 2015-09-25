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
	multimap<int, int> index; //TODO

	switch (q_type) {
		case 's': {
			cout<<"hello there!\n";
			for(int i=0; i<N; ++i) {
				getline(stream, line);
				//cout<<line<<endl;
				ticks[i].parse(line);
				index.insert(pair<int, int>(ticks[i].time, i));
				ticks[i].display();
			}

		} break;

		case 'p': {

		} break;

		case 'd': {

		} break;

		case 'm': {

		} break;
	}
	cout << "Done processing Tick file\n";	//TODO: where to put this?

	// Read and answer queries!
	while(getline(std::cin, line)) {
		int t1, t2, k;
		string f1, f2, symbol;
		cout<<line<< endl;
	}
	return 0;
}

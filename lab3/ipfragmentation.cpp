#include <bits/stdc++.h>
using namespace std;

#define HLEN 20

struct pkt {
	string message;
	int len;
};

vector<pkt> packets;

void fragment(string msg, int MTU) {
	int n = msg.size();
	int effective = MTU - HLEN;
	if(effective < 0) cout << "Fragmentation not possible" << endl;
	int sent_bytes = effective / 8;
	if (sent_bytes < 1) cout << "Fragmentation not possible" << endl; 

	int num_pac=ceil((double)n/((double)(sent_bytes*8)));
	cout<<num_pac<<endl;
	for(int i = 0; i < num_pac ; i++) {
		pkt *temp = new pkt;
		temp->len = sent_bytes * 8 + HLEN;
		string s = "";
		for(int j = 0; j < sent_bytes * 8; j++) {
			if(n>8*sent_bytes*i+j)
			s += msg[8*sent_bytes*i + j];
		}
		temp->message = s;
		packets.push_back(*temp);
	}

	for(int i = 0; i < packets.size(); i++) {
		cout << "Fragment " << i + 1 << ": " << packets[i].message << endl;
	}
}

string reassemble() {
	string m = "";
	for(int i = 0; i < packets.size(); i++) {
		m += packets[i].message;
	}
	return m;
}

int main() {
	string msg;
	cout << "input message (in binary)  : ";
	cin >> msg;
	int MTU;
	cout << "MTU size (greater than Header Length + 8 : " << HLEN + 8 << ") : ";
	cin >> MTU;
	fragment(msg, MTU);
	string m = reassemble();
	cout << "Reassembled = " << m << endl;
	return 0;
}
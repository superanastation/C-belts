#include<iostream>
#include<map>
#include<string>
#include<vector>

using namespace std;

void New_Bus(map<string, vector<string>>& bus_stop) {
	string name;
	int stop_count;
	cin >> name >> stop_count;
	for (int i = 0; i < stop_count; i++) {
		string stop;
		cin >> stop;
		bus_stop[name].push_back(stop);
	}
}

vector<string> busesForStop(const map<string, vector<string>>& bus_stop, const string& stop) {
	vector<string> buses;
	for (auto key : bus_stop) {
		for (auto name_stop:key.second)
		{
			if (name_stop == stop) {
				buses.push_back(key.first);
				break;
			}
		}
	}
	return buses;
}

void StopsForBus(const map<string, vector<string>>& bus_stop) {
	string bus;
	cin >> bus;
	bool exist = false;
	bool bbus = false;
	for (auto key : bus_stop) {
		if (key.first == bus) {
			exist = true;
			for (auto name_stop : key.second) {
				cout << "Stop " << name_stop << ": ";
				vector<string> buses = busesForStop(bus_stop, name_stop);
				if (buses.size() > 0) {
					for (auto all : buses) {
						if (all != bus)
						{
							cout << all << ' ';
							bbus = true;
						}
					}
				}
				if (!bbus)
					cout << "no interchange";
				cout << endl;
				bbus = false;
			}
			break;
		}
	}
	if (!exist)
		cout << "No bus" << endl;
}

void AllBuses(const map<string, vector<string>>& bus_stop) {
	if (bus_stop.size() > 0) {
		for (auto bustop : bus_stop) {
			cout << "Bus " << bustop.first << ": ";
			for (auto stop : bustop.second) {
				cout << stop << ' ';
			}
			cout << endl;
		}
	}
	else {
		cout << "No buses" << endl;
	}
		
}

int main() {
	int q;
	cin >> q;
	map<string, vector<string>> bus_stop; // first - маршрут second - вектор остановок
	for (int i = 0; i < q; i++) {
		string command;
		cin >> command;
		if (command == "NEW_BUS")
			New_Bus(bus_stop);
		else if (command == "BUSES_FOR_STOP") {
			string stop;
			cin >> stop;
			vector<string> buses = busesForStop(bus_stop, stop);
			if (buses.size() > 0) {
				for (auto all : buses) {
					cout << all << ' ';
				}
			}
			else
				cout << "No stop";
			cout << endl;
		}
		else if (command == "STOPS_FOR_BUS")
			StopsForBus(bus_stop);
		else if (command == "ALL_BUSES")
			AllBuses(bus_stop);
	}
	return 0;
}
#include<iostream>
#include<map>
#include<string>
#include<vector>

using namespace std;

void New_Bus(map<string, vector<string>>& bus_stop, vector<string>& buses) {
	string name;
	int stop_count;
	cin >> name >> stop_count;
	buses.push_back(name);
	for (int i = 0; i < stop_count; i++) {
		string stop;
		cin >> stop;
		bus_stop[name].push_back(stop);
	}
}

vector<string> busesForStop(const map<string, vector<string>>& bus_stop, const string& stop,const vector<string>& bus) {
	vector<string> buses;
	for (auto every : bus) {
		for (auto key : bus_stop) {
			if (every == key.first) {
				for (auto name_stop : key.second)
				{
					if (name_stop == stop) {
						buses.push_back(key.first);
						break;
					}
				}
				break;
			}
		}
	}
	return buses;
}

void StopsForBus(const map<string, vector<string>>& bus_stop, const vector<string>& bus_order) {
	string bus;
	cin >> bus;
	bool exist = false;
	bool bbus = false;
	for (auto key : bus_stop) {
		if (key.first == bus) {
			exist = true;
			for (auto name_stop : key.second) {
				cout << "Stop " << name_stop << ": ";
				vector<string> buses = busesForStop(bus_stop, name_stop, bus_order);
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
	vector<string> bus_ORDER;
	for (int i = 0; i < q; i++) {
		string command;
		cin >> command;
		if (command == "NEW_BUS")
			New_Bus(bus_stop, bus_ORDER);
		else if (command == "BUSES_FOR_STOP") {
			string stop;
			cin >> stop;
			vector<string> buses = busesForStop(bus_stop, stop, bus_ORDER);
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
			StopsForBus(bus_stop, bus_ORDER);
		else if (command == "ALL_BUSES")
			AllBuses(bus_stop);
	}
	return 0;
}
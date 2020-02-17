#include"database.h"

void Database::Print(ostream& os)
{
	for (const auto& item : base) {
		for (const auto& event : item.second) {
			os << item.first << " " << event << endl;
		}
	}
}
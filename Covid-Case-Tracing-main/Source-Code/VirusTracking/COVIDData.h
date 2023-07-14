#include <string>
using namespace std;

#ifndef COVID_DATA_H_
#define COVID_DATA_H_

class COVIDData
{
public:
	string day;
	long cases;
	long deaths;
	string country;
	string continent;
	long population;

	COVIDData(string day, long cases, long deaths, string country, long population, string continent)
	{
		this->day = day;
		this->cases = cases;
		this->deaths = deaths;
		this->country = country;
		this->population = population;
		this->continent = continent;
	}

	string toString()
	{
		return "COVIDData [day=" + day + ", cases=" + to_string(cases) + ", deaths=" + to_string(deaths) + ", country=" + country
				+ ", continent=" + continent + ", population=" + to_string(population) + "]";
	}

	bool operator==(const COVIDData* n2){
		return this->equals(n2);
	}

	bool equals(const COVIDData* n2)
	{
		if (this->cases != n2->cases)
			return false;
		if (!(this->continent == n2->continent))
			return false;
		if (! (this->country == n2->country))
			return false;
		if (!(this->day == n2->day))
			return false;
		if (this->deaths != n2->deaths)
			return false;
		if (this->population != n2->population)
			return false;
		return true;
	}
};

#endif

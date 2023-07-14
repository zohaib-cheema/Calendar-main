#include "CovidDataAnalyzer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>

// You will need to define attributes to manage the data here!
vector<COVIDData*>* data;
map<string, long> casesByContinent;
map<string, long> countryPopulations;
map<string, set<string>*> countriesOnContinent;

vector<COVIDData*>* readFile(string filename)
{
	vector<COVIDData*>* data = new vector<COVIDData*>;
	return data;
}

void generateReport(string country, string toFilename)
{
}

long getCasesForContinent(string continent)
{
	return 0;
}

long long getPopulationForContinent(string continent)
{
	return 0;
}

set<string>* getCountriesOnContinent(string continent)
{
	set<string>* countries = new set<string>;
	return countries;
}

#include "CovidTest.h"
#include "COVIDData.h"
#include "CovidDataAnalyzer.h"
#include "../helper/TestHelper.h"
#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

const int TOTAL_COUNT        = 46580;
string FILENAME        = "download.csv";
string REPORT_FILENAME = "belizeReport.csv";
string TEST_COUNTRY    = "Belize";

COVIDData FIRST("3/10/20", 5, 0, "Afghanistan", 38041757, "Asia");
COVIDData LAST("21/03/2020", 1, 0, "Zimbabwe", 14645473, "Africa");


string testLoad()
{
	string results;
	vector<COVIDData*>* data = readFile(FILENAME);
	results += checkEquals(data->size(), TOTAL_COUNT, "n/a", "You did not read the same number of records as is in the file");

	if (results.size() > 0)
	{
		return results;
	}

	COVIDData* first = data->front();
	results += checkTrue(FIRST == first, "n/a", "The first entry:\n" + first->toString() + "\ndoes not match the expected:\n" + FIRST.toString());
	COVIDData* last = data->back();
	results += checkTrue(LAST== last, "n/a", "The first entry:\n" + last->toString() + "\ndoes not match the expected:\n" + LAST.toString());
	return results;
}



string testReport()
{
	remove(REPORT_FILENAME.c_str());

	string results;
	results += testLoad();
	if (results.size() > 0)
	{
		return results;
	}

	vector<COVIDData*>* data = readFile(FILENAME);
	generateReport(TEST_COUNTRY, REPORT_FILENAME);

	ifstream reportFile;
	reportFile.open(REPORT_FILENAME);
	if (! reportFile)
	{
		results += "Tester did not find your report file: " + REPORT_FILENAME;
		return results;
	}

	string line;
	for(vector<COVIDData*>::size_type i = 0; i != data->size(); i++)
	{
		COVIDData* c = data->at(i);
		if(c->country == TEST_COUNTRY)
		{
			getline (reportFile,line);
			results += checkTrue(line.size() > 0, TEST_COUNTRY, "Not enough lines in your report file");
			stringstream tokens(line);
			string token;
			string day;
			string country;
			getline(tokens, country, ',');
			string continent;
			getline(tokens, continent, ',');
			getline(tokens, token, ','); // population
			int population = stoi(token);
			getline(tokens, day, ',');
			getline(tokens, token, ','); // cases
			int cases = stoi(token);
			getline(tokens, token, ','); // deaths
			int deaths = stoi(token);

			COVIDData* actual = new COVIDData(day, cases, deaths, country, population, continent);
			results += checkTrue(c->equals(actual), "n/a", "The entry:\n" + actual->toString() + "\ndoes not match the expected:\n" + c->toString());
			if (results.size() > 0)
			{
				return results;
			}
		}
	}
	return results;
}

string testCases()
{
	string results;
	results += testLoad();
	if (results.size() > 0)
	{
		return results;
	}

	map<string, long long> CONTINENT_CASES;
	CONTINENT_CASES["Asia"]    = 10814423L;
	CONTINENT_CASES["Oceania"] =    33791L;
	CONTINENT_CASES["America"] = 17043337L;
	CONTINENT_CASES["Africa"]  =  1498661L;
	CONTINENT_CASES["Europe"]  =  5289291L;

    for (const pair<string, long>& entry : CONTINENT_CASES)
	{
		long actual = getCasesForContinent(entry.first);
		results += checkEquals(actual, entry.second, entry.first, "Number of cases did not match");
	}
	return results;
}

string testPopulation()
{
	string results;
	results += testLoad();
	if (results.size() > 0)
	{
		return results;
	}

	map<string, long long> CONTINENT_POPULATION;
	CONTINENT_POPULATION["Asia"]    = 4542059903LL;
	CONTINENT_POPULATION["Oceania"] =   40438886LL;
	CONTINENT_POPULATION["America"] = 1013601796LL;
	CONTINENT_POPULATION["Africa"]  = 1306903030LL;
	CONTINENT_POPULATION["Europe"]  =  766212338LL;
    for (const pair<string, long long>& entry : CONTINENT_POPULATION)
    {
		long long actual = getPopulationForContinent(entry.first);
		results += checkEquals(actual, entry.second, entry.first, "Population did not match");
	}
	return results;
}


string testCountries()
{
	string results;
	results += testLoad();
	if (results.size() > 0)
	{
		return results;
	}

	map<string, int> CONTINENT_COUNTRIES;
	CONTINENT_COUNTRIES["Asia"]    = 43;
	CONTINENT_COUNTRIES["Oceania"] = 8;
	CONTINENT_COUNTRIES["America"] = 49;
	CONTINENT_COUNTRIES["Africa"]  =  55;
	CONTINENT_COUNTRIES["Europe"]  = 54;
    for (const pair<string, long>& entry : CONTINENT_COUNTRIES)
    {
		set<string>* countries = getCountriesOnContinent(entry.first);
		results += checkTrue(countries != NULL, entry.first, "Returned an null vector of countries");
		results += checkEquals(countries->size(), entry.second, entry.first, "Number of countries did not match");
	}
    return results;
}


string runCovidTests(string subtest)
{
	string results;

	if (subtest == "all")
	{
		cout << "------------------------------------\n";
        cout << "Testing readFile()\n";
        results += testLoad();
		cout << "------------------------------------\n";
        cout << "Testing generateReport()\n";
        results += testReport();
		cout << "------------------------------------\n";
        cout << "Testing getCasesForContinent()\n";
        results += testCases();
		cout << "------------------------------------\n";
        cout << "Testing getPopulationForContinent()\n";
        results += testPopulation();
		cout << "------------------------------------\n";
        cout << "Testing getCountriesOnContinent()\n";
        results += testCountries();
	} else if (subtest == "load") {results += testLoad();
	} else if (subtest == "report") {results += testReport();
	} else if (subtest == "cases") {results += testCases();
	} else if (subtest == "population") {results += testPopulation();
	} else if (subtest == "countries") {results += testCountries();
	} else {results = "Invalid Test";}

	return results;
}

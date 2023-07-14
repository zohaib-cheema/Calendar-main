#include "COVIDData.h"
#include <string>
#include <vector>
#include <set>

/**
 * Read the data in the know WHO format from the specified file
 * @param filename the name of the file to read
 * @return a list of COVIDData objects read from the file
 */
vector<COVIDData*>* readFile(string filename);

/**
 * Create a new report filtered to the specified country and stored in the specified
 * file.  The new file should use the following format
 * <country>, <continent>, <population>, <day>, <cases>, <deaths>
 * @param country - The country to report upon
 * @param toFilename - The destination filename to save the report
 */
void generateReport(string country, string toFilename);

/**
 * Retrieve the number of cases on each continent
 * @return a map with the key of the continent name and the
 *  value the total number of cases on that continent
 */
long getCasesForContinent(string continent);

/**
 * Retrieve the population of a continent
 * @param continent - the target
 * @return a map with the key of the continent name and the
 *  value the population of that continent
 */
long long getPopulationForContinent(string continent);

/**
 * Retrieve all the countries on a continent
 * @param continent - the target
 * @return a list of countries
 */
set<string>* getCountriesOnContinent(string continent);

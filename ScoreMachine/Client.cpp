#include "HighScoreManager.h"

using namespace std;

int main()
{
	// 1. Can create an instance of HighScoreManager with a new record
	HighScoreManager man("Alex", 90, "11/01/1987");

	// 2. Can add a second record
	man.createRecord("Baca", 55, "22/02/2012");

	// 3. Highest record is inserted at 0th pos
	man.createRecord("Petro", 91, "23/03/2013");

	// 4. Top ten records are printed out to the screen
	man.printTopTen();

	return 0;
}
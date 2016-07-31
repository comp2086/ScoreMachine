#include "HighScoreManager.h"

using namespace std;

int main()
{
	// 1. Can create an instance of HighScoreManager with a new record
	HighScoreManager man("Alex", 90, 2016, 11, 22);

	// 2. Can add a second record
	man.createRecord("Baca", 55, 2016, 11, 22);

	// 3. Highest record is inserted at 0th pos
	man.createRecord("Petro", 91, 2016, 11, 22);

	// 4. Top ten records are printed out to the screen
	man.printTopTen();

	system("PAUSE");
	return 0;
}
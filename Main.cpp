#include <iostream>
#include "RedBlackImpl.h"
#include "Main.h"
using std::cin;
using std::cout;
using std::endl;
#include <cstdio>
#include <time.h>
#include <cstdlib>

RedBlackImpl rbl;
timespec tmsp;
unsigned long long nano;
unsigned long long milli;

int insertion() {
	long input;
	long key;
	cout << endl;
	cout << "What is the count of elements you want to add?" << endl;
	cin >> input;

	for (int i = 1; i < input + 1; i++) {
		cout << "enter " << i << " value " << endl;
		cin >> key;

		rbl.insert(key);
	}

	cout << endl;
	return 0;
}
int bulkInsertion() {
	long input;
	cout << endl;
	cout << "What is the count of elements you want to add?" << endl;
	cin >> input;

	clock_settime(CLOCK_PROCESS_CPUTIME_ID, &tmsp);

	for (int i = 1; i < input + 1; i++) {
		rbl.insert(i);
	}

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tmsp);
	nano = (unsigned long long) (tmsp.tv_sec * 1000000000)
			+ (unsigned long long) tmsp.tv_nsec;
	milli = nano / 1000000;

	cout << endl;
	cout << input << " elements Insertion completed in " << milli
			<< " milliseconds" << endl;
	cout << endl;
	return 0;
}
int deletion() {
	long rmv;
	clock_settime(CLOCK_PROCESS_CPUTIME_ID, &tmsp);
	cout << endl;
	cout << "Enter the element you want to remove" << endl;
	cin >> rmv;
	cout << endl;
	rbl.deleteElement(rmv);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tmsp);
	nano = (unsigned long long) (tmsp.tv_sec * 1000000000)
			+ (unsigned long long) tmsp.tv_nsec;
	milli = nano / 1000000;
	cout << " deletion completed in " << milli << " milliseconds" << endl;
	cout << endl;
	return 0;
}
int elementSearch() {
	long searchElement;
	cout << "Enter the element num you want to search" << endl;
	cin >> searchElement;
	cout << endl;
	//cout << "Searching element..." << endl;
	rbl.searchTree(searchElement);
	return 0;
}

int deleteAll() {
	clock_settime(CLOCK_PROCESS_CPUTIME_ID, &tmsp);
	rbl.removeAll();
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tmsp);
	nano = (unsigned long long) (tmsp.tv_sec * 1000000000)
			+ (unsigned long long) tmsp.tv_nsec;
	milli = nano / 1000000;

	cout << "Deleting elements in " << milli << " milli seconds" << endl;
	cout << endl;
	return 0;
}

int main() {
	long option;
	bool flag = true;

	while (flag == true) {

		cout << "Red-Black Tree Operations" << endl;
		cout << "1. Insert" << endl;
		cout << "2. Bulk Insert" << endl;
		cout << "3. Delete Single Node" << endl;
		cout << "4. Delete All Nodes" << endl;
		cout << "5. Search" << endl;
		cout << "6. InorderTraversal" << endl;
		cout << "7. Display Red Black Tree Structure" << endl;
		cin >> option;

		switch (option) {
		case 1:
			insertion();
			break;
		case 2:
			bulkInsertion();
			break;
		case 3:
			deletion();
			break;
		case 4:
			deleteAll();
			break;
		case 5:
			elementSearch();
			break;
		case 6:
			rbl.inorderTraversal();
			break;
		case 7:
			rbl.print();
			break;
		default:
			break;
		}
	}
	return 0;
}

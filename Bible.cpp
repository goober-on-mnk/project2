// Bible class function definitions
// Computer Science, MVNU

#include "Ref.h"
#include "Verse.h"
#include "Bible.h" 
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

Bible::Bible() { // Default constructor
	infile = "/home/class/csc3004/Bibles/web-complete";
}

// Constructor – pass bible filename
Bible::Bible(const string s) { infile = s; }

// REQUIRED: lookup finds a given verse in this Bible
Verse Bible::lookup(Ref ref, LookupResult& status) {
	Verse final;
	if (status == NO_BOOK || status == OTHER) {
		final = Verse();
		return final;
	}
	status = OTHER;
	instream.open(infile, ifstream::in);
	string line;
	while (status == OTHER) {
		getline(instream, line);
		Ref r(line);
		if (r == ref) {
			status = SUCCESS;
		}
		if (r < ref) {
			status = OTHER;
		}
		if (r > ref) {
			if (r.getChap() > ref.getChap()) {
				status = NO_VERSE;
			}
			else if (r.getBook() > ref.getBook()) {      //1:50:30 2:1:1
				status = NO_CHAPTER;                //1:51:20 2:1:1
			}
			
		}
	}
	if (status == SUCCESS) {
		final = Verse(line);
	}
	else {
		final = Verse();
	}
	return final;
}
// REQUIRED: Return the next verse from the Bible file stream if the file is open.
// If the file is not open, open the file and return the first verse.
Verse Bible::nextVerse(LookupResult& status) {
	string line;
	getline(instream, line);
	Verse next(line);
	return next;
}

// REQUIRED: Return an error message string to describe status
string Bible::error(LookupResult status) {
	if (status == NO_CHAPTER) {
		return "Error: Chapter does not exist in the book of ";
	}
	else if (status == NO_VERSE) {
		return "Error: Verse does not exist in ";
	}
	else if (status == NO_BOOK) {
		return "Error: Book does not exist";
	}
	else if (status == OTHER) {
		return "Error: Invalid number of entries detected";
	}
	else {
		return "No error found";
	}
}
void Bible::display() {
	cout << "Bible file: " << infile << endl;
}
	
// OPTIONAL access functions
// OPTIONAL: Return the reference after the given ref
//Ref Bible::next(const Ref ref, LookupResult& status) { return; }

// OPTIONAL: Return the reference before the given ref
//Ref Bible::prev(const Ref ref, LookupResult& status) { return; }

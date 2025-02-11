// Ref class function definitions
// Computer Science, MVNU

#include "Ref.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;
map<int, string> BibleNames;

void makeMap() {
    BibleNames[1] = "Genesis";
    BibleNames[2] = "Exodus";
    BibleNames[3] = "Leviticus";
    BibleNames[4] = "Numbers";
    BibleNames[5] = "Deuteronomy";
    BibleNames[6] = "Joshua";
    BibleNames[7] = "Judges";
    BibleNames[8] = "Ruth";
    BibleNames[9] = "1 Samuel";
    BibleNames[10] = "2 Samuel";
    BibleNames[11] = "1 Kings";
    BibleNames[12] = "2 Kings";
    BibleNames[13] = "1 Chronicles";
    BibleNames[14] = "2 Chronicles";
    BibleNames[15] = "Ezra";
    BibleNames[16] = "Nehemiah";
    BibleNames[17] = "Esther";
    BibleNames[18] = "Job";
    BibleNames[19] = "Psalms";
    BibleNames[20] = "Proverbs";
    BibleNames[21] = "Ecclesiates";
    BibleNames[22] = "Song of Solomon";
    BibleNames[23] = "Isaiah";
    BibleNames[24] = "Jeremiah";
    BibleNames[25] = "Lamentations";
    BibleNames[26] = "Ezekiel";
    BibleNames[27] = "Daniel";
    BibleNames[28] = "Hosea";
    BibleNames[29] = "Joel";
    BibleNames[30] = "Amos";
    BibleNames[31] = "Obadiah";
    BibleNames[32] = "Jonah";
    BibleNames[33] = "Micah";
    BibleNames[34] = "Nahum";
    BibleNames[35] = "Habakkuk";
    BibleNames[36] = "Zephaniah";
    BibleNames[37] = "Haggai";
    BibleNames[38] = "Zechariah";
    BibleNames[39] = "Malachi";
    BibleNames[40] = "Matthew";
    BibleNames[41] = "Mark";
    BibleNames[42] = "Luke";
    BibleNames[43] = "John";
    BibleNames[44] = "Acts";
    BibleNames[45] = "Romans";
    BibleNames[46] = "1 Corinthians";
    BibleNames[47] = "2 Corinthians";
    BibleNames[48] = "Galatians";
    BibleNames[49] = "Ephesians";
    BibleNames[50] = "Philippians";
    BibleNames[51] = "Colossians";
    BibleNames[52] = "1 Thessalonians";
    BibleNames[53] = "2 Thessalonians";
    BibleNames[54] = "1 Timothy";
    BibleNames[55] = "2 Timothy";
    BibleNames[56] = "Titus";
    BibleNames[57] = "Philemon";
    BibleNames[58] = "Hebrews";
    BibleNames[59] = "James";
    BibleNames[60] = "1 Peter";
    BibleNames[61] = "2 Peter";
    BibleNames[62] = "1 John";
    BibleNames[63] = "2 John";
    BibleNames[64] = "3 John";
    BibleNames[65] = "Jude";
    BibleNames[66] = "Revelation";
   
}
// GetNextToken - general routine for getting next token from a string
// Parameters
//    str - string to search. search is destructive, i.e., token is removed.
//    delimiters - string, a list of characters to use a delimiters between tokens
// Returns: string token (removed from str)

string GetNextToken(string& str, const string& delimiters = " ") {
  // Skip delimiters at beginning                                          
  string::size_type startPos = str.find_first_not_of(delimiters, 0);
  // Find position of delimiter at end of token                                           
  string::size_type endPos = str.find_first_of(delimiters, startPos);

  // Found a token, remove it from string, and return it                       
  string next = str.substr(startPos, endPos - startPos);
  string rest = str.substr(endPos - startPos + 1, string::npos);
  str = rest;
  return(next);
}

// Ref member functions

Ref::Ref() {book = 0; chap = 0; verse = 0;}  	// Default constructor

Ref::Ref(const string s) { // Parse constructor - receives a line "34:5:7 text"
    string rtext = s; // make local copy of string to avoid modifying parameter
    // parse the reference - notice, currently there is no error checking!
    // Get book number
    string strbook = GetNextToken(rtext,":");
    book = atoi(strbook.c_str());
    // Get the chapter number
    string strchap = GetNextToken(rtext,":");
    chap = atoi(strchap.c_str());
    // Get the verse number
    string strverse = GetNextToken(rtext," ");
    verse = atoi(strverse.c_str());
}

Ref::Ref(const int b, const int c, const int v) { 	// Construct Ref from three integers
	book = b;
	chap = c;
	verse = v;
}

// Accessors
int Ref::getBook() {return book;}	 // Access book number
int Ref::getChap() {return chap;}	 // Access chapter number
int Ref::getVerse() {return verse;}; // Access verse number

// TO DO: implement comparison functions
// REQUIRED: == comparison
bool Ref::operator==(const Ref r) {
    if (book != r.book) {
        return false;
    }
    if (chap != r.chap) {
        return false;
    }
    if (verse != r.verse) {
        return false;
    }
    return true;
}

// OPTIONAL: define < and > comparisons
bool Ref::operator<(const Ref r) {
    if (book < r.book) {
        return true;
    }
    if (book == r.book) {
        if (chap < r.chap) {
            return true;
        }
        if (chap == r.chap) {
            if (verse < r.verse) {
                return true;
            }
            if (verse == r.verse) {
                return false;
            }
        }
    }
    return false;
}
bool Ref::operator>(const Ref r) {
    if (book > r.book) {
        return true;
    }
    else if (book == r.book) {
        if (chap > r.chap) {
            return true;
        }
        else if (chap == r.chap) {
            if (verse > r.verse) {
                return true;
            }
            else if (verse == r.verse) {
                return false;
            }
        }
    }
    return false;
}

// TO DO: modify display function to show book name instead of book number
void Ref::display() { 	// Display Reference
     cout << BibleNames[book] << ":" << chap << ":" << verse;
}

string getName(int book) {
    return BibleNames[book];
}

int getBookNum(string book) {
    for (int i = 1; i < 67; i++) {
        string s = BibleNames[0];
        if (book == s) {
            return i;
        }
    }
    return 0;
}
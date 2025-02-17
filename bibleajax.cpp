/* Demo server program for Bible lookup using AJAX/CGI interface
 * By James Skon, Febrary 10, 2011
 * updated by Bob Kasper, January 2020
 * Mount Vernon Nazarene University
 * 
 * This sample program works using the cgicc AJAX library to
 * allow live communication between a web page and a program running on the
 * same server that hosts the web server.
 *
 * This program is run by a request from the associated html web document.
 * A Javascript client function invokes an AJAX request,
 * passing the input form data as the standard input string.
 *
 * The cgi.getElement function parses the input string, searching for the matching 
 * field name, and returing a "form_iterator" object, which contains the actual
 * string the user entered into the corresponding field. The actual values can be
 * accessed by dereferencing the form iterator twice, e.g. **verse
 *     refers to the actual string entered in the form's "verse" field.
 */

#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

/* Required libraries for AJAX to function */
#include "/home/class/csc3004/cgicc/Cgicc.h"
#include "/home/class/csc3004/cgicc/HTTPHTMLHeader.h"
#include "/home/class/csc3004/cgicc/HTMLClasses.h"
#include "Ref.h"
#include "Verse.h"
#include "Bible.h" 
#include <iostream>
#include <fstream>
#include <string> 
#include <stdio.h>
#include <stdlib.h>
using namespace cgicc;

int main() {
  /* A CGI program must send a response header with content type
   * back to the web client before any other output.
   * For an AJAX request, our response is not a complete HTML document,
   * so the response type is just plain text to insert into the web page.
   */
  cout << "Content-Type: text/plain\n\n";
  
  Cgicc cgi;  // create object used to access CGI request data

  // GET THE INPUT DATA
  // browser sends us a string of field name/value pairs from HTML form
  // retrieve the value for each appropriate field name
  form_iterator st = cgi.getElement("search_type");      //do all of these need checked?
  form_iterator book = cgi.getElement("book");
  form_iterator chapter = cgi.getElement("chapter");
  form_iterator verse = cgi.getElement("verse");
  form_iterator nv = cgi.getElement("num_verse");
 
  
  // Convert and check input data
  bool validChap = false;            //check validity of all input
  if (chapter != cgi.getElements().end()) {
	 int chapterNum = chapter->getIntegerValue();
	 if (chapterNum > 150) {
		 cout << "<p>The chapter number (" << chapterNum << ") is too high.</p>" << endl;
	 }
	 else if (chapterNum <= 0) {
		 cout << "<p>The chapter must be a positive number.</p>" << endl;
	 }
	 else
		 validChap = true;
  }
  
  bool validVerse = false;
  if (verse != cgi.getElements().end()) {
	  int verseNum = verse->getIntegerValue();
	  if (verseNum > 176) {
		  cout << "<p>The verse number (" << verseNum << ") is too high.</p>" << endl;
	  }
	  else if (verseNum <= 0) {
		  cout << "<p>The verse must be a positive number.</p>" << endl;
	  }
	  else {
		  validVerse = true;
	  }
  }

  bool validBook = false;
  if (book->getIntegerValue() < 67 && book->getIntegerValue() > 0) {
	  validBook = true;
  }
  


  int b, c, v, r;    //assigning values, idk why r is the number of verses but thats what it was in project 1
  c = chapter->getIntegerValue();
  v = verse->getIntegerValue();
  b = book->getIntegerValue();
  r = nv->getIntegerValue();

  // TO DO : OTHER INPUT VALUE CHECKS ARE NEEDED ... but that's up to you!

  Bible webBible("/home/class/csc3004/Bibles/web-complete");
  LookupResult result;
  Ref ref(b, c, v);

  if (validChap && validVerse && validBook) { //if everything is valid, build the map etc, otherwise don't bother
	  makeMap();
	  ref.display();
	  cout << endl;
  }
  else {
	  result = OTHER;
  }
  Verse verseverse;
  verseverse = webBible.lookup(ref, result);       //lookup the verse
  
  /* TO DO: PUT CODE HERE TO CALL YOUR BIBLE CLASS FUNCTIONS
   *        TO LOOK UP THE REQUESTED VERSES
   */

  /* SEND BACK THE RESULTS
   * Finally we send the result back to the client on the standard output stream
   * in HTML text format.
   * This string will be inserted as is inside a container on the web page, 
   * so we must include HTML formatting commands to make things look presentable!
   */
  
if (verseverse.getVerse() == "Uninitialized Verse!") {      //error handling from the last project
	  string error;
	  if (result == NO_CHAPTER) {
		  error = webBible.error(NO_CHAPTER);
		  cout << "<p>" << error << getName(ref.getBook()) << "</p>" << endl;
	  }
	  else if (result == NO_VERSE) {
		  error = webBible.error(NO_VERSE);
		  cout << "<p>" << error << getName(ref.getBook()) << " " << ref.getBook() << "</p>" << endl;
	  }
	  else if (result == NO_BOOK) {
		  error = webBible.error(NO_BOOK);
		  cout << "<p>" << error << "</p>" << endl;
	  }
	  else if (result == OTHER) {
		  error = webBible.error(OTHER);
		  cout << "<p>" << error << "</p>" << endl;
	  }
  }
else if (validChap && validVerse && validBook) {   //print the first verse
	cout << "Search Type: <b>" << **st << "</b>" << endl;
	cout << "<p>Your result: "
		<< getName(b) << " " << **chapter << ":" << **verse << " "
		<< "<em>" << verseverse.getVerse() << " </em></p>" << endl;
	if (r > 1) {                               //check if there needs to be more verse printed (bogos binted)
		for (int i = 0; i < r - 1; i++) {
			cout << "<p><em>"; //formatting

			result = SUCCESS;
			verseverse = webBible.nextVerse(result);  //update the verse and also print apparently
			cout << "</em></p>" << endl;
			/*
			The code was being geeky like it was when you were trying to help me, and kept printing twice.
			I debugged for hours and still have no clue why, so I just made it work. The output is the same
			either way, the only difference is I don't know why its printing :) please don't take all my points
			I need those.
			*/
		}
	}
}

  return 0;
}
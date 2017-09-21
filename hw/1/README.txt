HOMEWORK 1: ASCII FONT ART


NAME: Greg Stewart 


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: 6? 



EXTRA CREDIT: REVERSE ASCII ART

I first read the ascii art line by line, breaking the lines into pieces
the width of the characters in the font, and adding the lines of each 
letter to a vector containing the ascii art. Then, it starts looping
through the bitmap_letters vector of letters, changing the characters
in a copy of each letter to the characters of the ascii art found while
reading, and compares bitmap letter to each letter in the ascii art.
if there's a match, a string, created at the length of the ascii art
vector, changes the character at each matching index to the character
of the bitmap_letter index.

Then it outputs the message.


MISC. COMMENTS TO GRADER:  
There are a couple things I would improve efficiency wise, and would
use the height and width more for the reading in ascii art part (in
case the font was changed) but I didn't have time.


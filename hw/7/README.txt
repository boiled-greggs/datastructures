HOMEWORK 7: HALLOWEEN COSTUME MAPS


NAME: Greg Stewart 


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

  just the lecture notes

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: 6 



ORDER NOTATION ANALYSIS (ORIGINAL VERSION W/MAPS):
Adding Costume: O(log(n))
  due to the map searching for the location to add a new costume

Renting Costume: O(log(c) + log(n))
  must search through both the customers map and the costumes map,
  so for c customers and n costumes we get this order notation
  (even though it looks through both about two times)

Lookup: O(log(n) + m) ~ O(log(n))
  The costume must be found from the map first, so log(n), then
  the renters printed, so m. But m<<n so this reduces to O(log(n))

Print: O(c)
  Every customer must be printed in order so this is linear


EXTRA CREDIT (W/O MAPS)
What alternate data structures did you use?  What is the order
notation of each operation without maps?  What is the expected
performance difference?  Summarize the results of your testing.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)







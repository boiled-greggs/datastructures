HOMEWORK 6: HASHI RECURSION


NAME: Greg Stewart 



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

the website linked to from the pdf

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: 22 



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h) 
The number of nodes/islands (n)? 
The number of edges/bridges (e)?
Etc. 

My program examines each node, checking which bridges are possible,
and follows paths down every possibility, adding them if they work out.
there are n/2 possible edges, i.e. e = n/2. Since it goes to each node,
and each node could build a bridge four ways, this is roughly 

  O( 4^n )


SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES:
# of solutions & approximate wall clock running time for different
puzzles for a single solution or all solutions.  Also, describe the
image in words.

For smaller puzzles, the solution is almost instantaneous.
As I wasn't able to finish the assignment, I'm not sure
how long bigger puzzles would take with this method, but
I imagine it would be a bit longer. For a single solution, however,
not _extremely_ long, as in the case of all solutions.

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)
It took me quite a while to get my head around recursion in general,
but it's making more sense now and I think this is easily manageable
with a bit more work, given time.


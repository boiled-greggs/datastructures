HOMEWORK 10: IMAGE COMPARISON HASHING


NAME: Greg Stewart 


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

cplusplus.com
StackOverflow for a couple errors I got

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: 10 




i = # of images
w = width x h = height (average size image)
s x s = seed size
r x r = typical subregion match. 
t = hash table size 
c = fraction of hash table to compare


ANALYSIS OF SIMPLE ALGORITHM (RUNNING TIME & MEMORY USAGE)
Include a short explanation/justification of your answer.

The algorithm loops (potentially) over the entirety of both
images being compared, in nested for loops. So this part of
the algorithm is

O(w x h x w x h) = O(w^2 x h^2)

Then, the boxes are expanded, first horizontally, then vertically

O(r x s + r x r)

So overall, the order notation simplifies a bit

O(w^2 x h^2 + r x r) => O(w^2 x h^2)

This is quite bad. The memory usage, however, is good, as only
new Points are created to mark the offsets, and new ints to track
the progress of the bounding box. Once the images are loaded, 
little memory is actually used to find the box. So disregarding
the initialized images and vector regions, the memory usage is

O(1)


ANALYSIS OF HASH TABLE ALGORITHM (RUNNING TIME & MEMORY USAGE)
Include a short explanation/justification of your answer.

First, the images' seeds are hashed into tables, which requires
looping over the images. So this is

O(w x h)

After that, almost everything is an O(1) operation. My hash table
is a vector of vectors of Seed objects, and the size of the overall
vector is 256, as the hash function related the pixel values of a
seed to its index in the table. So getting the seed to compare
averages to O(128), which is finite and on the smaller side.
We'll call it O(1). So overall this algorithm is

O(w x h)

However, it uses much more memory than the simple algorithm as it
creates a large table to store every single seed, where each seed
is an object containing a (much much smaller) vector. the memory
usage is on the order

O(w x h x s x s)

Still, the algorithm is /much/ faster.


SUMMARY OF RESULTS: 
Test your implementation on a variety of images and command line
arguments and summarize and discuss the results (both running time and
quality of results).

-method hashtable -seed 10 -table 1000000 -compare 0.02 marbles.pgm marbles_1.pgm marbles_2.pgm marbles_3.pgm :

Real Time: 5.017s
Quality: simply lovely


-method simple -seed 10 marbles.pgm marbles_1.pgm marbles_2.pgm marbles_3.pgm :

Real Time: 29.067s
Quality: gets the bounding box, but only highlights one seed :(


-method hashtable -seed 5 -table 1000000 -compare 0.02 marbles.pgm marbles_1.pgm marbles_2.pgm marbles_3.pgm :

Real Time: 2.538s
Quality: mmph


-method simple -seed 5 marbles.pgm marbles_1.pgm marbles_2.pgm marbles_3.pgm :

Real Time: 31.279s
Quality: the same


-method hashtable -seed 5 -table 1000000 -compare 0.02 sunflowers.pgm sunflowers_1.pgm sunflowers_20.pgm sunflowers_17.pgm :

Real Time: 33.093s
Quality: almost perfect


-method simple -seed 5 sunflowers.pgm sunflowers_1.pgm sunflowers_20.pgm sunflowers_17.pgm :

Real Time: 21m43.472s     ...i'm not doing any more
Quality: pretty good i guess





EXTRA CREDIT -- MULTIPLE ROTATION AND/OR 90/180/270 ROTATION AND
HORIZONTAL/VERTICAL FLIP:
Discuss your implementation and results of testing.




MISC. COMMENTS TO GRADER:  
Optional, please be concise!







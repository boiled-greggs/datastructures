HOMEWORK 4: JAGGED ARRAY


NAME: Greg Stewart 


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

stackexchange for a couple drmemory errors


Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  10



ORDER NOTATION:
For each function, for each version (packed vs. unpacked).  
b = the number of bins
e = the number of elements
k = the number of elements in the largest bin

numElements
 unpacked: O(1)
 packed: O(1)

numBins
 unpacked: O(1)
 packed: O(1)

numElementsInBin
 unpacked: O(1)
 packed: O(1)

getElement
 unpacked: O(1)
 packed: O(1)

isPacked
 unpacked: O(1)
 packed: O(1)

clear
 unpacked: O(bk + b)    [ ~ b*(k+1+1) ]
 packed: O(b + e)    [ ~ b + e + 1 ]

addElement
 unpacked: O(k)   [ k + k + 1 + 1 + k + 1 ~ 3k + 3 ]
 packed: O(1)

removeElement
 unpacked: O(k)    [ k + k + 1 + k + 1 + 1 ~ 3k + 3 ]
 packed: O(1)

pack
 unpacked: O(bk + b + e)     [ b + e + b + b*k + b*k + b + b + 1 + 1 ~ 2bk + 4b + e ]
 packed: O(1)

unpack
 unpacked: O(1)
 packed: O(bk + b + e)     [ b + b + b*(k+k+1) + b + e ~ 2bk + 4b + e ]

print 
 unpacked: O(bk + b)    [ 1 + 1 + 1 + b + k*b ~ bk + b ]
 packed: O(b + e)     [ 1 + 1 + 1 + b + e ~ b + e ]

constructor w/ integer argument
 unpacked: O(b)
 packed: N/A (does not construct packed jagged array)

copy constructor
 unpacked: O(bk + b)      [ 1 + 1 + b + b + b + b*(k+k) + 1 + 1 ~ 2bk + 3b ]
 packed: O(b + e)      [ 1 + 1 + b + b + e + e + 1 + 1 ~ 2b + 2e ]

destructor
 unpacked: O(bk + b)      [ b*k + b + b ~ bk + 2b ]
 packed: O(b + e)      [ ~ b + e ]

assignment operator
 unpacked: O(bk + b)     [ b*k + b + b + copy ~ bk + 2b + O(copy) => O(bk + b + bk + b) ]
 packed: O(b + e)     [ b + e + copy ~ b + e + O(copy) => O(b + e + b + e) ]




MISC. COMMENTS TO GRADER:  

For the order notation, I wasn't 100% sure what you wanted, so I show
the order notation I landed on first, then in [] the rough work and
thought process.

Also, since strings and floats could vary widely in display size (length),
their output may look strange, but following along the printed arrays one
can see that they are in the correct bins. This is obviously not a problem
with ints and chars.

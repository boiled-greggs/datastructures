HOMEWORK 3: GPS TRACKING & STACK HACKING


NAME: Greg Stewart 


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassment, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: 6~7



PART 2: DIAGRAMMING MEMORY & MAKING HYPOTHESES
hw3_sketches.pdf

The descriptions are next to the diagrams in the pdf, but in case it's
illegible, here they are from top to bottom:

1. How the distance function should be. Data array is size n, and the
    distance output will be correct in this case, along with average
    speed. All the data objects will get the correct speed.


2. How the filter function should be. Both input and output are the 
    same size, which is what we want (same as original data array).
    the input array is read and coordinates averaged as they should
    be to add to the output array, and then the new path lengths are
    found, compared, and the comparison returned.


3. distance(), n < count. so the data array is too small, so the total distance
    is too small, and the speeds will not be written for every data
    point. this means the average speed will be wrong, along with
    path length and other dependents.


4. distance(), n > count. so the funciton attempts to access values beyond the end
    of the array, which at best does nothing but return bad values or
    mess with unallocated memory. at worst, though, it causes a memory
    error which ends in the program crashing from trying to write to 
    memory it's not allowed to.


5. filter(), size(input[]) > size(output[]). final data object of output will be set
    to input's last, which is an immediate error due to the different sizes.
    Then the function loops through input averaging position, and tries to add
    GPSData objects beyond where the memory is allocated for it, so there wil be an
    error related to memory allocation as it's attempted.


6. filter(), size(input[]) < size(output[]). first GPSData objects are the same for
    input and output, but the rest of output will have deafult values, which will
    lead to incorrect distance and average speed, making the program output
    incorrect. the percent change in path length will also be wrong, so the
    functioning of recursive filter will be affected as well.



PART 3: TESTING YOUR HYPOTHESES
I first tested the program in full working order, which generated the following
examples of the stack showing updated values for data before and after distance.

STACK BEFORE DISTANCE
input[count] location: 0xbff96358  POINTER: 0xbff96558
             location: 0xbff96354  VALUE:   0
             location: 0xbff96350  VALUE:   0
             location: 0xbff9634c  VALUE:   210
             location: 0xbff96348  VALUE:   0
             location: 0xbff96344  VALUE:   0
             location: 0xbff96340  VALUE:   180
             location: 0xbff9633c  VALUE:   0
             location: 0xbff96338  VALUE:   45
             location: 0xbff96334  VALUE:   150
             location: 0xbff96330  VALUE:   0
             location: 0xbff9632c  VALUE:   45
             location: 0xbff96328  VALUE:   60
             location: 0xbff96324  VALUE:   0
             location: 0xbff96320  VALUE:   90
             location: 0xbff9631c  VALUE:   30
             location: 0xbff96318  VALUE:   0
             location: 0xbff96314  VALUE:   75
    input[0] location: 0xbff96310  VALUE:   0
STACK AFTER DISTANCE
input[count] location: 0xbff96358  POINTER: 0xbff96558
             location: 0xbff96354  VALUE:   423
             location: 0xbff96350  VALUE:   0
             location: 0xbff9634c  VALUE:   210
             location: 0xbff96348  VALUE:   763
             location: 0xbff96344  VALUE:   0
             location: 0xbff96340  VALUE:   180
             location: 0xbff9633c  VALUE:   1270
             location: 0xbff96338  VALUE:   45
             location: 0xbff96334  VALUE:   150
             location: 0xbff96330  VALUE:   763
             location: 0xbff9632c  VALUE:   45
             location: 0xbff96328  VALUE:   60
             location: 0xbff96324  VALUE:   473
             location: 0xbff96320  VALUE:   90
             location: 0xbff9631c  VALUE:   30
             location: 0xbff96318  VALUE:   0
             location: 0xbff96314  VALUE:   75
    input[0] location: 0xbff96310  VALUE:   0

I did the same with the filter function, which clearly alters the values
of some positions, also changing the speeds for each data point.
STACK AFTER FILTER
 filtered[n] location: 0xbff96308  POINTER: 0xbff9652c
             location: 0xbff96304  VALUE:   473
             location: 0xbff96300  VALUE:   0
             location: 0xbff962fc  VALUE:   210
             location: 0xbff962f8  VALUE:   736
             location: 0xbff962f4  VALUE:   15
             location: 0xbff962f0  VALUE:   180
             location: 0xbff962ec  VALUE:   823
             location: 0xbff962e8  VALUE:   30
             location: 0xbff962e4  VALUE:   130
             location: 0xbff962e0  VALUE:   719
             location: 0xbff962dc  VALUE:   60
             location: 0xbff962d8  VALUE:   80
             location: 0xbff962d4  VALUE:   429
             location: 0xbff962d0  VALUE:   70
             location: 0xbff962cc  VALUE:   30
             location: 0xbff962c8  VALUE:   0
             location: 0xbff962c4  VALUE:   75
 filtered[0] location: 0xbff962c0  VALUE:   0

Next, I tested what would happen if the value of int n for distance was
less than the size of the array (by about half). It starts with the same input as above,
but the result is obviously quite erroneous. What happens here is what I expected - the
first several data are correctly written to with speed, but after it stops looping
speeds stop showing up. Additionally, the total distance is incorrect, throwing off
average speed too.
STACK AFTER DISTANCE w/ n < count
input[count] location: 0xbfff2348  POINTER: 0xbfff2548
             location: 0xbfff2344  VALUE:   0
             location: 0xbfff2340  VALUE:   0
             location: 0xbfff233c  VALUE:   210
             location: 0xbfff2338  VALUE:   0
             location: 0xbfff2334  VALUE:   0
             location: 0xbfff2330  VALUE:   180
             location: 0xbfff232c  VALUE:   1270
             location: 0xbfff2328  VALUE:   45
             location: 0xbfff2324  VALUE:   150
             location: 0xbfff2320  VALUE:   763
             location: 0xbfff231c  VALUE:   45
             location: 0xbfff2318  VALUE:   60
             location: 0xbfff2314  VALUE:   473
             location: 0xbfff2310  VALUE:   90
             location: 0xbfff230c  VALUE:   30
             location: 0xbfff2308  VALUE:   0
             location: 0xbfff2304  VALUE:   75
    input[0] location: 0xbfff2300  VALUE:   0

Next, I tried int n greater than the size of the array ( by several integers ).
As expected, for smaller values of n, only slightly larger than count, the effect
was on total values like average speed. But the array of input was unaffected and
written to correctly (it looks like the first example). However, for larger n,
I got an error that was quite clear about memory access being denied to
something not allocated.

malloc: *** error for object 0x54: pointer being freed was not allocated
*** set a breakpoint in malloc_error_break to debug
Abort trap: 6


To test incorrect uses of FILTER, I first made it so the input array was larger
than the output array. This resulted in a segmentation fault, as the program tried
to access memory that was allocated for the input array.

The other FILTER test was for the output array being larger than the input array.
So the input array worked as expected, but the output array (filtered) contained
all the filtered input[] values, plus many (10 more) default data objects,
severely reducing the average speed. the stack is below
input[count] location: 0xbff1f338  POINTER: 0xbff1f538
             location: 0xbff1f334  VALUE:   423
             location: 0xbff1f330  VALUE:   0
             location: 0xbff1f32c  VALUE:   210
             location: 0xbff1f328  VALUE:   763
             location: 0xbff1f324  VALUE:   0
             location: 0xbff1f320  VALUE:   180
             location: 0xbff1f31c  VALUE:   1270
             location: 0xbff1f318  VALUE:   45
             location: 0xbff1f314  VALUE:   150
             location: 0xbff1f310  VALUE:   763
             location: 0xbff1f30c  VALUE:   45
             location: 0xbff1f308  VALUE:   60
             location: 0xbff1f304  VALUE:   473
             location: 0xbff1f300  VALUE:   90
             location: 0xbff1f2fc  VALUE:   30
             location: 0xbff1f2f8  VALUE:   0
             location: 0xbff1f2f4  VALUE:   75
    input[0] location: 0xbff1f2f0  VALUE:   0
             location: 0xbff1f2ec  VALUE:   0
             location: 0xbff1f2e8  VALUE:   0
             location: 0xbff1f2e4  VALUE:   0
             location: 0xbff1f2e0  VALUE:   0
             location: 0xbff1f2dc  VALUE:   0
             location: 0xbff1f2d8  VALUE:   0
             location: 0xbff1f2d4  VALUE:   0
             location: 0xbff1f2d0  VALUE:   0
             location: 0xbff1f2cc  VALUE:   0
             location: 0xbff1f2c8  VALUE:   0
             location: 0xbff1f2c4  VALUE:   0
             location: 0xbff1f2c0  VALUE:   0
             location: 0xbff1f2bc  VALUE:   0
             location: 0xbff1f2b8  VALUE:   0
             location: 0xbff1f2b4  VALUE:   0
             location: 0xbff1f2b0  VALUE:   0
             location: 0xbff1f2ac  VALUE:   0
             location: 0xbff1f2a8  VALUE:   0
             location: 0xbff1f2a4  VALUE:   0
             location: 0xbff1f2a0  VALUE:   0
             location: 0xbff1f29c  VALUE:   0
             location: 0xbff1f298  VALUE:   0
             location: 0xbff1f294  VALUE:   0
             location: 0xbff1f290  VALUE:   0
             location: 0xbff1f28c  VALUE:   0
             location: 0xbff1f288  VALUE:   0
             location: 0xbff1f284  VALUE:   0
             location: 0xbff1f280  VALUE:   0
             location: 0xbff1f27c  VALUE:   0
             location: 0xbff1f278  VALUE:   0
             location: 0xbff1f274  VALUE:   473
             location: 0xbff1f270  VALUE:   0
             location: 0xbff1f26c  VALUE:   210
             location: 0xbff1f268  VALUE:   736
             location: 0xbff1f264  VALUE:   15
             location: 0xbff1f260  VALUE:   180
             location: 0xbff1f25c  VALUE:   823
             location: 0xbff1f258  VALUE:   30
             location: 0xbff1f254  VALUE:   130
             location: 0xbff1f250  VALUE:   719
             location: 0xbff1f24c  VALUE:   60
             location: 0xbff1f248  VALUE:   80
             location: 0xbff1f244  VALUE:   429
             location: 0xbff1f240  VALUE:   70
             location: 0xbff1f23c  VALUE:   30
             location: 0xbff1f238  VALUE:   0
             location: 0xbff1f234  VALUE:   75
 filtered[0] location: 0xbff1f230  VALUE:   0



PART 4: PASS-BY-VALUE VS PASS-BY-REFERENCE

printout at the beginning of function, before calculations:

                    location: 0xbff84778  POINTER: 0xbff847d4  ----> avg_feet_per_minute
                    location: 0xbff84774  VALUE:   6
                    location: 0xbff84770  POINTER: 0xbff84780  ----> data[0]
     return address location: 0xbff8476c  CODE: 0x7e300
  FUNCTION DISTANCE location: 0xbff84768  POINTER: 0xbff849c8
                    location: 0xbff84764  VALUE:   6
                    location: 0xbff84760  VALUE:   0
                    location: 0xbff8475c  VALUE:   210
                    location: 0xbff84758  garbage or float? 
                    location: 0xbff84754  garbage or float? 
                  n location: 0xbff84750  VALUE:   6

and after function runs, before returning value:

                    location: 0xbff84778  POINTER: 0xbff847d4  ----> avg_feet_per_minute
                    location: 0xbff84774  VALUE:   6
                    location: 0xbff84770  POINTER: 0xbff84780  ----> data[0]
     return address location: 0xbff8476c  CODE: 0x7e300
  FUNCTION DISTANCE location: 0xbff84768  POINTER: 0xbff849c8
                    location: 0xbff84764  VALUE:   6
                    location: 0xbff84760  VALUE:   0
                    location: 0xbff8475c  VALUE:   210
                    location: 0xbff84758  garbage or float? 
                    location: 0xbff84754  garbage or float? 
                  n location: 0xbff84750  VALUE:   6

As can be seen here, when the function is called the pointer is used to find
avg_feet_per_minute, which is succesfully altered to the correct value once the
function runs. It's interesting that the function has a pointer location,
and the return address can also be clearly seen, which it uses once the function
ends.



PART 5: STACK FRAMES OF A RECURSIVE FUNCTION
The most important part of the printed stack for recursive filter is

                          location: 0xbffa0510  POINTER: 0xbffa0530  ----> tmp[0]
           return address location: 0xbffa050c  CODE: 0x61c60
FUNCTION RECURSIVE_FILTER location: 0xbffa0508  POINTER: 0xbffa05f8  ----> FUNCTION RECURSIVE_FILTER

which includes the function pointer, return address, and pointer to the tmp
array used by the function. As expected, the functions runs fewer times for
greater % change tolerance and more times for less tolerance.


Looking at the stack so thoroughly (and so many times in so many situations)
was quite helpful in understanding how memory is assigned and what problems
can occur if you aren't careful. It's interesting seeing this low level
representation of what the computer really does when you run a program.

Paste the relevant portion of the stck visualization (abbreviate as
appropriate) and your observations about the operation of recursive
functions on the stack.



MISC. COMMENTS TO GRADER:  
Optional, please be concise!


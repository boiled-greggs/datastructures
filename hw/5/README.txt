HOMEWORK 5: BACKUP ESSAY


NAME: Greg Stewart 


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

None

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: 13 



MISC. COMMENTS TO GRADER:  

In student tests, the homework server errors and exits, but 
no such thing happens for me when I run exactly the same code, 
so I have ~no idea~ what's going on, and I don't know what the 
error message means. The test cases I made all work perfectly
fine on my machine ( I know there should be more unfortunately
got swamped with tests this week ) and so I'm not sure what else
to do here but say that they work on my computer.

Also, simply couldn't get to a successful copy contructor in time.
Should have spent more time on the test cases :(

In fact, here is my personal output experience:


in test_basic_list_operations()
  empty: 
  initial: apple banana carrot
  push_front:FRONT apple banana carrot
  insert:FRONT apple MIDDLE banana carrot
  after:FRONT apple MIDDLE banana carrot BACK
  erased:FRONT apple MIDDLE banana BACK
  pop front&back:apple MIDDLE banana
finished test_basic_list_operations()

in test_backup_and_revert()
  empty: 
  empty: 
  initial: apple banana carrot
  initial: 
  backup: apple banana carrot
  backup: apple banana carrot

  FIRST DIAGRAM
  head:apple     tail:carrot    backup_head:apple     backup_tail:carrot    
  -------------------------
  current essay:
  prev:NULL      backup_prev:NULL      value:apple              next:banana    backup_next:banana    
  prev:apple     backup_prev:apple     value:banana             next:carrot    backup_next:carrot    
  prev:banana    backup_prev:banana    value:carrot             next:NULL      backup_next:NULL      
  -------------------------
  backup essay:
  prev:NULL      backup_prev:NULL      value:apple              next:banana    backup_next:banana    
  prev:apple     backup_prev:apple     value:banana             next:carrot    backup_next:carrot    
  prev:banana    backup_prev:banana    value:carrot             next:NULL      backup_next:NULL      
  -------------------------

  push_front:FRONT apple banana carrot
  push_front:apple banana carrot
  insert:FRONT apple MIDDLE banana carrot
  insert:apple banana carrot
  after:FRONT apple MIDDLE banana carrot BACK
  after:apple banana carrot
  erased:FRONT apple MIDDLE banana BACK
  erased:apple banana carrot

  SECOND DIAGRAM
  head:FRONT     tail:BACK      backup_head:apple     backup_tail:carrot    
  -------------------------
  current essay:
  prev:NULL      backup_prev:NULL      value:FRONT(ADDED)       next:apple     backup_next:NULL      
  prev:FRONT     backup_prev:NULL      value:apple              next:MIDDLE    backup_next:banana    
  prev:apple     backup_prev:NULL      value:MIDDLE(ADDED)      next:banana    backup_next:NULL      
  prev:MIDDLE    backup_prev:apple     value:banana             next:BACK      backup_next:carrot    
  prev:banana    backup_prev:NULL      value:BACK(ADDED)        next:NULL      backup_next:NULL      
  -------------------------
  backup essay:
  prev:FRONT     backup_prev:NULL      value:apple              next:MIDDLE    backup_next:banana    
  prev:MIDDLE    backup_prev:apple     value:banana             next:BACK      backup_next:carrot    
  prev:NULL      backup_prev:banana    value:carrot(REMOVED)    next:NULL      backup_next:NULL      
  -------------------------

  revert:apple banana carrot
  revert:apple banana carrot
  pop front&back:banana
  pop front&back:apple banana carrot
finished test_backup_and_revert()

here
here
in test_splice()
  before splice:  the quick brown fox jumped over the lazy dogs

  BEFORE SPLICE
  head:the       tail:dogs      backup_head:the       backup_tail:dogs      
  -------------------------
  current essay:
  prev:NULL      backup_prev:NULL      value:the                next:quick     backup_next:quick     
  prev:the       backup_prev:the       value:quick              next:brown     backup_next:brown     
  prev:quick     backup_prev:quick     value:brown              next:fox       backup_next:fox       
  prev:brown     backup_prev:brown     value:fox                next:jumped    backup_next:jumped    
  prev:fox       backup_prev:fox       value:jumped             next:over      backup_next:over      
  prev:jumped    backup_prev:jumped    value:over               next:the       backup_next:the       
  prev:over      backup_prev:over      value:the                next:lazy      backup_next:lazy      
  prev:the       backup_prev:the       value:lazy               next:dogs      backup_next:dogs      
  prev:lazy      backup_prev:lazy      value:dogs               next:NULL      backup_next:NULL      
  -------------------------
  backup essay:
  prev:NULL      backup_prev:NULL      value:the                next:quick     backup_next:quick     
  prev:the       backup_prev:the       value:quick              next:brown     backup_next:brown     
  prev:quick     backup_prev:quick     value:brown              next:fox       backup_next:fox       
  prev:brown     backup_prev:brown     value:fox                next:jumped    backup_next:jumped    
  prev:fox       backup_prev:fox       value:jumped             next:over      backup_next:over      
  prev:jumped    backup_prev:jumped    value:over               next:the       backup_next:the       
  prev:over      backup_prev:over      value:the                next:lazy      backup_next:lazy      
  prev:the       backup_prev:the       value:lazy               next:dogs      backup_next:dogs      
  prev:lazy      backup_prev:lazy      value:dogs               next:NULL      backup_next:NULL      
  -------------------------

  after splice A: the fox jumped over the quick brown lazy dogs
  after splice B: the lazy fox jumped over the quick brown dogs

  AFTER SPLICE
  head:the       tail:dogs      backup_head:the       backup_tail:dogs      
  -------------------------
  current essay:
  prev:NULL      backup_prev:NULL      value:the                next:lazy      backup_next:quick     
  prev:the       backup_prev:the       value:lazy               next:fox       backup_next:dogs      
  prev:lazy      backup_prev:brown     value:fox                next:jumped    backup_next:jumped    
  prev:fox       backup_prev:fox       value:jumped             next:over      backup_next:over      
  prev:jumped    backup_prev:jumped    value:over               next:the       backup_next:the       
  prev:over      backup_prev:over      value:the                next:quick     backup_next:lazy      
  prev:the       backup_prev:the       value:quick              next:brown     backup_next:brown     
  prev:quick     backup_prev:quick     value:brown              next:dogs      backup_next:fox       
  prev:brown     backup_prev:lazy      value:dogs               next:NULL      backup_next:NULL      
  -------------------------
  backup essay:
  prev:NULL      backup_prev:NULL      value:the                next:lazy      backup_next:quick     
  prev:the       backup_prev:the       value:quick              next:brown     backup_next:brown     
  prev:quick     backup_prev:quick     value:brown              next:dogs      backup_next:fox       
  prev:lazy      backup_prev:brown     value:fox                next:jumped    backup_next:jumped    
  prev:fox       backup_prev:fox       value:jumped             next:over      backup_next:over      
  prev:jumped    backup_prev:jumped    value:over               next:the       backup_next:the       
  prev:over      backup_prev:over      value:the                next:quick     backup_next:lazy      
  prev:the       backup_prev:the       value:lazy               next:fox       backup_next:dogs      
  prev:brown     backup_prev:lazy      value:dogs               next:NULL      backup_next:NULL      
  -------------------------

finished test_splice()

here
here
here
here
here
here
here
here
in student_tests()
--------------------
Test 1: Empty Essay
--------------------
  head:NULL      tail:NULL      backup_head:NULL      backup_tail:NULL      
  -------------------------
  current essay:
  -------------------------
  backup essay:
  -------------------------

backing up empty test
backed up:
  head:NULL      tail:NULL      backup_head:NULL      backup_tail:NULL      
  -------------------------
  current essay:
  -------------------------
  backup essay:
  -------------------------

reverting:
  head:NULL      tail:NULL      backup_head:NULL      backup_tail:NULL      
  -------------------------
  current essay:
  -------------------------
  backup essay:
  -------------------------

trying pop_front, pop_back, erase
--------------------
Test 2: One Word Essay
--------------------
  head:one_word  tail:one_word  backup_head:NULL      backup_tail:NULL      
  -------------------------
  current essay:
  prev:NULL      backup_prev:NULL      value:one_word(ADDED)    next:NULL      backup_next:NULL      
  -------------------------
  backup essay:
  -------------------------

backup:
  head:one_word  tail:one_word  backup_head:one_word  backup_tail:one_word  
  -------------------------
  current essay:
  prev:NULL      backup_prev:NULL      value:one_word           next:NULL      backup_next:NULL      
  -------------------------
  backup essay:
  prev:NULL      backup_prev:NULL      value:one_word           next:NULL      backup_next:NULL      
  -------------------------

reverting after popping:
  head:one_word  tail:one_word  backup_head:one_word  backup_tail:one_word  
  -------------------------
  current essay:
  prev:NULL      backup_prev:NULL      value:one_word           next:NULL      backup_next:NULL      
  -------------------------
  backup essay:
  prev:NULL      backup_prev:NULL      value:one_word           next:NULL      backup_next:NULL      
  -------------------------

  head:word_2    tail:word_2    backup_head:one_word  backup_tail:one_word  
  -------------------------
  current essay:
  prev:NULL      backup_prev:NULL      value:word_2(ADDED)      next:NULL      backup_next:NULL      
  -------------------------
  backup essay:
  prev:NULL      backup_prev:NULL      value:one_word(REMOVED)  next:NULL      backup_next:NULL      
  -------------------------

erase:
  head:NULL      tail:NULL      backup_head:one_word  backup_tail:one_word  
  -------------------------
  current essay:
  -------------------------
  backup essay:
  prev:NULL      backup_prev:NULL      value:one_word(REMOVED)  next:NULL      backup_next:NULL      
  -------------------------

finished student_tests()


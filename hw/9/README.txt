HOMEWORK 9:  PRIORITY QUEUES FOR MESH SIMPLIFICATION


NAME: Greg Stewart 


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

LMS
cplusplus.com (info on stl priority_queue)

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: 18 


ALGORITHM ANALYSIS: 

Assume v_0 vertices, e_0 edges, and t_0 triangles in the initial mesh,
k edges connected to each vertex (average or worst case),
reduced to t_final triangles using the -shortest criteria.

What is the overall order notation for the program?  Analyze the
separate components of the program to justify your answer.

ALGORITHM ANALYSIS -- LINEAR:
Simplify() ->
  Collapse() -> as many times as it takes to get target triangle count
    FindEdge() -> O(e_0)
    RemoveEdge() -> O(log(k))
    RemoveTriangle -> O(log(t_0))
    RemoveVertex -> O(log(v_0))
  
    AddTriangle -> O(log(t_0))
      AddEdge -> O(log e_0 + log k )
      CollectEdgesWithVertex -> O(e_0*log(e_0))
      ReCalculateEdges -> O(e_0)

So overall the order notation is, after removing coefficients

O( (t_0-t_final) * ( e_0 + log(k) + log(t_0) + log(v_0) + log(e_0*k) + e_0*log(e_0) ) )



ALGORITHM ANALYSIS -- PRIORITY QUEUE:
Simplify()
  FindEdge() -> if using shortest, O(1); otherwise the same
  RemoveEdge() -> O(log(e_o))
  RemoveVertext -> O(log(v_0))
  RemoveTriangle -> O(log t_0)

  AddTriangle
    Add -> O(log t_0)
    O(log e_0)
    O(e_0*log e_0)
    O(e_0)

So the overall order notation is, after removing coeffs

O( (t_0 - t_final) * (1 + log e_0 + log v_0 + log t_0 + e_0log e_0 + e_0 ) )

This is a bit better than the linear one thanks to the queue.

ALGORITHM ANALYSIS -- IMPACT OF -preserve_area command line argument?
Do your answers above change with or without the -preserve_area
command line argument?  Describe.

preserve area would change the order notation a bit as some of the triangles
would be illegal to change, reducing the number needed to look through. 
however it's another thing for the program to deal with as it's running
so it might take longer in real use.





EXTRA CREDIT:  COLOR & OVERALL APPERANCE
Discuss the quality of your results in your README.txt and include
screenshots of your more impressive results.  If you have submitted
screenshots, give the file names and describe the results.



MISC. COMMENTS TO GRADER:  
Optional, please be concise!







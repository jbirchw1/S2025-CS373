## To Do:
- We are dealing with finite non-deterministic finite automata, so 
it will be necessary to keep track of *all* the states that the machine
could end up in. 
- Maybe, to this end, we should loop through each state (starting with the
start state and then adding from there) and read each new symbol.
- Could do this recursively, where we have a function to do a for loop 
through one list of states (that is, all the states after the input 
symbol is read) and then we create a new list, stack, queue, whatever
to pass to the function again. When there are no more input characters, 
just return the list. If the list contains an accept state, accept the string
and print the list of accept states. If it does not, reject the string and 
print the whole list.

- Create wrapper function
- In wrapper function (say, fn1()) run a while(string is not empty) or a for(each
  char in string) make a call to another function (say, fn2()). Keep a vector
  of the current states reachable by the input vector. Make the call to fn2()
  equal to the vector, or pass it as an argument.
- In fn2(), create a new vector and return it, this will be the new list of attainable
  states. For each element in the list, pop the current state out (first) and append to it 
  the list of reachable elements (should be easy since they're stored in a vector
  inside the unordered list)

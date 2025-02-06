## To Do:
- We are dealing with finitie non-deterministic finite automata, so 
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
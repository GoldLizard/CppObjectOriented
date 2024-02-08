This is a digital logic simulator. Instead of calculating each time frame, this uses an event queue.
Each change is calculated, then data is filled between since it should be constant.
This program has 4 state logic: 0, 1, undetermined, and ungenerated
    For example, OR gates can be evaluated if the inputs are 1 and undetermined, regardless of the second input
    Ungenerated data tells the program to wait until another event generates that input.
All circuits are configured in a txt.
Wires point to gates. Gates point to wires. 

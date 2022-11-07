# TargetGenerator
This is a simple set of C++ programs that generates, shuffles, and collates sets of coordinates for use in a shooting gallery test program.

TargetGenerator generates one set of practice targets, and three sets of main targets. A "target" in this case refers to only an X,Y,Z coordinate, 
as the orientation of any target is adjusted to face the player in the shooting gallery program.

Before generating the targets, index arrays are shuffled, and three distance labels called close, medium and far each assigned to a random third. Within each third, half
of the targets are assigned the movement label "static" the other half "dynamic" This tells the shooting gallery wether or not to move the target around (circle strafing left at random intervals)

It generates coordinates on a unit sphere within the limits set, and according to each distance label this coordinate is multiplied by the close, medium or far value.
The program then proceeds to generate a text file, and prints out a line with the coordinates, distance label and movement label for each target. 
It separates normal session with an @ symbol, and practice sessions with a $ session.

TargetShuffler is a program that takes an exisiting input file, reads it, shuffles the order of the targets, and prints it out into a new shuffled input file.

TargetConcatenator takes three input files, and organizes them into 36 input files, with unique testperson names, ready to be read by the shooting gallery program.

Video on showcasing the implementation of the shooting gallery program, including target generation: 

https://www.youtube.com/watch?v=MfGbIWZZK48

Recording of the master's thesis presentation this program was a part of:

https://www.youtube.com/watch?v=5e2Anc2IwSk





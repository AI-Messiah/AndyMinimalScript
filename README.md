	This is mostly finished except for error handling. Not everything has been tested but I was able to make a script that is fully functional. I will make a youtube video of it when it is complete.

	Unlike a lot of things I have seen this has instructions for it and I will document how it works.

	I kept things simple like this because as a scripting language this is all that I need right now when I have more time I might add more features, but I will change the name of this. 

	This is a simple scripting language written by Carle Banning it was created in an unconventional way yet it is amazingly simple. Instead of using a lexer and a parser it constructs the abstract syntax tree from extracting the arguments using string methods and placing a character in the string to represent that a node has been created and joining the nodes together. The tree is created from the bottom up and the trees evaluate themselves, when they are needed. The lines are represented by a type of struct that contains its type, 2 trees and their relation to each other and where to go next on a condition or automatically. The methods are compiled to a simple command structuure.
	It only has one data type (number the equivalent of double) which supports arrays and only has the required reserved words. All values except 0 are treated as true and boolean operations return 0 for false and 1 for true. It has no support for creating your own internal functions.
	
This manual is written for people who have some experience with programming I will write a beginners manual later.

I thought I would include a main file and a script. These are easy to delete when you use this yourself.

These are it's reserved words.

*def – necessary for variable creation. Variables are only assigned by numbers once created.
*while
*if
*else
*goto
*exit
*e - for scientific notation

when a variable goes out of scope it's assignments are removed however it's reference is stored. To be able to use it again it must be created again to be used. When it is created again it can be created with a different array size.

All arguments are passed with parentheses.

Variables must only contain letters and this is a case sensitive language.

Even though arguments are evaluated from left to right. Variables are evaluated after numbers, so with this.

A ^ 2 ^ 3

2 ^ 3 is evaluated first.  However you can use (A ^ 2) ^ 3

The internal functions are

*abs – Absolute value make value returned positive.
*acos – Arc cosine reverse of cosine.
*asin – Arc sine reverse of sine.
*atan – Arc tangent reverse of tangent.
*ceil – Ceiling round of decimal place upwards.
*cos – Cosine.
*cosh – Hyperbolic cosine.
*exp – Exponential e ^ X.
*floor - Floor  round of decimal place downwards.
*log - Natural Logarithm.
*sin - Sine
*sinh - Hyperbolic sine.
*tan - Tangent
*tanh - Hyperbolic tangent.
*distrand – Distributed random number, This is supposed to return numbers that are evenly distributed. takes no arguments.
*secrand – Hardware generated random number, This returns whatever the microprocessor returns. This is suposed to be the most secure method. takes no arguments. these both return a number between 0 <= x < 1

This file contains characters that have been mistaken for formatting when displayed in Github. Please read this as a text file.

The order of operations are.
() - parentheses.
^ - exponents.
* / \ - multiply, divide, float modular.
+ - - add, subtract.
& - bit and – limited to 64 bit unsigned integers.
| - bit or – limited to 64 bit unsigned integers.
> < == != >= <= greater, less, equal, not equal, greater or equal, less or equal.
! logical not.
&& logical and.
|| logical or.

*= /= \= += -= = assignment operators multiply, divide, float modular, add, subtract, direct all of these must be done with variables.

While, if and else statements use brackets { }

labels have a colon after them.

Remarks are indicated by a pound sign which is eaten before lines are processed otherwise it would cause an error, because the pound sign indicates nodes.

External functions can have zero or more than one argument. These are seperated by commas 

To use this language you need C++ version 20

include the file Interface.h and create an instance of the Interface class. To set an error handler you create a method for it that takes a vector of errInfo and returns void and pass the address to setErrorHandler. To create an external function you create a function which takes a vector of double and returns a double and pass its internal name and it's address to setFunction.

errInfo is a struct that contains 4 values:
int errType - this is the number associated with the type of error as defined in this system.
int errLine - the line number that the error was thrown from (this is not the actual line in the code that entered into the system because the lines are restructured)
string errMes - this contains some text to describe the error.
string lineText - this contains the text from the line that the error occured so you know what line it came from.

To run the script pass it as a string to handleScript.   

There is an external shutdown method if you want to run this system inside a thread. This already has a mutex in it.

This Operation restructures the lines so that brackets have their own line.

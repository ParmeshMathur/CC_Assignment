# CC_Assignment

### Parmesh Mathur
#### 2018A7PS0133G

An assignment for:
Course: Compiler Construction (CS F363)


1.	This repository contains the following:
	- scanner.l
	- parser.y
	- driver.cpp
	- makefile
	- Other .c and .h files created by running the makefile.



2.	The program is a 2048 interpreter. The porgram is assumed to be **run on a linux environment terminal**. The terminal should be opened with the path where the .zip file was extracted to.



3.	To run the program, the files have to be compiled first. To compile the program, execute the following command in the terminal: 
	`make`



4.	The above command will create a binary executable 'interactive'. Run the file:
	`./interactive`



5.	Once the program starts running, the user has to choose which implementation they prefer:
	- A tile is 'destroyed' as soon as the value it holds becomes zero (tiles will move through the location that the tile held).
	- A tile is 'destroyed' after all other required changes to the board have been made (the location is still held by an empty tile).



6.	There are 4 possible types of commands the user can enter into the interpreter shell:
	- A MOVE type command: To <ADD>|<SUBTRACT>|<MULTIPLY>|<DIVIDE> <LEFT>|<RIGHT>|<UP>|<DOWN> (Like the original 2048 game, but with more options.)
	- An ASSIGN type command: To assign a tile a particular value (Only positive values are allowed for assigning.)
	- A NAME type command: To give a name to desired tile (assuming chosen the tile holds a value, otherwise this command fails).
	- A QUERY type command: To find out the values (names) in a particular tile.

	**NOTE:** For any command which takes coordinates as inputs, the command fails if the coordinates are not valid.


	
7.	The porgram consistently follows that empty tiles (tiles with value 0 in them) cannot hold any names. This follows with all scenarios where a zero tile may be encountered or created.
	- If an tile is emptied by force (assigning it or obliterating it by subtraction), the names of the tiles will be removed and available for the naming for other tiles.
	- If the user tries to name an empty file, the command will fail, and return an error.


	
8. 	All the commands follow the general rules of syntax specified in the specs sheet.
		https://quanta.bits-goa.ac.in/pluginfile.php/16170/mod_resource/content/2/assignmentspecs.pdf


9.	The program prints a readable output to stdout for the user to see and understand the process and state of the program easily. An output is also printed to stderr, which has a specific format, for evaluation.


10.	To end the execution, the user can enter `Ctrl`+`D` or `Ctrl`+`C`, which cause the process to immediately exit.


11.	The user can run the followint to clear the files creted in 'make':
	`make clean`

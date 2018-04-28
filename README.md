# CLCalc - Command Line Calculator

Author: Patrick Vresky
Contact: pvresky@gmail.com

A command line calculator. Numeric type is double precision floating point. Supports addition, subtraction, multiplication, and division, along with parentheses. Correctly implements order of operations. Expression parsing performed in single-pass, left to right.

To terminate the application, type `exit` or `quit`.

#### Alphabet
`{0,1,2,3,4,5,6,7,8,9,.,+,-,*,/,(,),'exit','quit'}`

#### Grammar
expression &rarr; terminal + expression
terminal &rarr; terminal + primary
primary &rarr; primary


#### Error handling
Simply returns ERROR if an error is encountered during parsing. Please check that your input is a valid mathematical expression and that parentheses are balanced.

#### Compilation on Linux:
`gcc clcalc.cpp -o clcalc`

#### Compilation on Windows
From Visual Studio Developer Command Prompt, type

`cl /EHsc clcalc.cpp`

#### Usage
Simply input your mathematical expression and hit <Enter>

#### Example usage
Input:

`1+1`

Output:

`2`

Input:

`54.5-0.5`

Output:

`54.5`

Input:

`(88+74+66+72+95+82)/6`

Output:

`79.5`

Input:

`100*(0.88+0.74+0.66+0.72+0.95+0.82)/(1+1+1+1+1+1)`

Output:

`79.5`

Input:

`5+9*4+2`

Output:

`43`

Input:

`(5+9)*(4+2)`

Output:

`84`

Input:

`1/3*100`

Output:

`33.3333`

Input:

`1/(3*100)`

Output:

`0.00333333`

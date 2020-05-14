/*****************************************************************************
 * AUTHOR 	  		: Nick Reardon
 * Assignment #15	: Huffman Coding
 * CLASS			: CS1D
 * SECTION			: MW - 2:30p
 * DUE DATE			: 05 / 13 / 20
 *****************************************************************************/
#ifndef _PRINTHEADER_H_
#define _PRINTHEADER_H_

#include <iostream>
#include <iomanip>
#include <ostream>
#include <string>
#include <fstream>

/*****************************************************************************
* PrintHeader
* ---------------------------------------------------------------------------
* This function will output a class header through the use of ostream.
* It also will output the program description
* ----------------------------------------------------------------------------
*  Call
* ------
* The function call requires 1 parameters. The following example uses an
* output file in the ostream parameter. Ex:
*
* 		PrintHeader (oFile);
*
* ---------------------------------------------------------------------------
*  Output
* --------
* 	The function will output as follows. Ex:
*
* 		**********************************************************
*	 	* PROGRAMMED BY : Parsa Khazravi and Nick Reardon
*	 	* CLASS         : CS1B
*	 	* SECTION       : MW: 7:30pm
*	 	* Lab #3        : Functions - GCD
*	 	*********************************************************
*
* ---------------------------------------------------------------------------
* CONSTANTS
* ---------------------------------------------------------------------------
* OUTPUT - USED FOR CLASS HEADING
* ---------------------------------------------------------------------------
* PROGRAMMER 		: Name(s) of programmer(s) 	- Nick Reardon
* SECTION 	  		: Class times 				- MW - 7:30p
* CLASS 	  		: Class label 				- CS1B
* PROGRAM_NUM		: # of the program
* PROGRAM_NAME		: Title of the program
* PROGRAM_TYPE		: Type of program - Lab, Assignment, etc.
*
* ---------------------------------------------------------------------------
* MAX_OUTPUT		: Max movies to be output at once
*****************************************************************************/
const std::string PROGRAMMER = "Nick Reardon";
const std::string SECTION = "MW - 2:30p";
const std::string CLASS = "CS1D";
const int PROGRAM_NUM = 15;
const std::string PROGRAM_NAME = "Huffman Coding";
const std::string PROGRAM_TYPE = "Assignment";


void PrintHeader(std::ostream &output, std::string inputText)
{
	std::string typeNum = PROGRAM_TYPE + " #" + std::to_string(PROGRAM_NUM);

	output << std::left
		<< std::string(76, '*')
		<< std::endl
		<< "* PROGRAMMED BY : " << PROGRAMMER << std::endl
		<< "* " << std::setw(14) << "CLASS" << ": " << CLASS << std::endl
		<< "* " << std::setw(14) << "SECTION" << ": " << SECTION << std::endl
		<< "* " << std::setw(14) << typeNum << ": " << PROGRAM_NAME << std::endl
		<< std::string(76, '*')
		<< std::endl << std::endl
		<< std::string(((60 - typeNum.length() - PROGRAM_NAME.length() ) / 2), ' ')
		<< typeNum + " - " + PROGRAM_NAME
		<< std::endl << std::endl
		<< std::ifstream(inputText).rdbuf()
		<< std::endl
		<< std::string(76, '*')
		<< std::endl << std::endl;

}

#endif //_PRINTHEADER_H_
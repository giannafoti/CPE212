// ****************************************
// Program Title: Project_01
// Project File: Project01.cpp
// Name: Gianna Foti
// Course Section: CPE-212-01
// Due Date: 08/27/23
// program description: 6 functions included in the main.cpp file
// ****************************************

#include <iostream>
#include <fstream>
#include <string>

void LoadImage(const string imagefile, int image[MAXROWS][MAXCOLS])
{

	ifstream source; // initializing variable to open file
	int read; 	// priming read variable
	
	source.open(imagefile.c_str()); //opening imagefile
	source.ignore(200,'\n'); //ignoring the first 200 characters
	source >> read; // priming read the file
	
	for (int numRow = 0; numRow < MAXROWS && !source.eof(); numRow++) // initializing numRow and making sure the num of rows doesnt exceed the max num and not end of file, adds a row if loops through
	{
		for (int numCol = 0; numCol < MAXCOLS && !source.eof(); numCol++) // initializing numCol and making sure the num of cols doesnt exceed the max num and not end of file, adds a col if loops through
		{
			image[numRow][numCol] = read; //setting the image to the int
			source >> read; // looking into the array
		}
	}
	source.close();
}

// LoadImage() must open the image file for input and load the image into a

// two-dimensional array for subsequent processing.  Assume that the file will open.

// Parameter imagefile is a string that will hold the name of the image file to load.

// Parameter image is a two-dimensional array of integers representing the image

// loaded from the file

//

// Note: Correct operation of this function is critical!!  If one cannot correctly

//       load images into the array from the file, then one cannot test the

//       image processing operations and your code will fail every test!


void FlipHorizontal(int image[MAXROWS][MAXCOLS])
{
	int flipHarray[MAXROWS][MAXCOLS]; //empty array to store new info
	int newCol; //new columns
	for (int numRow = 0; numRow < MAXROWS; numRow++)
	{
		newCol = 0; //initializing newCol
		for (int numCol = MAXCOLS - 1; numCol >= 0; numCol--) //going through the array backwards and decrementing
		{
			flipHarray[numRow][newCol] = image[numRow][numCol]; //rows arent affected flipping horizontal
			newCol++;
		}	
	}
	for (int numRow = 0; numRow < MAXROWS; numRow++)
		{
			for (int numCol = 0; numCol < MAXCOLS; numCol++) //implementing the array back
			{
				image[numRow][numCol] = flipHarray[numRow][numCol];
			}	
		}
}

// FlipHorizontal() - must flip the image horizontally.  For example,

// column zero exchanged with column N-1, column one exchanged with column N-2, etc.

// Parameter image is a two-dimensional array of integers representing the image


void FlipVertical(int image[MAXROWS][MAXCOLS])
{
	int flipVarray[MAXROWS][MAXCOLS]; //empty array to store new info
	int newRow; //newrows
	for (int numCol = 0; numCol < MAXCOLS; numCol++)
	{
		newRow = 0;
		for (int numRow = MAXROWS - 1; numRow >= 0; numRow--) //going through the array backwards and decrementing
		{
			flipVarray[newRow][numCol] = image[numRow][numCol]; //cols arent affected flipping horizontal
			newRow++;
		}	
	}
	for (int numCol = 0; numCol < MAXCOLS; numCol++)
		{
			for (int numRow = 0; numRow < MAXROWS; numRow++) //i,plemeting the new array
			{
				image[numRow][numCol] = flipVarray[numRow][numCol];
			}	
		}
}

// FlipVertical() - must flip the image Vertically.  For example,

// row zero exchanged with row N-1, row one exchanged with row N-2, etc.

// Parameter image is a two-dimensional array of integers representing the image


void RotateCW(int image[MAXROWS][MAXCOLS])
{
	Transpose(image); //calling transpose then flipping it
	FlipHorizontal(image);
}

// RotateCW() - must rotate the image 90 degrees clockwise.

// Parameter image is a two-dimensional array of integers representing the image


void RotateCCW(int image[MAXROWS][MAXCOLS])
{
	Transpose(image); //calling transpose then flipping it
	FlipVertical(image);
}

// RotateCCW() - must rotate the image 90 degrees counter clockwise.

// Parameter image is a two-dimensional array of integers representing the image


void Transpose(int image[MAXROWS][MAXCOLS])
{
	int tranArray[MAXROWS][MAXCOLS];
	for (int numRow = 0; numRow < MAXROWS; numRow++)
		{
			for (int numCol = 0; numCol < MAXCOLS; numCol++)
			{
				tranArray[numRow][numCol] = image[numCol][numRow]; //flipping columns and rows
			}	
		}
		for (int numCol = 0; numCol < MAXCOLS; numCol++)
		{
			for (int numRow = 0; numRow < MAXROWS; numRow++) //implementing new array
			{
				image[numRow][numCol] = tranArray[numRow][numCol];
			}	
		}
}


// Transpose() - must flip the image across the primary diagonal row = column as

// with a matrix transpose

// Parameter image is a two-dimensional array of integers representing the image




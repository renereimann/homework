// Summer of C++ 
// Homework Week 1 
// Excercise 1.10.3 from "Discovering Modern C++: An Intensive Course for Scientists, Engineers, and Programmers (C++ In-Depth)" by Peter Gottschling
// Solution by: Rene Reimann

/* The Matrix Market data format is used to store dense and sparse matrices in ASCII format.
 * The header contains some information about the type and the size of the matrix. For a sparse matrix, the data is stored in three columns. The fist column is the row number, the
 * second column the column number, and the third column the numerical value. When the value type of the matrix is complex, a fourth column is added for the imaginary part.
 *  An example of a Matri Market file is
 * 
 * %%MatrixMarket martix coordinate real general
 * %
 * % ATHENS course matrix
 * %
 *           2025           2025             100015
 *              1              1         .9273558001498543E-01
 *              1              2         .3545880644900583E-01
 * ....................
 * 
 * The first line that does not start with % contains the number of rows, the number of columns,
 * and the number of non-zero elements on the sparse matrix.
 * Use fstream to read the header of a Matrix Market file and print the number of rows and columns, and the number of non-zeroes on the screen.
 */

#include <iostream>
#include <fstream>

// this function opens a file and reads the complete content and puts int in a char[]
void read_file(char *fileName, char *&content){
 
    std::ifstream is (fileName);
    
    if (is) {
        // get length of file:
        is.seekg (0, is.end);
        int length = is.tellg();
        is.seekg (0, is.beg);

        char * buffer = new char [length];

        std::cout << "Reading " << length << " characters... ";
        // read data as a block:
        is.read (buffer,length);

        if (is)
            std::cout << "all characters read successfully." << std::endl;
        else
            std::cout << "error: only " << is.gcount() << " could be read" << std::endl;
        is.close();
    
        content = buffer;
        
        delete buffer;
    }
}

// this function calls read_function and prints the content of the file
void test_get_relevant_line_using_read_function(){
    char * content;
    char fileName[] = "SparsMatrix.txt";
    std::cout << fileName << std::endl;
    read_file(fileName, content);
    
    std::cout << content << std::endl;
}

// this function opens a file goes through line by line and checks for the first line not starting with '%'
void test_get_relevant_line(){
    
    std::string str;
    const std::string fileName = "../src/SparsMatrix.txt";    
    std::ifstream myFile (fileName);
    int rows, cols, nonzeros;
    if(myFile.is_open()){
        
        while(std::getline(myFile, str)){
            if (str.at(0) == '%'){ continue; }
            myFile >> rows >> cols >> nonzeros;
            break;
        }
        myFile.close();
    }
    std::cout << str << " " << str.size() << std::endl;

}


int main(){
    // here we have our main solution

    //test_get_relevant_line_using_read_function();
    //test_get_relevant_line();
    
    int rows, cols, nonzeros;
    
    const std::string fileName = "SparsMatrix.txt";    
    std::ifstream myFile (fileName);
    
    if(myFile.good() && myFile.is_open()){
        
        char first_char_of_line;
        std::string line;
        
        // check first char of line and jump to next line if starts with '%'
        while(myFile >> first_char_of_line && first_char_of_line == '%'){
            myFile.seekg(-1, myFile.cur); // jump back one char in stream so we get the full line
            std::getline(myFile, line);
        }
        myFile.seekg(-1, myFile.cur);
        
        // here we are at the beginning of in the fist line after the '%' header
        // this line contains the numbers we are interestred in
        myFile >> rows >> cols >> nonzeros;
        myFile.close();
        
        // check that we got the right numbers by printing them
        std::cout << "Rows: "<< rows << std::endl;
        std::cout << "Cols: "<< cols << std::endl;
        std::cout << "Non-Zeros: "<< nonzeros << std::endl;
    }else{
        std::cout << "Failed to open file." << std::endl;
    }

    return 0;
}

#include <iostream>
#include <fstream>
#include <vector>


// saving the mat function
void saving_mat(std::vector<std::vector<int>> &mat , std::ofstream &file){
    
    file << mat.size() << " " << mat[0].size()  << "\n";

    for (int i = 0; i <mat.size() ; ++i){
        for (int j = 0; j < mat[i].size(); ++j){
            file << mat[i][j] << " "; 
        }
        file << "\n";
    }   
}


// a testing of writing and reading to files
int main(){
    
    // making the ofstream object (opening a file)
    std::ofstream myfile("matrix.txt");
    
    // checking if the file opened
    if(!myfile){
        std::cerr << "file did not open!";
        return;
    }

    std::vector<std::vector<int>> query_mat = {{5 , 1, 9 ,3} , {2 , 8 ,7 ,4} , {6 , 0,5,2}};
    
    // couting the matrix std::cout
    for (int i = 0; i <query_mat.size() ; ++i){
        for (int j = 0; j < query_mat[i].size(); ++j){
            std::cout << query_mat[i][j] << " ";    
        }
        std::cout << "\n";
    }

    //saving the matrix 
    saving_mat(query_mat , myfile);    

    // closing the file
    myfile.close();
}
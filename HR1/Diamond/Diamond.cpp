#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int max = 0;
int found = 0;
int max2 = 0;
int found2 = 0;
std::vector< std::vector<int> > temp;
std::vector< std::vector<int> > final;

bool path( std::vector< std::vector<int> >& mat, int x, int y, int rows, int cols, bool& flag){

	if ( x > rows || y > cols ){
		flag = false;
		return flag;
	}
	if ( x == rows && y == cols ){
		flag = true;
		return flag;
	}
	if ( x+1<=rows && mat[x+1][y] !=-1 ){

		path( mat, x+1, y, rows, cols, flag);
	}
	if ( y+1<=cols && mat[x][y+1] !=-1 ){
		path( mat, x, y+1, rows, cols, flag );
	}

	return flag;

}



bool find_max( std::vector< std::vector<int> >& mat, int x, int y, int rows, int cols){
	std::vector<int> v;
	v.push_back(x);
	v.push_back(y);
	temp.push_back(v);

	if( mat[x][y] == 1 ){
		found++;
	}

	bool flag = false;
	if( path(mat, x, y+1, rows, cols, flag) ){
		find_max( mat, x, y+1, rows, cols);
	}
	flag = false;
	if( path(mat, x+1, y, rows, cols, flag) ){
		find_max( mat, x+1, y, rows, cols);
	}

	if ( x == rows && y == cols ){
		if(found>max){
			max = found;
			final = temp;
		}
		temp.pop_back();
		return true;
	}

	if( mat[x][y] == 1 ){
		found--;
	}
	temp.pop_back();
	return false;

}




bool path2( std::vector< std::vector<int> >& mat, int x, int y, bool& flag){

	if ( x < 0 || y < 0 ){
		flag = false;
		return flag;
	}
	if ( x == 0 && y == 0 ){
		flag = true;
		return flag;
	}
	if ( x-1>=0 && mat[x-1][y] !=-1 ){

		path2( mat, x-1, y, flag);
	}
	if ( y-1>=0 && mat[x][y-1] !=-1 ){
		path2( mat, x, y-1, flag );
	}

	return flag;

}



bool find_max2( std::vector< std::vector<int> >& mat, int x, int y){

	if( mat[x][y] == 1 ){
		found2++;
	}

	bool flag = false;
	if( path2(mat, x, y-1, flag) ){
		find_max2( mat, x, y-1);
	}
	flag = false;
	if( path2(mat, x-1, y, flag) ){
		find_max2( mat, x-1, y);
	}

	if ( x == 0 && y == 0 ){
		if(found2>max2){
			max2 = found2;
		}
		return true;
	}

	if( mat[x][y] == 1 ){
		found2--;
	}

	return false;

}



int main(){

	std::ifstream input;
	std::ofstream output;
	input.open("input.txt");
	output.open("output.txt");

	std::string line;
	int rows;
	int cols;

	std::getline( input, line ); 
	std::istringstream iss1(line);
	iss1>>rows;

	std::getline( input, line ); 
	std::istringstream iss2(line);
	iss2>>cols;

	std::vector< std::vector<int> > mat(rows, std::vector<int>(cols)  );
	

	for (int r=0; r<rows; r++){
		std::getline(input, line);
		std::istringstream iss3(line);
		for(int c = 0; c< cols; c++){
			iss3>>mat[r][c];
		}
	}

	int dummy =0;
	if(mat[ 0 ][ 0 ] == 1){
		mat[ 0 ][ 0 ] = 0;
		dummy++;
	}


	if(mat[ rows-1 ][ cols-1 ] == 1){
		mat[ rows-1 ][ cols-1 ] = 0;
		dummy++;
	}

	find_max( mat, 0, 0, rows-1, cols-1);
	
	for (int i=0; i<final.size(); i++ ){
			mat[ final[i][0] ][ final[i][1] ] = 0;
	}

	find_max2( mat, rows-1, cols-1);
	std::cout<<max+max2+dummy<<std::endl;
	output<<max+max2+dummy;

	input.close();
	output.close();

	return 0;
}
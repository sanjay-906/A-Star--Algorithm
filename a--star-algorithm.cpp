#include<bits/stdc++.h>
using namespace std;
#define ROW 9
#define COL 9

typedef pair<int,int> Pair;
typedef pair<double, pair<int,int>> pPair;

struct cell{
	int parent_i, parent_j;
	double f, g, h;
};
bool isValid(int row, int col){
	return row>=0 and row<ROW and col>=0 and col<COL;
}
bool isUnBlocked(int grid[][COL], int row, int col){
	return grid[row][col]==1;
}
bool isDestination(int row, int col, Pair dest){
	if(row==dest.first and col== dest.second)
		return true;
	else 
		return false;
}
double calculateHvalue(int row, int col, Pair dest){
	return ((double)sqrt( pow(row-dest.first, 2) + pow(col-dest.second, 2) ));
}
void tracePath(cell cellDetails[][COL], Pair dest){
	cout<<"\nThe Path is: ";
	int row= dest.first;
	int col= dest.second;
	stack<Pair> Path;
	
	while(!(cellDetails[row][col].parent_i== row and cellDetails[row][col].parent_j== col)){
		Path.push({row, col});
		int temp_r= cellDetails[row][col].parent_i;
		int temp_c= cellDetails[row][col].parent_j;		
		row= temp_r;
		col= temp_c;
	}
	
	Path.push({row, col});
	while(!Path.empty()){
		auto p= Path.top();
		Path.pop();
		cout<<"->"<<"("<<p.first<<","<<p.second<<")";
	}
	return;
}
void a_star(int grid[][COL], Pair src, Pair dest){
	if(isValid(src.first, src.second)==false){
		cout<<"\nSource Invalid";
		return;
	}
	
	if(isValid(dest.first, dest.second)==false){
		cout<<"\nDestination Invalid";
		return;
	}
	
	if(isUnBlocked(grid, src.first, src.second)==false or isUnBlocked(grid, dest.first, dest.second)==false){
		cout<<"\nSource or Destination is blocked";
		return;
	}
	
	bool closedList[ROW][COL];
	memset(closedList, false, sizeof(closedList));
	cell cellDetails[ROW][COL];
	int i, j;	
	for(int i=0; i<ROW; i++){
		for(int j=0; j<COL; j++){
			cellDetails[i][j].f= FLT_MAX;
			cellDetails[i][j].g= FLT_MAX;
			cellDetails[i][j].h= FLT_MAX;
			cellDetails[i][j].parent_i= -1;
			cellDetails[i][j].parent_j= -1;
		}
	}	
	i= src.first, j= src.second;
	cellDetails[i][j].f= 0.0;
	cellDetails[i][j].g= 0.0;
	cellDetails[i][j].h= 0.0;
	cellDetails[i][j].parent_i= i;
	cellDetails[i][j].parent_j= j;
	
	set<pPair> openList;
	openList.insert({0.0,{i,j}});
	bool foundDest= false;
	
	while(!openList.empty()){		
		pPair p= *openList.begin();
		openList.erase(openList.begin());
		
		i= p.second.first;
		j= p.second.second;
		closedList[i][j]= true;
		
		double gNew, hNew, fNew;
		int xaxis[]= {-1,0,1,0,1,1,-1,-1};
		int yaxis[]= {0,-1,0,1,1,-1,1,-1};
		
		for(int k=0; k<8; k++){			
			int i0= i+ xaxis[k];
			int j0= j+ yaxis[k];
			
			if(isValid(i0, j0)){
				if(isDestination(i0, j0, dest)){
					cellDetails[i0][j0].parent_i= i;
					cellDetails[i0][j0].parent_j= j;
					cout<<"\nDestination Reached";
					tracePath(cellDetails, dest);
					foundDest= true;
					return;
				}
				else if(closedList[i0][j0]==false and isUnBlocked(grid, i0 , j0)){
					if(k>3)
						gNew= cellDetails[i0][j0].g + 1.414;
					else
						gNew= cellDetails[i0][j0].g + 1.0;
					hNew= calculateHvalue(i0,j0, dest);
					fNew= gNew+ hNew;
					
					if(cellDetails[i0][j0].f==FLT_MAX or cellDetails[i0][j0].f >fNew){
						openList.insert({fNew,{i0,j0}});
						
						cellDetails[i0][j0].f= fNew;
						cellDetails[i0][j0].g= gNew;
						cellDetails[i0][j0].h= hNew;
						cellDetails[i0][j0].parent_i= i;
						cellDetails[i0][j0].parent_j= j;
					}
				}
			}
		}			
	}
	if(!foundDest){
		cout<<"\nUnable to find Destination";
	}
	return;	
}
int main(){
	int grid[ROW][COL]={
		{1,0,1,0,1,0,1,1,1},
		{1,1,0,1,0,1,0,0,0},
		{0,0,1,0,0,1,0,0,1},
		{0,1,0,1,0,0,1,0,1},
		{1,1,0,1,0,1,0,1,1},
		{1,1,0,0,0,1,0,0,1},
		{1,0,1,1,1,0,0,1,0},
		{1,1,1,0,1,0,1,0,1},
		{1,1,1,1,1,1,0,1,1}	
	};
	a_star(grid, {8,8}, {0,0});
}

// #include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>

#include "parser.tab.h"

using namespace std;


//DATA STRUCTURES//
unordered_map <string, vector<int> > umap;

typedef struct tile
{
	int value;
	vector<string> names;
}tile;

vector<vector<tile> > board(4, vector<tile>(4));

int implement_type;
//DATA STRUCTURES//


//EXTERN FUNCTIONS//
extern int yyparse();
//EXTERN FUNCTIONS//


int randNum()
{
	int temp = rand()%5;
	if (temp==0) return 4;
	return 2;
}


int putRand()
{
	// printf("putRand called\n");
	int pos = rand()%16;
    int i=pos/4;
    int j=pos%4;

    while(board[i][j].value!=0)
    {
        pos++;
        pos%=16;
        i=pos/4;
        j=pos%4;
    }

    board[i][j].value=randNum();
    
    return 0;
}


int printBoard()
{
	// printf("printBoard called\n");
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<21;j++) cout<<'-';
		cout<<'\n';
		for(int j=0;j<4;j++)
		{
			cout<<'|';
			if(board[i][j].value!=0) cout<<setw(3)<<board[i][j].value<<' ';
			else cout<<"    ";
		}
		cout<<"|\n";
	}
	for(int j=0;j<21;j++) cout<<'-';
	cout<<"\n\n\n";

	return 0;
}


int printState()
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++) 
		{
			fprintf(stderr, "%d ", board[i][j].value);
		}
	}
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			int n;
			if((n=board[i][j].names.size())!=0)
			{
				fprintf(stderr, "%d,%d", i+1, j+1);
				for(int k=0;k<n;k++)
				{
					int m = board[i][j].names[k].length();
				    char temp[m + 1];
				    strcpy(temp, board[i][j].names[k].c_str());

					if(k<n-1) fprintf(stderr, "%s,", temp);
					else fprintf(stderr, "%s", temp);
				}
				fprintf(stderr, " ");
			}
		}
	}
	fprintf(stderr, "\n");
	printf("\n\n");
	return 0;
}


int mergeTiles(tile* src, tile* dest, int oper)
{
	int retval=0;
	// printf("mergeTiles called\n");
	switch(oper)
	{
		case 1:
		{
			dest->value*=2;
			break;
		}
		case 2:
		{
			dest->value=0;
			break;
		}
		case 3:
		{
			dest->value*=dest->value;
			break;
		}
		case 4:
		{
			dest->value=1;
			break;
		}
		default: break;
	}
	if(dest->value!=0)
	{
		dest->names.insert(dest->names.end(), src->names.begin(), src->names.end());
	}
	else
	{
		cout<<"Clearing out names of empty tile.\n\n";
		dest->names.clear();
		retval=1;
	}
	src->value=0;
	src->names.clear();

	return retval;
}


int operate(int oper, int dir)
{
	bool isChange=false;
	bool zeroed=true;
	int tempArr[4][4];
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			tempArr[i][j]=board[i][j].value;
		}
	}
	switch(dir)
	{
		case 1:
		{
            for(int i=0;i<4;i++)
            {
                int j=1;
                int k=0; //merging limit. Start from left most, keep moving right as tiles accumulate to left side.
                while(j<4)
                {
                    if(board[i][j].value!=0)	
                    {
                        zeroed=false;
                        if(board[i][k].value==0)
                        {
                        	board[i][k].value = board[i][j].value;
                        	board[i][k].names = board[i][j].names;
                        	board[i][j].value = 0;
                        	board[i][j].names.clear();
                        }
                        else if(board[i][k].value==board[i][j].value)
                        {
                        	// printf("gg1\n\n");
                        	if( mergeTiles(&(board[i][j]), &(board[i][k]), oper)==1 && implement_type==1 ) k--;
                        	k++;
                        }
                        else
                        {
                        	int tempval=board[i][j].value;
                        	vector<string> tempvec = board[i][j].names;
                        	board[i][j].value = 0;
                        	board[i][j].names.clear();
                        	board[i][k+1].value = tempval;
                        	board[i][k+1].names = tempvec;
                        	k++;
                        }
                    }
                    j++;
                }
            }
            // putRand();
            break;
        }
        case 2:
        {
        	for(int i=0;i<4;i++) reverse(board[i].begin(), board[i].end());
        	operate(oper, 1);
        	for(int i=0;i<4;i++) reverse(board[i].begin(), board[i].end());
        	break;
        	// printBoard();
        }
        case 3:
        {
        	for(int i=0;i<4;i++)
            {
                int j=1;
                int k=0; //merging limit. Start from left most, keep moving right as tiles accumulate to left side.
                while(j<4)
                {
                    if(board[j][i].value!=0)	
                    {
                        zeroed=false;
                        if(board[k][i].value==0)
                        {
                        	board[k][i].value = board[j][i].value;
                        	board[k][i].names = board[j][i].names;
                        	board[j][i].value = 0;
                        	board[j][i].names.clear();
                        }
                        else if(board[k][i].value==board[j][i].value)
                        {
                        	// printf("gg3\n\n");
                        	if( mergeTiles(&(board[j][i]), &(board[k][i]), oper)==1 && implement_type==1 ) k--;
                        	k++;
                        }
                        else
                        {
                        	int tempval=board[j][i].value;
                        	vector<string> tempvec = board[j][i].names;
                        	board[j][i].value = 0;
                        	board[j][i].names.clear();
                        	board[k+1][i].value = tempval;
                        	board[k+1][i].names = tempvec;
                        	k++;
                        }
                    }
                    j++;
                }
            }
            // putRand();
            break;
        }
        case 4:
        {
        	reverse(board.begin(), board.end());
        	operate(oper, 3);
        	reverse(board.begin(), board.end());
        	break;
        	// printBoard();
        }
        default: break;
	}
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(isChange) break;
			if(tempArr[i][j]!=board[i][j].value) 
			{
				isChange=true;
				break;
			}
		}
	}
	// if(dir==1 || dir==3) printBoard();
	// printState();
	if(!isChange && !zeroed) return 1;
	return 0;
}


int assign(int val, int x, int y)
{
	if(val<0)
	{
		printf("Cannot assign negative numbers to a tile. Try again.\n");
		fprintf(stderr, "-1\n" );
		return 1;
	}
	if(x<=0 || x>4 || y<=0 || y>4)
	{
		printf("Invlid coordinates. Coordinates must be from the range of integers [1,4].\n");
		fprintf(stderr, "-1\n" );
		return 1;
	}
	if(board[x-1][y-1].value!=0) 
	{
		cout<<"Replacing tile value with ";
		if(val==0) cout<<"empty tile.\n\n";
		else cout<<val<<".\n\n";
	}
	else
	{
		if(val==0) 
		{
			cout<<"Assigning empty tile.\n";
			board[x-1][y-1].names.clear();
			printf("Clearing tile names.\n\n");
		}
		else cout<<"Assigning "<<val<<".\n\n";

	}
	board[x-1][y-1].value = val;
	printBoard();
	printState();
	return 0;
}


int namer(string s, int x, int y)
{
	if(x<=0 || x>4 || y<=0 || y>4)
	{
		printf("Invlid coordinates. Coordinates must be from the range of integers [1,4].\n");
		fprintf(stderr, "-1\n");
		printf("\n");
		return 1;
	}
	if(board[x-1][y-1].value==0)
	{
		printf("Cannot assign name to empty tile.\n");
		fprintf(stderr, "-1\n");
		printf("\n");
		return 1;
	}
	if(umap.find(s)!=umap.end())
	{
		int x1 = umap[s][0];
		int y1 = umap[s][1];
		vector<string> temp = board[x1-1][y1-1].names;
		int n = temp.size();
		printf("Name already in use. Reassigning name to new tile.\n");
		for(int i=0;i<n;i++)
		{
			if(temp[i]==s)
			{
				// board[x1-1][y1-1].names.erase(i);
				for(int j=i;j<n-1;j++) board[x1-1][y1-1].names[i]=board[x1-1][y1-1].names[i+1];
				board[x1-1][y1-1].names.pop_back();
				break;
			}
		}
	}
	board[x-1][y-1].names.push_back(s);
	vector<int> coordinates{x,y};
	umap[s]=coordinates;
	printState();

	return 0;
}


int query(int x, int y)
{
	if(x<=0 || x>4 || y<=0 || y>4)
	{
		printf("Invlid coordinates. Coordinates must be from the range of integers [1,4].\n");
		fprintf(stderr, "-1\n" );
		return 1;
	}
	vector<string> temp = board[x-1][y-1].names;
	int n=temp.size();
	if(n==0) 
	{
		cout<<"Tile "<<x<< "," <<y<< " is empty and hence has no names.\n\n";
	}
	else
	{
		cout<<"Tile "<<x<< "," <<y<< " contains value "<<board[x-1][y-1].value<<"\n";
		cout<<"Named: ";
		for(int i=0;i<n-1;i++)
		{
			cout<<temp[i]<<',';
		}
		cout<<temp[n-1];
		cout<<"\n\n\n";
	}

	return 0;
}


int main(int argc, char const *argv[])
{
	//board init//
	printf("Hello!\n\n");
	implement_type=0;
	printf("Choose between the 4400 implementation (PRESS '1'), or the 4040 implementation (PRESS ANY OTHER VALID ASCII KEY):\n");
	int temp;
	scanf("%d", &temp);
	{
		if(temp==1)
		{
			printf("The 4400 implementation was chosen.\n");
			implement_type=1;
		}
		else printf("The 4040 implementation was chosen.\n");
	}
	printf("\n");
	printf("Initializing board\n");
	for(int i=0;i<4;i++)
	{
		vector<string> temp{};
		for(int j=0;j<4;j++)
		{
			board[i][j].value=0;
			board[i][j].names=temp;
		}
	}
	srand(time(NULL));
	putRand();
	printBoard();
	printf("2048> \n");
	//
	yyparse();
	return 0;
}
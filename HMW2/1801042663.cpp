#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>


/*V-->Solves the problem from the current configuration
using the new intelligent algorithm.
T-->Prints a report about how many moves have been
done and if the solution is found
E-->Asks a file name and saves the current board
configuration as a loadable shape file.
Y-->Asks a file name and loads the current board
configuration from the shape file.
L-->Moves the empty cell left if there is room
R-->Moves the empty cell right if there is room
U-->Moves the empty cell up if there is room
D-->Moves the empty cell down if there is room
I-->Makes an “intelligent” move for you. Intelligent
move moves the blank tile in a way that after the
move, the tiles are closer to their final positions. You
may add extra intelligence if you like!
S-->Shuffle- takes the board to the final solution, and
makes size*size random moves to shuffle the board.
Q-->Quits the game*/




using namespace std;

#define MAX_SIZE 9
#define COMP_ARR_SIZE 4
#define DIGIT 2


void printing_board(char str[MAX_SIZE][MAX_SIZE][DIGIT],int row,int column);
void save_board_file(char str[MAX_SIZE][MAX_SIZE][DIGIT],int row,int column,string FileName);
void save_board_other_file(char str[MAX_SIZE][MAX_SIZE][DIGIT],int row,int column,string FileName);
void load_board_file(char str[MAX_SIZE][MAX_SIZE][DIGIT],int row,int column,string FileName);
void find_space_place(char str[MAX_SIZE][MAX_SIZE][DIGIT],int *x,int *y,int row,int column);
void swap(char *x,char *y);
void finding_true_place(char correct_str[MAX_SIZE][MAX_SIZE][DIGIT],int *x,int *y,char temp[2],int row,int column);
void contd_or_finish(char str[MAX_SIZE][MAX_SIZE][DIGIT],char correct_str[MAX_SIZE][MAX_SIZE][DIGIT],int row,int column,int *s);
void shuffle(char correct_str[MAX_SIZE][MAX_SIZE][DIGIT],int row,int column);


int main(int argc, char const *argv[])
{
	ifstream inputStream,outputStream,sStream;
	ofstream SaveStream;

	/*Find column file open,read and close*/
	/*Open files*/
	inputStream.open("dosya.txt");

	/*Str is main variables, correct_str is correct order of numbers*/
	char str[MAX_SIZE][MAX_SIZE][DIGIT],
		correct_str[MAX_SIZE][MAX_SIZE][DIGIT],
		shuffle_str[MAX_SIZE][MAX_SIZE][DIGIT];
	char find_size[9][9][2];



	string FileName,
			line;	//For getline

	int i=0,j=0,k, 	
		row=-1,column=-1,s=1, //Requested line and column
		move_num=0,  //Moving counting number
		x,y,	//For true coordinate intelligent move
		coor_x,coor_y,
		move_direction,number, //Using I choice
		counter=1,ctc=1,
		sum=0, 	//Using I choice
		flag=0, //For exit variable
		temp_x,temp_y, //Find space place variable
		sts=0,
		random=0;	//For choice V random move

	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			for(k=0;k<2;k++){
				find_size[i][j][k]='9';
			}
		}
	}

	char choice, //Switch choice 
		temp[2]; //For intelligent move, keep number

	int compare_arr[COMP_ARR_SIZE]={10000,10000,10000,10000};	//Which of the four directions to choose

	
	/*Find column*/
	while(getline(inputStream,line))
		row++;
	/*Close text files*/
	inputStream.close();

	/*Find size(row*column) file open,read and close*/
	/*Open files*/
	outputStream.open("dosya.txt");
	/*Find size*/
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			for(k=0;k<2;k++){
				outputStream >> find_size[i][j][k];
			}
		}
	}
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			for(k=0;k<2;k++){
				if(find_size[i][j][0] != '9' && find_size[i][j][1] != '9' ){
					s++;
					k=2;
				}
				k=2;
			}
		}
	}
	/*Close text files*/
	outputStream.close();


	/*File open,read real variable str and close file*/
	/*Open files*/
	sStream.open("dosya.txt");

	column=(s/row);

	cout<<"\n";

	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			for(k=0;k<2;k++){
				sStream >> str[i][j][k];
			}
		}
	}
	/*Printing from file*/
	printing_board(str,row,column);
	
	/*Close text files*/
	sStream.close();




	/*We are trying to find the right shape of the board*/
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			for(k=0;k<2;k++){
				if(str[i][j][k] == '0' && str[i][j][k+1] == '0'){
					correct_str[i][j][k]='0';
					correct_str[i][j][k+1]='0';
					k=2;
				}
				else{
					if(ctc < 10){
						correct_str[i][j][k]='0';
						correct_str[i][j][k+1]='0'+counter;
						counter++;
						ctc++;
						k=2;
					}
					else if(ctc >= 10 && ctc < 20){
						if(ctc == 10){
							counter=1;
							correct_str[i][j][k]='1';
							correct_str[i][j][k+1]='0';
							ctc++;
						}
						else{
							correct_str[i][j][k]='1';
							correct_str[i][j][k+1]='0'+counter;
							counter++;
							ctc++;
						}
					}
					else if(ctc >= 20 && ctc < 30){
						if(ctc == 20){
							counter=1;
							correct_str[i][j][k]='2';
							correct_str[i][j][k+1]='0';
							ctc++;
						}
						else{
							correct_str[i][j][k]='2';
							correct_str[i][j][k+1]='0'+counter;
							counter++;
							ctc++;
						}
					}
					else if(ctc >= 30 && ctc < 40){
						if(ctc == 30){
							counter=1;
							correct_str[i][j][k]='3';
							correct_str[i][j][k+1]='0';
							ctc++;
						}
						else{
							correct_str[i][j][k]='3';
							correct_str[i][j][k+1]='0'+counter;
							counter++;
							ctc++;
						}
					}
					k=2;
				}
			}
		}
	}
	

	if(correct_str[row-1][column-1][0] != '0' && correct_str[row-1][column-1][1] != '0'){
		correct_str[row-1][column-1][0]='b';
		correct_str[row-1][column-1][1]='b';
			
	}
	else if(correct_str[row-1][column-2][0] != '0' && correct_str[row-1][column-2][1] != '0'){
		correct_str[row-1][column-2][0]='b';
		correct_str[row-1][column-2][1]='b';		
	}
	else if(correct_str[row-1][column-3][0] != '0' && correct_str[row-1][column-3][1] != '0'){
		correct_str[row-1][column-3][0]='b';
		correct_str[row-1][column-3][1]='b';		
	}
	
	for(k=0;k<row;k++){
		for(i=0;i<column;i++){
			for(j=0;j<2;j++)
				shuffle_str[i][j][k]=correct_str[i][j][k];
		}
	}
	cout<<"\n";
	
	while(1){
		/*User choose */
		cout<<"Choice: \n";
		cin>>choice;
		if(flag != 1){
			switch(choice){
				case 'V':
					/*Check finish or not*/
					contd_or_finish(str,correct_str,row,column,&sts);
					if(sts == 1){
						cout<<"Problem solving\n";
						cout<<"Moving number: "<<move_num<<endl;
						sts=0;
						break;
					}
					while(sts == 0){
						/*First, find space place*/
						find_space_place(str,&temp_x,&temp_y,row,column);
						sum=0;
						/*For left*/
						/*Condition not to go off board and move left*/
						if(temp_y != 0 && (str[temp_x][temp_y-1][0] != '0' || str[temp_x][temp_y-1][1] != '0')){
							swap(&str[temp_x][temp_y][0],&str[temp_x][temp_y-1][0]);
							swap(&str[temp_x][temp_y][1],&str[temp_x][temp_y-1][1]);
							/*Calculate misplaced elements distance*/
							for(i=0;i<row;i++){
								for(j=0;j<column;j++){
									for(k=0;k<2;k++){
										if((str[i][j][k] != '0' && str[i][j][k+1] != '0') && (str[i][j][k] != 'b') && 
											(str[i][j][k] != correct_str[i][j][k] || str[i][j][k+1] != correct_str[i][j][k+1])){
											coor_x=i;
											coor_y=j;
											temp[0]=str[i][j][k];
											temp[1]=str[i][j][k+1];
											finding_true_place(correct_str,&x,&y,temp,row,column);
											sum += (abs(coor_x-x) + abs(coor_y-y));
											k=2;
										}
										k=2;
									}
								}
							}
							/*The condition for deciding which direction you are going*/
							compare_arr[0]=sum;
							/*Again, find space place*/
							find_space_place(str,&temp_x,&temp_y,row,column);
							/*Value returns*/
							swap(&str[temp_x][temp_y][0],&str[temp_x][temp_y+1][0]);
							swap(&str[temp_x][temp_y][1],&str[temp_x][temp_y+1][1]);
							sum=0;

						}
						/*First, find space place*/
						find_space_place(str,&temp_x,&temp_y,row,column);
						/*For right*/
						/*Condition not to go off board and move right*/
						if(temp_y != (column-1) && (str[temp_x][temp_y+1][0] != '0' || str[temp_x][temp_y+1][1] != '0')){
							swap(&str[temp_x][temp_y][0],&str[temp_x][temp_y+1][0]);
							swap(&str[temp_x][temp_y][1],&str[temp_x][temp_y+1][1]);
							/*Calculate misplaced elements distance*/
							for(i=0;i<row;i++){
								for(j=0;j<column;j++){
									for(k=0;k<2;k++){
										if((str[i][j][k] != '0' && str[i][j][k+1] != '0') && (str[i][j][k] != 'b') && 
											(str[i][j][k] != correct_str[i][j][k] || str[i][j][k+1] != correct_str[i][j][k+1])){
											coor_x=i;
											coor_y=j;
											temp[0]=str[i][j][k];
											temp[1]=str[i][j][k+1];
											finding_true_place(correct_str,&x,&y,temp,row,column);
											sum += (abs(coor_x-x) + abs(coor_y-y));
											k=2;
										}
										k=2;
									}
								}
							}
							/*The condition for deciding which direction you are going*/
							compare_arr[1]=sum;
							/*Again, find space place*/
							find_space_place(str,&temp_x,&temp_y,row,column);
							swap(&str[temp_x][temp_y][0],&str[temp_x][temp_y-1][0]);
							swap(&str[temp_x][temp_y][1],&str[temp_x][temp_y-1][1]);
							sum=0;
						}
						/*First, find space place*/
						find_space_place(str,&temp_x,&temp_y,row,column);
						/*For up*/
						/*Condition not to go off board and move up*/
						if(temp_x != 0 && (str[temp_x-1][temp_y][0] != '0' || str[temp_x-1][temp_y][1] != '0')){
							swap(&str[temp_x][temp_y][0],&str[temp_x-1][temp_y][0]);
							swap(&str[temp_x][temp_y][1],&str[temp_x-1][temp_y][1]);
							/*Calculate misplaced elements distance*/
							for(i=0;i<row;i++){
								for(j=0;j<column;j++){
									for(k=0;k<2;k++){
										if((str[i][j][k] != '0' && str[i][j][k+1] != '0') && (str[i][j][k] != 'b') && 
											(str[i][j][k] != correct_str[i][j][k] || str[i][j][k+1] != correct_str[i][j][k+1])){
											coor_x=i;
											coor_y=j;
											temp[0]=str[i][j][k];
											temp[1]=str[i][j][k+1];
											finding_true_place(correct_str,&x,&y,temp,row,column);
											sum += (abs(coor_x-x) + abs(coor_y-y));
											k=2;
										}
										k=2;
									}
								}
							}
							/*The condition for deciding which direction you are going*/
							compare_arr[2]=sum;
							/*Again, find space place*/
							find_space_place(str,&temp_x,&temp_y,row,column);
							/*The condition for deciding which direction you are going*/
							swap(&str[temp_x][temp_y][0],&str[temp_x+1][temp_y][0]);
							swap(&str[temp_x][temp_y][1],&str[temp_x+1][temp_y][1]);
							sum=0;
						}
						/*First, find space place*/
						find_space_place(str,&temp_x,&temp_y,row,column);
						/*For down*/
						/*Condition not to go off board and move down*/
						if(temp_x != (row-1) && (str[temp_x+1][temp_y][0] != '0' || str[temp_x+1][temp_y][1] != '0')){
							swap(&str[temp_x][temp_y][0],&str[temp_x+1][temp_y][0]);
							swap(&str[temp_x][temp_y][1],&str[temp_x+1][temp_y][1]);
							/*Calculate misplaced elements distance*/
							for(i=0;i<row;i++){
								for(j=0;j<column;j++){
									for(k=0;k<2;k++){
										if((str[i][j][k] != '0' && str[i][j][k+1] != '0') && (str[i][j][k] != 'b') && 
											(str[i][j][k] != correct_str[i][j][k] || str[i][j][k+1] != correct_str[i][j][k+1])){
											coor_x=i;
											coor_y=j;
											temp[0]=str[i][j][k];
											temp[1]=str[i][j][k+1];
											finding_true_place(correct_str,&x,&y,temp,row,column);
											sum += (abs(coor_x-x) + abs(coor_y-y));
											k=2;
										}
										k=2;
									}
								}
							}
							/*The condition for deciding which direction you are going*/
							compare_arr[2]=sum;
							/*Again, find space place*/
							find_space_place(str,&temp_x,&temp_y,row,column);
							swap(&str[temp_x][temp_y][0],&str[temp_x-1][temp_y][0]);
							swap(&str[temp_x][temp_y][1],&str[temp_x-1][temp_y][1]);
							sum=0;
						}


						/*Smallest sum number according to direction*/
						number=compare_arr[0];
						move_direction=0;
						for(i=1;i<4;i++){
							if(compare_arr[i] < number){
								move_direction=i;
								number=compare_arr[i];
							}
						}

						srand(time(NULL));
						if(random == 4){
							move_direction=rand()%4;
							random=0;
						}
						//Left
						if(move_direction == 0){
							find_space_place(str,&temp_x,&temp_y,row,column);
							if(temp_y != 0 && (str[temp_x][temp_y-1][0] != '0' || str[temp_x][temp_y-1][1] != '0')){
								swap(&str[temp_x][temp_y][0],&str[temp_x][temp_y-1][0]);
								swap(&str[temp_x][temp_y][1],&str[temp_x][temp_y-1][1]);
								move_num++;
								/*A lot after the same move*/
								random++; 
							}
							cout<<"Intelligent move choose: L\n";
						}
						//Right
						else if(move_direction == 1){
							find_space_place(str,&temp_x,&temp_y,row,column);
							if(temp_y != (column-1) && (str[temp_x][temp_y+1][0] != '0' || str[temp_x][temp_y+1][1] != '0')){
								swap(&str[temp_x][temp_y][0],&str[temp_x][temp_y+1][0]);
								swap(&str[temp_x][temp_y][1],&str[temp_x][temp_y+1][1]);
								move_num++;
								/*A lot after the same move*/
								random++; 
							}
							cout<<"Intelligent move choose: R\n";
						}
						//Up
						else if(move_direction == 2){
							find_space_place(str,&temp_x,&temp_y,row,column);
							/*Condition to go out of the board and to prevent it from coming to the wall*/ 
							if(temp_x != 0 && (str[temp_x-1][temp_y][0] != '0' || str[temp_x-1][temp_y][1] != '0')){
								swap(&str[temp_x][temp_y][0],&str[temp_x-1][temp_y][0]);
								swap(&str[temp_x][temp_y][1],&str[temp_x-1][temp_y][1]);
								move_num++;
								/*A lot after the same move*/
								random++; 
							}
							cout<<"Intelligent move choose: U\n";
						}
						//Down
						else if(move_direction == 3){
							find_space_place(str,&temp_x,&temp_y,row,column);
							/*Condition to go out of the board and to prevent it from coming to the wall*/ 
							if(temp_x != (row-1) && (str[temp_x+1][temp_y][0] != '0' || str[temp_x+1][temp_y][1] != '0')){
								swap(&str[temp_x][temp_y][0],&str[temp_x+1][temp_y][0]);
								swap(&str[temp_x][temp_y][1],&str[temp_x+1][temp_y][1]);
								move_num++;
								/*A lot after the same move*/
								random++; 
							}
							cout<<"Intelligent move choose: D\n";
						}
						/*Return first situation*/
						for(i=0;i<4;i++)
							compare_arr[i]=10000;
						printing_board(str,row,column);	

						/*Check finish or not*/
						contd_or_finish(str,correct_str,row,column,&sts);

						if(sts == 1){
							cout<<"Problem solving\n";
							cout<<"Moving number: "<<move_num<<endl;
						}
					}
					break;
				case 'T':
					cout<<"Moving number: "<<move_num<<endl;
					/*Check finish or not*/
					contd_or_finish(str,correct_str,row,column,&sts);
					if(sts == 1)
						cout<<"Problem solving\n";
					else
						cout<<"Problem not solving\n";
					break;
				case 'E':
					/*Ask file name to user*/
					cout<<"Enter file name and saves current board(File name dosya.txt): \n";
					cin>>FileName;

					if(FileName == "dosya.txt"){
						/*Save board on file*/
						save_board_file(str,row,column,FileName);
						cout<<"Save: "<<FileName<<endl;
					}
					else{
						save_board_other_file(str,row,column,FileName);
						cout<<"Save: "<<FileName<<endl;
					}
					break;
				case 'Y':
					/*Ask file name to user*/
					cout<<"Enter file name and load current board(File name dosya.txt): \n";
					cin>>FileName;
					if(FileName == "dosya.txt")
						/*Load board on file*/
						load_board_file(str,row,column,FileName);
					else
						cout<<"Wrong file name\n";
					break;
				case 'L':
					/*First, find space place*/
					find_space_place(str,&temp_x,&temp_y,row,column);
					/*Condition to go out of the board and to prevent it from coming to the wall*/ 
					if(temp_y != 0 && (str[temp_x][temp_y-1][0] != '0' || str[temp_x][temp_y-1][1] != '0')){
						swap(&str[temp_x][temp_y][0],&str[temp_x][temp_y-1][0]);
						swap(&str[temp_x][temp_y][1],&str[temp_x][temp_y-1][1]);
						move_num++;
					}
					else
						cout<<"Wrong move,please enter the other move shape!!\n";
					printing_board(str,row,column);	
					break;
				case 'R':
					find_space_place(str,&temp_x,&temp_y,row,column);
					if(temp_y != (column-1) && (str[temp_x][temp_y+1][0] != '0' || str[temp_x][temp_y+1][1] != '0')){
						swap(&str[temp_x][temp_y][0],&str[temp_x][temp_y+1][0]);
						swap(&str[temp_x][temp_y][1],&str[temp_x][temp_y+1][1]);
						move_num++;
					}
					else
						cout<<"Wrong move,please enter the other move shape!!\n";
					printing_board(str,row,column);	
					break;
				case 'U':
					/*First, find space place*/
					find_space_place(str,&temp_x,&temp_y,row,column);
					/*Condition to go out of the board and to prevent it from coming to the wall*/ 
					if(temp_x != 0 && (str[temp_x-1][temp_y][0] != '0' || str[temp_x-1][temp_y][1] != '0')){
						swap(&str[temp_x][temp_y][0],&str[temp_x-1][temp_y][0]);
						swap(&str[temp_x][temp_y][1],&str[temp_x-1][temp_y][1]);
						move_num++;
					}
					else
						cout<<"Wrong move,please enter the other move shape!!\n";
					printing_board(str,row,column);	
					break;
				case 'D':
					/*First, find space place*/
					find_space_place(str,&temp_x,&temp_y,row,column);
					/*Condition to go out of the board and to prevent it from coming to the wall*/ 
					if(temp_x != (row-1) && (str[temp_x+1][temp_y][0] != '0' || str[temp_x+1][temp_y][1] != '0')){
						swap(&str[temp_x][temp_y][0],&str[temp_x+1][temp_y][0]);
						swap(&str[temp_x][temp_y][1],&str[temp_x+1][temp_y][1]);
						move_num++;
					}
					else
						cout<<"Wrong move,please enter the other move shape!!\n";
					printing_board(str,row,column);	
					break;
				case 'S':
					shuffle(str,row,column);
					/*Printing from file*/
					printing_board(str,row,column);
					break;
				case 'I':
					/*First, find space place*/
					find_space_place(str,&temp_x,&temp_y,row,column);
					sum=0;
					/*For left*/
					if(temp_y != 0 && (str[temp_x][temp_y-1][0] != '0' || str[temp_x][temp_y-1][1] != '0')){
						swap(&str[temp_x][temp_y][0],&str[temp_x][temp_y-1][0]);
						swap(&str[temp_x][temp_y][1],&str[temp_x][temp_y-1][1]);

						for(i=0;i<row;i++){
							for(j=0;j<column;j++){
								for(k=0;k<2;k++){
									if((str[i][j][k] != '0' && str[i][j][k+1] != '0') && (str[i][j][k] != 'b') && 
										(str[i][j][k] != correct_str[i][j][k] || str[i][j][k+1] != correct_str[i][j][k+1])){
										coor_x=i;
										coor_y=j;
										temp[0]=str[i][j][k];
										temp[1]=str[i][j][k+1];
										finding_true_place(correct_str,&x,&y,temp,row,column);
										sum += (abs(coor_x-x) + abs(coor_y-y));
										k=2;
									}
									k=2;
								}
							}
						}
						compare_arr[0]=sum;
						/*Again, find space place*/
						find_space_place(str,&temp_x,&temp_y,row,column);
						swap(&str[temp_x][temp_y][0],&str[temp_x][temp_y+1][0]);
						swap(&str[temp_x][temp_y][1],&str[temp_x][temp_y+1][1]);
						sum=0;

					}
					/*First, find space place*/
					find_space_place(str,&temp_x,&temp_y,row,column);
					/*For right*/
					if(temp_y != (column-1) && (str[temp_x][temp_y+1][0] != '0' || str[temp_x][temp_y+1][1] != '0')){
						swap(&str[temp_x][temp_y][0],&str[temp_x][temp_y+1][0]);
						swap(&str[temp_x][temp_y][1],&str[temp_x][temp_y+1][1]);

						for(i=0;i<row;i++){
							for(j=0;j<column;j++){
								for(k=0;k<2;k++){
									if((str[i][j][k] != '0' && str[i][j][k+1] != '0') && (str[i][j][k] != 'b') && 
										(str[i][j][k] != correct_str[i][j][k] || str[i][j][k+1] != correct_str[i][j][k+1])){
										coor_x=i;
										coor_y=j;
										temp[0]=str[i][j][k];
										temp[1]=str[i][j][k+1];
										finding_true_place(correct_str,&x,&y,temp,row,column);
										sum += (abs(coor_x-x) + abs(coor_y-y));
										k=2;
									}
									k=2;
								}
							}
						}
						compare_arr[1]=sum;
						/*Again, find space place*/
						find_space_place(str,&temp_x,&temp_y,row,column);
						swap(&str[temp_x][temp_y][0],&str[temp_x][temp_y-1][0]);
						swap(&str[temp_x][temp_y][1],&str[temp_x][temp_y-1][1]);
						sum=0;
					}
					/*First, find space place*/
					find_space_place(str,&temp_x,&temp_y,row,column);
					/*For up*/
					if(temp_x != 0 && (str[temp_x-1][temp_y][0] != '0' || str[temp_x-1][temp_y][1] != '0')){
						swap(&str[temp_x][temp_y][0],&str[temp_x-1][temp_y][0]);
						swap(&str[temp_x][temp_y][1],&str[temp_x-1][temp_y][1]);

						for(i=0;i<row;i++){
							for(j=0;j<column;j++){
								for(k=0;k<2;k++){
									if((str[i][j][k] != '0' && str[i][j][k+1] != '0') && (str[i][j][k] != 'b') && 
										(str[i][j][k] != correct_str[i][j][k] || str[i][j][k+1] != correct_str[i][j][k+1])){
										coor_x=i;
										coor_y=j;
										temp[0]=str[i][j][k];
										temp[1]=str[i][j][k+1];
										finding_true_place(correct_str,&x,&y,temp,row,column);
										sum += (abs(coor_x-x) + abs(coor_y-y));
										k=2;
									}
									k=2;
								}
							}
						}
						compare_arr[2]=sum;
						/*Again, find space place*/
						find_space_place(str,&temp_x,&temp_y,row,column);
						swap(&str[temp_x][temp_y][0],&str[temp_x+1][temp_y][0]);
						swap(&str[temp_x][temp_y][1],&str[temp_x+1][temp_y][1]);
						sum=0;
					}
					/*First, find space place*/
					find_space_place(str,&temp_x,&temp_y,row,column);
					/*For down*/
					if(temp_x != (row-1) && (str[temp_x+1][temp_y][0] != '0' || str[temp_x+1][temp_y][1] != '0')){
						swap(&str[temp_x][temp_y][0],&str[temp_x+1][temp_y][0]);
						swap(&str[temp_x][temp_y][1],&str[temp_x+1][temp_y][1]);

						for(i=0;i<row;i++){
							for(j=0;j<column;j++){
								for(k=0;k<2;k++){
									if((str[i][j][k] != '0' && str[i][j][k+1] != '0') && (str[i][j][k] != 'b') && 
										(str[i][j][k] != correct_str[i][j][k] || str[i][j][k+1] != correct_str[i][j][k+1])){
										coor_x=i;
										coor_y=j;
										temp[0]=str[i][j][k];
										temp[1]=str[i][j][k+1];
										finding_true_place(correct_str,&x,&y,temp,row,column);
										sum += (abs(coor_x-x) + abs(coor_y-y));
										k=2;
									}
									k=2;
								}
							}
						}
						compare_arr[2]=sum;
						/*Again, find space place*/
						find_space_place(str,&temp_x,&temp_y,row,column);
						swap(&str[temp_x][temp_y][0],&str[temp_x-1][temp_y][0]);
						swap(&str[temp_x][temp_y][1],&str[temp_x-1][temp_y][1]);
						sum=0;
					}

					/*Smallest sum number according to direction*/
					number=compare_arr[0];
					move_direction=0;
					for(i=1;i<4;i++){
						if(compare_arr[i] < number){
							move_direction=i;
							number=compare_arr[i];
						}
					}
					//Left
					if(move_direction == 0){
						find_space_place(str,&temp_x,&temp_y,row,column);
						if(temp_y != 0 && (str[temp_x][temp_y-1][0] != '0' || str[temp_x][temp_y-1][1] != '0')){
							swap(&str[temp_x][temp_y][0],&str[temp_x][temp_y-1][0]);
							swap(&str[temp_x][temp_y][1],&str[temp_x][temp_y-1][1]);
							move_num++;
						}
						cout<<"Intelligent move choose: L\n";
					}
					//Right
					else if(move_direction == 1){
						find_space_place(str,&temp_x,&temp_y,row,column);
						if(temp_y != (column-1) && (str[temp_x][temp_y+1][0] != '0' || str[temp_x][temp_y+1][1] != '0')){
							swap(&str[temp_x][temp_y][0],&str[temp_x][temp_y+1][0]);
							swap(&str[temp_x][temp_y][1],&str[temp_x][temp_y+1][1]);
							move_num++;
						}
						cout<<"Intelligent move choose: R\n";
					}
					//Up
					else if(move_direction == 2){
						find_space_place(str,&temp_x,&temp_y,row,column);
						/*Condition to go out of the board and to prevent it from coming to the wall*/ 
						if(temp_x != 0 && (str[temp_x-1][temp_y][0] != '0' || str[temp_x-1][temp_y][1] != '0')){
							swap(&str[temp_x][temp_y][0],&str[temp_x-1][temp_y][0]);
							swap(&str[temp_x][temp_y][1],&str[temp_x-1][temp_y][1]);
							move_num++;
						}
						cout<<"Intelligent move choose: U\n";
					}
					//Down
					else if(move_direction == 3){
						find_space_place(str,&temp_x,&temp_y,row,column);
						/*Condition to go out of the board and to prevent it from coming to the wall*/ 
						if(temp_x != (row-1) && (str[temp_x+1][temp_y][0] != '0' || str[temp_x+1][temp_y][1] != '0')){
							swap(&str[temp_x][temp_y][0],&str[temp_x+1][temp_y][0]);
							swap(&str[temp_x][temp_y][1],&str[temp_x+1][temp_y][1]);
							move_num++;
						}
						cout<<"Intelligent move choose: D\n";
					}
					/*Return first situation*/
					for(i=0;i<4;i++)
						compare_arr[i]=10000;
					printing_board(str,row,column);	
					break;
				case 'Q':
					flag=1;
					break;
			}
		}
		if(flag == 1){
			break;
		}

	}


	return 0;
		
}
void printing_board(char str[MAX_SIZE][MAX_SIZE][DIGIT],int row,int column){
	int i,j,k;

	for(k=0;k<row;k++){
		for(i=0;i<column;i++){
			for(j=0;j<2;j++){
				cout<<str[k][i][j];
			}
			cout<<" ";
		}
		cout<<"\n";
	}
}


void save_board_file(char str[MAX_SIZE][MAX_SIZE][DIGIT],int row,int column,string FileName){
	fstream SaveStream;

	SaveStream.open(FileName);
	int i,j,k;

	for(k=0;k<row;k++){
		for(i=0;i<column;i++){
			for(j=0;j<2;j++){
				SaveStream << str[k][i][j];
			}
			SaveStream << " ";
		}
		SaveStream<<"\n";
	}

	SaveStream.close();

}

void load_board_file(char str[MAX_SIZE][MAX_SIZE][DIGIT],int row,int column,string FileName){
	fstream LoadStream;

	LoadStream.open(FileName);
	int i,j,k;
	for(k=0;k<row;k++){
		for(i=0;i<column;i++){
			for(j=0;j<2;j++){
				LoadStream >> str[k][i][j];
			}
		}
	}
	LoadStream.close();

}

void find_space_place(char str[MAX_SIZE][MAX_SIZE][DIGIT],int *x,int *y,int row,int column){
	int i,j,k;

	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			for(k=0;k<2;k++){
				if(str[i][j][k] == 'b'){
					*x=i;
					*y=j;
				}
			}
		}

	}

}

void swap(char *x,char *y){
	char tmp;

	tmp=*x;
	*x=*y;
	*y=tmp;
}

void finding_true_place(char correct_str[MAX_SIZE][MAX_SIZE][DIGIT],int *x,int *y,char temp[2],int row,int column){
	int i,j,k;

	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			for(k=0;k<2;k++){
				if(correct_str[i][j][k] == temp[0] && correct_str[i][j][k+1] == temp[1]){
					*x=i;
					*y=j;
				}
				k=2;
			}
		}
	}
}

/*Puzzle finish or continuous*/
void contd_or_finish(char str[MAX_SIZE][MAX_SIZE][DIGIT],char correct_str[MAX_SIZE][MAX_SIZE][DIGIT],int row,int column,int *s){
	int i,j,k,count=0;

	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			for(k=0;k<2;k++){
				if(str[i][j][k] == correct_str[i][j][k] && str[i][j][k+1] == correct_str[i][j][k+1])
					count++;
				k=2;
			}

		}
	}
	if(count == (row*column))
		*s=1;
	else
		*s=0;
	

}

void save_board_other_file(char str[MAX_SIZE][MAX_SIZE][DIGIT],int row,int column,string FileName){
	ofstream SaveStream;

	SaveStream.open(FileName);
	int i,j,k;

	for(k=0;k<row;k++){
		for(i=0;i<column;i++){
			for(j=0;j<2;j++){
				SaveStream << str[k][i][j];
			}
			SaveStream << " ";
		}
		SaveStream<<"\n";
	}

	SaveStream.close();
}

void shuffle(char correct_str[MAX_SIZE][MAX_SIZE][DIGIT],int row,int column){
	int coordinate_x,coordinate_y;
	int res=0;
	int i,j=0,y,x,f_condition;

	if(row > column)
		f_condition=row;
	else
		f_condition=column;
	srand(time(NULL));
	for(i=0;i<(f_condition-1);i++){
		res=0;
		x=rand()%row;
		y=rand()%column;
		if(correct_str[i][j][0] == '0' && correct_str[i][j][1] == '0')
			res=0;
		else if(correct_str[i][j][0] == 'b' && correct_str[i][j][1] == 'b')
			res=0;
		else if(correct_str[x][y][0] == '0' && correct_str[x][y][1] == '0')
			res=0;
		else if(correct_str[x][y][0] == 'b' && correct_str[x][y][1] == 'b')
			res=0;
		else
			res=1;
		if(res == 1){
			swap(&correct_str[i][j][0],&correct_str[x][y][0]);
			swap(&correct_str[i][j][1],&correct_str[x][y][1]);
			j++;
		}
	}


}
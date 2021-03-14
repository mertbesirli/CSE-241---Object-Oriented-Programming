#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstring>



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

#define MAX_SIZE 9
#define COMPARE_ARR_SIZE 4
#define DIGIT 2
#define TRUE 1
#define FALSE 0
using namespace std;

class NPuzzle{
private:
	class Board{
	public:
		void set_arr(char arr[MAX_SIZE][MAX_SIZE][DIGIT]);
		char get_arr();
		void sets(int r,int c,int m);
		int get_row();
		int get_column();
		int get_move_number();
		int find_row();
		int find_column();
		void print();
		void readFromFile(string FileName);
		void writeToFile();
		void move(char x);
		void intelligent_movement();
		bool isSolved();
		void reportMove();
		void setsize();
		void reset();
		void shuffle_moves(int n);
	private:
		int row,column;	//Board row and column
		int move_num=0;	//User moving number
		char str[MAX_SIZE][MAX_SIZE][DIGIT];
	};
public:
	Board box;
	void print();
	int find_row();
	int find_column();
	void readFromFile(string FileName);
	void writeToFile();
	void move(char x);
	void moveIntelligent();
	void solvePuzzle();
	void printReport();
	void moveRandom(char x);
	void setsize();
	void reset();
	void shuffle(int n);
};

using namespace std;

void find_space_place(char str[MAX_SIZE][MAX_SIZE][DIGIT],int *x,int *y,int row,int column);
void swap(char *x,char *y);
void find_final_arr(char correct_str[MAX_SIZE][MAX_SIZE][DIGIT],int row,int column,char str[MAX_SIZE][MAX_SIZE][DIGIT]);
void finding_true_place(char correct_str[MAX_SIZE][MAX_SIZE][DIGIT],int *x,int *y,char temp[2],int row,int column);
void contd_or_finish(char str[MAX_SIZE][MAX_SIZE][DIGIT],char correct_str[MAX_SIZE][MAX_SIZE][DIGIT],int row,int column,int *sts);

int main(int argc, char const *argv[])
{
	NPuzzle puzzle;

	/*Shuffle moves random N number */
	int n;
	srand(time(NULL));
	n=5+rand()%40;

	string FileName;

	if(argc != 1){	
		puzzle.find_row();
		puzzle.find_column();
		puzzle.readFromFile(argv[1]);
		cout<<"Open file: "<<argv[1]<<endl;	
	}
	else{
		puzzle.setsize();
		puzzle.reset();
		puzzle.shuffle(n);
		cout<<"\n\n\n";
	}

	/*Printing board*/
	puzzle.print();


	char choice,x;
	int flag=0;

	while(1){
		/*User choose */
		cout<<"Choice: \n";
		cin>>choice;
		if(flag != 1){
			switch(choice){
				case 'V':
					puzzle.solvePuzzle();
					puzzle.printReport();
					break;
				case 'T':
					puzzle.printReport();
					break;
				case 'E':
					puzzle.writeToFile();
					puzzle.print();
					break;
				case 'O':
					cout<<"Please enter load file: ";
					cin>>FileName;
					puzzle.readFromFile(argv[1]);
					cout<<"Open file: "<<argv[1]<<endl;
					puzzle.print();
					break;
				case 'L':
					x='L';
					puzzle.move(x);
					puzzle.print();
					break;
				case 'R':
					x='R';
					puzzle.move(x);
					puzzle.print();
					break;
				case 'U':
					x='U';
					puzzle.move(x);
					puzzle.print();
					break;
				case 'D':
					x='D';
					puzzle.move(x);
					puzzle.print();
					break;
				case 'S':
					x='S';
					puzzle.shuffle(n);
					puzzle.print();
					break;
				case 'I':
					puzzle.moveIntelligent();
					puzzle.print();
					break;
				case 'Q':
					flag=1;
					break;

			}


		}
		/*For exit*/
		if(flag == 1)
			break;
	}
	
	return 0;
}

void NPuzzle::Board::set_arr(char arr[MAX_SIZE][MAX_SIZE][DIGIT]){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			for(int k=0;k<2;k++)
				str[i][j][k]=arr[i][j][k];
		}
	}

}
char NPuzzle::Board::get_arr(){
	return (str[9][9][2]);

}

void NPuzzle::Board::sets(int r,int c,int m){
	row=r;
	column=c;
	move_num=m;

}

int NPuzzle::Board::get_row(){
	return row;
}

int NPuzzle::Board::get_column(){
	return column;
}
int NPuzzle::Board::get_move_number(){
	return move_num;
}

/*Find row*/
int NPuzzle::find_row(){
	box.find_row();

}
int NPuzzle::Board::find_row(){
	string line;
	ifstream Stream;
	int count=0;
	Stream.open("dosya.txt");
	/*Find column*/
	while(getline(Stream,line))
		count++;
	/*Close text files*/
	Stream.close();
	row=count;

	return row;

}
/*Find column*/
int NPuzzle::find_column(){
	box.find_column();
}

int NPuzzle::Board::find_column(){

	ifstream Stream;
	int count=1,i,j,k;
	char find_size[MAX_SIZE][MAX_SIZE][DIGIT];
	/*Inıtialized array*/
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			for(k=0;k<2;k++){
				find_size[i][j][k]='c';
			}
		}
	}

	/*Find size(row*column) file open,read and close*/
	/*Open files*/
	Stream.open("dosya.txt");
	/*Find size*/
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			for(k=0;k<2;k++){
				Stream >> find_size[i][j][k];
			}
		}
	}
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			for(k=0;k<2;k++){
				if(find_size[i][j][0] != 'c' && find_size[i][j][1] != 'c' ){
					count++;
					k=2;
				}
				k=2;
			}
		}
	}
	/*Close text files*/
	Stream.close();
	/*Find column*/
	column=(count/row);

	return column;

}

void NPuzzle::print(){
	box.print();
}
void NPuzzle::Board::print(){
	int i,j,k;
	/*According to row and column board printing*/
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
void NPuzzle::readFromFile(string FileName){
	box.readFromFile(FileName);
}
void NPuzzle::Board::readFromFile(string FileName){
	ifstream inputStream;
	int i,j,k;
	/*Read from file text*/
	inputStream.open(FileName);
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			for(k=0;k<2;k++){
				inputStream >> str[i][j][k];
			}
		}
	}
	inputStream.close();
}
void NPuzzle::writeToFile(){
	box.writeToFile();
}
void NPuzzle::Board::writeToFile(){
	string FileName;
	fstream Stream;
	ofstream WriteStream;
	int i,j,k;

	/*Ask file name to user*/
	cout<<"Enter file name and save current board: \n";
	cin>>FileName;
	if(FileName == "dosya.txt"){
		Stream.open(FileName);
		for(i=0;i<row;i++){
			for(j=0;j<column;j++){
				for(k=0;k<2;k++)
					Stream << str[i][j][k];
				Stream<<" ";
			}
			Stream<<"\n";
		}
		Stream.close();
		cout<<"Save: "<<FileName<<endl;
	}
	else{
		WriteStream.open(FileName);
		for(i=0;i<row;i++){
			for(j=0;j<column;j++){
				for(k=0;k<2;k++)
					WriteStream << str[i][j][k];
				WriteStream<<" ";
			}
			WriteStream<<"\n";
		}

	}
}

void NPuzzle::move(char x){
	box.move(x);
}

void NPuzzle::Board::move(char x){
	int temp_x,temp_y,
		number;
	/*Left moving*/
	if(x == 'L'){
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
	}
	/*Right moving*/
	else if(x == 'R'){
		/*First, find space place*/
		find_space_place(str,&temp_x,&temp_y,row,column);

		if(temp_y != (column-1) && (str[temp_x][temp_y+1][0] != '0' || str[temp_x][temp_y+1][1] != '0')){
			swap(&str[temp_x][temp_y][0],&str[temp_x][temp_y+1][0]);
			swap(&str[temp_x][temp_y][1],&str[temp_x][temp_y+1][1]);
			move_num++;
		}
		else
			cout<<"Wrong move,please enter the other move shape!!\n\n";
	}
	/*Up moving*/
	else if(x == 'U'){
		/*First, find space place*/
		find_space_place(str,&temp_x,&temp_y,row,column);
		/*Condition to go out of the board and to prevent it from coming to the wall*/ 
		if(temp_x != 0 && (str[temp_x-1][temp_y][0] != '0' || str[temp_x-1][temp_y][1] != '0')){
			swap(&str[temp_x][temp_y][0],&str[temp_x-1][temp_y][0]);
			swap(&str[temp_x][temp_y][1],&str[temp_x-1][temp_y][1]);
			move_num++;
		}
		else
			cout<<"Wrong move,please enter the other move shape!!\n\n";
	}
	/*Down moving*/
	else if(x == 'D'){
		/*First, find space place*/
		find_space_place(str,&temp_x,&temp_y,row,column);
		/*Condition to go out of the board and to prevent it from coming to the wall*/ 
		if(temp_x != (row-1) && (str[temp_x+1][temp_y][0] != '0' || str[temp_x+1][temp_y][1] != '0')){
			swap(&str[temp_x][temp_y][0],&str[temp_x+1][temp_y][0]);
			swap(&str[temp_x][temp_y][1],&str[temp_x+1][temp_y][1]);
			move_num++;
		}
		else
			cout<<"Wrong move,please enter the other move shape!!\n\n";
	}
	/*Moving random after shuffle*/
	else if(x == 'S'){
		srand(time(NULL));
		number=rand()%4;
		if(number == 0){
			x='L';
			move(x);
		}
		else if(number == 1){
			x='R';
			move(x);
		}
		else if(number == 2){
			x='U';
			move(x);
		}
		else if(number == 3){
			x='D';
			move(x);
		}
	}


}

/*Fing space('b') character*/
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

/*Swapping function*/
void swap(char *x,char *y){
	char temp;
	temp=*x;
	*x=*y;
	*y=temp;

}


void NPuzzle::moveIntelligent(){
	box.intelligent_movement();
}
void NPuzzle::Board::intelligent_movement(){
	int temp_x,temp_y,
		coor_x,coor_y,
		x,y,
		i,j,k,
		number,move_direction;
	int sum=0;
	char correct_str[MAX_SIZE][MAX_SIZE][DIGIT];	//For final array
	char temp[2]; //For intelligent move, keep number
	int compare_arr[COMPARE_ARR_SIZE]={10000,10000,10000,10000};
/*	NPuzzle n;
	int row=n.find_row();
	int column=n.find_column();*/


	/*We are trying to find the right shape of the board*/
	/*It's necessary for comparison */
	find_final_arr(correct_str,row,column,str);
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
		

}

/*For find final array solution for comparison*/
void find_final_arr(char correct_str[MAX_SIZE][MAX_SIZE][DIGIT],int row,int column,char str[MAX_SIZE][MAX_SIZE][DIGIT]){
	int i,j,k,ctc=1,counter=1;

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

}

/*Finding true place coordinate*/
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

void NPuzzle::solvePuzzle(){
	if(box.isSolved() == 1)
		cout<<"Problem solved\n";
	else
		cout<<"Not solved\n";


}

bool NPuzzle::Board::isSolved(){
	char correct_str[MAX_SIZE][MAX_SIZE][DIGIT];
	int sts=0,sum=0;
	int temp_x,temp_y,
		coor_x,coor_y,
		x,y,
		i,j,k,
		number,move_direction,
		random=0;
	char temp[2]; //For intelligent move, keep number
	int compare_arr[COMPARE_ARR_SIZE]={10000,10000,10000,10000};
	Board r;

	/*We are trying to find the right shape of the board*/
	/*It's necessary for comparison */
	find_final_arr(correct_str,row,column,str);
	/*Check finish or not*/
	contd_or_finish(str,correct_str,row,column,&sts);

	if(sts == 1)
		return TRUE;
	else{
		while(sts == 0){
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
			/*Moving random*/
			srand(time(NULL));
			if(random == 3){
				move('S'); 
				random=0;
			}
			//Left
			if(move_direction == 0){
				find_space_place(str,&temp_x,&temp_y,row,column);
				if(temp_y != 0 && (str[temp_x][temp_y-1][0] != '0' || str[temp_x][temp_y-1][1] != '0')){
					swap(&str[temp_x][temp_y][0],&str[temp_x][temp_y-1][0]);
					swap(&str[temp_x][temp_y][1],&str[temp_x][temp_y-1][1]);
					move_num++;
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
					random++;
				}
				cout<<"Intelligent move choose: D\n";
			}
			/*Return first situation*/
			for(i=0;i<4;i++)
				compare_arr[i]=10000;
			print();
			if(move_num == 1000000){
				cout<<"Problem not solving, sorry\n";
				sts=1;
				break;
			}

		}
		return FALSE;
	}




}

/*Puzzle finish or continuous*/
void contd_or_finish(char str[MAX_SIZE][MAX_SIZE][DIGIT],char correct_str[MAX_SIZE][MAX_SIZE][DIGIT],int row,int column,int *sts){
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
		*sts=1;
	else
		*sts=0;

}

void NPuzzle::printReport(){
	box.reportMove();

}

void NPuzzle::Board::reportMove(){
	char correct_str[MAX_SIZE][MAX_SIZE][DIGIT];
	int sts=0;
	/*Printing moving number*/
	cout<<"Moving number: "<<move_num<<endl;
	

	/*First find correct array for comparison my array*/
	find_final_arr(correct_str,row,column,str);
	/*My array solved or not, find it*/
	contd_or_finish(str,correct_str,row,column,&sts);
	/*Condition solve or not*/
	if(sts == 1)
		cout<<"Problem solved\n";
	else
		cout<<"Problem not solved\n";

}

void NPuzzle::moveRandom(char x){
	box.move(x);
}
void NPuzzle::setsize(){
	box.setsize();
}
void NPuzzle::Board::setsize(){
	/*Taken user row and column*/
	cout<<"Please row: \n";
	cin>>row;
	cout<<"Please column: \n";
	cin>>column;
}
void NPuzzle::reset(){
	box.reset();
}
void NPuzzle::Board::reset(){
	int ctc=1,counter=1,
		i,j,k;

	str[0][0][0]='0';	
	str[0][0][1]='0';
	str[0][1][0]='0';
	str[0][1][1]='0';
	str[1][0][0]='0';
	str[1][0][1]='0';
	str[1][0][0]='0';
	str[1][0][1]='0';
	str[1][1][0]='0';
	str[1][1][1]='0';
	str[0][column-1][0]='0';
	str[0][column-1][1]='0';
	str[row-2][0][0]='0';
	str[row-2][0][1]='0';

	/*We are trying to find the right shape of the board*/
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			for(k=0;k<2;k++){
				if(str[i][j][k] == '0' && str[i][j][k+1] == '0'){
					str[i][j][k]='0';
					str[i][j][k+1]='0';
					k=2;
				}
				else{
					if(ctc < 10){
						str[i][j][k]='0';
						str[i][j][k+1]='0'+counter;
						counter++;
						ctc++;
						k=2;
					}
					else if(ctc >= 10 && ctc < 20){
						if(ctc == 10){
							counter=1;
							str[i][j][k]='1';
							str[i][j][k+1]='0';
							ctc++;
						}
						else{
							str[i][j][k]='1';
							str[i][j][k+1]='0'+counter;
							counter++;
							ctc++;
						}
					}
					else if(ctc >= 20 && ctc < 30){
						if(ctc == 20){
							counter=1;
							str[i][j][k]='2';
							str[i][j][k+1]='0';
							ctc++;
						}
						else{
							str[i][j][k]='2';
							str[i][j][k+1]='0'+counter;
							counter++;
							ctc++;
						}
					}
					else if(ctc >= 30 && ctc < 40){
						if(ctc == 30){
							counter=1;
							str[i][j][k]='3';
							str[i][j][k+1]='0';
							ctc++;
						}
						else{
							str[i][j][k]='3';
							str[i][j][k+1]='0'+counter;
							counter++;
							ctc++;
						}
					}
					k=2;
				}
			}
		}
	}
	str[row-1][column-1][0]='b';
	str[row-1][column-1][1]='b';
}

void NPuzzle::shuffle(int n){
	box.shuffle_moves(n);
}
void NPuzzle::Board::shuffle_moves(int n){
	char x='S';
	int temp_x,temp_y;

	for(int i=0;i<n;i++)
		move(x);

	find_space_place(str,&temp_x,&temp_y,row,column);
	
	swap(&str[temp_x][temp_y][0],&str[row-1][0][0]);
	swap(&str[temp_x][temp_y][1],&str[row-1][0][1]);
}
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstring>
#include <vector>


#define TRUE 1
#define FALSE 0
#define MAX_SIZE 9
#define DIGIT 2


using namespace std;

class NPuzzle{
private:
	class Board{
	public:
		void sets(int r,int c,int m,int b);
		void set_c(char c);
		int get_row();
		int get_column();
		int get_move_number();
		int get_num_board();
		char get_last_move();
		int find_row();
		int find_column();
		void readFromFile(string file_name);
		void print();
		void setsize();
		void reset();
		void shuffle_moves(int n);
		void writeToFile();
		void move(char x);
		void reportMove();
		int isSolved();
		int numberOfBoards();
		char lastMove();
		int numberOfMoves();

	private:
		vector<vector<vector<char>>>str;
		int row,column,move_num=0,num_board=0;
		char last_move='S';
	};
public:
	Board box;
	int find_row();
	int find_column();
	void readFromFile(string file_name);
	void print();
	void setsize();
	void reset();
	void shuffle(int n);
	void writeToFile();
	void move(char x);
	void moveRandom(char x);
	void printReport();	
	void solvePuzzle();

};

void random_shuffle_number(int *x);
void find_space_place(vector<vector<vector<char>>>str,int *x,int *y);
void swap(char *x,char *y);
void find_final_arr(char correct_str[9][9][2],int row,int column,vector<vector<vector<char>>>str);
void contd_or_finish(vector<vector<vector<char>>>str,char correct_str[9][9][2],int row,int column,int *sts);
int comparison_vec(vector<vector<vector<char>>>str,vector<vector<vector<char>>>arr);

int main(int argc, char const *argv[])
{
	char choice,x;
	int flag=0,n;
	string FileName;
	/*Shuffle moving randomize number*/
	random_shuffle_number(&n);
	
	NPuzzle puzzle;


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
		
	}
	/*Printing board*/
	puzzle.print();

	while(1){
		/*User choose */
		cout<<"Choice: \n";
		cin>>choice;
		if(flag != 1){
			switch(choice){
				case 'V':
					puzzle.solvePuzzle();
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
					puzzle.readFromFile(FileName);
					cout<<"Open file: "<<FileName<<endl;
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
					puzzle.shuffle(n);
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

void NPuzzle::print(){

	box.print();
}

void NPuzzle::Board::print(){

	int i,j,k;

	for(k=0;k<str.size();k++){
		for(i=0;i<str[0].size();i++){
			for(j=0;j<str[0][0].size();j++){
				cout<<str[k][i][j];
			}
			cout<<" ";
		}
		cout<<"\n";
	}
}

void NPuzzle::readFromFile(string file_name){
	box.readFromFile(file_name);
}
void NPuzzle::Board::readFromFile(string file_name){
	ifstream inputStream;
	int i,j,k;
	
	char s[MAX_SIZE][MAX_SIZE][DIGIT];


	/*Read from file text*/
	inputStream.open(file_name);

	for(i=0;i<row;i++){
		str.push_back(vector<vector<char>>());
		for(j=0;j<column;j++){
			str[i].push_back(vector<char>());
			for(k=0;k<2;k++){
				inputStream >> s[i][j][k];
				str[i][j].push_back(s[i][j][k]);
			}
		}
	}

	inputStream.close();
	


}

void NPuzzle::Board::sets(int r,int c,int m,int b){
	row=r;
	column=c;
	move_num=m;
	num_board=b;
}
void NPuzzle::Board::set_c(char c){
	last_move=c;
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
int NPuzzle::Board::get_num_board(){
	return num_board;
}
char NPuzzle::Board::get_last_move(){
	return last_move;
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
	str.resize(0);


	int i,j,k,counter=1;
	int ctc=1;


	for(i=0;i<row;i++){
		str.push_back(vector<vector<char>>());
		for(j=0;j<column;j++){
			str[i].push_back(std::vector<char>());
			for(k=0;k<2;k++)
				str[i][j].push_back('0');
		}
	}

	/*We are trying to find the right shape of the board*/
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			for(k=0;k<2;k++){
				if(i == 0 && j == 0 && k == 0){
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

void random_shuffle_number(int *x){
	srand(time(NULL));

	*x=50+rand()%100;
}


void NPuzzle::shuffle(int n){
	box.shuffle_moves(n);
}
void NPuzzle::Board::shuffle_moves(int n){
	char x='S';
	int temp_x,temp_y;

	for(int i=0;i<n;i++)
		move(x);
	/*Find space ('b')*/
	find_space_place(str,&temp_x,&temp_y);
	/*Swapping board elements*/
	swap(&str[temp_x][temp_y][0],&str[row-1][0][0]);
	swap(&str[temp_x][temp_y][1],&str[row-1][0][1]);
}

void find_space_place(vector<vector<vector<char>>>str,int *x,int *y){
	int i,j,k;
	/*Finding space coordinate*/
	for(i=0;i<str.size();i++){
		for(j=0;j<str[0].size();j++){
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

void NPuzzle::move(char x){
	box.move(x);
}

void NPuzzle::Board::move(char x){
	int temp_x,temp_y,
		number;
	/*Left moving*/
	if(x == 'L'){
		/*First, find space place*/
		find_space_place(str,&temp_x,&temp_y);
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
		find_space_place(str,&temp_x,&temp_y);

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
		find_space_place(str,&temp_x,&temp_y);
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
		find_space_place(str,&temp_x,&temp_y);
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

void NPuzzle::printReport(){
	box.reportMove();
}

void NPuzzle::Board::reportMove(){
	char correct_str[MAX_SIZE][MAX_SIZE][DIGIT];
	int sts=0;

	/*Printing moving number,board number,last move*/
	cout<<"Move number: "<<numberOfMoves()<<endl;
	cout<<"Number of Boards: "<<numberOfBoards()<<endl;
	cout<<"Last move: "<<lastMove()<<endl;
	

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

/*For find final array solution for comparison*/
void find_final_arr(char correct_str[MAX_SIZE][MAX_SIZE][DIGIT],int row,int column,vector<vector<vector<char>>>str){
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
	

	if((correct_str[row-1][column-1][0] != '0' && correct_str[row-1][column-1][1] != '0')|| 
		(correct_str[row-1][column-1][0] == '0' && correct_str[row-1][column-1][1] != '0')){

		correct_str[row-1][column-1][0]='b';
		correct_str[row-1][column-1][1]='b';
			
	}
	else if((correct_str[row-1][column-2][0] != '0' && correct_str[row-1][column-2][1] != '0') || 
		(correct_str[row-1][column-2][0] == '0' && correct_str[row-1][column-2][1] != '0')){
		correct_str[row-1][column-2][0]='b';
		correct_str[row-1][column-2][1]='b';		
	}
	else if((correct_str[row-1][column-3][0] != '0' && correct_str[row-1][column-3][1] != '0') ||
		(correct_str[row-1][column-3][0] == '0' && correct_str[row-1][column-3][1] != '0')){
		correct_str[row-1][column-3][0]='b';
		correct_str[row-1][column-3][1]='b';		
	}

}
/*Puzzle finish or continuous*/
void contd_or_finish(vector<vector<vector<char>>>str,char correct_str[MAX_SIZE][MAX_SIZE][DIGIT],int row,int column,int *sts){
	int i,j,k,count=0;

	/*Find solution or not*/
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

void NPuzzle::solvePuzzle(){
	if(box.isSolved() == 1)
		cout<<"Problem solved\n";
	else
		cout<<"Not solved\n";

}

int NPuzzle::Board::isSolved(){

	int i,j,k,res,
		temp_x,temp_y,
		random_num,
		flag=0;
	int r=0,l=0,u=0,d=0;

	char correct_str[MAX_SIZE][MAX_SIZE][DIGIT];
	vector<vector<vector<char>>>arr;

	find_final_arr(correct_str,row,column,str);
	/*Final array pushing arr vector */
	for(i=0;i<row;i++){
		arr.push_back(vector<vector<char>>());
		for(j=0;j<column;j++){
			arr[i].push_back(vector<char>());
			for(k=0;k<2;k++)
				arr[i][j].push_back(correct_str[i][j][k]);
		}
	}
	/*Find solution*/
	res=comparison_vec(str,arr);
	/*Found solution return TRUE*/
	if(res == 1)
		return TRUE;


	while(flag == 0){
		/*First, find space place*/
		find_space_place(str,&temp_x,&temp_y);
		/*For left*/
		/*Condition to go out of the board and to prevent it from coming to the wall*/ 
		if(temp_y != 0 && (str[temp_x][temp_y-1][0] != '0' || str[temp_x][temp_y-1][1] != '0')){
			swap(&str[temp_x][temp_y][0],&str[temp_x][temp_y-1][0]);
			swap(&str[temp_x][temp_y][1],&str[temp_x][temp_y-1][1]);
			move_num++;
			num_board++;
			res=comparison_vec(str,arr);
			r=1;
		}
		if(res == 1)
			break;

		/*Again, find space place*/
		find_space_place(str,&temp_x,&temp_y);
		swap(&str[temp_x][temp_y][0],&str[temp_x][temp_y+1][0]);
		swap(&str[temp_x][temp_y][1],&str[temp_x][temp_y+1][1]);


		/*First, find space place*/
		find_space_place(str,&temp_x,&temp_y);
		/*For left*/
		/*Condition to go out of the board and to prevent it from coming to the wall*/ 
		if(temp_y != (column-1) && (str[temp_x][temp_y+1][0] != '0' || str[temp_x][temp_y+1][1] != '0')){
			swap(&str[temp_x][temp_y][0],&str[temp_x][temp_y+1][0]);
			swap(&str[temp_x][temp_y][1],&str[temp_x][temp_y+1][1]);
			move_num++;
			num_board++;
			res=comparison_vec(str,arr);
			l=1;
		}
		if(res == 1)
			break;

		/*Again, find space place*/
		find_space_place(str,&temp_x,&temp_y);
		swap(&str[temp_x][temp_y][0],&str[temp_x][temp_y-1][0]);
		swap(&str[temp_x][temp_y][1],&str[temp_x][temp_y-1][1]);

		/*First, find space place*/
		find_space_place(str,&temp_x,&temp_y);
		/*For up*/
		/*Condition to go out of the board and to prevent it from coming to the wall*/ 
		if(temp_x != 0 && (str[temp_x-1][temp_y][0] != '0' || str[temp_x-1][temp_y][1] != '0')){
			swap(&str[temp_x][temp_y][0],&str[temp_x-1][temp_y][0]);
			swap(&str[temp_x][temp_y][1],&str[temp_x-1][temp_y][1]);
			move_num++;
			num_board++;
			res=comparison_vec(str,arr);
			u=1;
		}
		if(res == 1)
			break;
		
		/*Again, find space place*/
		find_space_place(str,&temp_x,&temp_y);
		swap(&str[temp_x][temp_y][0],&str[temp_x+1][temp_y][0]);
		swap(&str[temp_x][temp_y][1],&str[temp_x+1][temp_y][1]);

		/*First, find space place*/
		find_space_place(str,&temp_x,&temp_y);
		/*For down*/
		/*Condition to go out of the board and to prevent it from coming to the wall*/
		if(temp_x != (row-1) && (str[temp_x+1][temp_y][0] != '0' || str[temp_x+1][temp_y][1] != '0')){
			swap(&str[temp_x][temp_y][0],&str[temp_x+1][temp_y][0]);
			swap(&str[temp_x][temp_y][1],&str[temp_x+1][temp_y][1]);
			move_num++;
			num_board++;
			res=comparison_vec(str,arr);
			d=1;
		}
		if(res == 1)	
			break;
		
		/*Again, find space place*/
		find_space_place(str,&temp_x,&temp_y);
		swap(&str[temp_x][temp_y][0],&str[temp_x-1][temp_y][0]);
		swap(&str[temp_x][temp_y][1],&str[temp_x-1][temp_y][1]);

		srand(time(NULL));
		random_num=rand()%4;

		if(random_num == 0 && r == 1){
			move('R');
			last_move='R';
		}
		else if(random_num == 1 && l == 1){
			move('L');
			last_move='L';
		}

		else if(random_num == 2 && u == 1){
			move('U');
			last_move='U';
		}
		else if(random_num == 3 && d == 1){
			move('D');
			last_move='D';
		}
		print();
		cout<<endl;
		if(move_num == 1000000){
			cout<<"Problem not solving, sorry\n";
			flag=1;
			break;
		}
	}
	if(res == 1)
		return TRUE;
	else
		return FALSE;


}

int comparison_vec(vector<vector<vector<char>>>str,vector<vector<vector<char>>>arr){
	int i,j,k,count=0;

	for(i=0;i<str.size();i++){
		for(j=0;j<str[0].size();j++){
			for(k=0;k<2;k++){
				if(str[i][j][k] == arr[i][j][k] && str[i][j][k+1] == arr[i][j][k+1])
					count++;
				k=2;
			}

		}
	}
	if(count == (str.size()*str[0].size()))
		return 1;
	else
		return 0;

}

int NPuzzle::Board::numberOfMoves(){
	return move_num;
}
int NPuzzle::Board::numberOfBoards(){
	return num_board;
}
char NPuzzle::Board::lastMove(){
	return last_move;
}
void NPuzzle::moveRandom(char x){
	box.move(x);
}
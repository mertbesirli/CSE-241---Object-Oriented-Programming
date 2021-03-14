#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>

using std::string;
using std::ifstream;
using std::vector;
using std::fstream;
using std::cin;
using std::ofstream;

namespace Board{
	//Base Class
	class AbstractBoard{
	public:
		AbstractBoard();
		AbstractBoard(int newRow,int newColumn);
		void setRow(int theRow);
		void setColumn(int theColumn);
		void setMoveNum(int theMoveNumber);
		void setNumBoard(int theNumberBoard);
		void setLastMove(char theLastMove);
		int getRow()const;
		int getColumn()const;
		int getMoveNum()const;
		int getNumBoard()const;
		char getLastMove()const;
		int find_row(string filename);
		int find_column(string filename);
		virtual void print();
		virtual void readFromFile(string filename);
		virtual void writeToFile(string file_name);
		virtual void reset();
		virtual void setSize();
		virtual void move(char x);
		virtual void shuffle(int num);
		virtual int isSolved();
		virtual int printReport();;
		virtual bool operator == (AbstractBoard &base);
		
	protected:
		int row,column,
			move_num=0,num_board=0;
		char last_move='S';
	};

	//Class BoardVector
	class BoardVector:public AbstractBoard{
	public:
		BoardVector(); //Default constructor
		BoardVector(int newRow,int newColumn,vector<char>newBox);
		void print();
		void readFromFile(string filename);
		void writeToFile(string file_name);
		void reset();
		void setSize();
		void move(char x);
		void shuffle(int num);
		int printReport();
		int isSolved();
		bool operator == (BoardVector &base);
	private:
		vector<char>box;

	};

	//Class BoardArray1D
	class BoardArray1D:public AbstractBoard{
	public:
		BoardArray1D();	//Default constructor
		BoardArray1D(int newRow,int newColumn);
		void print();
		void readFromFile(string filename);
		void writeToFile(string file_name);
		void reset();
		void setSize();
		void move(char x);
		void shuffle(int num);
		int printReport();
		int isSolved();
		bool operator == (BoardArray1D &base);
		~BoardArray1D();
	private:
		char *str;
	};
	//Class BoardArray2D
	class BoardArray2D:public AbstractBoard{
	public:
		BoardArray2D();	//Default constructor
		BoardArray2D(int newRow,int newColumn);
		void print();
		void readFromFile(string filename);
		void writeToFile(string file_name);
		void reset();
		void setSize();
		void move(char x);
		void shuffle(int num);	
		int isSolved();
		int printReport();
		bool operator == (BoardArray2D &base);
		~BoardArray2D();

	private:
		char **arr;
	};


	void find_space_place(vector<char>box,int *x);
	void swap(char *x,char *y);
	void find_space_place_1D(char *str,int *x,int t_row,int t_col);
	void find_space_place_2D(char **arr,int *x,int *y,int r_row,int r_col);
	void final_solution(char *str,char vcs[10000],int n_row,int n_col);
	int comparison_vec(vector<char>box,char vcs[10000]);
	int comparison_1d_arr(char *str,char vcs[10000],int r,int c);
	int comparison_2d_arr(char **arr,char comp[9][9],int r,int c);
	void final_sol_2D(char **arr,char comp[9][9],int therow,int thecol);
	void final_solution_vec(vector<char>box,char vcs[10000],int n_row,int n_col);
	int foo(const vector<AbstractBoard*>&v);

}

using std::cout;
using std::endl;
using Board::AbstractBoard;
using Board::BoardVector;
using Board::BoardArray1D;
using Board::BoardArray2D;





int main(int argc, char const *argv[])
{
	AbstractBoard b;
	int f_row,f_column,
		flag=0, //For while choose option
		res;
	char ans,choice,x;
	string FileName;

	BoardVector vec;
	BoardArray1D arr1d;


	if(argc != 1){
		f_row=b.find_row(argv[1]);
		f_column=b.find_column(argv[1]);
	}
	else{
		f_row=9;
		f_column=9;
	}
	BoardArray2D arr2d(f_row,f_column);
	
	/*For global Function*/
	vector<AbstractBoard*>mv;

	cout<<"Choose Vector(Press V),1DArray(Press D),2DArray(Press R): ";
	cin>>ans;
	if(ans == 'V'){
		if(argc != 1){
			/*Row and column update*/
			vec.setRow(f_row);
			vec.setColumn(f_column);
			/*Read from file text*/
			vec.readFromFile(argv[1]);
			cout<<"Open file: "<<argv[1]<<endl;
		}
		else{
			/*taken row and column for user*/
			vec.setSize();
			vec.reset();
			/*Shuffle 50 times*/
			vec.shuffle(50);
		}
		/*Printing Boardvector variable*/
		vec.print();
		while(1){
			/*User choose */
			cout<<"Choice: \n";
			cin>>choice;
			if(flag != 1){
				switch(choice){
					case 'V':
						res=vec.isSolved();
						if(res == 1)
							mv.push_back(&vec);
						vec.print();
						break;
					case 'T':
						vec.printReport();
						if(res == 1)
							mv.push_back(&vec);
						break;
					case 'E':
						vec.writeToFile(argv[1]);
						vec.print();
						break;
					case '0':
						cout<<"Please enter load file: ";
						cin>>FileName;
						vec.readFromFile(FileName);
						cout<<"Open file: "<<FileName<<endl;
						vec.print();
						break;
					case 'L':
						x='L';
						vec.move(x);
						vec.print();
						break;
					case 'R':
						x='R';
						vec.move(x);
						vec.print();
						break;
					case 'U':
						x='U';
						vec.move(x);
						vec.print();
						break;
					case 'D':
						x='D';
						vec.move(x);
						vec.print();
						break;
					case 'S':
						vec.shuffle(50);
						vec.print();
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
	}

	else if(ans == 'D'){
		if(argc != 1){
			/*Row and column update*/
			arr1d.setRow(f_row);
			arr1d.setColumn(f_column);
			//Read from file text
			arr1d.readFromFile(argv[1]);
			cout<<"Open file: "<<argv[1]<<endl;
		}
		else{
			//Taken row and column from user*/
			arr1d.setSize();
			arr1d.reset();
			arr1d.shuffle(50);
		}
		/*Printing BoardArray1D variable str*/
		arr1d.print();
		while(1){
			/*User choose */
			cout<<"Choice: \n";
			cin>>choice;
			if(flag != 1){
				switch(choice){
					case 'V':
						res=arr1d.isSolved();
						if(res == 1)
							mv.push_back(&arr1d);
						arr1d.print();
						break;
					case 'T':
						arr1d.printReport();
						if(res == 1)
							mv.push_back(&arr1d);
						break;
					case 'E':
						arr1d.writeToFile(argv[1]);
						arr1d.print();
						break;
					case '0':
						cout<<"Please enter load file: ";
						cin>>FileName;
						arr1d.readFromFile(FileName);
						cout<<"Open file: "<<FileName<<endl;
						arr1d.print();
						break;
					case 'L':
						x='L';
						arr1d.move(x);
						arr1d.print();
						break;
					case 'R':
						x='R';
						arr1d.move(x);
						arr1d.print();
						break;
					case 'U':
						x='U';
						arr1d.move(x);
						arr1d.print();
						break;
					case 'D':
						x='D';
						arr1d.move(x);
						arr1d.print();
						break;
					case 'S':
						arr1d.shuffle(50);
						arr1d.print();
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
	}
	else if(ans == 'R'){
		if(argc != 1){
			/*Row and column update*/
			arr2d.setRow(f_row);
			arr2d.setColumn(f_column);
			//Read from file text
			arr2d.readFromFile(argv[1]);
			cout<<"Open file: "<<argv[1]<<endl;
		}
		else{
			/*Taken row and column from user*/
			arr2d.setSize();
			arr2d.reset();
			arr2d.shuffle(50);
		}
		arr2d.print();
		while(1){
			/*User choose */
			cout<<"Choice: \n";
			cin>>choice;
			if(flag != 1){
				switch(choice){
					case 'V':
						res=arr2d.isSolved();
						if(res == 1)
							mv.push_back(&arr2d);
						arr2d.print();
						break;
					case 'T':
						arr2d.printReport();
						if(res == 1)
							mv.push_back(&arr2d);
						break;
					case 'E':
						arr2d.writeToFile(argv[1]);
						arr2d.print();
						break;
					case '0':
						cout<<"Please enter load file: ";
						cin>>FileName;
						arr2d.readFromFile(FileName);
						cout<<"Open file: "<<FileName<<endl;
						arr2d.print();
						break;
					case 'L':
						x='L';
						arr2d.move(x);
						arr2d.print();
						break;
					case 'R':
						x='R';
						arr2d.move(x);
						arr2d.print();
						break;
					case 'U':
						x='U';
						arr2d.move(x);
						arr2d.print();
						break;
					case 'D':
						x='D';
						arr2d.move(x);
						arr2d.print();
						break;
					case 'S':
						arr2d.shuffle(50);
						arr2d.print();
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
	}

	
	return 0;
}

namespace Board{
	AbstractBoard::AbstractBoard():row(0),column(0){
		//Empty
	}
	AbstractBoard::AbstractBoard(int newRow,int newColumn):row(newRow),column(newColumn){
		//Empty
	}
	void AbstractBoard::setRow(int theRow){
		row=theRow;
	}
	void AbstractBoard::setColumn(int theColumn){
		column=theColumn;
	}
	void AbstractBoard::setMoveNum(int theMoveNumber){
		move_num=theMoveNumber;
	}
	void AbstractBoard::setNumBoard(int theNumberBoard){
		num_board=theNumberBoard;
	}
	void AbstractBoard::setLastMove(char theLastMove){
		last_move=theLastMove;
	}
	int AbstractBoard::getRow()const{
		return row;
	}
	int AbstractBoard::getColumn()const{
		return column;
	}
	int AbstractBoard::getMoveNum()const{
		return move_num;
	}
	int AbstractBoard::getNumBoard()const{
		return num_board;
	}
	char AbstractBoard::getLastMove()const{
		return last_move;
	}
	int AbstractBoard::find_row(string filename){
		string line;
		ifstream Stream;
		int count=0;
		/*Open file*/
		Stream.open(filename);
		/*Find row*/
		while(getline(Stream,line))
			count++;
		/*Close text files*/
		Stream.close();
		row=count;
		return row;
	}
	int AbstractBoard::find_column(string filename){
		ifstream Stream;
		int count=1,i,j,k;
		char find_size[9][9][2];
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

	void AbstractBoard::print(){
		//empty
	}
	void AbstractBoard::readFromFile(string filename){
		//Empty
	}
	void AbstractBoard::writeToFile(string file_name){
		//empty
	}
	void AbstractBoard::reset(){
		//empty
	}
	void AbstractBoard::move(char x){
		//empty
	}
	void AbstractBoard::shuffle(int num){
		//empty
	}
	int AbstractBoard::isSolved(){
		//empty
	}
	int AbstractBoard::printReport(){
		//empty
	}

	void AbstractBoard::setSize(){
		int r,c;
		/*Taken user row and column*/
		cout<<"Please row: \n";
		cin>>r;
		setRow(r);
		cout<<"Please column: \n";
		cin>>c;
		setColumn(c);
	}

	bool AbstractBoard::operator == (AbstractBoard &base){
		//empty
	}


	///////////////////

	BoardVector::BoardVector():AbstractBoard(){
		//Empty
	}
	BoardVector::BoardVector(int newRow,int newColumn,vector<char>newBox):AbstractBoard(newRow,newColumn){
		box=newBox;
	} 
	void BoardVector::print(){
		int count=0,	//For between characters space
			c_counter=0;	//For finish line then new line

		for(int i=0;i<box.size();i++){
			if(count != 2){
				cout<<box[i];
				count++;
				c_counter++;
				//Between characters space
				if(count == 2){		
					cout<<" ";
					count=0;
				}
				//Finish line then new line
				if(c_counter == (getColumn()*2)){
					cout<<endl;
					c_counter=0;
				}
			}
		}
	}
	void BoardVector::readFromFile(string filename){
		char s[10000];
		int i,j;

		ifstream inputStream;
		/*Read from file text*/
		inputStream.open(filename);
		/*Read from file to variable*/
		for(i=0;i<(getRow()*getColumn()*2);i++){
			inputStream>>s[i];
			box.push_back(s[i]);
		}
		inputStream.close();
	}
	void BoardVector::writeToFile(string file_name){
		string FileName;
		fstream Stream;
		ofstream WriteStream;

		int count=0,	//For between characters space
			c_counter=0;	//For finish line then new line


		/*Ask file name to user*/
		cout<<"Enter file name and save current board: \n";
		cin>>FileName;
		/*If it is same file I'm using*/
		if(FileName == file_name){
			Stream.open(FileName);
			for(int i=0;i<box.size();i++){
				if(count != 2){
					Stream<<box[i];
					count++;
					c_counter++;
					//Between characters space
					if(count == 2){		
						Stream<<" ";
						count=0;
					}
					//Finish line then new line
					if(c_counter == (getColumn()*2)){
						Stream<<"\n";
						c_counter=0;
					}
				}
			}
		}
		/*If it is the other file*/
		else{
			WriteStream.open(FileName);
			for(int i=0;i<box.size();i++){
				if(count != 2){
					WriteStream<<box[i];
					count++;
					c_counter++;
					//Between characters space
					if(count == 2){		
						WriteStream<<" ";
						count=0;
					}
					//Finish line then new line
					if(c_counter == (getColumn()*2)){
						WriteStream<<"\n";
						c_counter=0;
					}
				}
			}
		}
	}
	void BoardVector::reset(){
		box.resize(0);

		int counter=1,count=1,i;
		/*First, all numbers is '0'*/
		for(i=0;i<(getRow()*getColumn()*2);i++)
			box.push_back('0');
		for(i=0;i<(getRow()*getColumn()*2);i++){
			if(i == 0){
				box[i]='0';
				box[i+1]='0';
				i += 1;
			}
			else{
				if(count < 10){
					box[i]='0';
					box[i+1]='0'+counter;
					counter++;
					count++;
				}
				else if(count >= 10 && count < 20){
					if(count == 10){
						counter=1;
						box[i]='1';
						box[i+1]='0';
						count++;
					}
					else{
						box[i]='1';
						box[i+1]='0'+counter;
						counter++;
						count++;
					}
				}
				else if(count >= 20 && count < 30){
					if(count == 20){
						counter=1;
						box[i]='2';
						box[i+1]='0';
						count++;
					}
					else{
						box[i]='2';
						box[i+1]='0'+counter;
						counter++;
						count++;	
					}
				}
				else if(count >= 30 && count <40){
					if(count == 30){
						counter=1;
						box[i]='3';
						box[i+1]='0';
						count++;
					}
					else{
						box[i]='3';
						box[i+1]='0'+counter;
						counter++;
						count++;	
					}

				}
				i += 1;
			}
		}

		box[(getRow()*getColumn()*2)-1]='b';
		box[(getRow()*getColumn()*2)-2]='b';
	}
	void BoardVector::setSize(){
		int r,c;
		/*Taken user row and column*/
		cout<<"Please row: \n";
		cin>>r;
		setRow(r);
		cout<<"Please column: \n";
		cin>>c;
		setColumn(c);
	}
	void BoardVector::move(char x){
		int temp_x,number;
		int count=0;

		//Left move
		if(x == 'L'){
			/*Find space coordinate*/
			find_space_place(box,&temp_x);
			/*If condition not go outside and not go wall('00')*/
			if(temp_x != 0 && temp_x != (getColumn()*2) && temp_x != (getColumn()*4) && temp_x != (getColumn()*6) && temp_x != (getColumn()*8) && temp_x != (getColumn()*10) 
				&& temp_x != (getColumn()*12)&& temp_x != (getColumn()*14) && temp_x != (getColumn()*16) && (box[temp_x-1] != '0' || box[temp_x-2] != '0') ){
				swap(&box[temp_x],&box[temp_x-2]);
				swap(&box[temp_x+1],&box[temp_x-1]);
				move_num++;
			}
			else
				cout<<"Wrong move,please enter the other move shape!!\n";
		}
		//Right move
		else if(x == 'R'){
			/*Find space coordinate*/
			find_space_place(box,&temp_x);
			if(temp_x != (getRow()*getColumn()*2-2) && (box[temp_x+2] != '0' || box[temp_x+3] != '0')){
				swap(&box[temp_x],&box[temp_x+2]);
				swap(&box[temp_x+1],&box[temp_x+3]);
				move_num++;
			} 
			else
				cout<<"Wrong move,please enter the other move shape!!\n";

		}
		//Up move
		else if(x == 'U'){
			/*Find space coordinate*/
			find_space_place(box,&temp_x);
			/*If condition not go outside and not go wall('00')*/
			if(temp_x > (getColumn()+2) && (box[temp_x-(getColumn()*2)] != '0' || box[(temp_x-(getColumn()*2))+1] != '0')){
				swap(&box[temp_x],&box[temp_x-(getColumn()*2)]);
				swap(&box[temp_x+1],&box[(temp_x-(getColumn()*2))+1]);
				move_num++;
			}
			else
				cout<<"Wrong move,please enter the other move shape!!\n";
		}
		//Down move
		else if(x == 'D'){
			/*Find space coordinate*/
			find_space_place(box,&temp_x);
			/*If condition not go outside and not go wall('00')*/
			if(temp_x < ((getRow()*getColumn()*2)-(getColumn()*2+1)) && (box[temp_x+(getColumn()*2)] != '0' || box[(temp_x+(getColumn()*2))+1] != '0')){
				swap(&box[temp_x],&box[temp_x+(getColumn()*2)]);
				swap(&box[temp_x+1],&box[(temp_x+(getColumn()*2))+1]);
				move_num++;
			}
			else
				cout<<"Wrong move,please enter the other move shape!!\n";
		}
		//Shuffle move
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
	void BoardVector::shuffle(int num){
		char x='S';
		int temp_x,res;

		for(int i=0;i<num;i++)
			move(x);
		/*Find space coordinate*/
		find_space_place(box,&temp_x);
		/*Swapping cell*/
		swap(&box[temp_x],&box[(getRow()*getColumn()*2)-(getColumn()*2)]);
		swap(&box[temp_x+1],&box[(getRow()*getColumn()*2)-(getColumn()*2)+1]);

	}
	int BoardVector::isSolved(){
		int temp_x,res,
			random_num;
		/*For comparison array*/
		char vcs[10000];
		/*find final solution*/
		final_solution_vec(box,vcs,getRow(),getColumn());
		/*Find space coordinate*/
		find_space_place(box,&temp_x);
		/*For left*/
		/*If condition not go outside and not go wall('00')*/
		if(temp_x != 0 && temp_x != (getColumn()*2) && temp_x != (getColumn()*4) && temp_x != (getColumn()*6) && temp_x != (getColumn()*8) && temp_x != (getColumn()*10) 
			&& temp_x != (getColumn()*12)&& temp_x != (getColumn()*14) && temp_x != (getColumn()*16) && (box[temp_x-1] != '0' || box[temp_x-2] != '0') ){
			swap(&box[temp_x],&box[temp_x-2]);
			swap(&box[temp_x+1],&box[temp_x-1]);
			move_num++;
			num_board++;
			last_move='L';
			/*Checking final solution or not*/
			res=comparison_vec(box,vcs);
		}
		if(res == 1)
			return 1;
		/*Again find space coordinate*/
		find_space_place(box,&temp_x);
		swap(&box[temp_x],&box[temp_x+2]);
		swap(&box[temp_x+1],&box[temp_x+3]);
		/*Find space place coordinate*/
		find_space_place(box,&temp_x);
		/*For right*/
		if(temp_x != (getRow()*getColumn()*2-2) && (box[temp_x+2] != '0' || box[temp_x+3] != '0')){
				swap(&box[temp_x],&box[temp_x+2]);
				swap(&box[temp_x+1],&box[temp_x+3]);
				move_num++;
				num_board++;
				last_move='R';
				/*Checking final solution or not*/
				res=comparison_vec(box,vcs);
		}
		if(res == 1)
			return 1;
		/*Again find space coordinate*/
		find_space_place(box,&temp_x);
		swap(&box[temp_x],&box[temp_x-2]);
		swap(&box[temp_x+1],&box[temp_x-1]);

		find_space_place(box,&temp_x);
		/*For up*/
		/*If condition not go outside and not go wall('00')*/
		if(temp_x > (getColumn()+2) && (box[temp_x-(getColumn()*2)] != '0' || box[(temp_x-(getColumn()*2))+1] != '0')){
			swap(&box[temp_x],&box[temp_x-(getColumn()*2)]);
			swap(&box[temp_x+1],&box[(temp_x-(getColumn()*2))+1]);
			move_num++;
			num_board++;
			last_move='U';
			/*Checking final solution or not*/
			res=comparison_vec(box,vcs);
		}
		if(res == 1)
			return 1;
		/*Again find space coordinate*/
		find_space_place(box,&temp_x);
		swap(&box[temp_x],&box[temp_x+(getColumn()*2)]);
		swap(&box[temp_x+1],&box[(temp_x+(getColumn()*2))+1]);

		find_space_place(box,&temp_x);
		/*For down*/
		/*If condition not go outside and not go wall('00')*/
		if(temp_x < ((getRow()*getColumn()*2)-(getColumn()*2+1)) && (box[temp_x+(getColumn()*2)] != '0' || box[(temp_x+(getColumn()*2))+1] != '0')){
			swap(&box[temp_x],&box[temp_x+(getColumn()*2)]);
			swap(&box[temp_x+1],&box[(temp_x+(getColumn()*2))+1]);
			move_num++;
			num_board++;
			last_move='D';
			/*Checking final solution or not*/
			res=comparison_vec(box,vcs);
		}
		if(res == 1)
			return 1;
		/*Again find space coordinate*/
		find_space_place(box,&temp_x);
		swap(&box[temp_x],&box[temp_x-(getColumn()*2)]);
		swap(&box[temp_x+1],&box[(temp_x-(getColumn()*2))+1]);



		srand(time(NULL));
		random_num=rand()%4;

		if(random_num == 0){
			move('R');
			last_move='R';
		}
		else if(random_num == 1){
			move('L');
			last_move='L';
		}
		else if(random_num == 2){
			move('U');
			last_move='U';
		}
		else if(random_num == 3){
			move('D');
			last_move='D';
		}

		
		return 0;

	}
	int BoardVector::printReport(){
		int return_value;
		char vcs[10000];

		final_solution_vec(box,vcs,getRow(),getColumn());

		cout<<"Move number: "<<move_num<<endl;
		cout<<"Number of boards: "<<num_board<<endl;
		cout<<"Last move: "<<last_move<<endl;
		return_value=comparison_vec(box,vcs);
		return return_value;
	}

	//////////
	BoardArray1D::BoardArray1D():AbstractBoard(){
		str=new char[getRow()*getColumn()*2];
	}
	BoardArray1D::BoardArray1D(int newRow,int newColumn):AbstractBoard(newRow,newColumn){
		str=new char[getRow()*getColumn()*2];	
	}
	void BoardArray1D::print(){
		int count=0,	//For between characters space
			c_counter=0;	//For finish line then new line

		for(int i=0;i<(getRow()*getColumn()*2);i++){
			if(count != 2){
				cout<<str[i];
				count++;
				c_counter++;
				//Between characters space
				if(count == 2){		
					cout<<" ";
					count=0;
				}
				//Finish line then new line
				if(c_counter == (getColumn()*2)){
					cout<<endl;
					c_counter=0;
				}
			}
		}
	}

	void BoardArray1D::readFromFile(string filename){
		int i;
		ifstream inputStream;
		/*Read from file text*/
		inputStream.open(filename);
		//Read board from file
		for(i=0;i<(getRow()*getColumn()*2);i++)
			inputStream >> str[i];
		//Close file
		inputStream.close();
	}
	void BoardArray1D::writeToFile(string file_name){
		string FileName;
		fstream Stream;
		ofstream WriteStream;

		int count=0,	//For between characters space
			c_counter=0;	//For finish line then new line


		/*Ask file name to user*/
		cout<<"Enter file name and save current board: \n";
		cin>>FileName;
		/*If it is same file I'm using*/
		if(FileName == file_name){
			Stream.open(FileName);
			for(int i=0;i<(getRow()*getColumn()*2);i++){
				if(count != 2){
					Stream<<str[i];
					count++;
					c_counter++;
					//Between characters space
					if(count == 2){		
						Stream<<" ";
						count=0;
					}
					//Finish line then new line
					if(c_counter == (getColumn()*2)){
						Stream<<"\n";
						c_counter=0;
					}
				}
			}
		}
		/*If it is the other file*/
		else{
			WriteStream.open(FileName);
			for(int i=0;i<(getRow()*getColumn()*2);i++){
				if(count != 2){
					WriteStream<<str[i];
					count++;
					c_counter++;
					//Between characters space
					if(count == 2){		
						WriteStream<<" ";
						count=0;
					}
					//Finish line then new line
					if(c_counter == (getColumn()*2)){
						WriteStream<<"\n";
						c_counter=0;
					}
				}
			}
		}
		Stream.close();
		WriteStream.close();
	}
	void BoardArray1D::reset(){
		int counter=1,count=1,i;

		for(i=0;i<(getRow()*getColumn()*2);i++){
			if(i == 0){
				str[i]='0';
				str[i+1]='0';
				i += 1;
			}
			else{
				if(count < 10){
					str[i]='0';
					str[i+1]='0'+counter;
					counter++;
					count++;
				}
				else if(count >= 10 && count < 20){
					if(count == 10){
						counter=1;
						str[i]='1';
						str[i+1]='0';
						count++;
					}
					else{
						str[i]='1';
						str[i+1]='0'+counter;
						counter++;
						count++;
					}
				}
				else if(count >= 20 && count < 30){
					if(count == 20){
						counter=1;
						str[i]='2';
						str[i+1]='0';
						count++;
					}
					else{
						str[i]='2';
						str[i+1]='0'+counter;
						counter++;
						count++;	
					}
				}
				else if(count >= 30 && count <40){
					if(count == 30){
						counter=1;
						str[i]='3';
						str[i+1]='0';
						count++;
					}
					else{
						str[i]='3';
						str[i+1]='0'+counter;
						counter++;
						count++;	
					}

				}
				i += 1;
			}
		}

		str[(getRow()*getColumn()*2)-1]='b';
		str[(getRow()*getColumn()*2)-2]='b';
	}
	void BoardArray1D::setSize(){
		int r,c;
		/*Taken user row and column*/
		cout<<"Please row: \n";
		cin>>r;
		setRow(r);
		cout<<"Please column: \n";
		cin>>c;
		setColumn(c);
	}

	void BoardArray1D::move(char x){
		int temp_x;
		int t_row,t_col,
			number;

		t_row=getRow();
		t_col=getColumn();

		

		//Left move
		if(x == 'L'){
			/*Find space coordinate*/
			find_space_place_1D(str,&temp_x,t_row,t_col);
			/*If condition not go outside and not go wall('00')*/
			if(temp_x != 0 && temp_x != (getColumn()*2) && temp_x != (getColumn()*4) && temp_x != (getColumn()*6) && temp_x != (getColumn()*8) && temp_x != (getColumn()*10) 
				&& temp_x != (getColumn()*12)&& temp_x != (getColumn()*14) && temp_x != (getColumn()*16) && (str[temp_x-1] != '0' || str[temp_x-2] != '0') ){
				swap(&str[temp_x],&str[temp_x-2]);
				swap(&str[temp_x+1],&str[temp_x-1]);
				move_num++;
			}
			else
				cout<<"Wrong move,please enter the other move shape!!\n";
		}
		//Right move
		else if(x == 'R'){
			/*Find space coordinate*/
			find_space_place_1D(str,&temp_x,t_row,t_col);
			/*If condition not go outside and not go wall('00')*/
			if(temp_x != (getRow()*getColumn()*2-2) && (str[temp_x+2] != '0' || str[temp_x+3] != '0')){
					swap(&str[temp_x],&str[temp_x+2]);
					swap(&str[temp_x+1],&str[temp_x+3]);
					move_num++;
			}
			else
				cout<<"Wrong move,please enter the other move shape!!\n";
		}
		//Up move
		else if(x == 'U'){
			/*Find space coordinate*/
			find_space_place_1D(str,&temp_x,t_row,t_col);
			/*If condition not go outside and not go wall('00')*/
			if(temp_x > (getColumn()+2) && (str[temp_x-(getColumn()*2)] != '0' || str[(temp_x-(getColumn()*2))+1] != '0')){
				swap(&str[temp_x],&str[temp_x-(getColumn()*2)]);
				swap(&str[temp_x+1],&str[(temp_x-(getColumn()*2))+1]);
				move_num++;
			}
			else
				cout<<"Wrong move,please enter the other move shape!!\n";
		}
		//Down move
		else if(x == 'D'){
			/*Find space coordinate*/
			find_space_place_1D(str,&temp_x,t_row,t_col);
			/*If condition not go outside and not go wall('00')*/
			if(temp_x < ((getRow()*getColumn()*2)-(getColumn()*2+1)) && (str[temp_x+(getColumn()*2)] != '0' || str[(temp_x+(getColumn()*2))+1] != '0')){
				swap(&str[temp_x],&str[temp_x+(getColumn()*2)]);
				swap(&str[temp_x+1],&str[(temp_x+(getColumn()*2))+1]);
				move_num++;
			}
			else
				cout<<"Wrong move,please enter the other move shape!!\n";
		}
		//Shuffle move
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
	void BoardArray1D::shuffle(int num){
		char x='S';
		int temp_x;


		for(int i=0;i<num;i++)
			move(x);
		/*Find space coordinate*/
		find_space_place_1D(str,&temp_x,getRow(),getColumn());
		swap(&str[temp_x],&str[(getRow()*getColumn()*2)-(getColumn()*2)]);
		swap(&str[temp_x+1],&str[(getRow()*getColumn()*2)-(getColumn()*2)+1]);

	}
	bool BoardArray1D::operator==(BoardArray1D &base){
		if(strcmp(str,base.str) == 0)
			return 1;
		else
			return 0;
	}
	int BoardArray1D::isSolved(){
		int temp_x,res,
			random_num;
		char vcs[10000];
		

	/*	BoardArray1D b1,b2;*/
		int t_row,t_col;
		t_row=getRow();
		t_col=getColumn();
		//For final solution
		final_solution(str,vcs,t_row,t_col);

	/*	if(b1 == b2)
			cout<<"Equal"<<endl;
		else
			cout<<"Not equal"<<endl;
	/*

		/*Find space coordinate*/
		find_space_place_1D(str,&temp_x,t_row,t_col);
		/*For left*/
		/*If condition not go outside and not go wall('00')*/
		if(temp_x != 0 && temp_x != (getColumn()*2) && temp_x != (getColumn()*4) && temp_x != (getColumn()*6) && temp_x != (getColumn()*8) && temp_x != (getColumn()*10) 
			&& temp_x != (getColumn()*12)&& temp_x != (getColumn()*14) && temp_x != (getColumn()*16) && (str[temp_x-1] != '0' || str[temp_x-2] != '0') ){
			swap(&str[temp_x],&str[temp_x-2]);
			swap(&str[temp_x+1],&str[temp_x-1]);
			move_num++;
			num_board++;
			last_move='L';
			/*Checking final solution or not*/
			res=comparison_1d_arr(str,vcs,t_row,t_col);
		}
		if(res == 1)
			return 1;
		/*Find space coordinate*/
		find_space_place_1D(str,&temp_x,t_row,t_col);
		swap(&str[temp_x],&str[temp_x+2]);
		swap(&str[temp_x+1],&str[temp_x+3]);

		find_space_place_1D(str,&temp_x,t_row,t_col);
		/*For right*/
		/*If condition not go outside and not go wall('00')*/
		if((temp_x != ((getColumn()*2)-2)) && (temp_x != ((getColumn()*1*2)-2)) && (temp_x != ((getColumn()*2*2)-2)) && (temp_x != ((getColumn()*3*2)-2)) && 
			(temp_x != ((getColumn()*4*2)-2)) && (str[temp_x+2] != '0') || str[temp_x+3] != '0'){
			if((temp_x != ((getColumn()*5*2)-2)) && (temp_x != ((getColumn()*6*2)-2)) && (temp_x != ((getColumn()*7*2)-2)) && (temp_x != ((getColumn()*8*2)-2)) 
				&& (temp_x != ((getColumn()*9*2)-2))){
				swap(&str[temp_x],&str[temp_x+2]);
				swap(&str[temp_x+1],&str[temp_x+3]);
				move_num++;
				num_board++;
				last_move='R';
				/*Checking final solution or not*/
				res=comparison_1d_arr(str,vcs,t_row,t_col);
			}
		}
		if(res == 1)
			return 1;
		/*Find space coordinate*/
		find_space_place_1D(str,&temp_x,row,column);
		swap(&str[temp_x],&str[temp_x-2]);
		swap(&str[temp_x+1],&str[temp_x-1]);

		find_space_place_1D(str,&temp_x,t_row,t_col);
		//For up
		/*If condition not go outside and not go wall('00')*/
		if(temp_x > (getColumn()+2) && (str[temp_x-(getColumn()*2)] != '0' || str[(temp_x-(getColumn()*2))+1] != '0')){
			swap(&str[temp_x],&str[temp_x-(getColumn()*2)]);
			swap(&str[temp_x+1],&str[(temp_x-(getColumn()*2))+1]);
			move_num++;
			num_board++;
			last_move='U';
			/*Checking final solution or not*/
			res=comparison_1d_arr(str,vcs,t_row,t_col);
		}
		if(res == 1)
			return 1;
		find_space_place_1D(str,&temp_x,t_row,t_col);
		swap(&str[temp_x],&str[temp_x+(getColumn()*2)]);
		swap(&str[temp_x+1],&str[(temp_x+(getColumn()*2))+1]);

		find_space_place_1D(str,&temp_x,t_row,t_col);
		//For down
		/*If condition not go outside and not go wall('00')*/
		if(temp_x < ((getRow()*getColumn()*2)-(getColumn()*2+1)) && (str[temp_x+(getColumn()*2)] != '0' || str[(temp_x+(getColumn()*2))+1] != '0')){
			swap(&str[temp_x],&str[temp_x+(getColumn()*2)]);
			swap(&str[temp_x+1],&str[(temp_x+(getColumn()*2))+1]);
			move_num++;
			num_board++;
			last_move='D';
			/*Checking final solution or not*/
			res=comparison_1d_arr(str,vcs,t_row,t_col);
		}
		if(res == 1)
			return 1;
		find_space_place_1D(str,&temp_x,t_row,t_col);
		swap(&str[temp_x],&str[temp_x-(getColumn()*2)]);
		swap(&str[temp_x+1],&str[(temp_x-(getColumn()*2))+1]);

		srand(time(NULL));
		random_num=rand()%4;

		if(random_num == 0){
			move('R');
			last_move='R';
		}
		else if(random_num == 1){
			move('L');
			last_move='L';
		}
		else if(random_num == 2){
			move('U');
			last_move='U';
		}
		else if(random_num == 3){
			move('D');
			last_move='D';
		}


	}
	int BoardArray1D::printReport(){
		int return_value;
		char vcs[10000];
		
		final_solution(str,vcs,getRow(),getColumn());
		cout<<"Move number: "<<move_num<<endl;
		cout<<"Number of boards: "<<num_board<<endl;
		cout<<"Last move: "<<last_move<<endl;
		/*Final solution or not*/
		return_value=comparison_1d_arr(str,vcs,getRow(),getColumn());

		return return_value;

	}
	//Destructor
	BoardArray1D::~BoardArray1D(){
		delete [] str;
	}


	//////////////
	BoardArray2D::BoardArray2D():AbstractBoard(){
		arr=new char *[getRow()];
		for(int i=0;i<getRow();i++)
			arr[i]=new char[getColumn()*2];
	}
	BoardArray2D::BoardArray2D(int newRow,int newColumn):AbstractBoard(newRow,newColumn){
		arr=new char *[getRow()];
		for(int i=0;i<getRow();i++)
			arr[i]=new char[getColumn()*2];
	}
	void BoardArray2D::print(){
		int count=0;
		for(int i=0;i<getRow();i++){
			for(int j=0;j<(getColumn()*2);j++){
				cout<<arr[i][j];
				count++;
				if(count == 2){
					cout<<" ";
					count=0;
				}
			}
			cout<<endl;
		}
		cout<<endl;

	}
	void BoardArray2D::readFromFile(string filename){
		ifstream inputStream;
		/*Read from file text*/
		inputStream.open(filename);
		//Read board from file
		for(int i=0;i<getRow();i++){
			for(int j=0;j<(getColumn()*2);j++)
				inputStream >> arr[i][j];
		}
		
		//Close file
		inputStream.close();

	}
	void BoardArray2D::writeToFile(string file_name){
		string FileName;
		fstream Stream;
		ofstream WriteStream;

		int count=0;

		/*Ask file name to user*/
		cout<<"Enter file name and save current board: \n";
		cin>>FileName;
		/*If it is same file I'm using*/
		if(FileName == file_name){
			Stream.open(FileName);
			for(int i=0;i<getRow();i++){
				for(int j=0;j<(getColumn()*2);j++){
					Stream << arr[i][j];
					count++;
					if(count == 2){
						Stream << " ";
						count=0;
					}
				}
				Stream << "\n";
			}
		}
		
		else{
			WriteStream.open(FileName);
			for(int i=0;i<getRow();i++){
				for(int j=0;j<(getColumn()*2);j++){
					WriteStream << arr[i][j];
					count++;
					if(count == 2){
						WriteStream << " ";
						count=0;
					}
				}
				WriteStream << "\n";
			}

		}
		Stream.close();
		WriteStream.close();
	}
	void BoardArray2D::reset(){
		int i,j,
			counter=1,count=1;

		for(i=0;i<getRow();i++){
			for(j=0;j<(getColumn()*2);j++){
				if(i == 0 && j == 0){
					arr[i][j]='0';
					arr[i][j+1]='0';
					j += 1;
				}
				else{
					if(count < 10){
						arr[i][j]='0';
						arr[i][j+1]='0'+counter;
						counter++;
						count++;
					}
					else if(count >= 10 && count < 20){
						if(count == 10){
							counter=1;
							arr[i][j]='1';
							arr[i][j+1]='0';
							count++;
						}
						else{
							arr[i][j]='1';
							arr[i][j+1]='0'+counter;
							counter++;
							count++;
						}
					}
					else if(count >= 20 && count < 30){
						if(count == 20){
							counter=1;
							arr[i][j]='2';
							arr[i][j+1]='0';
							count++;
						}
						else{
							arr[i][j]='2';
							arr[i][j+1]='0'+counter;
							counter++;
							count++;
						}
					}
					else if(count >= 30 && count < 40){
						if(count == 30){
							counter=1;
							arr[i][j]='3';
							arr[i][j+1]='0';
							count++;
						}
						else{
							arr[i][j]='3';
							arr[i][j+1]='0'+counter;
							counter++;
							count++;
						}
					}
					j += 1;
				}

			}
		}
		arr[getRow()-1][(getColumn()*2)-1]='b';
		arr[getRow()-1][(getColumn()*2)-2]='b';
	}
	void BoardArray2D::setSize(){
		int r,c;
		/*Taken user row and column*/
		cout<<"Please row: \n";
		cin>>r;
		row=r;
		cout<<"Please column: \n";
		cin>>c;
		column=c;
	}
	void BoardArray2D::move(char x){
		int temp_x,temp_y,
			r_row,r_col,
			number;

		r_row=getRow();
		r_col=getColumn();

		//Left moving
		if(x == 'L'){
			find_space_place_2D(arr,&temp_x,&temp_y,r_row,r_col);
			if(temp_y != 0 && (arr[temp_x][temp_y-1] != '0' || arr[temp_x][temp_y-2] != '0')){
				swap(&arr[temp_x][temp_y],&arr[temp_x][temp_y-2]);
				swap(&arr[temp_x][temp_y+1],&arr[temp_x][temp_y-1]);
				move_num++;
			}
			else
				cout<<"Wrong move,please enter the other move shape!!\n";
		}
		else if(x == 'R'){
			find_space_place_2D(arr,&temp_x,&temp_y,r_row,r_col);
			if(temp_y != ((getColumn()*2)-2) && (arr[temp_x][temp_y+2] != '0' || arr[temp_x][temp_y+3] != '0')){
				swap(&arr[temp_x][temp_y],&arr[temp_x][temp_y+2]);
				swap(&arr[temp_x][temp_y+1],&arr[temp_x][temp_y+3]);
				move_num++;
			}
			else
				cout<<"Wrong move,please enter the other move shape!!\n";
		}
		else if(x == 'U'){
			find_space_place_2D(arr,&temp_x,&temp_y,r_row,r_col);
			if(temp_x != 0 && (arr[temp_x-1][temp_y] != '0' || arr[temp_x-1][temp_y+1] != '0')){
				swap(&arr[temp_x][temp_y],&arr[temp_x-1][temp_y]);
				swap(&arr[temp_x][temp_y+1],&arr[temp_x-1][temp_y+1]);
				move_num++;
			}
			else
				cout<<"Wrong move,please enter the other move shape!!\n";
		}
		else if(x == 'D'){
			find_space_place_2D(arr,&temp_x,&temp_y,r_row,r_col);
			if(temp_x != (getRow()-1) && (arr[temp_x+1][temp_y] != '0' || arr[temp_x+1][temp_y+1] != '0')){
				swap(&arr[temp_x][temp_y],&arr[temp_x+1][temp_y]);
				swap(&arr[temp_x][temp_y+1],&arr[temp_x+1][temp_y+1]);
				move_num++;
			}
		}
		//Shuffle move
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
	void BoardArray2D::shuffle(int num){
		char x='S';
		int temp_x,temp_y;
		for(int i=0;i<num;i++)
			move(x);
		find_space_place_2D(arr,&temp_x,&temp_y,getRow(),getColumn());
		swap(&arr[temp_x][temp_y],&arr[getRow()-1][0]);
		swap(&arr[temp_x][temp_y+1],&arr[getRow()-1][1]);


	}
	int BoardArray2D::isSolved(){
		int temp_x,temp_y,
			res,random_num,
			r_row,r_col;

		char comp[9][9];

		r_row=getRow();
		r_col=getColumn();

		final_sol_2D(arr,comp,getRow(),getColumn());
		/*Find space coordinate*/
		find_space_place_2D(arr,&temp_x,&temp_y,r_row,r_col);
		/*For left*/
		if(temp_y != 0 && (arr[temp_x][temp_y-1] != '0' || arr[temp_x][temp_y-2] != '0')){
			swap(&arr[temp_x][temp_y],&arr[temp_x][temp_y-2]);
			swap(&arr[temp_x][temp_y+1],&arr[temp_x][temp_y-1]);
			move_num++;
			num_board++;
			last_move='L';
			res=comparison_2d_arr(arr,comp,r_row,r_col);		
		}
		if(res == 1)
			return 1;
		/*Find space coordinate*/
		find_space_place_2D(arr,&temp_x,&temp_y,r_row,r_col);
		swap(&arr[temp_x][temp_y],&arr[temp_x][temp_y+2]);
		swap(&arr[temp_x][temp_y+1],&arr[temp_x][temp_y+3]);
		/*Find space coordinate*/
		find_space_place_2D(arr,&temp_x,&temp_y,r_row,r_col);
		/*For right*/
		if(temp_y != ((getColumn()*2)-2) && (arr[temp_x][temp_y+2] != '0' || arr[temp_x][temp_y+3] != '0')){
			swap(&arr[temp_x][temp_y],&arr[temp_x][temp_y+2]);
			swap(&arr[temp_x][temp_y+1],&arr[temp_x][temp_y+3]);
			move_num++;
			num_board++;
			last_move='R';
			res=comparison_2d_arr(arr,comp,r_row,r_col);	
		}
		if(res == 1)
			return 1;
		/*Find space coordinate*/
		find_space_place_2D(arr,&temp_x,&temp_y,r_row,r_col);
		swap(&arr[temp_x][temp_y],&arr[temp_x][temp_y-2]);
		swap(&arr[temp_x][temp_y+1],&arr[temp_x][temp_y-1]);
		/*Find space coordinate*/
		find_space_place_2D(arr,&temp_x,&temp_y,r_row,r_col);
		/*For up*/
		if(temp_x != 0 && (arr[temp_x-1][temp_y] != '0' || arr[temp_x-1][temp_y+1] != '0')){
			swap(&arr[temp_x][temp_y],&arr[temp_x-1][temp_y]);
			swap(&arr[temp_x][temp_y+1],&arr[temp_x-1][temp_y+1]);
			move_num++;
			num_board++;
			last_move='U';
			res=comparison_2d_arr(arr,comp,r_row,r_col);	
		}
		if(res == 1)
			return 1;	
		/*Find space coordinate*/
		find_space_place_2D(arr,&temp_x,&temp_y,r_row,r_col);
		swap(&arr[temp_x][temp_y],&arr[temp_x+1][temp_y]);
		swap(&arr[temp_x][temp_y+1],&arr[temp_x+1][temp_y+1]);
		/*Find space coordinate*/
		find_space_place_2D(arr,&temp_x,&temp_y,r_row,r_col);
		/*For down*/
		if(temp_x != (getRow()-1) && (arr[temp_x+1][temp_y] != '0' || arr[temp_x+1][temp_y+1] != '0')){
			swap(&arr[temp_x][temp_y],&arr[temp_x+1][temp_y]);
			swap(&arr[temp_x][temp_y+1],&arr[temp_x+1][temp_y+1]);
			move_num++;
			num_board++;
			last_move='D';
			res=comparison_2d_arr(arr,comp,r_row,r_col);
		}
		if(res == 1)
			return 1;	
		/*Find space coordinate*/
		find_space_place_2D(arr,&temp_x,&temp_y,r_row,r_col);
		swap(&arr[temp_x][temp_y],&arr[temp_x-1][temp_y]);
		swap(&arr[temp_x][temp_y+1],&arr[temp_x-1][temp_y+1]);

		srand(time(NULL));
		random_num=rand()%4;

		if(random_num == 0){
			move('R');
			last_move='R';
		}
		else if(random_num == 1){
			move('L');
			last_move='L';
		}
		else if(random_num == 2){
			move('U');
			last_move='U';
		}
		else if(random_num == 3){
			move('D');
			last_move='D';
		}

	}
	int BoardArray2D::printReport(){
		int return_value;
		char comp[9][9];
		cout<<"Move number: "<<move_num<<endl;
		cout<<"Number of boards: "<<num_board<<endl;
		cout<<"Last move: "<<last_move<<endl;

		final_sol_2D(arr,comp,getRow(),getColumn());

		return_value=comparison_2d_arr(arr,comp,getRow(),getColumn());
	}
	BoardArray2D::~BoardArray2D(){
		for(int i=0;i<getRow();i++)
			delete [] arr[i];
		delete [] arr;
	}

	/*Find space place for Boardvector*/
	void find_space_place(vector<char>box,int *x){
		for(int i=0;i<box.size();i++){
			if(box[i] == 'b'){
				*x=i;
				break;
			}
		}
	}
	/*Swapping cell*/
	void swap(char *x,char *y){
		char temp;
		temp=*x;
		*x=*y;
		*y=temp;
	}
	/*Find space place for BoardArray1D*/
	void find_space_place_1D(char *str,int *x,int t_row,int t_col){
		for(int i=0;i<(t_row*t_col*2);i++){
			if(str[i] == 'b'){
				*x=i;
				break;
			}
		}
	}
	/*Find space place for BoardArray2D*/
	void find_space_place_2D(char **arr,int *x,int *y,int r_row,int r_col){
		for(int i=0;i<r_row;i++){
			for(int j=0;j<(r_col*2);j++){
				if(arr[i][j] == 'b'){
					*x=i;
					*y=j;
					break;
				}
			}
		}

	}
	/*Final solution assignment char vcs*/
	void final_solution(char *str,char vcs[10000],int n_row,int n_col){
		int counter=1,count=1,i;

		for(i=0;i<(n_row*n_col*2);i++){
			if(str[i] == '0' && str[i+1] == '0'){
				vcs[i]='0';
				vcs[i+1]='0';
				i += 1;
			}
			else{
				if(count < 10){
					vcs[i]='0';
					vcs[i+1]='0'+counter;
					counter++;
					count++;
				}
				else if(count >= 10 && count < 20){
					if(count == 10){
						counter=1;
						vcs[i]='1';
						vcs[i+1]='0';
						count++;
					}
					else{
						vcs[i]='1';
						vcs[i+1]='0'+counter;
						counter++;
						count++;
					}
				}
				else if(count >= 20 && count < 30){
					if(count == 20){
						counter=1;
						vcs[i]='2';
						vcs[i+1]='0';
						count++;
					}
					else{
						vcs[i]='2';
						vcs[i+1]='0'+counter;
						counter++;
						count++;	
					}
				}
				else if(count >= 30 && count <40){
					if(count == 30){
						counter=1;
						vcs[i]='3';
						vcs[i+1]='0';
						count++;
					}
					else{
						vcs[i]='3';
						vcs[i+1]='0'+counter;
						counter++;
						count++;	
					}

				}
				i += 1;
			}
		}

		vcs[(n_row*n_col*2)-1]='b';
		vcs[(n_row*n_col*2)-2]='b';
	}
	/*Vector box and final solution vcs compare*/
	int comparison_vec(vector<char>box,char vcs[10000]){
		int count=0;

		for(int i=0;i<box.size();i++){
			if(box[i] == vcs[i])
				count++;
		}
		if(count == box.size())
			return 1;
		else
			return 0;
	}
	void final_solution_vec(vector<char>box,char vcs[10000],int n_row,int n_col){
		int counter=1,count=1,i;

		for(i=0;i<(n_row*n_col*2);i++){
			if(box[i] == '0' && box[i+1] == '0'){
				vcs[i]='0';
				vcs[i+1]='0';
				i += 1;
			}
			else{
				if(count < 10){
					vcs[i]='0';
					vcs[i+1]='0'+counter;
					counter++;
					count++;
				}
				else if(count >= 10 && count < 20){
					if(count == 10){
						counter=1;
						vcs[i]='1';
						vcs[i+1]='0';
						count++;
					}
					else{
						vcs[i]='1';
						vcs[i+1]='0'+counter;
						counter++;
						count++;
					}
				}
				else if(count >= 20 && count < 30){
					if(count == 20){
						counter=1;
						vcs[i]='2';
						vcs[i+1]='0';
						count++;
					}
					else{
						vcs[i]='2';
						vcs[i+1]='0'+counter;
						counter++;
						count++;	
					}
				}
				else if(count >= 30 && count <40){
					if(count == 30){
						counter=1;
						vcs[i]='3';
						vcs[i+1]='0';
						count++;
					}
					else{
						vcs[i]='3';
						vcs[i+1]='0'+counter;
						counter++;
						count++;	
					}

				}
				i += 1;
			}
		}

		vcs[(n_row*n_col*2)-1]='b';
		vcs[(n_row*n_col*2)-2]='b';
	}
	int comparison_1d_arr(char *str,char vcs[10000],int r,int c){
		int count=0;

		for(int i=0;i<(r*c*2);i++){
			if(str[i] == vcs[i])
				count++;
		}
		if(count == (r*c*2))
			return 1;
		else 
			return 0;
	}
	int comparison_2d_arr(char **arr,char comp[9][9],int r,int c){
		int count=0;

		for(int i=0;i<r;i++){
			for(int j=0;j<(c*2);j++){
				if(arr[i][j] == comp[i][j] && arr[i][j+1] == comp[i][j+1])
					count++;
				j += 1;
			}
		}
		if(count ==(r*c*2))
			return 1;
		else
			return 0;

	}
	void final_sol_2D(char **arr,char comp[9][9],int therow,int thecol){
		int i,j,count=1,counter=1;

		for(i=0;i<therow;i++){
			for(j=0;j<thecol;j++){
				if(arr[i][j] == '0' && arr[i][j+1] == '0'){
					comp[i][j]='0';
					comp[i][j+1]='0';
				}
				else{
					if(count < 10){
						comp[i][j]='0';
						comp[i][j+1]='0'+counter;
						counter++;
						count++;
					}
					else if(count >= 10 && count < 20){
						if(count == 10){
							counter=1;
							comp[i][j]='1';
							comp[i][j+1]='0';
							count++;
						}
						else{
							comp[i][j]='1';
							comp[i][j+1]='0'+counter;
							counter++;
							count++;
						}
					}
					else if(count >= 20 && count < 30){
						if(count == 20){
							counter=1;
							comp[i][j]='2';
							comp[i][j+1]='0';
							count++;
						}
						else{
							comp[i][j]='2';
							comp[i][j+1]='0'+counter;
							counter++;
							count++;
						}
					}
					else if(count >= 30 && count < 40){
						if(count == 30){
							counter=1;
							comp[i][j]='3';
							comp[i][j+1]='0';
							count++;
						}
						else{
							comp[i][j]='3';
							comp[i][j+1]='0';
							counter++;
							count++;
						}
					}
				}
				j+=1;
			}
		}
	}
	//Global function*/
	int foo(const vector<AbstractBoard*>&v){
		cout<<"Problem solved"<<endl;
		return 1;
	}

}
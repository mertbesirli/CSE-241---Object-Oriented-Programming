#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;

#define MAX_SIZE 9
#define COMP_ARR_SIZE 4

void filling_array(int s,int board_n[]);
void swap(int *x,int *y);
void printing_board(int board_p[MAX_SIZE][MAX_SIZE],int size);
void find_space_place(int board_p[MAX_SIZE][MAX_SIZE],int *x,int *y,int size);
void finding_true_place(int board_temp[MAX_SIZE][MAX_SIZE],int *x,int *y,int num,int size);

int main(int argc, char const *argv[])
{
	int size,sqrt_size,
		i,j,	//For loop
		tmp,	//For swap
		count=0,
		ssb=0,
		temp_x,temp_y,//For x-y
		flag=0,
		move_num=0, //For move number
		x,y,	//For intelling move
		num,
		sum=0,
		coor_x,coor_y,
		num_ai;
	int compare_arr[COMP_ARR_SIZE]={10000,10000,10000,10000};
	char choice;	//For up,right etc.

	/*Taken size from user*/
	cout<<"Please enter the problem size: \n";
	cin>>size;
	cout<<"\n";
	/*Size condition*/
	while(size < 3 || size > 9 ){
		cout<<"Please enter the problem size: \n";
		cin>>size;
		cout<<"\n";
	}

	/*Find sizee square for filling array number*/
	sqrt_size=size*size;
	/*Board variables*/
	int board_p[MAX_SIZE][MAX_SIZE],
		 board_num[sqrt_size];
	/*Its necessary for finished game*/ 
	int board_temp[MAX_SIZE][MAX_SIZE],
		board_temp_num[sqrt_size];

	/*According to size, filling array numbers*/
	filling_array(sqrt_size,board_num);	


	srand(time(NULL));	//For random numbers
	/*Mixing numbers for board*/
	for(i=0;i<(sqrt_size-1);i++){
		/*Random number*/
		j=rand()%(sqrt_size-i);
		/*Doing swap*/
		tmp=board_num[i];
		board_num[i]=board_num[j];
		board_num[j]=tmp;
	}

	/*Put the values ​​in the array we will use*/
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			board_p[i][j]=board_num[count];
			count++;
		}
	}
	/*The board needed the true shape */
	for(i=0;i<(sqrt_size-1);i++)
		board_temp_num[i]=(i+1);
	board_temp_num[sqrt_size-1]=0;

	count=0;
	/*The correct numbers were thrown on the replacement board*/
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			board_temp[i][j]=board_temp_num[count];
			count++;
		}
	}

	/*Printing board*/
	printing_board(board_p,size);

	while(1){
		count=0;
		/*Problem is correct then solved*/
		for(i=0;i<size;i++){
			for(j=0;j<size;j++){
				if(board_p[i][j] == board_temp[i][j])
					count++;
			}
		}
		/*Condition of finish*/
		if(count == sqrt_size)
			flag=1;
		if(flag == 1){
			cout<<"Problem solved!\n";
			cout<<"Total number of moves: "<<move_num<<endl;
			break;
		}
		/*Choice move*/
		cout<<"Your move: ";
		cin>>choice;
				
		if(flag != 1){
			switch(choice){
				case 'L':
					/*Find space place*/
					find_space_place(board_p,&temp_x,&temp_y,size);

					/*Condition not to go off board and move left*/
					if(temp_y != 0){
						swap(&board_p[temp_x][temp_y],&board_p[temp_x][temp_y-1]);
						/*Count move number*/
						move_num++;
					}
					else
						cout<<"Wrong move,please enter the other move shape!!\n";
					/*Printing board*/
					printing_board(board_p,size);
					break;
				case 'R':
					/*Find space place*/
					find_space_place(board_p,&temp_x,&temp_y,size);
					/*Condition not to go off board and move right*/
					if(temp_y != (size-1)){
						swap(&board_p[temp_x][temp_y],&board_p[temp_x][temp_y+1]);
						/*Count move number*/
						move_num++;
					}
					else
						cout<<"Wrong move,please enter the other move shape!!\n";
					/*Printing board*/
					printing_board(board_p,size);
					break;
				case 'U':
					/*Find space place*/
					find_space_place(board_p,&temp_x,&temp_y,size);
					/*Condition not to go off board and move up*/
					if(temp_x != 0){
						swap(&board_p[temp_x][temp_y],&board_p[temp_x-1][temp_y]);
						move_num++;
					}
					else
						cout<<"Wrong move,please enter the other move shape!!\n";
					/*Printing board*/
					printing_board(board_p,size);
					break;
				case 'D':
					/*Find space place*/
					find_space_place(board_p,&temp_x,&temp_y,size);
					/*Condition not to go off board and move down*/
					if(temp_x != (size-1)){
						swap(&board_p[temp_x][temp_y],&board_p[temp_x+1][temp_y]);
						/*Count move number*/
						move_num++;
					}
					else
						cout<<"Wrong move,please enter the other move shape!!\n";
					/*Printing board*/
					printing_board(board_p,size);
					break;
				case 'S':
					/*First final solution*/
					for(i=0;i<size;i++){
						for(j=0;j<size;j++)
							board_p[i][j] == board_temp[i][j];		
					}
					srand(time(NULL));
					/*Mixing numbers for board*/
					for(i=0;i<(sqrt_size-1);i++){
						/*Random number*/
						j=rand()%(sqrt_size-i);
						/*Doing swap*/
						tmp=board_num[i];
						board_num[i]=board_num[j];
						board_num[j]=tmp;
					}

					/*Put the values ​​in the array we will use*/
					for(i=0;i<size;i++){
						for(j=0;j<size;j++){
							board_p[i][j]=board_num[ssb];
							ssb++;
						}
					}
					ssb=0;
					move_num=0;
					/*Printing board*/
					printing_board(board_p,size);
					break;
				case 'I':
					/*Find space place*/
					find_space_place(board_p,&temp_x,&temp_y,size);
					sum=0;
					/*For left*/
					/*Condition not to go off board and move left*/
					if(temp_y != 0){
						swap(&board_p[temp_x][temp_y],&board_p[temp_x][temp_y-1]);
						/*Calculate misplaced elements distance*/
						for(i=0;i<size;i++){
							for(j=0;j<size;j++){
								if(board_p[i][j] != board_temp[i][j] && board_p[i][j] != 0){
									coor_x=i;
									coor_y=j;
									num=board_p[i][j];
									/*Find misplaced number location*/
									finding_true_place(board_temp,&x,&y,num,size);
									sum += (abs(coor_x-x)+abs(coor_y-y));
								}
							}
						}
						/*The condition for deciding which direction you are going*/
						compare_arr[0]=sum;
						/*Find space place*/
						find_space_place(board_p,&temp_x,&temp_y,size);
						/*Value returns*/
						swap(&board_p[temp_x][temp_y],&board_p[temp_x][temp_y+1]);
						sum=0;
					}
					/*Find space place*/
					find_space_place(board_p,&temp_x,&temp_y,size);
					/*For right*/
					/*Condition not to go off board and move right*/
					if(temp_y != (size-1)){
						swap(&board_p[temp_x][temp_y],&board_p[temp_x][temp_y+1]);
						/*Calculate misplaced elements distance*/
						for(i=0;i<size;i++){
							for(j=0;j<size;j++){
								if(board_p[i][j] != board_temp[i][j] && board_p[i][j] != 0){
									coor_x=i;
									coor_y=j;
									num=board_p[i][j];
									/*Find misplaced number location*/
									finding_true_place(board_temp,&x,&y,num,size);
									sum += (abs(coor_x-x)+abs(coor_y-y));
								}
							}
						}
						/*The condition for deciding which direction you are going*/
						compare_arr[1]=sum;
						/*Find space place*/
						find_space_place(board_p,&temp_x,&temp_y,size);
						/*Value returns*/
						swap(&board_p[temp_x][temp_y],&board_p[temp_x][temp_y-1]);
						sum=0;	
					}
					/*Find space place*/
					find_space_place(board_p,&temp_x,&temp_y,size);
					/*For up*/
					/*Condition not to go off board and move up*/
					if(temp_x != 0){
						swap(&board_p[temp_x][temp_y],&board_p[temp_x-1][temp_y]);
						/*Calculate misplaced elements distance*/
						for(i=0;i<size;i++){
							for(j=0;j<size;j++){
								if(board_p[i][j] != board_temp[i][j] && board_p[i][j] != 0){
									coor_x=i;
									coor_y=j;
									num=board_p[i][j];
									/*Find misplaced number location*/
									finding_true_place(board_temp,&x,&y,num,size);
									sum += (abs(coor_x-x)+abs(coor_y-y));
								}
							}
						}
						/*The condition for deciding which direction you are going*/
						compare_arr[2]=sum;
						/*Find space place*/
						find_space_place(board_p,&temp_x,&temp_y,size);
						/*Value returns*/
						swap(&board_p[temp_x][temp_y],&board_p[temp_x+1][temp_y]);
						sum=0;	
					}
					/*Find space place*/
					find_space_place(board_p,&temp_x,&temp_y,size);
					/*For down*/
					/*Condition not to go off board and move down*/
					if(temp_x != (size-1)){
						swap(&board_p[temp_x][temp_y],&board_p[temp_x+1][temp_y]);
						/*Calculate misplaced elements distance*/
						for(i=0;i<size;i++){
							for(j=0;j<size;j++){
								if(board_p[i][j] != board_temp[i][j] && board_p[i][j] != 0){
									coor_x=i;
									coor_y=j;
									num=board_p[i][j];
									/*Find misplaced number location*/
									finding_true_place(board_temp,&x,&y,num,size);
									sum += (abs(coor_x-x)+abs(coor_y-y));
								}
							}
						}
						/*The condition for deciding which direction you are going*/
						compare_arr[3]=sum;
						/*Find space place*/
						find_space_place(board_p,&temp_x,&temp_y,size);
						/*Value returns*/
						swap(&board_p[temp_x][temp_y],&board_p[temp_x-1][temp_y]);
						sum=0;	
					}
					/*Smallest number*/
					num=compare_arr[0];
					num_ai=0;
					for(i=1;i<4;i++){
						if(compare_arr[i] < num){
							num_ai=i;
							num=compare_arr[i];
						}
					}
					if(num_ai == 0){
						/*Find space place*/
						find_space_place(board_p,&temp_x,&temp_y,size);

						/*Condition not to go off board and move left*/
						if(temp_y != 0){
							swap(&board_p[temp_x][temp_y],&board_p[temp_x][temp_y-1]);
							/*Count move number*/
							move_num++;
						}
						cout<<"Intelligent move choose: L\n";
					}
					
					else if(num_ai == 1){
						/*Find space place*/
						find_space_place(board_p,&temp_x,&temp_y,size);
						/*Condition not to go off board and move right*/
						if(temp_y != (size-1)){
							swap(&board_p[temp_x][temp_y],&board_p[temp_x][temp_y+1]);
							/*Count move number*/
							move_num++;
						}
						cout<<"Intelligent move choose: R\n";
					}
					else if(num_ai == 2){
						/*Find space place*/
						find_space_place(board_p,&temp_x,&temp_y,size);
						/*Condition not to go off board and move up*/
						if(temp_x != 0){
							swap(&board_p[temp_x][temp_y],&board_p[temp_x-1][temp_y]);
							move_num++;
						}
						cout<<"Intelligent move choose: U\n";
					}
					else if(num_ai == 3){
						/*Find space place*/
						find_space_place(board_p,&temp_x,&temp_y,size);
						/*Condition not to go off board and move down*/
						if(temp_x != (size-1)){
							swap(&board_p[temp_x][temp_y],&board_p[temp_x+1][temp_y]);
							/*Count move number*/
							move_num++;
						}
						cout<<"Intelligent move choose: D\n";
					}
					/*Return first situation*/
					for(i=0;i<4;i++)
						compare_arr[i]=10000;
					/*Printing board*/
					printing_board(board_p,size);
					break;
				case 'Q':
					/*For exit*/
					flag=1;
					break;
			}
		}	
		if(flag == 1){
			cout<<"Total number of moves: "<<move_num<<endl;
			break;
		}
	}
	
	return 0;
}


/*According to size, filling array numbers*/
void filling_array(int s,int board_n[]){

	for(int i=0;i<s;i++)
		board_n[i]=i;

}

/*Swap numbers place*/
void swap(int *x,int *y){
	int tmp;

	tmp=*x;
	*x=*y;
	*y=tmp;

}
/*Printing board*/
void printing_board(int board_p[MAX_SIZE][MAX_SIZE],int size){
	int i,j;

	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(board_p[i][j] == 0)
				cout<<"   ";
			else{
				if(board_p[i][j] < 10 && board_p[i][j] > 0)
					cout<<board_p[i][j]<<"  ";
				else
					cout<<board_p[i][j]<<" ";
			}
		}
		cout<<"\n";
	}

}
/*Find space place for board*/
void find_space_place(int board_p[MAX_SIZE][MAX_SIZE],int *x,int *y,int size){
	int i,j;

	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(board_p[i][j] == 0){
				*x=i;
				*y=j;
			}
		}
	}
}
/*Find the actual location of the number*/
void finding_true_place(int board_temp[MAX_SIZE][MAX_SIZE],int *x,int *y,int num,int size){
	int i,j;

	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(board_temp[i][j] == num){
				*x=i;
				*y=j;
			}
		}
	}
}
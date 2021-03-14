import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.Scanner;
import java.util.Random;
import java.io.FileWriter;
import java.util.Arrays;
/**
*BoardArray2D derived class to AbstractBoard
*It is invoked char one dimensional array
*Do vertain operations with methods.
*/


public class BoardArray2D extends AbstractBoard{

	private char arr2d [][];
	protected int x_coor=0;
	protected int y_coor=0;

	/**
	*Seven argument constructor
	*/
	public BoardArray2D(int therow,int thecolumn,int themove_num,int thenum_board,char thelast_move,int x,int y){
		super(therow,thecolumn,themove_num,thenum_board,thelast_move);
		setX(x);
		setY(y);
		arr2d=new char [9][26];
	}
	/**
	*@param x int
	*/
	public void setX(int x){
		x_coor=x;
	}
	/**
	*Get coordinate
	*@return int x_coor, x coordinate
	*/
	public int getX(){
		return x_coor;
	}
	/**
	*@param y int
	*/
	public void setY(int y){
		y_coor=y;
	}
	/**
	*Get coordinate
	*@return int y_coor, y coordinate
	*/
	public int getY(){
		return y_coor;
	}
	/**
	*Read from text files and find row and column to array
	*@param filename String, taken args[0]
	*@see Exception
	*/
	public void readFromFile(String filename)throws Exception{

		//It's necessary from read file
		String s[]=new String[9];
		int i=0;
		int x=0;
		int count=0;

		//Read from file
		File file = new File(filename);
		BufferedReader reader = null;
		reader = new BufferedReader(new FileReader(file));
		String col = reader.readLine();
		//Read and find row
		while (col!=null) {
			s[i]=col;
			i++;
			col = reader.readLine();
		}
		
		row=i;
		//Put them all on my array
		for(int k=0;k<row;k++){
			for(int j=0;j<s[0].length();j++){
				arr2d[k][j]=s[k].charAt(j);
				if(arr2d[k][j] == ' ')
					x++;
			}
		}
		//Find column
		int res=(row*s[0].length());
		column=res/row;
	}
	/**
	*args.length != 1, taken row and column from user
	*/
	public void setSize(){
		int r,c;
		Scanner input=new Scanner(System.in);

		/*Taken user row and column*/
		System.out.println("Please row: ");
		r=input.nextInt();
		setRow(r);
		System.out.println("Please column: ");
		c=input.nextInt();
		setColumn((c*2)+c-1);
	}
	/**
	*Array move left, right, up ,down
	*bb element similar space, changing place it
	*@param x char, determine direction
	*/
	public void move(char x){

		char temp;

		//Left moving
		if(x == 'L'){
			if(y_coor != 0 && (arr2d[x_coor][y_coor-3] != '0' || arr2d[x_coor][y_coor-2] != '0')){
				//Swap two elements
				temp=arr2d[x_coor][y_coor];
				arr2d[x_coor][y_coor]=arr2d[x_coor][y_coor-3];
				arr2d[x_coor][y_coor-3]=temp;
				
				temp=arr2d[x_coor][y_coor+1];
				arr2d[x_coor][y_coor+1]=arr2d[x_coor][y_coor-2];
				arr2d[x_coor][y_coor-2]=temp;
				//Move number increment and determines last move
				move_num++;
				last_move='L';
			}
			else
				System.out.println("Wrong move,please enter the other move shape!!");
		}
		else if(x == 'R'){
			
			if(y_coor != (column-2) && (arr2d[x_coor][y_coor+3] != '0' || arr2d[x_coor][y_coor+4] != '0')){
				//Swap two elements
				temp=arr2d[x_coor][y_coor];
				arr2d[x_coor][y_coor]=arr2d[x_coor][y_coor+3];
				arr2d[x_coor][y_coor+3]=temp;
		
				temp=arr2d[x_coor][y_coor+1];
				arr2d[x_coor][y_coor+1]=arr2d[x_coor][y_coor+4];
				arr2d[x_coor][y_coor+4]=temp;
				//Move number increment and determines last move
				move_num++;
				last_move='R';
			}
			else
				System.out.println("Wrong move,please enter the other move shape!!");
		}
		else if(x == 'U'){
			if(x_coor != 0 && (arr2d[x_coor-1][y_coor] != '0' || arr2d[x_coor-1][y_coor+1] != '0')){
				//Swap two elements
				temp=arr2d[x_coor][y_coor];
				arr2d[x_coor][y_coor]=arr2d[x_coor-1][y_coor];
				arr2d[x_coor-1][y_coor]=temp;
			
				temp=arr2d[x_coor][y_coor+1];
				arr2d[x_coor][y_coor+1]=arr2d[x_coor-1][y_coor+1];
				arr2d[x_coor-1][y_coor+1]=temp;
				//Move number increment and determines last move
				move_num++;
				last_move='U';
			}
			else
				System.out.println("Wrong move,please enter the other move shape!!");
		}
		else if(x == 'D'){
			if(x_coor != (row-1) && (arr2d[x_coor+1][y_coor] != '0' || arr2d[x_coor+1][y_coor+1] != '0')){
				//Swap two elements
				temp=arr2d[x_coor][y_coor];
				arr2d[x_coor][y_coor]=arr2d[x_coor+1][y_coor];
				arr2d[x_coor+1][y_coor]=temp;
				
				temp=arr2d[x_coor][y_coor+1];
				arr2d[x_coor][y_coor+1]=arr2d[x_coor+1][y_coor+1];
				arr2d[x_coor+1][y_coor+1]=temp;
				//Move number increment and determines last move
				move_num++;
				last_move='D';
			}
			else
				System.out.println("Wrong move,please enter the other move shape!!");
		}
		//Shuffle move
		else if(x == 'S'){
			//Find random number for shuffle move
			Random r=new Random();
			int number=r.nextInt(4);
			//According to random number moving
			if(number == 0){
				x='L';
				this.move(x);
			}
			else if(number == 1){
				x='R';
				this.move(x);
			}
			else if(number == 2){
				x='U';
				this.move(x);
			}
			else if(number == 3){
				x='D';
				this.move(x);
			}
		}

		
	}
	/**
	*Find bb(space) place
	*@return temp_x int 
	*/
	public int find_space_place_2D(){
		//Find "bb" coordinates
		for(int i=0;i<row;i++){
			for(int j=0;j<column;j++){
				if(arr2d[i][j] == 'b'){
					x_coor=i;
					y_coor=j;
					break;
				}
			}
		}
		return x_coor;
	}
	/**
	*Find correct cell
	*@param s1 int first element
	*@param s2 int second element
	*@return correct array element
	*/
	public char cell(int s1,int s2){
		return arr2d[s1][s2];
	}
	/**
	*It is solved method, creating left, right, up, down boards
	*but if prove conditions then creating boards and not find final solution
	*making random move
	*@return boolean
	*/
	public boolean isSolved(){
		//Solution array, we need
		char temp_array_2d [][]=new char [9][26];
		int i,j;
		int counter=1,count=1;
		char temp;
		int res=0,flag=0;
		//Find final solution array for comparison my array
		for(i=0;i<row;i++){
			for(j=0;j<column;j++){
				if(arr2d[i][j] == '0' && arr2d[i][j+1] == '0'){
					temp_array_2d[i][j]='0';
					temp_array_2d[i][j+1]='0';
				}
				else{
					if(count < 10){
						temp_array_2d[i][j]='0';
						temp_array_2d[i][j+1]=(char)('0'+counter);
						counter++;
						count++;
					}
					else if(count >= 10 && count < 20){
						if(count == 10){
							counter=1;
							temp_array_2d[i][j]='1';
							temp_array_2d[i][j+1]='0';
							count++;
						}
						else{
							temp_array_2d[i][j]='1';
							temp_array_2d[i][j+1]=(char)('0'+counter);
							counter++;
							count++;
						}
					}
					else if(count >= 20 && count < 30){
						if(count == 20){
							counter=1;
							temp_array_2d[i][j]='2';
							temp_array_2d[i][j+1]='0';
							count++;
						}
						else{
							temp_array_2d[i][j]='2';
							temp_array_2d[i][j+1]=(char)('0'+counter);
							counter++;
							count++;
						}
					}
					else if(count >= 30 && count < 40){
						if(count == 30){
							counter=1;
							temp_array_2d[i][j]='3';
							temp_array_2d[i][j+1]='0';
							count++;
						}
						else{
							temp_array_2d[i][j]='3';
							temp_array_2d[i][j+1]=(char)('0'+counter);
							counter++;
							count++;
						}
					}
				}//end of else
				if(j != column){
					if(j != (column-2)){
						temp_array_2d[i][j+2]=' ';
						j+=2;
					}
					else
						j+=1;
				}
			}
		}

		temp_array_2d[row-1][column-1]='b';
		temp_array_2d[row-1][column-2]='b';


		/*For left*/
		/*If condition not go outside and not go wall('00')*/
		if(y_coor != 0 && (arr2d[x_coor][y_coor-3] != '0' || arr2d[x_coor][y_coor-2] != '0')){
			//Swap two elements
			temp=arr2d[x_coor][y_coor];
			arr2d[x_coor][y_coor]=arr2d[x_coor][y_coor-3];
			arr2d[x_coor][y_coor-3]=temp;
			
			temp=arr2d[x_coor][y_coor+1];
			arr2d[x_coor][y_coor+1]=arr2d[x_coor][y_coor-2];
			arr2d[x_coor][y_coor-2]=temp;
			//Move number and number of boards increment and determines last move
			move_num++;
			num_board++;
			last_move='L';
			flag=1;
			//Comparison two array if equal return true;
			if(Arrays.equals(arr2d,temp_array_2d))
				res=1;
			//bb place coordinate changing
			y_coor -= 3;
		}
		
		if(flag == 1){
			//Result true and return 1
			if(res == 1)
				return true;
			//Result is false and will be restored
			temp=arr2d[x_coor][y_coor];
			arr2d[x_coor][y_coor]=arr2d[x_coor][y_coor+3];
			arr2d[x_coor][y_coor+3]=temp;
			//
			temp=arr2d[x_coor][y_coor+1];
			arr2d[x_coor][y_coor+1]=arr2d[x_coor][y_coor+4];
			arr2d[x_coor][y_coor+4]=temp;
			//bb place coordinate changing
			y_coor += 3;
			flag=0;
		}

		/*For right*/
		/*If condition not go outside and not go wall('00')*/
		if(y_coor != (column-2) && (arr2d[x_coor][y_coor+3] != '0' || arr2d[x_coor][y_coor+4] != '0')){
			//Swap two elements
			temp=arr2d[x_coor][y_coor];
			arr2d[x_coor][y_coor]=arr2d[x_coor][y_coor+3];
			arr2d[x_coor][y_coor+3]=temp;
			
			temp=arr2d[x_coor][y_coor+1];
			arr2d[x_coor][y_coor+1]=arr2d[x_coor][y_coor+4];
			arr2d[x_coor][y_coor+4]=temp;
			//Move number and number of boards increment and determines last move
			move_num++;
			num_board++;
			last_move='R';
			flag=1;
			//Comparison two array if equal return true;
			if(Arrays.equals(arr2d,temp_array_2d))
				res=1;
			//bb place coordinate changing
			y_coor +=3;
		}
		
		if(flag == 1){
			//Result true and return 1
			if(res == 1)
				return true;
			//Result is false and will be restored
			temp=arr2d[x_coor][y_coor];
			arr2d[x_coor][y_coor]=arr2d[x_coor][y_coor-3];
			arr2d[x_coor][y_coor-3]=temp;
			
			temp=arr2d[x_coor][y_coor+1];
			arr2d[x_coor][y_coor+1]=arr2d[x_coor][y_coor-2];
			arr2d[x_coor][y_coor-2]=temp;
			//bb place coordinate changing
			y_coor -= 3;
			flag=0;
		}

		//For up
		/*If condition not go outside and not go wall('00')*/
		if(x_coor != 0 && (arr2d[x_coor-1][y_coor] != '0' || arr2d[x_coor-1][y_coor+1] != '0')){
			//Swap two elements
			temp=arr2d[x_coor][y_coor];
			arr2d[x_coor][y_coor]=arr2d[x_coor-1][y_coor];
			arr2d[x_coor-1][y_coor]=temp;
			
			temp=arr2d[x_coor][y_coor+1];
			arr2d[x_coor][y_coor+1]=arr2d[x_coor-1][y_coor+1];
			arr2d[x_coor-1][y_coor+1]=temp;
			//Move number and number of boards increment and determines last move
			move_num++;
			num_board++;
			last_move='U';
			flag=1;
			//Comparison two array if equal return true;
			if(Arrays.equals(arr2d,temp_array_2d))
				res=1;
			//bb place coordinate changing
			x_coor -= 1;
		}
		
		if(flag == 1){
			//Result true and return 1
			if(res == 1)
				return true;
			//Result is false and will be restored
			temp=arr2d[x_coor][y_coor];
			arr2d[x_coor][y_coor]=arr2d[x_coor+1][y_coor];
			arr2d[x_coor+1][y_coor]=temp;
			
			temp=arr2d[x_coor][y_coor+1];
			arr2d[x_coor][y_coor+1]=arr2d[x_coor+1][y_coor+1];
			arr2d[x_coor+1][y_coor+1]=temp;
			//bb place coordinate changing
			x_coor += 1;
			flag=0;
		}
		//For down
		/*If condition not go outside and not go wall('00')*/
		if(x_coor != (row-1) && (arr2d[x_coor+1][y_coor] != '0' || arr2d[x_coor+1][y_coor+1] != '0')){
			//Swap two elements
			temp=arr2d[x_coor][y_coor];
			arr2d[x_coor][y_coor]=arr2d[x_coor+1][y_coor];
			arr2d[x_coor+1][y_coor]=temp;
			
			temp=arr2d[x_coor][y_coor+1];
			arr2d[x_coor][y_coor+1]=arr2d[x_coor+1][y_coor+1];
			arr2d[x_coor+1][y_coor+1]=temp;
			//Move number and number of boards increment and determines last move
			move_num++;
			num_board++;
			last_move='D';
			flag=1;
			//Comparison two array if equal return true;
			if(Arrays.equals(arr2d,temp_array_2d))
				res=1;
			//bb place coordinate changing
			x_coor += 1;
		}
		
		if(flag == 1){
			//Result true and return 1
			if(res == 1)
				return true;
			//Result is false and will be restored
			temp=arr2d[x_coor][y_coor];
			arr2d[x_coor][y_coor]=arr2d[x_coor-1][y_coor];
			arr2d[x_coor-1][y_coor]=temp;
			
			temp=arr2d[x_coor][y_coor+1];
			arr2d[x_coor][y_coor+1]=arr2d[x_coor-1][y_coor+1];
			arr2d[x_coor-1][y_coor+1]=temp;
			//bb place coordinate changing
			x_coor -= 1;
			flag=0;
		}

		//Find random number for shuffle move
		Random r=new Random();
		int random_num=r.nextInt(4);
		
		if(random_num == 0){
			this.move('R');
			last_move='R';
			return false;
		}
		else if(random_num == 1){
			this.move('L');
			last_move='L';
			return false;
		}
		else if(random_num == 2){
			this.move('U');
			last_move='U';
			return false;
		}
		else if(random_num == 3){
			this.move('D');
			last_move='D';
			return false;
		}	
		return false;
	}
	/**
	*After setsize, doing reset 
	*/
	public void reset(){
		int i,j;
		int counter=1,count=1;
		//Reset my array
		for(i=0;i<row;i++){
			for(j=0;j<column;j++){
				if(i==0 && j==0){
					arr2d[i][j]='0';
					arr2d[i][j+1]='0';
				}
				else{
					if(count < 10){
						arr2d[i][j]='0';
						arr2d[i][j+1]=(char)('0'+counter);
						counter++;
						count++;
					}
					else if(count >= 10 && count < 20){
						if(count == 10){
							counter=1;
							arr2d[i][j]='1';
							arr2d[i][j+1]='0';
							count++;
						}
						else{
							arr2d[i][j]='1';
							arr2d[i][j+1]=(char)('0'+counter);
							counter++;
							count++;
						}
					}
					else if(count >= 20 && count < 30){
						if(count == 20){
							counter=1;
							arr2d[i][j]='2';
							arr2d[i][j+1]='0';
							count++;
						}
						else{
							arr2d[i][j]='2';
							arr2d[i][j+1]=(char)('0'+counter);
							counter++;
							count++;
						}
					}
					else if(count >= 30 && count < 40){
						if(count == 30){
							counter=1;
							arr2d[i][j]='3';
							arr2d[i][j+1]='0';
							count++;
						}
						else{
							arr2d[i][j]='3';
							arr2d[i][j+1]=(char)('0'+counter);
							counter++;
							count++;
						}
					}
				}//end of else
				if(j != column){
					if(j != (column-2)){
						arr2d[i][j+2]=' ';
						j+=2;
					}
					else
						j+=1;
				}
			}
		}
		arr2d[row-1][column-1]='b';
		arr2d[row-1][column-2]='b';
	}
	/**
	*Find number of moves
	*@return int move_num
	*/
	public int numberOfMoves(){
		return move_num;
	}
	/**
	*Find last move
	*@return char last_move
	*/
	public char lastMove(){
		return last_move;
	}
	/**
	*Find number of boards
	*@return int num_boards
	*/
	public int numberOfBoards(){
		return num_board;
	}
	/**
	*This method writetofile
	*Asking user filename, then makine operation
	*@param filename args[0] 
	*@see Exception
	*/
	public void writeToFile(String filename)throws Exception{
		Scanner input=new Scanner(System.in);
		//Ask user filename and taken filename to user
		System.out.println("Enter file name and save current board: ");
		String askingFile=input.nextLine();
		/*If it is same file I'm using*/
		if(askingFile == filename){
			FileWriter writer=new FileWriter(filename);
			for(int i=0;i<row;i++){
				for(int j=0;j<column;j++){
					writer.write(arr2d[i][j]);
				}
				writer.write("\n");
			}
			writer.close();
		}
		/*If it is the other file*/
		else{
			FileWriter writer=new FileWriter(askingFile);
			for(int i=0;i<row;i++){
				for(int j=0;j<column;j++){
					writer.write(arr2d[i][j]);
				}
				writer.write("\n");
			}
			writer.close();
			System.out.printf("Saving: %s\n",askingFile);
		}

	}
	/**
	*Equals, compare two array elements
	*@param a Object
	*@param b Object
	*@return boolean
	*/
	public boolean equals(Object [] a,Object [] b){
		if(a == b)
			return true;
		return false;

	}
	/**
	*Shuffle method after reset array
	*@param num int, 50
	*/
	public void shuffle(int num){
		char x='S';
		//It's shuffle as the number.
		for(int i=0;i<num;i++)
			this.move(x);

		char temp;
		//We moved bb to its real coordinate.
		//For first element
		temp=arr2d[x_coor][y_coor];
		arr2d[x_coor][y_coor]=arr2d[row-1][0];
		arr2d[row-1][0]=temp;
		//For second element
		temp=arr2d[x_coor][y_coor+1];
		arr2d[x_coor][y_coor+1]=arr2d[row-1][1];
		arr2d[row-1][1]=temp;

	}
	/**
	*Printing string format
	*@return String
	*/
	public String toString(){
		for(int i=0;i<row;i++){
			for(int j=0;j<column;j++)
				System.out.printf("%c",arr2d[i][j]);
			System.out.println();
		}
		System.out.print("\n");
		return null;
	}

}
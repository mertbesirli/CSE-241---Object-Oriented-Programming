
import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.Scanner;
import java.util.Random;
import java.io.FileWriter;
import java.util.Arrays;
/**
*BoardArray1D derived class to AbstractBoard
*It is invoked char one dimensional array
*Do vertain operations with methods.
*/

public class BoardArray1D extends AbstractBoard{
	private char arr[];
	protected int temp_x=0;


	/**
	*Six argument constructor
	*/
	public BoardArray1D(int therow,int thecolumn,int themove_num,int thenum_board,char thelast_move,int thex){
		super(therow,thecolumn,themove_num,thenum_board,thelast_move);
		setCoorx(thex);
		arr=new char[300];
	}
	/**
	*@param newx int
	*/
	public void setCoorx(int newx){
		temp_x=newx;
	}
	/**
	*Get coordinate
	*@return int temp_x, x coordinate
	*/
	public int getCoorx(){
		return temp_x;
	}
	/**
	*Read from text files and find row and column to array
	*@param filename String, taken args[0]
	*@see Exception
	*/
	public void readFromFile(String filename) throws Exception{

		//It's necessary from read file
		String s[]=new String[9];
		int i=0,
			x=0,
			count=0;


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
				arr[j+count]=s[k].charAt(j);
				if(arr[j+count] == ' ')
					x++;
			}
			count += s[0].length();
		}

		//Find column
		int res=(row*s[0].length());
		column=res/row;
	}//End of readFromFile

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

	}//End of setSize

	/**
	*Array move left, right, up ,down
	*bb element similar space, changing place it
	*@param x char, determine direction
	*/
	public void move(char x){
		
		char temp;

		//Left move
		if(x == 'L'){
			/*If condition not go outside and not go wall('00')*/
			if(temp_x != 0 && temp_x != column && temp_x != (column*2) && temp_x != (column*3) && temp_x != (column*4) && temp_x != (column*5) 
				&& temp_x != (column*6)&& temp_x != (column*7) && temp_x != (column*8) && (arr[temp_x-2] != '0' || arr[temp_x-3] != '0') ){
				//Swap two elements
				temp=arr[temp_x];
				arr[temp_x]=arr[temp_x-3];
				arr[temp_x-3]=temp;
				
				temp=arr[temp_x-2];
				arr[temp_x-2]=arr[temp_x+1];
				arr[temp_x+1]=temp;
				//Move number increment and determines last move
				move_num++;
				last_move='L';
			}
			else
				System.out.println("Wrong move,please enter the other move shape!!");
		}
		else if(x == 'R'){
			/*If condition not go outside and not go wall('00')*/
			if(temp_x != (row*column-2) && (arr[temp_x+3] != '0' || arr[temp_x+4] != '0')){
				//Swap two elements
				temp=arr[temp_x];
				arr[temp_x]=arr[temp_x+3];
				arr[temp_x+3]=temp;
				
				temp=arr[temp_x+1];
				arr[temp_x+1]=arr[temp_x+4];
				arr[temp_x+4]=temp;
				//Move number increment and determines last move
				move_num++;
				last_move='R';
			}
			else
				System.out.println("Wrong move,please enter the other move shape!!");
		}
		//Up move
		else if(x == 'U'){
			/*If condition not go outside and not go wall('00')*/
			if(temp_x >= column && (arr[temp_x-column] != '0' || arr[temp_x-column+1] != '0')){
				//Swap two elements
				temp=arr[temp_x];
				arr[temp_x]=arr[temp_x-column];
				arr[temp_x-column]=temp;
				
				temp=arr[temp_x+1];
				arr[temp_x+1]=arr[temp_x-column+1];
				arr[temp_x-column+1]=temp;
				//Move number increment and determines last move
				move_num++;
				last_move='U';
			}
			else
				System.out.println("Wrong move,please enter the other move shape!!");
		}
		//Down move
		else if(x == 'D'){
			/*If condition not go outside and not go wall('00')*/
			if(temp_x < ((row*column)-(column+1)) && (arr[temp_x+column] != '0' || arr[temp_x+column+1] != '0')){
				//Swap two elements
				temp=arr[temp_x];
				arr[temp_x]=arr[temp_x+column];
				arr[temp_x+column]=temp;
				
				temp=arr[temp_x+1];
				arr[temp_x+1]=arr[temp_x+column+1];
				arr[temp_x+column+1]=temp;
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
			if(number == 1){
				x='L';
				this.move(x);
			}
			else if(number == 2){
				x='R';
				this.move(x);
			}
			else if(number == 3){
				x='U';
				this.move(x);
			}
			else if(number == 4){
				x='D';
				this.move(x);
			}
		}
	}

	/**
	*Find bb(space) place
	*@return temp_x int 
	*/
	public int find_space_place_1D(){

		//Find "bb" coordinate
		for(int i=0;i<(row*column);i++){
			if(arr[i] == 'b'){
				temp_x=i;
				break;
			}	
		}
		return temp_x;
	}	
	/**
	*Find correct cell
	*@param s1 int first element
	*@param s2 int second element
	*@return correct array element
	*/
	public char cell(int s1,int s2){
		return arr[s1];
	}
	/**
	*It is solved method, creating left, right, up, down boards
	*but if prove conditions then creating boards and not find final solution
	*making random move
	*@return boolean
	*/
	public boolean isSolved(){
		//Solution array, we need
		char temp_array [] = new char[300];
		int i,counter=1,count=1,x=1;
		char temp;
		int res=0,flag=0;


		//Find final solution array for comparison my array
		for(i=0;i<(row*column);i++){
			if(arr[i] == '0' && arr[i+1] == '0'){
				temp_array[i]='0';
				temp_array[i+1]='0';
			}
			else{
				if(count < 10){
					temp_array[i]='0';
					temp_array[i+1]=(char)('0'+counter);
					counter++;
					count++;
				}
				else if(count >= 10 && count < 20){
					if(count == 10){
						counter=1;
						temp_array[i]='1';
						temp_array[i+1]='0';
						count++;
					}
					else{
						temp_array[i]='1';
						temp_array[i+1]=(char)('0'+counter);
						counter++;
						count++;
					}
				}
				else if(count >= 20 && count < 30){
					if(count == 20){
						counter=1;
						temp_array[i]='2';
						temp_array[i+1]='0';
						count++;
					}
					else{
						temp_array[i]='2';
						temp_array[i+1]=(char)('0'+counter);
						counter++;
						count++;
					}
				}
				else if(count >= 30 && count < 40){
					if(count == 30){
						counter=1;
						temp_array[i]='3';
						temp_array[i+1]='0';
						count++;
					}
					else{
						temp_array[i]='3';
						temp_array[i+1]=(char)('0'+counter);
						counter++;
						count++;
					}
				}
			}
			if(i != (column*x)){
				if(i != (column*x-2)){
					temp_array[i+2]=' ';
					i+=2;
				}
				else{
					i+=1;
					x+=1;
				}
			}
		}
		temp_array[row*column-1]='b';
		temp_array[row*column-2]='b';


		/*For left*/
		/*If condition not go outside and not go wall('00')*/
		if(temp_x != 0 && temp_x != column && temp_x != (column*2) && temp_x != (column*3) && temp_x != (column*4) && temp_x != (column*5) 
			&& temp_x != (column*6)&& temp_x != (column*7) && temp_x != (column*8) && (arr[temp_x-2] != '0' || arr[temp_x-3] != '0')){
			//Swap two elements
			temp=arr[temp_x];
			arr[temp_x]=arr[temp_x-3];
			arr[temp_x-3]=temp;
			
			temp=arr[temp_x-2];
			arr[temp_x-2]=arr[temp_x+1];
			arr[temp_x+1]=temp;
			//Move number and number of boards increment and determines last move
			move_num++;
			num_board++;
			last_move='L';
			flag=1;
			//Comparison two array if equal return true;
			if(Arrays.equals(arr,temp_array))
				res=1;
			//bb place coordinate changing
			temp_x -= 3;
			
		}
		if(flag == 1){
			//Result true and return 1
			if(res == 1)
				return true;
			//Result is false and will be restored
			temp=arr[temp_x];
			arr[temp_x]=arr[temp_x+3];
			arr[temp_x+3]=temp;

			temp=arr[temp_x+1];
			arr[temp_x+1]=arr[temp_x+4];
			arr[temp_x+4]=temp;
			//bb place coordinate changing
			temp_x += 3;
			flag=0;
		}

		/*For right*/
		/*If condition not go outside and not go wall('00')*/
		if(temp_x != (row*column-2) && (arr[temp_x+3] != '0' || arr[temp_x+4] != '0')){
			//Swap two elements
			temp=arr[temp_x];
			arr[temp_x]=arr[temp_x+3];
			arr[temp_x+3]=temp;
			//
			temp=arr[temp_x+1];
			arr[temp_x+1]=arr[temp_x+4];
			arr[temp_x+4]=temp;
			//Move number and number of boards increment and determines last move
			move_num++;
			num_board++;
			last_move='R';
			flag=1;
			//Comparison two array if equal return true;
			if(Arrays.equals(arr,temp_array))
				res=1;
			//bb place coordinate changing
			temp_x += 3;
		}
		
		if(flag == 1){
			//Result true and return 1
			if(res == 1)
				return true;
			//Result is false and will be restored
			temp=arr[temp_x];
			arr[temp_x]=arr[temp_x-3];
			arr[temp_x-3]=temp;
			//
			temp=arr[temp_x-2];
			arr[temp_x-2]=arr[temp_x+1];
			arr[temp_x+1]=temp;
			//bb place coordinate changing
			temp_x -= 3;
			flag=0;
		}

		//For up
		/*If condition not go outside and not go wall('00')*/
		if(temp_x >= column && (arr[temp_x-column] != '0' || arr[temp_x-column+1] != '0')){
			//Swap two elements
			temp=arr[temp_x];
			arr[temp_x]=arr[temp_x-column];
			arr[temp_x-column]=temp;
			
			temp=arr[temp_x+1];
			arr[temp_x+1]=arr[temp_x-column+1];
			arr[temp_x-column+1]=temp;
			//Move number and number of boards increment and determines last move
			move_num++;
			num_board++;
			last_move='U';
			flag=1;
			//Comparison two array if equal return true;
			if(Arrays.equals(arr,temp_array))
				res=1;
			//bb place coordinate changing
			temp_x -= column;
		}
		
		if(flag == 1){
			//Result true and return 1
			if(res == 1)
				return true;
			//Result is false and will be restored
			temp=arr[temp_x];
			arr[temp_x]=arr[temp_x+column];
			arr[temp_x+column]=temp;
			
			temp=arr[temp_x+1];
			arr[temp_x+1]=arr[temp_x+column+1];
			arr[temp_x+column+1]=temp;
			//bb place coordinate changing
			temp_x += column;
			flag=0;
		}
		//For down
		/*If condition not go outside and not go wall('00')*/
		if(temp_x < ((row*column)-(column+1)) && (arr[temp_x+column] != '0' || arr[temp_x+column+1] != '0')){
			//Swap two elements
			temp=arr[temp_x];
			arr[temp_x]=arr[temp_x+column];
			arr[temp_x+column]=temp;
			
			temp=arr[temp_x+1];
			arr[temp_x+1]=arr[temp_x+column+1];
			arr[temp_x+column+1]=temp;
			//Move number and number of boards increment and determines last move
			move_num++;
			num_board++;
			last_move='D';
			flag=1;
			//Comparison two array if equal return true;
			if(Arrays.equals(arr,temp_array))
				res=1;
			//bb place coordinate changing
			temp_x += column;
		}
		
		if(flag == 1){
			//Result true and return 1
			if(res == 1)
				return true;
			//Result is false and will be restored
			temp=arr[temp_x];
			arr[temp_x]=arr[temp_x-column];
			arr[temp_x-column]=temp;
			
			temp=arr[temp_x+1];
			arr[temp_x+1]=arr[temp_x-column+1];
			arr[temp_x-column+1]=temp;
			//bb place coordinate changing
			temp_x -= column;
			flag=0;
		}
		//Final solution abstract board array and if board solution return true
		for(int k=0;k<(row*column);k++)
			abs_array[k]=temp_array[k];
		if(test(abs_array,arr))
			return true;

		//Find random number for shuffle move
		Random r=new Random();
		int random_num=r.nextInt(4);

		//According to random number then moving
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
		int i,count=1,counter=1,x=1;

		//Reset my array
		for(i=0;i<(row*column);i++){
			if(i == 0){
				arr[i]='0';
				arr[i+1]='0';
			}
			else {
				if(count < 10){
					arr[i]='0';
					arr[i+1]=(char)('0'+counter);
					counter++;
					count++;
				}
				else if(count >= 10 && count < 20){
					if(count == 10){
						counter=1;
						arr[i]='1';
						arr[i+1]='0';
						count++;
					}
					else{
						arr[i]='1';
						arr[i+1]=(char)('0'+counter);
						counter++;
						count++;
					}
				}
				else if(count >= 20 && count < 30){
					if(count == 20){
						counter=1;
						arr[i]='2';
						arr[i+1]='0';
						count++;
					}
					else{
						arr[i]='2';
						arr[i+1]=(char)('0'+counter);
						counter++;
						count++;
					}
				}
				else if(count >= 30 && count < 40){
					if(count == 30){
						counter=1;
						arr[i]='3';
						arr[i+1]='0';
						count++;
					}
					else{
						arr[i]='3';
						arr[i+1]=(char)('0'+counter);
						counter++;
						count++;
					}
				}
			}
			if(i != (column*x)){
				if(i != (column*x-2)){
					arr[i+2]=' ';
					i+=2;
				}
				else{
					i+=1;
					x+=1;
				}
			}
		}
		arr[row*column-1]='b';
		arr[row*column-2]='b';

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
		int c_counter=0;
		int count=0;

		Scanner input=new Scanner(System.in);
		//Ask user filename and taken filename to user
		System.out.println("Enter file name and save current board: ");
		String askingFile=input.nextLine();

		/*If it is same file I'm using*/
		if(askingFile == filename){
			FileWriter writer=new FileWriter(filename);
			for(int i=0;i<(row*column);i++){
				if(count != 2){
					writer.write(arr[i]);
					c_counter++;
					//Finish line newline
					if(c_counter == column){
						writer.write("\n");
						c_counter=0;
					}
				}
			}
			writer.close();
		}
		/*If it is the other file*/
		else{
			FileWriter writer=new FileWriter(askingFile);
			for(int i=0;i<(row*column);i++){
				if(count != 2){
					writer.write(arr[i]);
					c_counter++;
					//Finish line newline
					if(c_counter == column){
						writer.write("\n");
						c_counter=0;
					}
				}
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

	}
	/**
	*Printing string format
	*@return String
	*/
	public String toString(){
		int c_counter=0;
		int count=0;
		System.out.print("\n");
		for(int i=0;i<(row*column);i++){
			if(count != 2){
				System.out.printf("%c",arr[i]);
				c_counter++;
				if(c_counter == column){
					System.out.print("\n");
					c_counter=0;
				}
			}
		}
		System.out.print("\n");
		return null;
	}
	/**
	*Testing method to final solution and program ending
	*@param arr1 first comparison array
	*@param arr2 second comparison array
	*@return if find final solution true or false
	*/
	public static boolean test(char [] arr1,char [] arr2){
		//Comparison two array if equal return true;
		if(Arrays.equals(arr1,arr2))
			return true;
		return false;
	}
}
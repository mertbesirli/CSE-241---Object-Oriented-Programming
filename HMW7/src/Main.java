
import java.util.Scanner;
/**
*@author 1801042663 Mert Can Besirli
*/
/**
*This Main class, first asking user 1Darray or 2Darray choice
*then according to args.length setsize,reset,shuffle or readfromfile
*then according to operation, making process writetofile,readfromfile
*left move,right move,up move,down move,issolved,printreport,shuffle move,exit 
*@see Exception
*/

public class Main{
	public static void main(String[] args) throws Exception{
		BoardArray1D array1d = new BoardArray1D(0,0,0,0,'S',0);
		BoardArray2D array2d = new BoardArray2D(0,0,0,0,'S',0,0);


		int flag=0;
		char x;

		System.out.println("Enter choice 1DARRAY(A) and 2DARRAY(B): ");
		//Take user choice BoardArray1D and BoardArray2D	
		Scanner input=new Scanner(System.in);
		char answer=input.next().charAt(0);

		if(answer == 'A'){
			//Not enter one argument 
			//First setsize and then reset, shuffle
			if(args.length != 1){
				array1d.setSize();
				array1d.reset();
				array1d.find_space_place_1D();
				array1d.shuffle(50);
				array1d.find_space_place_1D();
			}
			//Enter one argument to txt file
			else{
				array1d.readFromFile(args[0]);
				System.out.printf("Open file: %s\n",args[0]);
			}
			//Printing array
			array1d.toString();
			while(true){
				System.out.print("Choice\n(V->isSolved)\n(T->PrintReport)\n(E->WriteToFile)\n(O->Readfromfile)\n");
				System.out.print("(L->Left move)\n(R->Right move\n(U->Up move)\n(D->Down move)\n(S->Shuffle move)\n(Q->exit): ");
				char choice=input.next().charAt(0);
				if(flag != 1){
					switch(choice){
						case 'V':
							array1d.find_space_place_1D();
							//Program solving and program ending
							if(array1d.isSolved())
								flag=1;
							array1d.find_space_place_1D();
							array1d.toString();
							break;
						case 'T':
							int b=array1d.numberOfBoards();
							int m=array1d.numberOfMoves();
							char l=array1d.lastMove();
							System.out.printf("\nNumber of boards: %d\nNumber of moves: %d\nLast move: %s\n",b,m,l);
							break;
						case 'E':
							array1d.writeToFile(args[0]);
							array1d.toString();
							break;
						case 'O':
							System.out.print("PLease enter load file: ");
							String line=input.nextLine();
							array1d.readFromFile(line);
							System.out.printf("Open file: %s\n",line);
							array1d.toString();
							break;
						case 'L':
							x='L';
							array1d.find_space_place_1D();
							array1d.move(x);
							array1d.toString();
							break;
						case 'R':
							x='R';
							array1d.find_space_place_1D();
							array1d.move(x);
							array1d.toString();
							break;
						case 'U':
							x='U';
							array1d.find_space_place_1D();
							array1d.move(x);
							array1d.toString();
							break;
						case 'D':
							x='D';
							array1d.find_space_place_1D();
							array1d.move(x);
							array1d.toString();
							break;
						case 'S':
							array1d.find_space_place_1D();
							array1d.shuffle(50);
							array1d.find_space_place_1D();
							array1d.toString();
							break;
						case 'Q':
							flag=1;
							break;
					}//end of switch
				}//end of flag
				/*For exit*/
				if(flag == 1)
					break;
			}//end of while
		}//end of if

		else if(answer == 'B'){
			//Not enter one argument 
			//First setsize and then reset, shuffle
			if(args.length != 1){
				array2d.setSize();
				array2d.reset();
				array2d.find_space_place_2D();
				array2d.shuffle(50);
				array2d.find_space_place_2D();
			}
			//Enter one argument
			else{
				array2d.readFromFile(args[0]);
				System.out.printf("Open file: %s\n",args[0]);
			}
			//Printing array 
			array2d.toString();
			while(true){
				System.out.print("Choice\n(V->isSolved)\n(T->PrintReport)\n(E->WriteToFile)\n(O->Readfromfile)\n");
				System.out.print("(L->Left move)\n(R->Right move\n(U->Up move)\n(D->Down move)\n(S->Shuffle move)\n(Q->exit): ");
				char choice=input.next().charAt(0);
				if(flag != 1){
					switch(choice){
						case 'V':
							array2d.find_space_place_2D();
							//Find solution program ending
							if(array2d.isSolved())
								flag=1;
							array2d.toString();
							break;
						case 'T':
							int b=array2d.numberOfBoards();
							int m=array2d.numberOfMoves();
							char l=array2d.lastMove();
							System.out.printf("\nNumber of boards: %d\nNumber of moves: %d\nLast move: %s\n\n",b,m,l);

							break;
						case 'E':
							array2d.writeToFile(args[0]);
							array2d.toString();
							break;
						case 'O':
							System.out.print("PLease enter load file: ");
							String line=input.nextLine();
							array2d.readFromFile(line);
							System.out.printf("Open file: %s\n",line);
							array2d.toString();
							break;
						case 'L':
							x='L';
							array2d.find_space_place_2D();
							array2d.move(x);
							array2d.toString();
							break;
						case 'R':
							x='R';
							array2d.find_space_place_2D();
							array2d.move(x);
							array2d.toString();
							break;
						case 'U':
							x='U';
							array2d.find_space_place_2D();
							array2d.move(x);
							array2d.toString();
							break;
						case 'D':
							x='D';
							array2d.find_space_place_2D();
							array2d.move(x);
							array2d.toString();
							break;
						case 'S':
							array2d.find_space_place_2D();
							array2d.shuffle(50);
							array2d.find_space_place_2D();
							array2d.toString();
							break;
						case 'Q':
							flag=1;
							break;
					}//end of switch
				}//end of flag
				/*For exit*/
				if(flag == 1)
					break;
			}//End of while
		}//End of else if
	}
	
}
import java.util.Scanner;
import java.util.Arrays;
import java.util.Iterator;

/**
*@author 1801042663 Mert Can Beşirli
*/

/**
*This Main class
*First define GTUSet and GTUVector and
*Ask user choice Vector or Set class
*Then asking chooice integer or double
*Then insert and then asking menu option
*Making choose according to operation
*/

public class Main{

	public static void main(String[] args) {

		GTUSet<Integer> s1=new GTUSet<Integer>(0,0);
		GTUSet<Double> s2=new GTUSet<Double>(0,0);
		GTUVector<Double> v2=new GTUVector<Double>(0,0);
		GTUVector<Integer> v1=new GTUVector<Integer>(0,0);

		char answer,choice;
		int flag=0,ret,
			erase_index;
		Object contain_num;
		int index=0;
		int numbers;
		double number;

		System.out.println("Enter choice Vector(V),Set(S): ");
		Scanner input=new Scanner(System.in);

		answer=input.next().charAt(0);

		//For vector
		if(answer == 'V'){
			System.out.println("Enter choice Integer(N),Double(D): ");
			choice=input.next().charAt(0);
			if(choice == 'D'){	
				//Taken number from user
				System.out.println("Enter of double numbers until negative number: ");
				number=input.nextDouble();
				v2.insert(number);
				//For double
				index=1;
				while(number >= 0.0){
					number=input.nextDouble();
					if(number >= 0.0)
						v2.insert(number);
					/*else
						throw new IllegalArgumentException(Integer.toString(numbers));*/
				}
				v2.display(index);
			}
			else if(choice == 'N'){
				//Taken number from user
				System.out.println("Enter of integer numbers until negative number: ");
				numbers=input.nextInt();
				v1.insert(numbers);
				//For double
				index=0;
				while(numbers >= 0){
					numbers=input.nextInt();
					if(numbers >= 0)
						v1.insert(numbers);
					/*else
						throw new IllegalArgumentException(Integer.toString(numbers));*/
				}
				v1.display(index);
			}

			while(true){
				System.out.print("Empty(E)\nSize(Z)\nMaxSize(M)\nErase(R)\nClear(C)\nIterator(T)\nContains(O)\nQuit(Q)\nChoice: ");
				choice=input.next().charAt(0);
				if(flag != 1){
					switch(choice){
						case 'E':
							if(index == 1){
								if(v2.empty())
									System.out.println("\nArray is empty\n");
								else
									System.out.println("\nArray is NOT empty\n");
							}
							else{
								if(v1.empty())
									System.out.println("\nArray is empty\n");
								else
									System.out.println("\nArray is NOT empty\n");
							}
							break;
						case 'Z':
							if(index == 1)
								System.out.printf("\nSize: %d\n",v2.size());
							else
								System.out.printf("\nSize: %d\n",v1.size());
							break;
						case 'M':
							if(index == 1)
								System.out.printf("\nMax size: %d\n",v2.max_size());
							else
								System.out.printf("\nMax size: %d\n",v1.max_size());
							break;
						case 'R':
							if(index == 1){
								System.out.println("Enter index of an array: ");
								erase_index=input.nextInt();
								v2.erase(erase_index);
								v2.display(index);
							}
							else{
								System.out.println("Enter index of an array: ");
								erase_index=input.nextInt();
								v1.erase(erase_index);
								v1.display(index);
							}
							break;
						case 'C':
							if(index == 1)
								v2.clear();
							else
								v1.clear();
							System.out.print("\nClear all elements\n");
							break;
						case 'T':
							if(index == 1)
								System.out.printf("\nBeginning number: %.1f\n",v2.iterator());
							else
								System.out.printf("\nBeginning number: %d\n",v1.iterator());
							break;
						case 'O':
							System.out.println("Enter contains number: ");
							if(index == 0){
								contain_num=input.nextInt();
								if(v1.contains(contain_num))
									System.out.println("\nIt is contains\n");
								else
									System.out.println("\nIt is not contains\n");
							}
							else{
								contain_num=input.nextDouble();
								if(v2.contains(contain_num))
									System.out.println("\nIt is contains\n");
								else
									System.out.println("\nIt is not contains\n");
							}
							break;
						case 'Q':
							flag=1;
							break;
					}//End of switch

				}//End of if
				if(flag == 1)
					break;
			}//End of while
		}//End of if

		//For set
		if(answer == 'S'){
			System.out.println("Enter choice Integer(N),Double(D): ");
			choice=input.next().charAt(0);
			if(choice == 'D'){
				//Taken number from user
				System.out.println("Enter of double numbers until negative number: ");
				number=input.nextDouble();
				s2.insert(number);
				//For double
				index=1;
				while(number >= 0.0){
					number=input.nextDouble();
					if(number >= 0.0){
						ret=s2.insert(number);
						if(ret == -1)
							//Taken number from user
							System.out.println("Enter of different numbers because it is set: ");
					}	
				/*	else
						throw new IllegalArgumentException(Integer.toString(numbers));*/
				}
				s2.sorting(index);
				s2.display(index);
			}
			else if(choice == 'N'){
				//Taken number from user
				System.out.println("Enter of numbers until negative number: ");
				numbers=input.nextInt();
				s1.insert(numbers);
				//For integer
				index=0;
				while(numbers >= 0){
					numbers=input.nextInt();
					if(numbers >= 0){
						ret=s1.insert(numbers);
						if(ret == -1)
							//Taken number from user
							System.out.println("Enter of different numbers because it is set: ");
					}
				/*	else
						throw new IllegalArgumentException(Integer.toString(numbers));*/
				}
				s1.sorting(index);
				s1.display(index);
			}

			while(true){
				System.out.print("Empty(E)\nSize(Z)\nMaxSize(M)\nErase(R)\nClear(C)\nIterator(T)\nContains(O)\nQuit(Q)\nChoice: ");
				choice=input.next().charAt(0);
				if(flag != 1){
					switch(choice){
						case 'E':
							if(index == 0){
								if(s1.empty())
									System.out.println("\nArray is empty\n");
								else
									System.out.println("\nArray is NOT empty\n");
							}
							else{
								if(s2.empty())
									System.out.println("\nArray is empty\n");
								else
									System.out.println("\nArray is NOT empty\n");
							}
							break;
						case 'Z':
							if(index == 0)
								System.out.printf("\nSize: %d\n",s1.size());
							else
								System.out.printf("\nSize: %d\n",s2.size());
							break;
						case 'M':
							if(index == 0)
								System.out.printf("\nMax size: %d\n",s1.max_size());
							else
								System.out.printf("\nMax size: %d\n",s2.max_size());
							break;
						case 'R':
							System.out.println("Enter index of an array: ");
							erase_index=input.nextInt();
							if(index == 0){
								s1.erase(erase_index);
								s1.display(index);
							}
							else{
								s2.erase(erase_index);
								s2.display(index);
							}
							break;
						case 'C':
							if(index == 0)
								s1.clear();
							else
								s2.clear();
							System.out.print("\nClear all elements\n");
							break;
						case 'T':
							if(index == 0)
								System.out.printf("\nBeginning number: %d\n\n",s1.iterator());
							else
								System.out.printf("\nBeginning number: %.1f\n\n",s2.iterator());
							break;
						case 'O':
							System.out.println("Enter contains number: ");
							if(index == 0){
								contain_num=input.nextInt();
								if(s1.contains(contain_num))
									System.out.println("\nIt is contains\n");
								else
									System.out.println("\nIt is not contains\n");
							}
							else{
								contain_num=input.nextDouble();
								if(s2.contains(contain_num))
									System.out.println("\nIt is contains\n");
								else
									System.out.println("\nIt is not contains\n");	
							}
							break;
						case 'Q':
							flag=1;
							break;
					}//End of switch
				}//End of if
				if(flag == 1)
					break;
			}//End of while
		}//End of if
	}
}
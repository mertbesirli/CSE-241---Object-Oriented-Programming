
import java.util.Arrays;
import java.util.Iterator;
import java.util.*;

/**
*GTUVector Class makes insert,size,max size,erase,
*clear,test empty,iterator begining,containing
*@param integer vector count actually array size
*@param Object vec array, keep data
*/

public class GTUVector<T> extends GTUContainer<T>{
	protected int vec_count;
	private Object vec[];

	/**
	*Constructor
	*/
	public GTUVector(int d,int v){
		super(d);
		this.vec_count=v;
		vec=new Object[200];
	}
	/**
	*Set vec count
	*/
	public void setNum(int v){
		vec_count=v;
	}
	/**
	*Get vec count
	*/
	public int getNum(){
		return vec_count;
	}
	/**
	*This method insert elements to my array 
	*@param num is int added element
	*@return int 
	*/
	public int insert(T num){
		vec[vec_count]=num;
		vec_count++;
		return 1;
	}
	/**
	*This method find size
	*@return int size
	*/
	public int size(){
		return vec_count;
	}
	/**
	*This method find max size
	*@return int max size
	*/
	public int max_size(){
		return vec.length;
	}
	/**
	*This method erase element according to index
	*@param index, erase element's index
	*int vec_count, array size 
	*/
	public void erase(int index){
		if(index > vec_count)
			System.out.println("Index have not this array");
		else{
			for(int i=index;i<(vec_count-1);i++){
				vec[i]=vec[i+1];
			}
			vec_count--;
		}	
	}
	/**
	*This method clear array
	*/
	public void clear(){
		vec=new Object[0];
		vec_count=0;
	}
	/**
	*This method checking empty or not to array
	*@return boolean true or false
	*/
	public boolean empty(){
		if(vec_count <= 0)
			return true;
		else
			return false;
	}
	/**
	*This method iterator beginning
	*@return beginning element
	*/
	public Object iterator(){
		return vec[0];
	}
	/**
	*This method elements check have or not 
	*@return boolean false or true
	*i counting variable 
	*@param o Object paramaters
	*/
	public boolean contains(Object o){
		if(vec == null)
			return false;
		int i=0;
		while(i < vec_count){
			if(vec[i] == o)
				return true;
			i++;
		}
		return false;
	}
	/**
	*This method display array
	*/
	public void display(int index){
		if(index == 1){
			for(int i=0;i<vec_count;i++)
				System.out.printf("%.1f ",vec[i]);
		}
		else{
			for(int i=0;i<vec_count;i++)
				System.out.printf("%d ",vec[i]);
		}
		System.out.println();
	}
	public boolean hasNext(){
		return true;
	}
	public Object next(){
		return 1;
	}
}

import java.util.Arrays;

/**
*Abstract clas GTUContainer
*@param Integer data
*@param Abstract Object class array 
*
*
*/
public abstract class GTUContainer<T> {
	private int data;
	private Object [] arr;

	/**
	*This method is constructor
	*/
	public GTUContainer(int d){
		this.data=d;
		arr=new Object[200];
	}
	/**
	*This method Integer data set
	*/
	public void setData(int d){
		data=d;
	}
	/**
	*@return int, get method
	*/
	public int getData(){
		return data;
	}

	public abstract boolean empty();
	public abstract int size();
	public abstract int max_size();
	public abstract int insert(T num);
	public abstract void erase(int index);
	public abstract void clear();
	public abstract Object iterator();
	public abstract boolean contains(Object o);
	public abstract void display(int index);

}

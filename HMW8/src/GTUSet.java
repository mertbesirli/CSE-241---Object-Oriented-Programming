
/**
*GTUSet Class makes insert,size,max size,erase,
*clear,test empty,iterator begining,containing
*@param integer set num actually array size
*@param Object sets array, keep data
*/

public class GTUSet<T> extends GTUContainer<T>{
	protected int set_num;
	private Object sets[];

	/**
	*Constructor
	*/
	public GTUSet(int d,int s){
		super(d);
		this.set_num=s;
		sets=new Object[200];
	}
	/**
	*Set set number
	*/
	public void setSetNum(int s){
		set_num=s;
	}
	/**
	*Get set number
	*/
	public int getSetNum(){
		return set_num;
	}
	/**
	*This method insert elements to my array 
	*@return int, if same inserting number return -1, or return 1
	*/
	public int insert(T num){
	//	sets=new Object[set_num+1];
		for(int i=0;i<set_num;i++){
			if(sets[i] == num)
				return -1;
		}
		sets[set_num]=num;
		set_num++;
		return 1;
	}
	/**
	*This method find size
	*@return int size
	*/
	public int size(){
		return set_num;
	}
	/**
	*This method find max size
	*@return int max size
	*/
	public int max_size(){
		return sets.length;
	}
	/**
	*This method erase element according to index
	*@param  index erase element's index
	*/
	public void erase(int index){
		if(index > set_num)
			System.out.println("Index have not this array");
		else{
			for(int i=index;i<(set_num-1);i++){
				sets[i]=sets[i+1];
			}
			set_num--;
		}	
	}
	/**
	*This method clear array
	*set_num is zero
	*/
	public void clear(){
		sets=new Object[0];
		set_num=0;
	}
	/**
	*This method checking empty or not to array
	*@return boolean true or false
	*/
	public boolean empty(){
		if(set_num <= 0)
			return true;
		else
			return false;
		
	}
	/**
	*This method iterator beginning
	*@return beginning element
	*/
	public Object iterator(){
		return sets[0];
	}
	/**
	*This method sorting after insert array
	*temp, keep number then swapping
	*/
	public void sorting(int index){
		Object temp;
		if(index == 0){
			for(int i=0;i<(set_num-1);i++){
				for(int j=0;j<(set_num-i-1);j++){
					if((int)sets[j] > (int)sets[j+1]){
						temp=sets[j];
						sets[j]=sets[j+1];
						sets[j+1]=temp;
					}
				}
			}
		}
		else{
			for(int i=0;i<(set_num-1);i++){
				for(int j=0;j<(set_num-i-1);j++){
					if((double)sets[j] > (double)sets[j+1]){
						temp=sets[j];
						sets[j]=sets[j+1];
						sets[j+1]=temp;
					}
				}
			}
		}
	}
	/**
	*This method display array
	*
	*/
	public void display(int index){
		if(index == 1){
			for(int i=0;i<set_num;i++)
				System.out.printf("%.1f ",sets[i]);
		}
		else{
			for(int i=0;i<set_num;i++)
				System.out.printf("%d ",sets[i]);
		}
		System.out.println();
	}
	/**
	*This method elements check have or not 
	*@return boolean false or true
	*@param o , Object type
	*/
	public boolean contains(Object o){
		if(sets == null)
			return false;
		int i=0;
		while(i < set_num){
			if(sets[i] == o)
				return true;
			i++;
		}
		return false;		
	}
	public boolean hasNext(){
		return true;
	}
	public Object next(){
		return 1;
	}


}
/**
*AbstractBoard abstract class 
*It's contain abstract method:
*toString,readFromFile,writeToFie,reset,setSize,move
*cell,isSolved,equals,numberOfBoards,lastMove,numberOfMoves,shuffle
*/

public abstract class AbstractBoard{

	protected int row;
	protected int column;
	protected int move_num=0;
	protected int num_board=0;
	protected char last_move='S';
	protected char [] abs_array;

	/**
	*Constructor
	*/
	public AbstractBoard(int therow,int thecolumn,int themove_num,int thenum_board,char thelast_move){
		setRow(therow);
		setColumn(thecolumn);
		setMoveNum(themove_num);
		setNumBoard(thenum_board);
		setLastMove(thelast_move);
		abs_array=new char[300];
	}
	/**
	*@param therow int
	*/
	public void setRow(int therow){
		row=therow;
	}
	/**
	*@return int row
	*/
	public int getRow(){
		return row;
	}
	/**
	*@param thecolumn int
	*/
	public void setColumn(int thecolumn){
		column=thecolumn;
	}
	/**
	*@return int column
	*/
	public int getColumn(){
		return column;
	}
	/**
	*@param themove_num int
	*/
	public void setMoveNum(int themove_num){
		move_num=themove_num;
	}
	/**
	*@return int move_num
	*/
	public int getMoveNum(){
		return move_num;
	}
	/**
	*@param thenum_board int
	*/
	public void setNumBoard(int thenum_board){
		num_board=thenum_board;
	}
	/**
	*@return int move_num
	*/
	public int getNumBoard(){
		return move_num;
	}
	/**
	*@param thelast_move
	*/
	public void setLastMove(char thelast_move){
		last_move=thelast_move;
	}
	/**
	*@return char last_move
	*/
	public char getLastMove(){
		return last_move;
	}

	public abstract String toString();
	/**
	*@see Exception
	*/
	public abstract void readFromFile(String filename)throws Exception; 
	/**
	*@see Exception
	*/ 
	public abstract void writeToFile(String filename)throws Exception;
	public abstract void reset();
	public abstract void setSize();
	public abstract void move(char x);
	public abstract char cell(int s1,int s2);
	public abstract boolean isSolved();
	public abstract boolean equals(Object [] a,Object [] b);
	public abstract int numberOfBoards();
	public abstract char lastMove();
	public abstract int numberOfMoves();
	public abstract void shuffle(int num);
}
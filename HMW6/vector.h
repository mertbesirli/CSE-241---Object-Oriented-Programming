#ifndef VECTOR_H
#define VECTOR_H


namespace Container{
	template<class T>
	class GTUVector: public GTUContainer<T>{
	public:
		GTUVector();
		GTUVector(T thenum,shared_ptr<GTUVector<T>> nextPtr);
		~GTUVector();
		T getVecNum()const;
		shared_ptr<GTUVector<T>> getNext();
		void setNextVec(shared_ptr<GTUVector<T>> nextPtr);
		T size(vector<T>str,set<T>s1);
		T empty(vector<T>str,set<T>s1);
		T max_size(vector<T> str,set<T> s1);
		T begin(vector<T> str,set<T> s1);
		T end(vector<T> str,set<T> s1);
		void clear(vector<T> str,set<T> s1);
		void erase(vector<T> str,set<T> s1);
		void insert(vector<T> &str,set<T> &s1);
		T &operator [](int index);
	private:
		shared_ptr<GTUVector<T>> vec;
		T vec_num;
	};
}
#endif
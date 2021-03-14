#ifndef SET_H
#define SET_H


using std::shared_ptr;
using std::vector;
using std::set;

namespace Container{
	template<class T>
	class GTUSet: public GTUContainer<T>{
	public:
		GTUSet();
		GTUSet(T thenum,shared_ptr<GTUSet<T>> nextP);
		~GTUSet();
		T getSetNum()const;
		shared_ptr<GTUSet<T>> getNext();
		void setNextSet(shared_ptr<GTUSet<T>> nextPtr);
		T size(vector<T>str,set<T>s1);
		T empty(vector<T>str,set<T>s1);
		T max_size(vector<T> str,set<T> s1);
		T begin(vector<T> str,set<T> s1);
		T end(vector<T> str,set<T> s1);
		void clear(vector<T> str,set<T> s1);
		void erase(vector<T> str,set<T> s1);
		void insert(vector<T> &str,set<T> &s1);

	private:
		shared_ptr<GTUSet<T>> set_t;
		T set_num;
	};
}
#endif

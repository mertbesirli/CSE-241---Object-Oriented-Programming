#ifndef CONTAINER_H
#define CONTAINER_H

#include <memory>
#include <vector>
#include <set>

using std::shared_ptr;
using std::vector;
using std::set;


namespace Container{
	template<class T>
	class GTUContainer{
	public:
		GTUContainer();
		GTUContainer(shared_ptr<GTUContainer<T>> nextPtr);
		~GTUContainer();
		shared_ptr<GTUContainer<T>> getNext();
		void setNext(shared_ptr<GTUContainer<T>> nextPtr);
		virtual T size(vector<T>str,set<T>s1)=0;
		virtual T empty(vector<T>str,set<T>s1)=0;
		virtual T max_size(vector<T> str,set<T> s1)=0;
		virtual T begin(vector<T> str,set<T> s1)=0;
		virtual T end(vector<T> str,set<T> s1)=0;
		virtual void clear(vector<T> str,set<T> s1)=0;
		virtual void erase(vector<T> str,set<T> s1)=0;
		virtual void insert(vector<T> &str,set<T> &s1)=0;
	private:
		shared_ptr<GTUContainer<T>> next;
	};
}

#endif
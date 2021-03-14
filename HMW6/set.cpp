#include <iostream>
#include <memory>
#include "container.h"
#include "set.h"
#include "vector.h"

using std::cout;
using std::endl;
using std::shared_ptr;
using std::cin;


namespace Container{
	template<class T>
	GTUSet<T>::GTUSet():GTUContainer<T>(),set_num(0),set_t(nullptr){
		//Empty
	}
	template<class T>
	GTUSet<T>::GTUSet(T thenum,shared_ptr<GTUSet<T>> nextP):set_num(thenum),set_t(nextP){
		//Empty
	}
	template<class T>
	T GTUSet<T>::getSetNum()const{
		return set_num;
	}
	template<class T>
	shared_ptr<GTUSet<T>> GTUSet<T>::getNext(){
		return set_t;
	}
	template<class T>
	void GTUSet<T>::setNextSet(shared_ptr<GTUSet<T>> nextPtr){
		set_t=nextPtr;
	}
	template<class T>
	GTUSet<T>::~GTUSet(){
		cout<<"Deleting "<<set_num<<endl;
	}
	template<class T>
	T GTUSet<T>::size(vector<T>str,set<T>s1){
		return s1.size();
	}
	template<class T>
	T GTUSet<T>::empty(vector<T>str,set<T>s1){
		if(s1.empty())
			return 1;
		else
			return 0;
	}
	template<class T>
	T GTUSet<T>::max_size(vector<T> str,set<T> s1){
		return s1.max_size();
	}
	template<class T>
	T GTUSet<T>::begin(vector<T> str,set<T> s1){
		set<int>::iterator it=s1.begin();
		return *it;
	}
	template<class T>
	T GTUSet<T>::end(vector<T> str,set<T> s1){
		set<int>::iterator p=s1.end();
		//In the end I had to do this because nullptr was
		p--;
		return *p;
	}
	template<class T>
	void GTUSet<T>::clear(vector<T> str,set<T> s1){
		s1.clear();
		cout<<"Clear set"<<endl;
	}
	template<class T>
	void GTUSet<T>::erase(vector<T> str,set<T> s1){
		set<int>::iterator it1=s1.begin();
		s1.erase(it1);
	}
	template<class T>
	void GTUSet<T>::insert(vector<T> &str,set<T> &s1){
		while(set_t != nullptr){
			s1.insert(set_t->getSetNum());
			set_t=set_t->getNext();
		}
		cout<<"Set numbers: ";
		for(auto it=s1.begin();it != s1.end();it++)
			cout<<" "<<*it;
		cout<<endl;
	}
}
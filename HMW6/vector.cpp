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
	GTUVector<T>::GTUVector():GTUContainer<T>(),vec_num(0),vec(nullptr){
		//Empty
	}
	template<class T>
	GTUVector<T>::GTUVector(T thenum,shared_ptr<GTUVector<T>> nextPtr):vec_num(thenum),vec(nextPtr){
		//Empty
	}
	template<class T>
	T GTUVector<T>::getVecNum()const{
		return vec_num;
	}
	template<class T>
	shared_ptr<GTUVector<T>> GTUVector<T>::getNext(){
		return vec;
	}
	template<class T>
	void GTUVector<T>::setNextVec(shared_ptr<GTUVector<T>> nextPtr){
		vec=nextPtr;
	}
	template<class T>
	GTUVector<T>::~GTUVector(){
		cout<<"Deleting "<<vec_num<<endl;
	}
	template<class T>
	T GTUVector<T>::size(vector<T>str,set<T>s1){
		return str.size();
	}
	template<class T>
	T GTUVector<T>::empty(vector<T>str,set<T>s1){
		if(str.empty())
			return 1;
		else
			return 0;
	}
	template<class T>
	T GTUVector<T>::max_size(vector<T> str,set<T> s1){
		return str.max_size();
	}
	template<class T>
	T GTUVector<T>::begin(vector<T> str,set<T> s1){
		vector<int>::iterator p=str.begin();
		return *p;
	}
	template<class T>
	T GTUVector<T>::end(vector<T> str,set<T> s1){
		vector<int>::iterator p=str.end();
		//In the end I had to do this because nullptr was
		p--;
		return *p;
	}
	template<class T>
	void GTUVector<T>::clear(vector<T> str,set<T> s1){
		str.clear();
		cout<<"Clear vector"<<endl;
	}
	template<class T>
	void GTUVector<T>::erase(vector<T> str,set<T> s1){
		vector<int>::iterator it1=str.begin();
		str.erase(it1);
	}
	template<class T>
	void GTUVector<T>::insert(vector<T> &str,set<T> &s1){
		/*Push back in vector elements*/
		while(vec != nullptr){
			str.push_back(vec->getVecNum());
			vec=vec->getNext();
		}
	}
	template<class T>
	T &GTUVector<T>::operator [](int index){
		return vec[index];
	}
}
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
	GTUContainer<T>::GTUContainer():next(nullptr){
		//Empty
	}
	template<class T>
	GTUContainer<T>::GTUContainer(shared_ptr<GTUContainer<T>> nextPtr):next(nextPtr){
		//Empty
	}
	template<class T>
	shared_ptr<GTUContainer<T>> GTUContainer<T>::getNext(){
		return next;
	}
	template<class T>
	void GTUContainer<T>::setNext(shared_ptr<GTUContainer<T>> nextPtr){
		next=nextPtr;
	}
	template<class T>
	GTUContainer<T>::~GTUContainer(){
		//Empty
	}
}
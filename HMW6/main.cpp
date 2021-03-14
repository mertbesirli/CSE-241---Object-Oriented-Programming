#include <iostream>
#include <vector>
#include <set>
#include <algorithm>



#include "container.h"
#include "set.h"
#include "vector.h"
#include "container.cpp"
#include "vector.cpp"
#include "set.cpp"

using Container::GTUContainer;
using Container::GTUSet;
using Container::GTUVector;

bool isEven(int x){
	return ((x%2) == 0);
}
void func(int i){
	cout<<"*"<<i<<"*"<<endl;
}


int main(int argc, char const *argv[])
{
	int number_of_ptr=0;
	int res,	
		flag=0;	//For loop exit
	char choice; //For switch choices
	vector<int>v;
	set<int>s;

	//For GTUVector
	//Enter numbers for vector shared_ptr 
	cout<<"Enter number or numbers until negative for vector: "<<endl;
	cin>>number_of_ptr;
	//Taken first number
	shared_ptr<GTUVector<int>> vec(new GTUVector<int>(number_of_ptr,nullptr));
	//For vector temporary
	shared_ptr<GTUVector<int>> temp_vec_ptr;
	//Keeping memory place
	temp_vec_ptr=vec;

	//Until negative enter numbers
	while(number_of_ptr >= 0){
		cin>>number_of_ptr;
		//If number_of_ptr less than zero, loop ending
		if(number_of_ptr < 0)
			break;
		shared_ptr<GTUVector<int>> temp_vec_ptr(new GTUVector<int>(number_of_ptr,nullptr));
		vec->setNextVec(temp_vec_ptr);
		vec=vec->getNext();
	}
	//Return begin, temp_vec_ptr keep begin memory place for vec
	vec=temp_vec_ptr;

	//For GTUSet
	//Enter numbers for vector shared_ptr 
	cout<<"Enter number or numbers until negative for set: "<<endl;
	cin>>number_of_ptr;
	//Taken first number
	shared_ptr<GTUSet<int>> set_t(new GTUSet<int>(number_of_ptr,nullptr));
	//For vector temporary
	shared_ptr<GTUSet<int>> temp_set_ptr;
	//Keeping memory place
	temp_set_ptr=set_t;

	//Until negative enter numbers
	while(number_of_ptr >= 0){
		cin>>number_of_ptr;
		//If number_of_ptr less than zero, loop ending
		if(number_of_ptr < 0)
			break;
		shared_ptr<GTUSet<int>> temp_set_ptr(new GTUSet<int>(number_of_ptr,nullptr));
		set_t->setNextSet(temp_set_ptr);
		set_t=set_t->getNext();
	}
	//Return begin, temp_vec_ptr keep begin memory place for vec
	set_t=temp_set_ptr;


	shared_ptr<GTUVector<int>> temp;
	shared_ptr<GTUSet<int>> set_temp;
	temp=vec;

	

	//Const iterator
	vector<int>::const_iterator iter;
	temp=vec;
	/*Push back in vector elements*/
	while(temp != nullptr){
		v.push_back(temp->getVecNum());
		temp=temp->getNext();
	}
	cout<<"Vector numbers: ";
	for(iter=v.begin();iter != v.end();iter++)
		cout<<" "<<*iter;
	cout<<endl;
	//Insert in set elements
	set_temp=set_t;
	while(set_temp != nullptr){
		s.insert(set_temp->getSetNum());
		set_temp=set_temp->getNext();
	}
	cout<<"Set numbers: ";
	for(auto it=s.begin();it != s.end();it++)
		cout<<" "<<*it;
	cout<<endl<<endl;

	//Iterator
	auto p=v.begin();
	auto s1=s.begin();


	//Find global function for vector
	p=find(v.begin(),v.end(),30);
	if(p != v.end())
		cout<<"Element find in vector: "<<*p<<endl;
	else
		cout<<"Element not find in vector"<<endl;
	cout<<endl;
	//Return back begin
	p=v.begin();

	//Find_if global function for vector
	p=find_if(v.begin(),v.end(),isEven);
	cout<<"Vector first even value: "<<*p<<endl<<endl;

	p=v.begin();
	//For_each global function for vector
	cout<<"For each vector"<<endl;
	for_each(v.begin(),v.end(),func);
	cout<<endl;

	//Find global function for set
	auto srt=s.find(15);
	if(srt != s.end())
		cout<<"Element find in set: "<<*srt<<endl;
	else
		cout<<"Element not find in set"<<endl;
	cout<<endl;
	//Return back begin
	s1=s.begin();
	//Find_if global function for set
	s1=find_if(s.begin(),s.end(),isEven);
	cout<<"Set first even value: "<<*s1<<endl<<endl;
	s1=s.begin();
	//For_each global function for set
	cout<<"For each set"<<endl;
	for_each(s.begin(),s.end(),func);
	cout<<endl;



	while(1){
		cout<<"Give result both of vector and set"<<endl;
		cout<<"Empty(E)"<<endl;
		cout<<"Size(S)"<<endl;
		cout<<"Max Size(M)"<<endl;
		cout<<"Erase(R)"<<endl;
		cout<<"Clear(C)"<<endl;
		cout<<"Begin element(B)"<<endl;
		cout<<"End element(A)"<<endl;
		cout<<"Increment++(I)"<<endl;
		cout<<"Decrement--(D)"<<endl;
		cout<<"Exit(Q)"<<endl;
		cout<<"Enter press choice : ";
		cin>>choice;
		if(flag != 1){
			switch(choice){
				case 'E':
					//Checking empty or not for vector
					res=vec->empty(v,s);
					if(res == 1)
						cout<<"Empty vector"<<endl;
					else
						cout<<"Not Empty vector"<<endl;
					cout<<endl;
					//Checking empty or not for set
					res=set_t->empty(v,s);
					if(res == 1)
						cout<<"Empty set"<<endl;
					else
						cout<<"Not Empty set"<<endl;
					break;
				case 'S':
					//Finding size for vector
					res=vec->size(v,s);
					cout<<"Vector size: "<<res<<endl<<endl;
					//Finding size for set
					res=set_t->size(v,s);
					cout<<"Set size: "<<res<<endl<<endl;
					break;
				case 'M':
					//Finding max_size for vector
					res=vec->max_size(v,s);
					cout<<"Max Size: "<<res<<endl<<endl;
					//Finding max_size for set
					res=set_t->max_size(v,s);
					cout<<"Max size: "<<res<<endl<<endl;
					break;
				case 'R':
					//Erase function for vector
					vec->erase(v,s);
					//Erase function for set
					set_t->erase(v,s);
					cout<<endl;
					break;
				case 'C':
					//Clear function for vector
					vec->clear(v,s);
					//Clear function for set
					set_t->clear(v,s);
					cout<<endl;
					break;
				case 'B':
					//Begin returning vector
					res=vec->begin(v,s);
					cout<<"Begin vector:"<<res<<endl;
					//Begin returning set
					res=set_t->begin(v,s);
					cout<<"Begin set: "<<res<<endl;
					break;
				case 'A':
					//End returning vector
					res=vec->end(v,s);
					cout<<"End: "<<res<<endl;
					//End returning set
					res=set_t->end(v,s);
					cout<<"End: "<<res<<endl;
					break;
				//Increment	
				case 'I':
					//Now number for vector
					cout<<"Now number for vector: "<<*p<<endl;
					//Increment number for vector
					p++;
					cout<<"Increment number for vector: "<<*p<<endl<<endl;
					//Now number for set
					cout<<"Now number for set: "<<*s1<<endl;
					//Increment number for set
					s1++;
					cout<<"Increment number for set: "<<*s1<<endl<<endl;;
					break;
				case 'D':
					//Now number for vector
					cout<<"Now number for vector: "<<*p<<endl;
					//Decrease number for vector
					p--;
					cout<<*"Decrement number of vector: "<<*p<<endl<<endl;;
					//Now number for set
					cout<<"Now number for set: "<<*s1<<endl;
					//Decrease number for set
					s1--;
					cout<<"Decreasing number for set: "<<*s1<<endl<<endl;;
					break;
				case 'Q':
					flag=1;
					break;
			}//switch
		}//flag
		if(flag == 1)
			break;
	}//while

	return 0;
}
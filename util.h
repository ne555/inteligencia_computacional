#ifndef UTIL_H
#define UTIL_H

#include <sstream>
#include <string>
#include <cstdlib>
#include <iterator>
#include <algorithm>
#include <cmath>

#include <iostream>
template<class T>
static void printv(const T &v){
	for(size_t K=0; K<v.size(); ++K)
		std::cerr << v[K] << ' ';
	std::cerr << std::endl;
}

namespace math{
	inline int sign(float r){
		return (r<0)? -1: 1;
	}
	
	template<class T>
	inline T sigmoid(T v){
		return 2/(1+exp(-v)) - 1;
	}
}

template<class T>
T convert(const std::string &s){
	T value;
	std::stringstream ss(s);
	ss >> value;
	return value;
}

template<class Iter>
void print(Iter beg, Iter end, std::ostream &out){
	std::copy(
		beg,
		end,
		std::ostream_iterator
			<typename std::iterator_traits<Iter>::value_type>
			(out, " ")
	);
	//out << std::endl;
}

template<class T>
struct randomize{
	typedef T value_type;
	randomize(value_type lower, value_type upper):lower(lower), upper(upper){}
	inline value_type operator()(){
		value_type result = rand()/value_type(RAND_MAX);
		return result*(upper-lower) + lower;
	}
	value_type lower, upper;
};

template<>
inline int randomize<int>::operator()(){
	return rand()%(upper-lower+1) + lower;
}

template<class T>
inline bool between(T inic, T mid, T end){
	return inic < mid and mid < end;
}

#endif

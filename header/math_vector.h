#ifndef MATH_VECTOR
#define MATH_VECTOR

#include <valarray>

namespace math{
	#if 0
	template<class T>
	struct vector{
		typedef std::valarray<T> type;
	}
	#endif

	template<class T>
	inline typename T::value_type dot(const T &a, const T&b){
		if(a.size() != b.size()) throw "math_vector::dot";
		return (a*b).sum();
	}

	template<class T>
	inline typename T::value_type norm2(const T &v){
		return dot(v,v);
	}

	template<class T>
	inline typename T::value_type norm1(const T &v){
		return abs(v).sum();
	}

	template<class T>
	inline typename T::value_type norm_inf(const T &v){
		return abs(v).max();
	}

	template<class T>
	void assign(std::valarray<T> &lvalue, const std::valarray<T> &rvalue){
		if( &lvalue == &rvalue ) return;
		lvalue.resize( rvalue.size() );
		lvalue = rvalue;
	}
}

#endif


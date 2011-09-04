#ifndef MATH_VECTOR
#define MATH_VECTOR

#include <valarray>
#include <iostream>

namespace math{
	template <typename T>
	class vector: public std::valarray<T>{
		typedef std::valarray<T> valarray;
	public:
		typedef typename vector<T>::value_type value_type;
	//constructor forwarding
		vector(): valarray(){}
		explicit vector(size_t n): valarray(n){}
		vector(const T &val, size_t n): valarray(val,n){}
		vector(const T *p, size_t n): valarray(p, n){}
		vector(const valarray &x): valarray(x){}
		vector(const std::slice_array<T> &sub): valarray(sub){}
		vector(const std::gslice_array<T> &sub): valarray(sub){}
		vector(const std::mask_array<T> &sub): valarray(sub){}
		vector(const std::indirect_array<T> &sub): valarray(sub){}

		vector& operator=(const valarray &x){
			//std::cerr << "mv=va";
			resize(x.size());
			valarray::operator=(x);
			return *this;
		}
		vector& operator=(const vector &x){
			//std::cerr << "mv=mv";
			resize(x.size());
			valarray::operator=(x);
			return *this;
		}

		void assign(const vector &v){
			valarray::operator=(v);
		}
		void assign(const valarray &v){
			valarray::operator=(v);
		}

	//added methods
		inline value_type dot(const vector &b) const{
			return (*this*b).sum();
		}
		inline value_type norm2() const{
			return this->dot(*this);
		}
	};

	template<class T>
	inline T dot(const std::valarray<T> &a, const std::valarray<T> &b){
		return (a*b).sum();
	}

	template<class T>
	inline T norm2(const std::valarray<T> &v){
		return dot<T>(v,v);
	}

}

#endif


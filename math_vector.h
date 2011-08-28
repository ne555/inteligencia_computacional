#ifndef MATH_VECTOR
#define MATH_VECTOR

#include <valarray>

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

	//added methods
		inline value_type dot(const vector &b) const{
			return (*this*b).sum();
		}
		inline value_type norm2() const{
			return this->dot(*this);
		}
	};


}

#endif


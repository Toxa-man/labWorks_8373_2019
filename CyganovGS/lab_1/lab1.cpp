#include<iostream>
#include<memory.h>
#include<cstdlib>

using namespace std;

template<typename T>
class Vector{
	private:
		unsigned vsize;
		T *data;
		friend ostream& operator <<(ostream& out, const Vector& v){
			for(int i=0; i<v.vsize; i++){
				out<<v.data[i]<<" ";
			}
			return out;
		}
	public:
		Vector();		
		Vector(unsigned s);		
		Vector(unsigned s, const T& val);		
		Vector(const Vector& vec);		
		int size();		
		void resize(unsigned s);		
		bool insert(unsigned pos, T val);		
		void push_back(T val);		
		bool contains(const T& val);		
		int find(const T& val);		
		T* Data();		
		Vector& operator =(const Vector &vec){
			if(this != &vec){
				vsize=vec.vsize;
				delete[] data;
				data=new T[vsize];
				memcpy(data, vec.data, sizeof(T)*vsize);
			}
			return *this;
		}	
		T& operator [](unsigned n){
			return data[n];
		}	
		~Vector();
		
};

template<typename T>
Vector<T>::Vector(){
			vsize=0;
			data=NULL;
		}

template<typename T>
Vector<T>::Vector(unsigned s){
			vsize=s;
			data=new T[s];
			for(int i=0; i<s; i++){
				data[i]=(T)i;
			}
		}

template<typename T>
Vector<T>::Vector(unsigned s, const T& val){
			vsize=s;
			data=new T[s];
			for(int i=0; i<s; i++){
				data[i]=(T)val;
			}
		}

template<typename T>
Vector<T>::Vector(const Vector& vec){
			vsize=vec.size;
			data=new T[size];
			memcpy(data, vec.data, vsize*sizeof(T));
		}

template<typename T>
int Vector<T>::size(){
			return vsize;
		}

template<typename T>
void Vector<T>::resize(unsigned s){
			T* cpy_arr=new T[s];
    		memcpy(cpy_arr, data, sizeof(T)*vsize);
    		delete []data;
    		data=new T[s];
			if(s>vsize){
        		memcpy(data, cpy_arr, sizeof(T)*vsize);
        		memset(data+vsize, T(), (s-vsize)*sizeof(T));
    		}else if(s<vsize){
            	memcpy(data, cpy_arr, sizeof(T)*s);
    		}
    		vsize=s;
    		delete []cpy_arr;
		}

template<typename T>
bool Vector<T>::insert(unsigned pos, T val){
			if(pos>=vsize || pos<0){
				return false;
			}else{
				resize(vsize+1);
				for(int i=vsize-1; i>pos; i--){
					data[i]=data[i-1];
				}
				data[pos]=val;
				return true;
			}
		}

template<typename T>
void Vector<T>::push_back(T val){
			resize(vsize+1);
			data[vsize-1]=val;
		}

template<typename T>
bool Vector<T>::contains(const T& val){
			for(int i=0; i<vsize; i++){
				if(val==data[i]){
					return true;
				}
			}
			return false;
		}

template<typename T>
int Vector<T>::find(const T& val){
			for(int i=0; i<vsize; i++){
				if(data[i]==val){
					return i;
				}
			}
			return -1;	
		}

template<typename T>
T* Vector<T>::Data(){
			return data;
		}

template<typename T>
Vector<T>::~Vector(){
			vsize=0;
			delete []data;
		}


int main(){
	setlocale(0, "");
	Vector<int> vec(10);
	cout<<vec<<endl;
	cout<<vec.size()<<endl;
	vec.resize(15);
	cout<<vec<<endl;
	vec.insert(11, 11);
	cout<<vec<<endl;
	vec.push_back(17);
	cout<<vec<<endl;
	cout<<vec.contains(1)<<" "<<vec.contains(14)<<endl;
	cout<<vec[1]<<endl;
	cout<<vec.find(11)<<" "<<vec.find(14)<<endl;
	cout<<vec.Data()<<endl;
	Vector<int> test_vec;
	test_vec=vec;
	cout<<test_vec<<endl;
	return 0;
}

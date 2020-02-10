
#include "Vector.h"

//
// Created by Shiv on 2/3/2020.
//

#ifndef PROJ_2_VECTOR_HPP
#define PROJ_2_VECTOR_HPP
using namespace std;
//Constructors
    //Default zero parameter constructor
        template<typename T>
        Vector<T>::Vector(){
            //Initialize member variables to zero
                theSize = 0;
                theCapacity = 0;
                array = nullptr;
        }
     //Copy Constructor
        template<typename  T>
        Vector<T>::Vector(const Vector &rhs) : theSize { rhs.theSize },
            theCapacity { rhs.theCapacity }, array { nullptr }{

            //Allocate size for array
                array = new T[theCapacity];
            //Copy the array
                for (int i = 0; i < rhs.array.size(); ++i) {
                    array[i] = rhs.array[i];
                }
        }
    //Move Constructor
        template<typename  T>
        Vector<T>::Vector(Vector &&rhs) : theSize { rhs.theSize },
            theCapacity { rhs.theCapacity }, array{ rhs.array }{

            //Reset Values
                rhs.theSize = 0;
                rhs.theCapacity = 0;
                rhs.array = nullptr;
        }
    //Explicit Constructor
        template<typename T>
        Vector<T>::Vector(int num, const T &val) : theCapacity {num}
        {
            //Create New Vector of size Capacity
                array = new T[theCapacity];
           //Set all elements equal to val
            for (int i = 0; i < num; ++i) {
                array[i] = val;
            }

        }
    //Constructor with range
    //TODO FIGURE OUT HOW TO DO THIS
        template<typename  T>
        Vector<T>::Vector(const_iterator start, const_iterator end) {
            //Create New Vector
                array = new T[theCapacity];
                int i=0;
           //Copy elements into new vector
            for(auto itr = start; itr != end; itr++ ){
                array[i++] = *itr;
            }
        }


//Destructor
    //Destructor
        template<typename T>
        Vector<T>::~Vector(){
            delete []array;
        }


//Operators
    //Index operators
        template<typename T>
        T &Vector<T>::operator[](int index){ //TODO Check if T& is correct format
            return array[index];
        }

        template<typename T>
        const T &Vector<T>::operator[](int index) const {
            return array[index];
        }
    //Copy Assignment Operator //TODO Gives error invalid use of template-name cop4530::Vector without argument list
        template<typename T> //TODO CHECK WHY its highlighted
        const Vector<T>& Vector<T>::operator=(const Vector<T> &rhs){
            Vector copy = *this;
            std::swap(*this, copy);
            return *this;
        }
   //Move Assignment Operator
        template<typename T>
        Vector<T>& Vector<T>::operator=(Vector<T> &&rhs) {
            //Swap
                std::swap(theSize, rhs.theSize);
                std::swap(theCapacity, rhs.theCapacity);
                std::swap(array, rhs.array);
            //Return
                return *this;
        }
    //AT Operators
        template<typename T>
        T& Vector<T>::at(int loc) {
            //Check if loc is within range
            if(loc < theSize){
                //return
                return array[loc];
            }
        }

        template<typename T>
        const T& Vector<T>::at(int loc) const{
            //Check if loc is within range
            if(loc < theSize){
                //return
                return array[loc];
            }
        }
    //Reference to first element
        template<typename T>
        T &Vector<T>::front() {
            return array[0];
        }
        template<typename T>
        const T &Vector<T>::front() const {
            return array[0];
        }
    //Reference to last element
        template<typename T>
         T &Vector<T>::back() {
            return array[theSize-1];
        }
        template <typename T>
        const T &Vector<T>::back() const{
            return array[theSize-1];
        }
    //Accessor Member Functions
        //Number of elements
            template <typename T>
            int Vector<T>::size() const {
                return theSize;
            }
        //Capacity of Vector
            template <typename T>
            int Vector<T>::capacity() const {
                return theCapacity;
            }
        //Check if list is empty
            template <typename T>
            bool Vector<T>::empty() const {
                return size() == 0;
            }
    //Mutator Member Fucntions
        //Delete all elements
            template<typename T>
            void Vector<T>::clear() { //TODO CHECK STL COMPLEXITY FOR VECTOR
                delete [] array;
            }
        //Insert to the end
            template <typename T>
            void Vector<T>::push_back(const T &val) {
                //Check is size == capacity
                    if(theSize == theCapacity){
                        //Increase theCapacity
                            reserve(2*theCapacity+1);
                    }
                    //Insert element
                    array[theSize++] = val;
            }
        //Delete Last Element
            template <typename T>
            void Vector<T>::pop_back() {
                //Decrement the size
                    --theSize;
            }
        //Resize the Vector
            template <typename T>
            void Vector<T>::resize(int num, T val) {
                //If newSize is Less than theCapacity
                if(num > theSize && num < theCapacity ){
                    //Set new positions in vector to newValue
                        for(int i=theSize; i < num; i++ ){
                            array[i] = val;
                        }
                     //Change size of vector
                        theSize = num;
                }
                //If newSize is Greater than theCapacity
                else if(num > theSize && num > theCapacity){
                    //Increase theCapacity
                        reserve(2*theCapacity+1);
                    //Set new positions in vector to newValue
                        for(int i=theSize; i < num; i++){
                            array[i] = val;
                        }
                      //Change size of vector
                        theSize = num;
                }
            }
        //Reserve
            template <typename T>
            void Vector<T>::reserve(int newCapacity) {
                //Check if newCapacity < theSize
                    if(newCapacity < theSize)
                        return;
                //OR
                //Create Temp Array of newCapacity
                    T*temparr = new T[newCapacity];
                //Move elements from arr to Temp
                    for(int i =0; i < theSize; i++){
                        temparr[i] = std::move(array[i]);
                    }
                //Set theCapacity to newCapacity
                    theCapacity = newCapacity;
                //Swap array
                    std::swap(array, temparr);
                //Delete Temparr
                    delete [] temparr;
            }
        //Print
            template <typename T>
            void Vector<T>::print(std::ostream &os, char ofc) const {
                for(int i=0; i < theSize; i++){
                    os << array[i] << "ofc";
                }
            }
    //Iterator Support
        //Iterator to first element
            template <typename T> //TODO Check if correct?
            typename Vector<T>::iterator Vector<T>::begin() {
                return &array[0];
            }
            template <typename T>
            typename Vector<T>::const_iterator Vector<T>::begin() const {
                return &array[0];
            }
        //End marker iterator
            template <typename T>
            typename Vector<T>::iterator Vector<T>::end() {
                return &array[theSize];
            }
            template <typename T>
            typename Vector<T>::const_iterator Vector<T>::end() const {
                return &array[theSize];
            }
        //Insert Iterator
            template <typename T>//TODO CHECK if I need <T> in parameter AND RETURN TYPE
            typename Vector<T>::iterator Vector<T>::insert(Vector<T>::iterator itr, const T &val) {
                //Check if enough room to grow
                    if(theCapacity-theSize <= 1){
                        //Grow theCapacity
                        reserve(2*theCapacity+1);
                    }
                //Push back array by 1
                    for(int i = theSize; i > itr+1; i--){
                        array[i] = array[i-1];
                    }
                //Insert val
                    array[itr] = val;
                return &itr;
            }
        //Erase 
            template <typename T>
            typename Vector<T>::iterator Vector<T>::erase(iterator itr) {
                //Push front array by 1
                    for(int i = itr; i < theSize; i++){
                       array[i] = array[i+1];
                    }
                    return &itr;
            }
            template <typename T>
            typename Vector<T>::iterator Vector<T>::erase(iterator start, iterator end) {
                //Loop
                for (auto i = start; i < end; i++) { //TODO CHECK START
                    erase(i);
                }
            }
        //Double Capacity
            template <typename T>
            void Vector<T>::doubleCapacity() { //TODO CHeck if to add in push back
                //Double theCapacity
                    reserve(2*theCapacity+1);
            }

#endif //PROJ_2_VECTOR_HPP

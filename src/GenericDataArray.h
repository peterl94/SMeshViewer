//-----------------------------------------------------------------------------
//Copyright (c) 2014 Peter Lama
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
//-----------------------------------------------------------------------------

#ifndef GENERIC_DATA_ARRAY_H
#define GENERIC_DATA_ARRAY_H

#include <stdexcept>

template<typename T>
class GenericDataArray
{
public:
    typedef T* iterator;
    typedef const T* const_iterator;
  
    GenericDataArray() 
		: m_length(0), m_componentLength(0), m_data(0)
    {
    
    }
    
	GenericDataArray(unsigned int length, unsigned int componentLength = 1) 
		: m_length(length), m_componentLength(componentLength)
    {
		m_data = new T[length * componentLength];
    }
    
	GenericDataArray(const T* data, unsigned int length, unsigned int componentLength = 1)
        : m_length(length), m_componentLength(componentLength)
    {
        m_data = new T[length * componentLength];
        setData(data, length, componentLength);
    }
    
	~GenericDataArray()
    {
        delete[] m_data;
    }
    
	unsigned int length() const { return m_length; }
	unsigned int componentLength() const { return m_componentLength; }
	unsigned int byteSize() const { return m_length * m_componentLength * sizeof(T); }

    iterator begin() const { return m_data; }
	iterator end() const { return m_data + (m_length * m_componentLength); }
    const T* data() const { return m_data; }
	void setData(const T* data, int length, int componentLength = 1)
	{
		if (m_data == 0) {
		    m_length = length;
		    m_componentLength = componentLength;
			m_data = new T[length * componentLength];
	    }
		std::copy(data, data + (length * componentLength), m_data);
	}
    
	T& at(unsigned int index)
	{
		if (index >= m_length) {
			throw std::out_of_range("GenericDataArray: index out of range");
		}
		return m_data[index];
	}

	T& at(unsigned int index, unsigned int componentIndex)
	{
		if (index >= m_length) {
			throw std::out_of_range("GenericDataArray: index out of range");
		}

		if (componentIndex >= m_componentLength) {
			throw std::out_of_range("GenericDataArray: component index out of range");
		}

		return m_data[(index * m_componentLength) + componentIndex];
	}

	T& operator[](unsigned int index) { return m_data[index]; }
    
private:
    GenericDataArray(const GenericDataArray& other);
    
    unsigned int m_length;
    unsigned int m_componentLength;
    T* m_data;
};

#endif // GENERIC_DATA_ARRAY_H

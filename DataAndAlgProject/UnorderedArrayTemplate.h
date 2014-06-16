#pragma once
template<class T>
class UnorderedArrayTemplate
{
public:
	// functions
	UnorderedArrayTemplate(int size, int growBy = 1) :
							m_array(NULL), m_maxSize(0),
							m_growSize(0), m_numElements(0)
	{
		if(size)
		{
			m_maxSize = size;
			m_array = new T[m_maxSize];
			memset(m_array, 0, sizeof(T) * m_maxSize);

			m_growSize = ((growBy > 0) ? growBy : 0);
		}
	}
	virtual ~UnorderedArrayTemplate(void)
	{
		if(m_array != NULL)
		{
			delete[] m_array;
			m_array = NULL;
		}
	}

	virtual void push(T val)
	{
		assert(m_array != NULL);

		if(m_numElements >= m_maxSize)
		{
			Expand();
		}

		m_array[m_numElements] = val;
		m_numElements++;
	}

	void pop(void)
	{
		if(m_numElements > 0)
		{
			m_numElements--;
		}
	}

	void remove(int index)
	{
		assert(m_array != NULL);

		if(index >= m_maxSize)
		{
			return;
		}

		for(int k = index; k < m_maxSize - 1; k++)
		{
			m_array[k] = m_array[k + 1];
		}

		m_maxSize--;

		if(m_numElements >= m_maxSize)
		{
			m_numElements = m_maxSize - 1;
		}
	}

	virtual T& operator[](int index)
	{
		assert(m_array != NULL && index <= m_numElements);
		return m_array[index];
	}

	virtual int search(T val)
	{
		assert(m_array != NULL);

		for(int i = 0; i < m_numElements; i++)
		{
			if(m_array[i] == val)
			{
				return i;
			}
		}
	}

	void setGrowSize(int val)
	{
		assert(val >= 0);
		m_growSize = val;
	}

	void clear()		{m_numElements = 0;}
	int GetSize()		{return m_numElements;}
	int GetMaxSize()	{return m_maxSize;}
	int GetGrowSize()	{return m_growSize;}

private:
	// functions
	bool Expand()
	{
		if(m_growSize <= 0)
		{
			return false;
		}

		T *temp = new T[m_maxSize + m_growSize];
		assert(temp != NULL);

		memcpy(temp, m_array, sizeof(T) * m_maxSize);

		delete[] m_array;
		m_array = temp;

		m_maxSize += m_growSize;

		return true;
	}

private:
	//fields
	T *m_array;

	int m_maxSize;
	int m_growSize;
	int m_numElements;
};




template <typename T>
class Vector
{
    public:

    //Default Constructor
    Vector():
    m_default_size(20),
    m_vector(static_cast<T*>(operator new[](m_default_size* sizeof(T)))), 
    m_current_pointer(0)
    {

    }

    //Param Construction
    Vector(int size): m_default_size(size), 
    m_vector(static_cast<T*>(operator new[](size * sizeof(T)))), 
    m_current_pointer(0)
    {

    }

    //Params Construction with a value
    Vector(int size, T default_value): m_default_size(size),
    m_vector(static_cast<T*>(operator new[](size * sizeof(T)))), 
    m_current_pointer(0)
    {
        for (int i = 0; i < size; ++i) {
            new(&m_vector[i]) T(default_value);
        }
    }

    //Copy assignment operator
    Vector& operator=(const Vector& copy_vector){
        clear(); // Clear current objects
        m_default_size = copy_vector.m_default_size;
        m_current_pointer = copy_vector.m_current_pointer;
        m_vector = static_cast<T*>(operator new[](m_default_size * sizeof(T)));
        for (size_t i = 0; i < m_current_pointer; i++) {
            new(&m_vector[i]) T(copy_vector.m_vector[i]); // Copy construct
        }
        return *this;
    }
    
    //Copy Constructor
    Vector(const Vector& copy_vector): m_default_size(copy_vector.m_default_size),
                                      m_current_pointer(copy_vector.m_current_pointer),
                                      m_vector(new T[m_default_size])
                                    
    {
        for(size_t i =0; i<m_default_size ; i++)
        {
            m_vector[i] = copy_vector[i];
        }
    }

   template <typename... Args>
void emplace_back(Args&&... args)
{
    if (m_current_pointer == m_default_size) {
        resize();
    }
    // Construct the object directly in the array using placement new
    new(&m_vector[m_current_pointer++]) T(std::forward<Args>(args)...);
}


    //Move Constructor
    Vector(Vector&& copy_vector){
        m_default_size = copy_vector.m_default_size;
        m_current_pointer = copy_vector.m_current_pointer;
        m_vector = copy_vector.m_vector;
        copy_vector.m_default_size = 0;
        copy_vector.m_current_pointer =0;
        copy_vector.m_vector = nullptr;

    }

    //Move assigment operator
    Vector& operator=(Vector&& copy_vector)
    {
        m_default_size = copy_vector.m_default_size;
        m_current_pointer = copy_vector.m_current_pointer;
        m_vector = copy_vector.m_vector;
        copy_vector.m_default_size = 0 ;
        copy_vector.m_current_pointer = 0;
        copy_vector.m_vector = nullptr;
        return *this;
    }

    //Destructor

    ~Vector()
    {
        clear(); // Ensure all objects are destructed
        ::operator delete[](m_vector); // Deallocate raw memory
    }

    

    

    T& operator[](size_t index)
    {
        if(m_default_size <=index)
        {
            throw std::out_of_range("Index out of range");
        }
        return m_vector[index];
    }

    void resize()
    {
        int current_default_size = m_default_size;
        m_default_size = m_default_size*2;
        T* temp_vector = new T[m_default_size];
        for(size_t i =0 ;i < current_default_size; i++)
        {
            temp_vector[i] = m_vector[i];
        }
    }

    void push_back(T value)
    {  
        if(m_current_pointer == m_default_size)
        {
            resize();
        }
        m_vector[m_current_pointer++] = T(value);
    }

    void push_back(T& value)
    {
        if(m_current_pointer == m_default_size)
        {
            resize();
        }
        m_vector[m_current_pointer++] = value;
    }

    void pop_back()
    {
        m_current_pointer--;
        
    }

    size_t size() const{
        return m_current_pointer;
    }

    void clear(){
        for(size_t i =0; i< m_current_pointer; i++)
        {
            m_vector[i].~T();
        }
        m_current_pointer =0;
    }

    private:
    int m_default_size = 20;
    T* m_vector;
    int m_current_pointer;



};
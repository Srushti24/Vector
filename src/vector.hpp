

template <typename T>
class Vector
{
    public:

    //Default Constrcutor
    Vector():m_vector(new T[m_default_size]), m_current_pointer(0)
    {

    }

    //Param Constrcutor
    Vector(int size): m_vector(new T[size]), m_current_pointer(0)
    {

    }
    //Params constructor with a value
    Vector(int size, T default_value): m_vector(new T[size]), m_default_size(size)
    {
        for (int i = 0; i < size; ++i) {
            m_vector[i] = default_value;
        }
    }


    //Copy assignment operator
    Vector& operator=(const Vector& copy_vector){
        delete m_vector;
        m_default_size = copy_vector.m_default_size;
        m_current_pointer = copy_vector.m_current_pointer;
        m_vector = new T[m_default_size];
        for(size_t i =0; i<m_current_pointer; i++)
            {
                m_vector[i] = copy_vector[i];
            }
        return *this;
    }
    
    //Copy constructor
    Vector(const Vector& copy_vector): m_default_size(copy_vector.m_default_size),
                                      m_current_pointer(copy_vector.m_current_pointer),
                                      m_vector(new T[m_default_size])
                                    
    {
        for(size_t i =0; i<m_default_size ; i++)
        {
            m_vector[i] = copy_vector[i];
        }
    }


    //Move constructor
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
        delete m_vector;
        m_vector = nullptr;
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

    void push_back(T& value)
    {
        if(m_current_pointer == m_default_size)
        {
            resize();
        }
        else
        {
            m_vector[m_current_pointer] = value;
            m_current_pointer++;
        }
    }

    void pop_back()
    {
        m_current_pointer--;
        
    }

    size_t size() const{
        return m_current_pointer;
    }

    void clear(){
        m_current_pointer = 0;
        delete m_vector;
        m_vector = new T[m_default_size];
    }

    private:
    int m_default_size = 20;
    T* m_vector;
    int m_current_pointer;



};
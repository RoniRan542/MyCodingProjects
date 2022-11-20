#include <iostream> //cout
using namespace std;

class PublicTransport
{
public:
    PublicTransport() : m_license_plate(++s_count)
    {
        cout << "PublicTransport::Ctor()" << m_license_plate << "\n";
    }

    virtual ~PublicTransport()
    {
        --s_count;
        cout << "PublicTransport::Dtor()" << m_license_plate << "\n";
    }

    PublicTransport(const PublicTransport &other) : m_license_plate(++s_count)
    {
        cout << "PublicTransport::CCtor() " << m_license_plate << "\n";
    }

    virtual void display()
    {
        cout << "PublicTransport::display(): " << m_license_plate << "\n";
    }

    static void print_count()
    {
        cout << "s_count: " << s_count << "\n";
    }

protected:
    int get_ID()
    {
        return m_license_plate;
    }

private:
    static int s_count;
    int m_license_plate;
    PublicTransport &operator=(const PublicTransport &); // disabled
};

int PublicTransport::s_count = 0;

class Minibus : public PublicTransport
{
public:
    Minibus() : m_numSeats(20)
    {
        cout << "Minibus::Ctor()\n";
    }

    Minibus(const Minibus &other) : PublicTransport(other),
                                    m_numSeats(other.m_numSeats)
    {
        cout << "Minibus::CCtor()\n";
    }

    ~Minibus()
    {
        cout << "Minibus::Dtor()\n";
    }

    void display()
    {
        cout << "Minibus::display() ID:" << get_ID();
        cout << " num seats:" << m_numSeats << "\n";
    }

    virtual void wash(int minutes)
    {
        cout << "Minibus::wash(" << minutes << ") ID:" << get_ID() << "\n";
    }

private:
    int m_numSeats;
};

class Taxi : public PublicTransport
{
public:
    Taxi()
    {
        cout << "Taxi::Ctor()\n";
    }

    Taxi(const Taxi &other) : PublicTransport(other)
    {
        cout << "Taxi::CCtor()\n";
    }

    ~Taxi()
    {
        cout << "Taxi::Dtor()\n";
    }

    void display()
    {
        cout << "Taxi::display() ID:" << get_ID() << "\n";
    }

private:
};

template <class T>
inline T max_func(const T &t1, const T &t2)
{
    return ((t1 > t2) ? t1 : t2);
}

/**/ class SpecialTaxi : public Taxi
{
public:
    SpecialTaxi()
    {
        cout << "SpecialTaxi::Ctor()\n";
    }

    SpecialTaxi(const SpecialTaxi &other) : Taxi(other)
    {
        cout << "SpecialTaxi::CCtor()\n";
    }

    ~SpecialTaxi()
    {
        cout << "SpecialTaxi::Dtor()\n";
    }

    void display()
    {
        cout << "SpecialTaxi::display() ID:" << get_ID() << "\n";
    }

private:
};

/*class PublicConvoy: public PublicTransport {
public:
    PublicConvoy() : m_pt1(new Minibus()), m_pt2(new Taxi())
    {
    }

    ~PublicConvoy()
    {
        delete m_pt1;
        delete m_pt2;
    }

    void display()
    {
        m_pt1->display();
        m_pt2->display();
        m_m.display();
        m_t.display();
    }

private:
    PublicTransport *m_pt1;
    PublicTransport *m_pt2;
    Minibus m_m;
    Taxi m_t;
};*/

void print_info(PublicTransport &a)
{
    a.display();
}

void print_info()
{
    PublicTransport::print_count();
}

void print_info(Minibus &m)
{
    m.wash(3);
}

PublicTransport print_info(int i)
{
    Minibus ret;
    cout << "print_info(int i)\n";
    ret.display();
    return ret;
}

void taxi_display(Taxi s)
{
    s.display();
}

int main(int argc, char **argv, char **envp)
{
    // minibus inherits from public transport
    Minibus m;
    print_info(m);
    print_info(3).display();
    PublicTransport *array[] = {new Minibus(), new Taxi(), new Minibus()};

    for (int i = 0; i < 3; ++i)
    {
        array[i]->display();
    }

    for (int i = 0; i < 3; ++i)
    {
        delete array[i];
    }

    PublicTransport arr2[] = {Minibus(), Taxi(), PublicTransport()};

    for (int i = 0; i < 3; ++i)
    {
        arr2[i].display();
    }
    print_info(arr2[0]);

    PublicTransport::print_count();
    Minibus m2;
    m2.print_count();

    Minibus arr3[4];
    Taxi *arr4 = new Taxi[4];
    delete[] arr4;

    std::cout << max_func(1, 2) << "\n";
    std::cout << max_func<int>(1, 2.0f) << "\n";
    SpecialTaxi st;
    taxi_display(st);

    /*PublicConvoy *ts1 = new PublicConvoy();
    PublicConvoy *ts2 = new PublicConvoy(*ts1);
    ts1->display();
    ts2->display();
    delete ts1;
    ts2->display(); // this crashes. fix the bug!
    delete ts2;*/

    return 0;
}

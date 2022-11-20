/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Author: Daniel Jenudi
- Date: 22/09/22
- Reviwer: Yaron
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <iostream>
#include <string>

#include "dispatcher.hpp"

using namespace std;
using namespace ilrd;

enum WhichRanCohenAmI
{
    FULLSTACK = 0,
    EMBEDED
};

/***** Room_Temperature *****/
class Room_Temperature
{
public:
    Room_Temperature(size_t temperature = 0);

    void SetTemp(size_t temperature);
    size_t GetTemp(void);

    void EnterRoom(Listener<size_t> *student);
    void ExitRoom(Listener<size_t> *student);

private:
    size_t m_temperature;
    Dispatcher<size_t> m_disp;
};

Room_Temperature::Room_Temperature(size_t temperature) : m_temperature(temperature)
{
    // Empty
}

void Room_Temperature::SetTemp(size_t temperature)
{
    m_temperature = temperature;
    m_disp.Invoke(temperature);
}
size_t Room_Temperature::GetTemp(void)
{
    return m_temperature;
}

void Room_Temperature::EnterRoom(Listener<size_t> *student)
{
    m_disp.AddListener(student);
}

void Room_Temperature::ExitRoom(Listener<size_t> *student)
{
    m_disp.RemoveListener(student);
}

/***** Hagar *****/
class Hagar : public Listener<size_t>
{
private:
    virtual void Invoke(const size_t &);
    virtual void PublisherDied(void) noexcept;
};

void Hagar::Invoke(const size_t &temperature)
{
    if (27 < temperature)
    {
        cout << "Hagar: wow perfect temperature!\n";
    }
    else
    {
        cout << "Hagar: oh, the room is like a freezer!\n";
    }
}
void Hagar::PublisherDied(void) noexcept
{
    cout << "Hagar: nice the air conditioner broke down\n";
}

/***** Daniel *****/
class Daniel : public Listener<size_t>
{
private:
    virtual void Invoke(const size_t &);
    virtual void PublisherDied(void) noexcept;
};

void Daniel::Invoke(const size_t &temperature)
{
    if (22 > temperature)
    {
        cout << "Daniel: wow perfect temperature!\n";
    }
    else
    {
        cout << "Daniel: its August GOD!\n";
    }
}
void Daniel::PublisherDied(void) noexcept
{
    cout << "Daniel: the air conditioner broke down, i'm leaving\n";
}

/***** Eyad *****/
class Eyad : public Listener<size_t>
{
private:
    virtual void Invoke(const size_t &);
    virtual void PublisherDied(void) noexcept;
};

void Eyad::Invoke(const size_t &temperature)
{
    (void)temperature;
    cout << "Eyad: Hunnyyyy!\n";
}
void Eyad::PublisherDied(void) noexcept
{
    cout << "Eyad: the air conditioner broke down Hunnyyyy\n";
}

/***** Osher *****/
class Osher : public Listener<size_t>
{
private:
    virtual void Invoke(const size_t &);
    virtual void PublisherDied(void) noexcept;
};

void Osher::Invoke(const size_t &temperature)
{
    if (27 < temperature)
    {
        cout << "Osher: lets play poker-yaniv\n";
    }
    else
    {
        cout << "Osher: let me tell you about let\n";
    }
}
void Osher::PublisherDied(void) noexcept
{
    cout << "Osher: bey\n";
}

/***** Ran_Cohen *****/
class Ran_Cohen : public Listener<size_t>
{
private:
    virtual void Invoke(const size_t &);
    virtual void PublisherDied(void) noexcept;
};

void Ran_Cohen::Invoke(const size_t &temperature)
{
    std::string lut[2] = {" FULLSTACK\n", " EMBEDED\n"};
    cout << "Ran_Cohen: Ran Cohen from" << lut[temperature];
}
void Ran_Cohen::PublisherDied(void) noexcept
{
    cout << "Ran_Cohen: Ran Cohens, assemble\n";
}

int main()
{
    Room_Temperature *lab = new Room_Temperature;
    Room_Temperature stinkey_lab;

    Hagar hagar;
    Eyad eyad;
    Daniel daniel;
    Osher osher;

    lab->EnterRoom(&hagar);
    lab->EnterRoom(&eyad);
    lab->EnterRoom(&daniel);
    lab->EnterRoom(&osher);

    cout << "temp 18\n";
    lab->SetTemp(18);

    cout << "\ntemp 28\n";
    lab->SetTemp(28);

    cout << "\nosher exit the lab\n";
    lab->ExitRoom(&osher);

    cout << "air conditioner broke(dtor, operatoe=)\n\n";
    stinkey_lab = *lab;
    delete lab;

    cout << "\nmove to stinkey_lab\n";
    cout << "eyad exit stinkey_lab\n";
    cout << "osher enter stinkey_lab\n\n";

    stinkey_lab.ExitRoom(&eyad);
    stinkey_lab.EnterRoom(&osher);

    cout << "temp 18\n";
    stinkey_lab.SetTemp(18);

    cout << "\ntemp 28\n";
    stinkey_lab.SetTemp(28);

    cout << "\nvisit in fullstack_room\n";
    Room_Temperature fullstack_room(stinkey_lab);

    cout << "temp in fullstack_room(cctor) - " << fullstack_room.GetTemp() << "\n";

    cout << "\ntemp 20\n";
    fullstack_room.SetTemp(20);

    fullstack_room.ExitRoom(&hagar);
    fullstack_room.ExitRoom(&daniel);
    fullstack_room.ExitRoom(&osher);

    cout << "\nRan cohen test\n";
    Ran_Cohen ran_cohen;
    Room_Temperature embeded_room;
    fullstack_room.EnterRoom(&ran_cohen);
    embeded_room.EnterRoom(&ran_cohen);

    embeded_room.SetTemp(EMBEDED);
    fullstack_room.SetTemp(FULLSTACK);

    return 0;
}

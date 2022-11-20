#include <iostream>
#include <list>

using namespace std;

class State
{
public:
    State(string str = "the free Editor:\n");
    string GetContent() const;

private:
    string m_content;
};

class History
{
public:
    History(){};
    void AddState(State st);
    State GetPervState();

private:
    list<State> m_prev_conts;
};

class Editor
{

public:
    void SetContent(State new_state);
    string GetContent() const;
    void Undo();

private:
    State m_curr_state;
    History m_history;
};

void Editor::SetContent(State new_state)
{
    m_history.AddState(m_curr_state);
    m_curr_state = new_state;
}

string Editor::GetContent() const
{
    return m_curr_state.GetContent();
}

void Editor::Undo()
{
    m_curr_state = m_history.GetPervState();
}

State::State(string str) : m_content(str)
{
}

string State::GetContent() const
{
    return m_content;
}

void History::AddState(State st)
{
    m_prev_conts.push_back(st);
}

State History::GetPervState()
{
    State ret = m_prev_conts.back();
    m_prev_conts.pop_back();

    return ret;
}

int main()
{
    Editor editor;

    State st1("Welcome to my blog!\n");
    State st2("Welcome to my blog!\n My name is Ran\n");
    State st3("Welcome to my blog!\n My name is Rani\n");
    State st4("Welcome to my blog!\nMy name is Roni\n");
    State st5("Welcome to my blog!\n Just call me Ryan\n");

    editor.SetContent(st1);
    cout << editor.GetContent() << endl;
    editor.SetContent(st2);
    cout << editor.GetContent() << endl;
    editor.SetContent(st3);
    cout << editor.GetContent() << endl;
    editor.SetContent(st4);
    cout << editor.GetContent() << endl;
    editor.SetContent(st5);
    cout << editor.GetContent() << endl;

    cout << "\n\n Go back twice \n\n"
         << endl;

    editor.Undo();
    editor.Undo();

    cout << editor.GetContent() << endl;

    cout << "\n\n Go to begin \n\n"
         << endl;

    editor.Undo();
    editor.Undo();

    cout << editor.GetContent() << endl;

    return 0;
}

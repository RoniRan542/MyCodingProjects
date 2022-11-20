#include <sys/types.h> //for dirent package
#include <iostream>    // for print cout
#include <dirent.h>    //for dirent package
#include <cstring>     // for string, strcmp, substr
#include <list>        // for list operations

#include "file_tree.hpp" //for file_tree funcs
#include "file.hpp"      //for file funcs
#include "directory.hpp" //for directory funcs
#include "reg_file.hpp"  //for reg_file funcs

#define BLUE "\033[34m"  // Color for directory
#define WHITE "\033[37m" // Color for regular file
#define GREEN "\033[32m" // Color for exe file

using namespace std;

namespace ilrd
{
    static void CleanResources(list<File *> m_dir_files);
    // Tree implementation

    Tree::Tree(const string &path) : m_root(new Directory(path))
    {
        cout << "tree Ctor\n\n";
    }

    Tree::~Tree() noexcept
    {
        delete m_root;
    }

    void Tree::Display()
    {
        m_root->print(0);
    }

    // File implementation
    File::~File() noexcept
    {
        // empty
    }

    void File::print(size_t indents)
    {
        for (size_t i = 0; i < indents; ++i)
        {
            cout << ((i + 1 == indents) ? "├──" : "│  ");
        }
    }

    // Directoy implementation

    Directory::Directory(const string &path) : m_name(strrchr(path.c_str(), '/') + 1)
    {
        DIR *dir = opendir(path.c_str());
        list<File *>::iterator iter = m_dir_files.begin();
        File *file = nullptr;

        if (dir)
        {
            struct dirent *entry = readdir(dir);
            while (entry != NULL)
            {

                if (0 == strcmp(entry->d_name, ".") ||
                    0 == strcmp(entry->d_name, ".."))
                {
                    entry = readdir(dir);
                    continue;
                }

                try
                {
                    if (entry->d_type == DT_DIR)
                    {
                        file = new Directory(path + "/" + entry->d_name);
                    }
                    else
                    {
                        file = new Reg_File(entry->d_name);
                    }
                }
                catch (const std::exception &e)
                {
                    CleanResources(m_dir_files);
                    cerr << "failed to allocate memory" << e.what() << '\n';
                    closedir(dir);
                    throw e;
                }
                m_dir_files.insert(iter, file);
                entry = readdir(dir);
            }
            closedir(dir);
        }
    }

    Directory::~Directory() noexcept
    {
        CleanResources(m_dir_files);
    }

    void Directory::print(size_t indents)
    {
        File::print(indents);
        cout << BLUE << m_name << WHITE << "\n";
        ++indents;

        for (list<File *>::iterator it = m_dir_files.begin();
             m_dir_files.end() != it; ++it)
        {
            (*it)->print(indents);
        }
    }

    // RegFile implementation
    Reg_File::Reg_File(const std::string &name) : m_name(name)
    {
        // empty
    }

    Reg_File::~Reg_File() noexcept
    {
        // empty
    }

    void Reg_File::print(size_t indents)
    {
        File::print(indents);

        if (m_name.substr(m_name.find_last_of(".") + 1) == "out")
        {
            cout << GREEN << m_name << WHITE << "\n";
        }
        else
        {
            cout << WHITE << m_name << "\n";
        }
    }

    // Static Funcs

    static void CleanResources(list<File *> m_dir_files)
    {
        list<File *>::iterator iter = m_dir_files.begin();

        while (iter != m_dir_files.end())
        {
            delete *iter;
            ++iter;
            m_dir_files.pop_front();
        }
    }

}

#ifndef __RD12123_FACTORY_HPP__
#define __RD12123_FACTORY_HPP__

#include <iostream>
#include <unordered_map> //unordered map
#include <functional>    //std::function
#include <exception>     //exception

namespace ilrd
{
    template <class Base, class Key, class Args>
    class Factory
    {
    public:
        void Add(const Key &key, Base *(*creator)(const Args &));
        Base *Create(const Key &key, const Args &args) const;

        class KeyDuplicateException : public std::exception
        {
        public:
            virtual const char *what() const noexcept;
        };

        class KeyDoesntExistException : public std::exception
        {
        public:
            virtual const char *what() const noexcept;
        };

    private:
        std::unordered_map<Key, Base *(*)(const Args &)> m_creation_funcs;
    };

    template <class Base, class Key, class Args>
    void Factory<Base, Key, Args>::Add(const Key &key, Base *(*creator)(const Args &))
    {
        if (m_creation_funcs.find(key) != m_creation_funcs.end())
        {
            throw Factory<Base, Key, Args>::KeyDuplicateException();
        }
        m_creation_funcs[key] = creator;
    }

    template <class Base, class Key, class Args>
    Base *Factory<Base, Key, Args>::Create(const Key &key, const Args &args) const
    {
        if (m_creation_funcs.find(key) == m_creation_funcs.end())
        {
            throw Factory<Base, Key, Args>::KeyDoesntExistException();
        }

        return m_creation_funcs.at(key)(args);
    }

    template <class Base, class Key, class Args>
    const char *Factory<Base, Key, Args>::KeyDuplicateException::what() const noexcept
    {
        return "DuplicateKeyException";
    }

    template <class Base, class Key, class Args>
    const char *Factory<Base, Key, Args>::KeyDoesntExistException::what() const noexcept
    {
        return "KeyDoesntExistException";
    }
}

#endif //__RD12123_FACTORY_HPP__

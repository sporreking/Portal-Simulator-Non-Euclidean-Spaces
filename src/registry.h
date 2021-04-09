#pragma once

#include <iostream>
#include <map>

#include "buttons.h"

template <typename T>
class Registry {
   public:
    // The class may only be instantiated by friends
    Registry<T>() = delete;

    // Puts a value into the registry
    Registry<T>* put(std::string const& name, T* val) {
        if (_bank.count(name)) {
            std::cerr << "There is already an entry with name \"" << name << "\" in this registry" << std::endl;
            throw -1;
        }

        _bank[name] = val;
        return this;
    }

    // Fetches the entry with the specified name from the registry (returns 'nullptr' if there is no match)
    T* get(std::string const& name) const {
        if (!_bank.count(name))
            return nullptr;

        return _bank.at(name);
    }

   private:
    // The passed function will be called with this registry, and is supposed to populate it.
    Registry<T>(void (*init)(Registry<T>*)) {
        init(this);
    }

    // Delete values from registry
    ~Registry<T>() {
        for (auto&& v : _bank)
            delete v.second;
    }

    // Registry container
    std::map<std::string, T*> _bank;

    // May only be instantiated by class REG in 'registries.h'
    friend class REG;
};
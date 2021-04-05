template <typename T>
size_t Entity::numComponents() {
    size_t count{0};

    for (auto&& c : _components)
        if (dynamic_cast<T*>(c))
            count++;

    return count;
}

template <typename T>
T* Entity::getComponent() {
    for (auto&& c : _components)
        if (dynamic_cast<T*>(c))
            return dynamic_cast<T*>(c);

    return nullptr;
}

template <typename T>
std::vector<T*> Entity::getComponents() {
    std::vector<T*> comps;

    for (auto&& c : _components)
        if (dynamic_cast<T*>(c))
            comps.push_back(dynamic_cast<T*>(c));

    return comps;
}
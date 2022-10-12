#pragma once
#include <iostream>
#include <cstdint> // For int64_t

namespace entity_component_system {

struct EntityID {
    // The id is a 64-bit integer.
    typedef int64_t IDType;
    // Instance variable holding the actual ID, initialized to -1.
    IDType id{-1};
    // Construct this object with the actual ID.
    EntityID( IDType val ) : id(val) {}
    // We still want the default constructor.
    EntityID() = default;
    
    // This EntityID can convert itself to an int64_t on demand.
    operator IDType() { return id; }
    
    // This EntityID supports `.Get<Component>()`
    // The definition for this function declaration is below, since it uses the global ECS that hasn't been declared yet.
    template <typename T>
    T& Get();
};

struct ECS {
    template <typename T>
    T& Get( EntityID ) { 
        return GetAppropriateSparseSet<T>()[ entity ];
    }
};

template <typename T> T& EntityID::Get() { return ecs.Get<T>(*this); }

}
#pragma once
#include <iostream>
#include <cstdint> // For int64_t

namespace ecs {

struct EntityID {
    
    typedef int64_t IDType;
    
    IDType id{-1};
    
    EntityID( IDType val ) : id(val) {}
    
    EntityID() = default;
    
    operator IDType() { return id; }
    
    template <typename T>
    T& Get();
};

class ECS {
    public:
        EntityID Create();
        void Destroy( EntityID e );

        template< typename T >
        T& Get(EntityID e) {
            return GetAppropriateSparseSet<T>()[ entity ];
        };

};

inline ECS ecs;

template <typename T> T& EntityID::Get() { return ecs.Get<T>(*this); }

}
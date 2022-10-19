#pragma once
#include <iostream>
#include <cstdint> // For int64_t
#include <typeindex>

#include <unordered_map>
using namespace std;

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

struct SparseSetHolder {
    // A virtual destructor, since we store pointers to this superclass yet have subclasses with destructors that need to run.
    virtual ~SparseSetHolder() = default;
    virtual bool Has( EntityID ) const = 0;
    virtual void Drop( EntityID ) = 0;
};

// Subclasses are templated on the component type they hold.
template< typename T > struct SparseSet : SparseSetHolder {
    std::unordered_map< EntityID, T > data;
    bool Has( EntityID e ) const override { return data.count( e ) > 0; };
    void Drop( EntityID e ) override { data.erase( e ); };
};
// template <typename T>
//std::unordered_map< std::type_index, SparseSetHolder::SparseSetHolder() > m_components;

class ECS {

    std::vector< std::unique_ptr< SparseSetHolder > > m_components;
    typedef int ComponentIndex;

    public:
        EntityID Create()
        {
            EntityID id;
            return id;
        };
        void Destroy( EntityID e )
        {
            for( const auto& comps : m_components ) { comps->Drop( e ); }
        };

        template< typename T >
        T& Get(EntityID entity) {
            return GetAppropriateSparseSet<T>()[ entity ];
        };

        // template <typename T>
        // T& Get( EntityID ) { static T val{}; return val; }

        // template< typename... EntitiesThatHaveTheseComponents >
        // void ForEach( callback );

        
        template<typename T> ComponentIndex GetComponentIndex() {
            static ComponentIndex index = GetNextIndex(); // Only calls GetNextIndex() the first time this function is called.
            return index;
        }
        ComponentIndex GetNextIndex() {
            static ComponentIndex index = -1; // Returns the sequence 0, 1, 2, ... every time this is called.
            index += 1;
            return index;
        }

        template< typename T > std::unordered_map< EntityID, T > GetAppropriateSparseSet() {
        // Get the index for T’s SparseSet
        const ComponentIndex index = GetComponentIndex<T>();
        // If we haven’t seen it yet, it must be one past the end. Create the sparse set.
        if( index >= m_components.size() ) { m_components.push_back( std::make_unique< SparseSet<T> >() ); }
        assert( index < m_components.size() );
        // It’s safe to cast the SparseSetHolder to its subclass and return the std::unordered_map< EntityID, T > inside.
        return static_cast< SparseSet<T>& >( *m_components[ index ] ).data;    
    }   

};

    // template <typename T>
    // std::unordered_map< EntityID,  T > umap;

    inline ECS ecs;
    template <typename T> T& EntityID::Get() { return ecs.Get<T>(*this); }

}

// #pragma once

// #include <iostream>
// #include <vector>
// #include <memory>
// #include <algorithm>
// #include <bitset>
// #include <array>


// namespace ecs {

// class Component;
// class Entity;

// using ComponentID = std::size_t;

// inline ComponentID getComponentID()
// {
//     static ComponentID lastID = 0;
//     return lastID++;
// }

// template <typename T> inline ComponentID getComponentID() noexcept
// {
//     static ComponentID typeID = getComponentID();
//     return typeID;
// }

// constexpr std::size_t maxComponents = 32;

// using ComponentBitSet = std::bitset<maxComponents>;
// using ComponentArray = std::array<Component*, maxComponents>;

// class Component
// {
// public:
//     Entity* entity;

//     virtual void init() {}
//     virtual void update() {}
//     virtual void draw() {}

//     virtual ~Component() {}
// };

// class Entity
// {
// private:
//     bool active = true;
//     std::vector<std::unique_ptr<Component>> components;

//     ComponentArray componentArray;
//     ComponentBitSet componentBitSet;

// public:
//     void update()
//     {
//         for ( auto& c : components ) c->update();
//         for ( auto& c: components ) c->draw();
//     }

//     void draw() {}
//     bool isActive() const { return active; }
//     void destroy() { active = false; }

//     template <typename T> bool hasComponentID() const
//     {
//         return componentBitSet[getComponentID<T>];
//     }

//     template <typename T, typename... TArgs>
//     T& addComponent(TArgs&&... mArgs)
//     {
//         T* c(new T(std::forward<TArgs>(mArgs)...));
//         c->entity = this;
//         std::unique_ptr<Component> uPtr{ c };
//         components.emplace_back(std::move(uPtr));

//         componentArray[getComponentTypeID<T>()] = c;
//         componentBitSet[getComponentTypeID<T>()] = true;

//         c->init();
//         return *c;
//     }

//     template<typename T> T& getComponent() const
//     {
//         auto ptr(componentArray[getComponentTypeID<T>()]);
//         return *static_cast<T*>(ptr);
//     }

//     // gameobject.getComponent<PositionComponent>().setXpos(25);
// };

// class Manager
// {
// private:
//     std::vector<std::unique_ptr<Entity>> entities;

// public:
//     void update()
//     {
//         for (auto& e : entities) e->update();
//     }

//     void draw()
//     {
//         for (auto& e : entities) e->draw();
//     }

//     void refresh()
//     {
//         entities.erase(std::remove_if(std::begin(entities), std::end(entities),
//             [](const std::unique_ptr<Entity> &mEntity)
//         {
//             return !mEntity->isActive();
//         }),
//             std::end(entities));
//     }

//     Entity& addEntity()
//     {
//         Entity* e = new Entity();
//         std::unique_ptr<Entity> uPtr{ e };
//         entities.emplace_back(std::move(uPtr));
//         return *e;
//     }
// };

// }

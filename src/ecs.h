#pragma once
#include <functional>
#include <iostream>
#include <cstdint> // For int64_t
#include <typeindex>

#include <unordered_map>
using namespace std;

namespace ecs {

    // typedef long EntityID;

	// class ECS {
	// 	class SparseSetHolder {
	// 	public:
	// 		// A virtual destructor, since we store pointers to this superclass yet have subclasses with destructors that need to run.
	// 		virtual ~SparseSetHolder() = default;
	// 		virtual bool Has(EntityID) const = 0;
	// 		virtual void Drop(EntityID) = 0;
	// 	};
	// 	// Subclasses are templated on the component type they hold.
	// 	template< typename T > class SparseSet : public SparseSetHolder {
	// 	public:
	// 		std::unordered_map< EntityID, T > data;
	// 		bool Has(EntityID e) const override { return data.count(e) > 0; };
	// 		void Drop(EntityID e) override { data.erase(e); };
	// 	};

	// 	std::vector< std::unique_ptr< SparseSetHolder > > m_components;

	// 	std::vector<EntityID> recycleableIDs;
	// 	std::vector<EntityID> activeIDs;
	// 	inline static EntityID entities = 0;

	// 	template<typename T>
	// 	bool vecContains(std::vector<T> vec, T thing) {
	// 		int x;
	// 		for (x = 0; x < vec.size(); x++) {
	// 			if (vec[x] == thing) {
	// 				return true;
	// 			}
	// 		}
	// 		return false;
	// 	}

	// 	typedef int ComponentIndex;

	// 	ComponentIndex GetNextIndex() {
	// 		static ComponentIndex index = -1; // Returns the sequence 0, 1, 2, … every time this is called.
	// 		index += 1;
	// 		return index;
	// 	}

	// 	template<typename T>
	// 	ComponentIndex GetComponentIndex() {
	// 		static ComponentIndex index = GetNextIndex(); // Only calls GetNextIndex() the first time this function is called.
	// 		return index;
	// 	}

	// 	template< typename T >
	// 	std::unordered_map< EntityID, T >& GetAppropriateSparseSet() {
	// 		// Get the index for T’s SparseSet
	// 		const ComponentIndex index = GetComponentIndex<T>();
	// 		// If we haven’t seen it yet, it must be past the end.
	// 		// Since component indices are shared by all ECS instances,
	// 		// it could happen that index is more than one past the end.
	// 		if (index >= m_components.size()) { m_components.resize(index + 1); }
	// 		assert(index < m_components.size());
	// 		// Create the actual sparse set if needed.
	// 		if (m_components[index] == nullptr) m_components[index] = std::make_unique< SparseSet<T> >();
	// 		// It’s safe to cast the SparseSetHolder to its subclass and return the std::unordered_map< EntityID, T > inside.
	// 		return static_cast<SparseSet<T>&>(*m_components[index]).data;
	// 	}
		
	// public:
	// 	EntityID Create() {
	// 		EntityID newID;
	// 		if (recycleableIDs.size() != 0) {
	// 			newID = recycleableIDs.back();
	// 			recycleableIDs.pop_back();
	// 			return newID;
	// 		}
	// 		else {
	// 			newID = entities;

	// 			while (vecContains(activeIDs, newID)) {
	// 				newID = entities++;
	// 			}
	// 		}

	// 		activeIDs.push_back(newID);
	// 		return newID;
	// 	}

	// 	template<typename T>
	// 	T& Get(EntityID entity) {
	// 		return GetAppropriateSparseSet<T>()[entity];
	// 	}


	// 	void Destroy(EntityID e) {
	// 		if (!vecContains(activeIDs, e)) {
	// 			return;
	// 		}
	// 		// Destroy the entity by removing all components.
	// 		for (const auto& comps : m_components) { comps->Drop(e); }


	// 		recycleableIDs.push_back(e);
	// 	}

	// 	// Returns true if the entity has all types.
	// 	template <typename T, typename... Rest>
	// 	bool HasAll(EntityID entity) {
	// 		bool result = true;
	// 		// https://stackoverflow.com/questions/48405482/variadic-template-no-matching-function-for-call/48405556#48405556
	// 		if constexpr (sizeof...(Rest) > 0) { result = HasAll<Rest...>(entity); }
	// 		return result && GetAppropriateSparseSet<T>().count(entity) > 0;
	// 	}

	// 	typedef std::function<void(EntityID)> ForEachCallback;
	// 	template<typename EntitiesThatHaveThisComponent, typename... AndAlsoTheseComponents>
	// 	void ForEach(const ForEachCallback& callback) {
	// 		// Iterate over elements of the first container.
	// 		auto& container = GetAppropriateSparseSet<EntitiesThatHaveThisComponent>();
	// 		for (const auto& [entity, value] : container) {
	// 			// We know it has the first component.
	// 			// Skip the entity if it doesn't have the remaining components.
	// 			// This `if constexpr` is evaluated at compile time. It is needed when AndAlsoTheseComponents is empty.
	// 			// https://stackoverflow.com/questions/48405482/variadic-template-no-matching-function-for-call/48405556#48405556
	// 			if constexpr (sizeof...(AndAlsoTheseComponents) > 0) {
	// 				if (!HasAll<AndAlsoTheseComponents...>(entity)) {
	// 					continue;
	// 				}
	// 			}
	// 			callback(entity);
	// 		}
	// 	}
	// };

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
    std::unordered_map< int64_t , T > data;
    bool Has( EntityID e ) const override { return data.count( e.id ) > 0; };
    void Drop( EntityID e ) override { data.erase( e.id ); };
};
// template <typename T>
//std::unordered_map< std::type_index, SparseSetHolder::SparseSetHolder() > m_components;

class ECS {

    std::vector< std::unique_ptr< SparseSetHolder > > m_components;
    typedef int ComponentIndex;

    public:

        int64_t i_var = 0;
        
        EntityID Create()
        {
            EntityID id = EntityID(i_var++);
            return id;
        };
        
        void Destroy( EntityID e )
        {
            for( const auto& comps : m_components ) { comps->Drop( e ); }
        };

        template< typename T >
        T& Get(EntityID entity) {

            // cout << "ID A " << entity << "\n";
            // cout << "ID B " << entity.id << "\n";
            // static T e =  GetAppropriateSparseSet<T>()[ entity ];

            T& e =  GetAppropriateSparseSet<T>()[ entity ];

            //cout << "AFTER " << &GetAppropriateSparseSet<T>()[ entity ] << "\n";

            //return GetAppropriateSparseSet<T>()[ entity ];

            return e;
        };

        // template <typename T>
        // T& Get( EntityID ) { static T val{}; return val; }

        // template< typename... EntitiesThatHaveTheseComponents >
        // void ForEach( callback );

        
        template<typename T> 
        ComponentIndex GetComponentIndex() {
            static ComponentIndex index = GetNextIndex(); // Only calls GetNextIndex() the first time this function is called.
            // cout << "INDEX " << index << "\n";
            return index;
        }
        
        ComponentIndex GetNextIndex() {
            static ComponentIndex index = -1; // Returns the sequence 0, 1, 2, ... every time this is called.
            index += 1;
            return index;
        }

        template< typename T > 
        std::unordered_map< int64_t , T >& GetAppropriateSparseSet() {

        // Get the index for T’s SparseSet
        const ComponentIndex index = GetComponentIndex<T>();
        
        // If we haven’t seen it yet, it must be one past the end. Create the sparse set.
        if( index >= m_components.size() ) 
        { 
            m_components.push_back( std::make_unique< SparseSet<T> >() ); 
        }
        
        assert( index < m_components.size() );

        // It’s safe to cast the SparseSetHolder to its subclass and return the std::unordered_map< EntityID, T > inside.
        std::unordered_map< int64_t , T >& e = static_cast< SparseSet<T>& >( *m_components[ index ] ).data;

        return e;   
    }   

    typedef std::function<void( EntityID )> ForEachCallback;
    template<typename EntitiesThatHaveThisComponent, typename... AndAlsoTheseComponents>
    void ForEach( const ForEachCallback& callback ) {
        // Iterate over elements of the first container.
        auto& container = GetAppropriateSparseSet<EntitiesThatHaveThisComponent>();

        cout << "size " << m_components.size() << "\n";

        for( const auto& [entity, value] : container ) {
            // We know it has the first component.
            // Skip the entity if it doesn't have the remaining components.
            // This `if constexpr` is evaluated at compile time. It is needed when AndAlsoTheseComponents is empty.
            // https://stackoverflow.com/questions/48405482/variadic-template-no-matching-function-for-call/48405556#48405556

            if constexpr (sizeof...(AndAlsoTheseComponents) > 0) {
                if( !HasAll<AndAlsoTheseComponents...>( entity ) ) {
                    continue;
                }
            }
            callback( entity );
        }
    }

    // Returns true if the entity has all types.
    template <typename T, typename... Rest>
    bool HasAll( EntityID entity ) {
        bool result = true;
        // https://stackoverflow.com/questions/48405482/variadic-template-no-matching-function-for-call/48405556#48405556
        if constexpr (sizeof...(Rest) > 0) { result = HasAll<Rest...>(entity); }
        return result && GetAppropriateSparseSet<T>().count( entity ) > 0;
    }

};

    // template <typename T>
    // std::unordered_map< EntityID,  T > umap;

    inline ECS ecs;
    template <typename T> T& EntityID::Get() { return ecs.Get<T>(*this); }

}

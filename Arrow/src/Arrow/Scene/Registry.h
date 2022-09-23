#pragma once

#include "Arrow/Core/Core.h"

#include <unordered_map>
#include <queue>

namespace {
	//Reference to component class (exists in Component.h)
	class Component;

	//Helper component
	struct ComponentStorage {
		std::unordered_map<uint32_t, Component> m_Storage;
	};     

	class ComponentManager {
	public:

		~ComponentManager() {
			//Clear up the component storages
			for(auto st : m_Storage)
				delete &st;
		}

		template<typename T>
		T& AddComponent(T& component, uint32_t& entity) {
			//Getting the component type in order to proccess it
			std::string type = typeid(T).name;

			//Checking whether the component storage exists
			//If it does, check if entity already has a component (do nothing) or create one
			if(m_Storage.find(type) != m_Storage.end()) {
				ComponentStorage& componentStorage = m_Storage.at(type);
				if(componentStorage.count(entity))
					AR_ERROR("{0} alraedy exists at {1}", type, entity);
				else
					componentStorage[entity] = component;
			//If component storage doesn't exist create one in the heap and the component
			} else {
				m_Storage.at(type) = new ComponentStorage;
				ComponentStorage& componentStorage = m_Storage.at(type);
				componentStorage[entity] = component;
			}

			return component;
		}

		//TODO : RemoveComponent

		template<typename T>
		T& GetComponent(uint32_t& id) {
			//Getting the component type in order to proccess it
			std::string type = typeid(T).name;

			//Checking whether the component storage exists
			//If it does, find and return the entity else return nullptr
			if(m_Storage.find(type) != m_Storage.end()) {
				ComponentStorage& componentStorage = m_Storage.at(type);
				if(componentStorage.count(id))
					return componentStorage.at(id);
			}

			//TODO : fix logging
			AR_ERROR("Entity {0} doesn't have component");
			return nullptr;
		}

		template<typename T>
		bool HasComponent(T& component, uint32_t& id) {
			//Getting the component type in order to proccess it
			std::string type = typeid(T).name;

			//Checking whether the component storage exists
			//If it does, check if entity has a component
			if(m_Storage.find(type) != m_Storage.end()) {
				ComponentStorage& componentStorage = m_Storage.at(type);
				return componentStorage.count(id);
			}

			//If it doesn't return false
			return false;
		}
	private:
		std::unordered_map<std::string, ComponentStorage> m_Storage;
	};

	class Registry {
	public:
		uint32_t CreateEntityID() {
			static uint32_t nextID = 0;
			uint32_t id;
			//Check if there are any non used deleted entity ids to give
			if(!m_DestroyedIDs.empty()) {
				id = m_DestroyedIDs.front();
				m_DestroyedIDs.pop();
			//If not give next ID in line
			} else {
				id = nextID;
				nextID++;
			}
			return id;
		}

		void DeleteEntityID(uint32_t& id) {
			//TODO : delete every component with that ID
			//TODO : add id to the queue
		}

		template<typename T>
		T& AddComponent(T& component, uint32_t& entity) {
			m_ComponentManager.AddComponent(component, entity);
		}

		//TODO : RemoveComponent

		template<typename T>
		T& GetComponent(uint32_t& entity) {
			return m_ComponentManager.GetComponent(id);
		}

		template<typename T>
		bool HasComponent(T& component, uint32_t& entity) {
			m_ComponentManager.HasComponent(component, entity);
		}
	private:
		std::queue<uint32_t> m_DestroyedIDs;
		ComponentManager m_ComponentManager;
	};

}
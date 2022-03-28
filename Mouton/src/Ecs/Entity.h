#ifndef ENTITY_H
#define ENTITY_H

#include "Components.h"
#include "MoutonPch.h"

namespace Mouton {

    class Entity
    {
      public:
        Entity(const std::string& name, uint32_t id);
        Entity(const std::string& name); // If this constructor is being called
                                         // the ID must be set after !

        void SetID(uint32_t id) { m_ID = id; };
        void SetName(const std::string& name) { m_Name = name; };
        uint32_t GetID() const { return m_ID; };
        const std::string& GetName() const { return m_Name; };

      private:
        uint32_t m_ID;
        std::string m_Name;
    };

} // namespace Mouton

#endif
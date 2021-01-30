#ifndef LAYER_H
#define LAYER_H

#include "MoutonPch.h"
#include "Core/Timestep.h"
#include "Renderer/Window.h"

namespace Mouton
{

    class Layer
    {
    public:
        Layer(const char* name = "Layer");
        virtual ~Layer() = default;
        std::string& GetName() { return m_Name; };

        virtual void OnBind()   = 0;
        virtual void OnUpdate(Timestep delta) = 0;
        virtual void OnUnbind() = 0;
        virtual bool OnEvent(Event& event)  = 0;
        virtual void OnRender() = 0;
    
    protected:
        std::string m_Name;
    };

} // namespace Mouton


#endif
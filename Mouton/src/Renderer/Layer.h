#ifndef LAYER_H
#define LAYER_H

#include "MoutonPch.h"
#include "Renderer/Window.h"

namespace Mouton
{

    class Layer
    {
    public:
        Layer(const char* name = "Layer");
        std::string& GetName() { return m_Name; };

        virtual void OnBind()   = 0;
        virtual void OnUpdate() = 0;
        virtual void OnUnbind() = 0;
        virtual bool OnEvent(Event& event)  = 0;
    
    protected:
        std::string m_Name;
    };

} // namespace Mouton


#endif
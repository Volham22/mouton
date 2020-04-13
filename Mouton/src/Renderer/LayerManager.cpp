#include "LayerManager.h"

namespace Mouton
{
    LayerManager::LayerManager()
    :   m_Layers()
    {
    }

    void LayerManager::AddLayer(Layer* layer)
    {
        m_Layers.push_back(layer);
    }

    bool LayerManager::RemoveLayer(Layer* layer)
    {
        auto target = std::find(m_Layers.begin(), m_Layers.end(), layer);

        if(target != m_Layers.end())
        {
            m_Layers.erase(target);
            return true;
        }
        else
            return false;
    }

    void LayerManager::UpdateLayers()
    {
        for(Layer* l : m_Layers)
            l->OnUpdate();
    }

    bool LayerManager::OnLayersEvent(Event& event)
    {
        auto it = m_Layers.begin();

        while(it != m_Layers.end() && !event.Handled())
        {
            (*it)->OnEvent(event);
            it++;
        }

        return event.Handled();
    }

    LayerManager::~LayerManager()
    {
        for(Layer* l : m_Layers)
            delete l;
    }

} // namespace Mouton

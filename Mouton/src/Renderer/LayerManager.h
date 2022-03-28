#ifndef LAYER_MANAGER_H
#define LAYER_MANAGER_H

#include "Core/Timestep.h"
#include "MoutonPch.h"

#include "Layer.h"

namespace Mouton {

    class LayerManager
    {
      public:
        LayerManager();
        ~LayerManager();

        void AddLayer(Layer* layer);
        bool RemoveLayer(Layer* layer);
        void UpdateLayers();
        bool OnLayersEvent(Event& event);

      private:
        std::vector<Layer*> m_Layers;
        Chrono m_Chrono;
    };

} // namespace Mouton

#endif
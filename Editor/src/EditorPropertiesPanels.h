#ifndef EDITOR_PROPERTIES_PANELS_H
#define EDITOR_PROPERTIES_PANELS_H

#include "MoutonComponents/TransformComponent.h"
#include "MoutonComponents/Material2DComponent.h"

class EditorPropertiesPanels
{
public:
    static void ShowTransformComponent(Mouton::TransformComponent* transformComponent);
    static void ShowMaterial2DComponent(Mouton::Material2DComponent* materialComponent);
};

#endif
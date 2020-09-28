import Mouton
import time
import math

class RedSpriteScript(Mouton.SpriteComponent):
    def __init__(self):
        Mouton.SpriteComponent.__init__(self, "SpriteComponent")
        self.color = Mouton.Vector4(0.5, 0.8, 0.2, 1.0)
        self.scale = Mouton.Vector2(3.0, 5.0)
        self.position = Mouton.Vector3(50.0)
        self.position.z = 0.0
        self.frame = 0.0

    """
    Call once when the scene begin (not implemented in the Engine yet)
    """
    def OnBegin(self):
        pass

    """
    Called when RedSprite is being updated
    Parameters:
        Timestep delta : the actual frametime
    """
    def OnUpdate(self, delta):

        incX = delta * math.cos(self.frame) * 10.0
        incY = delta * math.sin(self.frame) * 10.0
        
        self.position.x += incX
        self.position.y += incY
        self.scale.x += incX
        self.scale.y += incY

        self.frame += delta.GetSeconds()

    """
    Called once when the Scene end (not implemented in the Engine yet)
    """
    def OnEnd(self):
        pass
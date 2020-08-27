import Mouton
import time
import math

class RedSprite(Mouton.SpriteComponent):
    def __init__(self):
        Mouton.SpriteComponent.__init__(self, "SpriteComponent")
        self.color = Mouton.Vector4(0.5, 0.8, 0.2, 1.0)
        self.scale = Mouton.Vector2(3.0, 5.0)
        self.position = Mouton.Vector3(50.0)
        self.position.z = 0.0
        self.time = time.time()
        self.frame = 0.0

    def OnBegin(self):
        pass

    def OnUpdate(self):
        elapsed = time.time() - self.time
        self.time = time.time()

        incX = math.cos(self.frame) * elapsed * 10
        incY = math.sin(self.frame) * elapsed * 10
        
        self.position.x += incX
        self.position.y += incY
        self.scale.x += incX
        self.scale.y += incY

        self.frame += elapsed

    def OnEnd(self):
        pass
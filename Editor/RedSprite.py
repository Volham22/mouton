import Mouton
import time
import math

class RedSprite(Mouton.SpriteComponent):
    def __init__(self):
        Mouton.SpriteComponent.__init__(self, "SpriteComponent")
        self.scale = Mouton.Vector2(3.0)
        self.position = Mouton.Vector3(50.0)
        self.position.z = 0.0
        self.time = time.time()
        self.frame = 0.0

    def OnBegin(self):
        pass

    def OnUpdate(self):
        elapsed = time.time() - self.time
        self.time = time.time()
        
        self.position.x += math.cos(self.frame) * elapsed * 10
        self.position.y += math.sin(self.frame) * elapsed * 10

        self.frame += elapsed

    def OnEnd(self):
        pass
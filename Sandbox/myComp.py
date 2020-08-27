import Mouton
from datetime import datetime

class myComp(Mouton.SpriteComponent):
    def __init__(self):
        Mouton.SpriteComponent.__init__(self, "myComp")

    def OnBegin(self):
        print("Called OnBegin !")

    def OnUpdate(self):
        print("Called OnUpdate !")
        self.color.x += 0.001

        if self.color.x >= 1.0:
            self.color.x = 0.0

    def OnEnd(self):
        print("Called on end !")
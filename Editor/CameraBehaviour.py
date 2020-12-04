import Mouton
from math import sin, cos

# Your additionnal imports goes here ...

class CameraBehaviour(Mouton.OrthographicCameraComponent):
    def __init__(self, cameraController):
        Mouton.OrthographicCameraComponent.__init__(self, "CameraBehaviourComponent", cameraController)
        # Your members initialisation goes here ...

    """
    Call once when the scene begin (not implemented in the Engine yet)
    """
    def OnBegin(self):
        pass

    """
    Called when CameraBehaviour is being updated by Mouton.
    This is usually called before each new frame.
    Parameters:
        Timestep delta : the actual frametime
    """
    def OnUpdate(self, delta):
        move = Mouton.Vector3(0.1, 0.1, 0.0)
        # self.Move(move)
        # self.Rotate(1.0)

    """
    Called once when the Scene end (not implemented in the Engine yet)
    """
    def OnEnd(self):
        pass

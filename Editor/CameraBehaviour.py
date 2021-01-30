import Mouton
from math import sin, cos

# Your additionnal imports goes here ...

class CameraBehaviour(Mouton.OrthographicCameraComponent):
    def __init__(self, cameraController):
        Mouton.OrthographicCameraComponent.__init__(self, "CameraBehaviourComponent", cameraController)
        self.m_FrameCount = 0.0

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
        #move = Mouton.Vector3(cos(self.m_FrameCount * delta.GetSeconds()),
        #    sin(self.m_FrameCount * delta.GetSeconds()), 0.0) * 5
        #self.Translate(move)

        self.m_FrameCount += 0.1

    """
    Called once when the Scene end (not implemented in the Engine yet)
    """
    def OnEnd(self):
        pass

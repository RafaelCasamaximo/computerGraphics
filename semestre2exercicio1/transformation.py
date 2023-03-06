import math
import numpy as np

"""
Overall, the Transformation class provides a convenient and efficient way to
perform common 2D coordinate transformations in a programmatic manner.
"""
class Transformation:
    
    """
    The class constructor __init__ initializes the transformation matrix to the
    identity matrix and sets the origin of the coordinate system to (0,0) by default.
    The origin can be set to a different value by passing in a different list of [x, y] coordinates.
    You can change the origin of the following transformation using [object].origin = [new point]
    """
    def __init__(self, origin=[0, 0]):
        self.matrix = np.identity(3)
        self.origin = origin
        
    """
    The translate method moves all points in the coordinate system by adding
    the translation values tx and ty to the x and y coordinates respectively.
    It achieves this by multiplying the current transformation matrix with a
    translation matrix and updating the transformation matrix to the resulting matrix.
    """
    def translate(self, tx, ty):
        translate_matrix = np.array([[1, 0, tx], [0, 1, ty], [0, 0, 1]])
        self.matrix = np.matmul(translate_matrix, self.matrix)
    
    """
    The scale method scales all points in the coordinate system by a factor of
    sx in the x-direction and sy in the y-direction. It first moves the
    coordinate system so that the origin is at (0,0), then scales the coordinate
    system using a scaling matrix, and finally moves the coordinate system back
    to its original position.
    """
    def scale(self, sx, sy):
        self.translate(-self.origin[0], -self.origin[1])
        scale_matrix = np.array([[sx, 0, 0], [0, sy, 0], [0, 0, 1]])
        self.matrix = np.matmul(scale_matrix, self.matrix)
        self.translate(self.origin[0], self.origin[1])
    
    """
    The rotate method rotates all points in the coordinate system by an angle
    specified in radians. It achieves this by moving the coordinate system so
    that the origin is at (0,0), rotating the coordinate system using a rotation
    matrix, and moving the coordinate system back to its original position.
    """
    def rotate(self, angle):
        self.translate(-self.origin[0], -self.origin[1])
        rotate_matrix = np.array([[math.cos(angle), -math.sin(angle), 0], [math.sin(angle), math.cos(angle), 0], [0, 0, 1]])
        self.matrix = np.matmul(rotate_matrix, self.matrix)
        self.translate(self.origin[0], self.origin[1])

    """
    The shear method shears all points in the coordinate system by a factor of sx
    in the x-direction and sy in the y-direction. It achieves this by moving the
    coordinate system so that the origin is at (0,0), shearing the coordinate system
    using a shear matrix, and moving the coordinate system back to its original position.
    """  
    def shear(self, sx, sy):
        self.translate(-self.origin[0], -self.origin[1])
        shear_matrix = np.array([[1, sx, 0], [sy, 1, 0], [0, 0, 1]])
        self.matrix = np.matmul(shear_matrix, self.matrix)
        self.translate(self.origin[0], self.origin[1])
        
    """
    The mirror method reflects all points in the coordinate system across a specified axis.
    The axis can be either "x" or "y", or one of two diagonal axes, "y=x" or "y=-x".
    It achieves this by multiplying the current transformation matrix with a mirror
    matrix corresponding to the specified axis.
    """
    def mirror(self, axis):
        if axis == 'x':
            mirror_matrix = np.array([[-1, 0, 0], [0, 1, 0], [0, 0, 1]])
        elif axis == 'y':
            mirror_matrix = np.array([[1, 0, 0], [0, -1, 0], [0, 0, 1]])
        elif axis == 'y=x':
            mirror_matrix = np.array([[0, 1, 0], [1, 0, 0], [0, 0, 1]])
        elif axis == 'y=-x':
            mirror_matrix = np.array([[0, -1, 0], [-1, 0, 0], [0, 0, 1]])
        else:
            raise ValueError('Invalid axis parameter. Must be "x" or "y".')
        self.matrix = np.matmul(mirror_matrix, self.matrix)

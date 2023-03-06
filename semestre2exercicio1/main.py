from transformation import Transformation

import math
import pprint

if __name__ == '__main__':

    """
    A list of points [x, y] that make up a figure
    """
    points = [
        [2, 2],
        [4, 2],
        [4, 4],
        [2, 4]
    ]

    """
    The transformation class allows composite transforms to be performed.
    Within the class, the matrix attribute stores the homogeneous matrix containing the result of all transformations performed.
    At the end, just multiply t.matrix @ point (The @ is the matrix multiplier operator in numpy).
    The parameter Transformation takes is a point [x, y] containing the origin point.
    If the point is not specified, the origin coordinates used will be [0, 0]
    """
    t = Transformation([2, 2])
    t.translate(5, 5)
    t.rotate(math.pi/4)
    t.scale(2.5, 2)
    t.shear(2, 1)

    """
    Iterates over all the points applying the transformation to each of them.
    """
    newPoints = []
    for point in points:
        newPoints.append(t.matrix @ [point[0], point[1], 1])

    """
    Prints the points on the screen in list format
    """
    pp = pprint.PrettyPrinter(indent=4)
    pp.pprint(newPoints)

    pass
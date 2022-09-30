import cv2
import sys
import numpy as np

def main(imgPath):
    bgrMat = cv2.imread(imgPath)

    # Transformação Discreta do Cosseno
    dctMat = discreteCosineTransform(bgrMat)

    # Transformação Inversa Discreta do Cosseno
    idctMat = inverseDiscreteCosineTransform(dctMat)

    pass

def discreteCosineTransform(bgrMat, channel):
    dctMat = np.zeros((bgrMat.size[0], bgrMat.size[1], 1), dtype = "uint8")
    for i in range(bgrMat.size[0]):
        for j in range(bgrMat.size[1]):

            pass
        pass
    pass

def inverseDiscreteCosineTransform(dctMat):
    pass

"""HELPERS"""
def discreteCosineTransformCalculation(pixelValue, pixelX, pixelY, alphaU, alphaV):
    pass


if __name__ == '__main__':
    main(sys.argv[1])
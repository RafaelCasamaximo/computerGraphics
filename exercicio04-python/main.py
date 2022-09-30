import cv2
from math import cos, pi, sqrt, pow
import numpy as np
import click


def dct_2d(image):
    
    height = image.shape[0]
    width = image.shape[1]
    imageRow = np.zeros_like(image).astype(float)
    imageCol = np.zeros_like(image).astype(float)

    for h in range(height):
        imageRow[h, :] = dct_1d(image[h, :])
    for w in range(width):
        imageCol[:, w] = dct_1d(imageRow[:, w])

    return imageCol

def dct_1d(image):
    
    n = len(image)
    newImage= np.zeros_like(image).astype(float)

  
    for k in range(n):
        sum = 0
        for i in range(n):
            sum += image[i] * cos(2 * pi * k / (2.0 * n) * i + (k * pi) / (2.0 * n))
        ck = sqrt(0.5) if k == 0 else 1
        newImage[k] = sqrt(2.0 / n) * ck * sum

    return newImage

def idct_2d(image):
    
    height = image.shape[0]
    width =  image.shape[1]
    imageRow = np.zeros_like(image).astype(float)
    imageCol = np.zeros_like(image).astype(float)

  
    for h in range(height):
        imageRow[h, :] = idct_1d(image[h, :])
    for w in range(width):
        imageCol[:, w] = idct_1d(imageRow[:, w])

    return imageCol

def idct_1d(image):
   
    n = len(image)
    newImage = np.zeros_like(image).astype(float)

    for i in range(n):
        sum = 0
        for k in range(n):
            ck = sqrt(0.5) if k == 0 else 1
            sum += ck * image[k] * cos(2 * pi * k / (2.0 * n) * i + (k * pi) / (2.0 * n))

        newImage[i] = sqrt(2.0 / n) * sum

    return newImage

def lowPassButterworthFilter(fImg, d0, n):
    height = fImg.shape[0]
    width = fImg.shape[1]
    imageRow = np.zeros((width, height, 3)).astype(float)

    for u in range(width):
        for v in range(height):
            for k in range(3):
                imageRow[u][v][k] = 1 / 1 + pow(distanceBetweenPoints(0, 0, u, v) / d0, 2 * n)
    return imageRow

def highPassButterworthFilter(fImg, d0, n):
    height = fImg.shape[0]
    width = fImg.shape[1]
    imageRow = np.zeros((width, height, 3)).astype(float)

    for u in range(1, width):
        for v in range(1, height):
            for k in range(3):
                imageRow[u][v][k] = 1 / 1 + pow(d0 / distanceBetweenPoints(0, 0, u, v), 2 * n)
    return imageRow

def applyFilter(fImg, filter):
    return fImg * filter

def distanceBetweenPoints(x1, y1, x2, y2):
    result = sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)))
    return result if result != 0 else 0.5

@click.command()
@click.option('--figure', '-f', help='Figure to apply the DCT.')
def cli(figure):

    if figure != None:
        dctImg = cv2.imread(figure)
        dct = dct_2d(dctImg)
        cv2.imwrite('outputDiscreteCosineTransform.jpg', dct)
        lpf = lowPassButterworthFilter(dct, 30, 1)
        lpImg = applyFilter(dct, lpf)
        cv2.imwrite('outputDiscreteCosineTransformLowFilter.jpg', lpImg)
        hpf = highPassButterworthFilter(dct, 70, 1)
        hpImg = applyFilter(dct, hpf)
        cv2.imwrite('outputDiscreteCosineTransformHighFilter.jpg', hpImg)
        idct = idct_2d(dct)
        cv2.imwrite('outputInverseDiscreteCosineTransform.jpg', idct)
        ilpImg = idct_2d(lpImg)
        cv2.imwrite('outputInverseDiscreteCosineTransformLowFIlter.jpg', ilpImg)
        ihpImg = idct_2d(hpf)
        cv2.imwrite('outputInverseDiscreteCosineTransformHighFilter.jpg', ihpImg)

	

if __name__ == '__main__':
    cli()
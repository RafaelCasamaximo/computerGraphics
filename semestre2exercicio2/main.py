import matplotlib.pyplot as plt

def bresenhan_retas(x0, y0, x1, y1):
    dx = abs(x1 - x0)
    dy = abs(y1 - y0)
    sx = 1 if x0 < x1 else -1
    sy = 1 if y0 < y1 else -1
    err = dx - dy

    points = []
    while x0 != x1 or y0 != y1:
        points.append((x0, y0))
        e2 = err * 2
        if e2 > -dy:
            err -= dy
            x0 += sx
        if e2 < dx:
            err += dx
            y0 += sy
    points.append((x0, y0))
    
    x, y = zip(*points)
    plt.scatter(x, y)
    plt.show()

def bresenhan_circunferencia(xc, yc, r):
    x = 0
    y = r
    d = 3 - 2 * r

    points = []
    while x <= y:
        points.append((xc + x, yc + y))
        points.append((xc + y, yc + x))
        points.append((xc - x, yc + y))
        points.append((xc - y, yc + x))
        points.append((xc + x, yc - y))
        points.append((xc + y, yc - x))
        points.append((xc - x, yc - y))
        points.append((xc - y, yc - x))

        x += 1
        if d < 0:
            d += 4 * x + 6
        else:
            d += 4 * (x - y) + 10
            y -= 1
    x, y = zip(*points)
    plt.scatter(x, y)
    plt.show()


if __name__ == '__main__':
    # Utiliza o Algoritmo de Bresenham para rasterizar e aproximar uma reta
    # Parâmetros: x0, y0, x1, y1
    bresenhan_retas(0, 1, 10, 5)

    # Utiliza o Algoritmo de Bresenham para rasterizar e aproximar uma circunferencia
    # Parâmetros: xc, yc, raio
    bresenhan_circunferencia(2, 3, 10)

    # Foi utilizado o matplotlib para marcar em azul no grid quais são os pontos resultantes do algoritmo
    # Os pontos azuis representam os pixeis aproximados pelo o algoritmo de acordo com a equação da reta ou circunferencia

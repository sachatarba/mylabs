import pygame


FPS = 30
WIN_WIDTH = 400
WIN_HEIGHT = 400
GREEN = (0, 255, 0)
WHITE = (255, 255, 255)
ORANGE = (255, 150, 100)
BLACK = (0, 0, 0)

clock = pygame.time.Clock()
sc = pygame.display.set_mode(
    (WIN_WIDTH, WIN_HEIGHT))

def draw_lol(screen, scale, position):
    r = 10
    pygame.draw.ellipse(screen, GREEN, (*position, 75 * scale, 50 * scale))
    pygame.draw.circle(screen, ORANGE,(position[0] + 75 * scale / 2, position[1] - r * scale), r * scale)

pos = [300, 200]
scale = 1

while 1:
    for i in pygame.event.get():
        if i.type == pygame.QUIT:
            pygame.quit()

    # заливаем фон
    sc.fill(WHITE)
    # рисуем круг
    pygame.draw.line(sc, BLACK,
                       (0, 300), (200, 300))
    pygame.draw.line(sc, BLACK,
                     (200, 300), (200, 350))
    pygame.draw.line(sc, BLACK,
                     (200, 350), (400, 350))
    pygame.draw.line(sc, BLACK, (50, 300), (50, 250))
    pygame.draw.polygon(sc, GREEN, ((25, 250), (75, 250), (50, 200)))
    pygame.draw.polygon(sc, GREEN, ((25, 250), (75, 250), (50, 200)))
    pygame.draw.polygon(sc, GREEN, ((25, 200), (75, 200), (50, 150)))
    pygame.draw.polygon(sc, GREEN, ((25, 150), (75, 150), (50, 100)))
    pygame.draw.polygon(sc, ORANGE, ((100, 300), (150, 300), (125, 250)))
    draw_lol(sc, scale, pos)

    pos[0] -= 1
    pos[1] -= 1
    scale -= 0.005
    # обновляем окно
    pygame.display.update()


    clock.tick(FPS)
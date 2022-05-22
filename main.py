import pygame as pg

BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
FPS = 60
WIDTH = 600
HEIGHT = 780


class Bg(pg.sprite.Sprite):
    def __init__(self, image_name, width, height):
        pg.sprite.Sprite.__init__(self)
        self.height = height
        self.width = width
        self.image = pg.image.load(image_name)
        self.rect = pg.Rect(0, 0, self.image.get_width(), self.image.get_height())

    def update(self):
        self.rect.x -= 2
        print(self.image.get_width(), self.width)
        if abs(self.rect.x) >= abs(self.image.get_width() - self.width):
            self.rect.x = 0


class Mob(pg.sprite.Sprite):
    def __init__(self, image_name, sprites_rows=1, sprites_cols=1):
        self.sprites_rows = sprites_rows
        self.sprites_cols = sprites_cols
        pg.sprite.Sprite.__init__(self)
        sprites_set = pg.image.load(image_name)
        sprites_set_size_x, sprites_set_size_y = sprites_set.get_size()
        # print(sprites_set.get_width())
        self.frame_size_x, self.frame_size_y = sprites_set_size_x // sprites_cols, sprites_set_size_y // sprites_rows
        self._animation_frames = []
        self._current_frames_set = 0
        self._current_frame = 0
        self._use_all_frames = False
        self._FPS = FPS
        self._ticks = 0
        self.rect = pg.Rect(0, 0, self.frame_size_x, self.frame_size_y)
        self.rect.center = (WIDTH / 2, HEIGHT / 2)

        for current_row in range(sprites_rows):
            for current_col in range(sprites_cols):
                self._animation_frames.append([])
                self._animation_frames[current_row].append(sprites_set.subsurface(
                    pg.Rect(current_col * self.frame_size_x, current_row * self.frame_size_y, self.frame_size_x,
                            self.frame_size_y)))
        # self.image = pg.image.load(image_name)
        self.image = self._animation_frames[0][0]
        # self.bear = pg.image.load("bear.png")
        # self.image = self.bear.subsurface(pg.Rect(0, 0, 2048 // 8, 2048 // 8))
        # print(self.frame_size_x, self.frame_size_y)

    def set_sprite(self, sprite):
        self.image = sprite

    def set_current_frames_set(self, current_set):
        self._current_frames_set = current_set - 1

    def set_FPS(self, FPS):
        self._FPS = FPS

    def set_position(self, x, y):
        self.rect.center = (x, y)

    def use_all_frames(self):
        self._use_all_frames = True
    # async def start_animation(self, timer):
    #     self._set_animation_status(True)
    #     current_frame = 0
    #     while self._is_animated:
    #         self.set_sprite(self._animation_frames[self._current_frames_set][current_frame])
    #         current_frame += 1
    #         current_frame %= len(self._animation_frames[self._current_frames_set])
    #         print(len(self._animation_frames[self._current_frames_set]), current_frame)
    #         timer.tick(self._FPS)

    # def end_animation(self):
    #     self._set_animation_status(True)
    def set_scale(self, in_x, in_y):
        # self.image = pg.transform.scale(self.image, (self.image.get_width() * in_x, self.image.get_height() * in_y))
        for i in range(len(self._animation_frames)):
            for j in range(len(self._animation_frames[i])):
                self._animation_frames[i][j] = pg.transform.scale(self._animation_frames[i][j], (self.image.get_width() * in_x, self.image.get_height() * in_y))
        self.image = self._animation_frames[self._current_frames_set][self._current_frame]
        self.rect = pg.Rect(self.rect.x, self.rect.y, self.image.get_width() * in_x, self.image.get_height() * in_y)


    def update(self):
        # timer = pg.time.Clock()
        self._ticks += 1
        self._ticks %= self._FPS
        if self._ticks == 0:
            if not self._use_all_frames:
                self._current_frame = (self._current_frame + 1) % len(self._animation_frames[self._current_frames_set])
                self.image = self._animation_frames[self._current_frames_set][self._current_frame]
            else:
            # pass
                self._current_frame += 1
                if (self._current_frame >= self.sprites_cols):
                    self._current_frame = 0
                    self._current_frames_set += 1
                    if (self._current_frames_set >= self.sprites_rows):
                        self._current_frames_set = 0
                self.image = self._animation_frames[self._current_frames_set][self._current_frame]
        self.image.set_colorkey(WHITE)
        # timer.tick(20)


def main():
    # Создаем игру и окно
    pg.init()
    pg.mixer.init()
    pg.mixer.music.load('fire.mp3')
    pg.mixer.music.play()
    screen = pg.display.set_mode((WIDTH, HEIGHT))
    pg.display.set_caption("My Game")
    clock = pg.time.Clock()
    all_sprites = pg.sprite.Group()
    bear = Mob("bear.png", 8, 8)
    bg = Bg("forest.png", WIDTH, HEIGHT)
    car = Mob("car.png", 1, 1)
    car.set_scale(0.7, 0.7)
    car.use_all_frames()
    car.set_FPS(1)
    car.set_position(WIDTH - WIDTH // 3.5 - 50, HEIGHT - HEIGHT // 8 - 55)
    explosion = Mob("flame0.png", 3, 4)
    # explosion.image.
    # explosion.image.set_colorkey(WHITE)
    bg.rect.y -= 40
    bear.set_position(WIDTH // 2 - WIDTH // 4, HEIGHT - HEIGHT // 5)
    explosion.set_scale(0.2, 0.2)
    explosion.set_position(WIDTH - WIDTH // 9 - 25, HEIGHT - HEIGHT // 5 - 55)
    # pchel = Mob("pchel.png", 8, 8)
    # stoler = Mob("stoler.png", 2, 3)
    # pchel.set_position(WIDTH // 2 + 128, HEIGHT // 2)
    # stoler.set_position(WIDTH // 2 - 128, HEIGHT // 2)
    bear.use_all_frames()
    # bear.set_current_frames_set(8)
    explosion.use_all_frames()
    bear.set_FPS(5)
    explosion.set_FPS(2)
    # pchel.use_all_frames()
    # stoler.use_all_frames()
    all_sprites.add(bg)
    all_sprites.add(bear)
    all_sprites.add(car)
    all_sprites.add(explosion)
    # car.update()
    # all_sprites.add(pchel)
    # all_sprites.add(stoler)

    # Цикл игры
    running = True
    timer = 0
    while running:
        # Держим цикл на правильной скорости
        clock.tick(FPS)
        # Ввод процесса (события)
        for event in pg.event.get():
            # check for closing window
            if event.type == pg.QUIT:
                running = False

        # Обновление
        all_sprites.update()
        # bear.start_animation(clock)
        # Рендеринг
        screen.fill(WHITE)
        all_sprites.draw(screen)
        # car.draw(screen)
        # После отрисовки всего, переворачиваем экран
        pg.display.flip()

        timer += 1

        if timer == 10 ** 3:
            break

    while bear.rect.x != car.rect.x and running:
        clock.tick(FPS)
        for event in pg.event.get():
            # check for closing window
            if event.type == pg.QUIT:
                running = False

        bear.rect.x += 1
        bear.set_current_frames_set(8)
        bear.update()
        explosion.update()
        all_sprites.draw(screen)
        pg.display.flip()

    timer = 0
    all_sprites.remove(bear)
    explosion.set_FPS(1)
    bear_head = Mob("bear.png", 1, 1)
    bear_head.image = bear_head.image.subsurface(pg.Rect(0, 0, 256, 85))
    bear_head.rect = bear_head.image.get_rect()
    bear_head.set_position(WIDTH - WIDTH // 3.9, HEIGHT - HEIGHT // 4.6)
    all_sprites.add(bear_head)
    while running:
        clock.tick(FPS)
        for event in pg.event.get():
            # check for closing window
            if event.type == pg.QUIT:
                running = False


        if timer == 100:
            fire1 = Mob("flame0.png", 3, 4)
            fire1.set_scale(0.2, 0.2)
            fire1.use_all_frames()
            fire1.set_FPS(2)
            fire1.set_position(WIDTH - WIDTH // 8 - 50, HEIGHT - HEIGHT // 4.5 - 55)
            all_sprites.add(fire1)
            fire1.update()
        if timer == 200:
            fire2 = Mob("flame0.png", 3, 4)
            fire2.set_scale(0.2, 0.2)
            fire2.use_all_frames()
            fire2.set_FPS(2)
            fire2.set_position(WIDTH - WIDTH // 6 - 50, HEIGHT - HEIGHT // 4 - 55)
            all_sprites.add(fire2)
            fire2.update()
        if timer == 300:
            fire3 = Mob("flame0.png", 3, 4)
            fire3.use_all_frames()
            fire3.set_scale(0.2, 0.2)
            fire3.set_position(WIDTH // 2 - 50, HEIGHT - HEIGHT // 4 - 55)
            all_sprites.add(fire3)
            fire3.set_FPS(2)
            fire3.update()
        explosion.update()
        if timer > 100:
            fire1.update()
        if timer > 200:
            fire2.update()
        if timer > 300:
            fire3.update()
        all_sprites.draw(screen)
        pg.display.flip()
        if timer <= 300:
            timer += 1


    pg.quit()


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    main()

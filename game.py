import pygame as pg
from sys import exit

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
        pg.sprite.Sprite.__init__(self)
        sprites_set = pg.image.load(image_name)
        sprites_set_size_x, sprites_set_size_y = sprites_set.get_size()
        self.frame_size_x, self.frame_size_y = sprites_set_size_x // sprites_cols, sprites_set_size_y // sprites_rows
        self.sprites_rows = sprites_rows
        self.sprites_cols = sprites_cols
        self.is_animation_started = False
        self._first_frame = None
        self._last_frame = None
        self._current_frame = 0
        self._all_animation_frames = []
        self._FPS = FPS
        self._ticks = 0
        self.rect = pg.Rect(0, 0, self.frame_size_x, self.frame_size_y)
        self.rect.center = (WIDTH / 2, HEIGHT / 2)

        for current_row in range(sprites_rows):
            for current_col in range(sprites_cols):
                self._all_animation_frames.append(sprites_set.subsurface(
                    pg.Rect(current_col * self.frame_size_x, current_row * self.frame_size_y, self.frame_size_x,
                            self.frame_size_y)))

        self.image = self._all_animation_frames[self._current_frame]

    def set_sprite(self, sprite):
        self.image = sprite

    def set_animation_set(self, first_frame, last_frame):
        self.is_animation_started = True
        self._first_frame = first_frame - 1
        self._last_frame = last_frame - 1

    def set_current_frame(self, current_frame):
        self._current_frame = current_frame

    def set_FPS(self, FPS):
        self._FPS = FPS

    def set_center_position(self, x, y):
        self.rect.center = (x, y)

    def use_all_frames(self):
        self.set_animation_set(1, len(self._all_animation_frames))

    def set_scale(self, in_x, in_y):
        for i in range(len(self._all_animation_frames)):
            self._all_animation_frames[i] = pg.transform.scale(self._all_animation_frames[i], (
            self._all_animation_frames[i].get_width() * in_x, self._all_animation_frames[i].get_height() * in_y))
        self.image = self._all_animation_frames[self._current_frame]
        self.rect = pg.Rect(self.rect.x, self.rect.y, self.image.get_width() * in_x, self.image.get_height() * in_y)

    def update(self):
        self._ticks += 1
        self._ticks %= self._FPS
        if self.is_animation_started and self._ticks == 0:
            if self._first_frame <= self._last_frame:
                self.image = self._all_animation_frames[self._first_frame]
                self.rect = self.image.get_rect(center=self.rect.center)
                self._first_frame += 1
            else:
                self.is_animation_started = False
                self.image = self._all_animation_frames[self._current_frame]
                self.rect = self.image.get_rect(center=self.rect.center)


def main():
    pg.init()
    screen = pg.display.set_mode((WIDTH, HEIGHT))
    clock = pg.time.Clock()

    bear = Mob("bear.png", 8, 8)
    bear.set_FPS(5)
    bear.set_center_position(110, HEIGHT - 140)

    bg = Bg("forest.png", WIDTH, HEIGHT)
    bg.rect.centery -= 40

    # ninja = Mob("ninja.png", 6, 9)
    # ninja.set_scale(2, 2)
    # ninja.set_FPS(10)
    # ninja.set_center_position(WIDTH - 110, HEIGHT - 140)
    # ninja.set_animation_set(7, 14)

    all_sprites = pg.sprite.Group()
    all_sprites.add(bg)
    all_sprites.add(bear)
    # all_sprites.add(ninja)
    running = True
    is_bear_moving = False

    while running:
        clock.tick(FPS)
        all_sprites.draw(screen)
        for event in pg.event.get():

            if event.type == pg.QUIT:
                pg.display.quit()
                exit()

            if event.type == pg.KEYDOWN:
                if event.key == pg.K_RIGHT:
                    bear.set_animation_set(52, 64)
                    is_bear_moving = True
                elif event.key == pg.K_UP:
                    bear.set_animation_set(43, 52)
                    is_bear_moving = False

            if event.type == pg.MOUSEBUTTONUP:
                if event.button == 3:
                    bear.set_animation_set(23, 34)
                    is_bear_moving = False

        if is_bear_moving:
            bg.update()

        if not bear.is_animation_started:
            is_bear_moving = False

        pg.display.flip()
        bear.update()
        # ninja.update()
        # if not ninja.is_animation_started:
        #     ninja.set_animation_set(8, 14)


if __name__ == "__main__":
    main()

from math import *

class Function:
    def __init__(self, func):
        self.func = func

    def calc_value(self, x):
        return eval(self.func)

    def find_root_on_segment(self, start, stop, eps, max_iter):
        iter_counter = 1
        middle = None
        if self.calc_value(start) * self.calc_value(stop) <= 0:
            middle = (start + stop) / 2
            while iter_counter < max_iter and abs(start - stop) > eps:
                if self.calc_value(start) * self.calc_value(middle) <= 0:
                    stop = middle
                else:
                    start = middle
                middle = (start + stop) / 2
                iter_counter += 1

        return middle, middle if middle is None else self.calc_value(middle), iter_counter

    def find_root(self, start, stop, step, eps, max_iter):
        x_cur = start
        while x_cur + step <= stop:
            x_start = x_cur
            x_stop = x_start + step
            iter_counter = 1
            middle = (x_start + x_stop) / 2
            if self.calc_value(x_start) * self.calc_value(x_stop) <= 0:
                middle = (x_start + x_stop) / 2
                while iter_counter < max_iter and abs(x_start - x_stop) > eps:
                    if self.calc_value(x_start) * self.calc_value(middle) <= 0:
                        x_stop = middle
                    else:
                        x_start = middle
                    middle = (x_start + x_stop) / 2
                    iter_counter += 1
            x_cur += stop
        return middle, self.calc_value(middle), iter_counter

a = Function("sin(x - 3.14/2)")
print(a.calc_value(0))
print("{:5f} {:5f} {}".format(*a.find_root_on_segment(1, 2, 0.00001,1000)))
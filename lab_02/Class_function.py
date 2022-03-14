from math import *
from dataclasses import dataclass


@dataclass
class Roots_information:
    def __init__(self):
        pass

    number: int
    segment: str
    root: float
    value_in_root: float
    iterations: int


class Function:
    def __int__(self):
        pass

    def __init__(self, func):
        self.func = func

    def set_function(self, func):
        self.func = func

    def calc_value(self, x):
        try:
            return eval(self.func)
        except Exception:
            return "Error"

    def find_root_on_segment(self, start, stop, eps, max_iter):
        iter_counter = 1
        middle = None
        roots = Roots_information()
        if self.calc_value(start) * self.calc_value(stop) <= 0:
            middle = (start + stop) / 2
            while iter_counter < max_iter and abs(start - stop) > eps:
                if self.calc_value(start) * self.calc_value(middle) <= 0:
                    stop = middle
                else:
                    start = middle
                middle = (start + stop) / 2
                iter_counter += 1
        roots.root = round(middle, 6)
        roots.value_in_root = middle if middle is None else round(self.calc_value(middle))
        roots.iterations = iter_counter
        return roots

    def find_roots(self, start, stop, step, eps, max_iter):
        segment_start = start
        segment_stop = segment_start + step
        roots_counter = 1
        roots_list = []
        while segment_stop <= stop:
            roots = self.find_root_on_segment(segment_start, segment_stop, eps, max_iter)
            segment_start += step
            segment_stop += step
            roots.segment = f"[{start}, {stop}]"
            roots.number = roots_counter
            roots_list.append(roots)
            roots_counter += 1

        return roots_list

# a = Function("x**2-2*x-3")
# # print(a.calc_value(0))
# # print("{:5f} {:5f} {}".format(*a.find_root_on_segment(1, 2, 0.00001,1000)))
# print(a.find_roots(-2, 4, 3, 0.000001, 1000))

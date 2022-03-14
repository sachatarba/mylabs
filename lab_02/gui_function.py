from Class_function import *
import tkinter as tk


@dataclass
class Parameters:
    def __init__(self):
        pass

    function: Function
    segment: list
    step: float
    n_max: float
    eps: float


class Interface:
    def __init__(self):
        self.window = tk.Tk()
        self.window.title('Функционалити')
        self.window.geometry("512x512")
        self.in_function = tk.Entry(bg="#555", fg="#ccc", font="13")
        self.in_segment = tk.Entry(bg="#555", fg="#ccc", font="13")
        self.in_step = tk.Entry(bg="#555", fg="#ccc", font="13")
        self.in_n_max = tk.Entry(bg="#555", fg="#ccc", font="13")
        self.in_eps = tk.Entry(bg="#555", fg="#ccc", font="13")
        self.parameters = Parameters()
        self.menu = tk.Menu(self.window)
        self.window.config(menu=self.menu)
        self.menu.add_command(label="Выполнить", command=self.set_parameters)

    def draw_input_interface(self):
        self.in_function.place(height=51, width=512, x=0, y=0)
        self.in_function.insert(0, "Введите функцию:")
        self.in_segment.place(height=51, width=512, x=0, y=(51 * 1))
        self.in_segment.insert(0, "Введите отрезок(начало и конец через запятую):")
        self.in_step.place(height=51, width=512, x=0, y=(51 * 2))
        self.in_step.insert(0, "Введите шаг:")
        self.in_n_max.place(height=51, width=512, x=0, y=(51 * 3))
        self.in_n_max.insert(0, "Введите Nmax:")
        self.in_eps.place(height=51, width=512, x=0, y=(51 * 4))
        self.in_eps.insert(0, "Введите eps:")
        self.window.mainloop()

    def set_parameters(self):
        self.parameters.function = self.in_function.get()
        try:
            self.parameters.segment = list(
                map(float, self.in_segment.get().split(",") if len(self.in_segment.get().split(",")) == 2 and
                                                               self.in_segment.get().split(",")[0] <
                                                               self.in_segment.get().split(",")[1] else None))
        except Exception:
            self.in_segment.delete(0, len(self.in_segment.get()))
            self.in_segment.insert(0, "Неправильный ввод")
        try:
            self.parameters.step = float(self.in_step.get())
        except Exception:
            self.in_step.delete(0, len(self.in_step.get()))
            self.in_step.insert(0, "Неправильный ввод")
        try:
            self.parameters.n_max = float(self.in_n_max.get())
        except Exception:
            self.in_n_max.delete(0, len(self.in_n_max.get()))
            self.in_n_max.insert(0, "Неправильный ввод")
        try:
            self.parameters.eps = float(self.in_eps.get())
        except Exception:
            self.in_eps.delete(0, len(self.in_eps.get()))
            self.in_eps.insert(0, "Неправильный ввод")



t = Interface()
t.draw_input_interface()
# a = Parameters()
# b = Function()


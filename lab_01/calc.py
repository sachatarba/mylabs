import tkinter as tk
from tkinter import messagebox as mb
import re

class Calc:
    def __init__(self):
        self.window = tk.Tk()
        self.window.title('Калькулятор')
        self.window.geometry("512x512")
        self.menu = tk.Menu(self.window)
        self.window.config(menu=self.menu)
        self.DESCRIPTION = "Программа для работы с вещественными числами\nв 8-ми ричной системе счисления.\nРазработал Тарба Александр"
        self.menu.add_command(label="Вычислить", command=lambda: self.output.configure(
                                                   text=(self.calculate(self.entry.get())) if (set(
                                                       [True if x in self.alpha else False for x in
                                                        self.entry.get()]) == {True}) else 'Input error'))
        self.menu.add_command(label="Очистить ввод",command=lambda: self.entry.delete(0, len(self.entry.get())))
        self.menu.add_command(label="Очистить вывод",command=lambda: self.output.configure(text=""))
        self.menu.add_command(label="Информация о программе", command=lambda: mb.showinfo("Info", self.DESCRIPTION))
        self.btns_text = ("7", "6", "5", " Clear \ninput",
                          "4", "3", "2", " Clear \noutput",
                          "-", "+", "1", "0", ".", "=", " Clear \nall")

        self.entry = tk.Entry(self.window, font=("Montserrat", "40"))
        self.output = tk.Label(self.window, bg="white", font=("Montserrat", "40"))
        self.btns = dict.fromkeys(self.btns_text)
        self.alpha = {'0', "1", '2', '3', '4', '5', '6', '7', '+', '-', '.'}
        self.default_width = 512 // 4
        self.DESCRIPTION = "Программа для работы с вещественными числами\n в 8-ми ричной системе счисления.\n Разработал Тарба Александр"
    def convert_to10_from8(self, num):
        return int(str(num), base=8)

    def convert_to8_from10(self, num):
        if num == 0:
            return 0
        to_base = 8
        from_base = 10
        n = int(num, from_base) if isinstance(num, str) else num
        alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        res = ""
        while n > 0:
            n, m = divmod(n, to_base)
            res += alphabet[m]
        return res[::-1]

    def calculate(self, string):
        while "++" or "--" in string:
            if "++" in string:
                string = string.replace("++", '+', 1)
            elif "--" in string:
                string = string.replace('--', '-', 1)
            elif "-+" in string:
                string = string.replace('-+', '-', 1)
            elif "+-" in string:
                string = string.replace('+-', '-', 1)
            else:
                break
        nums = re.findall(r'\d*\.\d+|\d+', string)
        signs = re.findall(r'[+-]', string)
        if len(nums) != len(signs):
            signs = ['+'] + signs
        nums_split = sum(
            [list(map(int, (x.split('.')) if len(x.split(".")) == 2 else x.split('.') + [0])) for x in nums], [])
        nums_convert = list(map(self.convert_to10_from8, nums_split))
        nums_10 = []
        for i in range(0, len(nums_convert), 2):
            nums_10.append(str(nums_convert[i]) + '.' + str(nums_convert[i + 1]))
        statement = ""
        for i in range(len(nums_10)):
            statement += (signs[i] + nums_10[i])
        result = round(eval(statement), 3)
        if result >= 0:
            is_positive = True
        else:
            result *= -1
            is_positive = False

        result_split = list(map(self.convert_to8_from10, list(map(int, str(result).split(".")))))
        result = str(result_split[0]) + "." + str(result_split[1])
        # result = str(convert_to8_from10(int(str(result).split(".")[0]))) + "." + str(
        #     convert_to8_from10(int(str(result).split(".")[1])))
        return result if is_positive else "-" + result

    def draw_interface(self):
        self.entry.place(x=0, y=0, width=256, height=232)
        self.output.place(x=256, y=0, width=256, height=232)
        current_iter = 0
        for key_btn in self.btns:
            if key_btn != "=" and key_btn != " Clear \ninput" and key_btn != " Clear \noutput" and key_btn != " Clear \nall":
                self.btns[key_btn] = tk.Button(self.window, text=key_btn,
                                               font=("Montserrat", "20"),
                                               command=lambda txt=key_btn: self.entry.insert(len(self.entry.get()) + 1,
                                                                                             txt))
                if key_btn != "1" and key_btn != "0" and key_btn != "." and key_btn != "+" and key_btn != '-':
                    self.btns[key_btn].place(x=(current_iter % 4) * 512 // 4,
                                             y=current_iter // 4 * (512 - 232) // 3 + 232,
                                             width=512 // 4, height=(512 - 232) // 3)

                elif key_btn == "-":
                    self.btns[key_btn].place(x=(current_iter % 4) * 512 // 4,
                                             y=current_iter // 4 * (512 - 232) // 3 + 232,
                                             width=512 // 4 // 2, height=(512 - 232) // 3)
                elif key_btn == "+":
                    self.btns[key_btn].place(x=(current_iter % 4) * 512 // 4 - (512 // 8),
                                             y=current_iter // 4 * (512 - 232) // 3 + 232,
                                             width=512 // 4 // 2, height=(512 - 232) // 3)
                    current_iter -= 1

                elif key_btn == "1":
                    self.btns[key_btn].place(x=(current_iter % 4) * 512 // 4,
                                             y=current_iter // 4 * (512 - 232) // 3 + 232,
                                             width=512 // 4 // 2, height=(512 - 232) // 3)

                elif key_btn == "0":
                    self.btns[key_btn].place(x=(current_iter % 4) * 512 // 4 - (512 // 8),
                                             y=current_iter // 4 * (512 - 232) // 3 + 232,
                                             width=512 // 4 // 2, height=(512 - 232) // 3)
                    current_iter -= 1


                elif key_btn == ".":
                    self.btns[key_btn].place(x=(current_iter % 4) * 512 // 4,
                                             y=current_iter // 4 * (512 - 232) // 3 + 232,
                                             width=512 // 4 // 2, height=(512 - 232) // 3)


            elif key_btn == "=":
                self.btns[key_btn] = tk.Button(self.window, text=key_btn,
                                               font=("Montserrat", "20"),
                                               command=lambda txt=key_btn: self.output.configure(
                                                   text=(self.calculate(self.entry.get())) if (set(
                                                       [True if x in self.alpha else False for x in
                                                        self.entry.get()]) == {True}) else 'Input error'))
                self.btns[key_btn].place(x=(current_iter % 4) * 512 // 4 - (512 // 8),
                                         y=current_iter // 4 * (512 - 232) // 3 + 232,
                                         width=512 // 4 // 2, height=(512 - 232) // 3)
                current_iter -= 1

            elif key_btn == " Clear \ninput":
                self.btns[key_btn] = tk.Button(self.window, text=key_btn,
                                               font=("Montserrat", "20"),
                                               command=lambda txt=key_btn: self.entry.delete(0, len(self.entry.get())))
                self.btns[key_btn].place(x=(current_iter % 4) * 512 // 4, y=current_iter // 4 * (512 - 232) // 3 + 232,
                                         width=512 // 4, height=(512 - 232) // 3)

            elif key_btn == " Clear \noutput":
                self.btns[key_btn] = tk.Button(self.window, text=key_btn,
                                               font=("Montserrat", "20"),
                                               command=lambda txt=key_btn: self.output.configure(text=""))
                self.btns[key_btn].place(x=(current_iter % 4) * 512 // 4, y=current_iter // 4 * (512 - 232) // 3 + 232,
                                         width=512 // 4, height=(512 - 232) // 3)

            elif key_btn == " Clear \nall":
                self.btns[key_btn] = tk.Button(self.window, text=key_btn,
                                               font=("Montserrat", "20"),
                                               command=lambda txt=key_btn: self.entry.delete(0, len(
                                                   self.entry.get())) or self.output.configure(text=""))
                self.btns[key_btn].place(x=(current_iter % 4) * 512 // 4, y=current_iter // 4 * (512 - 232) // 3 + 232,
                                         width=512 // 4, height=(512 - 232) // 3)

            current_iter += 1
        self.window.mainloop()


calculator = Calc()
calculator.draw_interface()

from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from math import pi


class Point():
    def __init__(self, x_in=None, y_in=None, event=None):
        if event:
            self.x, self.y = eval(str(event.pos())[19:])

            self.point = event.pos()
        else:
            self.x, self.y = x_in, y_in
    # pass


# p = Point(1, 2)
class Triangle():
    def __init__(self, p1, p2, p3):
        self.point1 = p1
        self.point2 = p2
        self.point3 = p3
        self.len_a = ((p1.x - p2.x) ** 2 + (p1.y - p2.y) ** 2) ** 0.5
        self.len_b = ((p1.x - p3.x) ** 2 + (p1.y - p3.y) ** 2) ** 0.5
        self.len_c = ((p2.x - p3.x) ** 2 + (p2.y - p3.y) ** 2) ** 0.5
        self.demiPerimeter = (self.len_a + self.len_b + self.len_c) / 2

    def calcPerimeter(self):
        return self.len_a + self.len_b + self.len_c

    def calcSquare(self):
        p = self.calcPerimeter() / 2
        a = self.len_a
        b = self.len_b
        c = self.len_c

        return (p * (p - a) * (p - b) * (p - c)) ** 0.5

    def calcR(self):
        s_triangle = self.calcSquare()
        a = self.len_a
        b = self.len_b
        c = self.len_c
        R = int(a * b * c / s_triangle / 4)
        return R

    def circumscribedArea(self):
        R = self.calcR()
        circleArea = pi * R ** 2
        return circleArea

    def calcCircumscribedCenter(self):
        Ax = self.point1.x
        Ay = self.point1.y
        Bx = self.point2.x
        By = self.point2.y
        Cx = self.point3.x
        Cy = self.point3.y

        D = 2 * (Ax * (By - Cy) + Bx * (Cy - Ay) + Cx * (Ay - By))
        Ux = ((Ax ** 2 + Ay ** 2) * (By - Cy) + (Bx ** 2 + By ** 2) * (Cy - Ay) + (Cx ** 2 + Cy ** 2) * (Ay - By)) / D
        Uy = ((Ax ** 2 + Ay ** 2) * (Cx - Bx) + (Bx ** 2 + By ** 2) * (Ax - Cx) + (Cx ** 2 + Cy ** 2) * (Bx - Ax)) / D

        return int(Ux), int(Uy)


class MainWidget(QWidget):
    # Переопределяем конструктор класса
    def __init__(self):
        # Обязательно нужно вызвать метод супер класса
        QWidget.__init__(self)

        self.setMinimumSize(QSize(745, 745))  # Устанавливаем размеры
        self.setWindowTitle("Geometry")  # Устанавливаем заголовок окна
        central_widget = PaintWidget()  # Создаём центральный виджет
        # self.setCentralWidget(central_widget)  # Устанавливаем центральный виджет
        entry = Widget(central_widget)
        # self.

        grid_layout = QGridLayout()  # Создаём QGridLayout
        # central_widget.setLayout(grid_layout)  # Устанавливаем данное размещение в центральный виджет
        self.setLayout(grid_layout)
        grid_layout.addWidget(central_widget, 0, 0)
        grid_layout.addWidget(entry, 1, 0)
        # lbl = QLabel("heeeeey", self)
        # grid_layout.addWidget(lbl,1,0)
        # lbl = QLabel("Проверка автодополнения", self)
        # grid_layout.addWidget(lbl, 0, 0)

        # Создаём поле ввода
        # lineEdit = QLineEdit(self)
        # strList = ['Python', 'PyQt5', 'Qt', 'Django', 'QML']  # Создаём список слов
        # Создаём QCompleter, в который устанавливаем список, а также указатель на родителя
        # completer = QCompleter(strList, lineEdit)
        # lineEdit.setCompleter(completer)  # Устанавливает QCompleter в поле ввода
        # grid_layout.addWidget(entry, 0, 0)  # Добавляем поле ввода в сетку
        # lbl.move(-10, -10)


class PaintWidget(QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle('Geometry')
        self.setMaximumWidth(745)
        self.setMaximumHeight(645)
        self.ansTriangle = None
        self.points = []

    # def buttonClickedEvent(self, event):

    def mousePressEvent(self, event):
        # print(event)
        point = Point(event=event)
        self.points.append(point)

        # Вызов перерисовки виджета
        self.update()

    def mouseReleaseEvent(self, event):
        # self.point = None
        pass

    def paintEvent(self, event):
        super().paintEvent(event)
        # print(event.pos())
        # Если нет
        if not self.points:
            return

        # Рисовать будем на самом себе
        painter = QPainter(self)

        # Для рисования точки хватит setPen, но для других фигур (типо rect) понадобится setBrush
        painter.setPen(QPen(Qt.black, 5.0))
        try:
            # Рисование точки
            for point in self.points:
                painter.drawPoint(point.x, point.y)
                # painter.drawArc(point.x, point.y)
                print(point.x, point.y)

            if self.ansTriangle is not None:
                pen = QPen(Qt.blue, 2, Qt.SolidLine)
                # pen = QPen (QColor (255, 215, 0), 2, Qt.SolidLine) # Эффект такой же, как и в предыдущей строке кода
                painter.setPen(pen)
                painter.setBrush(QColor(255, 215, 0))
                painter.drawLine(self.ansTriangle.point1.x, self.ansTriangle.point1.y, self.ansTriangle.point2.x,
                                 self.ansTriangle.point2.y)
                painter.drawLine(self.ansTriangle.point2.x, self.ansTriangle.point2.y, self.ansTriangle.point3.x,
                                 self.ansTriangle.point3.y)
                painter.drawLine(self.ansTriangle.point1.x, self.ansTriangle.point1.y, self.ansTriangle.point3.x,
                                 self.ansTriangle.point3.y)
                # painter.setBrush(QColor(255, 215, 0))
                # painter.drawEllipse(*self.ansTriangle.calcCircumscribedCenter(), 2 * self.ansTriangle.calcR(), 2 * self.ansTriangle.calcR())
                painter.drawEllipse(20, 10, 20, 20)
        except Exception:
            pass


class Widget(QWidget):
    def __init__(self, paintWidget):
        super().__init__()
        self.initUI()
        self.paintWidget = paintWidget

    def initUI(self):
        self.setMaximumHeight(100)
        grid = QGridLayout()
        self.setLayout(grid)
        self.lbl = QLabel("Введите координаты точки в формате: x, y", self)
        grid.addWidget(self.lbl, 0, 0)
        self.lineEdit = QLineEdit(self)
        grid.addWidget(self.lineEdit, 0, 1)
        self.btn_entry = QPushButton(self, text="Ввести")
        self.btn_entry.clicked.connect(self.btnClicked)
        grid.addWidget(self.btn_entry, 0, 2)
        self.btn_del = QPushButton(self, text="Удалить точки")
        self.btn_del.clicked.connect(self.btnDelClicked)
        grid.addWidget(self.btn_entry, 0, 3)
        self.btn_calc = QPushButton(self, text="Нарисовать решение")
        self.btn_calc.clicked.connect(self.btnCalcClicked)
        grid.addWidget(self.btn_calc, 0, 4)

    def btnClicked(self):
        try:
            self.cords = tuple(map(int, eval("({})".format(str(self.lineEdit.text())))))
        except Exception:
            self.lineEdit.setText("Ошибка ввода")
            return
        print(*self.cords)
        point = Point(*self.cords)
        print(point.x, point.y)
        self.paintWidget.points.append(point)
        self.paintWidget.update()
        print(self.cords)

    def btnDelClicked(self):
        self.paintWidget.points = []
        self.paintWidget.ansTriangle = None
        self.paintWidget.update()

    def btnCalcClicked(self):
        delta = None
        ans_triangle = None
        try:
            for p1 in range(len(self.paintWidget.points) - 2):
                for p2 in range(p1 + 1, len(self.paintWidget.points) - 1):
                    for p3 in range(p2 + 1, len(self.paintWidget.points)):
                        triangle = Triangle(self.paintWidget.points[p1], self.paintWidget.points[p2],
                                            self.paintWidget.points[p3])
                        diff = abs(triangle.calcSquare() - triangle.circumscribedArea())
                        if delta is None:
                            delta = diff
                            ans_triangle = triangle
                        if delta > diff:
                            delta = diff
                            ans_triangle = triangle

            self.paintWidget.ansTriangle = ans_triangle
            self.paintWidget.update()
        except Exception:
            pass
        # qp = QPainter()
        # qp.begin(self)
        #
        # qp.end()


if __name__ == '__main__':
    app = QApplication([])

    # w = Widget()
    # w.show()
    m = MainWidget()
    m.show()
    app.exec()

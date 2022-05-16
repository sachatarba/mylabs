from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from math import pi


class Point():
    def __init__(self, x_in=None, y_in=None, qt_point_event=None):
        if qt_point_event:
            self.x, self.y = eval(str(qt_point_event.pos())[19:])

            self.point = qt_point_event.pos()
        else:
            self.x, self.y = x_in, y_in

class Triangle():
    def __init__(self, p1, p2, p3):
        self.point1 = p1
        self.point2 = p2
        self.point3 = p3
        self.len_a = ((p1.x - p2.x) ** 2 + (p1.y - p2.y) ** 2) ** 0.5
        self.len_b = ((p1.x - p3.x) ** 2 + (p1.y - p3.y) ** 2) ** 0.5
        self.len_c = ((p2.x - p3.x) ** 2 + (p2.y - p3.y) ** 2) ** 0.5

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
        entry = Widget(central_widget)
        grid_layout = QGridLayout()  # Создаём QGridLayout
        self.setLayout(grid_layout)
        grid_layout.addWidget(central_widget, 0, 0)
        grid_layout.addWidget(entry, 1, 0)



class PaintWidget(QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle('Geometry')
        self.setMaximumWidth(745)
        self.setMaximumHeight(645)
        self.ansTriangle = None
        self.points = []


    def paintTriangle(self, painter, triangle):
        pen = QPen(Qt.blue, 2, Qt.SolidLine)
        painter.setPen(pen)
        painter.drawLine(triangle.point1.x, triangle.point1.y, triangle.point2.x,
                         triangle.point2.y)
        painter.drawLine(triangle.point2.x, triangle.point2.y, triangle.point3.x,
                         triangle.point3.y)
        painter.drawLine(triangle.point1.x, triangle.point1.y, triangle.point3.x,
                         triangle.point3.y)

    def mousePressEvent(self, event):
        point = Point(qt_point_event=event)
        self.points.append(point)

        # Вызов перерисовки виджета
        self.update()

    def mouseReleaseEvent(self, event):
        pass

    def paintEvent(self, event):
        super().paintEvent(event)

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

            # Если искомый треугольник существует, рисуем его
            if self.ansTriangle is not None:
                self.paintTriangle(painter, self.ansTriangle)

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

        point = Point(*self.cords)
        self.paintWidget.points.append(point)
        self.paintWidget.update()

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



if __name__ == '__main__':
    app = QApplication([])

    main = MainWidget()
    main.show()
    app.exec()

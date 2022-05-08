#!/bin/bash

file1=$1
file2=$2

# Находим строчку в каждом файле, содержащую "Result: ",
# отбрасываем все, что идет до "Result: " 
f1=$(grep "Result: .*" "$file1")
f2=$(grep "Result: .*" "$file2")
f1_parced=${f1/*Result: /Result: }
f2_parced=${f2/*Result: /Result: }

# Записываем такие строчки в файлы
echo "$f1_parced" > f1
echo "$f2_parced" > f2

# Вычсиляем номера строк, в котором встретилось "Result: "
n1=$(sed -n '/Result: /=' "$file1")
n2=$(sed -n '/Result: /=' "$file2")
n1=$((n1 + 1))
n2=$((n2 + 1))

# Дозаписываем в файлы все, что идет после этих строк
less "$file1" | sed -n "$n1",100p >> f1
less "$file2" | sed -n "$n2",100p >> f2

# Сравниваем файлы
if diff f1 f2; then
    exit 0
else
    exit 1
fi

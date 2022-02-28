RB_ins = importdata('RB_ins.txt');
RB_find = importdata('RB_find.txt');
Bin_ins = importdata('Bin_ins.txt');
Bin_find = importdata('Bin_find.txt');

x = importdata('x.txt');

figure
subplot(2,1,1)
semilogy(x, RB_ins, 'LineWidth', 2);
hold on;
title('Добавление')
semilogy(x, Bin_ins, 'LineWidth', 2);
xlabel('Кол-во элементов в дереве', 'FontSize', 15)
ylabel('Время', 'FontSize', 15)
legend('Красно-черное дерево', 'Обычное дерево бинарного поиска', 'FontSize', 15, 'Location', 'SouthEast')

subplot(2,1,2)
semilogy(x, RB_find, 'LineWidth', 2);
hold on;
semilogy(x, Bin_find, 'LineWidth', 2);
title('Поиск')
xlabel('Кол-во элементов в дереве', 'FontSize', 15)
ylabel('Время', 'FontSize', 15)
legend('Красно-черное дерево', 'Обычное дерево бинарного поиска', 'FontSize', 15, 'Location', 'SouthEast')
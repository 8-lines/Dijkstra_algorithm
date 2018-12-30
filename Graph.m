x = [6000, 6100, 6200, 6300, 6400, 6500, 6600, 6700, 6800, 6900, 7000, 7100, 7200, 7300, 7400, 7500, 7600, 7700, 7800, 7900, 8000, 8100, 8200, 8300, 8400, 8500, 8600, 8700, 8800, 8900, 9000, 9100, 9200, 9300, 9400, 9500, 9600, 9700, 9800, 9900, 10000, 10100, 10200, 10300, 10400, 10500, 10600, 10700, 10800, 10900, 11000, 11100, 11200, 11300, 11400, 11500, 11600, 11700, 11800, 11900, 12000];
y = [0.247, 0.255, 0.263, 0.268, 0.282, 0.293, 0.297, 0.305, 0.314, 0.325, 0.336, 0.345, 0.373, 0.365, 0.385, 0.39, 0.393, 0.405, 0.418, 0.43, 0.436, 0.452, 0.46, 0.476, 0.484, 0.499, 0.505, 0.519, 0.537, 0.546, 0.55, 0.571, 0.582, 0.595, 0.614, 0.625, 0.629, 0.643, 0.656, 0.682, 0.687, 0.708, 0.714, 0.736, 0.752, 0.754, 0.773, 0.789, 0.801, 0.826, 0.841, 0.855, 0.856, 0.884, 0.894, 0.912, 0.933, 0.938, 0.949, 0.977, 0.999];

xx = min(x):0.1:max(x);

N = 2;
coeff2 = polyfit(x, y, N);
newY2 = 0;
for k=0:N
    newY2 = newY2 + coeff2(N-k+1) * xx.^k;
end
err2 = max(abs(y - appFunc(x, coeff2))./abs(y))*100

N = 4; 
coeff4 = polyfit(x, y, N);
newY4 = 0;
for k=0:N
    newY4 = newY4 + coeff4(N-k+1) * xx.^k;
end
err4 = max(abs(y-appFunc(x, coeff4))./abs(y))*100

k = length(xx); 
yLn = log(y); 
xLn = log(x); 
N = 1;
coeffLn = polyfit(xLn, yLn, N); 
newYLn = zeros(1, k); 
for i = 1:k 
    newYLn(i) = appFuncExp(xx(i), coeffLn); 
end 
errLn = max(abs(y-appFuncExp(x, coeffLn))./abs(y))*100

figure('Color','w');
hold on;
grid on
xlabel('size');
ylabel('time, s.');
plot(x, y, '*r');
plot(xx, newY2, 'r', 'Linewidth', 3);
plot(xx, newY4, 'y', 'Linewidth', 2);
plot(xx, newYLn, 'k', 'Linewidth', 1); 
legend("Original", "Pow 2", "Pow 4", "Pow Ln"); 



function [ret] = appFuncExp(x, coef) 
    ret = exp(coef(2))*x.^(coef(1)); 
end

function [ret] = appFunc(x, coef) 
    L = length(coef); 
    ret = 0; 
    for i = 1:L 
        ret = ret + (x.^(L-i))*coef(i); 
    end 
end
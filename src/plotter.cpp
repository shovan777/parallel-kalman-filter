// // We need a plotter to plot the data points generated by the code
// #include <stdio.h>
// #include <stdlib.h>

// #include <cmath>
// #include <matplot/matplot.h>
// #include "include/plotter.h"

// void plotter() {
//     std::cout << "Hi World!";
//     using namespace matplot;

//     auto x = linspace(0, 3 * pi, 200);
//     auto y = transform(x, [&](double x) { return cos(x) + rand(0, 1); });

//     scatter(x, y);

//     show();
//     return 0;
    
//     // using namespace matplot;
//     // std::vector<double> x = linspace(0, 2 * pi);
//     // std::vector<double> y = transform(x, [](auto x) { return sin(x); });

//     // plot(x, y, "-o");
//     // hold(on);
//     // plot(x, transform(y, [](auto y) { return -y; }), "--xr");
//     // plot(x, transform(x, [](auto x) { return x / pi - 1.; }), "-:gs");
//     // plot({1.0, 0.7, 0.4, 0.0, -0.4, -0.7, -1}, "k");

//     // show();
//     // return 0;
// }
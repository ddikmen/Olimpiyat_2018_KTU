#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
#include <algorithm>
#include <iomanip>

class Vertex{
    public:
        Vertex() : x(0), y(0) {}
        Vertex(double param1, double param2) : x(param1), y(param2) {}
        void Show(){std::cout << x << " " << y;}
        std::tuple<double,double> get() const {return {x,y};}
    private:
        double x, y;
};

std::vector<std::vector<Vertex>> get();
Vertex midPoint(const Vertex&, const Vertex&);
std::tuple<double,double,double> line(const Vertex&, const Vertex&);
double slope(const double&, const double&);
std::tuple<double,double,double> vLine(const Vertex&, const double&, const double&);
Vertex intersection(const std::tuple<double,double,double>&, const std::tuple<double,double,double>& );
double distance(const Vertex&, const Vertex&);
std::vector<double> distances(const Vertex&, const  Vertex&, const Vertex&, const Vertex&);
void calc(const Vertex&, const Vertex&, const std::vector<std::vector<Vertex>>&);

int main(){
    
    std::vector<std::vector<Vertex>> v;
    Vertex initial1(0,0), initial2(80,60);
    auto [a,b,c] = line(initial1,initial2);
    std::vector<std::vector<Vertex>> walls = get();
    calc(initial1,initial2,walls);

}

std::vector<std::vector<Vertex>> get(){
    std::vector<std::vector<Vertex>> vec;
    double x1, y1, x2, y2;
    while(std::cin >> x1 >> y1 >> x2 >> y2){
        std::vector<Vertex> v;
        Vertex a(x1,y1), b(x2,y2);
        v.push_back(a);
        v.push_back(b);
        vec.push_back(v);
    }
    return vec;
}

Vertex midPoint(const Vertex& a, const Vertex& b){
    double x,y;
    auto [xa,ya] = a.get();
    auto [xb,yb] = b.get();
    x = (xa + xb) / 2.0;
    y = (ya + yb) / 2.0;
    Vertex v(x,y);
    return v;
}

std::tuple<double,double,double> line(const Vertex& x, const Vertex& y){
    auto [xa,ya] = x.get();
    auto [xb,yb] = y.get();
    double a = yb - ya;
    double b = -1 * (xb - xa);
    double c = -1 * ((a*xb) + (b*yb));
    return {a/b, b/b, c/b};
}

double slope(const double& x, const double& y){
    double m = (-1 * x) / y;
    return m;
}

std::tuple<double,double,double> vLine(const Vertex& v, const double& x, const double& y){
    auto [xv,yv] = v.get();
    double m = slope(x,y);
    m = -1 / m;
    double a = -1 * m;
    double b = 1;
    double c = yv + m * xv;
    return {a, b, c};
}

Vertex intersection(const std::tuple<double,double,double>& a, const std::tuple<double,double,double>& b){
    double x, y;
    x = (-1 * std::get<2>(b) + std::get<2>(a)) / (-1 * std::get<0>(a) + std::get<0>(b));
    y = (-1 * x * std::get<0>(a)) + (-1 * std::get<2>(a));
    Vertex v(x,y);
    return v;
}

double distance(const Vertex& a, const Vertex& b){
    auto [xa,ya] = a.get();
    auto [xb,yb] = b.get();
    double d = pow((xa-xb),2) + pow((ya-yb),2);
    return sqrt(d);
}

std::vector<double> distances(const Vertex& initial1, const Vertex& initial2, const  Vertex& wall1, const Vertex& wall2){
    std::vector<double> d;
    d.resize(6);
    auto [a, b, c] = line(initial1,initial2);
    Vertex v1 = intersection(vLine(initial1, a, b),line(initial2, wall1));
    Vertex v2 = intersection(vLine(initial1, a, b),line(initial2, wall2));
    d[0] = distance(initial1,wall1);
    d[1] = distance(initial1,wall2);
    d[2] = distance(initial1,midPoint(wall2,v2));
    d[3] = distance(initial1,v2);
    d[4] = distance(initial1,v1);
    d[5] = distance(initial1,midPoint(wall1,v1));
    return d;
}

void calc(const Vertex& initial1, const Vertex& initial2, const std::vector<std::vector<Vertex>>& walls){
    for(auto i : walls){
        std::vector<Vertex> v;
        for(auto j : i){
            v.push_back(j);
        }
        std::vector<double> d = distances(initial1, initial2, v[0], v[1]);
        auto it = std::min_element(d.begin(),d.end());
        std::cout << std::fixed << std::setprecision(2) << std::distance(d.begin(),it) + 1 << " : " << *it << "\n";
        v.clear();
    }
}
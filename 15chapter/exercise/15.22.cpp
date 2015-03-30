#include <iostream>
#include <string>
using namespace std;
class graph
{
public:
    virtual void draw_g()const;
    virtual ~graph() = default;
};
void graph::draw_g()const
{
    cout << "draw_g" << endl;
}
class square : public graph
{
public:
    square() = default;
    square(const size_t i):side_length(i){}
    virtual void draw_g()const override = 0;
    virtual ~square() override = default;
protected:
    size_t side_length;
};
class circle : public graph
{
public:
    circle() = default;
    circle(const size_t i):radious(i){}
    virtual void draw_g()const override = 0;
    virtual ~circle() override = default;
protected:
    size_t radious;
};
class two_dimension_square : public square
{
public:
    two_dimension_square() = default;
    two_dimension_square(const size_t i):square(i),area(i*i){}
    virtual void draw_g()const override;
    virtual ~two_dimension_square() override= default;
private:
    size_t area;
};
void two_dimension_square::draw_g()const
{
    cout << "draw a square,area:" << area << endl;
}
class thr_dimension_square : public square
{
public:
    thr_dimension_square() = default;
    thr_dimension_square(const size_t i):square(i),volume(i*i*i){}
    virtual void draw_g()const override;
    virtual ~thr_dimension_square() override = default;
private:
    size_t volume;
};
void thr_dimension_square::draw_g()const
{
    cout << "draw a square,volume:" << volume << endl;
}
class two_dimension_circle : public circle
{
public:
    two_dimension_circle() = default;
    two_dimension_circle(const size_t i):circle(i),area(3.14*i*i){}
    virtual void draw_g()const override;
    virtual ~two_dimension_circle() override= default;
private:
    double area;
};
void two_dimension_circle::draw_g()const
{
    cout << "draw a circle,area:" << area << endl;
}
class thr_dimension_circle : public circle
{
public:
    thr_dimension_circle() = default;
    thr_dimension_circle(const size_t i):circle(i),volume(4*3.14*i*i*i/3){}
    virtual void draw_g()const override;
    virtual ~thr_dimension_circle() override= default;
private:
    double volume;
};
void thr_dimension_circle::draw_g()const
{
    cout << "draw a circle,volume:" << volume << endl;
}
void print_graph(graph &ga)
{
    ga.draw_g();
}
int main()
{
    two_dimension_circle tdc(3);
    two_dimension_square tds(2);
    thr_dimension_circle thrdc(3);
    thr_dimension_square thrds(2);
    print_graph(tdc);
    print_graph(tds);
    print_graph(thrdc);
    print_graph(thrds);
    return 0;
}

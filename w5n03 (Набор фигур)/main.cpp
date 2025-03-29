#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

const float pi = 3.14f;

class Figure
{
public:
    virtual string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
};

class Triangle : public Figure
{
public:
    Triangle(int &a, int &b, int &c)
    {
        double p = (a + b + c) / 2;
        area = sqrt(p * (p - a) * (p - b) * (p - c));
        perimeter = a + b + c;
    }
    string Name() const override
    {
        return "TRIANGLE";
    }

    double Perimeter() const override
    {
        return perimeter;
    }

    double Area() const override
    {
        return area;
    }

private:
    double area, perimeter;
};

class Rect : public Figure
{
public:
    Rect(int &width, int &height)
    {
        area = width * height;
        perimeter = (width + height) * 2;
    }
    string Name() const override
    {
        return "RECT";
    }

    double Perimeter() const override
    {
        return perimeter;
    }

    double Area() const override
    {
        return area;
    }

private:
    double area, perimeter;
};

class Circle : public Figure
{
public:
    Circle(int &r)
    {
        area = pi * r * r;
        perimeter = 2 * pi * r;
    }
    string Name() const override
    {
        return "CIRCLE";
    }

    double Perimeter() const override
    {
        return perimeter;
    }

    double Area() const override
    {
        return area;
    }

private:
    double area, perimeter;
};

shared_ptr<Figure> CreateFigure(istringstream &figure_description)
{
    string figure_type;
    figure_description >> figure_type;

    shared_ptr<Figure> figure_ptr;
    if (figure_type == "TRIANGLE")
    {
        int a, b, c;
        figure_description >> a >> b >> c;
        figure_ptr = make_shared<Triangle>(a, b, c);
    }
    else if (figure_type == "RECT")
    {
        int width, height;
        figure_description >> width >> height;
        figure_ptr = make_shared<Rect>(width, height);
    }
    else
    {
        int r;
        figure_description >> r;
        figure_ptr = make_shared<Circle>(r);
    }
    return figure_ptr;
}

int main()
{
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line);)
    {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD")
        {
            is >> ws;
            figures.push_back(CreateFigure(is));
        }
        else if (command == "PRINT")
        {
            for (const auto &current_figure : figures)
            {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}
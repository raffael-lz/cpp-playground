#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// classes we can not change
struct Shape
{
    virtual std::string str() const = 0;
};

class Circle : public Shape
{
    public:
    Circle(float radius) : radius(radius) {};

    string str() const override
    {
        ostringstream oss;
        oss << " Circle has radius: " << radius;
        return oss.str();
    }

    private:
    float radius{0.f};
};

class Square : public Shape
{ 
    public:
    Square(float length) : length(length) {};

    string str() const override
    {
        ostringstream oss;
        oss << " Square has length: " << length;
        return oss.str();
    }

    void resize(float new_length)
    {
        length = new_length;
    }

    private:
    float length{0.f};
};

// classes to extend (decorate)
template <typename T>
struct ColorShape : T
{
    template <typename ...Args>
    ColorShape(string color, Args... args) : color_(color), T(std::forward<Args>(args)...)
    {
    }

    string str() const override
    {
        ostringstream oss;
        oss << T::str() << " and color: " << color_;
        return oss.str();
    }

    private:
    string color_;
};

int main()
{
    Circle c{3.0};
    cout << c.str() << endl;

    Square s{5.0};
    s.resize(2.0);
    cout << s.str() << endl;
    
    // extendes objects
    ColorShape<Circle> color_circle{"red", 5.f};
    cout << color_circle.str() << endl;

    ColorShape<Square> color_square{"blue", 3.f};
    color_square.resize(12.f);
    cout << color_square.str() << endl;
}

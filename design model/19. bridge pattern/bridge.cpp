#include <iostream>

// 桥模式，将对象两种方向的不同变化通过组合的方式结合起来,
// 而非继承，从而大幅度减少类的个数
class Color {
public:
    virtual void drawColor() const = 0;
};

class Shape {
public:
    Shape(Color* _color) : color(_color) {}
    virtual void draw() const = 0;
protected:
    Color *color;
};

class Rectangle : public Shape {
public:
    Rectangle(Color* _color) : Shape(_color) {}

    void draw() const override {
        color->drawColor();
        std::cout << "rectangle\n";
    }
};

class Circle : public Shape {
public:
    Circle(Color* _color) : Shape(_color) {}

    void draw() const override {
        color->drawColor();
        std::cout << "circle\n";
    }
};

class Black : public Color {
public:
    void drawColor() const override {
        std::cout << "Black ";
    }
};

class Red : public Color {
public:
    void drawColor() const override {
        std::cout << "Red ";
    }
};

int main() {
    Color *black = new Black();
    Color *red = new Red();
    Shape *shape1 = new Circle(black);
    Shape *shape2 = new Rectangle(red);
    shape1->draw();
    shape2->draw();
    delete shape1;
    delete shape2;
    return 0;
}
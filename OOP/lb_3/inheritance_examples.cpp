#include <iostream>
#include <ostream>
#include <string>

using std::cout;
using std::string;
using std::ostream;

namespace my {
    class point;
    class graphic;
    class position;
    class styles;
    class line;
    ostream& operator<<(ostream& out, point p);
} // namespace my

class my::point {
  public:
    double x = 0, y = 0;

    point() {}
    point(double x, double y) : x(x), y(y) {}
    ~point() {}
};

class my::graphic {
  protected:
    string name;
  public:
    graphic() { cout << this << " graphic ctor\n"; }

    void set_graphic_name(string name) { this->name = name; }
    string &get_graphic_name() { return name; }
};

// class my::position : public graphic {
// use "virtual" to prevent two instances of graphic in my::line
class my::position : public virtual graphic {
  protected:
    point sp, ep;
  public:
    position() { cout << this << " position ctor\n"; }
    void set_coords(const point &sp, const point &ep);

    const char *get_type() { return "position"; } // same method in other parent of my::line 
};

// class my::styles : public graphic {
// use "virtual" to prevent two instances of graphic in my::line
class my::styles : public virtual graphic {
  protected:
    short width = 1, color = 0;
  public:
    styles() { cout << this << " styles ctor\n"; }
    styles(short width, short color) : width(width), color(color) { cout << this << " styles ctor\n"; }

    const char *get_type() { return "styles"; } // same method in other parent of my::line 
};

class my::line : public styles, public position {
  public:
    line() { cout << this << " line ctor\n"; }
    line(short width, short color) : position(), styles(width, color) { cout << this << " line ctor\n"; }
    void draw();
};

int main() {
    my::line l(1, 10);
    l.set_coords({1, 1}, {10, 10});
    l.draw();

    // l.get_type(); // error because this call is ambiguous (двусмысленный)
    ((my::styles)l).get_type(); // will be called get_type() of my::styles

    my::styles *s = &l;
    s->get_type();              // will be called get_type() of my::styles

    // using VIRTUAL INHERITANCE we have only one instance of graphic
    l.set_graphic_name("line");
    l.get_graphic_name();
}

void my::line::draw() {
    cout << "\ndrawing line:\n"
             << "styles: " << width << ", " << color << "\n"
             << "coordinates: " << sp << " , " << ep << "\n\n";
}

void my::position::set_coords(const point &sp, const point &ep) {
    this->sp = sp; this->ep = ep;
    cout << "set coords: " << sp << " , " << ep << "\n"; 
}

ostream& my::operator<<(ostream& out, my::point p) {
    return out << "{" << p.x << ", " << p.y << "}";
}

#include <iostream> // include ("import") the declarations for the I/O stream library
#include<vector>
#include<string>
#include<complex>
#include<limits>

using namespace std; // make names from std visible without std::

constexpr double square(double x) // square a double precision floating-point number
{
    return x*x;
}

void print_square(double x)
{
    cout << "the square of " << x << " is " << square(x) << "\n";
}

const int dmv = 17;
int var = 17;

constexpr double max1 = 1.4*square(dmv); // OK if square(17) is a constant expression
//constexpr double max2 = 1.4*square(var); // error: var is not a constant expression
const double max3 = 1.4*square(var); // OK, may be evaluated at run time

double sum(const vector<double>&); // sum will not modify its argument(1.8)
double sum(const vector<double>& vec)
{
    double sum_v = 0.0;
    for(auto v:vec)
    {
        sum_v += v;
    }
    return sum_v;
}
/*
Undefined symbols for architecture x86_64:
  "sum(std::__1::vector<double, std::__1::allocator<double> > const&)", referenced from:
      ___cxx_global_var_init.4 in learnCplusplus.cpp.o
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
make[2]: *** [learCplusplus] Error 1
make[1]: *** [CMakeFiles/learCplusplus.dir/all] Error 2
make: *** [all] Error 2"
*/
vector<double> v{1.2, 3.5, 4.5}; // v is not a constant
const double s1 = sum(v); //OK: evaluated at run time
//constexpr double s2 = sum(v); // error: sum(v) not constant expression

void size_of_types()
{
    cout << "bool size is " << sizeof(bool) << "\n";
    cout << "char size is " << sizeof(char) << "\n";
    cout << "int size is " << sizeof(int) << "\n";
    cout << "double size is " << sizeof(double) << "\n";
    cout << "unsigned size is " << sizeof(unsigned) << "\n";
}

template<typename T>
void print_value(const T & val, string name)
{
    cout << val << "\n";
}

template<typename T>
void print_value(const T & val)
{
    static_assert(is_same<vector<int>, T>(), "the val must be a vector<int>");
    for(const auto& x : val)
        cout << x << "[0x" << &x << "]" << " ";
    cout << "\n";
}
void variable_various_initialization()
{
    double d1 = 2.3;
    print_value(d1, "d1");
    double d2 {2.3};
    print_value(d2, "d2");
    complex<double> z = 1; // a complex number with double-precision floating-point scalars
    print_value(z, "z");
    complex<double> z2 {d1, d2};
    print_value(z2, "z2");
    complex<double> z3 = {1,2}; // the = is optional with { ... }
    print_value(z3, "z3");
//    print_value(z3);
    vector<int> v{1,2,3,4,5,6}; // a vector of ints  
    print_value(v);
}

struct Vector
{
    int sz; // numbers of elements
    double* elem; // pointer to elements
};

void vector_init(Vector& v, int s)
{
    v.elem = new double[s]; // allocate an array of s doubles
    v.sz = s;
    //That is, v's elem member gets a pointer produced by new operator and v's sz member gets the number of elements. The & in Vector& indicates that we pass v by non-const reference (1.8); that way, vector_init() can modify the vecotr passed to it.";
    //The new operator allocates memeory from an area called the free store (also known as dynamic memeory and heap). Objects allocated on the free store are independent of the scope from which they are created and \"live\" until they destroyed using the delete operator(4.2.2)";
}

void vector_destroy(Vector& v)
{
    delete v.elem;
    v.sz = 0;
}

void f_vec(Vector v, Vector& rv, Vector* pv)
{
    int i1 = v.sz; // access through name
    int i2 = rv.sz; // access through reference
    int i3 = pv->sz; // access through pointer
    cout << "v ptr = "<< &v << " rv ptr = "<< &rv << " pv ptr = " << pv << "\n";
    for (int i=0; i != v.sz; ++i)
    {
        cout << &(v.elem[i]) << ",";
    }
    cout << "\n";
    for (int i=0; i != rv.sz; ++i)
    {
        cout << &(rv.elem[i]) << ",";
    }
    cout << "\n";
    for (int i=0; i != pv->sz; ++i)
    {
        cout << &(pv->elem[i]) << ",";
    }
    cout << "\n";
}

double read_and_sum(int s) // read s integers from cin and return their sum; s is assumed to be positive
{
    Vector v;
    vector_init(v, s); // allocate s elements for v
    cout << "please give " << s << " integers:" << "\n";
    for (int i=0; i!=s; ++i)
        cin >> v.elem[i]; // read into elements

    double sum = 0; 
    cout << "Going to make sum of these integers:\n";
    for (int i=0; i!=s; ++i)
    {
        cout << v.elem[i];
        if (i < (s-1))
            cout << ",";
        else
            cout << "\n";
        sum += v.elem[i]; // take the sum of the elements
    }
    f_vec(v, v, &v);
    vector_destroy(v);
    return sum;
}

void study_struct()
{
    cout << "how many integers to sum:" << "\n";
    int num = 0;
    cin >> num;
    double sum = read_and_sum(num);
    cout << "the sum = " << sum << "\n";
}

void study_sizeof_types()
{
    cout << "size of long " << sizeof(1L) << '\n';
    cout << "size of long long" << sizeof(1LL) << '\n';
    cout << "largest float == " << std::numeric_limits<float>::max() << '\n';
    cout << "char is signed ==" << std::numeric_limits<char>::is_signed << '\n';
}

void study_alignment()
{
    auto ac = alignof('c'); // the alignment of a char
    auto ai = alignof(1); // the alignment of an int
    auto ad = alignof(2.0); // the alignment of a double
    int a[20];
    auto aa = alignof(a); // the alignment of an int

    cout << ac << ai << ad << aa << '\n';
}

void study_move_builtin()
{
    int z{10};
    int y{20};
    int x{30};

    cout << "x=" << x << " y=" << y << " z=" << z << '\n';

    z = x;
    y = move(x);
    cout << "x=" << x << " y=" << y << " z=" << z << '\n';
}

void study_move_Vector()
{
    Vector x;vector_init(x, 10);
    Vector y;vector_init(y, 100);
    Vector z;vector_init(z, 1000);
    cout << "x=" << x.sz << " y=" << y.sz << " z=" << z.sz << '\n';
    z = x;
    y = move(x);
    cout << "x=" << x.sz << " y=" << y.sz << " z=" << z.sz << '\n';
    vector_destroy(y);
    cout << "x=" << x.sz << " y=" << y.sz << " z=" << z.sz << '\n';
    //vector_destroy(z);
    //cout << "x=" << x.sz << " y=" << y.sz << " z=" << z.sz << '\n';
    //cout  << " x=" << x.sz << '\n';
}

void study_move_vector()
{
    vector<int> x{11,12,13};
    vector<int> y{21,22,23,24};
    vector<int> z{31,32,33,34,35};
    print_value(x);
    print_value(y);
    print_value(z);
    cout << "x=" << x.size() << " y=" << y.size() << " z=" << z.size() << '\n';
    //cout << "x=" << x.size() << " y=" << " z=" << z.size() << '\n';
    z = x;
    y = move(x);
    cout << "x=" << x.size() << " y=" << y.size() << " z=" << z.size() << '\n'; 
    print_value(x);
    print_value(y);
    print_value(z);

    vector<int> && h{41,42,43};
    print_value(h);
    vector<int> k = move(h);
    print_value(h);
    print_value(k);
    vector<int> & m = k;
    print_value(m);
}

template<typename T>
void t_swap(T& a, T&b) // "perfect swap" (almost)
{
    cout << " a[" << &a << "]=" << a << '\n';
    cout << " b[" << &b << "]=" << b << '\n';

    T tmp {static_cast<T&&>(a)}; // the initialization may write to a
    cout << " a[" << &a << "]=" << a << '\n';
    cout << " tmp[" << &tmp << "]=" << tmp << '\n';
    a = static_cast<T&&>(b); // the assignment may write to b
    cout << " a[" << &a << "]=" << a << '\n';
    cout << " b[" << &b << "]=" << b << '\n';
    b = static_cast<T&&>(tmp); // the assignment may write to tmp
    cout << " tmp[" << &tmp << "]=" << tmp << '\n';
    cout << " b[" << &b << "]=" << b << '\n';
    b = move(tmp);
    cout << " tmp[" << &tmp << "]=" << tmp << '\n';
 /*
 * The result value of static_cast<T&&>(x) is an rvalue of type T&& for x. An further operation that is optimized for rvalues can now use its optimization for x. 
 * In particular, if a type T has a move constructor or move assignment, it will be used. 
 * But if the type T has no "move" related features there is nothing difference with normal value or lvaue.
 * So the preparation of value type should be with aim in optimization.
 */
}

void study_lrvalue()
{
    int x{1};
    int y{2};
    int z{3};

    int &&xx = static_cast<int&&>(x);
    cout << " x[" << &x << "]=" << x << '\n';
    cout << " y[" << &y << "]=" << y << '\n';
    cout << " z[" << &z << "]=" << z << '\n';
    cout << "xx[" << &xx << "]=" << xx << '\n';

    int xm = move(xx);
    cout << "xm[" << &xm << "]=" << xm << '\n';
    cout << " x[" << &x << "]=" << x << '\n';
    cout << " y[" << &y << "]=" << y << '\n';
    cout << " z[" << &z << "]=" << z << '\n';
    cout << "xx[" << &xx << "]=" << xx << '\n';
    t_swap(x, y);    
}

void structures_holes()
{

    struct Readout1
    {
        char hour;
        int value;
        char seq;
    };
    struct Readout2
    {
        int value;
        char hour;
        char seq;
    };
    cout << "sizeof(Readout1)=" << sizeof(Readout1) << " sizeof(Readout2)=" << sizeof(Readout2) << '\n';

}

struct Point
{
    double x;
    double y;
};
struct Points
{
    vector<Point> elem;// must contain at least one Point
    Points(Point p0)
    {
        elem.push_back(p0);
    }
    Points(Point p0, Point p1)
    {
        elem.push_back(p0);
        elem.push_back(p1);
    }
};
Point g_point_x;// automatically be initialized to (0,0)
void struct_construct()
{
    Point point_x; // danger: uninitialized if in local scope
    Point p1 {}; // default construction:
    Point p2 {100}; // the second member is default constructed: {1, {}}; that is {100, 0}
    Point point_y {100, 200};
    cout << "g_point_x(" << g_point_x.x << "," << g_point_x.y << ")" << "\n";
    cout << "p1(" << p1.x << "," << p1.y << ")" << "\n";
    cout << "p2(" << p2.x << "," << p2.y << ")" << "\n";
    cout << "point_x(" << point_x.x << "," << point_x.y << ")" << "\n";
    cout << "point_y(" << point_y.x << "," << point_y.y << ")" << "\n";
    //Points x0;
    Points x1{ {100,200}};
    Points x2{{100, 200}, {300,400}};
    cout << "x1 has " << x1.elem.size() << " points, and x2 has " << x2.elem.size() << " points." << "\n";
}

template<typename T>
void mycopy(T* to,  const T* from, int count)
{
    if (is_pod<T>::value)
    {
        cout << "is pod" << "\n";
        memcpy(to,from,count*sizeof(T));
    }
    else
    {
        cout << "is not pod" << "\n";
        for (int i=0; i!=count; ++i)
            to[i]=from[i];
    }
}

void plain_old_data()
{
    int from[] {1,2,3,4,5,6};
    int to[] {7,8,9,10,11,12};
    mycopy(to, from, 6);

    
    Point p_x1[] {{100, 200}, {222,333}};
    Point p_x2[] {{444, 200}, {444,333}, {555,777}};
    mycopy(p_x2, p_x1, 2);
    
    Points x1[] {{ {100,200}}};
    Points x2[] {{{100, 200}, {300,400}}};    
    mycopy(x2, x1, 1);
}

void enumerations()
{
    enum class Class_Traffic_light:int { red, yellow, green };
    enum class Class_Warning:char { green, yellow, orange, red };// fire alert levels

    enum Plain_Traffic_light { e1_red, e1_yellow, e1_green }; // the default type is int
    enum Plain_Warning:char { green, yellow, orange, red }; // fire alert levels

    Class_Traffic_light class_Traffic_light {Class_Traffic_light::red};
    cout << static_cast<int>(class_Traffic_light) << "\n";
    Plain_Traffic_light plain_Traffic_light {Plain_Traffic_light::e1_red};
    cout << plain_Traffic_light << "\n";
}

void switch_case()
{
    enum class Vessel {cup, glass, goblet, chalice};

    Vessel v {Vessel::chalice};
    switch (v)
    {
        case Vessel::cup:
            int x;
            x = 0;
            break;
        case Vessel::glass:
            break;
        case Vessel::goblet:
            break;
        //case Vessel::chalice:
          //  break;
    }
}
int main()
{
    std::cout << "Hello, World!\n";
    print_square(1.234);  // print: the square of 1.234 is 1.52276
    cout << "vector {1.2, 3.5, 4.5} is summed to " << s1 << "\n";
    size_of_types();
    variable_various_initialization();
    //study_struct();
    study_sizeof_types();
    study_alignment();
    study_move_builtin();
    study_move_Vector();
    study_move_vector();
    study_lrvalue();
    structures_holes();
    struct_construct();
    plain_old_data();
    enumerations();
}

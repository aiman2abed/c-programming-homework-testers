#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct point {
    double x, y;
} Point;

typedef struct triangle {
    Point p, q, r;
} Triangle;

void print_point(Point p);

void set_point(Point* p, double x, double y);

double get_x(const Point* p);

double get_y(const Point* p);

Point get_p(const Triangle* t);

bool swap_points(Point* p1, Point* p2);

bool swap_pointers(Point** p1, Point** p2);

void set_triangle(Triangle* t, Point p, Point q, Point r);

double distance(Point p, Point q);

double perimeter(Triangle const* t);

double area(Triangle const* t);

bool is_right(Triangle const* t);

void print_triangle(Triangle const* t);


int main()
{

    int i;

    //Createing the structures and initialize to 0
    Point p = { .x = 0, .y = 0 };
    Point q = { .x = 0, .y = 0 };
    Point r = { .x = 0, .y = 0 };

    Triangle t = {
        .p = p,
        .r = r,
        .q = q
    };

    Point* orig_p_pointer, * orig_q_pointer;
    Point* orig_points[3];
    Point* points[3] = { &p, &q, &r };
    const char* labels[3] = { "P", "Q", "R" };

    //Getting the points values from the user
    for (int i = 0; i < 3; i++) {
        double x, y;
        printf("Enter coordinates for point %s (x y): \n", labels[i]);
        scanf("%lf %lf", &x, &y);  // Get input from user
        set_point(points[i], x, y);  // Use set_point to assign values
    }
    printf("---------------- Starting program --------------- \n");
    set_triangle(&t, p, q, r);
    print_point(get_p(&t));
    print_triangle(&t);

    printf("---------------- swap_points --------------- \n");
    orig_p_pointer = &p;
    orig_q_pointer = &q;
    printf("Before swap_points: P={%f,%f} Q={%f,%f} \n", get_x(&p), get_y(&p), get_x(&q), get_y(&q));
    if (swap_points(&p, &q))
    {
        printf("After swap_points: P={%f,%f} Q={%f,%f} \n", p.x, p.y, q.x, q.y);
        printf("p address %s changed, q address %s changed \n", &p == orig_p_pointer ? "hasn't" : "has", &q == orig_q_pointer ? "hasn't" : "has");
    }
    printf("---------------- swap_pointers --------------- \n");

    for (i = 0; i < 2; i++) {
        printf("Before swap_pointers: points[%d] points to (%f, %f)\n", i, points[i]->x, points[i]->y);
        orig_points[i] = points[i];
    }

    if (swap_pointers(&points[0], &points[1])) {
        for (int i = 0; i < 2; i++) {
            printf("After swap_pointers: points[%d] points to (%f, %f)\n", i, points[i]->x, points[i]->y);
            printf("points[%d] address %s changed \n", i, points[i] == orig_points[i] ? "hasn't" : "has");
        }
    }
    printf("---------------- End --------------- \n");

    return 0;
}

void print_point(Point p)
{
    printf("(%.2f, %.2f)\n", p.x, p.y);
}

double distance(Point p, Point q)
{
    return sqrt((q.x - p.x) * (q.x - p.x) + (q.y - p.y) * (q.y - p.y));
}

void print_triangle(Triangle const* t)
{
    if (t != NULL) {
        printf("Triangle Properties:\n");
        double perim = perimeter(t);
        double area_val = area(t);
        bool right = is_right(t);

        printf("Perimeter: %.2f\n", perim);
        printf("Area: %.2f\n", area_val);
        printf("The triangle %s a right-angled triangle. \n", right ? "is" : "isn't");
    } else {
        printf("Triangle is NULL.\n");
    }
}

double perimeter(Triangle const* t) {
    if (t == NULL) {
        return 0; // Return 0 if t is NULL
    }
    double d1 = distance(t->p, t->q);
    double d2 = distance(t->q, t->r);
    double d3 = distance(t->r, t->p);
    return d1 + d2 + d3;
}
double area(Triangle const* t) {
    if (t == NULL) {
        return 0; // Return 0 if t is NULL
    }
    double a = distance(t->p, t->q);
    double b = distance(t->q, t->r);
    double c = distance(t->r, t->p);
    
    // Using Heron's formula to calculate the area of the triangle
    double s = (a + b + c) / 2.0; // semi-perimeter
    return sqrt(s * (s - a) * (s - b) * (s - c));
}


bool is_right(Triangle const* t) {
    if (t == NULL) {
        return false; // Return false if t is NULL
    }
    double a = distance(t->p, t->q);
    double b = distance(t->q, t->r);
    double c = distance(t->r, t->p);

    // Check for the Pythagorean theorem
    return (fabs(a * a + b * b - c * c) < 1e-9 ||
            fabs(b * b + c * c - a * a) < 1e-9 ||
            fabs(c * c + a * a - b * b) < 1e-9);
}

void set_point(Point* p, double x, double y) {
    if (p != NULL) {
        p->x = x;
        p->y = y;
    }
}

// Get functions for Point
double get_x(const Point* p) {
    if (p != NULL) {
        return p->x;
    }
    return 0; // Return 0 if p is NULL
}

double get_y(const Point* p) {
    if (p != NULL) {
        return p->y;
    }
    return 0; // Return 0 if p is NULL
}

void set_triangle(Triangle* t, Point p, Point q, Point r) {
    if (t != NULL) {
        t->p = p;
        t->q = q;
        t->r = r;
    }
}

Point get_p(const Triangle* t) {
    if (t != NULL) {
        return t->p;
    }
    return (Point){0, 0}; // Return a default point if t is NULL

}

bool swap_points(Point* p1, Point* p2) {
    if (p1 == NULL || p2 == NULL) {
        return false; // Return false if either pointer is NULL
    }
    Point temp = *p1; // Store the value of p1 in a temporary variable
    *p1 = *p2;        // Assign the value of p2 to p1
    *p2 = temp;      // Assign the temporary value to p2
    return true;     // Return true to indicate successful swap
}
bool swap_pointers(Point** p1, Point** p2) {
    if (p1 == NULL || p2 == NULL || *p1 == NULL || *p2 == NULL) {
        return false; // Return false if any pointer is NULL
    }
    Point* temp = *p1; // Store the value of p1 in a temporary variable
    *p1 = *p2;         // Assign the value of p2 to p1
    *p2 = temp;       // Assign the temporary value to p2
    return true;      // Return true to indicate successful swap
}


//---------------------------------------------------------------------------
#ifndef CameraH
#define CameraH
#include <math.h>
//---------------------------------------------------------------------------

const double DANGLE = 7;
const float PI =3.141592653; //Замечательно число Пи

struct point {
       double x, y, z;
       point (double xx = 0, double yy = 0, double zz = 0):x(xx), y(yy), z(zz){}
       void norm(double R = 1){x/=R; y/=R; z/=R;}
} ;

class Camera{
      double R;
      point eye;
      point n;
      float alpha, beta; // Углы поворота камеры
public:
       Camera::Camera(double Rad = 1, double phi = 0, double theta = 90);
       ~Camera(){}
       void rotate(double vert = 0, double horiz = 0);
       void zoom(double val = 0);
       point getEye() {return eye;}
       point getNorm() {return n;}
       double getR(){return R;}
};
#endif

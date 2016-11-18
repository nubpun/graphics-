//---------------------------------------------------------------------------
#pragma hdrstop
#include "Camera.h"
//---------------------------------------------------------------------------


Camera::Camera(double Rad, double phi, double theta){
	R = Rad;
	alpha = theta;
	beta = phi;
	eye = point(R*sin(alpha / 180.*M_PI)*sin(beta / 180.*M_PI),
		R*cos(alpha / 180.*M_PI),
		R*sin(alpha / 180.*M_PI)*cos(beta / 180.*M_PI));
	if (sin(alpha / 180.*M_PI) >= 0) {
		n = point(0, 1, 0);
	}
	else{
		n = point(0, -1, 0);
	}
}

void Camera::rotate(double vert, double horiz){
	alpha += vert*DANGLE;
	beta += horiz*DANGLE;
	if (alpha > 360.0) {
		alpha - 360.;
	}
	if (beta >= 360.0) {
		beta -= 360.;
	}
	eye = point(R*sin(alpha / 180.*M_PI)*sin(beta / 180.*M_PI),
		R*cos(alpha / 180.*M_PI),
		R*sin(alpha / 180.*M_PI)*cos(beta / 180.*M_PI));
	if (sin(alpha / 180.*M_PI) >= 0) {
		n = point(0, 1, 0);
	}
	else{
		n = point(0, -1, 0);
	}
}

void Camera::zoom(double val){
	R += val;
	if (R < 0.5) {
		R = 0.5;
	}
	if (R > 70) {
		R = 70;
	}
	eye = point(R*sin(alpha / 180.*M_PI)*sin(beta / 180.*M_PI),
		R*cos(alpha / 180.*M_PI),
		R*sin(alpha / 180.*M_PI)*cos(beta / 180.*M_PI));
	if (sin(alpha / 180.*M_PI) >= 0) {
		n = point(0, 1, 0);
	}
	else{
		n = point(0, -1, 0);
	}
}
#pragma package(smart_init)

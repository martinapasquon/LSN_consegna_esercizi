#include "Posizione.h"
#include <cmath>
#include "random.h"

Random rnd;
Posizione::Posizione(double r){

	m_x=rnd.Rannyu(-r, r);
	m_y=r*r -pow(m_x,2);
	

}
Posizione::Posizione(double l, double m){
m_x=rnd.Rannyu(0, l);
m_y=rnd.Rannyu(0, l);
 }

Posizione::~Posizione(){ ;}
//coordinate cartesiane
double Posizione::getX() const{
	return m_x;
}     
double Posizione::getY() const{
  return m_y;
}

//coordinate sferiche
double Posizione::getR() const{
 return sqrt(pow(m_x,2)+pow(m_y,2));
}     

//distanza da un altro punto
double Posizione::Distanza(const Posizione& p) const{
 return ( pow(getX()-p.getX(),2) + pow(getY()-p.getY(),2));
}
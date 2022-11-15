#ifndef __Posizione_h__
#define __Posizione_h__

class Posizione {

public:

  // costruttori
  Posizione(double r);
  Posizione(double l, double m); 
  // distruttore
  ~Posizione();
  // metodi
  double getX() const;       // Coordinate cartesiane
  double getY() const;
  double getR() const;       // Coordinate sferiche
  double Distanza(const Posizione&) const; // distanza da un altro punto

private:

  double m_x, m_y;  

};

#endif // __Posizione_h__

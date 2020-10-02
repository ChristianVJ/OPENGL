#include "fuente_luz.h"

// CONSTRUCTOR

FuenteLuz :: FuenteLuz(GLenum luz, _vertex3f color, tipo_luz tipo, GLfloat posicion[4], GLfloat y, GLfloat x){

  this->luz = luz;
  this->color = color;
  this->tipo = tipo;
  for (int i=0 ;i<4 ;i++)
    this->posicion[i] = posicion[i];
  this->y = y;
  this->x = x;

}

void FuenteLuz :: Activar_fuente()
{


  /*
– Definir las luces (características). Una luz es un objeto más de la escena (ModelView)
– Habilitar la iluminación (glEnable (GL_LIGHTING) obsoleto desde la versión 3.0)
– Usar normales a las caras o a los vértices según el modo de suavizado
– Definir los materiales de los objetos
– Cambiar el modelo de iluminación*/

 
 glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE); // situamos al observador en el infinito y entonces la luz afecta de la misma manera a todos los objetos 
 glEnable(GL_LIGHTING); // Activa la iluminación 
 glEnable(this->luz); // Activar la fuente
 glMatrixMode(GL_MODELVIEW); // Antes de realizar una operacion de transformacion
 glLoadIdentity() ; // Se inicializa la matriz identidad

 glPushMatrix(); // Cambios unicamente dentro del pushmatrix

 glRotatef( x, 0.0, 1.0, 0.0 ) ;
 glRotatef( y, 1.0, 0.0, 0.0 ) ;

 // glLightfv(GL_LIGHT0,GL_POSITION,light_position);

 glLightfv(this->luz, GL_POSITION, this->posicion);
 glLightfv(this->luz, GL_AMBIENT, (GLfloat *) & color);
 glLightfv(this->luz, GL_SPECULAR, (GLfloat *) &color);
 glLightfv(this->luz, GL_DIFFUSE, (GLfloat *) &color);

 glPopMatrix() ; // Fin del Push
}


void FuenteLuz :: Desactivar_fuente(){

  glPushMatrix();

  glDisable(GL_LIGHTING); // ILUMINACION DESACTIVADA
  glDisable(this->luz); // FUENTE DESACTIVADA
  
  glPopMatrix();
}


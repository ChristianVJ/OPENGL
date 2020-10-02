#include "vertex.h"
#include <vector>
#include <GL/glut.h>
#include <GL/gl.h>
#include "textura_imagen.h"
#include "figura.h"
#include "Tipo_luz_material.h" //For enum

using namespace std;

#ifndef _BEVERAGECAN_H_
#define _BEVERAGECAN_H_

class Cocacola {

private:

      //OpenGL puede gestionar mas de
      //una textura a la vez. Para diferenciarlas
      //usa un valor entero unico para cada una de ellas
      static const char * archivo_textura;
      bool iluminado;

/*• lata-pcue.ply : perfil de la parte central, la que incorpora la textura de la
lata (archivo text-lata-1.jpg). Es un material difuso-especular.
• lata-psup.ply : tapa superior metálica. No lleva textura, es un material
difuso-especular de aspecto metálico (ver figura 4.3, derecha).
• lata-pinf.ply : base inferior metálica, sin textura y del mismo tipo de
material (ver figura 4.3, izquierda).*/

     Figura * t_central;  //can_body;
     Figura * t_inferior; //can_bottom;
     Figura * t_superior; //can_top;

public:

      Cocacola();
      ~Cocacola();
      void Dibujar_lata(visual_t visualization);

};

#endif

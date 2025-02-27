#include "Cocacola.h"
#include <iostream>
#include <vector>
#include "vertex.h"
#include <stdlib.h>
#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include "file_ply_stl.h"
#include <cmath>

using namespace std;

const char * Cocacola :: archivo_textura = "text-lata-1.jpg";

Cocacola :: Cocacola() //Constructor de la cocacola. Cargamos los diferentes ply y los revolucionamos
{
  t_central = new Figura(archivo_textura); // perfil de la parte central, la que incorpora la textura de la			      
  t_central-> revolucionar("lata-pcue.ply"); // lata (archivo text-lata-1.jpg). Es un material difuso-especular.

  t_inferior = new Figura(); // Tapa superior metálica. No lleva textura, es un material difuso-especular de aspecto metálico
  t_inferior-> revolucionar("lata-psup.ply");

  t_superior = new Figura (); // Base inferior metálica, sin textura y del mismo tipo de material.
  t_superior -> revolucionar("lata-pinf.ply");
}

Cocacola :: ~Cocacola()
{
  delete t_central;
  delete t_superior;
  delete t_inferior;
}

void Cocacola :: Dibujar_lata(visual_t visualization) {

  GLfloat whiteSpecular[] = {1.0, 1.0, 1.0};
  GLfloat blackSpecular[] = {0.0,0.0,0.0};
  GLfloat someDiffuse[] = {0.4,0.4,0.4};
  GLfloat someDiffuse1[] = {0.6,0.6,0.6};
  GLfloat silverAmbient[] = {0.19225,0.19225,0.19225};
  GLfloat silverDiffuse[] = {0.50754,0.50754,0.50754};
  GLfloat silverSpecular[] = {0.508273,0.508273,0.508273};

  t_central->setAmbiental(silverAmbient);
  t_central->setDifusa(silverDiffuse);
  t_central->setEspecular(silverSpecular);
  t_central->setBrillo(0);
  t_central->Dibujar(visualization);

  float shiny = 100.0;
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
  t_inferior->setAmbiental(silverAmbient);
  t_inferior->setDifusa(silverDiffuse);
  t_inferior->setEspecular(silverDiffuse);
  t_inferior->setBrillo(10);
  t_inferior->Dibujar(visualization);

 t_superior->setAmbiental(silverAmbient);
 t_superior->setDifusa(silverDiffuse);
 t_superior->setEspecular(silverDiffuse);
 t_superior->setBrillo(30);
 t_superior->Dibujar(visualization);


}

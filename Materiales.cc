#include "Materiales.h"

Material :: Material() // SIN texturaURA
{
  iluminado = false; 	
  textura = NULL;
  ambiental[3] = 1.0;
  difusa[3] = 1.0;
  especular[3]  = 1.0;
}

Material :: Material(const char * material_archivo) // CON texturaURA
{
  textura = new Textura ( material_archivo);
  ambiental[3] = 1.0;
  difusa[3] = 1.0;
  especular[3]  = 1.0;
}

Material :: ~Material()
{
  if(textura!= NULL) 
    delete textura;
}

void Material :: Activar_materiales(){

  glEnable(GL_LIGHTING); // habilitamos iluminación
  glEnable(GL_NORMALIZE);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

/*Para los materiales hay dos funciones básicas para setear sus características "lumínicas":
glMaterialfv (GLenum face, GLenum name, GLfloat vector_param);
glMaterialf (GLenum face, GLenum name, GLfloat param);*/

  //MATERIALES
  glMaterialfv(GL_FRONT,GL_AMBIENT,ambiental);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,difusa);
  glMaterialfv(GL_FRONT,GL_SPECULAR,especular);

  //exponente de brillo	
  glMaterialf(GL_FRONT,GL_SHININESS,brillo);

  if(textura!=NULL) 
    textura->Activar_texturas();
  else
    glDisable(GL_TEXTURE_2D);
}



void Material :: setAmbiental(GLfloat ambiental[MATERIAL-1]) {
  for(int i=0;i<MATERIAL;i++)
    this->ambiental[i] = ambiental[i];
}
void Material :: setDifusa(GLfloat difusa[MATERIAL-1]) {
  for(int i=0;i<MATERIAL;i++)
    this->difusa[i] = difusa[i];
}
void Material :: setEspecular(GLfloat especular[MATERIAL-1]) {
  for(int i=0;i<MATERIAL;i++)
    this->especular[i] = especular[i];
}
void Material :: setBrillo(GLfloat brillo) {
  this->brillo = brillo;
}



GLfloat * Material :: getAmbiental() const{
  return (GLfloat *)this->ambiental;
}
GLfloat * Material :: getDifusa() const{
  return (GLfloat *)this->difusa;
}
GLfloat * Material :: getEspecular() const{
  return (GLfloat *)this->especular;
}
GLfloat Material :: getBrillo() const {
  return this->brillo;
}


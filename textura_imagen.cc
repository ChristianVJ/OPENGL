#include "textura_imagen.h"
#include <cassert>



Textura :: Textura (const char *archivo_textura)
{
  this->pixels = NULL;
  //cargar la imagen
  this->pixels = new jpg::Imagen(archivo_textura);

  this->tamx = pixels->tamX(); //num.columnas
  this->tamy = pixels->tamY();
  this->texels = pixels->leerPixels(); // función declarada en jpg_imagen.cpp
  this->imageSize = tamx*tamy*3;
  this->gen = NOT_ACTIVE;

  for(int i=0;i<ARRAY_SIZE;i++)
  {
    array_1[i] = array_2[i] = 0.0f;
  }

// Creación de la textura [TEXT]:Primero hemos de obtener un identificador para la textura. Para ello pedimos a OpenGL que nos devuelva un identificador de textura libre:
  glGenTextures(1, &identificador_textura); //hace idTex igual a un nuevo identificador

// Activamos la textura como textura activa:
  glBindTexture(GL_TEXTURE_2D, identificador_textura); //activa textura con identificado 'idTex'

// Creamos la textura. El modo más sencillo de hacerlo es a través de una función de GLU que crea la textura y sus variaciones a aplicar según la distancia a la que se encuentre:
  gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, this->tamx, this->tamy, GL_RGB, GL_UNSIGNED_BYTE,this->texels);
// Con el primer parámetro indicamos el tipo de textura. En este caso ( GL_TEXTURE_2D ) es una textura 2D. Los siguentes parámetros indican el número de bytes por cada pixel, que dependerán de la imágen (p. ej. 3 para RGB y 4 para RGBA; en este caso, la imágen es de tipo RGB), su anchura y altura (que han de ser pares, y muy recomendable, múltiplos de 2), el formato de los datos ( GL_RGB , GL_RGBA ,...), el tipo de los datos, que en nuestro caso vendrá dado por bytes sin signo, por lo que usaremos la constante GL_UNSIGNED_BYTE , y finalmente, un puntero a los datos.

  assert(glGetError() == GL_NO_ERROR);
}

void Textura :: activate()
{


  glEnable(GL_TEXTURE_2D); // Activar textura
  glBindTexture(GL_TEXTURE_2D, this->identificador_textura); // Indicamos que textura queremos activar.

  if(gen == NOT_ACTIVE){
    glDisable(GL_TEXTURE_GEN_S); // Desactiva la generación de coordenadas
    glDisable(GL_TEXTURE_GEN_T); // Desactiva la tabla de coordenadas de textura
  }

  else
  {
    // Activamos las luces y sus características.
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR); 
 // especifica que el cálculo color especular de la iluminación se almacena por separado del resto de la computación de iluminación. El color especular se resume en el color del fragmento generado después de la aplicación de la asignación de texturas (si está activado )
    
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

    glTexGenfv(GL_S, GL_OBJECT_PLANE, array_1);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, array_2);

    glEnable( GL_TEXTURE_GEN_S); // Activa la generación de coordenadas
    glEnable( GL_TEXTURE_GEN_T); // Activa la tabla de coordenadas de textura

  }

}

unsigned long Textura :: getX() const{ // get ancho
  return this->tamx;
}
unsigned long Textura :: getY() const{ // get alto
  return this->tamy;
}
unsigned char * Textura :: getTexels() const{ // get texels
  return this->texels;
}

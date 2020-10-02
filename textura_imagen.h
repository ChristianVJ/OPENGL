/* Se incluirán en el programa las variables o instancias que almacenan los parámetros de cada una de las
texturas que se planean usar. Para cada textura, se debe guardar un puntero a los pixels en
memoría dinámica, el identificador de textura de OpenGL, un valor lógico que indique si
hay generación automática de coordenadas de textura o se usa la tabla de coordenadas de
textura, y finalmente los 8 parámetros (dos arrays de 4 flotantes cada uno) para la generación
automática de texturas.*/


#include "jpg_imagen.hpp"
#include <vector>
#include <GL/glut.h>
#define ARRAY_SIZE 4

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

enum generation_t {NOT_ACTIVE, OBJECT, EYE};

class Textura
{
  private:

	jpg::Imagen * pixels; // un puntero a los pixels en memoría dinámica
	GLuint identificador_textura; // identificador de textura de OpenGL
	// un valor lógico que indique si hay generación automática de coordenadas de textura o se usa la tabla de coordenadas de textura
	GLfloat array_1[ARRAY_SIZE]; // array1 para la generacion automática de texturas
        GLfloat array_2[ARRAY_SIZE]; // array2 para la generación automática de texturas
	unsigned long tamx;
    	unsigned long tamy;
    	unsigned char * texels;
   	unsigned int imageSize;
	generation_t gen;




  public:

	Textura (const char * archivo_textura);
	~Textura();
	void Activar_texturas();
  	unsigned long getX() const;
   	unsigned long getY() const;
    	unsigned char * getTexels() const;
    	//Para activar la textura
   	void activate();

};

#endif




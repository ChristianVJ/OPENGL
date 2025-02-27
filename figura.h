
#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>
#include "stdlib.h"
#include "vertex.h"
#include <math.h>
#include "Tipo_luz_material.h"
#include "Materiales.h"

#ifndef _MALLATVT_H_
#define _MALLATVT_H_
#define MATERIAL 4

using namespace std; 

class Figura { // CLASE PARA VISUALIZAR Y REVOLUCIONAR

private:

	int puntos_perfil;		// puntos_perfil inicial

  	vector<float> v_vertices_ply;  	// vector de vértices relacionados con el ply
  	vector<int> v_caras_ply; 	// vector de caras relacionados con el ply
	
	vector< _vertex3f > Vertices;   		// Vector de vértices
        vector< _vertex3ui > Caras;			// Vector de caras
        vector< _vertex3f > normal_vertices; 		// Vector de normales de los vértices
        vector< _vertex3f > normal_caras;		// Vector de normales de las caras
	/*1*/ vector< _vertex2f > v_texturas;           // Vector de texturas
	Material * material;

public:
	Figura();
 	Figura(const char * archivo_textura);
	~Figura();
	void Constructor(const char * filename);	// Constructor
	void revolucionar(const char * filename); 	// Revoluciona (no funciona visualizar normales)
	void Dibujar(visual_t visualization);		// Función que dibuja según el modo seleccionado
  	void setAmbiental(GLfloat ambiental[MATERIAL-1]);
  	void setDifusa(GLfloat difusa[MATERIAL-1]);
 	void setEspecular(GLfloat especular[MATERIAL-1]);
 	void setBrillo(GLfloat brillo);
	


};

#endif

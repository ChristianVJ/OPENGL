/*Para implementar las fuentes se definen en el programa las variables globales, estructu-
ras o instancias de clase que almacenan los parámetros de cada una de las fuentes de luz que
se planean usar. Para cada fuente de luz, se debe guardar: su color Si , su tipo (un valor lógico que indique si es direccional o posicional), su posición (para las fuentes posicionales), y su dirección en coordenadas esféricas (para las direccionales). Al menos para la fuente dada en coordenadas esfericas, se guardarán asimismo los valores a y b Para cada fuente de luz, se definirá una función (o habrá método de clase común) que se encarge de activarla. Aquí activar una fuente significa que en OpenGL se habilite su uso y que se configuran sus parámetros en función del valor actual de las variables globales que describen dicha fuente.*/


#include <vector>
#include <GL/glut.h>
#include <ctype.h>
#include <GL/gl.h>
#include "stdio.h"
#include "Tipo_luz_material.h"
#include <string.h>
#include "vertex.h"


#ifndef _LIGHT_SOURCE_H_
#define _LIGHT_SOURCE_H_

class FuenteLuz {

    private:

	GLenum luz;		
        _vertex3f color; 	// Color de la fuente
        tipo_luz tipo;     	// Tipo de fuente (direccional o posicional)
	GLfloat posicion[4]; 	// Posicion de la fuente ¿4?
        GLfloat y;		// dirección y de la fuente // longitud
        GLfloat x;		// dirección x de la fuente // latitud

    public:

        FuenteLuz(GLenum luz, _vertex3f color, tipo_luz tipo, GLfloat posicion[4], GLfloat y, GLfloat x);
	
	// en OpenGL se habilita su uso y se configuran sus parámetros en función del valor actual de las variables globales que describen dicha fuente

        void Activar_fuente();
        void Desactivar_fuente();


};


#endif




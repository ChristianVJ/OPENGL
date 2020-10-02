/*Será necesario definir en el programa las variables o instancias que almacenan los pará-
metros de cada uno de los materiales que se planean usar. Para cada material, se almacenará
la reflectividad ambiental (M A ) la difusa (M D ), la especular (M S ) y el exponente de brillo
(e). Cada reflectividad es un array con 4 valores float: las tres componentes RGB más la
cuarta componente (opacidad) puesta a 1 (opaco). Asimismo, un material puede llevar aso-
ciada una textura o no llevarla. Si la lleva, junto con el material se almacenan los parámetros
de dicha textura (un puntero a ellos), descritos más arriba en el documento. Si el material
no lleva textura, el citado puntero será nulo.

Después se definirán funciones o métodos para activar cada uno de los materiales. Cuan
do se activa un material, se habilita la iluminación en OpenGL, y se configuran los paráme-
tros de material de OpenGL usando las variables o instancias descritas en el párrafo anterior.

Para los materiales que lleven asociada una textura, se llamará a la función o método pa-
ra activar dicha textura, descrita anteriormente. Si el material no lleva textura, se deben
deshabilitar las texturas en OpenGL.*/

#include <vector>
#include <GL/gl.h>
#include "jpg_imagen.hpp"
#include "textura_imagen.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <GL/glut.h>

#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#define MATERIAL 4

class Material

 {
    private:

	bool iluminado;
	GLfloat ambiental [MATERIAL];
	GLfloat difusa [MATERIAL];
	GLfloat especular [MATERIAL];
	GLfloat brillo;
	Textura * textura;
	GLuint identificador_textura;

    public:

        Material(); // Si el material NO lleva textura
        Material(const char * material_archivo); // Si el material SI lleva textura
	~Material();
        void Activar_materiales();
	void setAmbiental(GLfloat ambiental[MATERIAL-1]);
        void setDifusa(GLfloat difusa[MATERIAL-1]);
        void setEspecular(GLfloat especular[MATERIAL-1]);
        void setBrillo(GLfloat brillo);

        GLfloat * getAmbiental() const;
        GLfloat * getDifusa() const;
        GLfloat * getEspecular() const;
        GLfloat getBrillo() const;

 };

#endif

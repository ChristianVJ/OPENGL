#include "mine.h"
#include <vector>
#include <iostream>
#include "vertex.h"
#include <stdlib.h>
#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include "file_ply_stl.h"
#include <cmath>


using namespace std;

Minecraft :: Minecraft() {
  this->modo = 1;
  Por_Defecto();
}

/******************************************************************************************************/
/************************************* DIBUJA ESFERA***************************************************/
/******************************************************************************************************/


void Minecraft :: draw_sphere(GLint slices, GLint stacks) {
  switch(this->modo) {
      case 1:
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // VERTICES
        glutSolidSphere(1.0,slices, stacks);
        break;
      case 2:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // LINEAS
        glutWireSphere(1.0,slices, stacks);
        break;
      case 3:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // SOLIDO
        glutSolidSphere(1.0,slices, stacks);
        break;
      case 4:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // AJEDREZ
        glutSolidSphere(1.0,slices, stacks);
        break;

    }

}

/******************************************************************************************************/
/************************************* DIBUJA CUBO  ***************************************************/
/******************************************************************************************************/


void Minecraft :: draw_cube() {
  switch(this->modo) {
      case 1:
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // VERTICES
        glutSolidCube(1.0);
        break;
      case 2:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // LINEAS
        glutSolidCube(1.0);
        break;
      case 3:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // SOLIDO
        glutSolidCube(1.0);
        break;
      case 4: 
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // AJEDREZ
        glutSolidCube(1.0);

        break;
    }
}

/******************************************************************************************************/
/************************************* DIBUJA CILINDRO ************************************************/
/******************************************************************************************************/


void Minecraft :: draw_cylinder(){
  static GLUquadricObj * qobj = NULL; 	// Crear objeto
  if(qobj == NULL) {
    qobj = gluNewQuadric();   		// Nuevo objeto
  }
  switch(this->modo){
    case 1:
      gluQuadricDrawStyle(qobj, GLU_POINT); // VERTICES
      break;
    case 2:
      gluQuadricDrawStyle(qobj, GLU_LINE); // LINEAS
      break;
    case 3:
      gluQuadricDrawStyle(qobj, GLU_FILL); // SOLIDO
      break;
    case 4:
      gluQuadricDrawStyle(qobj, GLU_FILL); // AJEDREZ
      break;

  }
  gluCylinder(qobj,0.3,0.3,0.5,25,25);
}


/******************************************************************************************************/
/************************************* MODO DE DIBUJO *************************************************/
/******************************************************************************************************/

void Minecraft :: Modo_de_dibujo_jerar (int modo) {this->modo = modo; }


/******************************************************************************************************/
/************************************ MODELO JERARQUICO ***********************************************/
/******************************************************************************************************/

void Minecraft::dibuja_todo()
{

glPushMatrix(); // MODELO BEGIN
glTranslatef(0,vuelo,0);
//glScalef(2,2,2); // Escala el objeto (MAYOR 1 , AUMENTA, MENOR 1, DISMINUYE)
		 // Deforma el objeto si no son iguales los 3 elementos
	
///////////////////////////////////////////////////////////////////////////////////////

glPushMatrix(); // Cabeza con dos ojos y dos fuentes de luz y AFRO BEGIN
	
	
	/*//1. Girar la cabeza
	glRotatef(cabeza_giro,0,1,0);

	// PELO BASE 

	glPushMatrix();
	glTranslatef(0,4.4,0);
	glColor3f(0.2,0.2,0.2);  
	glScalef(1.6,0.1,1.7);
	draw_cube();
	glPopMatrix();

	// PELO TRASERO 

	glPushMatrix();
	glTranslatef(0,3.6,-0.8);
	glColor3f(0.2,0.2,0.2);  
	glScalef(1.6,1.6,0.1);
	draw_cube();
	glPopMatrix();	

	 // CABEZA MINECRAFT

	glPushMatrix();
	glTranslatef(0,3.6,0);
	glColor3f(1,0.80,0.60);
	glScalef(1.5,1.5,1.5);
	draw_cube();
	glPopMatrix();


				// CEJA IZQ
				glPushMatrix();
				glTranslatef(-0.35,4,0.78);
				glScalef(0.6,0.1,0);
				glColor3f(0,0,0);
				draw_cube();
				glPopMatrix();

							// OJO DE COLOR
							glPushMatrix();
							glTranslatef(-0.277,3.8,0.77);
							glScalef(0.2,0.2,0);
							glColor3f(0,0,1);
							draw_cube();
							glPopMatrix();
						


							// RAYO IZQ
							glPushMatrix();
							glTranslatef(-0.27,3.8,0.8);
							glColor3f(1,0,0);  
							glutWireCone(0.05,laser,50,20);
							glPopMatrix();			


				// CEJA DCHA
				glPushMatrix();
				glTranslatef(+0.35,4,0.78);
				glScalef(0.6,0.1,0);
				glColor3f(0,0,0);
				draw_cube();
				glPopMatrix();

							// OJO DE COLOR
							glPushMatrix();
							glTranslatef(+0.277,3.8,0.77);
							glScalef(0.2,0.2,0);
							glColor3f(0,0,1);
							draw_cube();
							glPopMatrix();


							// RAYO	DCHA
							glPushMatrix();
							glTranslatef(+0.27,3.8,0.8);
							glColor3f(1,0,0);  
							glutWireCone(0.05,laser,50,20);
							glPopMatrix();			

	


				// BOCA
				glPushMatrix();
				glTranslatef(0,3.4,0.78);
				glScalef(0.2,0.1,0);
				glColor3f(0,0,0);
				draw_cube();
				glPopMatrix();
*/


glRotatef(180,0,1,0);

	// a

	glPushMatrix();
	glTranslatef(0,4.4,0);
	glutWireTorus(2.0, 5.0, 20, 20);
	glPopMatrix();

	// b

	glPushMatrix();
	glTranslatef(0,3.6,-0.8);
	glRotatef(cabeza_giro,0,1,0);
	glutWireTorus(2.0, 5.0, 20, 20);
	glPopMatrix();	

	// c

	glPushMatrix();
	glTranslatef(0,3.6,-0.8);
	glRotatef(cabeza_giro,0,1,0);
	glutWireTorus(2.0, 5.0, 20, 20);
	glPopMatrix();	


glPopMatrix(); // Cabeza con dos ojos y dos fuentes de luz BEGIN


/////////////////////////////////////////////////////////////////////////////////////////////
	
	// CUELLO

	glPushMatrix();
	glTranslatef(0,2.9,0);
	glColor3f(1,0.80,0.60); 
	glScalef(0.5,0.2,0.5);
	draw_cube();
	glPopMatrix();


	// TRONCO

	glPushMatrix();
	glTranslatef(0,1.7,0);
	glColor3f(0,0,0.8);  
	glScalef(1.5,2.2,0.7);
	draw_cube();
	glPopMatrix();	
	
	// CAPA

	glPushMatrix();
	glTranslatef(0,1.8,-0.9);
	glRotatef(30,1,0,0);
	glColor3f(1,0,0);  
	glScalef(1.5,2.2,0.1);
	draw_cube();
	glPopMatrix();
		
	
	//BRAZO DCHA PART1

	glPushMatrix();
	glTranslatef(1,2.45,0);
	glRotatef(20,0,0,0);
	glColor3f(0,0,0.8); 
	glScalef(0.6,0.8,0.8);
	draw_cube();
	glPopMatrix();	

			//BRAZO DCHA PART2

			glPushMatrix();
			glTranslatef(1,1.7,0);
			glRotatef(20,0,0,0);
			glColor3f(1,0.80,0.60);
			glScalef(0.5,1.5,0.7);
			draw_cube();
			glPopMatrix();


	//BRAZO IZQ PART1

	glPushMatrix();
	glTranslatef(-1,2.45,0);
	glRotatef(20,0,0,0);
	glColor3f(0,0,0.8);  
	glScalef(0.6,0.8,0.8);
	draw_cube();
	glPopMatrix();

			//BRAZO IZQ PART2

			glPushMatrix();
			glTranslatef(-1,1.7,0);
			glRotatef(20,0,0,0);
			glColor3f(1,0.80,0.60);  
			glScalef(0.5,1.5,0.7);
			draw_cube();
			glPopMatrix();



	//CINTURON

	glPushMatrix();
	glTranslatef(0,0.7,0);
	glColor3f(1,0,0);
	glScalef(1.56,0.41,0.77);
	draw_cube();
	glPopMatrix();
		
			
	//PIERNA DERECHA 

	glPushMatrix();
	glTranslatef(0.4,-0.28,0);
	glColor3f(0,0,1);
	glScalef(0.75,2,0.7);
	draw_cube();
	glPopMatrix();

			//PIE DERECHO

			glPushMatrix();
			glTranslatef(0.4,-1.3,0);
			glColor3f(1,0,0);
			glScalef(0.8,0.4,0.8);
			draw_cube();
			glPopMatrix();
	
						// PROPULSOR DERECHO
						glPushMatrix();
						glTranslatef(0.3,-1.5,0);
						glRotatef(270,1,0,0);
						glColor3f(1,0,0);  
						glutWireCone(propulsor,1,50,20);
						glPopMatrix();		


	//PIERNA IZQUIERDA 

	glPushMatrix();
	glTranslatef(-0.4,-0.28,0);
	glColor3f(0,0,1);
	glScalef(0.75,2,0.7);
	draw_cube();
	glPopMatrix();


			//PIE IZQUIERDO 
			glPushMatrix();
			glTranslatef(-0.4,-1.3,0);
			glColor3f(1,0,0);
			glScalef(0.8,0.4,0.8);
			draw_cube();
			glPopMatrix();

						// PROPULSOR IZQUIERDO 
						glPushMatrix();
						glTranslatef(-0.3,-1.5,0);
						glRotatef(270,1,0,0);
						glColor3f(1,0,0);  
						glutWireCone(propulsor,1,100,20);
						glPopMatrix();		




glPopMatrix();
}

void Minecraft::Por_Defecto(){
	cabeza_giro = 0;
	laser = 0;
	vuelo = 0;
	propulsor = 0;	
}


void Minecraft::cabeza_giro_derecha(){
	cabeza_giro-=2.1;
}

void Minecraft::cabeza_giro_izquierda(){
	cabeza_giro+=2.1;
}

void Minecraft::activa_laser(){
	laser = 60;
}

void Minecraft::desactiva_laser(){
	laser = 0;
}	

void Minecraft::volar_arriba(){
	 vuelo += 0.5;
	 propulsor = 0.75;
}
void Minecraft::volar_abajo(){
	 vuelo -= 0.5;
	 propulsor = 0;
}		



void Minecraft :: visualizar_modelo_jerarquico() {

    switch(this->modo) {

      case 1:glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // VERTICES
	     glPointSize(2.0);
      break;
      case 2: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // LINEAS
      break;
      case 3: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // SOLIDO
      break;
      case 4: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // AJEDREZ
      break;

      default:glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
      break;

    }
	glPushMatrix();
    dibuja_todo();
	 glPopMatrix();
}


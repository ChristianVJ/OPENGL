#include "socom.h"
#include <vector>
#include <iostream>
#include "vertex.h"
#include <stdlib.h>
#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include "file_ply_stl.h"
#include "vertex.h"
#include <cmath>


using namespace std;

Socom :: Socom() {
  this->modo = 1;
}


/******************************************************************************************************/
/************************************* DIBUJA ESFERA***************************************************/
/******************************************************************************************************/


void Socom :: draw_sphere(GLint slices, GLint stacks) {
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


void Socom :: draw_cube() {
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


void Socom :: draw_cylinder(){
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

void Socom :: Modo_de_dibujo_jerar (int modo) {this->modo = modo; }


/******************************************************************************************************/
/************************************ MODELO JERARQUICO ***********************************************/
/******************************************************************************************************/

void Socom :: dibuja_todo()
{

glPushMatrix(); // MODELO BEGIN
glRotatef(giro_socom,0,1,0);
glTranslatef(0.0,desplazamiento_socom,0.0);

		// CUBO BASE DE LA RECAMARA
  		 glPushMatrix();
 		 glTranslatef(0.0,1.465,0);
     		 glScalef(0.2,0.13,1.5);
		 draw_cube();
		 glPopMatrix();

			// CUBO SUPERIOR DE LA BASE DE LA RECAMARA
  			glPushMatrix();
 			glTranslatef(0.0,1.55,0);
      			glScalef(0.1,0.04,1.5);
			draw_cube();
			glPopMatrix();

			//CUBO SUPERIOR FINO DERECHO DE LA RECAMARA
			glPushMatrix();
 			glTranslatef(0.12,1.435,0);
      			glScalef(0.03,0.07,1.5);
			draw_cube();
			glPopMatrix();

			//CUBO SUPERIOR FINO IZQUIERDO DE LA RECAMARA
			glPushMatrix();
  			glTranslatef(-0.12,1.435,0);
     			glScalef(0.03,0.07,1.5);
			draw_cube();
			glPopMatrix();

			//CILINDRO DE LA BASE
  			glPushMatrix();
  			glTranslatef(0.0,1.465,0.03);
      			glScalef(0.2,0.13,1.6);
			draw_cylinder();
			glPopMatrix();

		//SILENCIADOR
  		glPushMatrix();
  		glTranslatef(0.0,1.465,0.8);
       	 	glScalef(0.31,0.24,1.7);
		draw_cylinder();
		glPopMatrix();	


		//SOPORTE PARA LA LUZ
  		glPushMatrix();
  		glTranslatef(0.0,1.15,0.4);
      		glScalef(0.2,0.5,0.7);
		draw_cube();
		glPopMatrix();
		
			//CILINDRO LUZ
 			glPushMatrix();
  			glTranslatef(0.0,1,0.24);
      			glScalef(0.2,0.13,1.1);
			draw_cylinder();
			glPopMatrix();	

			// LUZ
  			glPushMatrix();
  			glTranslatef(0.0,1,3.7);
     			glRotatef(180,1,0,0);
			glutWireCone(luz2,luz,20,50);
			glPopMatrix();


		// CUBO INFERIOR DE LA BASE PARA EL LASER
  		glPushMatrix();
  		glTranslatef(0.0,1.34,0.0);
     		glScalef(0.2,0.1,1.5);
		draw_cube();
		glPopMatrix();

			//CILINDRO LASER
  			glPushMatrix();
  			glTranslatef(0.0,1.34,0.005);
     			glScalef(0.2,0.13,1.6);
			draw_cylinder();
			glPopMatrix();

			//RAYO LASER
  			glPushMatrix();
  			glTranslatef(0.0,1.34,10.7);
	 		glRotatef(180,1,0,0);
			glutWireCone(0.01,laser,20,50);
			glPopMatrix();


		// AGARRE
  		glPushMatrix();
		glTranslatef(0.0,1,-0.49);
 		glRotatef(10,1,0,0);
      		glScalef(0.2,0.8,0.4);
		draw_cube();
		glPopMatrix();

			//CARGADOR
 			glPushMatrix();
			glTranslatef(0.0,1,-0.49);
 			glRotatef(10,1,0,0);
      			glScalef(0.1,0.7,0.3);
			draw_cube();
			glPopMatrix();
		

		//GATILLLO
  		glPushMatrix();
		glTranslatef(0.0,1.2,-0.24);
 		glRotatef(10,1,0,0);
      		glScalef(0.2,0.3,0.1);
		draw_cube();
		glPopMatrix();
		
			//PARA EL GATILLO
  			glPushMatrix();
  			glTranslatef(0.0,1.05,-0.13);
      			glScalef(0.2,0.02,0.44);
			draw_cube();
			glPopMatrix();


 glPopMatrix();

}

/******************************************************************************************************/
/****************************** FUNCIONES DE MOVIMIENTO ***********************************************/
/******************************************************************************************************/

void Socom::giro_derecha_socom(){
	giro_socom-=2.1;
}
void Socom::giro_izquierda_socom(){
	giro_socom+=2.1;
}
void Socom::subir_socom(){
	desplazamiento_socom+=0.1;
}
void Socom::bajar_socom(){
	desplazamiento_socom-=0.1;
}
void Socom::activa_laser(){
	laser = 10;
}
void Socom::desactiva_laser(){
	laser = 0;
}	
void Socom::activa_luz(){
	luz = 3;
	luz2 = 0.2;
}
void Socom::desactiva_luz(){
	luz = 0;
	luz2 = 0;
}
void Socom::abrir_socom(){
	corredera += 0.1;
}
void Socom::unir_socom(){
	corredera -= 0.1;
}



/******************************************************************************************************/
/************************************* VISUALIZAR MODELO JERARQUICO ***********************************/
/******************************************************************************************************/


void Socom :: visualizar_modelo_jerarquico() {

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


#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include <iostream> 
#include "jpg_imagen.hpp"
// #include "user_code.h"
#include "vertex.h"
#include "file_ply_stl.h"
#include "figura.h"
#include "socom.h"
#include "mine.h"
#include "Cocacola.h"
#include "Tipo_luz_material.h"
#include "fuente_luz.h"
#define BUFSIZE 512

using namespace std;

enum Tipo {VACIO=0, ARCH_PLY, ARCH_PERFIL, MOD_JERAR, MOD_JERAR2, P4};

Figura Figura1; // objeto de figura ply
Figura Figura2; // objeto de figura revolucionada
Figura * peonMadera;
Figura * peonBlanco;
Figura * peonNegro;
Socom socom; // objeto de modelo jerarquico
Minecraft minecraft; // objeto de modelo jerarquico

bool isP4 = false; //Modo practica 4

const char *rotation_body_file = "perfil.ply";
Cocacola * coca = NULL;

//Fuentes de Luz
FuenteLuz * source1 = NULL;
FuenteLuz * source2 = NULL;

//Variable que destaca el estado de dibujo. PLY, ROTACIONAL, HIERARCHY
Tipo tipo = VACIO; //inicialmente no hay objeto cargado
Tipo UltimoTipo = VACIO;
//Variable que destaca el modo de visualizacion
visual_t visualization = POINT;
visual_t last_visualization = POINT;

static GLfloat spin = 0.0;
static GLfloat spin2 = 0.0;

// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
//int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;
int UI_window_pos_x=80,UI_window_pos_y=80,UI_window_width=800,UI_window_height=800;


//**************************************************************************
//
//***************************************************************************

void clear_window()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
glShadeModel(GL_FLAT);
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}

//Modo practica 4
  void p4_scene(){
    glPushMatrix();
    glScalef(3.0,3.0,3.0);
    coca->Dibujar_lata(visualization);
    glPopMatrix();
    glPushMatrix();
    glScalef(0.5,0.5,0.5);
    glPushMatrix();
    glTranslatef(0.0,1.5,4.0);
    glPushMatrix();
    GLfloat shiny = 100.0;
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
    peonMadera->Dibujar(visualization);
    glPopMatrix();
    glTranslatef(3.5,0.0,0.0);
    peonBlanco->Dibujar(visualization);
    glTranslatef(3.5,0.0,0.0);
    peonNegro->Dibujar(visualization);
    glPopMatrix();
    glPopMatrix();
  }

//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{

 switch(tipo) {
    case ARCH_PLY: Figura1.Dibujar(visualization); break;
    case ARCH_PERFIL: Figura2.Dibujar(visualization); break;
    case MOD_JERAR2: minecraft.visualizar_modelo_jerarquico(); break;	
    case P4: p4_scene(); break;
  }

}

//**************************************************************************
// Dibuja la escena
//***************************************************************************

void draw_scene(void)
{
clear_window();
change_observer();
draw_axis();
draw_objects();
    GLfloat positional[] = {-3.0,-15.0, 1.0, 1.0};
    GLfloat directional[] = {0.0,0.0,1.0,0.0};
    if(tipo == P4) {
      tipo_luz type1 = DIRECTIONAL;
      tipo_luz type2 = POSITIONAL;

      source1 = new FuenteLuz(GL_LIGHT0, _vertex3f(1.0,1.0,1.0), type2, positional, 0.0, 0.0);
      source2 = new FuenteLuz(GL_LIGHT1, _vertex3f(0.6,0.6,0.6), type1, directional, spin, spin2);


      source1->Activar_fuente();
      source2->Activar_fuente();
    }
    else{
      glDisable(GL_LIGHTING);
      if(source1!= NULL)
        source1->Desactivar_fuente();
      if(source2 != NULL)
        source2->Desactivar_fuente();
    }
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{

// Cambios para no sufrir deformaciones en el modelo

float ratio;	// <----
ratio = (float) Alto1 / (float) Ancho1; // <----
Window_height = Window_width*ratio; // <----
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************


bool p4_keys(unsigned char Tecla)
{
  bool actualizar = true;
  switch(toupper(Tecla)) {
    case '1':
    visualization = ILUM_PLANO;
    glutPostRedisplay();
    break;
    case '2':
    visualization = ILUM_SOFT;
    glutPostRedisplay();
    break;
    case '4':
    isP4 = false;
    tipo = UltimoTipo;
    visualization = last_visualization;
    break;
    case 'A':
    spin = (spin + 3);
    glutPostRedisplay();
    break;
    case 'Z':
    spin = (spin - 3);
    glutPostRedisplay();
    break;
    case 'X':
    spin2 += 3;
    glutPostRedisplay();
    break;
    case 'C':
    spin2 -= 3;
    glutPostRedisplay();
    break;
    default:
    glutPostRedisplay();
    break;
  }
  return actualizar;

}



bool p1_to_p3_keys(unsigned char Tecla){

 bool actualizar = true;
  switch (Tecla) {

	// Selecciona según el valor seleccionado (de 1-4) el modelo que va a usarse

    case 'Q': exit(0); break;
    case '1': tipo = ARCH_PLY; break; 		// archivo ply
    case '2': tipo = ARCH_PERFIL; break; 	// archivo perfil
    case '3': tipo = MOD_JERAR; break; 		// modelo jerarquico
    case '4': isP4 = true; 
    UltimoTipo = tipo;
    tipo = P4;
    last_visualization = visualization;
    visualization = ILUM_PLANO;
    break; 	

	// Selecciona según el valor seleccionado, el modo de visualización. 

    case 'p': // en vertices
    visualization = POINT;
    glutPostRedisplay();
    break;

    case 'l': // en lineas
    visualization = LINE;
    glutPostRedisplay();
    break;

    case 's': // en solido
    visualization = FILL;
    glutPostRedisplay();
    break;

    case 'a': // en ajedrez
    visualization = CHECKERED;
    glutPostRedisplay();
    break;

    case 'B': 
	if(tipo == MOD_JERAR2) { // Desplazar eje y arriba
	minecraft.cabeza_giro_derecha();
	glutPostRedisplay();
	}
    break;
    case 'b': 
	if(tipo == MOD_JERAR2) { // Desplazar eje y abajo
	minecraft.cabeza_giro_izquierda();
	glutPostRedisplay();
	}
    break;
    case 'N': 
	if(tipo == MOD_JERAR2) { // Desplazar eje y arriba
	minecraft.activa_laser();
	glutPostRedisplay();
	}
    break;
    case 'n': 
	if(tipo == MOD_JERAR2) { // Desplazar eje y abajo
	minecraft.desactiva_laser();
	glutPostRedisplay();
	}
    break;
    case 'M': 
	if(tipo == MOD_JERAR2) { // Desplazar eje y arriba
	minecraft.volar_arriba();
	glutPostRedisplay();
	}
    break;
    case 'm': 
	if(tipo == MOD_JERAR2) { // Desplazar eje y abajo
	minecraft.volar_abajo();
	glutPostRedisplay();
	}
    break;

    default: glutPostRedisplay(); break;

  }

return actualizar;

}





void normal_keys(unsigned char Tecla1,int x,int y)
{

  //En base a la tecla tocada, se determina que se dibuja y como
  bool actualizar = true;;
  switch (Tecla1) {
    case 'Q': exit(0); break;
    case 27: exit(0); break;
    default:
    switch(isP4) {
      case true:
      actualizar = p4_keys(Tecla1);
      glutPostRedisplay();
      break;
      case false:
      actualizar = p1_to_p3_keys(Tecla1);
      glutPostRedisplay();
      break;
      default:
      glutPostRedisplay(); break;

    }
    if(actualizar)
      glutPostRedisplay();
    break;


  }

}
	

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(const char * file1)
{
// se inicalizan la ventana y los planos de corte
Window_width=.5;
Window_height=.5;
Front_plane=1;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=40*Front_plane; //POSICIÓN DE LA CAMARA
Observer_angle_x=10;
Observer_angle_y=10;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(0,0,0,0);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,UI_window_width,UI_window_height);

// Cargamos el modelo ply del perfil y lo revolucionamos. Se visualiza en la tecla '2'
Figura1.Constructor(file1);
Figura2.revolucionar("perfil");


  GLfloat whiteSpecular[] = {1.0, 1.0, 1.0};
  GLfloat blackSpecular[] = {0.0,0.0,0.0};
  GLfloat lowAmbient[] = {0.3, 0.3, 0.3};
  GLfloat a[] = {0.1,0.1,0.1};

  peonMadera = new Figura("text-madera.jpg");
  peonMadera->revolucionar(rotation_body_file);
  peonMadera->setAmbiental(a);
  peonMadera->setDifusa(whiteSpecular);
  peonMadera->setEspecular(whiteSpecular);
  peonMadera->setBrillo(30);


  peonBlanco = new Figura();
  peonBlanco->revolucionar(rotation_body_file);
  peonBlanco->setAmbiental(lowAmbient);
  peonBlanco->setDifusa(whiteSpecular);
  peonBlanco->setEspecular(blackSpecular);
  peonBlanco->setBrillo(30);

  peonNegro = new Figura();
  peonNegro->revolucionar(rotation_body_file);
  peonNegro->setAmbiental(blackSpecular);
  peonNegro->setDifusa(lowAmbient);
  peonNegro->setEspecular(whiteSpecular);
  peonNegro->setBrillo(30);

  coca = new Cocacola();

}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

     if(argc!=2)
   	cout << "El formato no es correcto. Introduce ./practica1 (nombrearchivoply.ply)" << endl;	

    // se indica las caracteristicas que se desean para la visualización con OpenGL
    // Las posibilidades son:
    // GLUT_SIMPLE -> memoria de imagen simple
    // GLUT_DOUBLE -> memoria de imagen doble
    // GLUT_INDEX -> memoria de imagen con color indizado
    // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
    // GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
    // GLUT_DEPTH -> memoria de profundidad o z-bufer
    // GLUT_STENCIL -> memoria de estarcido
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // posicion de la esquina inferior izquierdad de la ventana
    glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

    // tamaño de la ventana (ancho y alto)
    glutInitWindowSize(UI_window_width,UI_window_height);

    // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
    // al bucle de eventos)
    glutCreateWindow("PRACTICA INFORMATICA GRAFICA");

    // asignación de la funcion llamada "dibujar" al evento de dibujo
    glutDisplayFunc(draw_scene);
    // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
    glutReshapeFunc(change_window_size);
    // asignación de la funcion llamada "tecla_normal" al evento correspondiente
    glutKeyboardFunc(normal_keys);
    // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
    glutSpecialFunc(special_keys);

    // funcion de inicialización
     initialize(argv[1]);

    // inicio del bucle de eventos
    glutMainLoop();
    return 0;
}

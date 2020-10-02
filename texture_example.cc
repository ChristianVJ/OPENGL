#include <stdio.h>
#include <GL/glut.h>

#include "texture_example.h"
#include "textura.h"

enum {MENU_ANIMACION_SI,MENU_ANIMACION_NO,MENU_PROYECCION_PERSPECTIVA,
			MENU_PROYECCION_PARALELA,MENU_SALIR} _entradasMenu;


float AnguloY=0, AnguloX=0, RadioObservador=10,TamanioVentana=1;
bool Animacion=false;//true;
bool CambioAngulo=false,CambioRadio=false;
int Boton;
int PosicionInicialX,PosicionInicialY;
_tipoProyeccion TipoProyeccion;

//**************************************************************************
//
//***************************************************************************

void limpiarVentana()
{

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//**************************************************************************
//
//***************************************************************************

void cambiarProyeccion(_tipoProyeccion TipoProyeccion1)
{

// se indican los valores de la proyeccion segun el tipo
if (TipoProyeccion1==PROYECCION_PERSPECTIVA)
	{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();  
	//(MinimoVentanaMundo,XMaximoVentanaMundo,YMinimoVentanaMundo,YMaximoVentanaMundo,
	//  PlanoDelantero>0,PlanoTrasero>PlanoDelantero)
	glFrustum(-TamanioVentana,TamanioVentana,-TamanioVentana,TamanioVentana,1,20);
	}
else
	{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();  
	// (MinimoVentanaMundo,XMaximoVentanaMundo,YMinimoVentanaMundo,YMaximoVentanaMundo,
	//  PlanoDelantero,PlanoTrasero)
	glOrtho(-TamanioVentana,TamanioVentana,-TamanioVentana,TamanioVentana,-10,10);
	}
}

//**************************************************************************
//
//***************************************************************************

void cambiarObservador1()
{
// posicion del observador					
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();  
glTranslatef(0,0,-RadioObservador);
glRotatef(AnguloX,1,0,0);
glRotatef(AnguloY,0,1,0);
}

//**************************************************************************
//
//***************************************************************************

void dibujarEjes()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-10,0,0);
glVertex3f(10,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-10,0);
glVertex3f(0,10,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-10);
glVertex3f(0,0,10);
glEnd();
}


//**************************************************************************
//
//***************************************************************************

void dibujarObjeto()
{
float Pos=2;

// abilitacion de la textura
glEnable(GL_TEXTURE_2D);

glBegin(GL_TRIANGLES);
glTexCoord2f(0,1);
glVertex3f(-Pos,Pos,0);
glTexCoord2f(0,0);
glVertex3f(-Pos,-Pos,0);
glTexCoord2f(1,0);
glVertex3f(Pos,-Pos,0);

glTexCoord2f(1,0);
glVertex3f(Pos,-Pos,0);
glTexCoord2f(1,1);
glVertex3f(Pos,Pos,0);
glTexCoord2f(0,1);
glVertex3f(-Pos,Pos,0);
glEnd();

glDisable(GL_TEXTURE_2D);
}


//**************************************************************************
//
//***************************************************************************

void dibujar(void)
{

limpiarVentana();
cambiarObservador1();
dibujarEjes();
dibujarObjeto();
glPopMatrix();
glFlush();
glutSwapBuffers();
}


/***************************************************************************/
//
/***************************************************************************/

void cambiarTamanioVentana(int Ancho1,int Alto1)
{

glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


/***************************************************************************/
//
/***************************************************************************/

void teclaNormal(unsigned char Tecla1,int x,int y)
{

if (Tecla1=='q' || Tecla1=='Q') exit(0);
}

/***************************************************************************/
//
/***************************************************************************/

void teclaEspecial(int Tecla1,int x,int y)
{

}


/***************************************************************************/
//
/***************************************************************************/

void raton(int Boton,int Estado1,int x,int y)
{

if (Boton==GLUT_LEFT_BUTTON)
	{
	if (Estado1==GLUT_DOWN) 
		{
    CambioAngulo=true;
    PosicionInicialX=x;
		PosicionInicialY=y;
  	}
	else 
		{//Estado1==GLUT_UP
    CambioAngulo=false;
  	}
	}
if (Boton==GLUT_MIDDLE_BUTTON) 
	{
	if (Estado1==GLUT_DOWN) 
		{
    CambioRadio=true;
    PosicionInicialX=x;
		PosicionInicialY=y;
  	}
	else 
		{//Estado1==GLUT_UP
    CambioRadio=false;
  	}
	}
}

/***************************************************************************/
//
/***************************************************************************/

void movimientoActivo(int x,int y)
{
static int Contador1;

if (CambioAngulo==true) 
	{// se cambian los angulo de la posicion
  AnguloY+=(x-PosicionInicialX);
  AnguloX+=(y-PosicionInicialY);
  PosicionInicialX=x;
	PosicionInicialY=y;
	}
if (CambioRadio==true)
	{
	if (TipoProyeccion==PROYECCION_PERSPECTIVA)
		{// se cambian el radio de la posicion
	  RadioObservador+=(y-PosicionInicialY);
		PosicionInicialY=y;
		}
	else
		{// proyeccion paralela
		TamanioVentana+=(y-PosicionInicialY);
		PosicionInicialY=y;
		cambiarProyeccion(TipoProyeccion);
		}
	}
glutPostRedisplay();
}


/***************************************************************************/
//
/***************************************************************************/

void desocupado(void)
{

AnguloY++;
glutPostRedisplay();
}


/***************************************************************************/
//
/***************************************************************************/

void menuPrincipal(int Valor)
{

switch (Valor) 
	{
	case MENU_SALIR:
  	exit(0);
  	break;
	default:
		break;
	}
glutPostRedisplay();
}


/***************************************************************************/
//
/***************************************************************************/

void menuAnimacion(int Valor)
{

switch (Valor) 
	{
	case MENU_ANIMACION_SI:
		Animacion=true;
   	glutIdleFunc(desocupado);
  	break;
	case MENU_ANIMACION_NO:
		Animacion=false;
		glutIdleFunc(NULL);
  	break;
	default:
		break;
	}
glutPostRedisplay();
}

/***************************************************************************/
//
/***************************************************************************/

void menuProyeccion(int Valor)
{

switch (Valor) 
	{
	case MENU_PROYECCION_PERSPECTIVA:
		TipoProyeccion=PROYECCION_PERSPECTIVA;
		cambiarProyeccion(TipoProyeccion);
  	break;
	case MENU_PROYECCION_PARALELA:
		TipoProyeccion=PROYECCION_PARALELA;
		cambiarProyeccion(TipoProyeccion);
  	break;
	default:
		break;
	}
glutPostRedisplay();
}


/***************************************************************************/
//
/***************************************************************************/

void init(void)
{

glEnable(GL_DEPTH_TEST);

glMatrixMode(GL_PROJECTION);
glFrustum(-10,10,-10,10,5,100);
glMatrixMode(GL_MODELVIEW);
glTranslatef(0,0,-10);

glClearColor(1,1,1,1);
glClearDepth(1.0);
glEnable(GL_DEPTH_TEST);
}


/***************************************************************************/
//
/***************************************************************************/

int main(int argc, char **argv)
{
int XMinimoVentanaX,YMinimoVentanaX,XTamanioVentanaX,YTamanioVentanaX;
char NombreVentana[]={"gluat_animacion"};
int MenuPrincipal,MenuAnimacion,MenuProyeccion;
_textura Textura1;
char NomFichero1[250];
_pixel Pixel1(255,0,0,1);


if (argc<2)
	{
	printf("Uso:\n ejemplo_textura nombre_fichero.tif\n");
	exit(-1);
	}
strcpy(NomFichero1,argv[1]);

/*
Textura1.iniciar(40,40);
Textura1.pixeles()[0]=Pixel1;
Textura1.igualar(0,1,Pixel1);
printf("Valor x=%x\n",&(Textura1.pixeles()));
printf("Valor x=%x\n",&(Textura1.pixeles())[1]);
*/

XMinimoVentanaX=50;
YMinimoVentanaX=50;
XTamanioVentanaX=500;
YTamanioVentanaX=500;

glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowPosition(XMinimoVentanaX,YMinimoVentanaX);
glutInitWindowSize(XTamanioVentanaX,YTamanioVentanaX);
glutCreateWindow(NombreVentana);
glutDisplayFunc(dibujar);
//glutReshapeFunc(cambiarTamanioVentana);
glutKeyboardFunc(teclaNormal);
//glutSpecialFunc(teclaEspecial);
glutMouseFunc(raton);
glutMotionFunc(movimientoActivo);
if (Animacion==true) glutIdleFunc(desocupado);

// creacion de un menu flotante
// primero se crean los submenus de niveles mas bajos para engancharlos
// con menus de nivel mas alto
MenuProyeccion=glutCreateMenu(menuProyeccion);
glutAddMenuEntry("Perspectiva",MENU_PROYECCION_PERSPECTIVA);
glutAddMenuEntry("Paralela",MENU_PROYECCION_PARALELA);

MenuAnimacion=glutCreateMenu(menuAnimacion);
glutAddMenuEntry("SI",MENU_ANIMACION_SI);
glutAddMenuEntry("NO",MENU_ANIMACION_NO);

MenuPrincipal=glutCreateMenu(menuPrincipal);
glutAddSubMenu("Animacion",MenuAnimacion);
glutAddSubMenu("Proyeccion",MenuProyeccion);
glutAddMenuEntry("Salir", MENU_SALIR);
glutAttachMenu(GLUT_RIGHT_BUTTON);


init();

// tipo de proyeccion
TipoProyeccion=PROYECCION_PERSPECTIVA;
cambiarProyeccion(TipoProyeccion);

// el producto de matrices no es conmutativo
// el orden de las transformaciones es importante
cambiarObservador1();


// se lee el fichero de la textura
if (Textura1.leer(NomFichero1)==-1)
	{
	printf("No se ha podido leer correctamente la textura\n");
	exit(-1);
	}


printf("ancho=%d alto=%d\n",Textura1.ancho(),Textura1.alto());
// parametros de definicion de la textura
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

// parametros de aplicacion de la textura
glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

// asignacion de la textura
glTexImage2D(GL_TEXTURE_2D,0,4,Textura1.ancho(),Textura1.alto(),0,GL_RGBA,GL_UNSIGNED_BYTE,&(Textura1.pixeles()[0]));

glutMainLoop();
return 0;             
}


#include "figura.h"
#include "stdlib.h"
#include "stdio.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <ctype.h>
#include <cmath>
#include <iostream>
#include <vector>
#include "vertex.h"
#include "file_ply_stl.h"
#include <cassert>


using namespace std;


Figura :: ~Figura() {
  if(material != NULL)
  {
    delete material;
  }
}

/******************************************************************************************************/
/**************************** MODO SIN TEXTURA *********************************************/
/******************************************************************************************************/

Figura :: Figura() { // sin textura
  material = new Material();
}


/******************************************************************************************************/
/************************************* MODO CON TEXTURA *********************************************/
/******************************************************************************************************/

Figura :: Figura(const char * archivo_textura) { // con textura
  material = new Material(archivo_textura);
}


/******************************************************************************************************/
/******************************************** CONSTRUCTOR *********************************************/
/******************************************************************************************************/


 void Figura::Constructor(const char * filename) {

  ply::read(filename, v_vertices_ply, v_caras_ply); 

  for (int i=0; i<v_vertices_ply.size(); i+=3)
  {
    _vertex3f aux;
    aux.x = v_vertices_ply[i];
    aux.y = v_vertices_ply[i+1];
    aux.z = v_vertices_ply[i+2];
    this-> Vertices.push_back(aux);
  }

  for (int i=0; i<v_caras_ply.size(); i+=3){

    _vertex3ui aux2;
    aux2._0 = v_caras_ply[i];
    aux2._1 = v_caras_ply[i+1];
    aux2._2 = v_caras_ply[i+2];
    this->Caras.push_back(aux2);

  }
}

/******************************************************************************************************/
/************************ MODO DE VISUALIZACIÓN A DIBUJAR *********************************************/
/******************************************************************************************************/


void Figura :: Dibujar(visual_t visualization){

if(visualization >= 1 && visualization <= 6){
   glPointSize(5);

   switch(visualization) {
    case POINT: glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);   // PUNTOS
    break;
    case LINE: glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);    // LINEAS
    break; 
    case FILL:
    case CHECKERED: glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); // SOLIDO
    break;
    case ILUM_PLANO:
    case ILUM_SOFT: glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);    // AJEDREZ
    break;

    default: glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);  // POR DEFECTO, PUNTOS
    break;
  }

   /*2*/	
   // Modo con iluminación y sombreado plano: se activa el modo de sombreado plano de OpenGL, y se envían 
   // con begin/end los triángulos, usando la tabla de normales de triángulos

  /*Este método consiste en calcular una única intensidad para cada polígono. Una vez calculada la intensidad
  de cada polígono, se visualizan todos los puntos del mismo polígono con una única intensidad. Este método es 
  muy rápido y preciso si las luces y el observador están lejos. Pero presenta el inconveniente de que hay 
  discontinuidad de intensidad entre los polígonos. Este método es el más ineficiente y menos usado de los tres. */

  glEnable(GL_RESCALE_NORMAL);
  //glEnable(GL_NORMALIZE);

  if(visualization ==  ILUM_PLANO)
  {
    material -> Activar_materiales();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glShadeModel(GL_FLAT); // Para poder visionar la iluminacion plana
    glBegin(GL_TRIANGLES);

    for( int i=0; i<Caras.size() ;i++ ){

      if(!v_texturas.empty())

      glTexCoord2d(v_texturas[Caras[i]._0 ]._0 , v_texturas[Caras[i]._0 ]._1); // textura
      glNormal3f(normal_caras[i].x, normal_caras[i].y, normal_caras[i].z); // normal de iluminacion
      glVertex3f(Vertices[Caras[i]._0].x,Vertices[Caras[i]._0].y,Vertices[Caras[i]._0].z); //Caras

      glTexCoord2d(v_texturas[Caras[i]._1 ]._0 , v_texturas[Caras[i]._1 ]._1);
      glNormal3f(normal_caras[i].x, normal_caras[i].y, normal_caras[i].z);
      glVertex3f(Vertices[Caras[i]._1].x,Vertices[Caras[i]._1].y,Vertices[Caras[i]._1].z);

      glTexCoord2d(v_texturas[Caras[i]._2 ]._0 , v_texturas[Caras[i]._2 ]._1);
      glNormal3f(normal_caras[i].x, normal_caras[i].y, normal_caras[i].z);
      glVertex3f(Vertices[Caras[i]._2].x,Vertices[Caras[i]._2].y,Vertices[Caras[i]._2].z);

    }

    glEnd();
}
    /*2*/
    // Modo con iluminación y sombreado de suave (Gouroud): se activa el modo de sombreado suave, y se 
    // envían los vértices usando la tabla de normales de vértices.

    /* El método consiste en calcular la intensidad de los pixeles a lo largo de la línea de escaneo por
     interpolación. Este método elimina la discontinuidad de la intensidad entre los polígonos que presentaba 
     el método anterior. */

 else if(visualization == ILUM_SOFT)
  {
    glShadeModel(GL_SMOOTH); // Para poder visionar en modo Gouroud/Suave
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    material->Activar_materiales();
    glBegin(GL_TRIANGLES);

    for( int i=0;i<Caras.size();i++ ){

      if(!v_texturas.empty())

      glTexCoord2d(v_texturas[Caras[i]._0 ]._0 , v_texturas[Caras[i]._0 ]._1);
      glNormal3f(normal_vertices[Caras[i]._0 ].x, normal_vertices[Caras[i]._0 ].y, normal_vertices[Caras[i]._0 ].z);
      glVertex3f(Vertices[Caras[i]._0].x,Vertices[Caras[i]._0].y,Vertices[Caras[i]._0].z);

      glTexCoord2d(v_texturas[Caras[i]._1 ]._0 , v_texturas[Caras[i]._1 ]._1);
      glNormal3f(normal_vertices[Caras[i]._1 ].x, normal_vertices[Caras[i]._1 ].y, normal_vertices[Caras[i]._1 ].z);
      glVertex3f(Vertices[Caras[i]._1].x,Vertices[Caras[i]._1].y,Vertices[Caras[i]._1].z);

      glTexCoord2d(v_texturas[Caras[i]._2 ]._0 , v_texturas[Caras[i]._2 ]._1);
      glNormal3f(normal_vertices[Caras[i]._2 ].x, normal_vertices[Caras[i]._2 ].y, normal_vertices[Caras[i]._2 ].z);
      glVertex3f(Vertices[Caras[i]._2].x,Vertices[Caras[i]._2].y,Vertices[Caras[i]._2].z);

    }
    glEnd();
}
else {
  glBegin(GL_TRIANGLES);
  for (int i = 0; i <Caras.size(); i++)
  {
    if(visualization == CHECKERED){
      if(i % 2 == 0)
        glColor3f(0,1,0);
      else
        glColor3f(0,0,1);
    }
    else
      glColor3f(0,0,1);
      glDisable(GL_LIGHTING);
      glDisable(GL_TEXTURE_2D);
    glVertex3f( Vertices[Caras[i]._0].x, Vertices[Caras[i]._0].y, Vertices[Caras[i]._0].z );
    glVertex3f( Vertices[Caras[i]._1].x, Vertices[Caras[i]._1].y, Vertices[Caras[i]._1].z );
    glVertex3f( Vertices[Caras[i]._2].x, Vertices[Caras[i]._2].y, Vertices[Caras[i]._2].z );

  }
  glEnd();
}

}

}

/******************************************************************************************************/
/******************************************** REVOLUCIONAR ********************************************/
/******************************************************************************************************/

/*3 - MODIFICACIÓN PARA TEXTURAS */

void Figura::revolucionar(const char * filename){ 

Constructor(filename);

puntos_perfil = this->Vertices.size();	
int divisiones = 24;						
float grados = 2*M_PI/(divisiones*1.0);  // Grados según las divisiones que introduzcamos en radianes
_vertex3f aux;

	 for(int i=0; i<divisiones; i++){  // En cada división formamos los puntos generados a partir del perfil por esta.    
			for(int j=0; j<puntos_perfil; j++){ 

  			aux.x =  (Vertices[j].x) * cos(grados) + (Vertices[j].z) * sin(grados);
 			aux.y =  Vertices[j].y;	
  			aux.z = -(sin(grados) * (Vertices[j].x)) + (Vertices[j].z) * cos(grados);
                  
			if(!(aux.x==0 && aux.y==0 && aux.z==0)) //Eliminamos ceros del vector de vértices (fallo)
                   	this-> Vertices.push_back(aux) ;

 			}
  		grados += 0.2617;
	 }


int i,j = 0;
_vertex3ui aux1;

//------------CARAS CENTRALES-----------//

// Ejemplo =  1* FOR =  6 puntos de perfil,  144 en vertices. 144-6 (los iniciales) = 138
// Incrementamos en puntos_perfil i+=6
// 2* FOR = j=0; j<0+6-1 = 5 ; j++


for(i=0; i<Vertices.size()-puntos_perfil; i+=puntos_perfil){
 	for(j = i;j<i+puntos_perfil-1;j++){

			// Rellenamos de abajo a arriba lasCaras
		// Cara 1
   		aux1._0 = j; // 0 // 1
   		aux1._1 = j+puntos_perfil+1; // 7 // 8
  		aux1._2 = j+puntos_perfil; // 6 // 7
  		Caras.push_back(aux1);

		// Cara 2
   		aux1._0 = j; // 0 // 1
   		aux1._1 = j+1; // 1 // 2
   		aux1._2 = j+puntos_perfil+1; // 7 // 8
   		Caras.push_back(aux1);
 	}
}


//------------CARAS CENTRALES DE VERTICES INICIALES CON FINALES-----------//

// 1* FOR  6 puntos de perfil,  z=0 k= 144 en vertices 144-6 = 138; z < 6-1 = 5

_vertex3ui aux2;

for(int z=0, k=Vertices.size()-puntos_perfil ; z<puntos_perfil-1; z++,k++){

				// Rellenamos de abajo a arriba lasCaras
		// Cara 1
		aux2._0 = k; // 138
 		aux2._1 = z+1; // 1
 		aux2._2 = z; // 0
 		Caras.push_back(aux2);

		// Cara 2
 		aux2._0 = k; // 138
 		aux2._1 = k+1; // 139
 		aux2._2 = z+1; // 1
 		Caras.push_back(aux2);
}

//------------TAPAS SUPERIOR E INFERIOR-----------//

_vertex3f aux3;
aux3.x=0;
aux3.y=Vertices[0].y; //punto en la tapa inferior central
aux3.z=0;
this->Vertices.push_back(aux3);

aux3.x=0;
aux3.y=Vertices[Vertices.size()-2].y; // punto en la tapa superior central
aux3.z=0;
this->Vertices.push_back(aux3);


	
//------------TAPA INFERIOR-----------//

//ultimo vertice y el primero

_vertex3ui aux4;

aux4._0 = Vertices.size()-2-puntos_perfil; //144-2-6 = 136
aux4._1 = Vertices.size()-2; // 144 - 2 = 142
aux4._2 = 0; // 0
Caras.push_back(aux4);

 _vertex3ui aux5;

for(int i=0;i<Vertices.size()-2;i+=puntos_perfil){ // 142 // 6

  aux5._0 = i; // 0 // 6
  aux5._1 = i+puntos_perfil; // 6 // 12 
  aux5._2 = Vertices.size() -2; // 142 // 142
 Caras.push_back(aux5);
}
			
			
//------------TAPA SUPERIOR-----------//

//ultimo vertice y el primero

_vertex3ui aux6;

  aux6._0 = Vertices.size()-3; //El ultimo punto del ultimo vertice //  141
  aux6._1 = Vertices.size()-1; //El punto del centro // 143
  aux6._2 = puntos_perfil-1; //El ultimo punto del primer vertice // 5
 Caras.push_back(aux6);

_vertex3ui aux7;

  for(int i=puntos_perfil-1;i<Vertices.size()-3;i+=puntos_perfil){ // 5 // 141 // 6

   aux7._0 = i; // 5 // 11
   aux7._1 = Vertices.size()-1; // 143 // 143
   aux7._2 = i+puntos_perfil; // 5+6 = 11  // 17
  Caras.push_back(aux7);

 }

//////////////////// CALCULO DE LAS NORMALES A LAS CARAS ////////////////////

_vertex3f BA,CA;

 for (int i = 0; i <Caras.size(); i++){

   // 1.... Si se definen dos vectores BA,CA ... incluimos en vectorAB los vértices B y A de esa cara ...
   BA = Vertices[Caras[i]._1] - Vertices[Caras[i]._0]; 
  // 2.... Si se definen dos vectores BA,CA ... incluimos en vectorAC los vértices C y A de esa cara ...
   CA = Vertices[Caras[i]._2] - Vertices[Caras[i]._0];

   //3. Cross_product realiza el producto vectorial y normalize lo normaliza. 
   normal_caras.push_back((BA.cross_product(CA)).normalize());

 }

//////////////////// CALCULO DE LAS NORMALES A LOS VÉRTICES ///////////////////


 // 1. Limpieza del vector normales vertices
 this->normal_vertices.clear();
 // 2. Se rellena a ceros. 
 this->normal_vertices.resize(Vertices.size(), _vertex3f(0,0,0));

// 3. Recorremos las normales a las caras para calcular la de los vértices
 for(int i=0;i<this->normal_caras.size();i++)
 {

  this->normal_vertices[Caras[i]._0] += this->normal_caras[i];
  this->normal_vertices[Caras[i]._1] += this->normal_caras[i];
  this->normal_vertices[Caras[i]._2] += this->normal_caras[i];

 }

 // 4. Normalizamos el resultado, y obtenemos los normales de vertices
 for(int i=0;i<this->normal_vertices.size();i++)
  this->normal_vertices[i].normalize();


/*3 RELLENO DE TEXTURAS */


_vertex2f pairValues;
vector <GLfloat> tmpVector; // Vector para el calculo y almacenamiento de las distancias

float sum = 0.0;
tmpVector.push_back(sum);
for(int j = 1;j <this-> puntos_perfil;j++)
{
    //x y z
  sum += sqrt(pow(this->Vertices[j].x - this->Vertices[j-1].x,2) + pow(this->Vertices[j].y - this->Vertices[j-1].y,2) + pow(this->Vertices[j].z - this->Vertices[j-1].z,2));
  tmpVector.push_back(sum);
}

for(int i=0;i<int(grados) + 1;i++)
{
  pairValues.s = (float(i)/grados);
  for(int k = 0;k<tmpVector.size();k++)
  {
    pairValues.t = 1.0 - tmpVector[k]/tmpVector[tmpVector.size()-1];
    v_texturas.push_back(pairValues);
  }
}
}

////////////////////////////////////////////////////////////////////////////

void Figura :: setAmbiental(GLfloat ambiental[MATERIAL-1]){
  this->material->setAmbiental(ambiental);
}

void Figura :: setDifusa(GLfloat difusa[MATERIAL-1]){
  material->setDifusa(difusa);
}

void Figura :: setEspecular(GLfloat especular[MATERIAL-1]){
  material->setEspecular(especular);
}

void Figura :: setBrillo(GLfloat brillo){
  material->setBrillo(brillo);
}







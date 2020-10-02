#include <GL/gl.h>
#include <vector>
#include "vertex.h"

using namespace std; 

class Socom { // CLASE PARA EL MODELO JERARQUICO

private:
    
    int modo;						// Variable que representa el modo de dibujo
    void draw_cylinder();				// Dibujar_cilindro
    void draw_sphere(GLint slices, GLint stacks);	// Dibujar_esfera
    void draw_cube();					// Dibujar_cubo

  public:

    	Socom();
    	void Modo_de_dibujo_jerar(int modo);
   	void visualizar_modelo_jerarquico();
	void dibuja_todo();

	////////////////////////	
   	void giro_derecha_socom();
	void giro_izquierda_socom();	
	float giro_socom;
	////////////////////////
	void activa_laser();
	void desactiva_laser();
	void activa_luz();
	void desactiva_luz();
	float laser;
	float luz,luz2;
	////////////////////////
	void subir_socom();
	void bajar_socom();
	float desplazamiento_socom;
	////////////////////////
	void abrir_socom();
	void unir_socom();
	float corredera;

	

};



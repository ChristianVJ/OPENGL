#include <GL/gl.h>
#include <vector>
#include "vertex.h"

using namespace std; 

class Minecraft {

private:
    
    int modo;						// Variable que representa el modo de dibujo
    void draw_cylinder();				// Dibujar_cilindro
    void draw_sphere(GLint slices, GLint stacks);	// Dibujar_esfera
    void draw_cube();					// Dibujar_cubo

public:

    Minecraft(); // Inicializa los valores a 0
    void Modo_de_dibujo_jerar(int modo);
    void visualizar_modelo_jerarquico();
    void dibuja_todo();	
    void Por_Defecto();

	////////////////////////
	void cabeza_giro_derecha();
	void cabeza_giro_izquierda();	
	float cabeza_giro;
	////////////////////////
	void activa_laser();
	void desactiva_laser();
	float laser;
	////////////////////////
	void volar_arriba();
	void volar_abajo();
	float vuelo;
	float propulsor;
	////////////////////////
};


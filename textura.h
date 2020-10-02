/***************************************************************************
                          textura.h  -  description
                             -------------------
    begin                : Thu Nov 2 2000
    copyright            : (C) 2000 by 
    email                : 
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef TEXTURA
#define TEXTURA

#include "pixel.h"
#include <tiffio.h>

class _textura
{
public:

					_textura(void);
					~_textura();
bool		valida(){return Valida;};					
int		ancho(){return Ancho;};
int		alto(){return Alto;};
bool		comprimir(){return Comprimir;};
bool		ajustar(){return Ajustar;};
vector<_pixel>  &pixeles(){return Pixeles;};

_textura	&iniciar(int Ancho1,int Alto1,uint32 *Pixeles1=NULL);
_textura	&igualar(int Ancho1,int Alto1,uint32 *Pixeles1);
_textura	&igualar(_textura &Textura1);
_textura  &igualar(int Fila1,int Columna1,_pixel &Pixel1);
_pixel		&valor(int Fila1,int Columna1);
int		leer(char *NombreFichero1);
int		grabar(char *NombreFichero1);
_textura	&valida(bool Valida1);
_textura	&comprimir(bool Comprimir1);
bool  	ajustarDimensiones(int &Ancho1,int &Alto1);


protected:
bool Valida;
int Ancho;
int Alto;
bool Ajustar;
bool Comprimir;
vector<_pixel> Pixeles;
};

#endif

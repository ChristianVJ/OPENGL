/***************************************************************************
                          pixel.h  -  description
                             -------------------
    begin                : Fri Nov 3 2000
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
#ifndef PIXEL
#define PIXEL

#include <vector>

class _pixel
{
public:

				_pixel(unsigned char rojo1=0,unsigned char verde1=0,unsigned char azul1=0,unsigned char alfa1=255);
				
unsigned char	rojo(){return Rojo;};					
unsigned char	verde(){return Verde;};					
unsigned char	azul(){return Azul;};					
unsigned char	alfa(){return Alfa;};					
_pixel		&rojo(unsigned char rojo1);
_pixel		&verde(unsigned char verde1);
_pixel		&azul(unsigned char azul1);
_pixel		&alfa(unsigned char alfa1);
void			igualar(unsigned char rojo1=0,unsigned char verde1=0,unsigned char azul1=0,unsigned char alfa1=255);
void 			igualar(_pixel &pixel1);

protected:
unsigned char Rojo,Verde,Azul,Alfa;
};


#endif

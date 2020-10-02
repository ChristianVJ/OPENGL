/***************************************************************************
                          biblioTIFF.h  -  description
                             -------------------
    begin                : Tue Nov 7 2000
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
#ifndef BIBLIOTIFF
#define BIBLIOTIFF

#include "pixel.h"
#include "textura.h"
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <tiffio.h>     /* Sam Leffler's libtiff library. */

/* Some <math.h> files do not define M_PI... */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


class _imagenTIFF;


class _imagenTIFF
{
public:
TIFFRGBAImage Imagen;


int		leer(char *NomFichero,_textura &Textura1);
int		grabar(char *NomFichero,_textura &Textura1);
				
protected:
};

#endif

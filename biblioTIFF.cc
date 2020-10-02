/***************************************************************************
                          biblioTIFF.cc  -  description
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
#include "textura.h"
#include "biblioTIFF.h"

//*********************************************************************
//
//*********************************************************************
//*********************************************************************
//
//*********************************************************************

int _imagenTIFF::leer(char *NomFichero1,_textura &Textura1)
{
TIFF *Fichero1;
char emsg[1024];
tsize_t npixels;

// no hace falta hacer la inversion, ademas falla
int hasABGR=0;

Fichero1=TIFFOpen(NomFichero1, "r");
if (Fichero1==NULL)
	{
  printf("Error: no se puede abrir el fichero %s\n",NomFichero1);
  return(-1);
	}
	
if (TIFFRGBAImageBegin(&Imagen,Fichero1,0,emsg))
	{
  npixels=(tsize_t)(Imagen.width*Imagen.height);
  Textura1.iniciar(Imagen.width, Imagen.height);
  if (TIFFRGBAImageGet(&Imagen,(uint32 *) &(Textura1.pixeles()[0]),
  										Imagen.width,Imagen.height) == 0)
  	{
    TIFFError(NomFichero1, emsg);
    exit(1);
  	}
  }
#ifdef GL_EXT_abgr
if (glutExtensionSupported("GL_EXT_abgr")) hasABGR = 1;
#else
hasABGR = 0;
#endif

// If cannot directly display ABGR format, we need to reverse the component
//   ordering in each pixel. :-( */
if (!hasABGR)
	{
  int i;

  for (i = 0; i < npixels; i++)
  	{
    register unsigned char *cp = (unsigned char *) &(Textura1.pixeles()[0]);
    //&raster[i];
    int t;
		cp=cp+i;
		
    t = cp[3];
    cp[3] = cp[0];
    cp[0] = t;
    t = cp[2];
    cp[2] = cp[1];
    cp[1] = t;
  	}
	}

// OpenGL's default unpack (and pack) alignment is 4.  In the case of the
// data returned by libtiff which is already aligned on 32-bit boundaries,
// setting the pack to 1 isn't strictly necessary.

//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

// Linear sampling within a mipmap level.

// A TIFF file could be any size; OpenGL textures are allowed to have a
// width and height that is a power of two (32, 64, 128, etc.). To maximize
// the use of available texture memory, we scale the image to gluScaleImage
// to the next larger power of 2 width or height dimension (not exceeding
// 512, don't want to use too much texture memory!).  This rescaling can
// result in a bit of image bluring because of the resampling done by
// gluScaleImage.  An alternative would be to change the texture coordinates
// to only use a portion texture area.

if (Textura1.ajustar()==true)
	{
	int Ancho1,Alto1;
	
	Ancho1=Textura1.ancho();
	Alto1=Textura1.alto();
	if (Textura1.ajustarDimensiones(Ancho1,Alto1)==true)
		{
		_textura Textura2;
		
		Textura2.iniciar(Ancho1,Alto1);
		#ifdef GL_EXT_abgr
    #define APPROPRIATE_FORMAT (hasABGR ? GL_ABGR_EXT : GL_RGBA)
    #else
    #define APPROPRIATE_FORMAT GL_RGBA
    #endif


    gluScaleImage(APPROPRIATE_FORMAT,
      (GLsizei) Textura1.ancho(), (GLsizei) Textura1.alto(), GL_UNSIGNED_BYTE,
      &(Textura1.pixeles()[0]),Ancho1, Alto1, GL_UNSIGNED_BYTE,
      &(Textura2.pixeles()[0]));
    Textura1.igualar(Textura2);
    }
	}
else
	{
	int Ancho1,Alto1;
	
	Ancho1=Textura1.ancho();
	Alto1=Textura1.alto();
	if (Textura1.ajustarDimensiones(Ancho1,Alto1)==true)
		{
		printf("\bAdvertencia: la textura no se podra usar por no ajustarse el tamanio\n");
		return(-1);
		}
	}	
return(0);
}

//*********************************************************************
//
//*********************************************************************


int _imagenTIFF::grabar(char *NomFichero1,_textura &Textura1)
{
TIFF *Fichero1;
GLubyte *image, *p;
int Compresion1;
char Descripcion1[]="Sistema Alhambra";
unsigned int Ancho1,Alto1;
const int NumBytesPorPixel1=4;
int i;

Fichero1=TIFFOpen(NomFichero1, "w");
if (Fichero1==NULL)
	{
	printf("Error: no se puede abrir el fichero %s\n",NomFichero1);
  return(-1);
	}

Ancho1=Textura1.ancho();
Alto1=Textura1.alto();

TIFFSetField(Fichero1, TIFFTAG_IMAGEWIDTH, Ancho1);
TIFFSetField(Fichero1, TIFFTAG_IMAGELENGTH, Alto1);
TIFFSetField(Fichero1, TIFFTAG_BITSPERSAMPLE, 8);

// la compresion COMPRESSION_LZW se ha eliminado

if (Textura1.comprimir()==true) Compresion1=COMPRESSION_PACKBITS;
else Compresion1=COMPRESSION_NONE;
	
TIFFSetField(Fichero1, TIFFTAG_COMPRESSION, Compresion1);
TIFFSetField(Fichero1, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
TIFFSetField(Fichero1, TIFFTAG_SAMPLESPERPIXEL, NumBytesPorPixel1);
TIFFSetField(Fichero1, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
TIFFSetField(Fichero1, TIFFTAG_ROWSPERSTRIP, 1);
TIFFSetField(Fichero1, TIFFTAG_IMAGEDESCRIPTION, Descripcion1);
p=(GLubyte *) &(Textura1.pixeles()[0]);
for (i=Alto1-1;i>=0;i--)
	{
  if (TIFFWriteScanline(Fichero1, p, i, 0) < 0)
  	{
    free(image);
    TIFFClose(Fichero1);
    return 1;
  	}
  p+=Ancho1*sizeof(GLubyte)*NumBytesPorPixel1;
	}
TIFFClose(Fichero1);
return(0);
}

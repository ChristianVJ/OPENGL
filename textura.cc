/***************************************************************************
                          texturas.cc  -  description
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
#include "textura.h"
#include "biblioTIFF.h"

//*********************************************************************
//
//*********************************************************************
//*********************************************************************
//
//*********************************************************************

_textura::_textura(void)
{

Ancho=0;
Alto=0;
Ajustar=true;
Comprimir=true;
}

//*********************************************************************
//
//*********************************************************************

_textura::~_textura()
{
Ancho=0;
Alto=0;
Ajustar=false;
}

//*********************************************************************
//
//*********************************************************************

_textura &_textura::iniciar(int Ancho1,int Alto1,uint32 *Pixeles1)
{

if (Ancho1==0 || Alto1==0)
  {
	Ancho=0;
	Alto=0;
  }
else
  {
  if (Ancho1>0 & Alto1>0)
    {
    Ancho=Ancho1;
    Alto=Alto1;
    if (Pixeles1!=NULL)
    	{
			Pixeles.resize(Ancho*Alto);
			for (int i=0;i<Ancho*Alto;i++) Pixeles[i]=Pixeles1[i];
    	}
    else
    	{
			Pixeles.resize(Ancho*Alto);
    	}
    }
  }
return(*this);
}

//*********************************************************************
//
//*********************************************************************

_textura &_textura::igualar(int Ancho1,int Alto1,uint32 *Pixeles1)
{

if (Ancho1==0 || Alto1==0)
  {
	Ancho=0;
	Alto=0;
  }
else
  {
  if (Ancho1>0 & Alto1>0)
    {
    Ancho=Ancho1;
    Alto=Alto1;
    if (Pixeles1!=NULL)
    	{
			Pixeles.resize(Ancho*Alto);
			for (int i=0;i<Ancho*Alto;i++) Pixeles[i]=Pixeles1[i];
    	}
    else
    	{
			Pixeles.resize(Ancho*Alto);
    	}
    }
  }
return(*this);
}

//*********************************************************************
//
//*********************************************************************

_textura &_textura::igualar(_textura &Textura1)
{

if (Textura1.ancho()==0 || Textura1.alto()==0)
  {
	Ancho=0;
	Alto=0;
	Pixeles.clear();
  }
else
  {
  if (Textura1.ancho()>0 & Textura1.alto()>0)
    {
    Ancho=Textura1.ancho();
    Alto=Textura1.alto();
   	Pixeles=Textura1.pixeles();
    }
  }
return(*this);
}

//*********************************************************************
//
//*********************************************************************

_textura &_textura::igualar(int Fila1,int Columna1,_pixel &Pixel1)
{

Pixeles[Fila1*Ancho+Columna1]=Pixel1;
return(*this);
}

//*********************************************************************
//
//*********************************************************************

_pixel &_textura::valor(int Fila1,int Columna1)
{

return(Pixeles[Fila1*Ancho+Columna1]);
}


//*********************************************************************
//
//*********************************************************************

int _textura::leer(char *NombreFichero1)
{
_imagenTIFF ImagenTIFF;
char *Puntero1=NombreFichero1+(strlen(NombreFichero1)-4);
char Terminacion1[5];
char Terminacion2[6];

strcpy(Terminacion1,Puntero1);
strcpy(Terminacion2,Puntero1-1);
if ((strcmp(Terminacion2,".tiff")==0) || (strcmp(Terminacion2,".TIFF")==0) ||
  	(strcmp(Terminacion1,".tif")==0) || (strcmp(Terminacion1,".TIF")==0))

  {
  if (ImagenTIFF.leer(NombreFichero1,*this)==0) valida(true);
  else
    {
    valida(false);
    return(-1);
    }
  }
else
  {
  printf("Error: no coincide el tipo de textura con los permitidos (bmp y tiff)_n");
  }

return(0);
}

//*********************************************************************
//
//*********************************************************************

int _textura::grabar(char *NombreFichero1)
{
_imagenTIFF ImagenTIFF;
char *Puntero1=NombreFichero1+(strlen(NombreFichero1)-4);
char Terminacion1[6];

if ((strcmp(".tif",Terminacion1)==0) || (strcmp(".TIF",Terminacion1)==0) ||
		(strcmp(".tiff",Terminacion1)==0) || (strcmp(".TIFF",Terminacion1)==0))
	{
  if (ImagenTIFF.grabar(NombreFichero1,*this)==0) valida(true);
  else valida(false);
	}

return(0);
}

//*********************************************************************
//
//*********************************************************************

_textura	&_textura::valida(bool Valida1)
{

Valida=Valida1;
return(*this);
}

//*********************************************************************
//
//*********************************************************************

_textura	&_textura::comprimir(bool Comprimir1)
{

Comprimir=Comprimir1;
return(*this);
}

//*********************************************************************
//
//*********************************************************************

bool _textura::ajustarDimensiones(int &Ancho1,int &Alto1)
{
int AnchoSup1,AltoSup1,AnchoInf1,AltoInf1;
int DifAnchoSup1,DifAltoSup1,DifAnchoInf1,DifAltoInf1;

AnchoSup1=1 << (int) ceil(log(Ancho1) / log(2.0));
AltoSup1=1 << (int) ceil(log(Alto1) / log(2.0));
AnchoInf1=1 << (int) floor(log(Ancho1) / log(2.0));
AltoInf1=1 << (int) floor(log(Alto1) / log(2.0));


if ((AnchoSup1==Ancho1 && AltoSup1==Alto) || (AnchoSup1==Ancho1 && AltoInf1==Alto) ||
    (AnchoInf1==Ancho1 && AltoSup1==Alto) || (AnchoInf1==Ancho1 && AltoInf1==Alto)) return(false);

DifAnchoSup1=AnchoSup1-ancho();
DifAltoSup1=AltoSup1-alto();
DifAnchoInf1=ancho()-AnchoInf1;
DifAltoInf1=alto()-AltoInf1;

if (DifAnchoInf1<=DifAnchoSup1) Ancho1=AnchoInf1;
else Ancho1=AnchoSup1;
if (DifAltoInf1<=DifAltoSup1) Alto1=AltoInf1;
else Alto1=AltoSup1;

return(true);
}

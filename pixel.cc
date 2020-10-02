/***************************************************************************
                          pixel.cc  -  description
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
#include "pixel.h"


//*********************************************************************
//
//*********************************************************************
//*********************************************************************
//
//*********************************************************************

_pixel::_pixel(unsigned char rojo1,unsigned char verde1,unsigned char azul1,unsigned char alfa1)
{
Rojo=rojo1;
Verde=verde1;
Azul=azul1;
Alfa=alfa1;
}

//*********************************************************************
//
//*********************************************************************

_pixel &_pixel::rojo(unsigned char rojo1)
{
Rojo=rojo1;
return(*this);
}

//*********************************************************************
//
//*********************************************************************

_pixel &_pixel::verde(unsigned char verde1)
{
Verde=verde1;
return(*this);
}

//*********************************************************************
//
//*********************************************************************

_pixel &_pixel::azul(unsigned char azul1)
{
Azul=azul1;
return(*this);
}

//*********************************************************************
//
//*********************************************************************

_pixel &_pixel::alfa(unsigned char alfa1)
{
Alfa=alfa1;
return(*this);
}

//*********************************************************************
//
//*********************************************************************

void _pixel::igualar(unsigned char rojo1,unsigned char verde1,unsigned char azul1,unsigned char alfa1)
{
Rojo=rojo1;
Verde=verde1;
Azul=azul1;
Alfa=alfa1;
}

//*********************************************************************
//
//*********************************************************************

void _pixel::igualar(_pixel &pixel1)
{
Rojo=pixel1.rojo();
Verde=pixel1.verde();
Azul=pixel1.azul();
Alfa=pixel1.alfa();
}


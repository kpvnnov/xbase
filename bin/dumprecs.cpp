/*  $Id: dumprecs.cpp,v 1.1.1.1 2001-11-12 13:22:20 peter Exp $

    Xbase project source code

    This sample program dumps Xbase records

    Copyright (C) 1997  StarTech, Gary A. Kunkel   

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Contact:

      Mail:
  
        Technology Associates, Inc.
        XBase Project
        1455 Deming Way #11
        Sparks, NV  89434
        USA

     Email:
       
       xbase@techass.com

     Website:

       xdb.sourceforge.net


    V 1.0   10/10/97   - Initial release of software
    V 1.5   1/2/98     - Added memo field support
    V 1.6a  5/1/98     - Added expression support
    V 1.7.4d 23/11/98  - Added exceptions support
    V 1.8   11/29/98   - Version 1.8 upgrade
*/

#include <xbase/xbase.h>

#ifdef HAVE_EXCEPTIONS
#include <xbase/xbexcept.h>
#endif

int main(int ac,char** av)
{
    if (ac <= 1) {
        cout <<
            "\nUsage: dumprecs filename...\n"
            ;
        return 1;
    }

    for (int i=1; i<ac; ++i) {
        char* filename = av[i];

  xbXBase x;
  xbDbf MyFile( &x );

#ifdef HAVE_EXCEPTIONS
   try {
#endif
            xbShort rc = MyFile.OpenDatabase(filename);
            if ( rc != XB_NO_ERROR) {
       cout << "Could not open file " << filename << " Error = " << rc << "\n";
       return 0;
     }

     cout << "\nLoop through forwards...\n";
     int i = 0;
     while(i<MyFile.NoOfRecords()) {
       MyFile.DumpRecord(i+1);
       i++;
     }

     MyFile.CloseDatabase();	/* close database */
#ifdef HAVE_EXCEPTIONS
 } catch (xbEoFException &x) {
            // ignore
 } catch (xbException &x) {
   printf("Error: %s\n", x.error());
 }
#endif
    }

    return 0;
}     


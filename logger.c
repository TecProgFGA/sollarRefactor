/*
// Library to implement a simple log in programs based on c language
*/

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
 
FILE *log_file ;

char* print_time()
{
    time_t t;
    char *buf;
     
    time(&t);
    buf = (char*)malloc(strlen(ctime(&t))+ 1);
     
    snprintf(buf,strlen(ctime(&t)),"%s ", ctime(&t));
    
    return buf;
}
void print_debug_log(char* filename, int line, char *fmt,...)
{
    va_list         list;
    char            *p, *r;
    int             e;
 
      log_file = fopen ("debug.log","a+");
    
    fprintf(log_file,"[%s][%s][line: %d] ",print_time(),filename,line);
    va_start( list, fmt );
 
    for ( p = fmt ; *p ; ++p )
    {
        if ( *p != '%' )//If simple string
        {
            fputc( *p,log_file );
        }
        else
        {
            switch ( *++p )
            {
                /* string */
            case 's':
            {
                r = va_arg( list, char * );
 
                fprintf(log_file,"%s", r);
                continue;
            }
 
            /* integer */
            case 'd':
            {
                e = va_arg( list, int );
 
                fprintf(log_file,"%d", e);
                continue;
            }
 
            default:
                fputc( *p, log_file );
            }
        }
    }
    va_end( list );
    fputc( '\n', log_file );
    fclose(log_file);
}
void print_error_log(char* filename, int line, char *fmt,...)
{
    va_list         list;
    char            *p, *r;
    int             e;
 
      log_file = fopen ("error.log","a+");
     
    fprintf(log_file,"[%s][%s][line: %d] ",print_time(),filename,line);
    va_start( list, fmt );
 
    for ( p = fmt ; *p ; ++p )
    {
        if ( *p != '%' )//If simple string
        {
            fputc( *p,log_file );
        }
        else
        {
            switch ( *++p )
            {
                /* string */
            case 's':
            {
                r = va_arg( list, char * );
 
                fprintf(log_file,"%s", r);
                continue;
            }
 
            /* integer */
            case 'd':
            {
                e = va_arg( list, int );
 
                fprintf(log_file,"%d", e);
                continue;
            }
 
            default:
                fputc( *p, log_file );
            }
        }
    }
    va_end( list );
    fputc( '\n', log_file );
    fclose(log_file);
}
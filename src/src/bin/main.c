/*
 * vim:ts=8:sw=3:sts=8:noexpandtab:cino=>3
 */
#include "term.h"
#include "enterm.h"

int
main(int argc, char **argv)
{

   Ecore_Evas  *ee;     /* ecore_evas */
   Evas        *evas;   /* evas       */
   Evas_Object *term;   /* terminal   */

   pw = find_user();

   char *home = 0;
   int ret = 0;
   ret = asprintf(&home, "HOME=%s", pw->pw_dir);
   if (home) {
	   putenv(home);
	   ret = chdir(pw->pw_dir);
	   free(home);
   } else {
	   putenv("HOME=/tmp");
	   ret = chdir("/tmp");
   }

   /* Let's initialize some stuff*/
   /*edje_init();*//* hold off for now */
   ecore_init();
   ecore_evas_init();/* We NEED this to get the UTF-8 stuff!!*/
   
   ee = ecore_evas_sdl_new(NULL, 320, 480, 0, 0, 0, 0);
   ecore_evas_show(ee);
   evas = ecore_evas_get(ee);

   term = term_new(evas);
   evas_object_show(term);
   enterm_init(ee, term);

   ecore_main_loop_begin();
   ecore_evas_shutdown();
   ecore_shutdown();

   return 0;
}

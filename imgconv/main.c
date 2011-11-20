#include <string.h>
#include <stdio.h>
#include <allegro.h>
#include <glib.h>

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define FILENAME      "input.lst"
#define TAM_FILENAME  2048 //size of filename in chars
#define SCALE 3

int main(int argc, char *argv[])
{
  int w = SCREEN_WIDTH;
  int h = SCREEN_HEIGHT;  
  FILE *f;
  gchar *filein, *fileout;
  BITMAP *bmpin, *bmpout, *bmpout_half;
  RGB *pal=NULL;

  allegro_init();  
  install_keyboard();
  install_timer();
  
  /* set the best color depth that we can find */
  set_color_depth(32);
  if (set_gfx_mode(GFX_AUTODETECT, w, h, 0, 0) != 0) {
    allegro_exit();
    allegro_message("Error setting graphics mode%s", allegro_error);
  }
  set_color_conversion(COLORCONV_TOTAL);
  set_alpha_blender();
  f = fopen(FILENAME, "r");
  if (!f) {
     allegro_exit();
    allegro_message("Can't open file: '%s'", FILENAME);
  }  
  
  //Allocate memory to filenames
  filein  = (gchar *) g_malloc(sizeof(gchar)*TAM_FILENAME);
  fileout = (gchar *) g_malloc(sizeof(gchar)*TAM_FILENAME);
  //Do the conversion
  while(!feof(f)) {
    fgets(filein, TAM_FILENAME, f);
    filein = g_strstrip(filein);
    strcpy(fileout, filein);
    fileout[strlen(fileout)-4] =  '\0';
    strcat(fileout, ".pcx");
    //    g_print("\"%s\" \"%s\"\n", filein, fileout);
    bmpin = load_bitmap(filein, pal);
    bmpout = create_bitmap(bmpin->w, bmpin->h);
    bmpout_half = create_bitmap(bmpin->w/SCALE, bmpin->h/SCALE);
    clear_to_color(bmpout,  makecol32(255, 0, 255));
    draw_trans_sprite(bmpout, bmpin, 0, 0);
    stretch_blit(bmpout, bmpout_half, 0,0,bmpin->w, bmpin->h, 0,0,bmpin->w/SCALE, bmpin->h/SCALE);
    save_pcx(fileout, bmpout_half, pal);
    clear_to_color(screen, makecol32(255,255,255));
    draw_sprite(screen, bmpout, 0, 0);
    rest(200);
    g_free(pal);
    g_free(bmpin);
    g_free(bmpout);
    g_free(bmpout_half);
  }

  textout(screen, font, "Press any key to exit...", 50,50,-1);
  while(!readkey());
  
  fclose(f);
  set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
//  allegro_message("Exiting Succesfully\n");
  
  return 0;
}

END_OF_MAIN();


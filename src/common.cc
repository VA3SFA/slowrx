#include "common.h"
#include <gtkmm.h>
#include <thread>

Glib::KeyFile config;

//std::vector<std::thread> threads(2);

std::string version_string() {
  return "0.7-dev";
}

// Clip to [0..255]
guint8 clip (double a) {
  if      (a < 0)   return 0;
  else if (a > 255) return 255;
  return  round(a);
}

// Clip to [0..1]
double fclip (double a) {
  if      (a < 0.0) return 0.0;
  else if (a > 1.0) return 1.0;
  return  a;
}

double deg2rad (double Deg) {
  return (Deg / 180) * M_PI;
}

double rad2deg (double rad) {
  return (180 / M_PI) * rad;
}

size_t maxIndex (std::vector<double> v) {
  const int n = sizeof(v) / sizeof(double);
  return distance(v.begin(), max_element(v.begin(), v.end()));
}

void ensure_dir_exists(std::string dir) {
  struct stat buf;

  int i = stat(dir.c_str(), &buf);
  if (i != 0) {
    if (mkdir(dir.c_str(), 0777) != 0) {
      perror("Unable to create directory for output file");
      exit(EXIT_FAILURE);
    }
  }
}


/*** Gtk+ event handlers ***/


// Quit
void evt_deletewindow() {
  gtk_main_quit ();
}

// Transform the NoiseAdapt toggle state into a variable
void evt_GetAdaptive() {
  //Adaptive = gui.tog_adapt->get_active();
}

// Manual Start clicked
void evt_ManualStart() {
  //ManualActivated = true;
}

// Manual slant adjust
void evt_clickimg(Gtk::Widget *widget, GdkEventButton* event, Gdk::WindowEdge edge) {
  /*static double prevx=0,prevy=0,newrate;
  static bool   secondpress=false;
  double        x,y,dx,dy,xic;

  (void)widget;
  (void)edge;

  if (event->type == Gdk::BUTTON_PRESS && event->button == 1 && gui.tog_setedge->get_active()) {

    x = event->x * (ModeSpec[CurrentPic.Mode].ImgWidth / 500.0);
    y = event->y * (ModeSpec[CurrentPic.Mode].ImgWidth / 500.0) / ModeSpec[CurrentPic.Mode].LineHeight;

    if (secondpress) {
      secondpress=false;

      dx = x - prevx;
      dy = y - prevy;

      //gui.tog_setedge->set_active(false);

      // Adjust sample rate, if in sensible limits
      newrate = CurrentPic.Rate + CurrentPic.Rate * (dx * ModeSpec[CurrentPic.Mode].PixelTime) / (dy * ModeSpec[CurrentPic.Mode].LineHeight * ModeSpec[CurrentPic.Mode].LineTime);
      if (newrate > 32000 && newrate < 56000) {
        CurrentPic.Rate = newrate;

        // Find x-intercept and adjust skip
        xic = fmod( (x - (y / (dy/dx))), ModeSpec[CurrentPic.Mode].ImgWidth);
        if (xic < 0) xic = ModeSpec[CurrentPic.Mode].ImgWidth - xic;
        CurrentPic.Skip = fmod(CurrentPic.Skip + xic * ModeSpec[CurrentPic.Mode].PixelTime * CurrentPic.Rate,
          ModeSpec[CurrentPic.Mode].LineTime * CurrentPic.Rate);
        if (CurrentPic.Skip > ModeSpec[CurrentPic.Mode].LineTime * CurrentPic.Rate / 2.0)
          CurrentPic.Skip -= ModeSpec[CurrentPic.Mode].LineTime * CurrentPic.Rate;

        // Signal the listener to exit from GetVIS() and re-process the pic
        ManualResync = true;
      }

    } else {
      secondpress = true;
      prevx = x;
      prevy = y;
    }
  } else {
    secondpress=false;
    //gui.tog_setedge->set_active(false);
  }*/
}

ProgressBar::ProgressBar(double maxval, int width) :
  maxval_(maxval), val_(0), width_(width) {
  set(0);
}

void ProgressBar::set(double val) {
  val_ = val;

  fprintf(stderr,"  [");
  double prog = val_ / maxval_;
  size_t prog_points = round(prog * width_);
  for (size_t i=0;i<prog_points;i++) {
    fprintf(stderr,"=");
  }
  for (size_t i=prog_points;i<width_;i++) {
    fprintf(stderr," ");
  }
  fprintf(stderr,"] %.1f %%\r",prog*100);
}

void ProgressBar::finish() {
  fprintf(stderr, "\n");
}
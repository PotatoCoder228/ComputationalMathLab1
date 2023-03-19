//
// Created by potato_coder on 14.02.23.
//

#include <stdbool.h>
#include "gtk-3.0/gtk/gtk.h"
#include "../../include/chart/gtk_chart.h"

typedef struct point{
    double x;
    double y;
}point;

void draw_grid(cairo_t* cr, guint width, guint height){
    cairo_set_line_width(cr, 0.5);
    guint g_w, g_h;
    g_w = 0.8*width;
    g_h = 0.8*height;
    int64_t step = g_w / 100;
    cairo_set_source_rgba(cr, 0, 0, 0, 0.7);

    int counter = 1;

    for (guint i = (guint) (0.1 * width); i < (0.9 * width); i += step) {
        cairo_move_to(cr, i, 0.1 * height);
        cairo_line_to(cr, i, 0.9 * height);
    }
    cairo_stroke(cr);

    counter = 0;
    step = g_h / 57;
    for (guint i = (guint) (0.5 * height); i > (guint) (0.1 * height); i -= step) {
        counter++;
        cairo_set_line_width(cr, 0.5);
        if(counter%5==1){
            cairo_set_line_width(cr, 1.5);
        }
        cairo_move_to(cr, 0.1 * width, i);
        cairo_line_to(cr, 0.9 * width, i);
        cairo_stroke(cr);
    }
    counter = 0;
    for (guint i = (guint) (0.5 * height); i < (guint) (0.9 * height); i += step) {
        counter++;
        cairo_set_line_width(cr, 0.5);
        if(counter%5==1){
            cairo_set_line_width(cr, 1.5);
        }
        cairo_move_to(cr, 0.1 * width, i);
        cairo_line_to(cr, 0.9 * width, i);
        cairo_stroke(cr);
    }
}

gboolean draw_callback(GtkWidget *widget, cairo_t *cr, gpointer data) {
    guint width, height;
    GtkStyleContext *context;

    context = gtk_widget_get_style_context(widget);

    GdkColor color;
    gdk_color_parse ("#fff", &color); //setting a color - you can also use RGB
    gtk_widget_modify_bg(widget, GTK_STATE_NORMAL, &color);

    width = gtk_widget_get_allocated_width(widget);
    height = gtk_widget_get_allocated_height(widget);

    gtk_render_background(context, cr, 0, 0, width, height);
    //сетка
    cairo_move_to(cr, 0.1 * width, 0.1 * height);
    cairo_line_to(cr, 0.1 * width, 0.9 * height);
    cairo_line_to(cr, 0.9 * width, 0.9 * height);
    cairo_move_to(cr, 0.9 * width, 0.9 * height);
    cairo_line_to(cr, 0.9 * width, 0.1 * height);
    cairo_line_to(cr, 0.1 * width, 0.1 * height);
    cairo_stroke(cr);


    draw_grid(cr, width, height);

    cairo_fill(cr);
    point array[5];
    array[0].x = 0;
    array[0].y = 0;
    array[1].x = 2;
    array[1].y = 4;
    array[2].x = 4;
    array[2].y = 16;
    array[3].x = 8;
    array[3].y = 64;
    cairo_stroke(cr);
    cairo_set_line_width(cr, 2);
    cairo_set_source_rgba(cr, 255,165,0, 0.5);
    //cairo_arc (cr, width / 2.0, height / 2.0, MIN (width, height) / 2.0, 0, 2 * G_PI);
    for (size_t i = 1; i < 4; i++) {
        if(i>0) {
            double prev_x = array[i-1].x*width/500 + (0.1 * width);
            double prev_y = -(array[i-1].y*height/500) + (height/2);
            double x = array[i].x*width/500 + (0.1 * width);
            double y = -(array[i].y*height/500) + (height/2);
            cairo_move_to(cr, prev_x, prev_y);//(-(array[i-1] * array[i-1])) + (0.9 * height)
            cairo_line_to(cr, x,y);
            cairo_stroke(cr);
        }
    }
    cairo_set_source_rgba(cr, 144, 144, 255, 0.8);
    for (size_t i = 0; i < 4; i++) {
        double x = array[i].x*width/500 + (0.1 * width);
        double y = -(array[i].y*height/500) + (height/2);
        //array[i] + (0.1 * width), (-y)+(0.9*height),
        cairo_arc(cr, x, y,  4, 0, 2 * G_PI);
        cairo_fill(cr);
        cairo_stroke(cr);
    }
    return FALSE;
}

G_MODULE_EXPORT void on_destroy() {
    gtk_main_quit();
}

void main_win_set_parameteres(GtkWidget *main_window, GError *error) {
    gtk_window_set_title(GTK_WINDOW (main_window), "ChartBuilder");
    gtk_window_set_icon_from_file(GTK_WINDOW (main_window),
                                  "/mnt/c/Users/sasha/Download/CountMathLabs/linear_equations_solver/resources/icons/chart_logo.png",
                                  &error);
    gtk_window_set_default_size(GTK_WINDOW (main_window), 1280, 720);
}

bool win_init(GtkBuilder *builder, GError *error) {
    GtkWidget *window;
    if (!gtk_builder_add_from_file(builder,
                                   "/mnt/c/Users/sasha/Download/CountMathLabs/linear_equations_solver/resources/glade_templates/main.glade",
                                   &error)) {
        g_critical ("Не вышло загрузить файл с UI : %s", error->message);
        g_error_free(error);
    }
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    main_win_set_parameteres(window, error);
    gtk_builder_connect_signals(builder, NULL);
    GtkWidget *area = GTK_WIDGET(gtk_builder_get_object(builder, "drawing_area"));;
    gtk_widget_set_size_request(area, 100, 100);
    g_signal_connect (G_OBJECT(area), "draw",
                      G_CALLBACK(draw_callback), NULL);
    gtk_widget_show_all(window);
    gtk_main();
    gtk_widget_destroy(window);
    return true;
}

bool build_gtk_chart(double *points_array) {
    gtk_init(0, NULL);
    GError *error = NULL;
    GtkBuilder *ui_builder;
    ui_builder = gtk_builder_new();
    win_init(ui_builder, error);
    if (error != NULL) {
        g_error_free(error);
    }
    return true;
}
#include <stdio.h>
#include "Oled.h"
#include "sdkconfig.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_dev.h"
#include "esp_lcd_panel_ssd1306.h"

#include "../../managed_components/lvgl__lvgl/lvgl.h"
#include "../../managed_components/espressif__esp_lvgl_port/include/esp_lvgl_port.h"

#include "driver/i2c_master.h"

#include "../../clock/include/clock.h"
#include "../../I2c/include/I2c.h"

#define LABEL_TEXT_AZ  1
#define LABEL_TEXT_N  2
#define LABEL_TEXT_E  3
#define LABEL_TEXT_W  4
#define LABEL_TEXT_S  5

#define  CANVAS_AZIMUT_WIDTH 34
#define CANVAS_AZIMUT_HEIGHT  26

#define  CANVAS_COMPASS_WIDTH 82
#define CANVAS_COMPASS_HEIGHT  28


static const char *TAG = "OLED : ";
//static i2c_master_bus_handle_t i2c_bus;

static lv_obj_t *label, *label1, *label2, *label3, *label4;
static lv_obj_t *scr;
static lv_disp_t *disp;

static lv_obj_t *line;
static lv_obj_t *line0;
//static lv_obj_t *line1;

static lv_obj_t* line1, *line2, *line3, *line4, *line5, *line6, *line7, *line8, *line9;
static lv_style_t lv_style_plain1,lv_style_plain2,lv_style_plain3,lv_style_plain4;
static lv_point_t p1[] = {  {55,8},  {55,24} };
static lv_point_t p2[] = {  {70,8}, {70,24} };
static lv_point_t p3[] = {  {85,8}, {85,24} };
static lv_point_t p4[] = {  {100,8}, {100,24} };
static lv_point_t p5[] = {  {115,8}, {115,24} };
static lv_point_t p6[] = {  {115,8}, {115,24} };
static lv_point_t p7[] = {  {115,8}, {115,24} };
static lv_point_t p8[] = {  {115,8}, {115,24} };
static lv_point_t p9[] = {  {115,8}, {115,24} };

static int azimut = 0;
static char stringAzimut[5] = "0"; 


static lv_draw_rect_dsc_t rect_dsc_azimut;
static lv_obj_t* canvasAzimut;
static lv_draw_label_dsc_t azimut_label_dsc;

static lv_obj_t* canvasCompass;
static lv_draw_label_dsc_t compass_label_dsc;

static lv_obj_t* chart;

// Définir la couleur blanc
lv_color_t white_color = LV_COLOR_MAKE(0, 0, 0);

/**** 
 * LOCAL
*/
bool lvglportlockDevice (uint32_t timeOut){
    return lvgl_port_lock(timeOut);
}

void lvglPortUnlockDevice(void){
    lvgl_port_unlock();
}

void setAzimut(int value){
    azimut = value;
}

int getAzimut (void){

    

    return azimut;
}

char* getStringAzimut(){

    sprintf (stringAzimut,"%03d",azimut);

    return stringAzimut;
}


/********
 * LABEL
 ********/

lv_obj_t* getLabel(int index){
    lv_obj_t* labelx = label;
    if (index == LABEL_TEXT_AZ)  {
        labelx = label;
    }
    else if (index == LABEL_TEXT_N) {
        labelx = label1;
    }    
    else if (index == LABEL_TEXT_E) {
        labelx = label2;
    }    
    else if (index == LABEL_TEXT_W) {
        labelx = label3;
    }    
    else if (index == LABEL_TEXT_S) {
        labelx = label4;
    }
    return labelx;
}

void createLabel (int index){
    lv_obj_t *scr = lv_disp_get_scr_act(disp);

    if (index == LABEL_TEXT_AZ)  {
        label = lv_label_create(scr);
        lv_label_set_text(label, "0");
    }
    else if (index == LABEL_TEXT_N) {
        label1 = lv_label_create(scr);
        lv_label_set_text(label1, "N");
    }
    else if (index == LABEL_TEXT_E) {
        label2 = lv_label_create(scr);
        lv_label_set_text(label2, "E");
    }
    else if (index == LABEL_TEXT_W) {
        label3 = lv_label_create(scr);
        lv_label_set_text(label3, "W");
    }
    else if (index == LABEL_TEXT_S) {
        label4 = lv_label_create(scr);
        lv_label_set_text(label4, "S");
    }
}

void setTextOled(int index, char *text){
        lv_label_set_text(getLabel(index), text);
}

void setTextRotation(int value){
    lv_disp_set_rotation(disp, value);
}

void setLongMode (int index, int value){
        lv_label_set_long_mode(getLabel(index), value); /* Circular scroll */
}

void setRecolor(int index, bool status) {
    lv_label_set_recolor(getLabel(index), status);
}

void setXPos(int index, int value){
    lv_obj_set_x(getLabel(index), value);
}

void setYPos(int index, int value){
    lv_obj_set_y(getLabel(index), value);
}

void setPos(int index, int xvalue, int yvalue){
    lv_obj_set_pos(getLabel(index), xvalue, yvalue);
}

/********************
 *  CANVAS
 *******************/

 lv_obj_t* getCanvas(int index){

    lv_obj_t* labelx = label;

        labelx = canvasAzimut;


    return labelx;
 }

lv_draw_label_dsc_t* getLabelDsc(int index){
    return &azimut_label_dsc;
}

 void setTextCanvasOled(int index, char* str){
   lv_canvas_fill_bg(getCanvas(0), lv_color_hex(0xFFFFFF), LV_OPA_COVER);
   lv_canvas_fill_bg(getCanvas(0), lv_palette_lighten(LV_PALETTE_GREY, 3), LV_OPA_COVER);
   lv_canvas_draw_text(getCanvas(0), 5, 6, 40, getLabelDsc(0), str);
 }

/***********
 * DRAW RECTANGLE
 ***********/

void drawRectangle(int x, int y, int dimx, int dimy, int size){
    lv_obj_t * obj = lv_obj_create(lv_scr_act());
    lv_obj_set_size(obj, dimx, dimy);
    lv_obj_set_pos(obj, x, y);

    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_bg_color(&style, lv_color_hex(0xFFFFFF));
    lv_style_set_border_color(&style, white_color);
    lv_style_set_border_width(&style, size);
    lv_obj_add_style(obj, &style, 0);
}



/****************
 * CLEAR SCREEN
 ***************/
void clearScreen (void){
    lv_obj_clean(lv_scr_act());
}

void initBoussole(void){
    line1 = lv_line_create(lv_scr_act());
    line2 = lv_line_create(lv_scr_act());
    line3 = lv_line_create(lv_scr_act());
    line4 = lv_line_create(lv_scr_act());
    line5 = lv_line_create(lv_scr_act()); 
    line6 = lv_line_create(lv_scr_act()); 
    line7 = lv_line_create(lv_scr_act()); 
    line8 = lv_line_create(lv_scr_act()); 
    line9 = lv_line_create(lv_scr_act()); 

    lv_style_init(&lv_style_plain1);
    lv_style_set_line_color(&lv_style_plain1, white_color);
    lv_style_set_line_width(&lv_style_plain1, 1); // Définir l'épaisseur de la ligne

    lv_style_init(&lv_style_plain2);
    lv_style_set_line_color(&lv_style_plain2, white_color);
    lv_style_set_line_width(&lv_style_plain2, 2); // Définir l'épaisseur de la ligne

    lv_style_init(&lv_style_plain3);
    lv_style_set_line_color(&lv_style_plain3, white_color);
    lv_style_set_line_width(&lv_style_plain3, 3); // Définir l'épaisseur de la ligne

    lv_style_init(&lv_style_plain4);
    lv_style_set_line_color(&lv_style_plain4, white_color);
    lv_style_set_line_width(&lv_style_plain4, 0); // Définir l'épaisseur de la ligne

    lv_obj_add_style(line1, &lv_style_plain3, LV_PART_MAIN);
    lv_obj_add_style(line2, &lv_style_plain1, LV_PART_MAIN);
    lv_obj_add_style(line3, &lv_style_plain4, LV_PART_MAIN);
    lv_obj_add_style(line4, &lv_style_plain1, LV_PART_MAIN);
    lv_obj_add_style(line5, &lv_style_plain3, LV_PART_MAIN);
    lv_obj_add_style(line6, &lv_style_plain1, LV_PART_MAIN);
    lv_obj_add_style(line7, &lv_style_plain4, LV_PART_MAIN);
    lv_obj_add_style(line8, &lv_style_plain1, LV_PART_MAIN);
    lv_obj_add_style(line9, &lv_style_plain3, LV_PART_MAIN);
}

void boussole (unsigned int value){

    setAzimut(value);
    azimut = value;

    int center = 78 ;
    int posInit = center;
    int posText = posInit;
    int delta = 18;
    char str[4];

    int ligne = 0;

    int ofsObj = 41;

    lv_obj_set_x(getLabel(LABEL_TEXT_N),ofsObj); 
    lv_obj_set_x(getLabel(LABEL_TEXT_W),ofsObj); 
    lv_obj_set_x(getLabel(LABEL_TEXT_E),ofsObj); 
    lv_obj_set_x(getLabel(LABEL_TEXT_S),ofsObj); 

    ESP_LOGE(TAG, "%d ", azimut);


    if ((azimut >= 360)) {
        uint16_t coef  = azimut / 360;
        azimut = azimut - (360 * coef);
    }
    ESP_LOGE(TAG, "%d ", azimut);
        


    sprintf (str,"%03d",azimut);


    setTextCanvasOled(0,str);

    setTextOled(LABEL_TEXT_AZ, str);
    setTextOled(LABEL_TEXT_N, "N");
    setTextOled(LABEL_TEXT_E, "E");
    setTextOled(LABEL_TEXT_W, "W");
    setTextOled(LABEL_TEXT_S, "S");

    if (azimut > 359){
        int coef = 1;
        coef = (azimut / 360 ); 
        azimut = azimut - (360 * coef);
    }

    posInit = ((azimut * 72) / 90);
    posInit = center - posInit;
    posText = posInit;
    if ( azimut <= 90 ) {


    }
    else if ( (azimut <= 180) && (azimut > 90) ) {

        ligne = 72;

    }
    else if ( (azimut <= 270) && (azimut > 180) ) {

        ligne = 144;
    }
    else if ( (azimut <= 360) && (azimut > 270) ) {

        ligne = 216;
    }

    setXPos(LABEL_TEXT_N,posText);
    if ((azimut > 300) && (azimut < 360))   setXPos(LABEL_TEXT_N,posText+286);

    setXPos(LABEL_TEXT_E,posText+72);
    setXPos(LABEL_TEXT_S,posText+145);
    setXPos(LABEL_TEXT_W,posText+214);  

    ESP_LOGE(TAG, "%d ", posInit);

    posInit = posInit + ligne;

    p1[0].x = posInit-(4 * delta);
    p1[1].x = posInit-(4 * delta);
    p2[0].x = posInit-(3 * delta);
    p2[1].x = posInit-(3 * delta);
    p3[0].x = posInit-(2 * delta);
    p3[1].x = posInit-(2 * delta);
    p4[0].x = posInit-delta;
    p4[1].x = posInit-delta;
    p5[0].x = posInit;
    p5[1].x = posInit;
    p6[0].x = posInit+delta;
    p6[1].x = posInit+delta;
    p7[0].x = posInit+(2 * delta);
    p7[1].x = posInit+(2 * delta);
    p8[0].x = posInit+(3 * delta);
    p8[1].x = posInit+(3 * delta);
    p9[0].x = posInit+(4 * delta);
    p9[1].x = posInit+(4 * delta);




    lv_obj_set_x(line1,ofsObj); 
    lv_obj_set_x(line2,ofsObj); 
    lv_obj_set_x(line3,ofsObj); 
    lv_obj_set_x(line4,ofsObj); 
    lv_obj_set_x(line5,ofsObj); 
    lv_obj_set_x(line6,ofsObj); 
    lv_obj_set_x(line7,ofsObj); 
    lv_obj_set_x(line8,ofsObj); 
    lv_obj_set_x(line9,ofsObj); 

    lv_line_set_points(line1, p1, 2 );
    lv_line_set_points(line2, p2, 2 );
    lv_line_set_points(line3, p3, 2 );
    lv_line_set_points(line4, p4, 2 );
    lv_line_set_points(line5, p5, 2 );
    lv_line_set_points(line6, p6, 2 );
    lv_line_set_points(line7, p7, 2 );
    lv_line_set_points(line8, p8, 2 );
    lv_line_set_points(line9, p9, 2 );


    //lv_canvas_draw_text(canvasCompass, 8, 8, 88, &compass_label_dsc, "test");

}


/*****************
 * User Interface
 ****************/
void lvgl_ui(lv_disp_t *disp){

    clearScreen();

    drawRectangle(0,0,40,32,1);
    drawRectangle(40,0,88,32,1);

    createLabel(LABEL_TEXT_AZ);
    createLabel(LABEL_TEXT_N);
    createLabel(LABEL_TEXT_E);
    createLabel(LABEL_TEXT_W);
    createLabel(LABEL_TEXT_S);

    setLongMode(LABEL_TEXT_AZ, LV_LABEL_LONG_SCROLL_CIRCULAR); /* Circular scroll */
    setLongMode(LABEL_TEXT_N, LV_LABEL_LONG_SCROLL_CIRCULAR); /* Circular scroll */
    setLongMode(LABEL_TEXT_E, LV_LABEL_LONG_SCROLL_CIRCULAR); /* Circular scroll */
    setLongMode(LABEL_TEXT_W, LV_LABEL_LONG_SCROLL_CIRCULAR); /* Circular scroll */
    setLongMode(LABEL_TEXT_S, LV_LABEL_LONG_SCROLL_CIRCULAR); /* Circular scroll */



    setTextOled( LABEL_TEXT_AZ, "F4DEB init ...");
    /* Size of the screen (if you use rotation 90 or 270, please set disp->driver->ver_res) */
    setPos(LABEL_TEXT_N, 82, 8);
    setPos(LABEL_TEXT_E, 200, 8);
    setPos(LABEL_TEXT_W, 41, 8);
    setPos(LABEL_TEXT_S, 200, 8);


    
    lv_obj_set_width(getLabel(LABEL_TEXT_N), disp->driver->hor_res);
    lv_obj_set_width(getLabel(LABEL_TEXT_E), disp->driver->hor_res);
    lv_obj_set_width(getLabel(LABEL_TEXT_W), disp->driver->hor_res);
    lv_obj_set_width(getLabel(LABEL_TEXT_S), disp->driver->hor_res);


    

    lv_draw_label_dsc_init(&azimut_label_dsc);
    azimut_label_dsc.color = lv_palette_main(LV_PALETTE_NONE);
    static lv_color_t azimutCbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(CANVAS_AZIMUT_WIDTH, CANVAS_AZIMUT_HEIGHT)];
    canvasAzimut = lv_canvas_create(lv_scr_act());
    lv_canvas_set_buffer(canvasAzimut, azimutCbuf, CANVAS_AZIMUT_WIDTH, CANVAS_AZIMUT_HEIGHT, LV_IMG_CF_TRUE_COLOR);
    lv_obj_set_pos(canvasAzimut,2,2);
    static lv_color_t azimut_cbuf_tmp[CANVAS_AZIMUT_WIDTH * CANVAS_AZIMUT_HEIGHT];
    memcpy(azimut_cbuf_tmp, azimutCbuf, sizeof(azimut_cbuf_tmp));
    lv_img_dsc_t img;
    img.data = (void *)azimut_cbuf_tmp;
    img.header.cf = LV_IMG_CF_TRUE_COLOR;
    img.header.w = CANVAS_AZIMUT_WIDTH;
    img.header.h = CANVAS_AZIMUT_HEIGHT;
    lv_canvas_fill_bg(canvasAzimut, lv_palette_lighten(LV_PALETTE_GREY, 3), LV_OPA_COVER);
    lv_canvas_transform(canvasAzimut, &img, 0, LV_IMG_ZOOM_NONE, 0, 0, CANVAS_AZIMUT_WIDTH / 2, CANVAS_AZIMUT_HEIGHT / 2, true);

    


/*    lv_draw_rect_dsc_t rect_dsc_compass;
    lv_draw_rect_dsc_init(&rect_dsc_compass);
    rect_dsc_compass.radius = 5;
    rect_dsc_compass.bg_opa = LV_OPA_COVER;
    //rect_dsc_compass.bg_grad.dir = LV_GRAD_DIR_HOR;
    //rect_dsc.bg_grad.stops[0].color = lv_palette_main(LV_PALETTE_ORANGE);
    //rect_dsc.bg_grad.stops[1].color = lv_palette_main(LV_PALETTE_ORANGE);
    rect_dsc_compass.border_width = 1;
    rect_dsc_compass.border_opa = LV_OPA_COVER;
    rect_dsc_compass.border_color = lv_color_black();
    //rect_dsc_compass.shadow_width = 10;
    //rect_dsc_compass.shadow_ofs_x = 10;
    //rect_dsc_compass.shadow_ofs_y = 10;

  */ 
    lv_draw_label_dsc_init(&compass_label_dsc);
    compass_label_dsc.color = lv_palette_main(LV_PALETTE_NONE);

    static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(CANVAS_COMPASS_WIDTH, CANVAS_COMPASS_HEIGHT)];

    canvasCompass = lv_canvas_create(lv_scr_act());
    lv_canvas_set_buffer(canvasCompass, cbuf, CANVAS_COMPASS_WIDTH, CANVAS_COMPASS_HEIGHT, LV_IMG_CF_TRUE_COLOR);
    lv_obj_set_pos(canvasCompass,42,2);
    lv_canvas_fill_bg(canvasCompass, lv_palette_lighten(LV_PALETTE_GREY, 3), LV_OPA_COVER);

    lv_canvas_draw_text(canvasCompass, 0, 6, 88, &compass_label_dsc, "012345678__");

    static lv_color_t cbuf_tmp[CANVAS_COMPASS_WIDTH * CANVAS_COMPASS_HEIGHT];
    memcpy(cbuf_tmp, cbuf, sizeof(cbuf_tmp));
    lv_img_dsc_t img1;
    img1.data = (void *)cbuf_tmp;
    img1.header.cf = LV_IMG_CF_TRUE_COLOR;
    img1.header.w = CANVAS_COMPASS_WIDTH;
    img1.header.h = CANVAS_COMPASS_HEIGHT;

    lv_canvas_fill_bg(canvasCompass, lv_palette_lighten(LV_PALETTE_GREY, 3), LV_OPA_COVER);
    lv_canvas_transform(canvasCompass, &img1, 0, LV_IMG_ZOOM_NONE, 0, 0, CANVAS_COMPASS_WIDTH / 2, CANVAS_COMPASS_HEIGHT / 2, true);
    
    initBoussole();

    boussole(0);
}



/*********************
 *  INITIALISATION 
 *  If do not compil, check version 8.3.0 in dependencies.lock file
lvgl/lvgl:
    component_hash: 7b7ee85e48c2eb35bb242a8c7e0e4cd702e150541afb3f69089fb7ba81554d14
    dependencies: []
    source:
      registry_url: https://components.espressif.com/
      type: service
    version: 8.3.0

 *********************/
void oled (void){ 
    ESP_LOGI(TAG, "Install panel IO");
    esp_lcd_panel_io_handle_t io_handle = NULL;
    esp_lcd_panel_io_i2c_config_t io_config = {
        .dev_addr = I2C_HW_ADDR,
        .scl_speed_hz = LCD_PIXEL_CLOCK_HZ,
        .control_phase_bytes = 1,               // According to SSD1306 datasheet
        .lcd_cmd_bits = LCD_CMD_BITS,   // According to SSD1306 datasheet
        .lcd_param_bits = LCD_CMD_BITS, // According to SSD1306 datasheet
        .dc_bit_offset = 6,                     // According to SSD1306 datasheet
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c(getI2cBus(), &io_config, &io_handle));

    ESP_LOGI(TAG, "Install SSD1306 panel driver");
    esp_lcd_panel_handle_t panel_handle = NULL;
    esp_lcd_panel_dev_config_t panel_config = {
        .bits_per_pixel = 1,
        .reset_gpio_num = PIN_NUM_RST,
    };
#if CONFIG_LCD_CONTROLLER_SSD1306
    esp_lcd_panel_ssd1306_config_t ssd1306_config = {
        .height = LCD_V_RES,
    };
    panel_config.vendor_config = &ssd1306_config;
    ESP_ERROR_CHECK(esp_lcd_new_panel_ssd1306(io_handle, &panel_config, &panel_handle));
#elif CONFIG_LCD_CONTROLLER_SH1107
    ESP_ERROR_CHECK(esp_lcd_new_panel_sh1107(io_handle, &panel_config, &panel_handle));
#endif

    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));

#if CONFIG_LCD_CONTROLLER_SH1107
    ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_handle, true));
#endif

    ESP_LOGI(TAG, "Initialize LVGL");
    const lvgl_port_cfg_t lvgl_cfg = ESP_LVGL_PORT_INIT_CONFIG();
    lvgl_port_init(&lvgl_cfg);

    const lvgl_port_display_cfg_t disp_cfg = {
        .io_handle = io_handle,
        .panel_handle = panel_handle,
        .buffer_size = LCD_H_RES * LCD_V_RES,
        .double_buffer = true,
        .hres = LCD_H_RES,
        .vres = LCD_V_RES,
        .monochrome = true,
        .rotation = {
            .swap_xy = false,
            .mirror_x = false,
            .mirror_y = false,
        }
    };
    disp = lvgl_port_add_disp(&disp_cfg);

    /* Rotation of the screen */
    lv_disp_set_rotation(disp, LV_DISP_ROT_NONE);

    ESP_LOGI(TAG, "Display LVGL Scroll Text");
    // Lock the mutex due to the LVGL APIs are not thread-safe
    if (lvglportlockDevice(0)) {
        lvgl_ui(disp);
        // Release the mutex
        lvglPortUnlockDevice();
    }
}



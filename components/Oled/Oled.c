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

static const char *TAG = "OLED : ";
//static i2c_master_bus_handle_t i2c_bus;

static lv_obj_t *label;
static lv_obj_t *scr;
static lv_disp_t *disp;

static lv_obj_t *line;
static lv_obj_t *line0;
//static lv_obj_t *line1;

lv_obj_t* line1, *line2, *line3;


static lv_obj_t * chart;

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

/********
 * LABEL
 ********/

void createLabel (void){
    lv_obj_t *scr = lv_disp_get_scr_act(disp);
    label = lv_label_create(scr);
    lv_label_set_text(label, "");
}

lv_obj_t*  getLabel(void){
    return label;
}

void setTextOled(char *text){
    lv_label_set_text(getLabel(), text);
}

void setTextRotation(int value){
    lv_disp_set_rotation(disp, value);
}

void setLongMode (int value){
    lv_label_set_long_mode(label, value); /* Circular scroll */
}

void setRecolor(bool status) {
    lv_label_set_recolor(label, status);
}

void setXPos(int value){
    lv_obj_set_x(label, value);
}

void setYPos(int value){
    lv_obj_set_y(label, value);
}

void setPos(int xvalue, int yvalue){
    lv_obj_set_pos(label, xvalue, xvalue);
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

/*************
 * DRAW LINE
 *************/
void initLine(int index){
    
}

void drawLine(int index, int x, int y, int X, int Y, int Size){
   
}



/****************
 * CLEAR SCREEN
 ***************/
void clearScreen (void){
    lv_obj_clean(lv_scr_act());
}

/*****************
 * User Interface
 ****************/
void lvgl_ui(lv_disp_t *disp){

    clearScreen();

    drawRectangle(0,0,40,32,1);

    drawRectangle(40,0,88,32,1);


    createLabel();
    setLongMode(LV_LABEL_LONG_SCROLL_CIRCULAR); /* Circular scroll */
    setTextOled( "F4DEB init ...");
    /* Size of the screen (if you use rotation 90 or 270, please set disp->driver->ver_res) */
    setPos(6,8);
    lv_obj_set_width(label, disp->driver->hor_res);
    //lv_obj_align(label, LV_ALIGN_TOP_MID, 5, 7);

    //initLine(0);
    //initLine(1);

    //drawLine(0,60,5,60,27,1);
    //drawLine(1,70,5,70,27,3);


    
    line1 = lv_line_create(lv_scr_act());
    line2 = lv_line_create(lv_scr_act());
    line3 = lv_line_create(lv_scr_act());
    
    static lv_point_t p1[] = {  {0,0},  {15,15} };
    static lv_point_t p2[] = {  {20,0}, {20,32} };
    static lv_point_t p3[] = {  {60,0}, {80,20} };
  
    lv_line_set_points(line1, p1, 2 );
    lv_line_set_points(line2, p2, 2 );
    lv_line_set_points(line3, p3, 2 );




    static lv_style_t lv_style_plain;
    lv_style_init(&lv_style_plain);
    lv_style_set_line_color(&lv_style_plain, white_color);
    lv_style_set_line_width(&lv_style_plain, 1); // Définir l'épaisseur de la ligne
    lv_obj_add_style(line1, &lv_style_plain, LV_PART_MAIN);
    lv_obj_add_style(line2, &lv_style_plain, LV_PART_MAIN);
    lv_obj_add_style(line3, &lv_style_plain, LV_PART_MAIN);




  
    


    //boussole();
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



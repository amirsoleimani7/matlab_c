#ifndef H_Line
#define H_Line

#define NPrime 14
#define from_bus_index 0 
#define to_bus_index 1 
#define r_index 2 
#define rx_index 3 
#define chrg_index 4 
#define raw_tap_index 5 
#define phase_shift_index 6 
#define tap_max_index 7 
#define tp_min_index 8 
#define tap_size_index 9 

class Line
{
    public:
    float from_bus;
    float to_bus;
    float r;
    float rx;
    float chrg;
    float raw_tap;
    float phase_shift;
    float tap_max;
    float tp_min;
    float tap_size;
};

#endif
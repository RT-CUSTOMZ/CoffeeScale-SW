#ifndef HX711_H
#define HX711_H

typedef void (*HX711_new_value_callback) (int value, void *obj);

typedef struct {
    HX711_new_value_callback new_value_callback;
    void * new_value_callback_obj;
} HX711;


extern void HX711_init(HX711 * obj);

extern void HX711_tick(HX711 * obj);

#endif //HX711_H

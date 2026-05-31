#include "adc_service.h"
#include "adc_driver.h"

void MQ150_service_init(void){
    adc_driver_init();
}

float adc_read_percentage(void){
    float mv = adc_read_mv();

    return mv*100.f/3300.f
}
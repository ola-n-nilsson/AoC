unsigned long seeds[]={79,14,55,13};

unsigned long seed_to_soil_map[] = {
  50, 98, 2,
  52, 50, 48
};

unsigned long soil_to_fertilizer_map[] = {
0,15,37,
37,52,2,
39,0,15
};

unsigned long fertilizer_to_water_map[] = {
49,53,8,
0,11,42,
42,0,7,
57,7,4
};

unsigned long water_to_light_map[] = {
88,18,7,
18,25,70
};

unsigned long light_to_temperature_map[] = {
45,77,23,
81,45,19,
68,64,13
};

unsigned long temperature_to_humidity_map[] = {
0,69,1,
1,0,69
};

unsigned long humidity_to_location_map[] = {
60,56,37,
56,93,4
};

typedef struct  {
  unsigned long *map;
  int len;
} maps_t;

maps_t maps[] = {
{ seed_to_soil_map, sizeof(seed_to_soil_map)/sizeof(seed_to_soil_map[0])},
{ soil_to_fertilizer_map, sizeof(soil_to_fertilizer_map)/sizeof(soil_to_fertilizer_map[0])},
{ fertilizer_to_water_map, sizeof(fertilizer_to_water_map)/sizeof(fertilizer_to_water_map[0])},
{ water_to_light_map, sizeof(water_to_light_map)/sizeof(water_to_light_map[0])},
{ light_to_temperature_map, sizeof(light_to_temperature_map)/sizeof(light_to_temperature_map[0])},
{ temperature_to_humidity_map, sizeof(temperature_to_humidity_map)/sizeof(temperature_to_humidity_map[0])},
{ humidity_to_location_map, sizeof(humidity_to_location_map)/sizeof(humidity_to_location_map[0])}
};













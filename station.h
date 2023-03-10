#ifndef _STATION_H_
#define _STATION_H_

/*

Representation of a train car.
*/
typedef struct TrainCar {
int weight; // weight of a train car
struct TrainCar *next; // next car in the sequence
} TrainCar;


// Representation of a train.

typedef struct Train {
int locomotive_power; // power of the locomotive
TrainCar train_cars; // first car in the sequence of train cars
} Train;


//Representation of a train station.

typedef struct TrainStation {
int platforms_no; // number of platforms
Train **platforms; // array of platforms
} TrainStation;

TrainStation* open_train_station(int platforms_no);
void close_train_station(TrainStation *station);
void show_existing_trains(TrainStation *station, FILE *f);
void arrive_train(TrainStation *station, int platform, int locomotive_power);
void leave_train(TrainStation *station, int platform);
void add_train_car(TrainStation *station, int platform, int weight);
void remove_train_cars(TrainStation *station, int platform, int weight);
void move_train_cars(TrainStation *station, int platform_a, int pos_a, 
                                int cars_no, int platform_b, int pos_b);
int find_express_train(TrainStation *station);
int find_overload_train(TrainStation *station);
int find_optimal_train(TrainStation *station);
int find_heaviest_sequence_train(TrainStation *station, int cars_no, 
                                    TrainCar **start_car);
void order_train(TrainStation *station, int platform);
void fix_overload_train(TrainStation *station);

#endif

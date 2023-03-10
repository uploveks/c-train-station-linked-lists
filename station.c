#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "station.h"


/* Create a station with a fixed number of platforms.
 *
 * platforms_no: the number of platforms of the station
 *
 * return: the station created
 */
TrainStation* open_train_station(int platforms_no) {
    if (platforms_no <= 0) {
        return NULL;
    }
    TrainStation *station = (TrainStation *)malloc(sizeof(TrainStation));
    if (station) {
        station->platforms_no = platforms_no;
        station->platforms = (Train **)malloc(platforms_no * sizeof(Train*));
    }
    if (station->platforms) {
        for (int i = 0; i < station->platforms_no; i++) {
            station->platforms[i] = (Train*)malloc(sizeof(Train));
            if(station->platforms[i]) {
                station->platforms[i]->locomotive_power = 0;
                station->platforms[i]->train_cars = NULL;
            }
        }
    }
    return station;
}


/* Release the memory allocated for the station.
 *
 * station: the existing train station
 */
void close_train_station(TrainStation *station) {
    int i  = 0;
    if (station) {
        if (station->platforms) {
            for (i = 0; i < station->platforms_no; i++) {
                if (station->platforms[i]) {
                    if (station->platforms[i]->train_cars) {
                        TrainCar *train = station->platforms[i]->train_cars;
                        while (train != NULL) {
                            station->platforms[i]->train_cars = station->platforms[i]->train_cars->next;
                            free(train);
                            train = station->platforms[i]->train_cars;
                        }
                    }
                    free(station->platforms[i]);
                }
        }
            free(station->platforms);
    }
        free(station); 
    }
}



/* Displays the trains stationed in the station.
 *
 * station: the existing train station
 * f: the file in which the display is made
 */
void show_existing_trains(TrainStation *station, FILE *f) {
    int i = 0;
    if (station == NULL) {
        return;
    }
    if (station->platforms == NULL) {
        return;
    }
    for (i = 0; i < station->platforms_no; i++) {
        if (station->platforms[i] == NULL) {
            fprintf(f, "%d: \n", i);
        } else {
            if (station->platforms[i]->train_cars == NULL) {
                fprintf(f, "%d: \n", i);
            } else {
                fprintf(f, "%d: (%d)", i, station->platforms[i]->locomotive_power);
                TrainCar *t = station->platforms[i]->train_cars->next;
                while (t != NULL) {
                    fprintf(f, "-|%d|", t->weight);
                    t = t->next;
                }
                fprintf(f, "\n");
            }
        }
    }
}



/* Add a locomotive to a platform.
 *
 * station: the existing train station
 * platform: the platform on which the locomotive is added
 * locomotive_power: traction power of the locomotive
 */
void arrive_train(TrainStation *station, int platform, int locomotive_power) {
    if (platform < 0 || platform >= station->platforms_no) {
        return;
    }
    if (locomotive_power < 0) {
        return;
    }
    if (station == NULL) {
        return;
    }
    if (station->platforms == NULL) {
        return;
    }
    if (station->platforms[platform] == NULL) {
        return;
    }
    if (station->platforms[platform]->train_cars != NULL) {
        return;
    } else {
        station->platforms[platform]->train_cars = (TrainCar*)malloc(sizeof(TrainCar));
        station->platforms[platform]->train_cars->weight = 0;
        station->platforms[platform]->locomotive_power = locomotive_power;
        station->platforms[platform]->train_cars->next = NULL;
        
    }
    
}


/* Release a platform.
 *
 * station: the existing train station
 * platform: the platform from which the train departs
 */
void leave_train(TrainStation *station, int platform) {
    if (platform < 0 || platform >= station->platforms_no) {
        return;
    }
    if (station == NULL) {
        return;
    }
    if (station->platforms == NULL) {
        return;
    }
    if (station->platforms[platform] == NULL) {
        return;
    }
    if (station->platforms[platform]->train_cars == NULL) {
        return;
    } else {
        TrainCar *temp = station->platforms[platform]->train_cars;
        while (temp != NULL) {
            station->platforms[platform]->train_cars = station->platforms[platform]->train_cars->next;
            free(temp);
            temp = station->platforms[platform]->train_cars;
        }
    }
}



/* Add a carriage to the end of a train.
 *
 * station: the existing train station
 * platform: the platform on which the train is located
 * weight: the weight of the added wagon
 */
void add_train_car(TrainStation *station, int platform, int weight) {
    if (platform < 0 || platform >= station->platforms_no) {
        return;
    }
    if (weight < 0) {
        return;
    }
    if (station == NULL) {
        return;
    }
    if (station->platforms == NULL) {
        return;
    }
    if (station->platforms[platform] == NULL) {
        return;
    }
    if (station->platforms[platform]->train_cars == NULL) {
        return;
    }
    TrainCar *t = (TrainCar*)malloc(sizeof(TrainCar)), *last = NULL;
    t->weight = weight;
    t->next = NULL;
        last = station->platforms[platform]->train_cars;
        while (last->next != NULL)
            last = last->next;
        last->next = t;
}



/* Removes wagons of a certain weight from a train.
 *
 * station: the existing train station
 * platform: the platform on which the train is located
 * weight: the weight of the removed wagon
 */
void remove_train_cars(TrainStation *station, int platform, int weight) {
    if (platform < 0 || platform >= station->platforms_no) {
        return;
    }
    if (weight < 0) {
        return;
    }
    if (station == NULL) {
        return;
    }
    if (station->platforms == NULL) {
        return;
    }
    if (station->platforms[platform] == NULL) {
        return;
    }
    if (station->platforms[platform]->train_cars == NULL) {
        return;
    } else {
        TrainCar *current = station->platforms[platform]->train_cars->next, 
            *prev = station->platforms[platform]->train_cars;
        while (current != NULL) {
            if (current->weight == weight) {
                prev->next = current->next;
                free(current);
                current = NULL;
            }
            if (current == NULL) {
                current = prev->next;
            } else {
                current = current->next;
                prev = prev->next;
            }
        }

    }

}


/* Move a sequence of carriages from one train to another.
 *
 * station: the existing train station
 * platform_a: the platform on which the train is located from where the carriages are removed
 * pos_a: the position of the first wagon in the sequence
 * cars_no: length of the sequence
 * platform_b: the platform on which the train is located where the carriages are added
 * pos_b: the position where the train sequence is added
 */
void move_train_cars(TrainStation *station, int platform_a, int pos_a, 
                                int cars_no, int platform_b, int pos_b) {
    if (station == NULL || station->platforms == NULL) {
        return;
    }
    if (pos_a < 1 || pos_b < 1) {
        return;
    }
    if (station->platforms[platform_a] == NULL || station->platforms[platform_b] == NULL) {
        return;
    }
    if (station->platforms[platform_a]->train_cars == NULL || station->platforms[platform_b]->train_cars == NULL) {
        return;
    }
    int nr_vagoane_a = 0, nr_vagoane_b = 0;
    TrainCar *vagon = station->platforms[platform_a]->train_cars;
    TrainCar *vagon_prev_start_a, *vagon_end_a;
    TrainCar *vagon_b_pos;
    while (vagon != NULL) {
        nr_vagoane_a++;
        if (nr_vagoane_a == pos_a) {
            vagon_prev_start_a = vagon;   
        }
        if (nr_vagoane_a == pos_a + cars_no) {
            vagon_end_a = vagon;
        }
        vagon = vagon->next;
    }
    if (pos_a >= nr_vagoane_a ) {
        return;
    }

    vagon = station->platforms[platform_b]->train_cars;
    while (vagon != NULL) {
        nr_vagoane_b++;
        if (nr_vagoane_b == pos_b) {
            vagon_b_pos = vagon;
        }
        vagon = vagon->next;
    }
    if (pos_b > nr_vagoane_b) {
        return;
    }
    if (cars_no <= 0 || cars_no > nr_vagoane_a - pos_a) {
        return;
    }

    TrainCar *temp = vagon_prev_start_a->next;
    vagon_prev_start_a->next = vagon_end_a->next;
    vagon_end_a->next = vagon_b_pos->next;
    vagon_b_pos->next = temp;
}



/* Find the fastest train.
 *
 * station: the existing train station
 *
 * return: the platform on which the train is located
 */
int find_express_train(TrainStation *station) {
    int i = 0;
    if (station == NULL || station->platforms == NULL) {
        return -1;
    }
    int weight = 0, max = 0, pos = 0;
    for (i = 0; i < station->platforms_no; i++) {
        if (station->platforms[i] == NULL || station->platforms[i]->train_cars == NULL) {
            weight = 0;
        } else {
            int train_weight = 0;
            TrainCar *temp = station->platforms[i]->train_cars->next;
            while (temp != NULL) {
                train_weight = train_weight + temp->weight;
                temp = temp->next;
            }
            int locomotive_powerr = station->platforms[i]->locomotive_power;
            weight = locomotive_powerr - train_weight;
        }
        if (max < weight) {
            max = weight;
            pos = i; 
        }
    }
    return pos;
}


/* Find the overloaded train.
 *
 * station: the existing train station
 *
 * return: the platform on which the train is located
 */
int find_overload_train(TrainStation *station) {
    int i = 0;
    if (station == NULL || station->platforms == NULL) {
        return -1;
    }
    for (i = 0; i < station->platforms_no; i++) {
        if (station->platforms[i] == NULL || station->platforms[i]->train_cars == NULL) {
            continue;
        } else {
            int train_weight = 0;
            int min = 0;
            TrainCar *temp = station->platforms[i]->train_cars->next;
            while (temp != NULL) {
                train_weight = train_weight + temp->weight;
                temp = temp->next;
            }
            int locomotive_powerr = station->platforms[i]->locomotive_power;
            min = locomotive_powerr - train_weight;
            if (min < 0) {
                return i;
            }
        }
    }
    return -1;
}


/* Find the train with the optimal load.
 *
 * station: the existing train station
 *
 * return: the platform on which the train is located
 */
int find_optimal_train(TrainStation *station) {
    int i = 0;
    if (station == NULL || station->platforms == NULL) {
        return -1;
    }
    int weight = 0, min = INT_MAX, pos = 0;
    for (i = 0; i < station->platforms_no; i++) {
        if (station->platforms[i] == NULL || station->platforms[i]->train_cars == NULL) {
            continue;
        } else {
            int train_weight = 0;
            TrainCar *temp = station->platforms[i]->train_cars->next;
            while (temp != NULL) {
                train_weight = train_weight + temp->weight;
                temp = temp->next;
            }
            weight = station->platforms[i]->locomotive_power - train_weight;
        }
        if (weight < min) {
            min = weight;
            pos = i;
        }
    }
    return pos;
}


/* Find the train with the load not distributed well.
 *
 * station: the existing train station
 * cars_no: the length of the train sequence
 *
 * return: the platform on which the train is located
 */
int find_heaviest_sequence_train(TrainStation *station, int cars_no, TrainCar **start_car) {
    if (station == NULL || station->platforms == NULL) {
        return -1;
    }
    if (cars_no < 0) {
      return -1;
    }
    int max_seq_train = 0, max_pos_in = 0, max_platform = 0;
    TrainCar *start = NULL;
    for (int i = 0; i < station->platforms_no; i++) {
         if (station->platforms[i]->train_cars != NULL) {
            TrainCar *temp = station->platforms[i]->train_cars->next, 
                *max_pos = station->platforms[i]->train_cars->next, *curr = max_pos;
            int nr_vagoane = 0;
            while (temp != NULL) {
                nr_vagoane++;
                temp = temp->next;
            }
            if (cars_no <= nr_vagoane) {
                for (int i = 0; i < nr_vagoane + 1; i++) {
                    int sum_seq = 0;
                    for (int j = 0; j < cars_no; j++) {
                        sum_seq = sum_seq + curr->weight;
                        curr = curr->next;
                    }
                    if (sum_seq > max_seq_train) {
                        max_seq_train = sum_seq;
                        start = max_pos;
                    }
                    if(curr == NULL) {
                        break;
                    }
                    max_pos = max_pos->next;
                    curr = max_pos;
                }
                if (max_seq_train > max_platform) {
                    max_platform = max_seq_train;
                    max_pos_in = i;
                    *start_car = start;
                }
            }
        }
    }
    if (max_platform != 0) {
        return max_pos_in;
    }
    *start_car = NULL;
    return -1;
}

TrainCar* swapNodes(TrainCar *Node1, TrainCar *Node2) {
    TrainCar *temp = Node2->next;
    Node2->next = Node1;
    Node1->next = temp;
    return Node2;
}

/* Sorts the wagons in a train in descending order of weight.
 *
 * station: the existing train station
 * platform: the platform on which the train is located
 */
void order_train(TrainStation *station, int platform) {
    if (platform < 0 || platform >= station->platforms_no) {
        return;
    }
    if (station == NULL) {
        return;
    }
    if (station->platforms == NULL) {
        return;
    }
    if (station->platforms[platform] == NULL) {
        return;
    }
    if (station->platforms[platform]->train_cars == NULL) {
        return;
    } else {
        TrainCar *head =  station->platforms[platform]->train_cars->next;
        int nr_vagoane = 0;
        while (head != NULL) {
            nr_vagoane++;
            head = head->next;
        }
        int i, j, swapped;
        for (i = 0; i <= nr_vagoane; i++) {
            head =  station->platforms[platform]->train_cars;
            swapped = 0;
            for (j = 0; j < nr_vagoane - i - 1; j++) {
                TrainCar *Node1 = head->next;
                TrainCar *Node2 = Node1->next;
                if (Node1->weight < Node2->weight) {
                    head->next = swapNodes(Node1, Node2);
                    swapped = 1;
                }
                head = head->next;
            }
            if (swapped == 0)
                break;
        }
    }
}


/* Remove a carriage from the overloaded train.
 *
 * station: the existing train station
 */
void fix_overload_train(TrainStation * station) {
  if (station == NULL || station -> platforms == NULL) {
    return;
  }
  int overload_train = find_overload_train(station);
  if (overload_train == -1) {
    return;
  }
  TrainCar *train = station->platforms[overload_train]->train_cars->next;
    int pos = 1, weight = 0, nr_vagoan = 0;
    while (train != NULL) {
      weight = weight + train->weight;
      train = train->next;
    }
    if (weight == station->platforms[overload_train]->locomotive_power)
    return;
    int min_diff = station->platforms[overload_train]->locomotive_power;
    train = station->platforms[overload_train]->train_cars->next;
    while(train != NULL){
      nr_vagoan++;
      if (weight - train->weight >= station->platforms[overload_train]->locomotive_power && 
                                                                    weight - train->weight <= min_diff) {
        min_diff = weight - train->weight;
        pos = nr_vagoan;
      }
      train = train->next;
    }
    int count = pos - 1;
    TrainCar* prev = station->platforms[overload_train]->train_cars;
    TrainCar *to_delete = prev;
    while (prev != NULL && count > 0) {
      prev = prev->next;
      count--;
    }
    if (count == 0 && prev->next != NULL) {
      to_delete = prev->next;
      prev->next = to_delete->next;
      free(to_delete);
    }
 
}

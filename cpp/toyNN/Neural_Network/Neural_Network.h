//
//  Neural_Network.h
//  toyNN
//
//  Created by Jeffrey Fisher on 2/11/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

#ifndef Neural_Network_h
#define Neural_Network_h

#include <fstream>
#include <vector>
#include "Neural_Layer.h"

class Neural_Network{
    public:
        //---Constructors---//
        Neural_Network(void);
        Neural_Network(std::vector<unsigned int> neurons);
        Neural_Network(std::string name);
        //---Copy Constructors---//
        Neural_Network(const Neural_Network &obj);
        Neural_Network(const Neural_Network &obj, std::string new_name);
        //---Destructors---//
        ~Neural_Network(void);
    
        //---Set---//
        void set_name(std::string name);
        //---Get---//
        std::string get_name(void);
    
    
        //---File_Write---//
        void save_file(void);
        void save_file(std::string name);
        //---File_Read---//
        void get_file(void);
        void get_file(std::string name);
        void setup_from_file(void);
    
    
        //---Predict---//
        Tensor feed_forward(Tensor input_data);
        Tensor predict(Tensor input_data);
        //---Learn---//
        void train(Tensor input_data, Tensor target_data);
    
    private:
        //---Network_Structure---//
        std::vector<unsigned int> neurons; //Address = layer, Value = #nodes/layer
        std::vector<Neural_Layer> layers;
    
        //---Settings---//
        std::string name = "Neural_Network";
        float learning_rate = 0.2;
        unsigned int training_runs = 1000;
};
#endif /* Neural_Network_h */

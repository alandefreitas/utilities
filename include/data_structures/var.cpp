//
// Created by Alan de Freitas on 30/03/17.
//

#include "var.h"

void var::set(string x){
    if (x != string_data){
        string_data = x;
        string_known = true;
        int_known = false;
        double_known = false;
        bool_known = false;
        array_data.clear();
        pointer_data = nullptr;
    }
}

void var::set(int x){
    if (x != int_data){
        int_data = x;
        string_known = false;
        string_data.clear();
        int_known = true;
        double_known = false;
        bool_known = false;
        array_data.clear();
        pointer_data = nullptr;
    }
}

void var::set(double x){
    if (x != double_data){
        double_data = x;
        string_known = false;
        string_data.clear();
        int_known = false;
        double_known = true;
        bool_known = false;
        array_data.clear();
        pointer_data = nullptr;
    }
}

void var::set(bool x){
    if (x != bool_data){
        bool_data = x;
        string_known = false;
        string_data.clear();
        int_known = false;
        double_known = false;
        bool_known = true;
        array_data.clear();
        pointer_data = nullptr;
    }
}

var var::cast(datatype target_type){
    if (target_type == current_type){
        return *this;
    } else {
        switch(current_type){
            case Boolean:
                switch (target_type){
                    case Integer:
                        return (bool_data == false ? 0 : 1);
                    case Float:
                        return (bool_data == false ? 0. : 1.);
                    case String:
                        return (bool_data == false ? "False" : "True");
                }
                break;
            case Integer:
                switch (target_type){
                    case Float:
                        return ((double) int_data);
                    case Boolean:
                        return (int_data==0) ? false : true;
                    case String:
                        return (itos(int_data));
                }
                break;
            case Float:
                switch (target_type){
                    case Integer:
                        return ((int) double_data);
                    case Boolean:
                        return (double_data==0.0) ? false : true;
                    case String:
                        return (dtos(double_data));
                }
                break;
            case String:
                switch (target_type){
                    case Integer:
                        return (stoi(string_data));
                    case Boolean:
                        return (string_data=="" || string_data == "0") ? false : true;
                    case String:
                        return (stod(string_data));
                }
                break;
            case Array:
                switch (target_type){
                    case Integer:
                        return ((int) double_data);
                    case Boolean:
                        return (!array_data.empty());
                    case String:
                        return (dtos(double_data));
                }
                break;
            case Null:
                switch (target_type){
                    case Integer:
                        return 0;
                    case Float:
                        return 0.;
                    case Boolean:
                        return false;
                    case String:
                        return "";
                }
                break;
            default:
                switch (target_type){
                    case Integer:
                        return var(0);
                    case Float:
                        return var(0.);
                    case Boolean:
                        return var(false);
                    case String:
                        return var("");
                }
                return var();
        }
    }
}
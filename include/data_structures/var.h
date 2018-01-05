//
// Created by Alan de Freitas on 30/03/17.
//

#ifndef TREE_VAR_H
#define TREE_VAR_H

#include <string>


// this class defines a php-like or javascript-like variable
// reference: http://php.net/manual/en/langref.php
class var {
public:
    // Possible datatypes
    enum datatype {Integer, Float, String, Boolean, Array, Object, Callable, Null, Pointer, Nan};

    // Constructors
    var(string x){set(x);}
    var(int x){set(x);}
    var(double x){set(x);}
    var(bool x){set(x);}

    // Modifying functions
    void set(string x);
    void set(int x);
    void set(double x);
    void set(bool x);

    var cast(datatype target_type);
    void settype(datatype type);
    var round(){
        *this = *this+0.5;
        cast(Integer);
    }

    // Non-modifying functions
    bool is_string();
    bool is_int();
    bool is_double();
    bool is_bool();
    bool is_null();
    bool is_nan();
    string get_type();

    // operators
    // operator / (if two ints are divided, a float is returned)

private:
    // Four scalar types:
    string string_data = {""};
    int int_data = {0};
    double double_data = {0.};
    bool bool_data = {false};
    // Other types
    map<var,var> array_data;
    var* pointer_data = nullptr;

    // pre-processed data
    bool string_known = {false};
    bool int_known = {false};
    bool double_known = {false};
    bool bool_known = {false};

    // current type used in the variable
    datatype current_type = Null;
};


#endif //TREE_VAR_H

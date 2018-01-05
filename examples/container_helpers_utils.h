//
// Created by Alan de Freitas on 03/01/18.
//


struct comparable_animal
    // If two objects can be equal, also use boost::partially_ordered
    // see list at : http://www.boost.org/doc/libs/1_65_1/libs/utility/operators.htm
        : public less_than_comparable<comparable_animal> {
    std::string name;
    int legs;

    comparable_animal(std::string n, int l) : name{std::move(n)}, legs{l} {}

    bool operator<(const comparable_animal &a) const { return legs < a.legs; }
};

class animal {
    public:
        animal() = default;

        animal(int legs) : legs_{legs} {}

        int legs() const { return legs_; }

    private:
        friend class boost::serialization::access;

        template<typename Archive>
        void serialize(Archive &ar, const unsigned int version) { ar & legs_; }

        int legs_;
};

struct free_standing_animal {
    int legs_;

    free_standing_animal() = default;

    free_standing_animal(int legs) : legs_{legs} {}

    int legs() const { return legs_; }
};



template<typename Archive>
void serialize(Archive &ar, free_standing_animal &a, const unsigned int version) {
    ar & a.legs_;
}

class named_animal {
    public:
        named_animal() = default;

        named_animal(int legs, std::string name) :
                legs_{legs}, name_{std::move(name)} {}

        int legs() const { return legs_; }

        const std::string &name() const { return name_; }

    private:
        friend class boost::serialization::access;

        template<typename Archive>
        friend void serialize(Archive &ar, named_animal &a, const unsigned int version);

        int legs_;
        std::string name_;
};

template<typename Archive>
void serialize(Archive &ar, named_animal &a, const unsigned int version) {
    ar & a.legs_;
    ar & a.name_;
}

class compatible_animal {
    public:
        compatible_animal() = default;

        compatible_animal(int legs, std::string name) :
                legs_{legs}, name_{std::move(name)} {}

        int legs() const { return legs_; }

        const std::string &name() const { return name_; }

    private:
        friend class boost::serialization::access;

        template<typename Archive>
        friend void serialize(Archive &ar, compatible_animal &a, const unsigned int version);

        int legs_;
        std::string name_;
};

template<typename Archive>
void serialize(Archive &ar, compatible_animal &a, const unsigned int version) {
    ar & a.legs_;
    if (version > 0) {
        ar & a.name_;
    }
}

BOOST_CLASS_VERSION(compatible_animal, 1)

class bird
        : public animal {
    public:
        bird() = default;

        bird(int legs, bool can_fly) :
                animal{legs}, can_fly_{can_fly} {}

        bool can_fly() const { return can_fly_; }

    private:
        friend class boost::serialization::access;

        template<typename Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & boost::serialization::base_object<animal>(*this);
            ar & can_fly_;
        }

        bool can_fly_;
};

BOOST_CLASS_EXPORT(bird)

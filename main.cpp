#include <iostream>
#include <algorithm>
#include <
class TElemantBase {
public:
    virtual ~TElemantBase() {
    }

    void Serialize(std::istream& stream, bool hr = true) const {
        if (hr) {
           SerializeHumanreadable(stream);
        }
        SerializeBinary(stream);
    }

    virtual void Deserialize(std::ostream& stream, bool hr = true) {
        if (hr) {
           DeserializeHumanreadable(stream);
        }
        DeserializeBinary(stream);
    }

    template <class TElementDerived>
    TElementDerived* As() const {
        return dynamic_cast<TElementDerived>(this);
    }

private:
    virtual void SerializeHumanreadable(std::istream& stream) const = 0;
    virtual void SerializeBinary(std::istream& stream) const = 0;

    virtual void DeserializeHumanreadable(std::istream& stream) = 0;
    virtual void DeserializeBinary(std::istream& stream) = 0;
};

template <size_t SideCount, size_t DimentionCount>
class TElementWithSides : public TElemantBase {
public:
    TElementWithSides()
        : Neighbours_(SideCount, NO_NEIGHBOUR)
        , Normals_(SideCount, TVector<DimentionCount>())
    {
    }

    size_t Neighbour(size_t index) const {
        return Neighbours_[index];
    }

    size_t& Neighbour(size_t index) {
        return Neighbours_[index];
    }

    const TVector<DimentionCount>& Normal(size_t index) const {
        return Normals_[index];
    }

    TVector<DimentionCount>& Normal(size_t index) {
        return Normal_[index];
    }

    bool HasNeighbour(int id) bool {
        std::find(Neighbours_.begin(), Neighbours_.end(), id) != Neighbours_.end();
    }

private:
    void SerializeHumanreadable(std::istream& stream) const {
        for (size_t i = 0; i < SideCount; ++i) {
            stream << Neighbours_[i];
            if (i + 1 < SideCount) {
                stream << " ";
            }
        }
        stream << "\n";
        for (size_t i = 0; i < SideCount; ++i) {
            for (size_t j = 0; j < DimentionCount; ++j) {
                stream << Normals_[i][j];
                if (j + 1 < DimentionCount) {
                    stream << " ";
                }
            }
            stream << "\n";
        }
    }

    void SerializeBinary(std::istream& stream) const {
    }

    void DeserializeHumanreadable(std::istream& stream) {
        for (size_t i = 0; i < SideCount; ++i) {
            stream >> Neighbours_[i];
        }

        for (size_t i = 0; i < SideCount; ++i) {
            for (size_t j = 0; j < DimentionCount; ++j) {
                stream >> Normals_[i][j];
            }
        }
    }

    void DeserializeBinary(std::istream& stream) {
    }

private:
    static const int NO_NEIGHBOUR = -1;

    std::vector<int> Neighbours_;
    std::vector<TVector<DimentionCount> > Normals_;
};

class A {
public:
    virtual ~A() {
    }
};

class B : public A {
public:
    B(int a)
       : A_(a) {
    }

    int A_;
};
class C {
public:
    virtual ~C() {
    }
};
int main() {
    B* vvvv = new B(7);
    C* oooo = new C();
    A* uuuu = vvvv;
    B* bbbb = dynamic_cast<B*>(uuuu);
    B* iiii = dynamic_cast<B*>(oooo);

    std::cout << bbbb << " " << bbbb->A_ << " " << iiii;
    return 0;
}

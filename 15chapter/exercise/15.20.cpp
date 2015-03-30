class Base{void memfcn(Base &b){b = *this;}};
class Sneaky:public Base{void memfcn(Base &b){b = *this;}};
class pub_derv:public Base{void memfcn(Base &b){b = *this;}};
class priv_derv:private Base{void memfcn(Base &b){b = *this;}};
class prot_derv:protected Base{void memfcn(Base &b){b = *this;}};
class derived_from_public:public pub_derv{void memfcn(Base &b){b = *this;}};
class derived_from_private:public priv_derv{};
class derived_from_protected:public prot_derv{};
int main()
{
    pub_derv d1;
    priv_derv d2;
    prot_derv d3;
    derived_from_public dd1;
    derived_from_private dd2;
    derived_from_protected dd3;
    Base *p = &d1;
    p = &dd3;
    return 0;
}

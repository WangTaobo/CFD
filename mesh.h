class Mesh1D 
{
public:
    Mesh1D ();
    Mesh1D (double L, int N);
    ~Mesh1D ();
    virtual void BuildMesh (const char method);
    virtual void MethodA ();
    virtual void MethodB ();
private:
    int N;
    double alpha = 1.0;
    double* x_pt = new double[N]{};
    double* x_fc = new double[N]{};
    double L;
};